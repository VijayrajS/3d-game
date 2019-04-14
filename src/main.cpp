#include "main.h"
#include "time.h"
#include "ball.h"
#include "bomb.h"
#include "cube.h"
#include "ring.h"
#include "arrow.h"
#include "timer.h"
#include "needle.h"
#include "enemies.h"
#include "volcano.h"
#include "sevenseg.h"
#include "rectangle.h"

using namespace std;

float alph = M_PI / 180.0f;
int sign = 1; // For missile (sign 1: missle releases from right wing, sign -1, left wing)
int score_c = 0;
float clock_bomb = -1.0f;
float clock_missile = -1.0f;
int critical_altitude = 0;
int health = 100;
int timer = 0;

int camera = 1;

/*
1 for followcam
2 for topcam
3 for towercam
4 for first person
5 for helicopter cam
*/

GLMatrices Matrices;    // For game
GLMatrices Matrix_Dash; // For dashboard

GLuint     programID;
GLFWwindow *window;

Ball ball1;

Rectangle sea;
Rectangle base, line1, line2;
Arrow arrow;
Volcano volc;

vector<Bomb> missile_set;
vector<Bomb> bomb_set;
vector<Cube> fuelup;
vector<Ring> smoke_rings;

vector<glm::vec2> checkpoints;

vector<Volcano> volc_set;
vector<Cannon> e1_set;
vector<Para> e2_set;
vector<Bomb> e1_bset;

// Dashboard related

Ring fuel_meter;
Needle fuel_needle;
Ring health_meter;
Needle health_needle;

Ring pointer_d;
Needle compass;
Needle compass2;

Rectangle h;
Sevenseg score[6];
Sevenseg speed[6];
Sevenseg altitude[6];
Sevenseg c_altitude[6];

// ---------------------

float theta = -45, phi = -90;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;


Timer t60(1.0 / 60);

