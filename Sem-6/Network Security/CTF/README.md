* Before running the attack.py script, you need to install the following dependencies:\
	`pip3 install python-nmap`\
	`pip3 install pydirbuster`

* The attack.py script is the main script that runs the attack and retrieves the flags. dirbuster_ctf.py(modified main.py of the pydirbuster module) and heartbleed.py(Note that its a python2 file) are opensource codes the attack.py script uses. The wordlist used for flag2 bruteforce is in directory-list-lowercase-2.3-small.txt (copied from the dirbuster tool).

* To start the script, simply run `python3 attack.py` and enter the IP address of the vulnerable machine.