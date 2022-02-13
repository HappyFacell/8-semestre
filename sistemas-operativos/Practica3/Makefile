#Este programa compila todos los programas que necesita la
#practica 3
start: PISerial.c PI_Posix.c PI_Fork.c PI_Clone.c
	gcc -o PISerial PISerial.c -lm
	gcc -o PI_Posix PI_Posix.c -lpthread -lm
	gcc -o PI_Fork PI_Fork.c -lm
	gcc -o PI_Clone PI_Clone.c -lm