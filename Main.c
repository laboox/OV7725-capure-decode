/**
* File "camera.c"
* Created by Sina on Tue Jul 14 14:15:24 2015.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "wiringSerial.h"
#include "camera.h"

#define BUF_SIZE 1024

int main(){
    unsigned char buffer[BUF_SIZE] = {0};
    unsigned int picSize=0;
    unsigned int packNum=0;
    unsigned int packSize;
    unsigned short int checksum;
    unsigned int width, height;
    unsigned int i,j;
    unsigned char bytes[2];
    unsigned char image[160][120];

    int  fd = serialOpen("/dev/ttyUSB1", 115200);
    FILE* filefd = fopen("./image.ppm", "w");
    unsigned char* bufptr;

    sendShot(fd, RES_160X128);
    readImageDetails(fd, &picSize, &packNum);
    printf("size: %d\npackets count: %d\n", picSize, packNum);
    unsigned char* imgBuffer = (unsigned char*) malloc((picSize+1)*sizeof(unsigned char));
    readImage(fd, imgBuffer, picSize, packNum); 
    serialClose(fd);
    njInit();
    if (njDecode(imgBuffer, picSize)) {
        printf("Error decoding the input file.\n");
        return 1;
    }
    printf("size:\n%d %d\n", njGetWidth(), njGetHeight());
    fprintf(filefd, "P%d\n%d %d\n255\n", njIsColor() ? 6 : 5, njGetWidth(), njGetHeight());
    width = njGetWidth();
    height = njGetHeight();
    fwrite(njGetImage(), 1, njGetImageSize(), filefd);
    bufptr = njGetImage();
    for(i=0;i<width;i++){
        for(j=0;j<height;j++){
            image[i][j] = (char)((0.21 * (double)bufptr[(i+j*width)*3]) + 0.72 * (double)bufptr[(i+j*width)*3 + 1]  + 0.07 * (double)bufptr[(i+j*width)*3 + 2]);
        }
    }
    for(j=0;j<height;j++){
        for(i=0;i<width;i++){
            if(image[i][j]<63)
                printf("@");
            else if(image[i][j]<128)
                printf("*");
            else if(image[i][j]<191)
                printf("+");
            else
                printf("-");
        }
        printf("\n");
    }   
    fclose(filefd);
    njDone();
}
