#include <Windows.h>
#include <GL/GL.h>
#include <GL/glut.h>


GLfloat diffuseMaterial[4] = { 0.5, 0.5, 0.5, 1.0 };

void init(void)
{

    GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };

    GLfloat ambientAndDiffuseMaterial[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat shininess[] = { 0.0 };
    GLfloat specularMaterial[] = { 1, 1, 1, 1 };
    GLfloat emissionMaterial[] = { 0.0, 0.0, 0.0, 0 };

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);


    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient); // Global Ambient Light

    // glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ambientAndDiffuseMaterial);
    // glMaterialfv(GL_FRONT, GL_SPECULAR, specularMaterial);
    // glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    // glMaterialfv(GL_FRONT, GL_EMISSION, emissionMaterial);


  

    glColorMaterial(GL_FRONT, GL_SPECULAR);
    glColor4fv(specularMaterial);

    glColorMaterial(GL_FRONT, GL_SHININESS);
    glColor4fv(shininess);

    glColorMaterial(GL_FRONT, GL_EMISSION);
    glColor4fv(emissionMaterial);
    
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glColor4fv(ambientAndDiffuseMaterial);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glColorMaterial(GL_FRONT, GL_DIFFUSE);
     glEnable(GL_COLOR_MATERIAL);

}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
            diffuseMaterial[0] += 0.1;
            if (diffuseMaterial[0] > 1.0)
                diffuseMaterial[0] = 0.0;
            glColor4fv(diffuseMaterial);
            glutPostRedisplay();
        }
        break;
    case GLUT_MIDDLE_BUTTON:
        if (state == GLUT_DOWN) {       /*  change green  */
            diffuseMaterial[1] += 0.1;
            if (diffuseMaterial[1] > 1.0)
                diffuseMaterial[1] = 0.0;
            glColor4fv(diffuseMaterial);
            glutPostRedisplay();
        }
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN) {      /*  change blue  */
            diffuseMaterial[2] += 0.1;
            if (diffuseMaterial[2] > 1.0)
                diffuseMaterial[2] = 0.0;
            glColor4fv(diffuseMaterial);
            glutPostRedisplay();
        }
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
    glutMainLoop();
    return 0;
}
