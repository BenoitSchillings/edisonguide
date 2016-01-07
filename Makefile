UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	gflags = -D FAKE
endif

ifneq ($(UNAME_S), Darwin)
	lflags = -Wl,-R -Wl,./lib/ -pthread  -lupm-adafruitms1438
endif

control: Makefile ./obj/control.o ./obj/motors.o ./obj/camera.o
	g++ $(lflags) -L./lib/ -L/usr/lib/  -lASICamera ./obj/camera.o ./obj/control.o ./obj/motors.o -o control
./obj/control.o:
	g++ -c control.cpp -o ./obj/control.o
./obj/motors.o:	
	g++ $(gflags) -c -I /usr/include/upm/ -L/usr/lib/  -lupm-adafruitms1438 motors.cpp -o ./obj/motors.o 
./obj/camera.o:	
	g++ $(gflags) -c camera.cpp -o ./obj/camera.o	
clean:
	rm control ./obj/*

