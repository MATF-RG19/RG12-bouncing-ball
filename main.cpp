#include "header.h"
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cstdio>
#include <cmath> 
#include <ctime>
#include <cstdlib>
#include <vector>
#include <queue>
#include <string>

using namespace std;

void texture_init();

int main(int argc, char **argv)
{
    /* Inicijalizuje se GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    /* Kreira se prozor. */
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    /* Registruju se callback funkcije */
    glutDisplayFunc(on_display);
    glutReshapeFunc(on_reshape);
    glutKeyboardFunc(on_keyboard);

    /* Obavlja se OpenGL inicijalizacija. */
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D);
    
    texture_init();
    quadricsInit1();
    

    float light_position[] = {10,10, 10, 0}; //10 10 10 0 ~ maddness 4, -16, 0, 0
    float light_ambient[] = {.3f, .3f, .3f, 1};
    float light_diffuse[] = {.7f, .7f, .7f, 1};
    float light_specular[] = {.7f, .7f, .7f, 1};

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);


    glClearColor(0.24, 0.53, 0.77, 1);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);

	  obstacles_init();
 	
    glutMainLoop();

  return 0;
}
