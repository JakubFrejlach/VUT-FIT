#!/usr/bin/env python3

# IPK - project 1 - variant 2 - Client for OpenWeatherMap API
# 17.3.2019
# Author - Jakub Frejlach (xfrejl00)
# My API key - 97a125611972d22696c880b421b1f971

import sys
import json
import socket
import re

#Arguments check
if(len(sys.argv) != 3):
    sys.stderr.write('ERROR: Wrong number of params.\n')
    sys.exit(1)

#HOST and PORT taken from https://openweathermap.org/ via web browser developer tool
HOST = 'api.openweathermap.org'
PORT = 80


#Valid API key and city name given by user
API_KEY = sys.argv[1].encode('utf-8')
CITY = sys.argv[2].encode('utf-8').lower()


#Basics taken from https://realpython.com/python-sockets/
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:

    #Checking if socket was succesfully created via file descriptor
    if(s.fileno() == -1):
        s.close()
        sys.stderr.write('ERROR: Socket failed.\n')
        sys.exit(1)

    try:
        s.connect((HOST, PORT))

    #Handling exception when HOST is unavailable
    except Exception as e:
         s.close()
         sys.stderr.write('ERROR: Something\'s wrong with %s:%d. Exception is %s.\n' % (HOST, PORT, e))
         sys.exit(1)

    #Sending request
    s.sendall(b'GET /data/2.5/weather?q=%s&APPID=%s&units=metric HTTP/1.1\r\nHOST:api.openweathermap.org\r\n\r\n' % (CITY, API_KEY))
    data = s.recv(1024)

#Return code extraction from API data
return_code = re.findall(r' ([0-9].*?)\\', str(data))[0]

if(return_code != '200 OK'):
    sys.stderr.write('ERROR: Request failed with code %s\n' % return_code)
    sys.exit(1)

#Spliting HTTP balast from API data and loading valid data to json format
data = data.split(b'\r\n\r\n', 1)[1]
json_data = json.loads(data.decode('utf-8'))

#Printing weather data from json
print (json_data['name'])
print (json_data['weather'][0]['description'])
print ('Temperature: ', json_data['main']['temp'],'°C', sep='')
print ('Humidity: ', json_data['main']['humidity'],'%', sep='')
print ('Pressure: ', json_data['main']['pressure'],'hPa',sep='')
print ('Wind speed: ', round(json_data['wind']['speed']*3.6,2),'km/h',sep='')

#Wind deg is sometimes missing in API data
if 'deg' not in json_data['wind']:
    print('Wind deg: Unavailable')
else:
    print ('Wind deg:', json_data['wind']['deg'])
