
//  Mobil3D.cpp

//  Nama : Dandy Faishal Fahmi
//  NIM  : 24060123140136
//  LAB  : GKV B1

#include <math.h>
#include <GLUT/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DEG2RAD 3.14159 / 180.0

float angleX = 0.0f, angleY = 0.0f, deltaAngleX = 0.0f, deltaAngleY = 0.0f, ratio;
float x = 0.0f, y = 1.75f, z = 15.0f;
float lx = 0.0f, ly = 0.0f, lz = -1.0f;
int deltaMove = 0, deltaStrafe = 0, deltaUp = 0, h, w;
int bitmapHeight = 12;

void Reshape(int w1, int h1)
{
    if (h1 == 0) h1 = 1;
    w = w1;
    h = h1;
    ratio = 1.0f * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45, ratio, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

void orientMe(float ang)
{
    lx = sin(angleX);
    ly = sin(angleY); // Tidak perlu mengubah komponen Y
    lz = -cos(angleX);
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

void moveMeFlat(int i)
{
    x = x + i * (lx)*0.01;  // Mengurangi faktor kecepatan menjadi 0.01
    z = z + i * (lz)*0.01;  // Mengurangi faktor kecepatan menjadi 0.01
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

void strafeMeFlat(int i)
{
    x = x + i * (lz)*0.01;  // Mengurangi faktor kecepatan menjadi 0.01
    z = z - i * (lx)*0.01;  // Mengurangi faktor kecepatan menjadi 0.01
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

void moveMeUp(int i)
{
    y += i * 0.01;  // Mengurangi faktor kecepatan menjadi 0.01
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

void Grid() {
    double i;
    const float Z_MIN = -50, Z_MAX = 50;
    const float X_MIN = -50, X_MAX = 50;
    const float gap = 1.5;
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINES);
    for (i = Z_MIN; i < Z_MAX; i += gap) {
        glVertex3f(i, 0, Z_MIN);
        glVertex3f(i, 0, Z_MAX);
    }

    for (i = X_MIN; i < X_MAX; i += gap) {
        glVertex3f(X_MIN, 0, i);
        glVertex3f(X_MAX, 0, i);
    }
    glEnd();
}

void Mobil3D(){
    glPushMatrix();
        glScalef(1.6, 1.6, 1.6);
        glPushMatrix();
            glTranslatef(-0.3, 0.0, 0);
            // Badan mobil van
            glPushMatrix();
                glTranslatef(-0.9, 0.8, 0);
                glScalef(4, 2, 4);
                glColor3f(0.0, 0.0, 1.0);
                glutSolidCube(0.5);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(1, 0.8, 0);
                glScalef(6, 2, 4);
                glColor3f(0.0, 0.0, 1.0);
                glutSolidCube(0.5);
            glPopMatrix();
    
                glPushMatrix();
                    glTranslatef(1, 1.4, 0);
                    glScalef(12.1, 6, 8);
                    glColor3f(0.0, 0.0, 1.0);
                    glutSolidCube(0.25);
                glPopMatrix();

            // Lampu Utama
            glPushMatrix();
                glTranslatef(-1.87, 1.0, -0.00);
                glScalef(0.2, 0.31, 3.9);
                glColor3f(1.0, 1.0, 1.0);
                glutSolidCube(0.5);
            glPopMatrix();
            // Lampu Rem
            glPushMatrix();
                glTranslatef(2.5, 1.0, -0.00);
                glScalef(0.2, 0.31, 3.9);
                glColor3f(1.0, 0.0, 0.0);
                glutSolidCube(0.5);
            glPopMatrix();
            
            //Kaca depan
            glPushMatrix();
                glTranslatef(-0.4, 1.3, -0.001);
                glScalef(17, 12, 19.5);
                glRotatef(228, 0, 0, 250);
                glColor3f(0.66, 0.66, 0.66);
                glutSolidCube(0.1);
            glPopMatrix();
            
            // Roda depan kiri
            glTranslatef(0, 0.3, 0.5);
            glPushMatrix();
                // Depan kiri
                glPushMatrix();
                    glTranslatef(-1.0, 0.1, 0.5);
                    glColor3f(0.1, 0.1, 0.1);
                    glutSolidTorus(0.16, 0.26, 20, 20);
                glPopMatrix();
                
                // Velg depan kiri
                glPushMatrix();
                    glTranslatef(-1.0, 0.1, 0.6);
                    glScalef(0.8, 0.8, 0.1);
                    glColor3f(0.6, 0.6, 0.6);
                    glutSolidSphere(0.2, 20, 20);
                glPopMatrix();
                
                // Belakang kiri
                glPushMatrix();
                    glTranslatef(1.8, 0.1, 0.5);
                    glColor3f(0.1, 0.1, 0.1);
                    glutSolidTorus(0.16, 0.26, 20, 20);
                glPopMatrix();
                
                // Velg belakang kiri
                glPushMatrix();
                    glTranslatef(1.8, 0.1, 0.6);
                    glScalef(0.8, 0.8, 0.1);
                    glColor3f(0.6, 0.6, 0.6);
                    glutSolidSphere(0.2, 20, 20);
                glPopMatrix();
            glPopMatrix();
            
            // Roda depan kanan
            glTranslatef(0, 0.0, -1.0);
            glPushMatrix();
                // Depan kanan
                glPushMatrix();
                    glTranslatef(-1.0, 0.1, -0.5);
                    glColor3f(0.1, 0.1, 0.1);
                    glutSolidTorus(0.16, 0.26, 20, 20);
                glPopMatrix();
                
                // Velg depan kanan
                glPushMatrix();
                    glTranslatef(-1.0, 0.1, -0.6);
                    glScalef(0.8, 0.8, 0.1);
                    glColor3f(0.6, 0.6, 0.6);
                    glutSolidSphere(0.2, 20, 20);
                glPopMatrix();
                
                // Belakang kanan
                glPushMatrix();
                    glTranslatef(1.8, 0.1, -0.5);
                    glColor3f(0.1, 0.1, 0.1);
                    glutSolidTorus(0.16, 0.26, 20, 20);
                glPopMatrix();
                
                // Velg belakang kanan
                glPushMatrix();
                    glTranslatef(1.8, 0.1, -0.6);
                    glScalef(0.8, 0.8, 0.1);
                    glColor3f(0.6, 0.6, 0.6);
                    glutSolidSphere(0.2, 20, 20);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void display() {
    if (deltaMove)
        moveMeFlat(deltaMove);
    if (deltaStrafe)
        strafeMeFlat(deltaStrafe);
    if (deltaUp)
        moveMeUp(deltaUp);
    if (deltaAngleX) {
        angleX += deltaAngleX;
        orientMe(angleX);
    }
    if (deltaAngleY) {
        angleY += deltaAngleY;
        orientMe(angleY);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Grid();
    Mobil3D();

    glutSwapBuffers();
    glFlush();
}

void pressKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            deltaAngleY = -0.01f;
            break;
        case GLUT_KEY_RIGHT:
            deltaAngleY = 0.01f;
            break;
        case GLUT_KEY_UP:
            deltaMove = 1;
            break;
        case GLUT_KEY_DOWN:
            deltaMove = -1;
            break;
    }
}

void releaseKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT:
            deltaAngleY = 0.0f;
            break;
        case GLUT_KEY_UP:
        case GLUT_KEY_DOWN:
            deltaMove = 0;
            break;
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
        case 'W':
            deltaMove = 2;
            break;
        case 's':
        case 'S':
            deltaMove = -2;
            break;
        case 'd':
        case 'D':
            deltaStrafe = -2;
            break;
        case 'a':
        case 'A':
            deltaStrafe = 2;
            break;
        case 'q':
        case 'Q':
            deltaUp = 2;
            break;
        case 'e':
        case 'E':
            deltaUp = -2;
            break;
        case 'l':
        case 'L':
            deltaAngleX = 0.005f;
            break;
        case 'j':
        case 'J':
            deltaAngleX = -0.005f;
            break;
        case 'k':
        case 'K':
            deltaAngleY = -0.005f;
            break;
        case 'i':
        case 'I':
            deltaAngleY = 0.005f;
            break;
    }
}

void releaseKey(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
        case 'W':
        case 's':
        case 'S':
            deltaMove = 0;
            break;
        case 'a':
        case 'A':
        case 'd':
        case 'D':
            deltaStrafe = 0;
            break;
        case 'q':
        case 'Q':
        case 'e':
        case 'E':
            deltaUp = 0;
            break;
        case 'i':
        case 'I':
        case 'k':
        case 'K':
            deltaAngleY = 0.0f;
            break;
        case 'j':
        case 'J':
        case 'l':
        case 'L':
            deltaAngleX = 0.0f;
            break;
    }
}

void lighting()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    // Parameter pencahayaan
    GLfloat light_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_position[] = { 0.0f, 20.0f, 10.0f, 1.0f };

    // Parameter material
    GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat high_shininess[] = { 100.0f };

    // Set parameter pencahayaan
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // Set parameter material
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

void init(void) {
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("MOBIL 3D DANDY FAISHAL FAHMI");
    glutIgnoreKeyRepeat(1);
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(releaseKey);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(Reshape);
    lighting();
    init();
    glutMainLoop();
    return 0;
}
