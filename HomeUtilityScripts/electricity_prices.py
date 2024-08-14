from bs4 import BeautifulSoup
from datetime import datetime
import requests
import json


electricty_page = requests.get("https://oomi.fi/en/electricity/electricity-contracts/active/spot-price-of-electricity/")
eSoup = BeautifulSoup(electricty_page.text, "html.parser")

prices = [] # numeric manipulable values
hours = [] # string non manipulable values

def find_prices():
    # put prices and hours in regular list objects
    for price in eSoup.find_all("span", attrs={"class":"with_vat"}):
        prices.append(float((price.text).replace(',','.')))

    for adjacent_td in eSoup.find_all('td', attrs={"class":"min-width"}):
        
        next_td = adjacent_td.find_next_sibling('td')
        if next_td:
            h = next_td.text.replace(":00", "")
            hours.append(h)

    if len(prices) == 0 : 
        print("search did not find anything")
        return False
    return True


def calc_avg(lst):
     return round((sum(lst)/len(lst)),2)

# returns list of tuples (hour, price)
def get_cheapest_times(prices, hours):
    avg = calc_avg(prices)
    cheapest = []

    for i in range(len(prices)):
        if prices[i] < avg:
            cheapest.append((hours[i],prices[i]))

    return cheapest

# returns float of price electricity for the current hour
def get_current_price(prices, hours):
    now = datetime.now()
    current_time = now.strftime("%H")
    i = hours.index(current_time)
    return prices[i]
    
# packs the whole of the electricity prices informations
# and insights into a json file
def package_information():

    avg = calc_avg(prices)
    cheapest = get_cheapest_times(prices, hours)
    # list containing hour/price dicts
    hour_price = [dict(zip(['hour','price'], value)) for value in zip(hours, prices)]
    # list containing cheapest hour / price dicts
    cheapest_hour_price = [dict(zip(['hour','price'], value)) for value in cheapest]
    
    data = {
        "hour_price": hour_price,
        "average_price": avg,
        "cheapest_times": cheapest_hour_price
    }

    with open('prices.json' , 'w') as f:
        json.dump(data, f, indent=1)

    #print(data)
    print("electricity prices json created")


def main():
    if(not find_prices()):
        #print(electricty_page.text)
        return
    
    avg = calc_avg(prices)
    print(f"average of prices is: {avg}")
    cheapest = get_cheapest_times(prices, hours)
    print("cheapest times")
    for times in cheapest:
        print(f"{times[0]} --> {times[1]}")
    current_price = get_current_price(prices, hours)
    print(f"Current price is {current_price}")
    package_information()



if __name__ == "__main__":
    main()