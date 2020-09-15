#include "widget.hpp"


void Widget::render (void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    if (use_bunny)
        shading.render(bunnymesh, camera, light);
    else
        shading.render(planemesh, camera, light);

    camera.render();

    gui.render();
}


void Widget::openMeshFile(std::string fn)
{
    if (Tucano::MeshImporter::loadPlyFile(&bunnymesh, fn))
    {
        bunnymesh.normalizeModelMatrix();
    }
}

void Widget::screenshot (const Tucano::Camera& camera, const Tucano::Camera& light, string filename, bool use_counter)
{
    static int counter = 0;

    Eigen::Vector2i viewport = camera.getViewportSize();
    screenshot_fbo.create (viewport[0], viewport[1], 1, 1);
    screenshot_fbo.clearAttachments(Eigen::Vector4f(1.0, 1.0, 1.0, 0.0));
    screenshot_fbo.bindRenderBuffer(0);

    if (use_bunny)
        shading.render(bunnymesh, camera, light);
    else
        shading.render(planemesh, camera, light);        

    
    screenshot_fbo.unbind();
    std::ostringstream screenshot_name;
    if (use_counter)    
    {
        screenshot_name << filename << counter << ".ppm";
        counter ++;
    }
    else
    {
        screenshot_name << filename << ".ppm";
    }
    screenshot_fbo.saveAsPPM(screenshot_name.str(), 0);
    
}

void Widget::createPlaneGeometry (void)
{
    vector<Eigen::Vector4f> vertices;
    vector<Eigen::Vector3f> normals;
    vector<GLuint> indices;

    vertices.push_back ( Eigen::Vector4f( -1.0, -1.0, 0.0, 1.0) );
    vertices.push_back ( Eigen::Vector4f(  1.0, -1.0, 0.0, 1.0) );
    vertices.push_back ( Eigen::Vector4f(  1.0,  1.0, 0.0, 1.0) );
    vertices.push_back ( Eigen::Vector4f( -1.0,  1.0, 0.0, 1.0) );

    normals.push_back ( Eigen::Vector3f(  0.0,  0.0, 1.0) );
    normals.push_back ( Eigen::Vector3f(  0.0,  0.0, 1.0) );
    normals.push_back ( Eigen::Vector3f(  0.0,  0.0, 1.0) );
    normals.push_back ( Eigen::Vector3f(  0.0,  0.0, 1.0) );

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(0);

    planemesh.loadVertices(vertices);
    planemesh.loadIndices(indices);
    planemesh.loadNormals(normals);
    
    planemesh.setDefaultAttribLocations();
}



