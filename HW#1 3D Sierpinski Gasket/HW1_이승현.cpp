/*******************************************************************************************************/
/*                                           HW#1 : 3D Sierpinski Gasket                               */
/*  �ۼ��� : �̽���                                                             ��¥ : 2021�� 9�� 20�� */
/*                                                                                                     */
/* ���� ���� :                                                                                         */
/* 3D Sierpinski Gasket�� �����ϰ�, Reshape callback�� ����Ͽ� �ְ� ������ �ذ��Ѵ�.                  */
/* ��� :                                                                                              */
/* 1. (0, 0, 0), (500, 0, 0), (250, 250 * ��3, 0), (250, 250 / 3 * ��3, 500 / 3 * ��3)�� ����������    */
/*    ���� �����ü�� X, Y�� �������� ���� 40, -20�Ƹ�ŭ ȸ���Ͽ� �ش� ���ü�� ��ü������ �׸���.     */
/*    ���ü�� ���ο� ��ġ�� �� p�� ���ü�� ������ �� ������ �� ������ ���� ������ �� p�� ���, �ٽ�  */
/*    �� p�� ���ü�� ������ �� ������ �� ������ ���� ������ �� p�� ��� ������ 50000�� �ݺ��Ͽ�       */
/*    3D tetrahedron Gasket�� �����Ѵ�.                                                                */
/*    �̶� z�࿡�� ���� ���� ���� ���� ���� ��������, ū ���� ���� ���� ���� �ʷϻ��� ���.            */
/* 2. MyReshape �ݹ��Լ��� ���� ���ú��ǿ� �������� ��Ⱦ�� ��ġ��Ű��, glutReshapeFunc�� ����        */
/*    MyReshape�ݹ��Լ��� ����Ѵ�. �̶� ȭ���� �߽��� (0, 0, 0)�̴�.                                  */
/*******************************************************************************************************/

#define RADIAN 3.14159 / 180.0 // ���� ����
#include <GL/glut.h>
#include <stdlib.h> // rand() �Լ� ��� �뵵
#include <math.h> // sqrt(), fabs() �Լ� ��� �뵵

// �ʱ� ����
void MyInit()
{ 
	glClearColor(1.0, 1.0, 1.0, 1.0); // �Ͼ������� ����
	glColor3f(1.0, 0.0, 0.0); // ���������� ����

	glMatrixMode(GL_PROJECTION); // ������� ����
	glLoadIdentity(); // ���� ��������� �׵���ķ� �ʱ�ȭ
	glOrtho(0.0, 500.0, 0.0, 500.0, 1, -1); // ��ĺ�ȯ

	glMatrixMode(GL_MODELVIEW);  // �𵨺���� ����
	glLoadIdentity(); // ���� �𵨺� ����� �׵���ķ� �ʱ�ȭ
}

// X�� �������� x�Ƹ�ŭ ��ǥ ȸ��
void RotateX(float vertex[3], float x)
{
	float y, z;
	y = vertex[1];
	z = vertex[2];
	vertex[1] = y * cosf(x * RADIAN) - z * sinf(x * RADIAN);
	vertex[2] = y * sinf(x * RADIAN) + z * cosf(x * RADIAN);
}

// Y�� �������� y�Ƹ�ŭ ��ǥ ȸ��
void RotateY(float vertex[3], float y)
{
	float x, z;
	x = vertex[0];
	z = vertex[2];
	vertex[0] = z * sinf(y * RADIAN) + x * cosf(y * RADIAN);
	vertex[2] = z * cosf(y * RADIAN) - x * sinf(y * RADIAN);
}

// Z�� �������� z�Ƹ�ŭ ��ǥ ȸ��
void RotateZ(float vertex[3], float z)
{
	float x, y;
	x = vertex[0];
	y = vertex[1];
	vertex[0] = x * cosf(z * RADIAN) - y * sinf(z * RADIAN);
	vertex[1] = x * sinf(z * RADIAN) + y * cosf(z * RADIAN);
}

