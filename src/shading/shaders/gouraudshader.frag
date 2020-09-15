#version 330

/******** in variables from vertex shader (interpolated) ********/
in vec4 color;
/**********************************/

/******** output color of fragment ********/
out vec4 out_Color;
/**********************************/

void main(void)
{
    out_Color = color;
}