void Widget::runHandInCases (void)
{

    /****************** save rendering state ********************/
    bool cur_use_bunny = use_bunny;
    bool cur_use_phong = shading.phong_selected;
    Eigen::Vector3f cur_ka = shading.ka;
    Eigen::Vector3f cur_kd = shading.kd;
    Eigen::Vector3f cur_ks = shading.ks;
    float cur_shininess = shading.shininess;
    Eigen::Vector3f cur_light_intensity = shading.light_intensity;
    /***********************************************************/

    // test camera and light
    Tucano::Camera test_camera;
    Tucano::Camera test_light;

    test_camera.setProjectionMatrix (camera.getProjectionMatrix());
    test_camera.setViewport(camera.getViewport());
    
    /************************* test case 1 ***************************/
    
    test_camera.viewMatrix()->translate(Eigen::Vector3f(0.0, 0.0, 2.0));
    test_camera.setViewMatrix(test_camera.getViewMatrix().inverse());
    test_light.viewMatrix()->translate(Eigen::Vector3f(0.0, 0.0, 10.0));
    test_light.setViewMatrix(test_light.getViewMatrix().inverse());

    shading.ka = Eigen::Vector3f(0.3, 0.3, 0.3);
    shading.kd = Eigen::Vector3f(0.7, 0.2, 0.2);
    shading.ks = Eigen::Vector3f(1.0, 1.0, 1.0);
    shading.shininess = 5.0;
    shading.light_intensity = Eigen::Vector3f(1.0, 1.0, 1.0);

    writeSolutionImages(test_camera, test_light, 1);


    /************************* test case 2 ***************************/
    test_camera.resetViewMatrix();
    test_light.resetViewMatrix();
    
    test_camera.viewMatrix()->rotate(Eigen::AngleAxisf(-M_PI*0.125, Eigen::Vector3f::UnitX()));
    test_camera.viewMatrix()->rotate(Eigen::AngleAxisf(M_PI*0.125, Eigen::Vector3f::UnitY()));    
    test_camera.viewMatrix()->translate(Eigen::Vector3f(0.0, 0.0, 2.2));
    test_camera.setViewMatrix(test_camera.getViewMatrix().inverse());

    test_light.viewMatrix()->translate(Eigen::Vector3f(0.0, 0.0, 10.0));
    test_camera.viewMatrix()->rotate(Eigen::AngleAxisf(-M_PI*0.05, Eigen::Vector3f::UnitY()));
    test_light.setViewMatrix(test_light.getViewMatrix().inverse());

    shading.ka = Eigen::Vector3f(0.0, 0.0, 0.0);
    shading.kd = Eigen::Vector3f(1.0, 0.0, 0.0);
    shading.ks = Eigen::Vector3f(0.0, 0.0, 1.0);
    shading.shininess = 10.0;
    shading.light_intensity = Eigen::Vector3f(1.0, 1.0, 1.0);

    writeSolutionImages(test_camera, test_light, 2);


    /************************* test case 3 ***************************/
    test_camera.resetViewMatrix();
    test_light.resetViewMatrix();
    
    test_camera.viewMatrix()->rotate(Eigen::AngleAxisf(-M_PI*0.25, Eigen::Vector3f::UnitX()));
    test_camera.viewMatrix()->rotate(Eigen::AngleAxisf(-M_PI*0.05, Eigen::Vector3f::UnitY()));    
    test_camera.viewMatrix()->translate(Eigen::Vector3f(0.0, 0.0, 2.2));
    test_camera.setViewMatrix(test_camera.getViewMatrix().inverse());

    test_light.viewMatrix()->translate(Eigen::Vector3f(0.0, 0.0, 10.0));
    test_camera.viewMatrix()->rotate(Eigen::AngleAxisf(-M_PI*0.25, Eigen::Vector3f::UnitX()));
    test_light.setViewMatrix(test_light.getViewMatrix().inverse());

    shading.ka = Eigen::Vector3f(0.0, 0.0, 0.0);
    shading.kd = Eigen::Vector3f(0.0, 1.0, 1.0);
    shading.ks = Eigen::Vector3f(1.0, 1.0, 1.0);
    shading.shininess = 100.0;
    shading.light_intensity = Eigen::Vector3f(1.0, 1.0, 1.0);

    writeSolutionImages(test_camera, test_light, 3);

    /****************** restore rendering state ********************/
    use_bunny = cur_use_bunny;
    shading.phong_selected = cur_use_phong;
    shading.ka = cur_ka;
    shading.kd = cur_kd;
    shading.ks = cur_ks;
    shading.shininess = cur_shininess;
    shading.light_intensity = cur_light_intensity;
}


void Widget::writeSolutionImages (const Tucano::Camera& test_camera, const Tucano::Camera& test_light, int case_id)
{
    shading.phong_selected = true;
    use_bunny = true;

    screenshot (test_camera, light, string("solution-case") + std::to_string(case_id) +  string("-bunny-phong"), false);
    use_bunny = false;
    screenshot (test_camera, test_light, string("solution-case") + std::to_string(case_id) +  string("-plane-phong"), false);
    shading.phong_selected = false;
    use_bunny = true;
    screenshot (test_camera, test_light, string("solution-case") + std::to_string(case_id) +  string("-bunny-gouraud"), false);
    use_bunny = false;
    screenshot (test_camera, test_light, string("solution-case") + std::to_string(case_id) +  string("-plane-gouraud"), false);
}

void Widget::toggleShader (void)
{
    shading.toggleShader();
    phong_label.toggleDisplay();
    gouraud_label.toggleDisplay();
}

