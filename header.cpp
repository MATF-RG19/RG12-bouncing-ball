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

static char buffer[30];

static double translation_animate = 0.3;
static double translation_rotate = 1;
static double rotira_se_levo;
static double rotira_se_desno;
static double faktor_ubrzanja = 0;
static double faktor_skretanja = 0;
static double faktor_rot = 0; //

static int broj_prepreka = 100;
static int health = 3;
static int max_param = -1;
static int index = 0;
static int pozmax = broj_prepreka - 1;

static int strana = 0;


static int animation_ongoing = 0;
static int animation_parameter = 0;

static bool initovane_prepreke = false;
static bool temp = false;

static GLUquadric *qobj;


struct prepreka{
	
	double pozx = 1.2;
	double pozy; //
	double pozz; //
};

static vector<prepreka> prepreke(broj_prepreka); //smanji

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

void text_log( float x, float z, const char *s)
{
    glDisable(GL_LIGHT0);

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glRasterPos3f(x, -6, z);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char *>( s ) ); 

    glEnable(GL_LIGHT0);
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
        		faktor_rot += 0.3; 
        		rotira_se_levo = 1;
        		rotira_se_desno = 0;    			
        		break;
        case 'd':
        case 'D':
        		faktor_rot -= 0.3;
        		rotira_se_levo = 0;
        		rotira_se_desno = 1;
        		break;
        
        case 'g':
        case 'G':
            if (!animation_ongoing && health > 0) {
                animation_ongoing = 1;
                glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
            }
            break;
        case 'p':
        case 'P':
            animation_ongoing = 0;
            break;
        case 'r':
        case 'R': //popravi ne radi lepo
            animation_parameter = 0;
            animation_ongoing = 0;
            faktor_ubrzanja = 0;
            translation_rotate = 1;
            health = 3;
            index = 0;
			pozmax = broj_prepreka - 1;
            max_param = -1; //proveravanje kolizije se vraca na default
            obstacle_renew();
            obstacles_init();
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
	
			animation_parameter++;
			if(animation_parameter%1000 == 0)   //koliko cesto se ubrzava
			{		
				faktor_ubrzanja += 0.05;         // ovde se igrica ubrzava
				translation_rotate += 0.1;			//srazmerno povecati i brzinu rotacije
			}												//u move left i move right		
			
		}
		
		obstacle_renew();
		
		/*text_log(20,20, "POENI");*/
		
		move_forward(translation_animate + faktor_ubrzanja);

		//dodati W za pravo?
		if(rotira_se_levo == 1 && rotira_se_desno == 0)
			move_left(translation_rotate); //param_left
		else
			move_right(translation_rotate);	
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

    gluPerspective(30, (float) width/height, 1, 500);
}

void move_forward(double val1)
{
	for(int i=0; i < broj_prepreka; i++)
	{
		prepreke[i].pozy -= val1;
	}	
}

void move_left(double val1)
{
	for(int i=0; i < broj_prepreka; i++)
	{
		
		prepreke[i].pozz = (prepreke[i].pozz + val1); //pazi
		if(prepreke[i].pozz > 360)
			prepreke[i].pozz -= 360; // =0
	}	
}

void move_right(double val1)
{
	for(int i=0; i < broj_prepreka; i++)
	{
		prepreke[i].pozz = (prepreke[i].pozz - val1); //pazi
		if(prepreke[i].pozz < 0)
			prepreke[i].pozz += 360; // =360
	}
}


void draw_ball(){
    glPushMatrix();

    GLfloat diffuse1[] = { 0.24, 0.53, 0.77, 0};
    GLfloat ambient1[] = {0.3,0.3,0.3,1};
    GLfloat specular1[] = {0.6,0.6,0.6,1};
    GLfloat shininess1 = 80;
    /*
    if(blink_ball){
        srand(time(NULL));
        diffuse1[0] = rand()%11/10.0;
        diffuse1[1] = rand()%11/10.0;
        diffuse1[2] = rand()%11/10.0;
    }*/

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular1);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess1);

    
    glTranslatef(2.55, -8, 0);
    glRotatef((4* animation_parameter)%360, 0, 0, 1);
    glutSolidSphere(0.3, 50, 50);
    
    //gluCylinder(qobj, 10, 1.0, 0.4, 20, 20);

    glPopMatrix();
}