void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    glm::vec3 eye(ball1.position.x - 10*sin(ball1.rotationy * M_PI / 180.0f), ball1.position.y + 8, ball1.position.z - 10*cos(ball1.rotationy * M_PI / 180.0f));
    glm::vec3 target(ball1.position.x + 3*sin(ball1.rotationy * M_PI / 180.0f), ball1.position.y, ball1.position.z + 3 * cos(ball1.rotationy * M_PI / 180.0f));
    glm::vec3 up(0, -1, 0);

    switch (camera)
    {
        case 1:
            eye = glm::vec3(ball1.position.x - 10 * sin(ball1.rotationy * M_PI / 180.0f), ball1.position.y + 8, ball1.position.z - 10 * cos(ball1.rotationy * M_PI / 180.0f));
            target = glm::vec3(ball1.position.x + 3 * sin(ball1.rotationy * M_PI / 180.0f), ball1.position.y, ball1.position.z + 3 * cos(ball1.rotationy * M_PI / 180.0f));
            up = glm::vec3(0, -1, 0);
            break;

        case 2:
            eye = glm::vec3(ball1.position.x, ball1.position.y + 40, ball1.position.z);
            target = glm::vec3(ball1.position.x, ball1.position.y, ball1.position.z);
            up = glm::vec3(0, 0, -1);
            break;

        case 3:
            eye = glm::vec3(-7.5, 25, 2.5);
            target = glm::vec3(ball1.position.x, ball1.position.y, ball1.position.z);
            up = glm::vec3(0, -1, 0);
            break;

        case 4:
            eye = glm::vec3(ball1.position.x, ball1.position.y + 1, ball1.position.z + 5);
            target = glm::vec3(ball1.position.x, ball1.position.y, ball1.position.z + 10);
            up = glm::vec3(0, -1, 0);
            break;

        case 5:
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);

            if(xpos > 768)
                theta -= 0.5;

            if(ypos > 768)
                phi -= 0.5;

            if(xpos < 256)
                theta += 0.5;

            if(ypos < 256)
                phi += 0.5;

            eye = glm::vec3(ball1.position.x + 10 * sin(alph * phi) * cos(alph * theta), ball1.position.y + 10 * cos(alph * phi), ball1.position.z + +10 * sin(alph * theta) * sin(alph * phi));
            target = glm::vec3(ball1.position.x, ball1.position.y, ball1.position.z);
            up = glm::vec3(0, -1, 0);
            break;

        default:
            eye = glm::vec3(ball1.position.x - 10 * sin(ball1.rotationy * M_PI / 180.0f), ball1.position.y + 8 + 0 * sin(ball1.rotationx), ball1.position.z - 10 * cos(ball1.rotationy * M_PI / 180.0f));
            target = glm::vec3(ball1.position.x + 3 * sin(ball1.rotationy * M_PI / 180.0f), ball1.position.y, ball1.position.z + 3 * cos(ball1.rotationy * M_PI / 180.0f));
            up = glm::vec3(0, -1, 0);
            break;
    }

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt(eye, target, up); // Rotating Camera for 3D
    Matrix_Dash.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 VP2 = Matrix_Dash.projection * Matrix_Dash.view;
    
    // For checkpoints to be visible, infinite perspective for checkpoint arrow
    glm::mat4 VP3 = glm::infinitePerspective(glm::radians(270.0f/screen_zoom), 1.0f, 0.1f) * Matrices.view; 
    // glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ball1.draw(VP);

    sea.draw(VP);
    base.draw(VP);
    line1.draw(VP);
    line2.draw(VP);

    volc.draw(VP);
    arrow.draw(VP3);

    for(int i = 0; i < missile_set.size(); i++)
        missile_set[i].draw(VP);

    for (int i = 0; i < bomb_set.size(); i++)
        bomb_set[i].draw(VP);

    for (int i = 0; i < fuelup.size(); i++)
        fuelup[i].draw(VP);

    for (int i = 0; i < volc_set.size(); i++)
        volc_set[i].draw(VP);

    for (int i = 0; i < e1_set.size(); i++)
        e1_set[i].draw(VP);

    for (int i = 0; i < e2_set.size(); i++)
        e2_set[i].draw(VP);

    for (int i = 0; i < e1_bset.size(); i++)
        e1_bset[i].draw(VP);

    for (int i = 0; i < smoke_rings.size(); i++)
            smoke_rings[i].draw(VP);

    fuel_meter.draw(VP2);
    fuel_needle.draw(VP2);

    health_meter.draw(VP2);
    health_needle.draw(VP2);

    pointer_d.draw(VP2);
    compass.draw(VP2);
    compass2.draw(VP2);

    int temp = score_c;
    for (int i = 5; i >= 0; i--)
    {
        score[i].draw(VP2, temp % 10);
        temp /= 10;
    }

    temp = ball1.position.y*10;

    if(critical_altitude == 0)
    {
        for (int i = 5; i >= 0; i--)
        {
            altitude[i].draw(VP2, temp % 10);
            temp /= 10;
        }
    }

    else
    {
        for (int i = 5; i >= 0; i--)
        {
            c_altitude[i].draw(VP2, temp % 10);
            temp /= 10;
        }
    }

    temp = ball1.speed*1000;
    for (int i = 5; i >= 0; i--)
    {
        speed[i].draw(VP2, temp % 10);
        temp /= 10;
    }
}

