#ifndef __WIDGET__
#define __WIDGET__

#include <GL/glew.h>

#include "tucano/utils/trackball.hpp"
#include "tucano/utils/plyimporter.hpp"
#include "tucano/utils/imageIO.hpp"
#include "tucano/gui/base.hpp"
#include "shading.hpp"


class Widget 
{

private:

    /// Mesh to be rendered in this widget
    Tucano::Mesh bunnymesh;
    Tucano::Mesh planemesh;
    bool use_bunny = true;

    /// Trackball for manipulating the camera
    Tucano::Trackball camera;

    /// Trackball for manipulating light direction
    Tucano::DirectionalTrackball light;

    /// Phong effect to render mesh
    Tucano::Effects::Shading shading;

    /// a buffer for saving screenshots
    Tucano::Framebuffer screenshot_fbo;

    /// GUI holder
    Tucano::GUI::Base gui;

	/// Box to group all gui elements
	Tucano::GUI::GroupBox groupbox;

    /// Reload button
    Tucano::GUI::Button reload_button;

	/// Menu show/hide button
	Tucano::GUI::SelectButton menu_button;

    /// Sliders for coefficients
    Tucano::GUI::Slider kd_slider_red;
    Tucano::GUI::Slider kd_slider_green;
    Tucano::GUI::Slider kd_slider_blue;
    Tucano::GUI::Slider ks_slider_red;
    Tucano::GUI::Slider ks_slider_green;
    Tucano::GUI::Slider ks_slider_blue;
    Tucano::GUI::Slider ka_slider_red;
    Tucano::GUI::Slider ka_slider_green;
    Tucano::GUI::Slider ka_slider_blue;
    Tucano::GUI::Slider shininess_slider;

    /// Light intensity slider
    Tucano::GUI::Slider light_slider_red;
    Tucano::GUI::Slider light_slider_green;
    Tucano::GUI::Slider light_slider_blue;

    /// Label for coefficient text
    Tucano::GUI::Label diffuse_label;
    Tucano::GUI::Label specular_label;
    Tucano::GUI::Label ambient_label;
    Tucano::GUI::Label shininess_label;
    Tucano::GUI::Label light_label;

    Tucano::GUI::Label phong_label;
    Tucano::GUI::Label gouraud_label;

public:

    Widget(void) {}
    
    /**
     * @brief Initializes the widget and shaders
     * @param width Widget width in pixels
     * @param height Widget height in pixels 
     */
    void initialize(int width, int height);

    /**
     * Repaints screen buffer.
     **/
    virtual void render();

    /**
    * @brief Returns a pointer to the camera instance
    * @return pointer to trackball camera
    **/
    Tucano::Trackball* getCamera (void)
    {
        return &camera;
    }

    /**
     * @brief Returns pointer to GUI
     * @return pointer to GUI
     */
    Tucano::GUI::Base* getGUI (void)
    {
        return &gui;
    }

    /**
    * @brief Returns a pointer to the light instance
    * @return pointer to trackball light
    **/
    Tucano::DirectionalTrackball* getLight (void)
    {
        return &light;
    }

    /**
     * @brief setMeshFile
     * @param fn
     * New function to setup a meshFile var
     */
    void openMeshFile(string fn);

    /**
     * @brief Take a screenshot of the application and save it to a PPM file
     **/
    void screenshot (const Tucano::Camera& camera, const Tucano::Camera& light, string filename = "assignment5-screenshot", bool use_counter = true);
    void screenshot (void) {screenshot(camera, light);}

    /**
     * @brief Toggles between Phong and Gouraud shaders
     **/
    void toggleShader (void);

    /**
     * @brief Toggles between the Bunny and the Plane meshes
     **/
    void toggleMesh (void) {use_bunny = !use_bunny;}

    /**
     * @brief Creates the plane geometry with two triangles
     **/
    void createPlaneGeometry (void);

    /**
     * @brief Runs the test cases and writes the result to PPM images
     **/
    void runHandInCases (void);
    void writeSolutionImages (const Tucano::Camera& test_camera, const Tucano::Camera& test_light, int case_id);

};

#endif // MODELWIDGET
