/*******************************************************************************************************/
/*                                       HW#4-1 : �κ� ��-�� �𵨸�                                    */
/*  �ۼ��� : �̽���                                                            ��¥ : 2021�� 10�� 26�� */
/*                                                                                                     */
/* ���� ���� :                                                                                         */
/* ��� ������ �̿��Ͽ� �κ��� �հ� ���� �����Ѵ�.                                                     */
/* ��� :                                                                                              */
/* 1. 1�� ������ ù ��° �հ����� �����δ�.                                                            */
/* 2. 2�� ������ �� ��° �հ����� �����δ�.                                                            */
/* 3. 3�� ������ �� ��° �հ����� �����δ�.                                                            */
/* 4. 4�� ������ ��� �հ����� �����δ�.                                                               */
/* 5. s �Ǵ� S�� ������ �����̴� �հ����� �����.                                                      */
/* 6. ���콺 ��Ŭ���� �ϸ� ���, �Ȳ�ġ �� ��� �հ����� �������� Robot Arm�� ȸ���Ѵ�.                */
/* 7. ���콺 ��Ŭ���� �ϸ� ���, �Ȳ�ġ �� ��� �հ����� �������� Roboat Arm�� ���� �ڼ��� ���ư���.   */
/*******************************************************************************************************/

#include <gl/glut.h>
#include <math.h>
#define PI 3.14159265

static float shoulder = 0, elbow = 0; // ����� �Ȳ�ġ�� ȸ����ų ���� ����
static float finger[3][3]; // ������ �հ��� ���� ȸ����ų ���� ����
static bool shoulderFlip, elbowFlip, shoulderFlipBackward, elbowFlipBackward; // ����� �Ȳ�ġ�� ȸ����ų�� ��Ʈ���ϴ� ����
static bool fingerFlip[3], fingerFlipBackward[3], fingerFlipToggle[3]; // �հ����� ��� �������� ��Ʈ���ϴ� ����

// �ʱ� ����
void MyInit()
{
	glClearColor(0, 0, 0, 1); // ���������� ȭ�� �����
	glShadeModel(GL_FLAT); // flat shading���� ���� (������ �׸�)
	for (int i = 0; i < 3; i++) // �ʱ� ȭ�鿡���� �հ����� �������� �ʵ��� ��
	{
		fingerFlip[i] = false; 
		fingerFlipBackward[i] = false;
	}
	shoulderFlip = false; // �ʱ� ȭ�鿡���� ����� �������� �ʵ��� ��
	elbowFlip = false; // �ʱ� ȭ�鿡���� �Ȳ�ġ�� �������� �ʵ��� ��
}

