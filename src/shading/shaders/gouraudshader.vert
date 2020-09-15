#version 150

/*********** in vertex attributes **********/
in vec4 in_Position;
in vec3 in_Normal;
in vec4 in_Color;
/*****************************************/

/********* going to fragment shader (will be interpolated) ********/
out vec4 color;
/*****************************************/

/************* uniform variables **********************/
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 lightViewMatrix;
uniform vec4 default_color;

/***************** write your code here ****************/
/******** uniform variables with material parameters ********/
uniform vec3 Ambient_Coefficient;
uniform vec3 Diffuse_Coefficient;
uniform vec3 Specular_Coefficient;
uniform vec3 Light_Intensity;
uniform float Shininess;
/*****************************************/

void main(void)
{
	color = default_color;

	/********* write your shader code here *****/	

	vec3 normal = mat3(transpose(inverse(modelMatrix)))*in_Normal;
	vec4 vert = modelMatrix * in_Position;

	vec3 normalized = normalize(normal);

	//Q1
	vec4 init = vec4(0,0,1,0);
	vec3 light_dir = vec3(normalize(inverse(lightViewMatrix) * init));

	//Q2
	vec3 reflected = reflect(-light_dir,normalized);

	//Q3
	vec4 eye_pos = vec4(0,0,0,1);
	vec4 eye_vect = inverse(viewMatrix) * eye_pos;	
	vec3 view = normalize(eye_vect.xyz - vert.xyz);

	//Q4
	vec3 ambient_lighting = Ambient_Coefficient * Light_Intensity;
	vec3 diffuse_lighting = Diffuse_Coefficient * max(dot(normalized,light_dir),0.0) * Light_Intensity;
	vec3 specular_lighting = Specular_Coefficient * pow(max(dot(view, reflected), 0.0), float(Shininess)) * Light_Intensity;

	//Q5
	vec3 final_color = (ambient_lighting +  diffuse_lighting + specular_lighting);
	color = vec4(final_color.xyz, 1.0);
	
    /*************************************/

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * in_Position;

}
