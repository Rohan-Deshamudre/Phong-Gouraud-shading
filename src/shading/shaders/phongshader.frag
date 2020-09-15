#version 330

/******** in variables from vertex shader (interpolated) ********/
in vec4 color;
in vec3 normal;
in vec4 vert;
/**********************************/

/******** output color of fragment ********/
out vec4 out_Color;
/**********************************/

/******** uniform variables ********/
uniform mat4 viewMatrix;
uniform mat4 lightViewMatrix;
/**********************************

/***************** write your uniform variable code here ****************/
/******** uniform variables with material parameters ********/
uniform vec3 Ambient_Coefficient;
uniform vec3 Diffuse_Coefficient;
uniform vec3 Specular_Coefficient;
uniform vec3 Light_Intensity;
uniform float Shininess;
/**********************************/

void main(void)
{
    out_Color = color;

    /***************** write your shading code here ****************/
    
    /// 1) compute the light direction
    /// 1) reflect light direction according to normal vector
    /// 2) compute eye direction
    /// 3) compute ambient, diffuse and specular components
    /// 4) compute final color using the Phong Model

    /**************************************************************/    

	vec3 normalized = normalize(normal);
	
	//Question 1
	vec4 init = vec4(0,0,1,0);
	vec3 light_dir = vec3(normalize(inverse(lightViewMatrix) * init));
	

	//Question 2
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
	out_Color = vec4(final_color.xyz, 1.0);


}