// Display Event�� �߻����� �� ȣ��Ǵ� callback �Լ�
void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT); // ȭ�鿡�� �׸� �����
	glMatrixMode(GL_MODELVIEW); // �𵨺� ��� ����
	glLoadIdentity(); // �𵨺� ��ĸ� �׵� ��ķ� �ʱ�ȭ
	glPushMatrix(); // ���� ��ȯ ����� ��� ���ÿ� ����

	glTranslatef(-2.0, 0.0, 0.0); // Robot Arm�� ��ü ��ġ ����
	glRotatef(20, 1.0, 0.0, 0.0); // x���� �������� 20�� ȸ�� (Robot Arm�� �� �� ��ü������ ���� ����)
	glPushMatrix(); // ���� ��ȯ ����� ��� ���ÿ� ����

	// ��� �Ʒ�
	glTranslatef(-1.0, 0.0, 0.0); // Pivot ���� �� ��ü �̵�
	glRotatef((GLfloat)shoulder, 0.0, 1.0, 0.0); // ������ shoulder�Ƹ�ŭ ȸ��
	glTranslatef(1.0, 0.0, 0.0); // Pivot���� ������ ��ġ�� �������� �̵�
	glPushMatrix(); // ���� ��ȯ ����� ��� ���ÿ� ����
	glColor3f(1.0, 1.0, 1.0); // ������� ĥ�ϱ�
	glScalef(2.0, 0.4, 1.0); // ���� ũ�� ����
	glutWireCube(1.0); // ���� ��ȯ ����� �������� 3D ����ü �׸��� 
	glPopMatrix(); // ���� ��ȯ ����� ��� ���ؿ��� ����

	// �Ȳ�ġ �Ʒ�
	glTranslatef(1.0, 0.0, 0.0); // �� ��ġ ����
	glRotatef((GLfloat)elbow, 0.0, 1.0, 0.0); // �Ʒ����� ������ �ݸ�ŭ �̵��� ������ elbow�Ƹ�ŭ ȸ��
	glTranslatef(1.0, 0.0, 0.0); // x�࿡�� 1.0��ŭ ��ü �̵� (�Ʒ����� x�� ������ ��)
	glPushMatrix(); // ���� ��ȯ ����� ��� ���ÿ� ����
	glColor3f(1.0, 1.0, 1.0); // ������� ĥ�ϱ�
	glScalef(2.0, 0.4, 1.0); // �Ʒ��� ũ�� ����
	glutWireCube(1.0); // ���� ��ȯ ����� �������� 3D ����ü �׸���
	glPopMatrix(); // ���� ��ȯ ����� ��� ���ؿ��� ����

	// �հ��� �׸���
	glTranslatef(0.6, 0.0, 0.0); // �հ����� ���������� ���� �� �κп� ��ġ�ϵ��� ��
	glPushMatrix(); // ���� ��ȯ ����� ��� ���ÿ� ����
	
	// ��� �հ����� ù ��° ����
	glTranslatef(0.4, 0.0, 0.0); // ���� �հ��� ���� ���� �հ����� �ٸ� ������ ���� ������ ��
	glRotatef(finger[1][0], 0.0, 1.0, 0.0); // ��� �հ����� ù ��° ���� finger[1][0]�Ƹ�ŭ ȸ��
	glTranslatef(0.4, 0.0, 0.0); // �հ��� ������ �ݸ�ŭ �̵��Ͽ� ������ ���� ���� ���� ��ġ (elbow�� ȸ���Կ� ���� �հ����� ��ġ�� �����ϵ��� ��)
	glPushMatrix(); // ���� ��ȯ ����� ��� ���ÿ� ����
	glScalef(0.8, 0.1, 0.25); // �հ��� ���� ũ�� ����
	glutWireCube(1.0); // �հ��� ���� �׸���
	glPopMatrix(); // ���� ��ȯ ����� ��� ���ؿ��� ����
	
	// ��� �հ����� �� ��° ����
	glTranslatef(0.4, 0.0, 0.0); // ���� �հ��� ���� ���� �հ����� �ٸ� ������ ���� ������ ��
	glRotatef(finger[1][1], 0.0, 1.0, 0.0); // ��� �հ����� �� ��° ���� finger[1][1]�Ƹ�ŭ ȸ��
	glTranslatef(0.4, 0.0, 0.0); // �հ��� ������ �ݸ�ŭ �̵��Ͽ� ������ ���� ���� ���� ��ġ
	glPushMatrix(); // ���� ��ȯ ����� ��� ���ÿ� ����
	glScalef(0.8, 0.1, 0.25); // �հ��� ���� ũ�� ����
	glutWireCube(1.0); // �հ��� ���� �׸���
	glPopMatrix(); // ���� ��ȯ ����� ��� ���ؿ��� ����

	// ��� �հ����� �� ��° ����
	glTranslatef(0.4, 0.0, 0.0); // ���� �հ��� ���� ���� �հ����� �ٸ� ������ ���� ������ ��
	glRotatef(finger[1][2], 0.0, 1.0, 0.0); // ��� �հ����� �� ��° ���� finger[1][2]�Ƹ�ŭ ȸ��
	glTranslatef(0.4, 0.0, 0.0); // �հ��� ������ �ݸ�ŭ �̵��Ͽ� ������ ���� ���� ���� ��ġ
	glScalef(0.8, 0.1, 0.25); // �հ��� ���� ũ�� ����
	glutWireCube(1.0); // �հ��� ���� �׸���
	glPopMatrix(); // ���� ��ȯ ����� ��� ���ÿ��� ����
	glPushMatrix(); // ���� ��ȯ ����� ��� ���ÿ� ����

	// ���� �հ��� �׸���
	glRotatef(20, 0.0, 0.0, 1.0); // ���� �հ����� ��� �հ������� 20�� ���� �ֵ��� ��
	glPushMatrix(); // ���� ��ȯ ����� ��� ���ÿ� ����

	// ���� �հ����� ù ��° ����
	glTranslatef(0.4, 0.0, 0.0); // ���� �հ��� ���� ���� �հ����� �ٸ� ������ ���� ������ ��
	glRotatef(finger[0][0], 0.0, 1.0, 0.0); // ���� �հ����� ù ��° ���� finger[0][0]�Ƹ�ŭ ȸ��
	glTranslatef(0.4, 0.0, 0.0); // �հ��� ������ �ݸ�ŭ �̵��Ͽ� ������ ���� ���� ���� ��ġ
	glPushMatrix(); // ���� ��ȯ ����� ��� ���ÿ� ����
	glScalef(0.8, 0.1, 0.25); // �հ��� ���� ũ�� ����
	glutWireCube(1.0); // �հ��� ���� �׸���
	glPopMatrix(); // ���� ��ȯ ����� ��� ���ؿ��� ����

	// ���� �հ����� �� ��° ����
	glTranslatef(0.4, 0.0, 0.0); // ���� �հ��� ���� ���� �հ����� �ٸ� ������ ���� ������ ��
	glRotatef(finger[0][1], 0.0, 1.0, 0.0); // ���� �հ����� �� ��° ���� finger[0][1]�Ƹ�ŭ ȸ��
	glTranslatef(0.4, 0.0, 0.0); // �հ��� ������ �ݸ�ŭ �̵��Ͽ� ������ ���� ���� ���� ��ġ
	glPushMatrix(); // ���� ��ȯ ����� ��� ���ÿ� ����
	glScalef(0.8, 0.1, 0.25); // �հ��� ���� ũ�� ����
	glutWireCube(1.0); // �հ��� ���� �׸���
	glPopMatrix(); // ���� ��ȯ ����� ��� ���ؿ��� ����

	// ���� �հ����� �� ��° ����
	glTranslatef(0.4, 0.0, 0.0); // ���� �հ��� ���� ���� �հ����� �ٸ� ������ ���� ������ ��
	glRotatef(finger[0][2], 0.0, 1.0, 0.0); // ���� �հ����� �� ��° ���� finger[0][2]�Ƹ�ŭ ȸ��
	glTranslatef(0.4, 0.0, 0.0); // �հ��� ������ �ݸ�ŭ �̵��Ͽ� ������ ���� ���� ���� ��ġ
	glPushMatrix(); // ���� ��ȯ ����� ��� ���ÿ� ����
	glScalef(0.8, 0.1, 0.25); // �հ��� ���� ũ�� ����
	glutWireCube(1.0); // �հ��� ���� �׸���
	glPopMatrix(); // ���� ��ȯ ����� ��� ���ؿ��� ����
	glPopMatrix(); // ���� ��ȯ ����� ��� ���ؿ��� ����
	glPopMatrix(); // ���� ��ȯ ����� ��� ���ؿ��� ����

	// �Ʒ��� �հ��� �׸���
	glRotatef(-20, 0.0, 0.0, 1.0); // �Ʒ��� �հ����� ��� �հ������� 20�� �Ʒ��� �ֵ��� ��
	glPushMatrix(); // ���� ��ȯ ����� ��� ���ÿ� ����

	// �Ʒ��� �հ����� ù ��° ����
	glTranslatef(0.4, 0.0, 0.0); // ���� �հ��� ���� ���� �հ����� �ٸ� ������ ���� ������ ��
	glRotatef(finger[2][0], 0.0, 1.0, 0.0); // �Ʒ��� �հ����� ù ��° ���� finger[2][0]�Ƹ�ŭ ȸ��
	glTranslatef(0.4, 0.0, 0.0); // �հ��� ������ �ݸ�ŭ �̵��Ͽ� ������ ���� ���� ���� ��ġ
	glPushMatrix(); // ���� ��ȯ ����� ��� ���ÿ� ����
	glScalef(0.8, 0.1, 0.25); // �հ��� ���� ũ�� ����
	glutWireCube(1.0); // �հ��� ���� �׸���
	glPopMatrix(); // ���� ��ȯ ����� ��� ���ؿ��� ����

	// �Ʒ��� �հ����� �� ��° ����
	glTranslatef(0.4, 0.0, 0.0); // ���� �հ��� ���� ���� �հ����� �ٸ� ������ ���� ������ ��
	glRotatef(finger[2][1], 0.0, 1.0, 0.0); // �Ʒ��� �հ����� �� ��° ���� finger[2][1]�Ƹ�ŭ ȸ��
	glTranslatef(0.4, 0.0, 0.0); // �հ��� ������ �ݸ�ŭ �̵��Ͽ� ������ ���� ���� ���� ��ġ
	glPushMatrix(); // ���� ��ȯ ����� ��� ���ÿ� ����
	glScalef(0.8, 0.1, 0.25); // �հ��� ���� ũ�� ����
	glutWireCube(1.0); // �հ��� ���� �׸���
	glPopMatrix(); // ���� ��ȯ ����� ��� ���ؿ��� ����

	// �Ʒ��� �հ����� �� ��° ����
	glTranslatef(0.4, 0.0, 0.0); // ���� �հ��� ���� ���� �հ����� �ٸ� ������ ���� ������ ��
	glRotatef(finger[2][2], 0.0, 1.0, 0.0); // �Ʒ��� �հ����� �� ��° ���� finger[2][2]�Ƹ�ŭ ȸ��
	glTranslatef(0.4, 0.0, 0.0); // �հ��� ������ �ݸ�ŭ �̵��Ͽ� ������ ���� ���� ���� ��ġ
	glPushMatrix(); // ���� ��ȯ ����� ��� ���ÿ� ����
	glScalef(0.8, 0.1, 0.25); // �հ��� ���� ũ�� ����
	glutWireCube(1.0); // �հ��� ���� �׸���
	glPopMatrix(); // ���� ��ȯ ����� ��� ���ؿ��� ����
	glPopMatrix(); // ���� ��ȯ ����� ��� ���ؿ��� ����
	glPopMatrix(); // ���� ��ȯ ����� ��� ���ؿ��� ����
	glPopMatrix(); // ���� ��ȯ ����� ��� ���ؿ��� ����
	glPopMatrix(); // ���� ��ȯ ����� ��� ���ؿ��� ����
	glPopMatrix(); // ���� ��ȯ ����� ��� ���ؿ��� ���� (�׵� ��ĸ� ����)

	glutSwapBuffers(); // ���� ���ۿ� �ĸ� ���۸� ��ü�Ͽ� �ĸ� ���ۿ� �غ��ص� �׸��� ��Ÿ��
}

