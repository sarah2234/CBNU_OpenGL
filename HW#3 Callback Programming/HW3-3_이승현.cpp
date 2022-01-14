/*******************************************************************************************************/
/*                                     HW#3-3. Mouse Callback ����                                     */
/*  �ۼ��� : �̽���                                                             ��¥ : 2021�� 10�� 6�� */
/*                                                                                                     */
/* ���� ���� :                                                                                         */
/* 1. Mouse Callback�� �̿��Ͽ� ��Ŭ���� ��Ŭ������ �簢���� �������� �����Ѵ�.                        */
/* 2. Idle Callback�� �̿��Ͽ� �簢���� ���������� �����̵��� �Ѵ�.                                    */
/* 3. Display Callback�� �̿��Ͽ� �簢���� â ���� ����� �ʵ��� �Ѵ�.                               */
/* ��� :                                                                                              */
/* 1. ���콺�� ���� ��ư�� Ŭ���ϸ� �簢���� 0.01�� ���������� �����δ�.                               */
/* 2. ���콺�� ������ ��ư�� Ŭ���ϸ� �̵��ϰ� �ִ� �簢���� �����.                                   */
/* 3. â�� ũ�⸦ �ٲ��� �� �簢���� â �� �������� �Ѿ�� �ʵ��� �Ѵ�.                              */
/*******************************************************************************************************/

// �簢���� �����̴� �ӵ��� ���� 0.01�� ���߾����ϴ�.

#include <GL/glut.h>

GLfloat moveX; // �簢���� ��ġ�� �����ϱ� ���� ����
GLfloat windowWidth; // ���� â ũ�⿡ ���� ���� ����

// �ʱ� ����
void MyInit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0); // ������� ȭ�� �����

	glMatrixMode(GL_PROJECTION); // ���� ��� ����
	glLoadIdentity(); // ���� ����� �׵� ��ķ� �ʱ�ȭ
	glOrtho(-1.0, 1.0, -1.0, -1.0, -1.0, 1.0); // ���� ������ ����
}

// Display Event�� �߻��� �� â���� �׸��� ����� �簢���� �׸��� �Լ�
void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT); // �� ���۸� �����Ͽ� â���� �׸� ����
	glColor3f(0.5, 0.5, 0.5); // �簢���� ȸ������ ����

	if (0.5 + moveX > windowWidth / 2)
	{
		moveX = -0.5 + windowWidth / 2; // �簢���� â�� ������ �ٱ��� ��ġ�ϸ� â�� ������ �鿡 �´굵�� ��ġ ����
	}

	glBegin(GL_POLYGON); // �簢�� �׸��� ����
	
	glVertex3f(-0.5 + moveX, -0.5, 0.0); // ���� �Ʒ�
	glVertex3f(0.5 + moveX, -0.5, 0.0); // ������ �Ʒ�
	glVertex3f(0.5 + moveX, 0.5, 0.0); // ������ ��
	glVertex3f(-0.5 + moveX, 0.5, 0.0); // ���� ��
	glEnd(); // �簢�� �׸��� ������
	glutSwapBuffers();
}

// ȭ���� ���� �׷��� �� �� �簢���� ������ �����ϵ��� ���߰�, �簢���� ��ġ�� �������ϴ� �Լ�
void MyReshape(int width, int height)
{
	GLfloat widthFactor = (GLfloat)width / (GLfloat)500;
	GLfloat heightFactor = (GLfloat)height / (GLfloat)500;
	glViewport(0, 0, width, height); // ���� ����

	glMatrixMode(GL_PROJECTION); // ���� ��� ����
	glLoadIdentity(); // ���� ����� �׵� ��ķ� �ʱ�ȭ
	// â�� ũ�Ⱑ �ٲ� �簢���� ũ��� ���ߵ��� ��
	glOrtho(-1 * widthFactor, 1 * widthFactor, -1 * heightFactor, 1 * heightFactor, -1, 1);

	windowWidth = 2 * widthFactor; // â ���� ����
}

// Ű���忡�� Ű�� �Է¹޾� ó���ϴ� �Լ�
void MyKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'Q':
		exit(0); break;
	case 'q':
		exit(0); break;
	case 27: // esc
		exit(0); break; // Q, q, esc�� ������ ����
	}
	
	glutPostRedisplay(); // ������ Display Event �߻���Ŵ
}

// Idle�� �� �簢���� �������� �����̵��� �ϴ� �Լ�
void MoveToTheLeft(void)
{
	if (0.5 + moveX < windowWidth / 2)
		moveX += 0.01; // �簢���� â ���� ���� �Ѿ�� ������ ���������� ���������� �����̵��� ��
	glutPostRedisplay(); // ������ Display Event �߻���Ŵ
}

// ���콺 Ŭ���� ���� ���� �̺�Ʈ�� ó���ϴ� �Լ�
void MyMouseClick(GLint button, GLint state, GLint x, GLint y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		glutIdleFunc(MoveToTheLeft); // ��Ŭ���� �ϸ� �ش� Idle Callback �Լ��� ȣ���Ͽ� �簢���� ���������� �������� ������ 
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		glutIdleFunc(NULL); // ��Ŭ���� �ϸ� �簢���� �����ӿ� ���� ��� ������ ���� ����
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); // Window OS ���ǰ� �����ϰ� GLUT Library �ʱ�ȭ
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // Display Mode ����
	glutInitWindowPosition(0, 0); // â ��ġ ����
	glutInitWindowSize(500, 500); // â ũ�� ����
	glutCreateWindow("Keyboard Callback-1"); // â ���� �� �̸� ����
	MyInit(); // �ʱ� ����
	glutDisplayFunc(MyDisplay); // Display Event�� �Ͼ ������ MyDisplay ȣ���ϵ��� ���
	glutReshapeFunc(MyReshape); // ȭ���� ���� �׷��� �� ������ MyReshape ȣ���ϵ��� ���
	glutKeyboardFunc(MyKeyboard); // Ű����κ��� Ű�� �Է¹��� ������ MyKeyboard ȣ���ϵ��� ���
	glutMouseFunc(MyMouseClick); // ���콺�� Ŭ���� ������ MyMouseClick ȣ���ϵ��� ���
	glutMainLoop(); // GLUT Event ó�� Loop ����
	return 0;
}