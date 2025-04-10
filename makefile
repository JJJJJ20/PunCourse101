compile: pun.cpp
	 g++  pun.cpp course.cpp courseLL.cpp function.cpp -o pun


run: pun
	 ./pun

clean: pun
	 rm pun