void Widget::initialize (int width, int height)
{
    glEnable(GL_DEPTH_TEST);

    createPlaneGeometry();

    // initialize the shader effect (if TUCANOSHADERDIR is set, no need to set dir before init)
    shading.initialize();

    /// no need to translate, the trackball already does that for you
    camera.setPerspectiveMatrix(60.0, (float)width/(float)height, 0.1f, 100.0f);
    camera.setRenderFlag(true);
    camera.setViewport(Eigen::Vector2f ((float)width, (float)height));

    light.setRenderFlag(false);
    light.setViewport(Eigen::Vector2f ((float)width, (float)height));


    /********** from now on initialize the GUI sliders, labels, and buttons ************/

    gui.setViewportSize (width, height);

    string assets_path = "../resources/assets/";

    menu_button.setPosition( 10, 10 );
    menu_button.onClick ( [&](){groupbox.toggleDisplay();} );
    menu_button.setTexture ( assets_path + "menu_button.pam" );    
    menu_button.setDimensionsFromHeight(30);
    gui.add(&menu_button);

    groupbox.setPosition (1, 50);
    groupbox.setDimensions (100, 480);
    groupbox.setTexture ( assets_path + "groupbox_long.pam");
    gui.add(&groupbox);

    reload_button.setPosition( 10, 60 );
    reload_button.onClick ( [&](){shading.reloadShaders();} );
    reload_button.setTexture (assets_path + "reload_button.pam" );
    reload_button.setDimensionsFromHeight(30);
    groupbox.add(&reload_button);

    ambient_label.setPosition(10, 90);
    ambient_label.setTexture(assets_path + "label_ambient.pam");
    ambient_label.setDimensionsFromHeight(12);
    groupbox.add(&ambient_label);

    ka_slider_red.setPosition(10, 120);
    ka_slider_red.setDimensions(80, 10);
    ka_slider_red.onValueChanged( [&](float v){shading.setAmbientCoeff(v, 0);} );
    ka_slider_red.setTexture(assets_path + "slider_bar.pam", assets_path + "slider.pam");
    ka_slider_red.moveSlider(shading.getAmbientCoeff(0));
    groupbox.add(&ka_slider_red);

    ka_slider_green.setPosition(10, 140);
    ka_slider_green.setDimensions(80, 10);
    ka_slider_green.onValueChanged( [&](float v){shading.setAmbientCoeff(v, 1);} );
    ka_slider_green.setTexture(assets_path + "slider_bar.pam", assets_path + "slider.pam");
    ka_slider_green.moveSlider(shading.getAmbientCoeff(1));
    groupbox.add(&ka_slider_green);

    ka_slider_blue.setPosition(10, 160);
    ka_slider_blue.setDimensions(80, 10);
    ka_slider_blue.onValueChanged( [&](float v){shading.setAmbientCoeff(v, 2);} );
    ka_slider_blue.setTexture(assets_path + "slider_bar.pam", assets_path + "slider.pam");
    ka_slider_blue.moveSlider(shading.getAmbientCoeff(2));
    groupbox.add(&ka_slider_blue);

    diffuse_label.setPosition(10, 190);
    diffuse_label.setTexture( assets_path + "label_diffuse.pam" );
    diffuse_label.setDimensionsFromHeight(12);
    groupbox.add(&diffuse_label);

    kd_slider_red.setPosition(10, 210);
    kd_slider_red.setDimensions(80, 10);
    kd_slider_red.onValueChanged( [&](float v){shading.setDiffuseCoeff(v, 0);} );
    kd_slider_red.setTexture(assets_path + "slider_bar.pam", assets_path +"slider.pam");
    kd_slider_red.moveSlider(shading.getDiffuseCoeff(0));
    groupbox.add(&kd_slider_red);

    kd_slider_green.setPosition(10, 230);
    kd_slider_green.setDimensions(80, 10);
    kd_slider_green.onValueChanged( [&](float v){shading.setDiffuseCoeff(v, 1);} );
    kd_slider_green.setTexture(assets_path + "slider_bar.pam", assets_path +"slider.pam");
    kd_slider_green.moveSlider(shading.getDiffuseCoeff(1));
    groupbox.add(&kd_slider_green);

    kd_slider_blue.setPosition(10, 250);
    kd_slider_blue.setDimensions(80, 10);
    kd_slider_blue.onValueChanged( [&](float v){shading.setDiffuseCoeff(v, 2);} );
    kd_slider_blue.setTexture(assets_path + "slider_bar.pam", assets_path +"slider.pam");
    kd_slider_blue.moveSlider(shading.getDiffuseCoeff(2));
    groupbox.add(&kd_slider_blue);

    specular_label.setPosition(10, 280);
    specular_label.setTexture(assets_path + "label_specular.pam");
    specular_label.setDimensionsFromHeight(12);
    groupbox.add(&specular_label);

    ks_slider_red.setPosition(10, 300);
    ks_slider_red.setDimensions(80, 10);
    ks_slider_red.onValueChanged( [&](float v){shading.setSpecularCoeff(v, 0);} );
    ks_slider_red.setTexture(assets_path + "slider_bar.pam", assets_path + "slider.pam");
    ks_slider_red.moveSlider(shading.getSpecularCoeff(0));
    groupbox.add(&ks_slider_red);

    ks_slider_green.setPosition(10, 320);
    ks_slider_green.setDimensions(80, 10);
    ks_slider_green.onValueChanged( [&](float v){shading.setSpecularCoeff(v, 1);} );
    ks_slider_green.setTexture(assets_path + "slider_bar.pam", assets_path + "slider.pam");
    ks_slider_green.moveSlider(shading.getSpecularCoeff(1));
    groupbox.add(&ks_slider_green);

    ks_slider_blue.setPosition(10, 340);
    ks_slider_blue.setDimensions(80, 10);
    ks_slider_blue.onValueChanged( [&](float v){shading.setSpecularCoeff(v, 2);} );
    ks_slider_blue.setTexture(assets_path + "slider_bar.pam", assets_path + "slider.pam");
    ks_slider_blue.moveSlider(shading.getSpecularCoeff(2));
    groupbox.add(&ks_slider_blue);

    shininess_label.setPosition(10, 370);
    shininess_label.setTexture(assets_path + "label_shininess.pam");
    shininess_label.setDimensionsFromHeight(12);
    groupbox.add(&shininess_label);

    shininess_slider.setPosition(10, 390);
    shininess_slider.setDimensions(80, 10);
    shininess_slider.onValueChanged( [&](float v){shading.setShininessCoeff(v);} );
    shininess_slider.setTexture(assets_path + "slider_bar.pam", assets_path + "slider.pam");
    shininess_slider.setMinMaxValues(1.0, 100.0);
    shininess_slider.moveSlider(shading.getShininessCoeff());
    groupbox.add(&shininess_slider);

    light_label.setPosition(10, 420);
    light_label.setTexture(assets_path + "label_light_intensity.pam");
    light_label.setDimensionsFromHeight(12);
    groupbox.add(&light_label);

    light_slider_red.setPosition(10, 440);
    light_slider_red.setDimensions(80, 10);
    light_slider_red.onValueChanged( [&](float v){shading.setLightIntensity(v, 0);} );
    light_slider_red.setTexture(assets_path + "slider_bar.pam", assets_path + "slider.pam");
    light_slider_red.moveSlider(shading.getLightIntensity(0));
    groupbox.add(&light_slider_red);

    light_slider_green.setPosition(10, 460);
    light_slider_green.setDimensions(80, 10);
    light_slider_green.onValueChanged( [&](float v){shading.setLightIntensity(v, 1);} );
    light_slider_green.setTexture(assets_path + "slider_bar.pam", assets_path + "slider.pam");
    light_slider_green.moveSlider(shading.getLightIntensity(1));
    groupbox.add(&light_slider_green);

    light_slider_blue.setPosition(10, 480);
    light_slider_blue.setDimensions(80, 10);
    light_slider_blue.onValueChanged( [&](float v){shading.setLightIntensity(v, 2);} );
    light_slider_blue.setTexture(assets_path + "slider_bar.pam", assets_path + "slider.pam");
    light_slider_blue.moveSlider(shading.getLightIntensity(2));
    groupbox.add(&light_slider_blue);

    phong_label.setPosition(200, 20);
    phong_label.setTexture(assets_path + "label_phong.pam");
    phong_label.setDimensionsFromHeight(30);
    gui.add(&phong_label);

    gouraud_label.setPosition(200, 20);
    gouraud_label.setTexture(assets_path + "label_gouraud.pam");
    gouraud_label.setDimensionsFromHeight(22);
    gui.add(&gouraud_label);
    gouraud_label.hide();
}