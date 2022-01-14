/*******************************************************************************************************/
/*                                           HW#2-1. GL Modeling                                       */
/*  �ۼ��� : �̽���                                                             ��¥ : 2021�� 9�� 29�� */
/*                                                                                                     */
/* ���� ���� :                                                                                         */
/* 10 ���� 2D Primitive(Points, Lines, LineStrip, LineLoop, TriangleFan, Triangles, TriangleStrip,     */
/* Polygon, Quads, QuadStrip)�� �����Ѵ�.                                                              */
/* ��� :                                                                                              */
/* 1. glBegin �Լ��� GL_POINTS�� �μ��� �Է¹ް�, glGetFloatv �Լ��� �̿��� ���� ũ�⿡ ����           */
/*    ���� ���� ���� �޾ƿ� ���� ũ�⸦ �����Ͽ� 6���� ���� �׸���.                                    */
/* 2. glBegin �Լ��� GL_LINES�� �μ��� �Է¹޾� 3���� ������ �׸���.                                   */
/* 3. glBegin �Լ��� GL_LINESTRIP�� �μ��� �Է¹޾� 5���� ������ ���� ����ǵ��� �׸���.               */
/*    (ù ��° ���� ������ ���� ���� ������� �ʴ´�.)                                                 */
/* 4. glBegin �Լ��� GL_LINELOOP�� �μ��� �Է¹޾� 6���� ��� ���� ����ǵ��� 6���� ������ �׸���.     */
/* 5. glBegin �Լ��� GL_TRIANGLE_FAN�� �μ��� �Է¹޾� �ϳ��� �������� �����ϴ� 4���� �ﰢ���� �׸���. */
/* 6. glBegin �Լ��� GL_TRIANGLES�� �μ��� �Է¹޾� ���� 3���� �������� �׷����� �ﰢ�� 2���� �׸���.  */
/* 7. glBegin �Լ��� GL_TRIANGLE_STRIP�� �μ��� �Է¹޾� �ﰢ������ ��� ����� ���·� �׸���.         */
/* 8. glBegin �Լ��� GL_POLYGON�� �μ��� �Է¹޾� ������ü(�ٰ���)�� �׸���.                           */
/* 9. glBegin �Լ��� GL_QUADS�� �μ��� �Է¹޾� ���� 4���� �������� �׷����� �簢�� 2���� �׸���.      */
/* 10. glBegin �Լ��� GL_QUAD_STRIP�� �μ��� �Է¹޾� �簢������ ��� ����� ���·� �׸���.            */
/*******************************************************************************************************/

// * MyDisplay �Լ����� 2D Primitive�鿡 ���� �ּ��� �ֽ��ϴ�.

#include <GL/glut.h>
#include <math.h>