// 3D Sierpinski Gasket ����
void MyDisplay(void)
{
	float vertices[4][3] = { {0.0, 0.0, 0.0},
		{500.0,0.0,0.0},
		{250.0, 250.0 * sqrt(3), 0.0},
		{250.0, 250.0 / 3 * sqrt(3), 500.0 / 3 * sqrt(6)} }; // �ʱ� �����ü�� ������ ��ǥ
	float minZ = vertices[0][2], maxZ = vertices[0][2];
	for (int i = 0; i < 4; i++)
	{
		RotateX(vertices[i], 40); // ��� ���� ���� X�� �������� 40��ȸ��
		RotateY(vertices[i], -20); // ��� ���� ���� Y�� �������� -20��ȸ��
		RotateZ(vertices[i], 0); // Z�� �������δ� ȸ������ �ʴ´�.
		if (minZ > vertices[i][2])
			minZ = vertices[i][2]; // ȸ�� �� ������ �� z�࿡�� ���� ���� ���� ������ ���� z�� ��ǥ�� minZ�� ����
		if (maxZ < vertices[i][2])
			maxZ = vertices[i][2]; // ȸ�� �� ������ �� z�࿡�� ���� ū ���� ������ ���� z�� ��ǥ�� maxZ�� ����
	}
	float rangeZ = maxZ - minZ; // rangeZ = z�� ����

	int i, j;
	float p[3] = { 250.0, 125.0, 150.0 };  // ���� ����Ʈ
	RotateX(p, 40); // �� p�� X�� �������� 40��ȸ��
	RotateY(p, -20); //�� p�� Y�� �������� -20��ȸ��
	RotateZ(p, 0); // Z�� �������δ� ȸ������ �ʴ´�.

	glClear(GL_COLOR_BUFFER_BIT); // �� ���� �����Ͽ� �����쿡�� �׸� ����

	for (j = 0; j < 50000; j++)
	{
		i = rand() % 4; // ������ �� ����
		// ���� ���õ� ���� ���� ���� �������� ���ο� �� ��ġ ��� 
		p[0] = (p[0] + vertices[i][0]) / 2.0; // x ��ǥ
		p[1] = (p[1] + vertices[i][1]) / 2.0; // y ��ǥ
		p[2] = (p[2] + vertices[i][2]) / 2.0; // z ��ǥ

		glBegin(GL_POINTS); // �� �׸��� ���� (glBegin�� glEnd ���̿��� ���� ����)
		// z�� �� ū ���� ������ ���� ���� �ʷϻ�, ���� ���� ������ ���� ���� �������� ���.
		if (minZ < 0)
			glColor3f(1.0 - (p[2] + fabs(minZ)) / rangeZ, (p[2] + fabs(minZ)) / rangeZ, 0.0);
		else
			glColor3f(1.0 - (p[2] - minZ) / rangeZ, (p[2] - minZ) / rangeZ, 0.0);
		glVertex3fv(p); // ���� ��ġ�� �� ���
		glEnd(); // �� �׸��� ������
	}

	glFlush(); // ���� ������� ���� ����� ��� ���� (���� ���º����� �������� ���������� ���μ��� ����)
}

void MyReshape(int NewWidth, int NewHeight)
{ 
	glViewport(0, 0, NewWidth, NewHeight); // glViewport: ���� ���� (���� �簢���� ���� �Ʒ� �������� �ȼ����� ������ �ʺ�, ���̸� �μ��� �Է¹���)
	GLfloat Widthfactor = (GLfloat)NewWidth / (GLfloat)500; // �ٲ� ������ �ʺ� ���� ����
	GLfloat Heightfactor = (GLfloat)NewHeight / (GLfloat)500; // �ٲ� ������ ���̿� ���� ����
	glMatrixMode(GL_PROJECTION); // ������� ����
	glLoadIdentity(); // ���� ��������� �׵� ��ķ� �ʱ�ȭ
	// glOrtho: �þ ���� ������ŭ ���ú����� ��Ⱦ�� ����
	glOrtho(-600.0 * Widthfactor, 600.0 * Widthfactor, -600.0 * Heightfactor, 600.0 * Heightfactor, -600.0, 600.0);
} 

void main(int argc, char** argv)
{
	glutInit(&argc, argv); // Window OS�� ������ �����ϰ� GLUT Library�� �ʱ�ȭ
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Display Mode ���� (���� ���� â�� ����� RGB ���� ����)
	glutInitWindowSize(500, 500); // Window â ũ�⸦ (500, 500)���� ����
	glutInitWindowPosition(0, 0); // Window â ��ġ�� (0, 0)���� ����
	glutCreateWindow("Sierpinski Gasket"); // �̸��� "Sierpinski Gasket"�� Window â ����
	MyInit(); // �ʱ� ����
	glutDisplayFunc(MyDisplay); // Window�� �׸� ������ MyDisplay �Լ��� ȣ���ϵ��� �ݹ��Լ� ���
	glutReshapeFunc(MyReshape); // Window�� ũ�⸦ ������ ������ MyReshape �Լ��� ȣ���ϵ��� �ݹ��Լ� ���
	glutMainLoop(); // GLUT Event ó�� Loop ���� (�Լ��� ��� ����Ǹ鼭 �߻��� �޽����� �޾� �޽��� ó���Լ��� ȣ��)
}
