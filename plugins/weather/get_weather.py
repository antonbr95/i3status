#!/bin/python3
from time import sleep
from bs4 import BeautifulSoup
import urllib3 
import sys
import os
urllib3.disable_warnings()

def write_day(s, path):
	f = open(path + 'day', 'w')
	f.write(s)
	f.close()
	
def write_temperature(s, path):
	f = open(path + 'temperature', 'w')
	f.write(s)
	f.close()

def write_icon(s, path):
	icon = ''
	# alt = ziemlich sonnig
	if 'ziemlich sonnig' in s:
		icon = '🌤'
	# alt = Sonne und Wolken im Wechsel
	elif 'Sonne und Wolken im Wechsel' in s:
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
	# alt = Dauerregen
	elif 'Dauerregen' in s:
		icon = '🌧 🌧'
	else:
		# TODO: find out other names
		icon = s
	print("writing to icon: " + icon)
	f = open(path + 'icon', 'w')
	f.write(icon)
	f.close()

def write_weather_string(s, path):
	f = open(path + 'weather_string', 'w')
	f.write(s)
	f.close()

def get_weather():
	http = urllib3.PoolManager()
	url = 'http://www.srf.ch/meteo'

	meteo_html = http.request('GET', url)
	soup = BeautifulSoup(meteo_html.data, 'lxml')

	# get path
	path = __file__
	path_length = path.rfind('/')
	path = path[:path_length + 1] 
	# path is now the absolute path to the directory of this .py file ending with '/'

	for tag in soup.find_all('span'):
		tmp = tag.text.replace('\xa0', ' ')
		set = tmp.split(' ')
		if ('Heute' in set):
			print (set)
			write_day('Heute', path)
			continue
		if ('Morgen' in set):
			print (set)
			write_day('Morgen', path)
			continue
		print(set)
		write_temperature(set[0], path)
		break

	for tag in soup.find_all('img'):
		if 'SRF Meteo' in tag['title']:
			print('reading weather info for icon: ' + tag['alt'])
			write_icon(tag['alt'], path)
			write_weather_string(tag['alt'], path)
			break

if len(sys.argv) == 1:
	get_weather()
elif len(sys.argv) > 1 and sys.argv[1] == 'loop':
	while True:
		get_weather()
		sleep(600)
