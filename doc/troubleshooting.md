Troubleshooting       {#troubleshooting}
===========

## Wrong OpenGL or GLSL versions

Typically, if you do not have a dedicated graphics card, you will be running the **Mesa** Driver. Some implementations of the Mesa driver by default limit the OpenGL version to 3.0 and GLSL version to 1.3. If this is the case, you might get an error when running the application, for example:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Graphics Card Vendor: Intel Open Source Technology Center
Renderer (driver): Mesa DRI Intel(R) UHD Graphics 620 (Kabylake GT2) 
OpenGL Version: 3.0 Mesa 19.0.8
GLSL Version: 1.30

Error compiling vertex shader: /home/marroquim/devel/cse2215-glpractical/helloworld/src/shaders/helloworld.vert

0:2(10): error: GLSL 4.30 is not supported. Supported versions are: 1.10, 1.20, 1.30, 1.00 ES, 3.00 ES, 3.10 ES, and 3.20 ES
Error compiling fragment shader: /home/marroquim/devel/cse2215-glpractical/helloworld/src/shaders/helloworld.frag

0:2(10): error: GLSL 4.30 is not supported. Supported versions are: 1.10, 1.20, 1.30, 1.00 ES, 3.00 ES, 3.10 ES, and 3.20 ES
Error linking program : helloworld
error: linking with uncompiled/unspecialized shadererror: linking with uncompiled/unspecialized shader
GL error in /home/marroquim/devel/cse2215-glpractical/helloworld/../dependencies/tucano/tucano/mesh.hpp  line 1031 : invalid operation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Fortunately there is an easy solution to this problem. Even though Mesa defaults to OpenGL 3.0, you can force it to run with a higher version using the following command when calling your program:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MESA_GL_VERSION_OVERRIDE=4.3 ./helloworld
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

************