void draw_floor(){
    glPushMatrix();

    GLfloat ambient[] = {0.3,0.3,0.3,1};
    GLfloat diffuse[] = {1,0.7,0,0};
    GLfloat specular[] = {0.6,0.6,0.6,1};
    GLfloat shininess = 80;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	 glTranslatef(0,-100, 0);
	 glRotatef(faktor_rot, 0, 1, 0);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(qobj, 2.4, 2.0, 400, 20, 20);
    glTranslatef(0,100, 0);
	 //glutSolidCylinder
	 
    glPopMatrix();
}

void obstacle_renew()
{		
	if(prepreke[index].pozy < -13)
	{
		double MaxUdaljenost = prepreke[pozmax].pozy + rand()%3 + 9;
		
		for(int j = 0; j < 4; j++)
		{
			int dodatnaRot = rand()%90;
						
			prepreke[index + j].pozy = MaxUdaljenost;;
			prepreke[index + j].pozz = j*90 + dodatnaRot; //rotacija
		}
		index += 4; pozmax = index-1;
		if(index == broj_prepreka){		
			index = 0;
			pozmax = broj_prepreka - 1;	
		}
	}
}

void draw_obstacle(int rot, double pomeraj, double visina){

	glPushMatrix();

		GLfloat ambient2[] = {0.4,0.4,0.4,1};
		GLfloat diffuse2[] = {1,0.0,0,0};
		GLfloat specular2[] = {0.6,0.6,0.6,1};
		GLfloat shininess2 = 80;

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient2);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse2);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular2);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess2);
				
		glRotatef(rot, 0, 1, 0);
		glTranslatef(visina, pomeraj, 0); // 0.75 je min visina za x koord
		glScalef(3, 3, 1.2);
		glutSolidCube(1);
		//glutWireCube(3);
		
	glPopMatrix();
}

void draw_obstacles(){
	
	for(int i=0; i < broj_prepreka; i++)
	{
        if(max_param == -1){

            if((prepreke[i].pozz >= 0 && prepreke[i].pozz <=20 
            || (prepreke[i].pozz >= 340 && prepreke[i].pozz <360))
            && (prepreke[i].pozy >= (-9.6) && prepreke[i].pozy <= (-5.2)))
            {
                max_param = animation_parameter;
                health--;

                if(health < 1) animation_ongoing = 0;

                cout<< animation_parameter <<endl;
            }
        }
        else if(max_param + 50 <= animation_parameter){
            max_param = -1;
             
        }
        else{ 

        }

		draw_obstacle(prepreke[i].pozz, prepreke[i].pozy, prepreke[i].pozx);
	}
}

void obstacles_init()
{
	srand(time(0));//NULL
	double pomeraj = 9;
	for(int i=0; i < broj_prepreka/4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			int dodatnaRot = rand()%90;
						
			prepreke[4*i + j].pozy = pomeraj;
			prepreke[4*i + j].pozz = j*90 + dodatnaRot; //rotacija
		}
		pomeraj += rand()%3 + 9; //podesi
	}
}


void on_display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	
    gluLookAt(4, -16, 0,
              0, 200, 0,
              0, 1, 0);

    sprintf(buffer, "Score : %d ", animation_parameter);
    text_log(6.2, 2.5, buffer);
    
    sprintf(buffer, "Health : %d ", health);
    text_log(6, 2.5, buffer);


    //draw_axis(5);
    glPushMatrix();

        draw_floor();

    glPopMatrix();
    
   /* glPushMatrix();
    	draw_obstacle(7, -5, 1);
    glPopMatrix();*/
   	
    draw_obstacles();

    temp = true;
    if(max_param != -1)
    {
        temp = (animation_parameter / 8) % 2;
    }
    if(temp == true)
        draw_ball();


    glutSwapBuffers();
}
