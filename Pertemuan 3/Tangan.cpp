/*
Nama: Dandy Faishal Fahmi
NIM: 24060123140136 / LAB B1
Program: membuat lengan dan jari bergerak
*/

#include <GLUT/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static int shoulder = 45, elbow = 20, finger1 = 0, finger2 = 0, finger3 = 0,
            finger4 = 0, finger5 = 0, finger6 = 0, finger7 = 0, finger8 = 0,
            finger9 = 0, palm = 15, finger10 = 0, finger11 = 0, finger12 = 0,
            finger13 = 0, finger14 = 0, finger15 = 0;

// variable untuk kontrol jari individual
static int index_finger1 = 0, index_finger2 = 0, index_finger3 = 0;
static int middle_finger1 = 0, middle_finger2 = 0, middle_finger3 = 0;
static int ring_finger1 = 0, ring_finger2 = 0, ring_finger3 = 0;
static int pinky_finger1 = 0, pinky_finger2 = 0, pinky_finger3 = 0;
static int thumb_finger1 = 0, thumb_finger2 = 0, thumb_finger3 = 0;

static int mouseX = 0, mouseY = 0;
static bool leftButtonDown = false;
static bool rightButtonDown = false;
static bool middleButtonDown = false;

static float cameraDistance = 5.0f;
static float cameraAngleX = 20.0f;
static float cameraAngleY = 35.0f;
static float cameraAngleZ = 0.0f;
static float zoom = 1.0f;

static int rotationMode = 0;

static float xRotation = 0.0f;
static float yRotation = 0.0f;
static float zRotation = 0.0f;

