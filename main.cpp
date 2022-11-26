#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>
#include <iostream>

#define MAX_VEHICLES 7

void display();
int i, q;
int score = 0;
int screen = 0;
int collide = 3;
char buffer[10];

int vehicleX = 200, vehicleY = 70;
int otherVehiclesX[MAX_VEHICLES], otherVehiclesY[MAX_VEHICLES];
int divx = 250, divy = 4, movd;
int speed = 10000000, speedDivider = 10;

void init();

void drawText(char ch[], int xpos, int ypos)
{
    int numofchar = strlen(ch);
    glLoadIdentity();
    glRasterPos2f(xpos, ypos);
    for (i = 0; i <= numofchar - 1; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch[i]);
    }
}

void drawTextNum(char ch[], int numtext, int xpos, int ypos)
{
    int len;
    int k;
    k = 0;
    len = numtext - strlen(ch);
    glLoadIdentity();
    glRasterPos2f(xpos, ypos);
    for (i = 0; i <= numtext - 1; i++)
    {
        if (i < len)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '0');
        else
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch[k]);
            k++;
        }
    }
}

void ovpos()
{
    glClearColor(0, 0, 0, 0);
    for (i = 0; i < MAX_VEHICLES; i++)
    {
        if (rand() % 4 == 0)
        {
            otherVehiclesX[i] = 100;
        }
        else if (rand() % 3 == 0)
        {
            otherVehiclesX[i] = 200;
        }
        else if (rand() % 2 == 0)
        {
            otherVehiclesX[i] = 300;
        }
        else
        {
            otherVehiclesX[i] = 400;
        }
        otherVehiclesY[i] = 1000 - i * 160;
    }
}

void drawRoad()
{
    glBegin(GL_QUADS);
    glColor3f(0, 0, 0);
    glVertex2f(10, 500);
    glVertex2f(10, 0);
    glVertex2f(490, 0);
    glVertex2f(490, 500);
    glEnd();
}

void drawDivider()
{
    glLoadIdentity();
    glTranslatef(0, movd, 0);
    for (i = 1; i <= 10; i++)
    {
        glColor3f(1, 1, 1);
        glBegin(GL_QUADS);
        glVertex2f(divx - 5, divy * 15 * i + 18);
        glVertex2f(divx - 5, divy * 15 * i - 18);
        glVertex2f(divx + 5, divy * 15 * i - 18);
        glVertex2f(divx + 5, divy * 15 * i + 18);
        glEnd();
    }
    glLoadIdentity();
}

void drawVehicle()
{
    glPointSize(10.0);
    glBegin(GL_POINTS);
    glColor3f(0.5, 0.5, 0.5);
    glVertex2f(vehicleX - 20, vehicleY + 16);
    glVertex2f(vehicleX + 20, vehicleY + 16);
    glVertex2f(vehicleX - 20, vehicleY - 16);
    glVertex2f(vehicleX + 20, vehicleY - 16);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    glVertex2f(vehicleX - 20, vehicleY + 20);
    glVertex2f(vehicleX - 20, vehicleY - 20);
    glVertex2f(vehicleX + 20, vehicleY - 20);
    glVertex2f(vehicleX + 20, vehicleY + 20);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0, 0, 1);
    glVertex2f(vehicleX - 18, vehicleY + 20);
    glVertex2f(vehicleX - 17, vehicleY + 40);
    glVertex2f(vehicleX + 17, vehicleY + 40);
    glVertex2f(vehicleX + 18, vehicleY + 20);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0, 0, 1);
    glVertex2f(vehicleX - 18, vehicleY - 20);
    glVertex2f(vehicleX - 17, vehicleY - 35);
    glVertex2f(vehicleX + 17, vehicleY - 35);
    glVertex2f(vehicleX + 18, vehicleY - 20);
    glEnd();
}

