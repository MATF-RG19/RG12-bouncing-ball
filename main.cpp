#include <GL/glut.h>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <queue>

#define TIMER_INTERVAL 20
#define TIMER_ID 0
#define PI 3.14159265359

using namespace std;

static void on_display();
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);
static void on_timer(int id);

static void draw_axis(float len);
static void draw_ball();
static void draw_floor();
void obstacles_init();
void quadricsInit1();
void draw_obastacles();



float animation_parameter = 0;
float translateObs = 0;
double translation_animate = 0;
int animation_ongoing = 0;
int faktorRot = 0;
bool initovane_prepreke = false;

GLUquadric *qobj;


struct prepreka{
	
	double pozx = 1.9;
	double pozy; //dodeljuje se random
	int pozz; //rotiranjem dobijem?
};

vector<prepreka> prepreke(400);

/* KLIPING
    GLdouble plane0[] = {0, 0, -1, 0};
    GLdouble plane1[] = {0, -1, 0, 0};

    glEnable(GL_CLIP_PLANE0);
    glEnable(GL_CLIP_PLANE1);

    glClipPlane(GL_CLIP_PLANE0, plane0);
    glClipPlane(GL_CLIP_PLANE1, plane1);
    
    glDisable(GL_CLIP_PLANE0);
    glDisable(GL_CLIP_PLANE1);
*/

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
    
    quadricsInit1();
    

    float light_position[] = {-1, 1, 1, 0};
    float light_ambient[] = {.3f, .3f, .3f, 1};
    float light_diffuse[] = {.7f, .7f, .7f, 1};
    float light_specular[] = {.7f, .7f, .7f, 1};

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);


    glClearColor(0, 0.5, 0.5, 1);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
    
	//if(!initovane_prepreke)
	//{
		obstacles_init();
	//	initovane_prepreke = true;
	//}
 	
 	for(int i=0; i < 400; i++)
	{
		cout<< prepreke[i].pozx<<" "<<prepreke[i].pozy<<" "<< prepreke[i].pozz <<endl;
	}
 	
    glutMainLoop();

  return 0;
}

/*
 *POMOCNA FUNKCIJA ZA ISCRTAVANJE KOODINATNOG SISTEMA
 */
void draw_axis(float len) {
    glDisable(GL_LIGHTING);

    glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(len,0,0);

        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,len,0);

        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,len);
    glEnd();

    glEnable(GL_LIGHTING);
}

void quadricsInit1(){
    
    qobj = gluNewQuadric();
    gluQuadricNormals(qobj, GLU_SMOOTH);
    
}

void on_keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'w':
        case 'W':
        		    			
        		break;
        case 's':
        case 'S':
        		      			
        		break;
        case 'a':
        case 'A':
        		faktorRot += 3;      			
        		break;
        case 'd':
        case 'D':
        		faktorRot -= 3;      			
        		break;
        
        case 'g':
        case 'G':
            if (!animation_ongoing) {
                animation_ongoing = 1;
                glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
            }
            break;
        case 'p':
        case 'P':
            animation_ongoing = 0;
            break;
        case 'r':
        case 'R':
            animation_parameter = 0;
            glutPostRedisplay();
            break;
        /*
         * KRAJ STUDENTSKOG KODA
         */
        case 27:
          exit(0);
          break;
    }
    glutPostRedisplay();
}

void on_timer(int id) {
    if (id == TIMER_ID) {
	
		if(animation_ongoing){
			//translateObs -= 1.5f;
			
			animation_parameter++;
			if(animation_parameter > 90)
			{
				animation_parameter = 0;
			}
			
			cout<< animation_parameter<<endl;
			//ovde provera kolizije
			//if colision tru then stani animacija ->uradi sta treba..
			
			
		}
    }

    glutPostRedisplay();


    if (animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }

}

void on_reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(30, (float) width/height, 1, 1000);
}

void draw_ball(){
    glPushMatrix();
    
    GLfloat ambient1[] = {0.3,0.3,0.3,1};
    GLfloat diffuse1[] = {0.7,0.0,0,0};
    GLfloat specular1[] = {0.6,0.6,0.6,1};
    GLfloat shininess1 = 80;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular1);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess1);
    
    
    glTranslatef(2.55, -8, 0); 
    glutSolidSphere(0.3, 30, 30);
    
    
    
    //gluCylinder(qobj, 10, 1.0, 0.4, 20, 20);

    glPopMatrix();
}

void draw_floor(){
    glPushMatrix();

    GLfloat ambient[] = {0.3,0.3,0.3,1};
    GLfloat diffuse[] = {0,0.7,0,0};
    GLfloat specular[] = {0.6,0.6,0.6,1};
    GLfloat shininess = 80;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	 glTranslatef(0,-100, 0);
	 glRotatef(faktorRot, 0, 1, 0);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(qobj, 2.4, 2.0, 400, 20, 20);
    glTranslatef(0,100, 0);
	 //glutSolidCylinder
	 
    glPopMatrix();
}


void draw_obstacle(int rot, double pomeraj){

	glPushMatrix();

		GLfloat ambient2[] = {0.3,0.3,0.3,1};
		GLfloat diffuse2[] = {1,0.0,1,0};
		GLfloat specular2[] = {0.6,0.6,0.6,1};
		GLfloat shininess2 = 80;

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient2);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse2);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular2);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess2);
				
		glRotatef(rot, 0, 1, 0);
		glTranslatef(1.9, pomeraj, 0); //1.9
		glScalef(1, 1, 0.4);
		glutSolidCube(3);
		
	glPopMatrix();
}

void draw_obastacles(){
		//velicina vekt je A*B
	for(int i=0; i < 100; i++) //A
	{
		for(int j= 0; j < 4; j++) //B
		{			
			draw_obstacle(prepreke[4*i + j].pozz, prepreke[4*i + j].pozy);			
		}
	}
}


void obstacles_init()
{
	srand(time(0));//NULL
	double pomeraj = 5;
	for(int i=0; i < 100; i++)
	{
		for(int j= 0; j < 1; j++)
		{
			int strana = rand()%4;
			int dodatnaRot = rand()%90;
						
			prepreke[i].pozy = pomeraj;
			prepreke[i].pozz = strana*90 + dodatnaRot;
			
			int rot = strana*90 + dodatnaRot;
		}
		pomeraj += rand()%3 + 4; //ispravi	
	}
}


void on_display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	
    gluLookAt(4, -16, 0,
              0, 200, 0,
              0, 1, 0);

    draw_axis(5);
    glPushMatrix();

        draw_floor();

    glPopMatrix();
   	
   draw_obastacles();
   	
    glPushMatrix();
    /*	glRotatef(faktorRot, 0, 1, 0);
		glTranslatef(0,translateObs, 0);
      draw_obstacle(0,400);*/
    glPopMatrix();

    glPushMatrix();  
        draw_ball();
    glPopMatrix();

    glutSwapBuffers();
}

