# Prerequisite  

*Instruction for Ubuntu*  
## 1. Install OpenCV (build from source)
- Install required dependencies:  
```
$ sudo apt install build-essential cmake git pkg-config libgtk-3-dev libavcodec-dev libavformat-dev libswscale-dev libv41-dev libxvidcore-dev libx264-dev libjpeg-dev libpng-dev libtiff-dev gfortran openexr libatlas-base-dev python3-dev python3-numpy libtbb2 libtbb-dev libdc1394-22-dev
```
- Clone the OpenCV's and OpenCV contrip repositories
```
$ mkdir ~/opencv_build && cd ~/opencv_build  
$ git clone https://github.com/opencv/opencv.git  
$ git clone https://github.com/opencv/opencv_contrib.git
```
- Once complete create build directory and cd into it
```
$ cd ~/opencv_build/opencv  
$ mkdir build && cd build
```
- Set up OpenCV build with CMake
```
$ cmake -D CMAKE_BUILD_TYPE=RELEASE \  
        -D CMAKE_INSTALL_PREFIX=/usr/local \  
        -D INSTALL_C_EXAMPLES=ON \  
        -D INSTALL_PYTHON_EXAMPLES=ON \  
        -D OPENCV_GENERATE_PKGCONFIG=ON \  
        -D OPENCV_EXTRA_MODULES_PATH=~/opencv_build/opencv_contrib/modules \  
        -D BUILD_EXAMPLES=ON ..
```
- Start the compilation process
```
$ make -j8
```
*note: modify -j according to your processor*
- Install OpenCV with:
```
$ sudo make install
```
- Verify if OpenCV installed successfully
```
$ pkg-config --modversion opencv4
```
```
output
4.5.5
```
## 2. Install C++20 support  
- Install tools
```
$ sudo apt install gcc-10 gcc-10-base gcc-10-doc g++-10 libstdc++-10-dev libstdc++-10-doc
``` 
- If you can't find the packages, run the following command:
```
$ sudo apt-apt-repository ppa:ubuntu-toolchain-r/test  
$ sudo apt-get update
```
- Then you need to tell the compiler to use C++20 by using `-std=c++20` flag

# Compiling the project
- Clone the project
```
$ cd ~  
$ git clone https://github.com/Khoadnd/NT219_Project_Rev2.git
$ cd NT219_Project_Rev2
```
- Compile the project
```
$ g++-10 -std=c++20 -o main main.cpp src/*.cpp $(pkg-config opencv4 --cflags --libs)
```
- Run
```
$ ./main
```
- The program read input image "image.jpg"