/**
 * Demonstrate the different configurations of face culling and
 * the use of depth sorting (z-buffer).
 *
 * Author: Mihalis Tsoukalos
 * Contributions: Fernando Bevilacqua
 */

#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>
// Global variables to control the rotation of the
// stripped cube according to user input.
GLfloat rX = -25.0;
GLfloat rY = 25.0;
int nOrder = 0;

void strippedCube(int eita)
{
    // The coordinates for the vertices of the cube
    GLfloat x = eita*0.3f;
    GLfloat y = eita*0.3f;
    GLfloat z = eita*0.3f;

    // BACK face
    // glColor3f(0.4f, 0.3f, 0.5f);
    glBegin(GL_TRIANGLES);
        glVertex3f(x, y, z);
        glVertex3f(-x, y, z);
        glVertex3f(x, -y, z);
    glEnd();

    // glColor3f(0.45f, 0.35f, 0.55f);
    glBegin(GL_TRIANGLES);
        glVertex3f(-x, -y, z);
        glVertex3f(x, -y, z);
        glVertex3f(-x, y, z);
    glEnd();

    // FRONT face
    // glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_TRIANGLES);
        glVertex3f(x, y, -z);
        glVertex3f(x, -y, -z);
        glVertex3f(-x, y, -z);
    glEnd();

    // glColor3f(0.35f, 0.35f, 0.35f);
    glBegin(GL_TRIANGLES);
        glVertex3f(-x, -y, -z);
        glVertex3f(-x, y, -z);
        glVertex3f(x, -y, -z);
    glEnd();

    // LEFT face
    // glColor3f(0.3f, 0.5f, 0.6f);
    glBegin(GL_TRIANGLES);
        glVertex3f(-x, -y, -z);
        glVertex3f(-x, -y, z);
        glVertex3f(-x, y, -z);
    glEnd();

    // glColor3f(0.35f, 0.55f, 0.65f);
    glBegin(GL_TRIANGLES);
        glVertex3f(-x, y, z);
        glVertex3f(-x, y, -z);
        glVertex3f(-x, -y, z);
    glEnd();

    // RIGHT face
    // glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_TRIANGLES);
        glVertex3f(x, y, z);
        glVertex3f(x, -y, z);
        glVertex3f(x, y, -z);
    glEnd();

    // glColor3f(0.25f, 0.25f, 0.25f);
    glBegin(GL_TRIANGLES);
        glVertex3f(x, -y, -z);
        glVertex3f(x, y, -z);
        glVertex3f(x, -y, z);
    glEnd();

    // BOTTOM face
    // glColor3f(0.4f, 0.0f, 0.4f);
    glBegin(GL_TRIANGLES);
        glVertex3f(-x, -y, -z);
        glVertex3f(x, -y, z);
        glVertex3f(-x, -y, z);
    glEnd();

    // glColor3f(0.45f, 0.05f, 0.45f);
    glBegin(GL_TRIANGLES);
        glVertex3f(x, -y, z);
        glVertex3f(-x, -y, -z);
        glVertex3f(x, -y, -z);
    glEnd();

    // TOP face
    // glColor3f(0.9f, 0.0f, 0.9f);
    glBegin(GL_TRIANGLES);
        glVertex3f(-x, y, -z);
        glVertex3f(-x, y, z);
        glVertex3f(x, y, z);
    glEnd();

    // glColor3f(0.85f, 0.05f, 0.85f);
    glBegin(GL_TRIANGLES);
        glVertex3f(x, y, z);
        glVertex3f(x, y, -z);
        glVertex3f(-x, y, -z);
    glEnd();
}

void display()
{
    // Set the background color
    glClearColor(0.4f, 0.4f, 0.4f, 0.0f);
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (nOrder == 1){
        glFrontFace(GL_CCW);
    }else{
        glFrontFace(GL_CW);
    }
    // Reset transformations
    glTranslatef(.0f, .0f,5.0f);
    glLoadIdentity();

    // Rotate according to user input (rX and rY)
    glRotatef(rX, 1.0f, 0.0f, 0.0f);
    glRotatef(rY, 0.0f, 1.0f, 0.0f);

	glPushMatrix();
    	glColor3f(0.1f, 0.1f, 0.1f);
		glTranslatef(.0f, -.30f, .0f);
		glScalef(20.0f,0.01f,20.0f);
		strippedCube(1);
	glPopMatrix();

    // Render a cube without the top and front faces.

	glPushMatrix();
    	glColor3f(0.6f, 0.6f, 0.6f);
    	strippedCube(1.5);
	glPopMatrix();

	glPushMatrix();
    	glColor3f(0.5f, 0.3f, 0.3f);
		glTranslatef(.5f, .0f, 1.2f);
		strippedCube(1.5);
	glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void keyboard(int key, int x, int y)
{
    if (key == GLUT_KEY_RIGHT) {
        rY += 5;
    } else if (key == GLUT_KEY_LEFT) {
        rY -= 5;
    } else if (key == GLUT_KEY_DOWN) {
        rX -= 5;
    } else if (key == GLUT_KEY_UP) {
        rX += 5;
    }
         
    // Request display update
    glutPostRedisplay();
}

void keyb(unsigned char key, int x, int y)
{
    if (key == 'b') {
        nOrder = 0;
    } else if (key == 'a') {
        nOrder = 1;
    }
         
    // Request display update
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    // Initialize GLUT and process user parameters
    glutInit(&argc, argv);

    // Request double buffered true color window with Z-buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);

    // Create window
    glutCreateWindow("Culling and z-buffer");

    // Enable Z-buffer depth test
    glEnable(GL_DEPTH_TEST);

    // Enable face culling. When this is enabled, you can use
    // the functions glCullFace() and glFrontFace() to specify
    // how faces should be culled.
    glEnable(GL_CULL_FACE);

    // Callback functions
    glutDisplayFunc(display);
    glutSpecialFunc(keyboard);
    glutKeyboardFunc(keyb);
    glutIdleFunc(display);

    // Pass control to GLUT for events
    glutMainLoop();

    return 0;
}
