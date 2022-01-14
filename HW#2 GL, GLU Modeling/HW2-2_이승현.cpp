/*******************************************************************************************************/
/*                                           HW#2-2. GLU Modeling                                      */
/*  �ۼ��� : �̽���                                                             ��¥ : 2021�� 9�� 29�� */
/*                                                                                                     */
/* ���� ���� :                                                                                         */
/*  Display List�� ����Ͽ� 4���� 3D Primitive(Sphere, Cylinder, Disk, PartialDisk)�� �����ϰ�,        */
/*  ������ Primitive�� �پ��� Draw Style�� �����Ѵ�.                                                   */
/* ��� :                                                                                              */
/* 1. 3D Primitive�� ������ �� Display List�� ����Ͽ� ���α׷��� �ӵ��� ����Ų��.                   */
/* 2. gluSphere �Լ��� ����Ͽ� �������� 1.5�� ���� �׸���.                                            */
/* 3. gluCylinder �Լ��� ����Ͽ� �ظ��� 1.5�̰� ���̰� 2.0�� ������� �׸���.                         */
/* 4. gluDisk �Լ��� ����Ͽ� ���� ���� �������� 0.5, �ٱ��� ���� �������� 1.5�� disk�� �׸���.        */
/* 5. gluPartialDisk �Լ��� ����Ͽ� 4�� Disk�� 90����ŭ�� �ش��ϴ� partial disk�� �׸���.             */
/* 6. ������ ������ ���Ͽ� �پ��� DrawStyle(GLU_FILL, GLU_LINE, GLU_SILHOUETTE, GLU_POINT)�� �����Ѵ�. */
/* 7. MyInit �Լ����� ���� ǥ�鿡 ���� ������ �Ѵ�.                                                    */
/* 8. MyReshape �Լ����� ������ ���ú����� ��Ⱦ�� ��ġ���� �ְ� ������ �ذ��Ѵ�.                     */
/*******************************************************************************************************/

// * main �Լ����� My___DisplayList�� �ּ��� ����� ���� �ٸ� ������ ȭ�鿡�� �� �� �ֽ��ϴ�.

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

int MyListID[4]; // Display List ���� (Display List�� ���� ID�� ���� �ĺ���)

GLUquadricObj* sphere = gluNewQuadric(); // Sphere�� �����ϱ� ���� ���ο� Quadric Object ����
GLUquadricObj* cylinder = gluNewQuadric(); // Cylinder�� �����ϱ� ���� ���ο� Quadric Object ����
GLUquadricObj* disk = gluNewQuadric(); // Disk�� �����ϱ� ���� ���ο� Quadric Object ����
GLUquadricObj* partialDisk = gluNewQuadric(); // Partial disk�� �����ϱ� ���� ���ο� Quadric Object ����

// �ʱ� ���� (4���� Display List ���� �� ���� ����) 
void MyInit()
{
    MyListID[0] = glGenLists(4); // 4���� Display List ID�� ����� ù ��° ���̵� MyListID[0]�� ����
    for (int i = 1; i < 4; i++)
        MyListID[i] = MyListID[i - 1] + 1; // ������ 3���� Display List ID�� MyListID �迭�� ����

    GLfloat mat_ambient[] = { 1.0, 0.0, 0.0, 1.0 }; // RGBA �ݻ縦 ����
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 }; // RGBA �ݻ縦 ����
    GLfloat mat_shininess[] = { 50.0 }; // ���� Ŭ ���� ǥ���� �Ų������� (0 ~ 128)
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 }; // ���� ��ġ ����
    GLfloat model_ambient[] = { 1.0, 0.0, 0.0, 1.0 }; // ��ü ȭ���� RGBA ���� ����

    glClearColor(0.0, 0.0, 0.0, 0.0); // ȭ���� ���������� �����

    // glMaterialfv : ���� ���� (GL_FRONT�� �μ��� �޾� �Ѹ鿡 ���� ���� ����)
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient); // GL_AMBIENT : �ֺ����� ���� (Ư�� ���� ���� ��� ������ ������ ����)
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); // GL_SPECULAR : �ݻ籤�� ���� (�ſ��ó�� ���������� ���� ǥ��)
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess); // GL_SHININESS : ���� (ǥ���� �Ų����� ����)
    glLightfv(GL_LIGHT0, GL_POSITION, light_position); // ������ ��ġ ����
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient); // ���� �� �Ű� ���� ���� (���� ȿ�� ���� �����Ͽ� �ֺ��� ���)

    glEnable(GL_LIGHTING); // ���� ���
    glEnable(GL_LIGHT0); // ���� �� 0 �� ���� ���
    glEnable(GL_DEPTH_TEST); // ���� ���� (�������� �� ����� �鸸 ���̵��� ��)
}

