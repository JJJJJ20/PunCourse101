compile: pun.cpp
	 g++  class.cpp pun.cpp -o pun


run: pun
	 ./pun

clean: pun
	 rm pun