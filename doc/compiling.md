Compiling       {#compiling}
===========

Before starting with the OpenGL fun, we need to make sure everything compiles and runs properly.
Below are all the instruction for Windows and Linux (Ubuntu)

****************

<img src="windows-logo.jpg" width="300" alt="windows logo" />

# Dependencies

We have included the headers an binaries for GLWF, GLEW and Eigen in this distribution for convenience. We have only added the binaries for x64, compiled with Visual Studio 2019.

# Compiling

We have provided a solution (.sln) for you that already has the projects configured. Open it with Visual Studio 2019 and simply build the projects. You can switch the "active" project by right clicking one > Set as Startup Project. If it fails to build, contact the TA's David Alderliesten or Mick van Gelderen as soon as possible. 

# Running

Click on the appropriate button or press F5.

****************

<img src="ubuntu-logo.jpg" width="300" alt="ubuntu logo" />

# Dependencies

You need to have a few libraries installed to use Tucano and run the assignments:

### Eigen, GLEW and GLFW

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sudo apt install libeigen3-dev libglew-dev libglfw3-dev
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### CMake

If you haven't done so during the previous C++ assignment, make sure you have the following packages installed:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sudo apt-get install build-essential g++ cmake pkg-config
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# Compiling

Here are the instructions for compiling the HelloWorld project using CMake.
For the other projects (exercises and assignments) it is very similar, the only thing that changes is the last line when you execute the application.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
mkdir build           #creates a new directory build
cd build              #enters the build directory
cmake ..              #runs the CMakeLists.txt and generates a Makefile
cd ..                 #go back to the project directory
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Now you can invoke make to build the project. Pass the `-C` argument to specify
the directory for make to run in, which is `build` in our case. Additionally, to
speed up compilation, you can pass the `-jN` flagg where N is the number of
threads to use for compilation.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
make -C build -j8
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# Running

Make sure you run the program with the project directory as the Current Working
Directory (CWD) (also called Process Working Directory (PWD)). This makes it so
assets and shaders can be found, since the paths to them are specified as
relative paths from the CWD.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
build/APPLICATION_NAME
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

> If the application complains, check out the [troubleshooting section](@ref troubleshooting).

To recompile and run you can chain the commands like so:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
make -C build -j8 && build/APPLICATION_NAME
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

************

## Next step

Do [the assigment](@ref assignment-phong)
