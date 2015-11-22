all: camera
camera: Main.o nanojpeg.o
	gcc *.o -o camera
Main.o:	Main.c camera.o
	gcc -c Main.c
camera.o: camera.c camera.h wiringSerial.o
	gcc -c camera.c
wiringSerial.o: wiringSerial.c wiringSerial.h
	gcc -c wiringSerial.c
nanojpeg.o: nanojpeg.c nanojpeg.h
	gcc -c nanojpeg.c

.PHONEY: clean
clean:
	rm *.o camera
