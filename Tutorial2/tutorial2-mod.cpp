#include <Windows.h>
#include <GL/GL.h>
#include <GL/glut.h> 
#include <Math.h>     // Needed for sin, cos
#define PI 3.14159265f

// Global variables
char title[] = "Bouncing Ball (2D)";  // Windowed mode's title
int windowWidth = 640;     // Windowed mode's width
int windowHeight = 480;     // Windowed mode's height
int windowPosX = 50;      // Windowed mode's top-left corner x
int windowPosY = 50;      // Windowed mode's top-left corner y

GLfloat ballRadius = 0.5f;   // Radius of the bouncing ball
GLfloat ballX = 0.0f;         // Ball's center (x, y) position
GLfloat ballY = 0.0f;
GLfloat ballXMax, ballXMin, ballYMax, ballYMin; // Ball's center (x, y) bounds
GLfloat xSpeed = 0.02f;      // Ball's speed in x and y directions
GLfloat ySpeed = 0.007f;
int refreshMillis = 30;      // Refresh period in milliseconds

//added: spinning 
GLfloat spin = 0.0f;

//added for changing color as touch edge:
bool touchEdge = false;
GLfloat red = 0.0f;
GLfloat green = 0.0f;
GLfloat blue = 1.0f;

//added: changes in radius and direction
GLfloat ballRadiusChange = 0.01f;
GLfloat xSpeedChange = 0.01f;
GLfloat ySpeedChange = 0.01f;

bool fullScreenMode = true;//Full screen mode boolean variable 

// Projection clipping area
GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;

/* Initialize OpenGL Graphics */
void initGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background (clear) color to black
    glEnable(GL_DEPTH_TEST);
    /*  Lighting    */

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);


}

/* Callback handler for window re-paint event */
void display() {
    GLfloat light0_position[] = { 0.5, 0, 0.5, 1.0 }; //Directional Light source
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);//set light before modelview transformation(Translate, Rotatef) to move light 


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear the color buffer
    glMatrixMode(GL_MODELVIEW);    // To operate on the model-view matrix
    glLoadIdentity();              // Reset model-view matrix

    //do any camera stuff you want
    glPushMatrix();
    
    //update spin
    spin += 2.0f;
    if (spin > 360.0)
        spin = 0;

    glTranslatef(ballX, ballY, 0.0f);  // Translate to (xPos, yPos)
    
    //rotate
    glRotatef(spin, 0, 1, 0);

    // Use triangular segments to form a circle
    //MID-TERM: CHANGE CIRCLE TO A ROTATING SQUARE 

    //implement color changing

    if (touchEdge)
    {
        if (blue >= 1.0f)//FLoat comparison
        {
            blue = 0.0f;
            red = 1.0f;
            touchEdge = false;
        }
        else if (red >= 1.0f)
        {
            red = 0.0f;
            green = 1.0f;
            touchEdge = false;

        }
        else if (green >= 1.0f)
        {
            green = 0.0f;
            blue = 1.0f;
            touchEdge = false;

        }

    }
    glEnable(GL_COLOR_MATERIAL);

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glColor3f(red, green, blue);

    //glDisable(GL_COLOR_MATERIAL);

    glColor3f(red, green, blue);  // Set foreground color: Blue
    glutSolidTorus(ballRadius-0.3, 0.3, 30, 30);
    //glBegin(GL_TRIANGLE_FAN);
    //glColor3f(red, green, blue);  // Set foreground color: Blue
    //glVertex2f(0.0f, 0.0f);       // Set Center of circle
    //int numSegments = 4;
    //GLfloat angle;
    //for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
    //    angle = i * 2.0f * PI / numSegments;  // 360 deg for all segments
    //    glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
    //}


    // Animation Control - compute the location for the next refresh
    ballX += xSpeed;
    ballY += ySpeed;
    // Check if the ball exceeds the edges
    if (ballX > ballXMax) {
        ballX = ballXMax;
        xSpeed = -xSpeed;
        touchEdge = true;
    }
    else if (ballX < ballXMin) {
        ballX = ballXMin;
        xSpeed = -xSpeed;
        touchEdge = true;

    }
    if (ballY > ballYMax) {
        ballY = ballYMax;
        ySpeed = -ySpeed;
        touchEdge = true;

    }
    else if (ballY < ballYMin) {
        ballY = ballYMin;
        ySpeed = -ySpeed;
        touchEdge = true;

    }
    glPopMatrix();
    
    glEnd();

    

    glutSwapBuffers();  // Swap front and back buffers (of double buffered mode)
}

