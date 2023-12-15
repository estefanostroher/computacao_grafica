#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <climits>
#include <GL/glut.h>
#include "Prova3.h"
using namespace std;

// g++ -o Prova3_2 Prova3_1.cpp Prova3_2.cpp -lGL -lGLU -lglut -lm; ./Prova3_2

GLfloat light0_ambient[] = {0.1, 0.1, 0.1, 1.0};
GLfloat light0_diffuse[] = {1.0, 1.0, 1.0, 0.0};
GLfloat light1_diffuse[] = {0.1, 0.1, 0.1, 1.0};
GLfloat light0_position[] = {0.0, 100.0, -100.0, 0.0};
GLfloat light1_position[] = {0.0, 0.0, 50.0, 1.0};
GLfloat light2_diffuse[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light2_position[] = {0.0, -50.0, -50.0, 11.0};
GLfloat light2_lookat[] = {1.0, 0.0, 0.0, 0.0};
GLfloat specularLight[] = {1.0f, 0.0f, 0.0f, 1.0f};
GLfloat globalAmbient[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light2_spot[] = {0.0, 0.0, 0.0, 1.0};
GLfloat cor_spec[] = {1.0, 0.0, 0.0};
GLfloat global_ambient[] = {0.4, 0.4, 0.4, 1};

float cameraX = 0.0f, cameraY = 12.0f, cameraZ = 30.0f;
float centerX = 0.0f, centerY = 0.0f, centerZ = 0.0f;
float rotate = 0.0, alpha, theta, omega, sc = 1.0;
float step_alpha = 0.2, step_gama = 0.0, raio = 1.0, gama = 0.0;

vector<Objeto *> objetos;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLightfv(GL_LIGHT2, GL_SPOT_EXPONENT, light2_diffuse);
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light2_lookat);
    glLightfv(GL_LIGHT0, GL_SPECULAR, cor_spec);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glEnable(GL_LIGHT2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light2_spot);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    gluLookAt(cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glScalef(sc, sc, sc);

    glPushMatrix();
    glTranslatef(objetos[0]->posX, objetos[0]->posY, objetos[0]->posZ - alpha);
    glRotatef(theta, -1.0, 0.0, 0.0);
    objetos[0]->desenharObjeto(0, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(objetos[1]->posX, objetos[1]->posY, objetos[1]->posZ - gama);

    glRotatef(-90.0, 1.0, 0.0, 0.0); // Rotação para colocar o objeto em pé
                                     // glRotatef(theta, 0.0, 0.0, 1.0);
    objetos[1]->desenharObjeto(0, 3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(objetos[2]->posX, objetos[2]->posY, objetos[2]->posZ - gama);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    objetos[2]->desenharObjeto(0, 3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(objetos[3]->posX, objetos[3]->posY, objetos[3]->posZ - gama);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    objetos[3]->desenharObjeto(0, 3);
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void init()
{
    glShadeModel(GL_FLAT);
    glClearDepth(100.0f);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE);

    glDepthFunc(GL_LEQUAL);
    glDepthRange(50, -50);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glDepthMask(GL_TRUE);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a':
        cameraX -= 1;
        break;
    case 'd':
        cameraX += 1;
        break;
    case 'w':
        cameraY += 1;
        break;
    case 's':
        cameraY -= 1;
        break;
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if (button == 3)
        cameraZ -= 1;
    if (button == 4)
        cameraZ += 1;
    glutPostRedisplay();
}

void myReshape(int w, int h)
{
    float aspectRatio = (float)w / (float)h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45, aspectRatio, -10, 10);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void timer(int value)
{
    alpha += step_alpha;
    theta += 1.0;
    gama += step_gama;

    if (alpha > 18)
        omega -= 0.1;

    if (theta >= 360)
        theta = 0.0;

    if (alpha > 50)
    {
        alpha = 0.0;
        omega = 0;
    }

    if (fabs(objetos[0]->posZ - alpha) < 2 * raio)
    {
        step_alpha = -0.001;
        step_gama = 0.2;
    }
    glutPostRedisplay();
    glutTimerFunc(10, timer, 0);
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cout << "\nUso: " << argv[0] << " <arquivo.obj> <arquivo.obj>" << endl;
        return 1;
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow(argv[0]);
    glutInitWindowSize(1000, 576);
    // glutFullScreen();
    init();
    glutDisplayFunc(display);

    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);

    glutReshapeFunc(myReshape);
    glutTimerFunc(10, timer, 0);

    Objeto *obj1 = new Objeto(0, 0, 30);
    obj1->carregarObjeto(argv[1]);
    objetos.push_back(obj1);

    Objeto *obj2 = new Objeto(0, 0, 0);
    obj2->carregarObjeto(argv[2]);
    objetos.push_back(obj2);

    Objeto *obj3 = new Objeto(2, 0, 0);
    obj3->carregarObjeto(argv[2]);
    objetos.push_back(obj3);

    Objeto *obj4 = new Objeto(-2, 0, 0);
    obj4->carregarObjeto(argv[2]);
    objetos.push_back(obj4);

    glutMainLoop();

    delete obj1;
    delete obj2;

    return 0;
}
