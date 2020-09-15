#version 150

/*********** in vertex attributes **********/
in vec4 in_Position;
in vec3 in_Normal;
in vec4 in_Color;

/********* going to fragment shader (will be interpolated) ********/
out vec4 color;
out vec3 normal;
out vec4 vert;

/************* uniform variables **********************/
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec4 default_color;

void main(void)
{

	/********************************************************************/
	// if you need to pass to the fragment shader a transformed normal or
	// transformed vertex position, just overwrite or modify the variables below
	/********************************************************************/
	

	/********* write your shader code here *****/	

	normal = mat3(transpose(inverse(modelMatrix))) * in_Normal;
	vert = modelMatrix * in_Position;

	/*************************************/

    color = default_color;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * in_Position;

}
