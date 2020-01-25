#ifndef HEADER
#define HEADER

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

#define TIMER_INTERVAL 20
#define TIMER_ID 0
#define PI 3.14159265359



void on_display();
void on_reshape(int width, int height);
void on_keyboard(unsigned char key, int x, int y);
void on_timer(int id);
void draw_axis(float len);
void text_log(float x, float z, const char *s);
void draw_floor();
void draw_ball();
void obstacles_init();
void quadricsInit1();
void draw_obstacles();
void move_forward(double val1);
void move_left(double val1);
void move_right(double val1);
void obstacle_renew();


#endif