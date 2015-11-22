/**
* File "camera.h"
* Created by Sina on Sun Aug  2 15:48:40 2015.
*/

#ifndef CAMERA_H_
#define CAMERA_H_

#include "wiringSerial.h"

#define RES_160X128     0x31
#define RES_320X240     0x32
#define RES_640X480     0x33
// Only for 1.3MGP cameras
#define RES_1280X1024   0x34

char sendShot(int fd, unsigned char resolution);
char readImageDetails(int fd, unsigned int* pickSize, unsigned int* packNum);
char readImage(int fd, unsigned char* img, unsigned int picSize, unsigned int packNum);

#endif
