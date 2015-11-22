/**
* File "camera.c"
* Created by Sina on Sun Aug  2 15:48:35 2015.
*/

#include "camera.h"


#define BUF_SIZE 1024

const unsigned char ACK[] = {0x55, 0x48, 0x00, 0x23};
const unsigned char ACKE[] = {0x55, 0x45, 0x00, 0x23};
unsigned char buffer[BUF_SIZE] = {0};

char sendShot(int fd, unsigned char resolution){
    unsigned char shot[] = {0x55, 0x48, 0x00, 0x33, 0x00, 0x02, 0x23};
    shot[3]=resolution;
    serialWrite(fd, shot, 7);
    if(serialDataRead(fd, buffer, 4)<0){
        return -1;
    }
    if(memcmp(buffer, ACK, 4) == 0)
        return 0;
    else{
        return -1;
    }
}


char readImageDetails(int fd, unsigned int* picSize, unsigned int* packNum){
    if(serialDataRead(fd, buffer, 10)<0)
        return -1;
    *picSize = buffer[6] << 24 | buffer[5] << 16 | buffer[4] << 8 | buffer [3];
    *packNum = buffer[8] << 8 | buffer [7];
    return 0;
}

char readImage(int fd, unsigned char* img, unsigned int picSize, unsigned int packNum){
    int i;
    int j;
    unsigned int packSize;
    unsigned int imgIndex;
    unsigned char PACKREQ[] = {0x55, 0x45, 0x00, 0x01, 0x00, 0x23};
    unsigned char bytes;
    for(i=1;i<=packNum;i++){
        PACKREQ[3] = i & 0xFF;
        PACKREQ[4] = (i&0xFF00)>>256;
        serialWrite(fd, PACKREQ, 6);
        serialDataRead(fd, buffer, 4);
        if(memcmp(buffer, ACKE, 4)!=0){
            return -1;
        }
        serialDataRead(fd, buffer, 7);
        packSize = buffer[6] << 8 | buffer [5];
        for(j=0;j<packSize;j++){
            serialDataRead(fd, &bytes, 1);
            img[imgIndex++] = bytes;
        }
        //reading cheack sum
        serialDataRead(fd, &bytes, 1);
        serialDataRead(fd, &bytes, 1);
    }
    return 0;
}
