# OV7725-capure-decode
This code can capture image from *OV7725* Serial Camera and decode it using Nanojpeg library.
## Compile and Test
To compile the source code open the root folder of the project and type:
```
make
```
It is possible that this command shows you some warnings.

Now you can capture image and decode it by executing:
```
./camera
```
The image will be stored in *image.ppm*.
## Capture the image
You can capture jpeg images from *OV7725* by using functions in camera.h.if you want to capture an image using this library you havr to call following functions in order.
### Open port
For opening a serial port you can use ``serialOpen(address, baudrate)``. and store the file descriptor.
If you are using this code on other platforms like Arduino or Nios. *you have to use their own wiring library.* The wiring library which is uploaded in this repo is only working in Linux operating system.
### Send shot
You have to send a shot order to the camera using ``sendShot(fd, resolution)`` function. By this function the camera captures an image and stores it in its memory.
You can capture images in four different resolutions:

* 160\*128 *RES_160X128* 
* 320\*240 *RES_320X240* 
* 640\*480 *RES_640X480* 
* 1280\*1024 *RES_1280X1024* (only for 1.3MGP cameras) 

### Read details
After sending the ``sendShot`` command. You have to read the image details. ``readImageDetails(fd, picture size, frames count)`` will tell you the image size and the number of frames that the camera will send you.
### Read Image
To read an Image using this code you can call ``readImage(fd, image buffer, picture size, frames count)``.
This function will read a jpeg image and will store the image in the buffer.
## Decode the image
There are lots of libraries that can decode jpeg images. However, I used [Nanojpeg](http://keyj.emphy.de/nanojpeg/) becaue it's a light library and it's suitable to use on embedded designs.
you can find how to decode images using  *Nanojpeg* in its [website](http://keyj.emphy.de/nanojpeg/).