void tick_input(GLFWwindow *window) {
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);

    int w = glfwGetKey(window, GLFW_KEY_W);
    int a = glfwGetKey(window, GLFW_KEY_A);
    int s = glfwGetKey(window, GLFW_KEY_S);
    int d = glfwGetKey(window, GLFW_KEY_D);
    int q = glfwGetKey(window, GLFW_KEY_Q);
    int e = glfwGetKey(window, GLFW_KEY_E);

    int c1 = glfwGetKey(window, GLFW_KEY_1);
    int c2 = glfwGetKey(window, GLFW_KEY_2);
    int c3 = glfwGetKey(window, GLFW_KEY_3);
    int c4 = glfwGetKey(window, GLFW_KEY_4);
    int c5 = glfwGetKey(window, GLFW_KEY_5);

    // test keys j, k, l
    int j = glfwGetKey(window, GLFW_KEY_J);
    int k = glfwGetKey(window, GLFW_KEY_K);
    int l = glfwGetKey(window, GLFW_KEY_L);
    if (up)
        ball1.set_position(0, 0, 0);
    if (j)
        ball1.set_position(1, 0, 0);
    if (k)
        ball1.set_position(0, 1, 0);
    if (l)
        ball1.set_position(0, 0, 1);
    //---------------------------------

    if(w && ball1.fuel > 0 && ball1.speed < 2)
        ball1.speed += 0.001;

    if (s && ball1.fuel > 0 && ball1.speed > 0.2)
        ball1.speed -= 0.001;

    if(ball1.speed > 0)
    {if(e) 
        ball1.rotationy -= 0.5;

    if(q)
        ball1.rotationy += 0.5;

    if(a)
        ball1.rotationz -= 0.5;

    if(d)
        ball1.rotationz += 0.5;

    if(space && ball1.rotationx > -90 && ball1.fuel > 0)
        ball1.rotationx -= 0.15;

    if(down && ball1.rotationx < 90)
        ball1.rotationx += 0.15;

    if(ball1.rotationx < -90)
        ball1.rotationx = -90;

    if(ball1.rotationx < 90 && ball1.speed > 0.1)
    {
        ball1.rotationx += 0.05;
        ball1.position.y -= 0.01;
    }}

    if(c1) camera = 1;
    if(c2) camera = 2;
    if(c3) camera = 3;
    if(c4) camera = 4;
    if(c5) camera = 5;

    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (state == GLFW_PRESS)
    {
        if(clock_missile < 0 || clock() - clock_missile > CLOCKS_PER_SEC/2)
        {
            clock_missile = clock();
            missile_set.push_back(Bomb(ball1.position.x + sign,
                                    ball1.position.y - 0.5, ball1.position.z,
                                    ball1.rotationx, ball1.rotationy, ball1.rotationz, 1, ball1.speed));
            sign *= -1;
        }
    }

    int state_b = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
    if (state_b == GLFW_PRESS)
    {
        if (clock_bomb < 0 || clock() - clock_bomb > CLOCKS_PER_SEC / 2)
        {
            clock_bomb = clock();
            bomb_set.push_back(Bomb(ball1.position.x, ball1.position.y - 1, ball1.position.z,
                                       0, ball1.rotationy, 0, 0, ball1.speed));
        }
    }
}

void tick_elements() {
    ball1.tick();

    sea.tick();

    arrow.tick();
    volc.tick();

    fuel_needle.tick(ball1.fuel);
    health_needle.tick(health);
    compass.tick((ball1.rotationy+90)*5/9);
    compass2.tick((ball1.rotationy+270)*5/9);

    for (int i = 0; i < missile_set.size(); i++)
        missile_set[i].tick();

    for (int i = 0; i < bomb_set.size(); i++)
        bomb_set[i].tick();

    for (int i = 0; i < e1_bset.size(); i++)
        e1_bset[i].tick();

    for (int i = 0; i < e2_set.size(); i++)
        e2_set[i].tick();
}

