UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin))
	gflags = -D FAKE
endif

control: Makefile ./obj/control.o ./obj/motors.o ./obj/camera.o
	g++ -Wl,-R -Wl,./lib/  -pthread -L./lib/ -L/usr/lib/ -lupm-adafruitms1438  -lASICamera ./obj/camera.o ./obj/control.o ./obj/motors.o -o control
./obj/control.o:
	g++ -c control.cpp -o ./obj/control.o
./obj/motors.o:	
	g++ $(gflags) -c -I /usr/include/upm/ -L/usr/lib/  -lupm-adafruitms1438 motors.cpp -o ./obj/motors.o 
./obj/camera.o:	
	g++ -c camera.cpp -o ./obj/camera.o	
clean:
	rm control ./obj/*

