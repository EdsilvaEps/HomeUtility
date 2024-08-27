from bs4 import BeautifulSoup
#from datetime import datetime
import requests
import json


weather_page = requests.get("https://www.foreca.com/100643492/Oulu-Finland/hourly?day=0")
soup = BeautifulSoup(weather_page.text,"html.parser")

hours = []
temps = []
rain_chance = []

print("weather forecast")
# put hours, temperature and rain chance in lists
for hourly_item in soup.find_all("div", attrs={"class":"hour"}):
    hour = hourly_item.find("span", attrs={"class":"value time time_12h"})
    temp = hourly_item.find("span", attrs={"class":"value temp temp_c"})
    rain_ch = hourly_item.find("span", attrs={"class":"precipChance"})
    hours.append(hour.text)
    temps.append(temp.text)
    rain_chance.append(rain_ch.text)

for i in range(len(hours)):
    print(f"{hours[i]} | temperature: {temps[i]} | {rain_chance[i]} ")

if len(temps) == 0 : 
    print("search did not find anything")
    exit

# packs the whole of the electricity prices informations
# and insights into a json file
def package_information():

    # list of dicts containin hour, temperature and precipitation chance:
    temp_objs = [dict(zip(['hour','temp','precip'], value)) for value in zip(hours, temps, rain_chance)]
    #print(temp_objs)

    data = {
        'tempObjs' : temp_objs 
    }
   
    with open('weather.json' , 'w') as f:
        json.dump(data, f, indent=1)

    print("weather forecast json created")
    

def main():
    package_information()

if __name__ == "__main__":
    main()