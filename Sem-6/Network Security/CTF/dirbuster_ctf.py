#!/usr/bin/python3
"""The main implementation file for pybuster.
It contains the Pybuster class that is used
to create and run the scanner"""
import requests, urllib.request
from requests_ntlm import HttpNtlmAuth
from random import shuffle, choice
import concurrent.futures
import argparse
from string import ascii_letters
import sys, time
from pydirbuster import utils, __version__
from pathlib import Path
from collections import defaultdict
from tqdm import tqdm

class Pybuster(object):
	"""The Pybuster class is the main interface for this website scanner.

	Pybuster Class:

	param: url - The website base url for scanning.
	type: str

	param: wordfile - The filepath, relative or absolute for wordlist.
	type: str

	param: threads - The number of threads for the scanner to run. Default = 15
	type: int

	param: exts - The list of file extensions to check. default = ['']
	It is best pass it a list, ie. ['php', 'html', 'png'], but it can be
	passed a comma delimited string ex., 'php,html,png'
	type: list

	param: logfile - The name of an output file write results to.
	type: str

	param: codes - The http status codes to accept in responses.
	Can be passed a list of numbers in either int or str forms, or a 
	comma delimited string. So ['200','204','301','302','307','401','403'],
	[200,204,301,302,307,401,403], and "200,204,301,302,307,401,403" are all
	valid, but the inner values must be able to converted to integers.
	Default = [200,204,301,302,307,401,403]
	param: user - HTTP username - Default = None
	type: list

	param: password - HTTP password - Default = None
	type: str

	param: force - Switch for forcing processing on a wildcard matching webserver.
	To switch on this option use the boolean value True, but any valid truthy value
	would work. Default = False
	type: bool

	param: user_agent - The user agent to use in http requests. If None is
	passed as the user_agent, a randomizer will be called to supply one.
	Default is the current python requests user agent.
	type: str"""
	def __init__(self, url:str, wordfile:str, threads:int=15, exts:list=[''],
				logfile:str=None, codes:list=utils.status_codes, user:str=None,
				password:str=None, force:bool=True,
				user_agent:str=requests.utils.default_user_agent(),
				filename:str='', text_to_search:str=''): ###
		file = Path(wordfile)
		if not file.exists():
			raise FileNotFoundError(f"{wordfile} doesn't exist")
		self.url = url if url.endswith('/') else url + '/'
		self.wordlist = ''
		self.wordfile = wordfile
		with open(wordfile) as f:
			self.wordlist = f.read().splitlines()
		self.threads = threads
		self.exts = self._lister(exts, 'ext')
		self.logfile = logfile
		self.codes = self._lister(codes, 'http')
		self.user = user
		self.password = password
		self.force = force
		self.user_agent = user_agent or utils.RandomAgent()
		self.results = defaultdict(list)
		
		self.filename = filename ###
		self.text_to_search = text_to_search ###
		self.found_flag = False ###
		self.flag2_dir = 'Not-found' ###

	def _lister(self, exts, ver:str):
		"""Properly converts status codes or extenstions options
		into lists for latter use. ver is an internal parameter
		to differentiate what kind of list is needed to output
		since they can functionaly be the same on input."""
		if isinstance(exts, str):
			exts = [i for i in exts.split(',')]
		elif isinstance(exts, list):
			pass
		else:
			if exts == None:
				return ['']
			else:
				raise ValueError(f"{exts} type {type(exts)} is not valid! Need string or list.")
		if ver == 'ext':
			if exts != ['']:
				exts = ['.'+i if not i.startswith('.') else i for i in exts]
				exts.insert(0,'')
				try:
					exts.remove('.')
				except ValueError:
					pass
		else:
			try:
				exts = [int(i) for i in exts]
			except ValueError:
				raise ValueError(f"Status code in {exts} is not a valid integer.")
		return exts

	def _brute(self, client:requests.Session, url:str, dirname:str, pbar):
		"""Function that sends the http requests and processes the response.
		param: client - The Session object to send requests.
		type: requests.Session
		param: url - Website base url.
		type: str
		param: filename - File on webserver to request.
		type: str"""

		if self.found_flag: ###
			pbar.update(1); ###
			return ###
		
		resp = client.get(url+dirname+'/'+self.filename) ###
		pbar.update(1)
		if resp.status_code in self.codes:
			result = f"/{dirname}/{self.filename} (Status : {resp.status_code})"
			self.results[resp.status_code].append(dirname+'/'+self.filename)
			# tqdm.write(result)
			if self.logfile:
				with open(self.logfile,'a') as f:
					f.write(result+'\n')

			if self.text_to_search in resp.text: ###
				self.found_flag = True ###
				self.flag2_dir = dirname ###
	
	def Run(self):
		"""The main function of the Pybuster class. This function kicks off and
		controls all of the scanning, the checks on whether the server is down
		or is wildcard matching, and returns a results dictionary that has keys
		that correspond to various http response codes and values that are lists
		of filenames that came back with the corresponding response code."""
		try:
			r = urllib.request.urlopen(self.url+''.join(choice(ascii_letters) for i in range(60)))
		except urllib.error.HTTPError:
			r = None
		except urllib.error.URLError:
			tqdm.write(f"Do you have the proper address? Because {self.url} seems to be down.")
			sys.exit(1)
		if r and not self.force:
			tqdm.write("Website is wildcard matching. Do you really want to bruteforce this website?")
			sys.exit(0)
		if bool(self.user) and bool(self.password):
			r = requests.post(self.url,auth=HttpNtlmAuth(self.user,self.password))
			if r.status_code != 200:
				tqdm.write("Don't have proper credentials. Please recheck.")
				sys.exit(0)
		if self.logfile:
			with open(self.logfile,'w'):
				pass
		client = requests.Session()
		client.headers['User-Agent'] = self.user_agent
		list_length = len(self.wordlist) * len(self.exts)
		wordlist =  (i+e for i in self.wordlist for e in self.exts)
		clientpool, urllist = (client for i in range(list_length)), (self.url for i in range(list_length))
		pbar = tqdm(total=list_length, leave=False)
		pbars = (pbar for i in range(list_length))
		self._header()
		with concurrent.futures.ThreadPoolExecutor(max_workers=self.threads) as executor:
			try:
				start = time.perf_counter()
				executor.map(self._brute, clientpool, urllist, wordlist, pbars)
			except:
				executor.shutdown()

		pbar.close() ###
		self._print_func(f"Time elapsed : {time.perf_counter() - start}\n{self.text_to_search} found in {self.url}{self.flag2_dir}/{self.filename}") ###
		return self.results

	def _header(self):
		"""Output Formatter"""
		self._print_func()
		header_text = "Url:".ljust(20) + self.url +'\n'
		header_text += "Threads:".ljust(20) + str(self.threads) + '\n'
		header_text += "Wordlist:".ljust(20) + self.wordfile + '\n'
		header_text += "Status Codes:".ljust(20) + ','.join(map(str,self.codes)) + '\n'
		header_text += "User Agent:".ljust(20) + self.user_agent + '\n'
		header_text += "File name:".ljust(20) + self.filename + '\n' ###
		self._print_func(header_text)
	
	@utils.pretty
	def _print_func(self, text:str=''):
		end = '\n'
		if text == '':
			end = ''
		tqdm.write(text,end=end)

	def get_url(self):
		return f'{self.url}{self.flag2_dir}/{self.filename}'
		