// Sphere�� ���� Display List �����ϰ�, GLU_FILL���� �׸���
void MySphereDisplayList()
{
    glNewList(MyListID[0], GL_COMPILE); // sphere�� ���� Display List ����
   
    glMatrixMode(GL_MODELVIEW); // �𵨺� ��� ����
    glLoadIdentity(); // �𵨺� ����� �׵� ��ķ� �ʱ�ȭ

    glEnable(GL_LIGHTING); // ���� ���

    glShadeModel(GL_SMOOTH); // ǥ���� �ε巴�� ���� (�⺻��)

    gluQuadricTexture(sphere, GL_FALSE); // Texture ��ǥ�� ����� ������ ���� (�μ� : Texture ��ǥ�� �������� ����(Default))

    gluQuadricNormals(sphere, GLU_SMOOTH); // ���� ���� ����
    gluQuadricOrientation(sphere, GLU_OUTSIDE); // ���� ���� ���� �� �ܺο� ���� ���� ����

    gluQuadricDrawStyle(sphere, GLU_FILL); // Solid ������ Modeling���� Draw Style ����
    //gluQuadricDrawStyle(sphere, GLU_LINE); // Wire-frame ������ Modeling���� Draw Style ����
    //gluQuadricDrawStyle(sphere, GLU_SILHOUETTE); // �ܺ� �𼭸� Modeling���� Draw Style ����
    //gluQuadricDrawStyle(sphere, GLU_POINT); // ������ �������� ���� Modeling���� Draw Style ����
    
    gluSphere(sphere, 1.5, 50, 50); // �������� 1.5�� ���� �׸�
    glEndList(); // Display List�� �� ǥ��
}

// Cylinder�� ���� Display List �����ϰ�, GLU_LINE���� �׸���
void MyCylinderDisplayList()
{
    glNewList(MyListID[1], GL_COMPILE); // cylinder�� ���� Display List ����

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_LIGHTING);

    glShadeModel(GL_SMOOTH);
    
    gluQuadricTexture(cylinder, GL_FALSE);

    gluQuadricNormals(cylinder, GLU_SMOOTH);
    gluQuadricOrientation(cylinder, GLU_OUTSIDE);

    //gluQuadricDrawStyle(cylinder, GLU_FILL);
    gluQuadricDrawStyle(cylinder, GLU_LINE);
    //gluQuadricDrawStyle(cylinder, GLU_SILHOUETTE);
    //gluQuadricDrawStyle(cylinder, GLU_POINT);

    glRotatef(60.0f, 0.5f, 1.0f, 0.0f); // �Ǹ����� ����� ��ü������ ���� ���� ȸ����Ŵ
    gluCylinder(cylinder, 1.5, 1.5, 2.0, 50, 50); // �ظ��� �������� 1.5�̰� ���̰� 2.0�� ������� �׸�

    glEndList(); // Display List�� ��
}

// Disk�� ���� Display List �����ϰ�, GLU_SILHOUETTE���� �׸���
void MyDiskDisplayList()
{
    glNewList(MyListID[2], GL_COMPILE); // disk�� ���� Display List ����

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_LIGHTING);

    glShadeModel(GL_SMOOTH);
    
    gluQuadricTexture(disk, GL_FALSE);

    gluQuadricNormals(disk, GLU_SMOOTH);
    gluQuadricOrientation(disk, GLU_OUTSIDE);

    //gluQuadricDrawStyle(disk, GLU_FILL);
    //gluQuadricDrawStyle(disk, GLU_LINE); 
    gluQuadricDrawStyle(disk, GLU_SILHOUETTE);
    //gluQuadricDrawStyle(disk, GLU_POINT);

    glRotatef(60.0f, 0.5f, 1.0f, 0.0f);
    gluDisk(disk, 0.5, 1.5, 20, 20); // ���� ���� �������� 0.5�̰� �ٱ��� ���� �������� 1.5�� Disk �׸�
    glEndList(); // Display List�� ��
}

