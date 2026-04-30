import os
import subprocess
import json
import time
import sys
# create a clean build opion.

commands = sys.argv
CLEAN = False

eflags = ""
COMPILER_SETTINGS = "g++ -std=c++23 "
print(commands)
if 'clean' in commands:
		CLEAN = True
if 'release' in commands:
	release_config = "-O3 -DNDEBUG"
	COMPILER_SETTINGS+=release_config




def run_command(str_):
	subprocess.run(str_.split(),check=True)

if CLEAN:
	print('cleaning objs')
	if os.path.exists('objs'):
		subprocess.run("rm -R objs".split(),check=True)
	run_command("mkdir objs")

def build(clean=False):
	print("Starting.. ")
	_iflags = " -I./dependencies/include -I./src -I./dependencies/include/gp"
	_lflags = " -lcurl -lssl -lcrypto -lgq -lgumbo -lcpr "
	_Lflags = " -L./dependencies/lib "
	p  = subprocess.run((COMPILER_SETTINGS+" -c main.cpp -o objs/main.o"+_iflags+eflags).split(),check=True)
	mod_time_fp = "mod_time.json"

	time_dict = {}

	with open(mod_time_fp, 'r') as file:
		time_dict = json.loads(file.read())


	print(time_dict)
	__l_str = COMPILER_SETTINGS+ " objs/main.o "

	for file in os.listdir("src"):
		if file.endswith(".cpp"):

			file_name = file.split('.')[0]
			b_t = time_dict.get(file_name)
			m_t = os.path.getmtime("src/"+file)
			#print(b_t,m_t)
			if not b_t: b_t = 1
			if ((b_t < m_t) or clean):
					p = subprocess.run((f"{COMPILER_SETTINGS} -c src/{file_name}.cpp -o objs/{file_name}.o"+_iflags+eflags).split(),check=True)

					print(file_name)
					time_dict[file_name] = time.time()
			__l_str+="objs/"+file_name+".o "
	__l_str += "-o build/app"

	__l_str += _iflags + _Lflags + _lflags + eflags
	print(__l_str)
	print("Linking ..")
	p = subprocess.run((__l_str.split()),check=True)

	with open(mod_time_fp,'w') as file:
		json.dump(time_dict,file)


if __name__ == "__main__":
	build(CLEAN)

