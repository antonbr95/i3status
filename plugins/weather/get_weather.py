#!/bin/python3
from time import sleep
from bs4 import BeautifulSoup
import urllib3 
urllib3.disable_warnings()

def write_day(s):
	print("writing to day")
	f = open('day', 'w')
	f.write(s)
	f.close()
	
def write_temperature(s):
	print("writing to temperature")
	f = open('temperature', 'w')
	f.write(s)
	f.close()

def write_icon(s):
	icon = ''
	# alt = ziemlich sonnig
	if 'ziemlich sonnig' in s:
		icon = '🌤'
	# alt = Sonne und Wolken im Wechsel
	elif 'Sonne und Wolken im Wechsel' in s:
		print('s = "' + s + '"')
		icon = '🌥'
	# alt = sonnig
	elif 'sonnig' in s:
		icon = '☼'
	# alt = wenige Gewitter
	elif 'wenige Gewitter' in s:
		icon = '🌩'
	# alt = teils sonnig, teils Schauer
	elif 'teils sonnig, teils Schauer' in s:
		icon = '🌦'
	# alt = regnerisch
	elif 'regnerisch' in s:
		icon = '🌧'
	else:
		# TODO: find out other names
		icon = s
		print('after else: s = "' + s + '"')
	print("writing to icon: " + icon)
	f = open('icon', 'w')
	f.write(icon)
	f.close()

def write_weather_string(s):
	print("writing to weather_string")
	f = open('weather_string', 'w')
	f.write(s)
	f.close()

http = urllib3.PoolManager()
url = 'http://www.srf.ch/meteo'

while True:
	meteo_html = http.request('GET', url)
	soup = BeautifulSoup(meteo_html.data, 'lxml')

	for tag in soup.find_all('span'):
		#print('test = "' + tag.text + '"')
		tmp = tag.text.replace('\xa0', ' ')
		set = tmp.split(' ')
		if ('Heute' in set):
			print (set)
			write_day('Heute')
			continue
		if ('Morgen' in set):
			print (set)
			write_day('Morgen')
			continue
		print(set)
		write_temperature(set[0])
		break

	for tag in soup.find_all('img'):
		if 'SRF Meteo' in tag['title']:
			print('reading weather info for icon: ' + tag['alt'])
			write_icon(tag['alt'])
			write_weather_string(tag['alt'])
			break

	# wait one minute
	sleep(600)