// ȭ���� �ٽ� �׷��� �� �� ȣ��Ǵ� callback �Լ�
void MyReshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); // ���� ����
	glMatrixMode(GL_PROJECTION); // ���� ��� ����
	glLoadIdentity(); // ���� ����� �׵� ��ķ� �ʱ�ȭ
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0); // ���� ���� ����
	glTranslatef(0.0, 0.0, -5.0); // z�࿡�� -5.0��ŭ �̵�
}

void MyIdle()
{
	if (shoulderFlip) // ����� ������ �����̶�� ���ð� ����
	{
		if (shoulder < 20)
		{
			shoulder += 0.1; // 20���� �Ǳ� ������ ����� ������ �����̱�
		}
	}
	else if (shoulderFlipBackward) // ����� ������ �����̶�� ���ð� ����
	{
		if (0 < shoulder)
		{
			shoulder -= 0.1; // 0���� �Ǳ� ������ ����� ������ �����̱�
		}
	}

	if (elbowFlip) // ���� ������ ������� ���ð� ����
	{
		if (elbow < 20)
		{
			elbow += 0.1; // 20���� �Ǳ� ������ ���� ������ ����
		}
	}
	else if (elbowFlipBackward) // ���� ������ ��ġ��� ���ð� ����
	{
		if (0 < elbow)
		{
			elbow -= 0.1; // 0���� �Ǳ� ������ ���� ��ġ��
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (finger[i][0] >= 20 && fingerFlip[i] && fingerFlipToggle[i])
		{
			// �հ����� ���������� �������� �ϰ�, �հ����� ���� ��ŭ ������ �� �հ����� ��ġ���� ��
			fingerFlipBackward[i] = true;
			fingerFlip[i] = false;
		}
		else if (finger[i][0] <= 0 && fingerFlipBackward[i] && fingerFlipToggle[i])
		{
			// �հ����� ���������� �������� �ϰ�, �հ����� ������ ��ŭ �������� �� �հ����� ������ ��
			fingerFlipBackward[i] = false;
			fingerFlip[i] = true;
		}

		for (int j = 0; j < 3 && finger[i][j] < 20 && fingerFlip[i]; j++)
		{
			finger[i][j] += 0.1; // �հ����� 20������ ����
		}

		for (int j = 0; j < 3 && finger[i][j] > 0 && fingerFlipBackward[i]; j++)
		{
			finger[i][j] -= 0.1; // �հ����� 0������ ��ġ��
		}
	}

	glutPostRedisplay(); // Display Event �߻���Ű��
}

// Keyboard Event�� �߻����� �� ȣ��Ǵ� callback �Լ�
void MyKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		if (fingerFlipToggle[0])
			break; // �̹� �հ����� ���������� �����̰� ������ �ǳʶٱ�
		fingerFlip[0] = true; // ���� �հ��� ����
		fingerFlipBackward[0] = false; // ���� �հ��� ����
		fingerFlipToggle[0] = true; // ���� �հ����� ���������� �����̱�
		break;
	case '2':
		if (fingerFlipToggle[1])
			break; // �̹� �հ����� ���������� �����̰� ������ �ǳʶٱ�
		fingerFlip[1] = true; // ��� �հ��� ����
		fingerFlipBackward[1] = false; // ��� �հ��� ����
		fingerFlipToggle[1] = true; // ��� �հ����� ���������� �����̱�
		break;
	case '3':
		if (fingerFlipToggle[2])
			break; // �̹� �հ����� ���������� �����̰� ������ �ǳʶٱ�
		fingerFlip[2] = true; // �Ʒ��� �հ��� ����
		fingerFlipBackward[2] = false; // �Ʒ��� �հ��� ����
		fingerFlipToggle[2] = true; // �Ʒ��� �հ����� ���������� �����̱�
		break;
	case '4':
		for (int i = 0; i < 3; i++)
		{
			// ��� �հ����� ���� ���������� ������� ���
			if (!fingerFlipToggle[i]) // �հ����� ���������� �����̰� ������ �ش� �հ��� �ǳʶٱ�
			{
				fingerFlip[i] = true; 
				fingerFlipBackward[i] = false;
				fingerFlipToggle[i] = true;
			}
		}
		break;
	case 'S':
	case 's':
		// ��� �հ����� ���� ���߶�� ���
		for (int i = 0; i < 3; i++)
		{
			fingerFlip[i] = false;
			fingerFlipBackward[i] = false;
			fingerFlipToggle[i] = false;
		}
		break;
	}
}