void init(void) {
    glClearColor(0.100f, 0.50f, 0.81f, 0.0);
    glShadeModel(GL_FLAT);
    
    glEnable(GL_DEPTH_TEST);
    
    glLineWidth(1.5f);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -cameraDistance / zoom);
    
    glRotatef(cameraAngleX, 1.0, 0.0, 0.0);
    glRotatef(cameraAngleY, 0.0, 1.0, 0.0);
    glRotatef(cameraAngleZ, 0.0, 0.0, 1.0);
    
    glPushMatrix();
    
    glRotatef(xRotation, 1.0f, 0.0f, 0.0f);
    glRotatef(yRotation, 0.0f, 1.0f, 0.0f);
    glRotatef(zRotation, 0.0f, 0.0f, 1.0f);
    
    glTranslatef(-2.0, -1.0, 0.0);
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
    glTranslatef(-1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)palm, 0.0, 0.0, 1.0);
    glTranslatef(0.5, 0.0, 0.0);
    glPushMatrix();
    glScalef(1.0, 0.5, 1.5);
    glutWireCube(1.0);
    glPopMatrix();
    
    // Jari telunjuk
    glPushMatrix();
    glTranslatef(0.47, 0.0, 0.6);
    glRotatef((GLfloat)index_finger1, 0.0, 0.0, 1.0);
    glTranslatef(0.2, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.37, 0.3, 0.27);
    glutWireCube(1.0);
    glPopMatrix();

    glTranslatef(0.17, 0.0, 0.0);
    glRotatef((GLfloat)index_finger2, 0.0, 0.0, 1.0);
    glTranslatef(0.2, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.37, 0.3, 0.27);
    glutWireCube(1.0);
    glPopMatrix();
    
    glTranslatef(0.17, 0.0, 0.0);
    glRotatef((GLfloat)index_finger3, 0.0, 0.0, 1.0);
    glTranslatef(0.2, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.37, 0.3, 0.27);
    glutWireCube(1.0);
    glPopMatrix();
    glPopMatrix();

    // Jari tengah
    glPushMatrix();
    glTranslatef(0.56, 0.0, 0.25);
    glRotatef((GLfloat)middle_finger1, 0.0, 0.0, 1.0);
    glTranslatef(0.2, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.5, 0.3, 0.27);
    glutWireCube(1.0);
    glPopMatrix();

    glTranslatef(0.3, 0.0, 0.0);
    glRotatef((GLfloat)middle_finger2, 0.0, 0.0, 1.0);
    glTranslatef(0.2, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.5, 0.3, 0.27);
    glutWireCube(1.0);
    glPopMatrix();
    
    glTranslatef(0.3, 0.0, 0.0);
    glRotatef((GLfloat)middle_finger3, 0.0, 0.0, 1.0);
    glTranslatef(0.2, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.5, 0.3, 0.27);
    glutWireCube(1.0);
    glPopMatrix();
    glPopMatrix();
    
    // Jari manis
    glPushMatrix();
    glTranslatef(0.56, 0.0, -0.1);
    glRotatef((GLfloat)ring_finger1, 0.0, 0.0, 1.0);
    glTranslatef(0.25, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.58, 0.3, 0.27);
    glutWireCube(1.0);
    glPopMatrix();

    glTranslatef(0.34, 0.0, 0.0);
    glRotatef((GLfloat)ring_finger2, 0.0, 0.0, 1.0);
    glTranslatef(0.25, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.58, 0.3, 0.27);
    glutWireCube(1.0);
    glPopMatrix();
    
    glTranslatef(0.34, 0.0, 0.0);
    glRotatef((GLfloat)ring_finger3, 0.0, 0.0, 1.0);
    glTranslatef(0.25, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.58, 0.3, 0.27);
    glutWireCube(1.0);
    glPopMatrix();
    glPopMatrix();
    
    // Jari kelingking
    glPushMatrix();
    glTranslatef(0.5, 0.0, -0.45);
    glRotatef((GLfloat)pinky_finger1, 0.0, 0.0, 1.0);
    glTranslatef(0.25, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.5, 0.3, 0.27);
    glutWireCube(1.0);
    glPopMatrix();

    glTranslatef(0.25, 0.0, 0.0);
    glRotatef((GLfloat)pinky_finger2, 0.0, 0.0, 1.0);
    glTranslatef(0.25, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.5, 0.3, 0.27);
    glutWireCube(1.0);
    glPopMatrix();
    
    glTranslatef(0.25, 0.0, 0.0);
    glRotatef((GLfloat)pinky_finger3, 0.0, 0.0, 1.0);
    glTranslatef(0.25, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.5, 0.3, 0.27);
    glutWireCube(1.0);
    glPopMatrix();
    glPopMatrix();
    
    // Jempol
    glPushMatrix();
    glTranslatef(-0.1, 0.0, -0.88);
    glRotatef((GLfloat)thumb_finger1, 0.0, 0.0, 1.0);
    glTranslatef(0.25, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.37, 0.3, 0.27);
    glutWireCube(1.0);
    glPopMatrix();

    glTranslatef(0.13, 0.0, 0.0);
    glRotatef((GLfloat)thumb_finger2, 0.0, 0.0, 1.0);
    glTranslatef(0.25, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.37, 0.3, 0.27);
    glutWireCube(1.0);
    glPopMatrix();
    
    glTranslatef(0.13, 0.0, 0.0);
    glRotatef((GLfloat)thumb_finger3, 0.0, 0.0, 1.0);
    glTranslatef(0.25, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.37, 0.3, 0.27);
    glutWireCube(1.0);
    glPopMatrix();
    glPopMatrix();
    
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat)w/(GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

void mouse(int button, int state, int x, int y) {
    mouseX = x;
    mouseY = y;
    
    if (button == GLUT_LEFT_BUTTON) {
        leftButtonDown = (state == GLUT_DOWN);
    }
    else if (button == GLUT_RIGHT_BUTTON) {
        rightButtonDown = (state == GLUT_DOWN);
    }
    else if (button == GLUT_MIDDLE_BUTTON) {
        middleButtonDown = (state == GLUT_DOWN);
    }
    else if (button == 3) {
        zoom += 0.1f;
        if (zoom > 3.0f) zoom = 3.0f;
        glutPostRedisplay();
    }
    else if (button == 4) {
        zoom -= 0.1f;
        if (zoom < 0.1f) zoom = 0.1f;
        glutPostRedisplay();
    }
}

void motion(int x, int y) {
    int deltaX = x - mouseX;
    int deltaY = y - mouseY;
    
    mouseX = x;
    mouseY = y;
    
    int modifiers = glutGetModifiers();
    
    if (leftButtonDown) {
        if (modifiers & GLUT_ACTIVE_SHIFT) {
            elbow += deltaX / 2;
            if (elbow > 90) elbow = 90;
            if (elbow < -90) elbow = -90;
        }
        else if (modifiers & GLUT_ACTIVE_CTRL) {
            palm += deltaX / 2;
            if (palm > 90) palm = 90;
            if (palm < -90) palm = -90;
        }
        else {
            shoulder += deltaX / 2;
            shoulder = shoulder % 360;
        }
    }
    
    if (rightButtonDown) {
        if (modifiers & GLUT_ACTIVE_SHIFT) {
            cameraAngleZ += deltaX / 2.0f;
            if (cameraAngleZ > 360.0f) cameraAngleZ -= 360.0f;
            if (cameraAngleZ < 0.0f) cameraAngleZ += 360.0f;
        }
        else {
            cameraAngleY += deltaX / 2.0f;
            cameraAngleX += deltaY / 2.0f;
            
            if (cameraAngleY > 360.0f) cameraAngleY -= 360.0f;
            if (cameraAngleY < 0.0f) cameraAngleY += 360.0f;
            if (cameraAngleX > 360.0f) cameraAngleX -= 360.0f;
            if (cameraAngleX < 0.0f) cameraAngleX += 360.0f;
        }
    }
    
    if (middleButtonDown) {
        if (modifiers & GLUT_ACTIVE_SHIFT) {
            xRotation += deltaY / 2.0f;
            yRotation += deltaX / 2.0f;
            
            if (xRotation > 360.0f) xRotation -= 360.0f;
            if (xRotation < 0.0f) xRotation += 360.0f;
            if (yRotation > 360.0f) yRotation -= 360.0f;
            if (yRotation < 0.0f) yRotation += 360.0f;
        }
        else if (modifiers & GLUT_ACTIVE_CTRL) {
            zRotation += deltaX / 2.0f;
            
            if (zRotation > 360.0f) zRotation -= 360.0f;
            if (zRotation < 0.0f) zRotation += 360.0f;
        }
        else {
            zoom += deltaY * 0.01f;
            if (zoom < 0.1f) zoom = 0.1f;
            if (zoom > 3.0f) zoom = 3.0f;
        }
    }
    
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            yRotation -= 5.0f;
            if (yRotation < 0.0f) yRotation += 360.0f;
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            yRotation += 5.0f;
            if (yRotation >= 360.0f) yRotation -= 360.0f;
            glutPostRedisplay();
            break;
        case GLUT_KEY_UP:
            xRotation -= 5.0f;
            if (xRotation < 0.0f) xRotation += 360.0f;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            xRotation += 5.0f;
            if (xRotation >= 360.0f) xRotation -= 360.0f;
            glutPostRedisplay();
            break;
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'p':
            if (palm < 90) palm = (palm + 5);
            glutPostRedisplay();
            break;
        case 'P':
            if (palm > -90) palm = (palm - 5);
            glutPostRedisplay();
            break;
            
        // Kontrol untuk jari telunjuk
        case '1':
            if (index_finger1 < 90) index_finger1 = (index_finger1 + 5);
            glutPostRedisplay();
            break;
        case '!':
            if (index_finger1 > 0) index_finger1 = (index_finger1 - 5);
            glutPostRedisplay();
            break;
        case '2':
            if (index_finger2 < 90) index_finger2 = (index_finger2 + 5);
            glutPostRedisplay();
            break;
        case '@':
            if (index_finger2 > 0) index_finger2 = (index_finger2 - 5);
            glutPostRedisplay();
            break;
        case '3':
            if (index_finger3 < 90) index_finger3 = (index_finger3 + 5);
            glutPostRedisplay();
            break;
        case '#':
            if (index_finger3 > 0) index_finger3 = (index_finger3 - 5);
            glutPostRedisplay();
            break;
            
        // Kontrol untuk jari tengah
        case '4':
            if (middle_finger1 < 90) middle_finger1 = (middle_finger1 + 5);
            glutPostRedisplay();
            break;
        case '$':
            if (middle_finger1 > 0) middle_finger1 = (middle_finger1 - 5);
            glutPostRedisplay();
            break;
        case '5':
            if (middle_finger2 < 90) middle_finger2 = (middle_finger2 + 5);
            glutPostRedisplay();
            break;
        case '%':
            if (middle_finger2 > 0) middle_finger2 = (middle_finger2 - 5);
            glutPostRedisplay();
            break;
        case '6':
            if (middle_finger3 < 90) middle_finger3 = (middle_finger3 + 5);
            glutPostRedisplay();
            break;
        case '^':
            if (middle_finger3 > 0) middle_finger3 = (middle_finger3 - 5);
            glutPostRedisplay();
            break;
            
        // Kontrol untuk jari manis
        case 'q':
            if (ring_finger1 < 90) ring_finger1 = (ring_finger1 + 5);
            glutPostRedisplay();
            break;
        case 'Q':
            if (ring_finger1 > 0) ring_finger1 = (ring_finger1 - 5);
            glutPostRedisplay();
            break;
        case 'w':
            if (ring_finger2 < 90) ring_finger2 = (ring_finger2 + 5);
            glutPostRedisplay();
            break;
        case 'W':
            if (ring_finger2 > 0) ring_finger2 = (ring_finger2 - 5);
            glutPostRedisplay();
            break;
        case 'e':
            if (ring_finger3 < 90) ring_finger3 = (ring_finger3 + 5);
            glutPostRedisplay();
            break;
        case 'E':
            if (ring_finger3 > 0) ring_finger3 = (ring_finger3 - 5);
            glutPostRedisplay();
            break;
            
        // Kontrol untuk jari kelingking
        case 'a':
            if (pinky_finger1 < 90) pinky_finger1 = (pinky_finger1 + 5);
            glutPostRedisplay();
            break;
        case 'A':
            if (pinky_finger1 > 0) pinky_finger1 = (pinky_finger1 - 5);
            glutPostRedisplay();
            break;
        case 's':
            if (pinky_finger2 < 90) pinky_finger2 = (pinky_finger2 + 5);
            glutPostRedisplay();
            break;
        case 'S':
            if (pinky_finger2 > 0) pinky_finger2 = (pinky_finger2 - 5);
            glutPostRedisplay();
            break;
        case 'd':
            if (pinky_finger3 < 90) pinky_finger3 = (pinky_finger3 + 5);
            glutPostRedisplay();
            break;
        case 'D':
            if (pinky_finger3 > 0) pinky_finger3 = (pinky_finger3 - 5);
            glutPostRedisplay();
            break;
            
        // Kontrol untuk jempol
        case 'z':
            if (thumb_finger1 < 90) thumb_finger1 = (thumb_finger1 + 5);
            glutPostRedisplay();
            break;
        case 'Z':
            if (thumb_finger1 > 0) thumb_finger1 = (thumb_finger1 - 5);
            glutPostRedisplay();
            break;
        case 'x':
            if (thumb_finger2 < 90) thumb_finger2 = (thumb_finger2 + 5);
            glutPostRedisplay();
            break;
        case 'X':
            if (thumb_finger2 > 0) thumb_finger2 = (thumb_finger2 - 5);
            glutPostRedisplay();
            break;
        case 'c':
            if (thumb_finger3 < 90) thumb_finger3 = (thumb_finger3 + 5);
            glutPostRedisplay();
            break;
        case 'C':
            if (thumb_finger3 > 0) thumb_finger3 = (thumb_finger3 - 5);
            glutPostRedisplay();
            break;
        
        // Gerakan semua jari sekaligus
        case 'f':
            // Reset semua jari ke posisi lurus
            index_finger1 = index_finger2 = index_finger3 = 0;
            middle_finger1 = middle_finger2 = middle_finger3 = 0;
            ring_finger1 = ring_finger2 = ring_finger3 = 0;
            pinky_finger1 = pinky_finger2 = pinky_finger3 = 0;
            thumb_finger1 = thumb_finger2 = thumb_finger3 = 0;
            glutPostRedisplay();
            break;
        case 'g':
            // Tekuk semua jari (bentuk genggaman)
            index_finger1 = index_finger2 = index_finger3 = 70;
            middle_finger1 = middle_finger2 = middle_finger3 = 70;
            ring_finger1 = ring_finger2 = ring_finger3 = 70;
            pinky_finger1 = pinky_finger2 = pinky_finger3 = 70;
            thumb_finger1 = thumb_finger2 = thumb_finger3 = 70;
            glutPostRedisplay();
            break;
        
        case 'v':
            zRotation += 5.0f;
            if (zRotation >= 360.0f) zRotation -= 360.0f;
            glutPostRedisplay();
            break;
        case 'V':
            zRotation -= 5.0f;
            if (zRotation < 0.0f) zRotation += 360.0f;
            glutPostRedisplay();
            break;
            
        case 'r':
            cameraAngleX = 20.0f;
            cameraAngleY = 35.0f;
            cameraAngleZ = 0.0f;
            zoom = 1.0f;
            shoulder = 45;
            elbow = 20;
            palm = 15;
            xRotation = 0.0f;
            yRotation = 0.0f;
            zRotation = 0.0f;
            
            // Reset semua jari ke posisi awal
            index_finger1 = index_finger2 = index_finger3 = 0;
            middle_finger1 = middle_finger2 = middle_finger3 = 0;
            ring_finger1 = ring_finger2 = ring_finger3 = 0;
            pinky_finger1 = pinky_finger2 = pinky_finger3 = 0;
            thumb_finger1 = thumb_finger2 = thumb_finger3 = 0;
            
            glutPostRedisplay();
            break;
            
        case 'm':
            rotationMode = (rotationMode + 1) % 3;
            printf("Rotation mode: %s\n",
                rotationMode == 0 ? "Shoulder" :
                rotationMode == 1 ? "Elbow" : "Palm");
            break;
            
        case 27:
            exit(0);
            break;
        default:
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DANDY FAISHAL FAHMI - 24060123140136 - GKV LAB B1:\n");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    
    glutMainLoop();
    return 0;
}
