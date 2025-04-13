compile: pun.cpp
	 g++ pun.cpp course.cpp courseLL.cpp function.cpp login.cpp progress.cpp -o pun

run: pun
	 ./pun

clean: pun
	 rm pun