void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */

    ball1 = Ball(0, sin(M_PI/3));

    sea = Rectangle(0, 0, 0, 5000, 5000, 0, {12, 52, 47});
    base = Rectangle(0, 0.1, 0, 10, 21, 0, {111, 111, 111});
    line1 = Rectangle(3, 0.11, 0, 1, 21, 0, {255, 255, 111});
    line2 = Rectangle(-3, 0.11, 0, 1, 21, 0, {255, 255, 0});

    arrow = Arrow(0, 7, 100, {255, 0, 0});
    volc = Volcano(0, 0, 300, COLOR_RED);

    for(int i = 0; i < checkpoints.size(); i++)
        e1_set.push_back(Cannon(checkpoints[i][0], 0, checkpoints[i][1]));
    
    for(int i = 2; i < 40; i+=2)
    {
        int i1 = 50*i;
        fuelup.push_back(Cube(i1, 15, i1, 1, 1, 1, COLOR_RED));
        fuelup.push_back(Cube(i1, 15, -i1, 1, 1, 1, COLOR_RED));
        fuelup.push_back(Cube(-i1, 15, i1, 1, 1, 1, COLOR_RED));
        fuelup.push_back(Cube(-i1, 15, -i1, 1, 1, 1, COLOR_RED));

        if(i%4 == 0)
        {
            smoke_rings.push_back(Ring(0, 30, i1, 6, 90, {150, 150, 150}));
            smoke_rings.push_back(Ring(i1, 30, 0, 6, 0, {150, 150, 150}));
            smoke_rings.push_back(Ring(0, 30, -i1, 6, 90, {150, 150, 150}));
            smoke_rings.push_back(Ring(-i1, 30, 0, 6, 0, {150, 150, 150}));
        }
    }

    int i1;
    for (int i = 1; i < 40; i+= 7)
    {
        if(i1 > 0)
            i1 = 100*i;
        
        else
            i1 = 80;

        float M_PI_8 = M_PI_4/2;
        float rad = rand_FloatRange(i1,  i1 + 10);
        float th[4] = { rand_FloatRange(-M_PI_8, M_PI_8), 
                        rand_FloatRange(M_PI_2 - M_PI_8, M_PI_2 + M_PI_8),
                        rand_FloatRange(M_PI - M_PI_8, M_PI + M_PI_8),
                        rand_FloatRange(3*M_PI_2 - M_PI_8, 3*M_PI_2 + M_PI_8),};

        int index = rand()%4;
        volc_set.push_back(Volcano(rad*cos(th[index]), 0, rad*sin(th[index]), {0, 0, 0}));
    }

    for (int i = 1; i < 40; i += 7)
    {
        if (i1 > 0)
            i1 = 100 * i;

        else
            i1 = 80;

        float M_PI_8 = M_PI_4 / 2;
        float rad = rand_FloatRange(i1, i1 + 10);
        float th[4] = {
            rand_FloatRange(M_PI_4 - M_PI_8, M_PI_4 + M_PI_8),
            rand_FloatRange(3 * M_PI_4 - M_PI_8, 3 * M_PI_4 + M_PI_8),
            rand_FloatRange(5 * M_PI_4 - M_PI_8, 5 * M_PI_4 + M_PI_8),
            rand_FloatRange(7 * M_PI_4 - M_PI_8, 7 * M_PI_4 + M_PI_8),
        };

        int index = rand() % 4;
        e1_set.push_back(Cannon(rad * cos(th[index]), 1.4, rad * sin(th[index])));
    }

    fuel_meter = Ring(-2, -2, 0, 0.5, 0, {255, 255, 255});
    fuel_needle = Needle(-2, -2.6, 0, {255, 0, 90});
    health_meter = Ring(-3.2, -2, 0, 0.5, 0, {255, 255, 255});
    health_needle = Needle(-3.2, -2.6, 0, {0, 255, 90});

    pointer_d = Ring(2, -2, 0, 0.5, 0, {255, 255, 255});
    compass = Needle(2, -2.6, 0, {255, 0, 0});
    compass2 = Needle(2, -2.6, 0, {0, 0, 255});

    float u = 1;
    for(int i = 0; i < 6; i++)
    {
        score[i] = Sevenseg(u, 3, {255, 0, 10});
        u += 0.25;
    }

    u = -2;
    for (int i = 0; i < 6; i++)
    {
        altitude[i] = Sevenseg(u, 3, {0, 0, 255});
        u += 0.25;
    }

    u = -2;
    for (int i = 0; i < 6; i++)
    {
        c_altitude[i] = Sevenseg(u, 3, {255, 0, 0});
        u += 0.25;
    }

    u = -2;
    for (int i = 0; i < 6; i++)
    {
        speed[i] = Sevenseg(u, 3.5, {0, 255, 10});
        u += 0.25;
    }

    for(int i = 1; i <= 5; i++)
    {
        checkpoints.push_back(glm::vec2{100*i, 100*i});
        checkpoints.push_back(glm::vec2{-100*i, 100*i});
        checkpoints.push_back(glm::vec2{-100*i, -100*i});
        checkpoints.push_back(glm::vec2{100*i, -100*i});
    }

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1200;
    int height = 1200;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    ball1.fuel = 50;
    while (!glfwWindowShouldClose(window)) {
        // Process timers
        if (t60.processTick()) {
            // Cannonballs with plane
            int hits = 0;
            auto it = e1_bset.begin();
            for(; it != e1_bset.end(); it++)
            {
                if(abs(ball1.position.y - (*it).position.y) < 3)
                {
                    if (abs(ball1.position.x - (*it).position.x) <= 5 && abs(ball1.position.z - (*it).position.z) <= 3)
                    {
                        hits++;
                        break;
                    }
                }
            }
            if (it != e1_bset.end())
                e1_bset.erase(it--);

            draw();
            glfwSwapBuffers(window);

            timer += 1;

            // Moving sea tile
            sea.set_position(ball1.position.x, 0, ball1.position.z);
            // Update health bar

            // Collision
            ring_col();
            volcano_col();

            if(timer%900 == 0 && timer)
            {
                e2_set.push_back(Para(ball1.position.x, 100, ball1.position.z));
                e2_set.push_back(Para(-ball1.position.x, 100, ball1.position.z));
                e2_set.push_back(Para(ball1.position.x, 100, -ball1.position.z));
                e2_set.push_back(Para(-ball1.position.x, 100, -ball1.position.z));
            }

            // --Bomb/Missile with sea
            for (auto it = missile_set.begin(); it != missile_set.end(); it++)
                if ((*it).position.y < 0 || (*it).position.y > 200)
                    missile_set.erase(it--);

            for (auto it = bomb_set.begin(); it != bomb_set.end(); it++)
                if ((*it).position.y < 0)
                    bomb_set.erase(it--);
            // Enemy 2 with sea

            for (auto it = e2_set.begin(); it != e2_set.end(); it++)
                if ((*it).position.y < 0)
                    e2_set.erase(it--);


            health -= hits;
            // fuel with plane
            for (auto it = fuelup.begin(); it != fuelup.end(); it++)
            {
                if (abs(ball1.position.y - (*it).position.y) < 5)
                {
                    if (abs(ball1.position.x - (*it).position.x) <= 5 && abs(ball1.position.z - (*it).position.z) <= 5)
                    {
                        fuelup.erase(it--);
                        ball1.fuel += 30;

                        if(ball1.fuel > 100) ball1.fuel = 100;
                    }
                }
            }

            // Missile/Bomb with enemies
            for (auto it = missile_set.begin(); it != missile_set.end(); it++)
            {
                for (auto it1 = e1_set.begin(); it1 != e1_set.end(); it1++)
                {
                    float x1 = (*it).position.x;
                    float y1 = (*it).position.y;
                    float z1 = (*it).position.z;
                    float x2 = (*it1).position.x;
                    float y2 = (*it1).position.y;
                    float z2 = (*it1).position.z;

                    if (distance(x1, y1, z1, x2, y2, z2) < 6 && y1 >= 0)
                    {
                        missile_set.erase(it--);
                        (*it1).alive = 0;
                        score_c += 10;
                    }
                }
            }

            for (auto it = bomb_set.begin(); it != bomb_set.end(); it++)
            {
                for (auto it1 = e1_set.begin(); it1 != e1_set.end(); it1++)
                {
                    float x1 = (*it).position.x;
                    float y1 = (*it).position.y;
                    float z1 = (*it).position.z;
                    float x2 = (*it1).position.x;
                    float y2 = (*it1).position.y;
                    float z2 = (*it1).position.z;

                    if (distance(x1, y1, z1, x2, y2, z2) < 6 && y1 >= 0)
                    {
                        bomb_set.erase(it--);
                        (*it1).alive = 0;
                        score_c += 10;
                    }
                }
            }

             // Missile/Bomb with enemies
            for (auto it = missile_set.begin(); it != missile_set.end(); it++)
            {
                for (auto it1 = e1_set.begin(); it1 != e1_set.end(); it1++)
                {
                    if ((*it1).alive)
                    {
                        float x1 = (*it).position.x;
                        float y1 = (*it).position.y;
                        float z1 = (*it).position.z;
                        float x2 = (*it1).position.x;
                        float y2 = (*it1).position.y;
                        float z2 = (*it1).position.z;

                        if (distance(x1, y1, z1, x2, y2, z2) < 8 && y1 >= 0)
                        {
                            missile_set.erase(it--);
                            (*it1).alive = 0;
                            score_c += 10;
                        }
                    }
                }
            }

            for (auto it = bomb_set.begin(); it != bomb_set.end(); it++)
            {
                for (auto it1 = e1_set.begin(); it1 != e1_set.end(); it1++)
                {
                    if ((*it1).alive)
                    {
                        float x1 = (*it).position.x;
                        float y1 = (*it).position.y;
                        float z1 = (*it).position.z;
                        float x2 = (*it1).position.x;
                        float y2 = (*it1).position.y;
                        float z2 = (*it1).position.z;

                        if (distance(x1, y1, z1, x2, y2, z2) < 8 && y1 >= 0)
                        {
                            bomb_set.erase(it--);
                            (*it1).alive = 0;
                            score_c += 10;
                        }
                    }
                }
            }

            for (auto it = missile_set.begin(); it != missile_set.end(); it++)
            {
                for (auto it1 = e2_set.begin(); it1 != e2_set.end(); it1++)
                {
                    float x1 = (*it).position.x;
                    float y1 = (*it).position.y;
                    float z1 = (*it).position.z;
                    float x2 = (*it1).position.x;
                    float y2 = (*it1).position.y;
                    float z2 = (*it1).position.z;

                    if (distance(x1, y1, z1, x2, y2, z2) < 6)
                    {
                        missile_set.erase(it--);
                        e2_set.erase(it1--);
                        score_c += 20;
                    }
                }
            }

            // Dashboard related
            ball1.fuel -= 0.025 * ball1.speed;

            if(ball1.position.y <= 20)
                critical_altitude = 1;

            else
                critical_altitude = 0;

            // Checkpoint
            arrow = Arrow(checkpoints[0][0], 20, checkpoints[0][1], {255, 0, 0});
            checkpoint_reached();
            tick_elements();
            tick_input(window);
        }
        shoot();
        // Sea collision of plane OR health <= 0
        if(ball1.sea_coll() || health <= 0)
            exit(0);

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

void volcano_col()
{
    for(int i = 0; i < volc_set.size(); i++)
        if (abs(ball1.position.x - volc_set[i].position.x) <= 70/2 && abs(ball1.position.z - volc_set[i].position.z) <= 70/2)
        {
            if(ball1.position.y < 80/2)
                exit(0);
            else if(ball1.position.y < 100/2)
                health -= 1;
        }

    // Test volcano
    if (abs(ball1.position.x - volc.position.x) <= 70 && abs(ball1.position.z - volc.position.z) <= 70)
    {
        if (ball1.position.y < 80)
            exit(0);
        else
            health -= 1;
    }
}

void ring_col()
{
    for (auto it = smoke_rings.begin(); it != smoke_rings.end(); it++)
        if (abs(ball1.position.x - (*it).position.x) <= 5 && abs(ball1.position.z - (*it).position.z) <= 5)
            if (abs(ball1.position.y - (*it).position.y) <= 5)
            {    
                score_c += 100;
                smoke_rings.erase(it--);
            }
}

float distance(float x1, float y1, float z1, float x2, float y2, float z2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2));
}

