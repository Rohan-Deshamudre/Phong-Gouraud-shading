#ifndef __DEMO__
#define __DEMO__

#include "tucano/effect.hpp"
#include "tucano/camera.hpp"
#include "tucano/mesh.hpp"


class Widget;

namespace Tucano
{
namespace Effects
{

/**
 * @brief Renders a mesh using a custom shader.
 */
class Shading : public Tucano::Effect
{

    friend class ::Widget;

private:

    /// Shading Assignment shader
    Tucano::Shader phongshader;
    Tucano::Shader gouraudshader;

    /// Ambient coefficient
    Eigen::Vector3f ka = Eigen::Vector3f(0.0, 0.0, 0.0);

    /// Diffuse coefficient
    Eigen::Vector3f kd = Eigen::Vector3f(0.0, 1.0, 0.0);

    /// Specular coefficient
    Eigen::Vector3f ks = Eigen::Vector3f(1.0, 1.0, 1.0);

    Eigen::Vector3f light_intensity = Eigen::Vector3f(1.0, 1.0, 1.0);

    /// Shininess
    float shininess = 10.0;

    bool phong_selected = true;

public:

    /**
     * @brief Default constructor.
     * We do not call initialize here because we are not sure GLEW has been initialized yet
     * and the shaders can only be loaded after GLEW is ready
     */
    Shading (void) {}

    /**
     * @brief Load and initialize shaders
     */
    virtual void initialize (void)
    {
        // searches in default shader directory (/shaders) for shader files shading.(vert,frag,geom,comp)
        // it should find shading.vert and shading.frag
        loadShader(phongshader, "phongshader") ;
        loadShader(gouraudshader, "gouraudshader") ;
    }


    void renderWithShader (Tucano::Mesh& mesh, const Tucano::Camera& camera, const Tucano::Camera& light, Tucano::Shader & shader)
    {
        // bind the shader, any operation until the unbind operation will affect this shader
        shader.bind();

        // sets all uniform variables for the current shader (these are the variables that will be used in the vertex/fragment shaders)
        shader.setUniform("projectionMatrix", camera.getProjectionMatrix());
        shader.setUniform("modelMatrix", mesh.getShapeModelMatrix());                               
        shader.setUniform("default_color", mesh.getColor());

        // OBS: no need to pass inverse for the view matrices in this example, the Trackball class already uses the inverse paradigm
        shader.setUniform("viewMatrix", camera.getViewMatrix());
        shader.setUniform("lightViewMatrix", light.getViewMatrix());
        
        /***** write your code here **********/
        /******* pass your uniforms for the shading parameters **********/

		shader.setUniform("Ambient_Coefficient", ka);
		shader.setUniform("Diffuse_Coefficient", kd);
		shader.setUniform("Specular_Coefficient", ks);
		shader.setUniform("Light_Intensity", light_intensity);
		shader.setUniform("Shininess", shininess);

        /************************************************/

        // sets the mesh attributes automatically, such as vertex position and normals
        mesh.setAttributeLocation(shader);

        // render the mesh and call shaders
        mesh.render();

        // unbind the shader for a clean exit
        shader.unbind();
    }


    /** 
     * @brief Render the mesh given a camera and light, using a Phong shader 
     * @param mesh Given mesh
     * @param camera Given camera 
     * @param lightTrackball Given light camera 
     */
    void render (Tucano::Mesh& mesh, const Tucano::Camera& camera, const Tucano::Camera& light)
    {

        // set the current viewport to match the camera's viewport
        Eigen::Vector4f viewport = camera.getViewport();
        glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

        if (phong_selected)
            renderWithShader(mesh, camera, light, phongshader);
        else
            renderWithShader(mesh, camera, light, gouraudshader);

    }


    void setAmbientCoeff (float value, int channel) {ka[channel] = value;}
    void setDiffuseCoeff (float value, int channel) {kd[channel] = value;}
    void setSpecularCoeff (float value, int channel) {ks[channel] = value;}
    void setShininessCoeff (float value) {shininess = value;}
    void setLightIntensity (float value, int channel) {light_intensity[channel] = value;}

    float getDiffuseCoeff (int channel) {return kd[channel];}
    float getAmbientCoeff (int channel) {return ka[channel];}
    float getSpecularCoeff (int channel) {return ks[channel];}
    float getShininessCoeff (void ) {return shininess;}
    float getLightIntensity (int channel) {return light_intensity[channel];}

    void toggleShader (void) {phong_selected = !phong_selected;}
    bool phongSelected (void) {return phong_selected;}

};
}
}


#endif
