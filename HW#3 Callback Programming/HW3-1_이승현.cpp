/*******************************************************************************************************/
/*                                       HW#3-1 : Keyboard Callback ����I                              */
/*  �ۼ��� : �̽���                                                             ��¥ : 2021�� 10�� 6�� */
/*                                                                                                     */
/* ���� ���� :                                                                                         */
/* �簢���� �׸� �� Keyboard Callback�� ���� �ش� �簢���� ������ �� ���� �ٲٴ� ����� �����Ѵ�.      */
/* ��� :                                                                                              */
/* 1. a �Ǵ� A�� ������ �簢���� �������� 0.1�� �̵��Ѵ�.                                              */
/* 2. f �Ǵ� F�� ������ �簢���� ���������� 0.1�� �̵��Ѵ�.                                            */
/* 3. r �Ǵ� R�� ������ �簢���� �Ʒ��� 0.1�� �̵��ϰ�, ���������� �ٲ��.                             */
/* 4. v �Ǵ� V�� ������ �簢���� ���� 0.1�� �̵��Ѵ�.                                                  */
/* 5. b �Ǵ� B�� ������ �簢���� �Ķ������� �ٲ��.                                                    */
/*******************************************************************************************************/

#include <GL/glut.h>

GLfloat moveX;
GLfloat moveY;
GLint red = 1;
GLint blue = 1;

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
	glColor3f(red, 0, blue); // �ʱ� ������ ��ũ������ ����

	glBegin(GL_POLYGON); // �簢�� �׸��� ����
	glVertex3f(-0.5 + moveX, -0.5 + moveY, 0.0);
	glVertex3f(0.5 + moveX, -0.5 + moveY, 0.0);
	glVertex3f(0.5 + moveX, 0.5 + moveY, 0.0);
	glVertex3f(-0.5 + moveX, 0.5 + moveY, 0.0);
	glEnd(); // �簢�� �׸��� ������
	glFlush(); // ���� ���� ������ �������� ���������� ���μ��� ����
}

// ȭ���� ���� �׷��� �� �� �簢���� ������ �����ϵ��� ���ߴ� �Լ�
void MyReshape(int width, int height)
{
	glViewport(0, 0, width, height); // ���� ����

	glMatrixMode(GL_PROJECTION); // ���� ��� ����
	glLoadIdentity(); // ���� ����� �׵� ��ķ� �ʱ�ȭ
	glOrtho(-1 , 1 , -1 * height / width, 1 * height / width, -1, 1); // ���ú��Ǹ� ������ ��Ⱦ�� ���߱�
}

// Ű���带 �̿��Ͽ� �簢���� �����̵��� �ϴ� �Լ�
void MyKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
	case 'A': // a�� A�� �Է¹����� �簢���� �������� ������
		moveX -= 0.1;
		break;
	case 'f':
	case 'F': // f�� f�� �Է¹����� �簢���� ���������� ������
		moveX += 0.1;
		break;
	case 'r':
	case 'R': // r�� R�� �Է¹����� �簢���� �Ʒ������� �����̰� ���������� ����
		moveY -= 0.1;
		red = 1;
		blue = 0;
		break;
	case 'v':
	case 'V': // v�� V�� �Է¹����� �簢���� �������� ������
		moveY += 0.1;
		break;
	case 'b':
	case 'B': // b�� B�� �Է¹����� �簢���� �Ķ������� ����
		red = 0;
		blue = 1;
		break;
	case 'Q':
		exit(0); break;
	case 'q':
		exit(0); break;
	case 27: // esc
		exit(0); break; // Q, q, esc�� ������ ���α׷� ����
	}
	glutPostRedisplay(); // ������ Display Event �߻���Ŵ
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); // Window OS ���ǰ� �����ϰ� GLUT Library �ʱ�ȭ
	glutInitDisplayMode(GLUT_RGB); // Display Mode ����
	glutInitWindowPosition(0, 0); // â ��ġ ����
	glutInitWindowSize(500, 500); // â ũ�� ����
	glutCreateWindow("Keyboard Callback-1"); // â ���� �� �̸� ����
	MyInit(); // �ʱ� ����
	glutDisplayFunc(MyDisplay); // Display Event�� �Ͼ ������ MyDisplay ȣ���ϵ��� ���
	glutReshapeFunc(MyReshape); // ȭ���� ���� �׷��� �� ������ MyReshape ȣ���ϵ��� ���
	glutKeyboardFunc(MyKeyboard); // Keyboard Event�� �Ͼ ������ MyKeyboard ȣ���ϵ��� ���
	glutMainLoop(); // GLUT Event ó�� Loop ����
	return 0;
}