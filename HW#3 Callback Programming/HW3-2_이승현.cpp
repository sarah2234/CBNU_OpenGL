/*******************************************************************************************************/
/*                                     HW#3-2. Keyboard Callback ����II                                */
/*  �ۼ��� : �̽���                                                             ��¥ : 2021�� 10�� 6�� */
/*                                                                                                     */
/* ���� ���� :                                                                                         */
/* 1. Keyboard Callback�� �̿��Ͽ� �簢���� �������� �����Ѵ�.                                         */
/* 2. Special Keyboard Callback�� �̿��Ͽ� �簢���� ũ�⸦ �����Ѵ�.                                   */
/* 3. Display Callback�� �̿��Ͽ� �簢���� â ���� ����� �ʵ��� �Ѵ�.                               */
/* ��� :                                                                                              */
/* 1. ���콺�� ���� ��ư�� Ŭ���ϸ� �簢���� 0.01�� ���������� �����δ�.                               */
/* 2. ���콺�� ������ ��ư�� Ŭ���ϸ� �̵��ϰ� �ִ� �簢���� �����.                                   */
/* 3. â�� ũ�⸦ �ٲ��� �� �簢���� â �� �������� �Ѿ�� �ʵ��� �Ѵ�.                              */
/* 4. �簢���� ũ�⸦ ����Ͽ� â �� �������� �Ѿ�� �ʵ��� �Ѵ�.                                    */
/*******************************************************************************************************/

#include <GL/glut.h>

GLfloat moveX, moveY; // �簢���� ��ġ�� �����ϱ� ���� ����
GLfloat sizeX, sizeY; // �簢���� ũ�⸦ �����ϱ� ���� ����
GLint red = 1, blue = 1; // �簢���� ������ �����ϱ� ���� ����
GLfloat windowWidth, windowHeight; // ���� â ũ�⿡ ���� ���� ����

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

	// �簢���� ũ�Ⱑ â�� �Ѿ �� �簢���� ũ�⸦ â�� ũ�⸸ŭ ����
	if (sizeX > windowWidth / 2 - 0.5 || sizeY > windowHeight / 2 - 0.5)
	{
		sizeX = windowWidth / 2 - 0.5;
		sizeY = windowHeight / 2 - 0.5;
	}

	// �簢���� â�� �ٱ� ������ ��ġ�ϸ� �簢���� â�� ���ο� ��ġ�� �� �ֵ��� ����
	if (-0.5 + moveX - sizeX < -windowWidth / 2) // ���� �Ʒ� ���� x��ǥ�� �ٱ� ������ ���� �� ����
		moveX = 0.5 + sizeX - windowWidth / 2;
	if (-0.5 + moveY - sizeY < -windowHeight / 2) // ���� �Ʒ� ���� y ��ǥ�� �ٱ� ������ ���� �� ����
		moveY = 0.5 + sizeY - windowHeight / 2;
	if (0.5 + moveX + sizeX > windowWidth / 2) // ������ �� ���� x��ǥ�� �ٱ� ������ ���� �� ����
		moveX = -0.5 - sizeX + windowWidth / 2;
	if (0.5 + moveY + sizeY > windowHeight / 2) // ������ �� ���� y ��ǥ�� �ٱ� ������ ���� �� ����
		moveY = -0.5 - sizeY + windowHeight / 2;

	glBegin(GL_POLYGON); // �簢�� �׸��� ����
	glVertex3f(-0.5 + moveX - sizeX, -0.5 + moveY - sizeY, 0.0); // ���� �Ʒ�
	glVertex3f(0.5 + moveX + sizeX, -0.5 + moveY - sizeY, 0.0); // ������ �Ʒ�
	glVertex3f(0.5 + moveX + sizeX, 0.5 + moveY + sizeY, 0.0); // ������ ��
	glVertex3f(-0.5 + moveX - sizeX, 0.5 + moveY + sizeY, 0.0); // ���� ��
	glEnd(); // �簢�� �׸��� ������
	glFlush(); // ���� ���� ������ �������� ���������� ���μ��� ����
}

// ȭ���� ���� �׷��� �� �� �簢���� ������ �����ϵ��� ���߰�, �簢���� ��ġ�� �������ϴ� �Լ�
void MyReshape(int width, int height)
{
	GLfloat widthFactor = (GLfloat)width / (GLfloat)500;
	GLfloat heightFactor = (GLfloat)height / (GLfloat)500;
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// â�� ũ�Ⱑ �ٲ� �簢���� ũ��� ���ߵ��� ��
	glOrtho(-1 * widthFactor, 1 * widthFactor, -1 * heightFactor, 1 * heightFactor, -1, 1); 

	windowWidth = 2 * widthFactor; // â ���� ����
	windowHeight = 2 * heightFactor; // â ���� ����
}

// Ű���忡�� Ű�� �Է¹޾� ó���ϴ� �Լ�
void MyKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
	case 'A': // a�� A�� �Է¹����� �簢���� â�� ���ʸ鿡 ���� ������ �������� ������
		if(-0.5 + moveX - sizeX > -windowWidth / 2)
			moveX -= 0.1;
		break;
	case 'f':
	case 'F': // f�� F�� �Է¹����� �簢���� â�� �����ʸ鿡 ���� ������ ���������� ������
		if (0.5 + moveX + sizeX < windowWidth / 2)
			moveX += 0.1;
		break;
	case 'r':
	case 'R': // r�� R�� �Է¹����� �簢���� â�� �Ʒ��ʸ鿡 ���� ������ �Ʒ������� �����̰� �簢���� ���������� �ٲ�
		if (-0.5 + moveY - sizeY > -windowHeight / 2)
			moveY -= 0.1;
		red = 1;
		blue = 0;
		break;
	case 'v':
	case 'V': // v�� V�� �Է¹����� �簢���� â�� ���ʸ鿡 ���� ������ �������� ������
		if (0.5 + moveY + sizeY < windowHeight / 2)
			moveY += 0.1;
		break;
	case 'b':
	case 'B': // b�� B�� �Է¹����� �簢���� �Ķ������� �ٲ�
		red = 0;
		blue = 1;
		break;
	case 'Q':
		exit(0); break;
	case 'q':
		exit(0); break;
	case 27: // esc
		exit(0); break; // Q, q, esc�� ������ ����
	}
	glutPostRedisplay(); // ������ Display Event �߻���Ŵ
}

// Ư��Ű�� �Է¹޾� ó���ϴ� �Լ�
void MySpecialKey(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_PAGE_UP: // Pg Up Ű�� �Է� �޾��� ��
		if (sizeX < windowWidth / 2 - 0.5 && sizeY < windowHeight / 2 - 0.5)
		{
			sizeX += 0.05; // (0.1 / 2) ũ�⸸ŭ �翷, ���Ʒ� �÷��ֱ�
			sizeY += 0.05;
		}
		break;
	case GLUT_KEY_PAGE_DOWN:
		if (sizeX > -0.5 && sizeY > -0.5) // Pg Down Ű�� �Է� �޾��� ��
		{
			sizeX -= 0.05; // (0.1 / 2) ũ�⸸ŭ �翷, ���Ʒ� ���̱�
			sizeY -= 0.05;
		}
		break;
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
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);
	glutSpecialFunc(MySpecialKey);
	glutMainLoop(); // GLUT Event ó�� Loop ����
	return 0;
}