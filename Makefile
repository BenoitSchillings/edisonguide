control: Makefile control.cpp motors.cpp 
	g++ -o control control.cpp -pthread 
	g++ -c -I /usr/include/upm/ -L/usr/lib/  -lupm-adafruitms1438 motors.cpp 
clean:
	rm control