// Mouse Event�� �߻����� �� ȣ��Ǵ� callback �Լ�
void MyMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		// ���콺 ��Ŭ���� ���� �� ���, �Ȳ�ġ, ��� �հ����� ������ �����̱�
		shoulderFlip = true;
		shoulderFlipBackward = false;
		elbowFlip = true;
		elbowFlipBackward = false;
		for (int i = 0; i < 3; i++)
		{
			fingerFlip[i] = true;
			fingerFlipBackward[i] = false;
		}
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		// ���콺 ��Ŭ���� ���� �� ���, �Ȳ�ġ, ��� �հ����� �����·� ������
		shoulderFlip = false;
		shoulderFlipBackward = true;
		elbowFlip = false;
		elbowFlipBackward = true;
		for (int i = 0; i < 3; i++)
		{
			fingerFlip[i] = false;
			fingerFlipBackward[i] = true;
		}
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); // Window OS�� ���� ���� & GLUT Library �ʱ�ȭ
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // Display Mode ���� (Ʈ�� �÷� ��� & 2���� ���� ���)
	glutInitWindowPosition(100, 100); // ������ ��ġ ����
	glutInitWindowSize(800, 600); // ������ ũ�� ����
	glutCreateWindow("Robot Arm"); // ������ ���� �� �̸� ����
	MyInit(); // �ʱ�ȭ ���� ����
	glutDisplayFunc(MyDisplay); // Display Event�� �߻��� ������ MyDisplay ȣ���ϵ��� ���
	glutReshapeFunc(MyReshape); // ȭ���� �ٽ� �׷��� �� ������ MyReshape ȣ���ϵ��� ���
	glutKeyboardFunc(MyKeyboard); // Keyboard Event�� �߻��� ������ MyKeyboard ȣ���ϵ��� ���
	glutMouseFunc(MyMouse); // Mouse Event�� �߻��� ������ MyMouse ȣ���ϵ��� ���
	glutIdleFunc(MyIdle); // ó���ϰ� �ִ� �̺�Ʈ�� ���� �� MyIdle ȣ���ϵ��� ���
	glutMainLoop(); // GLUT Event ó�� Loop ����
	return 0;
}