/* Call back when the windows is re-sized */
void reshape(GLsizei width, GLsizei height) {
    // Compute aspect ratio of the new window

    //Danie comment:
          //What is aspect ratio ?
          //what does this viewport function do? 

    if (height == 0) height = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // Set the aspect ratio of the clipping area to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset the projection matrix
    if (width >= height) {
        clipAreaXLeft = -1.0 * aspect;
        clipAreaXRight = 1.0 * aspect;
        clipAreaYBottom = -1.0;
        clipAreaYTop = 1.0;
    }
    else {
        clipAreaXLeft = -1.0;
        clipAreaXRight = 1.0;
        clipAreaYBottom = -1.0 / aspect;
        clipAreaYTop = 1.0 / aspect;
    }
    gluOrtho2D(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
    ballXMin = clipAreaXLeft + ballRadius;
    ballXMax = clipAreaXRight - ballRadius;
    ballYMin = clipAreaYBottom + ballRadius;
    ballYMax = clipAreaYTop - ballRadius;
}

/* Called back when the timer expired */
void Timer(int value) {
    glutPostRedisplay();    // Post a paint request to activate display()
    glutTimerFunc(refreshMillis, Timer, 0); // subsequent timer call at milliseconds
}


/*Callback handler for special key event*/
void specialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_F1:
         //if key is F1, set full screen mode to window mode
        fullScreenMode = !fullScreenMode;
        //if windowed Mode->fullScreenMode, save positions X Y W and H of ball
        //and switch to full screen
        if (fullScreenMode)
        {
            
            windowPosX = glutGet(GLUT_WINDOW_X);//save PosX of ball 
            windowPosY = glutGet(GLUT_WINDOW_X);//save PosY of ball 
            windowWidth = glutGet(GLUT_WINDOW_X);//save PosW of ball 
            windowHeight = glutGet(GLUT_WINDOW_X);//save PosH of ball
            glutFullScreen();

        }
        else //fullscreen -> window, call glutReshapeWindow and glutPositionWindow to 
            //position ball in window mode
        {
            glutReshapeWindow(windowWidth, windowHeight);
            glutPositionWindow(windowPosX, windowPosX);//position of the top left corner
        }
        break;
    //left-right  arrow keys increase/decrease the horrizontal speed
    //up/down arrow keys increase/decrease the vertical speed
    //page up down increase and decrease ball's radius
    case GLUT_KEY_LEFT://increase horizontal speed //Xmax
        xSpeed += xSpeedChange;
        //whenever xSpeed hit wall -> it changes sign -> xSpeedChange also need to align the sign
        if (xSpeed < 0)
        {
            xSpeed -= xSpeedChange;
        }
        break;
    case GLUT_KEY_RIGHT://Xmin
        xSpeed -= xSpeedChange;
        //whenever xSpeed hit wall -> it changes sign -> xSpeedChange also need to align the sign
        if (xSpeed < 0)
        {
            xSpeed += xSpeedChange;
        }
        break;
        //SAME LOGIC AS XSPEEDCHANGE
    case GLUT_KEY_UP://increase vertical speed
        ySpeed += ySpeedChange;
        if (ySpeed < 0)
        {
            ySpeed -= ySpeedChange;
        }
        break;
    case GLUT_KEY_DOWN:
        ySpeed -= ySpeedChange;
        if (ySpeed < 0)
        {
            ySpeed += ySpeedChange;
        }
        break;
    case GLUT_KEY_PAGE_UP:
        ballRadius += ballRadiusChange;
        ballXMin = clipAreaXLeft + ballRadius;
        ballXMax = clipAreaXRight - ballRadius;
        ballYMin = clipAreaYBottom + ballRadius;
        ballYMax = clipAreaYTop - ballRadius;
        break;
    case GLUT_KEY_PAGE_DOWN:
        ballRadius -= ballRadiusChange;
        ballXMin = clipAreaXLeft + ballRadius;
        ballXMax = clipAreaXRight - ballRadius;
        ballYMin = clipAreaYBottom + ballRadius;
        ballYMax = clipAreaYTop - ballRadius;
        break;

    }
}


/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
    glutInit(&argc, argv);            // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
    glutInitWindowSize(windowWidth, windowHeight);  // Initial window width and height
    glutInitWindowPosition(windowPosX, windowPosY); // Initial window top-left corner (x, y)
    glutCreateWindow(title);      // Create window with given title
    glutDisplayFunc(display);     // Register callback handler for window re-paint
    glutReshapeFunc(reshape);     // Register callback handler for window re-shape

    //add glutSpecialFUunc(specialKeys)
    glutSpecialFunc(specialKeys);

    //add full screen 
    glutFullScreen(); //QUESTION: WHY IS glutFullScreen being called x2, once in specialKeys fn & once in main?

    glutTimerFunc(0, Timer, 0);   // First timer call immediately
    initGL();                     // Our own OpenGL initialization
    glutMainLoop();               // Enter event-processing loop
    return 0;
}