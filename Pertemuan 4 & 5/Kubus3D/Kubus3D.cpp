//  Nama : Dandy Faishal Fahmi
//  NIM  : 24060123140136
//  LAB  : GKV B1

#include <math.h>
#include <GLUT/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

float angle = 0.0, deltaAngle = 0.0, ratio;
float x = 0.0f, y = 2.0f, z = 15.0f;
float lx = 0.0f, ly = 0.0f, lz = -1.0f;
int deltaMove = 0, h, w;
GLuint texture;  // variabel untuk tekstur

// Fungsi untuk mengatur pencahayaan
void lighting() {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    // Parameter pencahayaan
    GLfloat light_ambient[] = { 0.5f, 0.5f, 0.5f, 0.0f };
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

// Fungsi untuk tekstur
GLuint loadTexture(const char *filename) {
    GLuint texID;
    FILE *file;
    unsigned char *data;
    int width, height;
    file = fopen(filename, "rb");
    if (!file) {
        printf("Texture file not found\n");
        return 0;
    }

    // Membaca header BMP
    fseek(file, 18, SEEK_SET);  // Lompat ke lebar dan tinggi gambar
    fread(&width, sizeof(int), 1, file);
    fread(&height, sizeof(int), 1, file);
    fseek(file, 54, SEEK_SET);  // Lompat ke data gambar

    int size = width * height * 3;
    data = (unsigned char*)malloc(size);
    fread(data, size, 1, file);
    fclose(file);

    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    free(data);
    return texID;
}

// Fungsi untuk menggambar grid
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

// Fungsi untuk menggambar kotak kayu dengan tekstur
void KotakKayu() {
    glBindTexture(GL_TEXTURE_2D, texture);
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 10.0f);
        glColor3f(0.5f, 0.2f, 0.0f);

        // Depan
        glPushMatrix();
            glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 0.0f); glVertex3f(-3.0f, -3.0f, 0.0f);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(3.0f, -3.0f, 0.0f);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(3.0f, 3.0f, 0.0f);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(-3.0f, 3.0f, 0.0f);
            glEnd();
        glPopMatrix();

    glPopMatrix();
}

// Fungsi untuk menggerakkan kamera
void moveMeFlat(int i) {
    x = x + i * (lx) * 0.1;
    z = z + i * (lz) * 0.1;
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

// Fungsi untuk mengorientasikan kamera
void orientMe(float ang) {
    lx = sin(ang);
    lz = -cos(ang);
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

void display() {
    if (deltaMove) {
        moveMeFlat(deltaMove);
    }
    if (deltaAngle) {
        angle += deltaAngle;
        orientMe(angle);
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Grid();
    KotakKayu();
    glutSwapBuffers();
    glFlush();
}

void pressKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT: deltaAngle = -0.01f; break;
        case GLUT_KEY_RIGHT: deltaAngle = 0.01f; break;
        case GLUT_KEY_UP: deltaMove = 1; break;
        case GLUT_KEY_DOWN: deltaMove = -1; break;
    }
}

void releaseKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT: deltaAngle = 0.0f; break;
        case GLUT_KEY_UP:
        case GLUT_KEY_DOWN: deltaMove = 0; break;
    }
}

void Reshape(int w1, int h1) {
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

void init() {
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    texture = loadTexture("texture.bmp");
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("3D KUBUS DANDY FAISHAL FAHMI");
    glutIgnoreKeyRepeat(1);
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(Reshape);
    lighting();
    init();
    glutMainLoop();
    return 0;
}