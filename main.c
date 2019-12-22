#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define TIMER_INTERVAL 20
#define TIMER_ID 0
#define PI 3.14159265359

static void on_display();
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);
static void on_timer(int id);

static void draw_axis(float len);
static void draw_ball();
static void draw_floor();

float animation_parameter = 0;
int animation_ongoing = 0;

float goredole = 0, levodesno = 0;




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

    float light_position[] = {-1, 1, 1, 0};
    float light_ambient[] = {.3f, .3f, .3f, 1};
    float light_diffuse[] = {.7f, .7f, .7f, 1};
    float light_specular[] = {.7f, .7f, .7f, 1};

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);


    glClearColor(.5f, .5f, .5f, 1);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
 
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

void on_keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'w':
        case 'W':
        		goredole += 0.1;      			
        		break;
        case 's':
        case 'S':
        		goredole -= 0.1;      			
        		break;
        case 'a':
        case 'A':
        		levodesno -= 0.1;      			
        		break;
        case 'd':
        case 'D':
        		levodesno += 0.1;      			
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
}

void on_timer(int id) {
    if (id == TIMER_ID) {
        /*
         *      Azuriraj animacioni parametar po potrebi
         * POCETAK STUDENTSKOG KODA
         */

        if (animation_parameter >= 180) {
            animation_ongoing = 0;
            return;
        }

        animation_parameter += 1.5f;

        /*
         * KRAJ STUDENTSKOG KODA
         */
    }

    glutPostRedisplay();

    /*
     * POCETAK STUDENTSKOG KODA
     */
    if (animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
    /*
     * KRAJ STUDENTSKOG KODA
     */
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
    

    glutSolidSphere(0.5, 30, 30);

    glPopMatrix();
}

void draw_floor(){
    glPushMatrix();
/*
    GLdouble plane0[] = {0, 0, -1, 0};
    GLdouble plane1[] = {0, -1, 0, 0};

    glEnable(GL_CLIP_PLANE0);
    glEnable(GL_CLIP_PLANE1);

    glClipPlane(GL_CLIP_PLANE0, plane0);
    glClipPlane(GL_CLIP_PLANE1, plane1);
    
    glDisable(GL_CLIP_PLANE0);
    glDisable(GL_CLIP_PLANE1);
*/
    GLfloat ambient[] = {0.3,0.3,0.3,1};
    GLfloat diffuse[] = {0,0.7,0,0};
    GLfloat specular[] = {0.6,0.6,0.6,1};
    GLfloat shininess = 80;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);


    glutSolidCube(3);



    glPopMatrix();
}


void on_display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /*
    *       Animiraj kretanje kamere
    * POCETAK STUDENTSKOG KODA
    */

    gluLookAt(levodesno, goredole, 15,
              0, 7, 0,
              0, 1, 0);


    /*
    * KRAJ STUDENTSKOG KODA
    */



    
    draw_axis(5);
    glPushMatrix();

        draw_floor();

    glPopMatrix();
   

   
    glPushMatrix();

   


        glTranslatef(0, 0, 10);
        draw_ball();

    glPopMatrix();


    glutSwapBuffers();
}

