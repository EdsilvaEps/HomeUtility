from bs4 import BeautifulSoup
#from datetime import datetime
import requests

# https://putricinta.com/dj-live-stream/
page = requests.get("https://influencersgonewild.com/")
soup = BeautifulSoup(page.text,"html.parser")

interest = ['Kat Wonders', 'Vicky Stark']
found = 0

for item in soup.find_all("a", attrs={"class":"g1-frame"}):
    for person in interest:
        if(person in item['title']):
            print(item['title'])
            found +=1

