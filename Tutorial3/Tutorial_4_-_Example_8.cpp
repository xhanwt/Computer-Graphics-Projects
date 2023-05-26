/*an interactive program that uses glColorMaterial() 
to change material parameters. 
Pressing each of the three mouse buttons changes the color of the diffuse reflection.*/
#include <Windows.h>
#include <GL/GL.h>
#include <GL/glut.h>
#include <cmath>

GLfloat dX = 0.0;
GLfloat dY = 0.0;


GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };//default values for global ambient

//initialize material's ambient, specular, shininess & diffuse
GLfloat ambientAndDiffuseMaterial[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat shininess[] = { 0.0 }; //shininess is a vector of one element
GLfloat specularMaterial[] = { 1, 1, 1, 1 };
GLfloat emissionMaterial[] = { 0.0, 0.0, 0.0, 0 };


//declare vector for ambient, diffuse, specular, shininess and emission reflectance params



void init(void)
{
    //GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);//Global Ambient light

    /*Material */

    //glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ambientAndDiffuseMaterial);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, specularMaterial);
    //glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    //glMaterialfv(GL_FRONT, GL_EMISSION, emissionMaterial);

        //enable glColorMaterial;
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glColor4fv(ambientAndDiffuseMaterial);

    glColorMaterial(GL_FRONT, GL_SPECULAR);
    glColor4fv(specularMaterial);


    glColorMaterial(GL_FRONT, GL_SHININESS);
    glColor4fv(shininess);

    glColorMaterial(GL_FRONT, GL_EMISSION); //Drive Emission compoent of glMaterial using glColor()
    //from this point performing a glColor commd has the exact same effect as calling glMaterial(GL_FRONT, GL_EMISSION, colors);
    glColor4fv(emissionMaterial);

    glEnable(GL_COLOR_MATERIAL);

    /*  Lighting    */
}


//Speculation: glMaterialfv() gotta be called in display() so that param for colors can be updated

void display(void)
{
    GLfloat light0_position[] = { dX, dY, 1.5, 1.0 }; //Directional Light source
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glTranslatef(dX, dY,1.5);
    //glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ambientAndDiffuseMaterial);

    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glPopMatrix();

    glutSolidSphere(1.0, 20, 16);
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-1.5, 1.5, -1.5 * (GLfloat)h / (GLfloat)w,
            1.5 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
    else
        glOrtho(-1.5 * (GLfloat)w / (GLfloat)h,
            1.5 * (GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
    switch (button) {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN) {       /*  change red  */
            ambientAndDiffuseMaterial[0] += 0.1;
            if (ambientAndDiffuseMaterial[0] > 1.0) //diffuseMaterial is capped at  1 1 1
                ambientAndDiffuseMaterial[0] = 0.0;
            glColor4fv(ambientAndDiffuseMaterial);
            glutPostRedisplay();
        }
        break;
    case GLUT_RIGHT_BUTTON: /*  reset global ambient to default     */
        if (state == GLUT_DOWN) {      /*  change blue  */
            ambientAndDiffuseMaterial[2] += 0.1;
            if (ambientAndDiffuseMaterial[2] > 1.0)
                ambientAndDiffuseMaterial[2] = 0.0;
            glColor4fv(ambientAndDiffuseMaterial);
            glutPostRedisplay();
        }
        break;
    default:
        break;
    }
}

//1- Alter Global Ambient Light using Special Keys
void specialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        lmodel_ambient[0] += 0.1;
        if (lmodel_ambient[0] > 1.0) //diffuseMaterial is capped at  1 1 1
            lmodel_ambient[0] = 0.0;
        glColor4fv(lmodel_ambient);
        glutPostRedisplay();
        break;
                
    case GLUT_KEY_DOWN:
        lmodel_ambient[1] += 0.1;
        if (lmodel_ambient[1] > 1.0)
            lmodel_ambient[1] = 0.0;
        glColor4fv(lmodel_ambient);
        glutPostRedisplay();
        break;
    case GLUT_KEY_LEFT:
        lmodel_ambient[2] += 0.1;
        if (lmodel_ambient[1] > 1.0)
            lmodel_ambient[1] = 0.0;
        glColor4fv(lmodel_ambient);
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        lmodel_ambient[0] = 0.2;
        lmodel_ambient[1] = 0.2;
        lmodel_ambient[2] = 0.2;
        lmodel_ambient[3] = 1.0;
        glColor4fv(lmodel_ambient);
        glutPostRedisplay();

        /*  lesson: when color isnt changing remember glutPostRedisplay() */
        break;


        //Add this after calling glColorMaterial(GL_FRONT, GL_EMISSION);
        //Otherwise, you will need to add glMaterialfv(GL_FRONT, GL_EMISSION, emissionMaterial) in display to be redrawn


    case GLUT_KEY_PAGE_DOWN: /* adjust emission  */
        dX -= 0.5; //move light from right to left
        dY -= 0.5;
        glutPostRedisplay();        
        break;
    case GLUT_KEY_PAGE_UP: /* adjust emission  */
        dX += 0.5; //move light from right to left
        dY += 0.5;
        glutPostRedisplay();
        break;
    default:
        break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 0;
}