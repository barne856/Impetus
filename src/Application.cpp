#include "PROF.hpp"
#include "PROF_Modules.hpp"
#include "PROF_Objects.hpp"

using namespace PROF;

// Pendulum phase space
float xFunc(float x, float y, float t)
{
    return 4.0f*y - y*y*sin(t);
}

float yFunc(float x, float y, float t)
{
    return 4.0f*x*sin(t) - x*x*x*cos(t);
}

class Application : public Context
{
    Scene scene;
    Field* field = new Field();
    SolutionCurve* curve = new SolutionCurve();

    vmath::vec2 initPos = vmath::vec2(0.0f);

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

        field->genFieldArrow(60.0f, 0.7f, 0.3f, 0.15f);
        //field->genField();
        field->setColor(Colors::white);
        field->setSlope(xFunc, yFunc, 0.0f);

        curve->genSolutionCurve(xFunc, yFunc, 0.0f, 0.0f, 0.0f, 5000);
        curve->setColor(Colors::orange);

        scene.addObject(field);
        scene.addObject(curve);

    }
    void render(double currentTime)
    {
        float t = (float)currentTime;
        GLCall(glClear(GL_DEPTH_BUFFER_BIT));
        GLCall(glClearBufferfv(GL_COLOR, 0, Colors::silver));

        field->setSlope(xFunc, yFunc, t);
        
        curve->update(initPos, t);

        // render scene
        scene.render();
    }
    void shutdown() {
        delete field;
        delete curve;
    }

    void onResize(int w, int h)
    {
        info.windowWidth = w;
        info.windowHeight = h;
        info.aspect = (float)info.windowWidth / (float)info.windowHeight;
        glViewport(0, 0, w, h);
        scene.setAspect(info.aspect);
    }

    vmath::vec2 screenToWorld(vmath::vec2 vec)
    {
        vec[1] *= -1.0f;
        vec[0] -= 0.5f*(float)info.windowWidth;
        vec[1] += 0.5f*(float)info.windowHeight;
        vec[0] /= 0.5f*(float)info.windowHeight;
        vec[1] /= 0.5f*(float)info.windowHeight;
        return vec/2.0f;
    }

    void onMouseMove(double x, double y)
    {
        vmath::vec2 vec = vmath::vec2((float)x, (float)y);
        initPos = screenToWorld(vec);
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