// Partial Disk�� ���� Display List �����ϰ�, GLU_POINT�� �׸���
void MyPartialDiskDisplayList()
{
    glNewList(MyListID[3], GL_COMPILE); // partialDisk�� ���� Display List ����

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_LIGHTING);

    glShadeModel(GL_SMOOTH);
    
    gluQuadricTexture(partialDisk, GL_FALSE);

    gluQuadricNormals(partialDisk, GLU_SMOOTH);
    gluQuadricOrientation(partialDisk, GLU_OUTSIDE);

    //gluQuadricDrawStyle(partialDisk, GLU_FILL);
    //gluQuadricDrawStyle(partialDisk, GLU_LINE); 
    //gluQuadricDrawStyle(partialDisk, GLU_SILHOUETTE);
    gluQuadricDrawStyle(partialDisk, GLU_POINT);

    gluPartialDisk(partialDisk, 0.5, 1.5, 50, 13, 0, 90); // ���� ���� �������� 0.5�̰� �ٱ��� ���� �������� 1.5�� Disk�� 90����ŭ �׸�

    glEndList(); // Display List�� ��
}

// Display event�� �Ͼ �� ȭ���� ����� Display List�� �����ϴ� �Լ�
void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // �� ����, ���� ���� �����Ͽ� ȭ�� �����

    glCallList(MyListID[0]); // ù ��° Display List ����
    glCallList(MyListID[1]); // �� ��° Display List ����
    glCallList(MyListID[2]); // �� ��° Display List ����
    glCallList(MyListID[3]); // �� ��° Display List ����
    glFlush(); // ���� ������� ���� ����� ��� ���� (���� ���º����� �������� ���������� ���μ��� ����)
}

// ������ ���ú����� ��Ⱦ�� ���缭 �ְ� ���� �ذ��ϱ�
void MyReshape(int NewWidth, int NewHeight)
{
    glViewport(0, 0, NewWidth, NewHeight);

    glMatrixMode(GL_PROJECTION); // ���� ��� ����
    glLoadIdentity(); // ���� ����� �׵� ��ķ� �ʱ�ȭ

    // ���ú��Ǹ� ������ ��Ⱦ�� ���߱�
    glOrtho(-3, 3, -3 * (GLfloat)NewHeight / (GLfloat)NewWidth, 3 * (GLfloat)NewHeight / (GLfloat)NewWidth, -10.0, 10.0);
}

int main(int argc, char** argv) {
    glutInit(&argc,argv); // Window OS�� �����ϰ� GLUT Library �ʱ�ȭ
    glutInitDisplayMode(GLUT_RGB); // Display Mode ����
    glutInitWindowSize(300, 300); // â ũ�� ����
    glutInitWindowPosition(0, 0); // â ��ġ ����
    glutCreateWindow("3D Primitives Using Display List"); // â �̸� ����
    glClearColor(1.0, 1.0, 1.0, 1.0); // ȭ���� ������� �����
    MyInit(); // �ʱ� ����
    glutDisplayFunc(MyDisplay); // Display Even�� �߻��� ������ MyDisplay ȣ���ϵ��� ���
    glutReshapeFunc(MyReshape); // ȭ���� ���� �׷��� �� ������ MyReshape ȣ���ϵ��� ���

    MySphereDisplayList(); // sphere�� ���� Display List ����
    //MyCylinderDisplayList(); // cylinder�� ���� Display List ����
    //MyDiskDisplayList(); // disk�� ���� Display List ����
    //MyPartialDiskDisplayList(); // partialDisk�� ���� Display List ����

    glutMainLoop(); // GLUT Event ó�� Loop ����
    return 0;
}