void MyDisplay( ) {
    GLfloat Size[2];
     glClear(GL_COLOR_BUFFER_BIT); // �� ���۸� �����Ͽ� �����쿡�� �׸� ����
     glColor3f(0.5, 0.4, 0.3); // ���� ����

     // 1. Points �׸��� (���� �߾ӿ� ���簢�� �׸���)
     glGetFloatv(GL_POINT_SIZE, Size); // ���� ������ ���� �޾ƿ� (�� ũ���� �ּڰ��� �ִ��� Size�� ����)
     glPointSize(Size[0] * 5); // �� ũ�⸦ �ּڰ��� 5�� ũ��� ����

     glBegin(GL_POINTS); // ������ Primitive �׸���
     glVertex3f(-0.5, -0.5 * sqrt(3), 0.0); // �� ��ġ ���� (v0)
     glVertex3f(0.5, -0.5 * sqrt(3), 0.0); // v1
     glVertex3f(1.0, 0.0, 0.0); // v2
     glVertex3f(0.5, 0.5 * sqrt(3), 0.0); // v3
     glVertex3f(-0.5, 0.5 * sqrt(3), 0.0); // v4
     glVertex3f(-1.0, 0.0, 0.0); // v5
     glEnd(); // �׸��� ������

     /*
     // 2. Lines �׸��� (�� ���� �����ϴ� ���� �׸���)
     glBegin(GL_LINES);
     glVertex3f(-0.5, -0.5 * sqrt(3), 0.0); // v0
     glVertex3f(0.5, -0.5 * sqrt(3), 0.0); // v1
     glVertex3f(1.0, 0.0, 0.0); // v2
     glVertex3f(0.5, 0.5 * sqrt(3), 0.0); // v3
     glVertex3f(-0.5, 0.5 * sqrt(3), 0.0); // v4
     glVertex3f(-1.0, 0.0, 0.0); // v5
     glEnd();
     */

     /*
     // 3. LineStrip �׸��� (���е��� �����Ͽ� �׸���, �̶� ù ��° ���� ������ ���� ������� ����)
     glBegin(GL_LINE_STRIP);
     glVertex3f(-0.5, -0.5 * sqrt(3), 0.0); // v0
     glVertex3f(0.5, -0.5 * sqrt(3), 0.0); // v1
     glVertex3f(1.0, 0.0, 0.0); // v2
     glVertex3f(0.5, 0.5 * sqrt(3), 0.0); // v3
     glVertex3f(-0.5, 0.5 * sqrt(3), 0.0); // v4
     glVertex3f(-1.0, 0.0, 0.0); // v5
     glEnd();
     */

     /*
     // 4. LineLoop �׸��� (ù ��° ���� ������ ���� �����Ͽ� ��� ���е��� ����ǵ��� �׸���)
     glBegin(GL_LINE_LOOP);
     glVertex3f(-0.5, -0.5 * sqrt(3), 0.0); // v0
     glVertex3f(0.5, -0.5 * sqrt(3), 0.0); // v1
     glVertex3f(1.0, 0.0, 0.0); // v2
     glVertex3f(0.5, 0.5 * sqrt(3), 0.0); // v3
     glVertex3f(-0.5, 0.5 * sqrt(3), 0.0); // v4
     glVertex3f(-1.0, 0.0, 0.0); // v5
     glEnd();
     */

     /*
     // 5. TriangleFan �׸��� (�ϳ��� �������� �����ϴ� �Ϸ��� �ﰢ���� �׸���)
     glBegin(GL_TRIANGLE_FAN);
     glVertex3f(-1.0, -1.0, 0.0); // v0
     glVertex3f(1.0, -0.8, 0.0); // v1
     glVertex3f(0.8, -0.5, 0.0); // v2
     glVertex3f(0.7, -0.2, 0.0); // v3
     glVertex3f(0.2, 0.0, 0.0); // v4
     glVertex3f(0.0, 0.0, 0.0); // v5
     glEnd();
     */

     /*
     // 6. Triangles �׸��� (3���� ������ �ﰢ�� �ϳ� �׸���)
     glBegin(GL_TRIANGLES);
     glVertex3f(-0.5, -0.5 * sqrt(3), 0.0); // v0
     glVertex3f(0.5, -0.5 * sqrt(3), 0.0); // v1
     glVertex3f(1.0, 0.8, 0.0); // v2
     glVertex3f(0.5, 0.5 * sqrt(3), 0.0); // v3
     glVertex3f(-0.5, 0.5 * sqrt(3), 0.0); // v4
     glVertex3f(-1.0, -0.3, 0.0); // v5
     glEnd();
     */

     /*
     // 7. TriangleStrip �׸��� (����� �Ϸ��� �ﰢ������ �׸���)
     glBegin(GL_TRIANGLE_STRIP);
     glVertex3f(1.5, -1.2, 0.0); // v0
     glVertex3f(1.0, 1.0, 0.0); // v1
     glVertex3f(0.8, -0.8, 0.0); // v2
     glVertex3f(0.5, 1.0, 0.0); // v3
     glVertex3f(0.2, -1.0, 0.0); // v4
     glVertex3f(-0.5, 0.8, 0.0); // v5
     glVertex3f(-1.0, -1.1, 0.0); // v6
     glEnd();
     */

     /*
     // 8. Polygon �׸��� (������ ������ ���������� ���� �ٰ��� �׸���, ���⼭�� �������� �׸���)
     glBegin(GL_POLYGON);
     glVertex3f(-0.5, -0.5 * sqrt(3), 0.0); // v0
     glVertex3f(0.5, -0.5 * sqrt(3), 0.0); // v1
     glVertex3f(1.0, 0.0, 0.0); // v2
     glVertex3f(0.5, 0.5 * sqrt(3), 0.0); // v3
     glVertex3f(-0.5, 0.5 * sqrt(3), 0.0); // v4
     glVertex3f(-1.0, 0.0, 0.0); // v5
     glEnd();
     */

     /*
     // 9. Quads �׸��� (4���� ������ �簢�� �ϳ� �׸���)
     glBegin(GL_QUADS);
     glVertex3f(1.0, -1.0, 0.0); // v0
     glVertex3f(1.3, 0.2, 0.0);  // v1
     glVertex3f(0.5, 0.4, 0.0); // v2
     glVertex3f(0.0, -1.0, 0.0); // v3
     glVertex3f(-0.2, 0.0, 0.0); // v4
     glVertex3f(-0.1, 1.2, 0.0); // v5
     glVertex3f(-0.7, 1.0, 0.0); // v6
     glVertex3f(-0.9, 0.4, 0.0); // v7
     glEnd();
     */

     /*
     // 10. QuadStrip �׸��� (����� �Ϸ��� �簢���� �׸���)
     glBegin(GL_QUAD_STRIP);
     glVertex3f(1.0, -1.0, 0.0); // v0
     glVertex3f(1.3, 0.2, 0.0);  // v1
     glVertex3f(0.0, -1.0, 0.0); // v2
     glVertex3f(0.5, 0.4, 0.0); // v3
     glVertex3f(-0.2, 0.0, 0.0); // v4
     glVertex3f(-0.1, 1.2, 0.0); // v5
     glVertex3f(-0.9, 0.4, 0.0); // v6
     glVertex3f(-0.7, 1.0, 0.0); // v7
     glEnd();
     */

     glFlush(); // ���� ������� ���� ��ɵ� ��� ���� (���� ���� ������ �������� ���������� ���μ��� ����)
}

int main(int argc, char** argv) {
     glutInit(&argc, argv); // ������ �ý����� ������ ó�� & GLUT ���̺귯�� �ʱ�ȭ
     glutInitDisplayMode(GLUT_RGBA); // ���÷��� ǥ���� �ֿ� Ư¡ ���� (Ʈ�� �÷� ���(�⺻��))
     glutInitWindowSize(500, 500); // ������ â ũ�� ����
     glutInitWindowPosition(0, 0); // ������ â ��ġ ����
     glutCreateWindow("2D Primitives"); // ������ â �̸� ����
     glClearColor(1.0, 1.0, 1.0, 1.0); // ������ â ���ȭ�� ���� ���� (���)
     glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0); // ���� ��Ʈ������ ���� ����� ����
     glutDisplayFunc(MyDisplay); // ���÷��� �̺�Ʈ�� ���� MyDisplay �ݹ��Լ� ���

     glutMainLoop( ); // GLUT Event ó�� Loop ���� (�Լ��� ����Ǹ鼭 �߻��ϴ� �޼����� ó���ϵ��� �޼��� ó���Լ� ȣ��)
     return 0;
}