float rand_FloatRange(float a, float b)
{
    return ((b - a) * ((float)rand() / RAND_MAX)) + a;
}

void checkpoint_reached()
{
    if (distance(ball1.position.x, 0, ball1.position.z, checkpoints[0][0], 0, checkpoints[0][1]) <= 10)
    {
        if(checkpoints.empty())
        {
            cout << "You've won! :" << score_c << endl;
            exit(0);
        }
        checkpoints.erase(checkpoints.begin());
        score_c += 30;
    }
}

void shoot()
{
    for (auto it1 = e1_set.begin(); it1 != e1_set.end(); it1++)
    {
        float x1 = ball1.position.x;
        float y1 = ball1.position.y;
        float z1 = ball1.position.z;
        float x2 = (*it1).position.x;
        float y2 = (*it1).position.y;
        float z2 = (*it1).position.z;

        float d = distance(x1, y1, z1, x2, y2, z2) ;
        if (d <= 70)
        {
            float x = x1- x2, y = y1- y2, z = z1 - z2;
            glm::vec3 dir, dir1, dir2;
            dir  = glm::vec3(x/d, y/d, z/d);
            dir1 = glm::vec3(-y/sqrt(x*x + y*y), x/sqrt(x*x + y*y), 0);
            dir2 = glm::vec3(-z*x, -y*z, x*x + y*y);
            float l = glm::length(dir2);

            glm::mat4 u;
            u[0][0] = dir1[0];
            u[0][1] = dir1[1];
            u[0][2] = dir1[2];
            u[0][3] = 0;
            u[1][0] = dir2[0]/l;
            u[1][1] = dir2[1]/l;
            u[1][2] = dir2[2]/l;
            u[1][3] = 0;
            u[2][0] = dir[0];
            u[2][1] = dir[1];
            u[2][2] = dir[2];
            u[2][3] = 0;
            u[3][0] = 0;
            u[3][1] = 0;
            u[3][2] = 0;
            u[3][3] = 1;

            Bomb bull1 = Bomb(x2, 5.5, z2, dir[0]/d, dir[1]/d, dir[2]/d, 2, ball1.speed);
            bull1.cannonb = u;
            
            if(timer%60 == 0)
                e1_bset.push_back(bull1);
        }
    }
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;

    switch (camera)
    {
        case 2:
        case 3:
        case 4:
            Matrices.projection = glm::infinitePerspective(glm::radians(270.0f/screen_zoom), 1.0f, 0.1f);
            break;
    
        default:
            Matrices.projection = glm::perspective(glm::radians(270.0f/screen_zoom), 1.0f, 0.1f, 1000.0f);
            break;
    }

    Matrix_Dash.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
