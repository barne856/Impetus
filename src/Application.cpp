#include "PROF.hpp"
#include "PROF_Modules.hpp"
#include "PROF_Objects.hpp"

using namespace PROF;

// Pendulum phase space
float xFunc(float x, float y, float t)
{
    return 10.0f*y;
}

float yFunc(float x, float y, float t)
{
    return -sin(10.0f*x);
}

class Application : public Context
{
    Scene scene;
    Field* field = new Field();

    void init()
    {
        info.title = "Untitled";
        info.windowWidth = 1280;
        info.windowHeight = 720;
        info.aspect = (float)info.windowWidth / (float)info.windowHeight;
        info.majorVersion = 4;
        info.minorVersion = 5;
        info.samples = 32;
        info.fullscreen = false;
        info.cursor = true;
    }

    void startup()
    {
        scene.setView3D();
        vmath::vec3 eye = vmath::vec3(0.0f, 0.0f, 4.0f);
        vmath::vec3 center = vmath::vec3(0.0f, 0.0f, 0.0f);
        vmath::vec3 up = vmath::vec3(0.0f, 1.0f, 0.0f);
        scene.setLookat(eye, center, up);

        field->genFieldArrow(90.0f, 0.7f, 0.3f, 0.35f);
        field->setColor(Colors::orange);
        field->setSlope(xFunc, yFunc, 0.0f);

        scene.addObject(field);

    }
    void render(double currentTime)
    {
        float t = (float)currentTime;
        GLCall(glClear(GL_DEPTH_BUFFER_BIT));
        GLCall(glClearBufferfv(GL_COLOR, 0, Colors::spaceGray));

        field->setSlope(xFunc, yFunc, t);

        // render scene
        scene.render();
    }
    void shutdown() {
        delete field;
    }

    void onResize(int w, int h)
    {
        info.windowWidth = w;
        info.windowHeight = h;
        info.aspect = (float)info.windowWidth / (float)info.windowHeight;
        glViewport(0, 0, w, h);
        scene.setAspect(info.aspect);
    }
};
// Entry Point
int main()
{
    Application *app = new Application();
    app->run(app);
    delete app;
    return 0;
}