void drawOtherVehicles() // other cars
{

    for (i = 0; i < MAX_VEHICLES; i++)
    {
        glPointSize(10.0);
        glBegin(GL_POINTS);
        glColor3f(0.5, 0.5, 0.5);
        glVertex2f(otherVehiclesX[i] - 20, otherVehiclesY[i] + 16);
        glVertex2f(otherVehiclesX[i] + 20, otherVehiclesY[i] + 16);
        glVertex2f(otherVehiclesX[i] - 20, otherVehiclesY[i] - 16);
        glVertex2f(otherVehiclesX[i] + 20, otherVehiclesY[i] - 16);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.8, 0.8, 0);
        glVertex2f(otherVehiclesX[i] - 20, otherVehiclesY[i] + 20);
        glVertex2f(otherVehiclesX[i] - 20, otherVehiclesY[i] - 20);
        glVertex2f(otherVehiclesX[i] + 20, otherVehiclesY[i] - 20);
        glVertex2f(otherVehiclesX[i] + 20, otherVehiclesY[i] + 20);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(otherVehiclesX[i] - 18, otherVehiclesY[i] + 20);
        glVertex2f(otherVehiclesX[i] - 17, otherVehiclesY[i] + 40);
        glVertex2f(otherVehiclesX[i] + 17, otherVehiclesY[i] + 40);
        glVertex2f(otherVehiclesX[i] + 18, otherVehiclesY[i] + 20);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(otherVehiclesX[i] - 18, otherVehiclesY[i] - 20);
        glVertex2f(otherVehiclesX[i] - 17, otherVehiclesY[i] - 35);
        glVertex2f(otherVehiclesX[i] + 17, otherVehiclesY[i] - 35);
        glVertex2f(otherVehiclesX[i] + 18, otherVehiclesY[i] - 20);
        glEnd();

        otherVehiclesY[i] = otherVehiclesY[i] - 8;

        if (abs(otherVehiclesY[i] - vehicleY) <= 80
            && abs(otherVehiclesX[i] - vehicleX) <= 40
        )
        {
            collide--;
            glutIdleFunc(NULL);
            ovpos();
            glutIdleFunc(display);
        }

        if (otherVehiclesY[i] < -25)
        {
            if (rand() % 4 == 0)
            {
                otherVehiclesX[i] = 100;
            }
            else if (rand() % 3 == 0)
            {
                otherVehiclesX[i] = 200;
            }
            else if (rand() % 2 == 0)
            {
                otherVehiclesX[i] = 300;
            }
            else
            {
                otherVehiclesX[i] = 400;
            }
            otherVehiclesY[i] = 600;
        }
    }
}

void Specialkey(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        if (vehicleX <= 50)
            vehicleX = 50;
        else
            vehicleX -= 40;
        break;
    case GLUT_KEY_RIGHT:
        if (vehicleX >= 450)
            vehicleX = 450;
        else
            vehicleX += 40;
        break;
    case GLUT_KEY_UP:
        speed -= 100000;
        // if (vehicleY < 450)
        //     vehicleY += 10;
        break;
    case GLUT_KEY_DOWN:
        speed += 150000;
        // if (vehicleY >= 10)
        //     vehicleY -= 10;
        break;
    }

    glutPostRedisplay();
}

void Normalkey(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'y':
        score = 0;
        collide = 3;
        ovpos();
        glutIdleFunc(display);
        break;

    case 'n':
        exit(0);
    }
}

void drawSideBorder()
{
    for (int i = 0; i < 800; i += 20)
    {
        glPointSize(15.0);
        glBegin(GL_POINTS);
        glColor3f(1, 0, 0);
        int temp = i;
        for (int j = 0; j < 10; j++)
        {
            glVertex2f(0, i + j);
            temp = i + j;
        }

        glColor3f(1, 1, 1);
        for (int j = 0; j < 10; j++)
            glVertex2f(0, temp + j);
        glEnd();
    }
    for (int i = 0; i < 800; i += 20)
    {
        glPointSize(15.0);
        glBegin(GL_POINTS);
        glColor3f(1, 0, 0);
        int temp = i;
        for (int j = 0; j < 10; j++)
        {
            glVertex2f(500, i + j);
            temp = i + j;
        }
        
        glColor3f(1, 1, 1);
        for (int j = 0; j < 10; j++)
            glVertex2f(500, temp + j);
        glEnd();
    }
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawSideBorder();
    drawRoad();
    drawDivider();
    drawVehicle();
    drawOtherVehicles();
    movd = movd - speedDivider;
    if (movd < -60)
    {
        movd = 0;
    }

    score = score + 1;
    glColor3f(1, 1, 1);
    drawText("Score:", 360, 455);
    itoa(score, buffer, 10);
    drawTextNum(buffer, 6, 420, 455);
    drawText("Life:", 360, 355);
    itoa(collide, buffer, 10);
    drawTextNum(buffer, 1, 420, 355);
    glutSwapBuffers();
    for (q = 0; q <= speed; q++)
    {
        ;
    }
    if (collide == 0)
    {
        glutIdleFunc(NULL);
        glColor3f(1, 1, 1);
        drawText("Game Over", 50, 350);
        drawText("Play again? Press y or n", 20, 300);
        drawText("Life:", 360, 355);
        itoa(collide, buffer, 10);
        drawTextNum(buffer, 1, 420, 355);
        glutSwapBuffers();
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 500);
    glutCreateWindow("CAR DASH");
    ovpos();
    init();
    glutDisplayFunc(display);
    glutSpecialFunc(Specialkey);
    glutKeyboardFunc(Normalkey);
    glutIdleFunc(display);

    glutMainLoop();
}
