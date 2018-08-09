#include "PROF.hpp"
#include "PROF_Modules.hpp"
#include "PROF_Objects.hpp"

using namespace PROF;

float rodLength = 1.0f;
float m = 1.0f;
float g = 10.0f;
float dt = 0.001f;

vmath::vec4 angleToVec(float theta1, float theta2)
{
    float x1 = rodLength * sin(theta1) / 2.0f;
    float y1 = -rodLength * cos(theta1) / 2.0f;
    float x2 = rodLength * (sin(theta1) + 0.5f * sin(theta2));
    float y2 = -rodLength * (cos(theta1) + 0.5f * cos(theta2));
    return vmath::vec4(x1, y1, x2, y2);
}

vmath::vec4 angleToPos(float theta1, float theta2)
{
    float x1 = rodLength * sin(theta1);
    float y1 = -rodLength * cos(theta1);
    float x2 = rodLength * (sin(theta1) + sin(theta2));
    float y2 = -rodLength * (cos(theta1) + cos(theta2));
    return vmath::vec4(x1, y1, x2, y2);
}

class Application : public Context
{
    Scene scene;
    // Create objects on the heap here
    Sphere *s1 = new Sphere();
    Sphere *s2 = new Sphere();
    Line *l1 = new Line();
    Line *l2 = new Line();
    float theta1 = (float)M_PI + 0.01f, theta2 = (float)M_PI -0.08f;
    float theta1Dot = 0.0f, theta2Dot = 0.0f;
    vmath::vec4 positions = angleToVec(theta1, theta2);

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

        l1->genLine();
        l1->setScale(rodLength);
        l1->setSlope(tan(theta1 - (float)M_PI / 2.0f));
        l1->setPosition(vmath::vec3(positions[0], positions[1], 0.0f));
        l1->setColor(Colors::cream);
        l2->genLine();
        l2->setScale(rodLength);
        l2->setSlope(tan(theta2 - (float)M_PI / 2.0f));
        l2->setPosition(vmath::vec3(positions[2], positions[3], 0.0f));
        l2->setColor(Colors::cream);

        vmath::vec4 ballPos = angleToPos(theta1, theta2);
        s1->genSphere(4);
        s1->setPosition(vmath::vec3(ballPos[0], ballPos[1], 0.0f));
        s1->setScale(0.03f);
        s1->setColor(Colors::orange);
        s2->genSphere(4);
        s2->setPosition(vmath::vec3(ballPos[2], ballPos[3], 0.0f));
        s2->setScale(0.03f);
        s2->setColor(Colors::orange);

        scene.addObject(l1);
        scene.addObject(l2);
        scene.addObject(s1);
        scene.addObject(s2);
    }
    void render(double currentTime)
    {
        float t = (float)currentTime;
        GLCall(glClear(GL_DEPTH_BUFFER_BIT));
        GLCall(glClearBufferfv(GL_COLOR, 0, Colors::spaceGray));

        // update objects here
        int iter = 10;
        for (int i = 0; i < iter; i++)
        {
            float F1 =
                (-3.0f * g * m * sin(theta1) - m * g * sin(theta1 - 2.0f * theta2) -
                 2.0f * sin(theta1 - theta2) * m *
                     (theta2Dot * theta2Dot * rodLength +
                      theta1Dot * theta1Dot * rodLength * cos(theta1 - theta2))) /
                (rodLength * (3.0f * m - m * cos(2.0f * theta1 - 2.0f * theta2)));

            float F2 =
                (2.0f * sin(theta1 - theta2) *
                 (theta1Dot * theta1Dot * rodLength * 2.0f * m +
                  g * 2.0f * m * cos(theta1) +
                  theta2Dot * theta2Dot * rodLength * m * cos(theta1 - theta2))) /
                (rodLength * (3.0f * m - m * cos(2.0f * theta1 - 2.0f * theta2)));

            theta1Dot += F1 * dt;
            theta2Dot += F2 * dt;
            theta1 += theta1Dot * dt;
            theta2 += theta2Dot * dt;
        }
        float F1 =
            (-3.0f * g * m * sin(theta1) - m * g * sin(theta1 - 2.0f * theta2) -
             2.0f * sin(theta1 - theta2) * m *
                 (theta2Dot * theta2Dot * rodLength +
                  theta1Dot * theta1Dot * rodLength * cos(theta1 - theta2))) /
            (rodLength * (3.0f * m - m * cos(2.0f * theta1 - 2.0f * theta2)));

        float F2 =
            (2.0f * sin(theta1 - theta2) *
             (theta1Dot * theta1Dot * rodLength * 2.0f * m +
              g * 2.0f * m * cos(theta1) +
              theta2Dot * theta2Dot * rodLength * m * cos(theta1 - theta2))) /
            (rodLength * (3.0f * m - m * cos(2.0f * theta1 - 2.0f * theta2)));

        theta1Dot += F1 * dt;
        theta2Dot += F2 * dt;
        theta1 += theta1Dot * dt;
        theta2 += theta2Dot * dt;
        positions = angleToVec(theta1, theta2);
        l1->setPosition(vmath::vec3(positions[0], positions[1], 0.0f));
        l1->setSlope(tan(theta1 - (float)M_PI / 2.0f));
        l2->setPosition(vmath::vec3(positions[2], positions[3], 0.0f));
        l2->setSlope(tan(theta2 - (float)M_PI / 2.0f));

        vmath::vec4 ballPos = angleToPos(theta1, theta2);
        s1->setPosition(vmath::vec3(ballPos[0], ballPos[1], 0.0f));
        s2->setPosition(vmath::vec3(ballPos[2], ballPos[3], 0.0f));

        float E = 0.5f*m*rodLength*rodLength*theta1Dot*theta1Dot +
        0.5f*m*(rodLength*rodLength*theta1Dot*theta1Dot +
        rodLength*rodLength*theta2Dot*theta2Dot +
        2.0f*rodLength*rodLength*theta1Dot*theta2Dot*cos(theta1 - theta2) ) -
        2.0f*m*g*rodLength*cos(theta1) - m*g*rodLength*cos(theta2);
        std::cout << E << "\n";
        
        // render scene
        scene.render();
    }
    void shutdown() {}

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