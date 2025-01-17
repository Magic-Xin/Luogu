#include <cmath>
#include "GLUT/glut.h"

#define PI 3.14259265

int winW = 600, winH = 600;

void DrawAxis()
{
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-10.0f, 0.0f, 0.0f);
    glVertex3f(10.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -10.0f, 0.0f);
    glVertex3f(0.0f, 10.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -10.0f);
    glVertex3f(0.0f, 0.0f, 10.0f);
    glEnd();
}

void DrawSphere(float radius, int step)
{
    float x, y, z;

    glBegin(GL_TRIANGLE_STRIP);
    for (float i = 0.0; i < PI; i += PI/step)
    {
        for (float j = 0.0; j < 2.0 * PI; j += PI/step)
        {
            x = radius * std::cos(j) * std::sin(i);
            y = radius * std::sin(j) * std::sin(i);
            z = radius * std::cos(i);
            glVertex3f(x, y, z);
            x = radius * std::cos(j) * std::sin(i + PI/step);
            y = radius * std::sin(j) * std::sin(i + PI/step);
            z = radius * std::cos(i + PI/step);
            glVertex3f(x, y, z);
        }
    }
    glEnd();
}

void RenderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 1.0f);
    glLoadIdentity();
    //gluLookAt(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    gluLookAt(5.0f, 5.0f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, -1.0f);
    glColor4f(1.0f, 0.5f, 0.2f, 1.0f);
    DrawSphere(2.0f, 10);
    DrawAxis();

    glutSwapBuffers();
}

void Reshape(int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5.0f, 5.0f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, -1.0f);
}

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitWindowPosition (100, 100);
    glutInitWindowSize(winW, winH);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow("Sphere Test");

    glEnable(GL_DEPTH_TEST);
    glutReshapeFunc(Reshape);
    glutDisplayFunc(RenderScene);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glutMainLoop();
    return 0;
}