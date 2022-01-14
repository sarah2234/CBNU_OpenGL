/*******************************************************************************************************/
/*                                       HW#5-2 : �𵨺� ��ȯ ���� �ǽ�                                */
/*  �ۼ��� : �̽���                                                            ��¥ : 2021�� 11�� 01�� */
/*                                                                                                     */
/* ���� ���� :                                                                                         */
/* 1. �翷, �Ʒ�, ���� ������ �پ��� �������� �𵨸��� ��ü�� ������ �� �ֵ��� �����Ѵ�.               */
/* ��� :                                                                                              */
/* 1. �� Ű�� ������ Camera�� Y�� ��ǥ�� 0.01�� ���������� ����                                        */
/* 2. �� Ű�� ������ Camera�� Y�� ��ǥ�� 0.01�� ���������� ����                                        */
/* 3. �� Ű�� ������ Camera�� X�� ��ǥ�� 0.01�� ���������� ����                                        */
/* 4. �� Ű�� ������ Camera�� X�� ��ǥ�� 0.01�� ���������� ����                                        */
/* 5. Home Ű�� ������ Camera�� Z�� ��ǥ�� 0.01�� ���������� ����                                      */
/* 6. End Ű�� ������ Camera�� Z�� ��ǥ�� 0.01�� ���������� ����                                       */
/* 7. a �Ǵ� A Ű�� ������ ����(Focus)�� X�� ��ǥ�� 0.01�� ���������� ����                             */
/* 8. f �Ǵ� F Ű�� ������ ����(Focus)�� X�� ��ǥ�� 0.01�� ���������� ����                             */
/* 9. r �Ǵ� R Ű�� ������ ����(Focus)�� Y�� ��ǥ�� 0.01�� ���������� ����                             */
/* 10. v �Ǵ� V Ű�� ������ ����(Focus)�� Y�� ��ǥ�� 0.01�� ���������� ����                            */
/* 11. z �Ǵ� Z Ű�� ������ ����(Focus)�� Z�� ��ǥ�� 0.01�� ���������� ����                            */
/* 12. t �Ǵ� T Ű�� ������ ����(Focus)�� Z�� ��ǥ�� 0.01�� ���������� ����                            */
/* 13. 1 Ű�� ������ �κ��� �Ʒ��� ����                                                                */
/* 14. 2 Ű�� ������ �κ��� ���� ����                                                                  */
/* 15. 3 Ű�� ������ �κ��� ������ ����                                                                */
/* 16. 4 Ű�� ������ �κ��� �������� ����                                                              */
/* 17: s �Ǵ� S Ű�� ������ �ʱ� ��ȯ ���·� �ǵ��ư�                                                  */
/* 18. f5 Ű�� ������ ī�޶� �� ���� ��ġ�� �ʱ� ȭ�� �������� �ǵ����� ī�޶��� �������� ����         */
/* 19. Menu Callback�� ���� �κ��� �Ӹ�, ��, �ٸ��� ������ (4-2 ����)                                  */
/*******************************************************************************************************/

#include <gl/glut.h>

bool headMove, leftArmMove, rightArmMove, leftLegMove, rightLegMove; // ������ ��ü ������ �������� �����ϱ� ���� ����
bool headMoveToggle, leftArmMoveToggle, rightArmMoveToggle, leftLegMoveToggle, rightLegMoveToggle; // ������ ��ü ������ �������� �����ϱ� ���� ����
GLfloat head, leftArm[2], rightArm[2], leftLeg, rightLeg, body; // ������ ��ü ������ �����̴� ������ ���ϱ� ���� ����

bool moveCameraX[2], moveCameraY[2], moveCameraZ[2], moveFocusX[2], moveFocusY[2], moveFocusZ[2]; // ī�޶� �� ������ ��ġ�� �����ϴ� ������
GLdouble cameraX, cameraY, cameraZ, focusX, focusY, focusZ; // ī�޶� �� ������ ��ġ�� �����ϴ� ������

// �޴��� ������
void MyMenu(int value)
{
	switch (value)
	{
	case 1:
		headMove = true; // ù ��° �޴� Ŭ�� �� �Ӹ��� ������
		headMoveToggle = true; // �Ӹ��� �������ٰ� ���� ���·� ���ƿ����� ��
		break;
	case 2:
		rightArmMove = true; // �� ��° �޴� Ŭ�� �� �������� ������
		rightArmMoveToggle = true; // �������� �������ٰ� ���� ���·� ���ƿ����� ��
		break;
	case 3:
		leftArmMove = true; // �� ��° �޴� Ŭ�� �� ������ ������
		leftArmMoveToggle = true; // ������ �������ٰ� ���� ���·� ���ƿ����� ��
		break;
	case 4:
		rightLegMove = true; // �� ��° �޴� Ŭ�� �� �����ٸ��� ������
		rightLegMoveToggle = true; // �����ٸ��� �������ٰ� ���� ���·� ���ƿ����� ��
		break;
	case 5:
		leftLegMove = true; // �ټ� ��° �޴� Ŭ�� �� �޴ٸ��� ������
		leftLegMoveToggle = true; // �޴ٸ��� �������ٰ� ���� ���·� ���ƿ����� ��
		break;
	}
}

// �ʱ� ȭ�� ����
void MyInit()
{
	// �ʱ� ȭ�鿡�� ��� ��ü �κ��� �������� �ʵ��� ��
	headMove = false;
	leftArmMove = false;
	rightArmMove = false;
	leftLegMove = false;
	rightLegMove = false;
	headMoveToggle = false;
	leftArmMoveToggle = false;
	rightArmMoveToggle = false;
	leftLegMoveToggle = false;
	rightLegMoveToggle = false;

	// �ʱ� ȭ�鿡���� �Ӹ�, ��, �ٸ� ����
	head = 0;
	leftArm[0] = -20;
	leftArm[1] = 0;
	rightArm[0] = 20;
	rightArm[1] = 0;
	leftLeg = -20;
	rightLeg = 20;
	body = 0;

	// �ʱ� ȭ�鿡�� ī�޶�� ������ �������� �ʵ��� ����
	// '������[0] = true'�� �� ��ǥ�迡�� ��� ������, '������[1] = true'�� �� ���� ������ �̵�
	for (int i = 0; i < 2; i++)
	{
		moveCameraX[i] = false;
		moveCameraY[i] = false;
		moveCameraZ[i] = false;
		moveFocusX[i] = false;
		moveFocusY[i] = false;
		moveFocusZ[i] = false;
	}

	// �ʱ� ȭ�鿡���� ī�޶� �� ���� ��ġ ����
	cameraX = 0.0;
	cameraY = -3.5;
	cameraZ = 3.5;
	focusX = 0.0;
	focusY = 0.0;
	focusZ = 0.0;

	GLint menuID = glutCreateMenu(MyMenu); // �޴� ����
	glutAddMenuEntry("Move Head", 1); // ù ��° �޴� ����
	glutAddMenuEntry("Move Right Arm", 2); // �� ��° �޴� ����
	glutAddMenuEntry("Move Left Arm", 3); // �� ��° �޴� ����
	glutAddMenuEntry("Move Right Leg", 4); // �� ��° �޴� ����
	glutAddMenuEntry("Move Left Leg", 5); // �ټ� ��° �޴� ����
	glutAttachMenu(GLUT_RIGHT_BUTTON); // ���콺 ��Ŭ���� �ϸ� �޴��� ��Ÿ��
}

//
void MyDisplay()
{
	GLfloat mat_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat mat_specular[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat mat_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat light_position[] = { 10.0f, 15.0f, 10.0f, 0.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position); // 0�� ���� ��ġ ���ϱ�
	glLightfv(GL_LIGHT0, GL_AMBIENT, mat_ambient); // �ֺ��� ���ϱ�
	glLightfv(GL_LIGHT0, GL_DIFFUSE, mat_diffuse); // �л걤 ���ϱ�
	glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular); // �ݻ籤 ���ϱ�

	glEnable(GL_LIGHTING); // ���� ���
	glEnable(GL_LIGHT0); // 0�� ���� ���
	glEnable(GL_COLOR_MATERIAL); // ��ü�� ������ �������� ��

	glEnable(GL_DEPTH_TEST); // ���� ����
	glFrontFace(GL_CCW); // �ո� ���� 
	glEnable(GL_CULL_FACE); // �� ������ ������ �ʴ� �޺κ� ����


	glClearColor(0.0, 0.0, 0.0, 0.0); // ���������� ȭ�� �����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // �� ����, ���� ���۸� �����Ͽ� ȭ�鿡�� �׸� �����
	glMatrixMode(GL_MODELVIEW); // �𵨺� ��� ����
	glLoadIdentity(); // �𵨺� ����� �׵� ��ķ� �ʱ�ȭ
	gluLookAt(cameraX, cameraY, cameraZ, focusX, focusY, focusZ, 0.0, 1.0, 0.0); // ���� ��ǥ�� ���� (ī�޶��� ��ġ�� ���� ����)

	glTranslatef(0.0, body, 0.0); // �ٸ� �����ӿ� ���� �κ��� ��ġ ����
	glPushMatrix(); // ���� ���� ��ȯ ��� ����
	glColor3f(0.2, 0.5, 0.5); // �� ���� ����
	glScalef(1.0, 1.5, 1.0); // �� ũ�� ����
	glutSolidCube(1.0); // ��
	glPopMatrix(); // �� �׸��� ��
	glPushMatrix(); // �� ��ű��� ���� ��ȯ ��� ����
	glTranslatef(0.0, 0.2, 0.5); // ��ű��� ��ġ ����
	glColor3f(0.5, 0.0, 0.0); // ��ű� ���� ����
	glutSolidTorus(0.05, 0.3, 20, 20); // �� ���κ��� ��ű� �׸���
	glRotatef(45, 0, 0, 1); // �� ���κ��� ��ű� ȸ��(���̾� ���)
	glutSolidCube(0.3); // �� ���κ��� ��ű� �׸���
	glPopMatrix(); // �� ���κ��� ��ű��� ���� ��ȯ ��� ����
	glPushMatrix(); // �� �Ʒ��κ��� ��ű��� ���� ��ȯ ��� ����
	glTranslatef(0.3, -0.5, 0.6); // ��ű��� ��ġ ����
	glColor3f(0.0, 0.3, 0.3); // ��ű��� ���� ����
	glutSolidCube(0.1); // �� �Ʒ��κ��� ��ű� �׸���
	glPopMatrix(); // �� ��ű��� ���� ��ȯ ��� ����

	glPushMatrix(); // �� �׸���
	glTranslatef(0.0, 1.5 / 2 + 0.2 / 2, 0.0); // �� ��ġ ����(���� ���� ��ġ��)
	glColor3f(0.1, 0.3, 0.3); // �� ���� ����
	glutSolidCube(0.2); // ��
	glTranslatef(0.0, 1.0 / 2, 0.0); // �Ӹ��� �� ���� ��ġ�ϵ��� ��
	glTranslatef(0.0, -0.2 / 2 - 1.0 / 2, 0.0); // ȸ�� �� ���� ��ġ�� ���ƿ�
	glRotatef(head, 0, 0, 1); // �� ������ �Ӹ��� head����ŭ ȸ��
	glTranslatef(0.0, 0.2 / 2 + 1.0 / 2, 0.0); // ȸ���ϱ� ���� pivot ����
	glColor3f(0.2, 0.5, 0.5); // �Ӹ� ���� ����
	glutSolidCube(1.0); // �Ӹ�
	glPushMatrix(); // �Ӹ��� �����ӿ� ���� ��, �� ��ġ�� �޸��ϵ��� �Ӹ��� ���� ��ȯ��� ����
	glTranslatef(-0.3, 0.0, 1.0 / 2); // �Ӹ��� �ִ� ���� ��ġ ����
	glRotatef(90, 0, 0, 1); // Torus�� 90�� ȸ��
	glColor3f(0.5, 0.5, 1.0); // �Ķ��� �� �׵θ�
	glutSolidTorus(0.08, 0.14, 20, 20); // ���� �� �׸���
	glColor3f(0.0, 0.0, 0.0); // ���� ��
	glutSolidSphere(0.08, 20, 20); // ���� ������ �׸���
	glColor3f(1.0, 1.0, 1.0); // ��� ����
	glTranslatef(0.0, 0.0, 0.055); // ������ ������ ������ ���̵��� ��
	glutSolidSphere(0.03, 20, 20); // ���� ���� �׸���
	glPopMatrix(); // ���� ���� ���� ��ȯ ��� ����
	glPushMatrix(); // ������ ���� ���� ��ȯ ��� ����
	glTranslatef(0.3, 0.0, 1.0 / 2); // �Ӹ��� �ִ� ���� ��ġ ����
	glRotatef(90, 0, 0, 1); // Torus�� 90�� ȸ��
	glColor3f(0.5, 0.5, 1.0); // �Ķ��� �� �׵θ�
	glutSolidTorus(0.08, 0.14, 20, 20); // ������ �� �׸���
	glColor3f(0.0, 0.0, 0.0); // ���� ��
	glutSolidSphere(0.08, 20, 20); // ������ ������ �׸���
	glColor3f(1.0, 1.0, 1.0); // ��� ����
	glTranslatef(0.0, 0.0, 0.055); // ������ ������ ������ ���̵��� ��
	glutSolidSphere(0.03, 20, 20); // ������ ���� �׸���
	glPopMatrix(); // ������ ���� ���� ��ȯ ��� ����
	glPushMatrix(); // �Կ� ���� ��ȯ ��� ����
	glTranslatef(0.0, -0.25, 1.0 / 2 + 0.1 / 2); // �Ӹ��� �ִ� ���� ��ġ ����
	glScalef(0.3, 0.1, 0.1); // �� ũ�� ����
	glColor3f(0.5, 0.0, 0.0); // ������ ��
	glutSolidCube(1.0); // �� �׸���
	glPopMatrix(); // �Կ� ���� ��ȯ ��� ����
	glPopMatrix(); // �� ��ġ�� ���� ��ȯ ��� ����

	glColor3f(0.2, 0.5, 0.5); // �� ���� ����
	glPushMatrix(); // �� �׸���
	glTranslatef(-1.0 / 2 - 0.15 / 2, 0.3, 0.0); // �� ��ġ ����(���� ���ʿ� �پ�����)
	glTranslatef(0.15 / 2, 0.35 / 2, 0.0); // ȸ�� �� ���� �ڸ��� ���ƿ�
	glRotatef(leftArm[0], 0, 0, 1); // �� ������ leftArm[0]����ŭ ������ ���� �����̱�
	glTranslatef(-0.15 / 2, -0.35 / 2, 0.0); // ������ ���� ����� pivot���� �Ͽ� ȸ��
	glPushMatrix(); // ������ ���� �κп� ���� ��ȯ ��� ����
	glScalef(0.15, 0.35, 0.15); // ������ ũ�� ����
	glutSolidCube(1.0); // ����(����) �׸���
	glPopMatrix(); // ������ ���� �κ��� ũ�⿡ ���� ������ ��ȯ ��Ŀ��� ����
	glPushMatrix(); // ������ ���� �κ��� ��ȯ ��Ŀ� ���� ������ ������ ä�� ������ �Ʒ��� �κ� �׸���
	glTranslatef(0.0, -0.35, 0.0); // �� ��ġ ����(�� ���κ��� �Ʒ��� �پ�����)
	glTranslatef(0.15 / 2, 0.35 / 2, 0.0); // ȸ�� �� ���� �ڸ��� ���ƿ�
	glRotatef(leftArm[1], 0, 0, 1); // ������ �Ʒ����� leftArm[1]����ŭ �Ʒ����� ���� �����̱�
	glTranslatef(-0.15 / 2, -0.35 / 2, 0.0); // ������ ���� ����� pivot���� �Ͽ� ȸ��
	glPushMatrix(); // ������ �Ʒ��� �κп� ���� ��ȯ ��� ����
	glScalef(0.15, 0.35, 0.15); // ������ ũ�� ����
	glutSolidCube(1.0); // ����(�Ʒ���) �׸���
	glPopMatrix(); // ������ �Ʒ��� �κ��� ũ�⿡ ���� ������ ��ȯ ��Ŀ��� ����
	glTranslatef(0.0, -0.35 / 2, 0.0); // �޼��� ������ ���� ��ġ�ϵ��� ��
	glutSolidCube(0.2); // �޼� �׸���
	glTranslatef(-0.4, -0.2, 0.0); // �������� ��ġ ����
	glRotatef(180, 0, 1, 0); // �����ڸ� y�� �������� 180�� ȸ��
	glColor3f(0.5, 0.2, 0.3); // �������� ���� ����
	glutSolidTeapot(0.4); // �޼տ� �����ڸ� ��� �ִ� ���·� �׸���
	glPopMatrix(); // ������ + �޼� + ������ �Ʒ��� �κп� ���� ��ȯ ��� ����
	glPopMatrix(); // ������ ���� �κп� ���� ��ȯ ��� ����(�޼� + ���� �׸��� ��)

	glPushMatrix(); // ������ + ������ �׸���
	glColor3f(0.2, 0.5, 0.5); // �������� ���� ����
	glTranslatef(1.0 / 2 + 0.15 / 2, 0.2, 0.0); // �������� ���� �����ʿ� �پ��ֵ��� ��
	glTranslatef(-0.15 / 2, 0.7 / 2, 0.0); // ȸ�� �� ���� �ڸ��� ���ƿ�
	glRotatef(rightArm[0], 0, 0, 1); // �� ������ rightArm[0]�� ��ŭ ������ ���� �����̱�
	glTranslatef(0.15 / 2, -0.7 / 2, 0.0); // �������� ���� ����� pivot���� �Ͽ� ȸ��
	glPushMatrix(); // �������� ���� �κп� ���� ��ȯ ��� ����
	glScalef(0.15, 0.35, 0.15); // �������� ũ�� ����
	glutSolidCube(1.0); // ������(����) �׸���
	glPopMatrix(); // �������� ���� �κ��� ũ�⿡ ���� ������ ��ȯ ��Ŀ��� ����
	glPushMatrix(); // �������� ���� �κ��� ��ȯ ��Ŀ� ���� ������ ������ ä�� �������� �Ʒ��� �κ� �׸���
	glTranslatef(0.0, -0.35, 0.0); // �� ��ġ ����(�� ���κ��� �Ʒ��� �پ�����)
	glTranslatef(-0.15 / 2, 0.35 / 2, 0.0); // ȸ�� �� ���� �ڸ��� ���ƿ�
	glRotatef(rightArm[1], 0, 0, 1); // ������ �Ʒ����� rightArm[1]����ŭ �Ʒ����� ���� �����̱�
	glTranslatef(0.15 / 2, -0.35 / 2, 0.0); // �������� ���� ����� pivot���� �Ͽ� ȸ��
	glPushMatrix(); // �������� �Ʒ��� �κп� ���� ��ȯ ��� ����
	glScalef(0.15, 0.35, 0.15); // �������� ũ�� ����
	glutSolidCube(1.0); // ������(�Ʒ���) �׸���
	glPopMatrix(); // �������� �Ʒ��� �κ��� ũ�⿡ ���� ������ ��ȯ ��Ŀ��� ����
	glTranslatef(0.0, -0.35 / 2, 0.0); // �������� �������� ���� ��ġ�ϵ��� ��
	glutSolidCube(0.2); // ������ �׸���
	glPopMatrix(); // ������ + �������� �Ʒ��� �κп� ���� ��ȯ ��� ����
	glPopMatrix(); // �������� ���� �κп� ���� ��ȯ ��� ����(������ + ������ �׸��� ��)

	glPushMatrix(); // �ٸ� �׸���
	glTranslatef(0.0, -1.5 / 2 - 1.0 / 2, 0.0); // �� �ٸ��� ��ġ ����
	glPushMatrix(); // �� �ٸ��� ��ġ�� ���� ��ȯ ��� ����
	glTranslatef(-0.3, 0.0, 0.0); // �޴ٸ��� ���� ���ʿ� �پ��ֵ��� ����
	glTranslatef(0.0, 1.0 / 2, 0.0); // ȸ�� �� ���� �ڸ��� ���ƿ�
	glRotatef(leftLeg, 0, 0, 1); // leftLeg����ŭ �޴ٸ��� ������ �����̱�
	glTranslatef(0.0, -1.0 / 2, 0.0); // �ٸ��� ��� ����� pivot���� �Ͽ� ȸ��
	glPushMatrix(); // �޴ٸ��� ���� ��ȯ ��� ����
	glScalef(0.15, 1.0, 0.15); // �޴ٸ��� ũ�� ����
	glutSolidCube(1.0); // �޴ٸ� �׸���
	glPopMatrix(); // �޴ٸ� ũ�⿡ ���� ��ȯ ��� ���� (�޴ٸ��� ȸ��, ��ġ�� ���� ������ ����Ǿ� ����)
	glTranslatef(-(0.4 - 0.15) / 2, -1.0 / 2 - 0.15 / 2, 0.0); // �޹��� �޴ٸ��� ���� ��ġ��
	glScalef(0.4, 0.15, 0.3); // �޹��� ũ�� ����
	glutSolidCube(1.0); // �޹� �׸���
	glPopMatrix(); // �޴ٸ� + �޹߿� ���� ��ȯ ��� ����
	glTranslatef(0.3, 0.0, 0.0); // �����ٸ��� ���� �����ʿ� �پ��ֵ��� ����
	glTranslatef(0.0, 1.0 / 2, 0.0); // ȸ�� �� ���� �ڸ��� ���ƿ�
	glRotatef(rightLeg, 0, 0, 1); // rightLeg����ŭ �����ٸ��� ������ �����̱�
	glTranslatef(0.0, -1.0 / 2, 0.0); // �ٸ��� ��� ����� pivot���� �Ͽ� ȸ��
	glPushMatrix(); // �����ٸ��� ���� ��ȯ ��� ����
	glScalef(0.15, 1.0, 0.15); // �����ٸ��� ũ�� ����
	glutSolidCube(1.0); // �����ٸ� �׸���
	glPopMatrix(); // �����ٸ� ũ�⿡ ���� ��ȯ ��� ���� (�����ٸ��� ȸ��, ��ġ�� ���� ������ ����Ǿ� ����)
	glTranslatef((0.4 - 0.15) / 2, -1.0 / 2 - 0.15 / 2, 0.0); // �������� �����ٸ��� ���� ��ġ��
	glScalef(0.4, 0.15, 0.3); // �������� ũ�� ����
	glutSolidCube(1.0); // ������ �׸���
	glPopMatrix(); // �����ٸ� + �����߿� ���� ��ȯ ��� ����
	glPopMatrix(); // �� �ٸ��� ��ġ�� ���� ��ȯ ��� ����

	glutSwapBuffers(); // ���� ���ۿ� �ĸ� ���۸� �ٲ㼭 ȭ�鿡 ���
}

// ȭ���� �ٽ� �׷��� �� �� ȣ��Ǵ� callback �Լ�
void MyReshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); // ���� ����
	glMatrixMode(GL_PROJECTION); // ���� ��� ����
	glLoadIdentity(); // ���� ����� �׵� ��ķ� �ʱ�ȭ
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0); // ���� ���� ����
}

// Keyboard Event�� �߻����� �� ȣ��Ǵ� callback �Լ�
void MyKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
	case 'A': // 'a'�� 'A'�� �Է����� ��
		moveFocusX[0] = true; // ������ ���������� �����ؼ� ������
		moveFocusX[1] = false;
		break;
	case 'f':
	case 'F': // 'f'�� 'F'�� �Է����� ��
		moveFocusX[0] = false;
		moveFocusX[1] = true; // ������ �������� �����ؼ� ������
		break;
	case 'r':
	case 'R': // 'r'�̳� 'R'�� �Է����� ��
		moveFocusY[0] = true; // ������ �������� �����ؼ� ������
		moveFocusY[1] = false;
		break;
	case 'v':
	case 'V': // 'v'�� 'V'�� �Է����� ��
		moveFocusY[0] = false;
		moveFocusY[1] = true; // ������ �Ʒ������� �����ؼ� ������
		break;
	case 'z':
	case 'Z': // 'z'�� 'Z'�� �Է����� ��
		moveFocusZ[0] = true; // ������ ������ �����ؼ� ������
		moveFocusZ[1] = false;
		break;
	case 't':
	case 'T': // 't'�� 'T'�� �Է����� ��
		moveFocusZ[0] = false;
		moveFocusZ[1] = true; // ������ �ڷ� �����ؼ� ������
		break;
	case '1': // 1 Ű�� �Է����� ��
		// ī�޶� �κ��� �Ʒ����� ���ߵ��� ��
		cameraX = 0.0;
		cameraY = -5.0;
		cameraZ = 0.5;
		focusX = 0.0;
		focusY = -1.0;
		focusZ = 0.0;
		// ī�޶� �� ������ �������� �ʵ��� ��
		for (int i = 0; i < 2; i++)
		{
			moveCameraX[i] = false;
			moveCameraY[i] = false;
			moveCameraZ[i] = false;
			moveFocusX[i] = false;
			moveFocusY[i] = false;
			moveFocusZ[i] = false;
		}
		break;
	case '2': // 2 Ű�� �Է����� ��
		// ī�޶� �κ��� ������ ���ߵ��� ��
		cameraX = 0.0;
		cameraY = 5.0;
		cameraZ = 1.0;
		focusX = 0.0;
		focusY = -1.0;
		focusZ = 0.0;
		// ī�޶� �� ������ �������� �ʵ��� ��
		for (int i = 0; i < 2; i++)
		{
			moveCameraX[i] = false;
			moveCameraY[i] = false;
			moveCameraZ[i] = false;
			moveFocusX[i] = false;
			moveFocusY[i] = false;
			moveFocusZ[i] = false;
		}
		break;
	case '3': // 3 Ű�� �Է����� ��
		// ī�޶� �κ��� ���ʸ��� ���ߵ��� ��
		cameraX = -5.0;
		cameraY = 0.0;
		cameraZ = 0.0;
		focusX = 0.0;
		focusY = 0.0;
		focusZ = 0.0;
		// ī�޶� �� ������ �������� �ʵ��� ��
		for (int i = 0; i < 2; i++)
		{
			moveCameraX[i] = false;
			moveCameraY[i] = false;
			moveCameraZ[i] = false;
			moveFocusX[i] = false;
			moveFocusY[i] = false;
			moveFocusZ[i] = false;
		}
		break;
	case '4': // 4 Ű�� �Է����� ��
		// ī�޶� �κ��� ���ʸ��� ���ߵ��� ��
		cameraX = 5.0;
		cameraY = 0.0;
		cameraZ = 0.0;
		focusX = 0.0;
		focusY = 0.0;
		focusZ = 0.0;
		// ī�޶� �� ������ �������� �ʵ��� ��
		for (int i = 0; i < 2; i++)
		{
			moveCameraX[i] = false;
			moveCameraY[i] = false;
			moveCameraZ[i] = false;
			moveFocusX[i] = false;
			moveFocusY[i] = false;
			moveFocusZ[i] = false;
		}
		break;
	case 's':
	case 'S': // 's'�� 'S'�� �Է����� ��
		// �����̴� ��ü�� ����
		headMove = false;
		leftArmMove = false;
		rightArmMove = false;
		leftLegMove = false;
		rightLegMove = false;
		headMoveToggle = false;
		leftArmMoveToggle = false;
		rightArmMoveToggle = false;
		leftLegMoveToggle = false;
		rightLegMoveToggle = false; 
		break;
	}
}

// Keyboard Event �߻� �� ȣ��Ǵ� callback �Լ� (Ư��Ű ó��)
void MySpecialKey(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP: // �踦 �Է����� ��
		moveCameraY[0] = true; // ī�޶��� ��ġ�� ���� �����ؼ� ������
		moveCameraY[1] = false;
		break;
	case GLUT_KEY_DOWN: // �鸦 �Է����� ��
		moveCameraY[0] = false;
		moveCameraY[1] = true; // ī�޶��� ��ġ�� ������ �����ؼ� ������
		break;
	case GLUT_KEY_LEFT: // �縦 �Է����� ��
		moveCameraX[0] = false;
		moveCameraX[1] = true; // ī�޶��� ��ġ�� �������� �����ؼ� ������
		break;
	case GLUT_KEY_RIGHT: // �渦 �Է����� ��
		moveCameraX[0] = true; // ī�޶��� ��ġ�� ���������� �����ؼ� ������
		moveCameraX[1] = false;
		break;
	case GLUT_KEY_HOME: // HomeŰ�� �Է����� ��
		moveCameraZ[0] = true; // ī�޶��� ��ġ�� ������ �����ؼ� ������
		moveCameraZ[1] = false;
		break;
	case GLUT_KEY_END: // EndŰ�� �Է����� ��
		moveCameraZ[0] = false;
		moveCameraZ[1] = true; // ī�޶��� ��ġ�� �ڷ� �����ؼ� ������
		break;
	case GLUT_KEY_F5:
		// ī�޶� �� ���� ��ġ�� �ʱ� ȭ�� �������� �ǵ���
		cameraX = 0.0;
		cameraY = -3.5;
		cameraZ = 3.5;
		focusX = 0.0;
		focusY = 0.0;
		focusZ = 0.0;

		// ī�޶� �� ������ �������� �ʵ��� ��
		for (int i = 0; i < 2; i++)
		{
			moveCameraX[i] = false;
			moveCameraY[i] = false;
			moveCameraZ[i] = false;
			moveFocusX[i] = false;
			moveFocusY[i] = false;
			moveFocusZ[i] = false;
		}
		break;
	}	
}

// �Լ� ȣ���� ���� �� ó���ϴ� callback �Լ�
void MyIdle()
{
	if (headMove && head < 10) // �Ӹ��� �����̶�� ����� ���� ��
	{
		head += 0.2; // head�� 10���� �Ǳ� ������ �����Ͽ� �Ӹ��� �������� ������
	}
	else if (headMoveToggle && !headMove && head > 0) // �Ӹ��� ���� �ڸ��� �ֶ�� ����� ���� ��
	{
		head -= 0.2; // head�� 0���� �Ǳ� ������ �����Ͽ� �Ӹ��� ���� �ڸ��� ���ƿ�
	}
	if (headMoveToggle && head >= 10) // head�� 10�� �̻��̰�, �Ӹ��� ���� �ڸ��� �ξ�� �� ��
	{
		headMove = false; // �� �̻� �Ӹ��� �������� ȸ������ �ʵ��� ��
	}
	if (head <= 0) // �Ӹ��� ���� �ڸ��� ���ƿ��� ��
	{
		headMoveToggle = false; // �� �̻� �Ӹ��� ���������� ȸ������ �ʵ��� ��
	}

	if (rightArmMove && rightArm[0] < 60) // �������� �����̶�� ����� ���� ��
	{
		rightArm[0] += 0.5;
		rightArm[1] += 0.5; // �������� ���κ��� 60���� �Ǳ� ������ �������� ���� ����
	}
	else if (rightArmMoveToggle && !rightArmMove && rightArm[0] > 20) // �������� ���� ���·� �ֶ�� ����� ���� ��
	{
		rightArm[0] -= 0.5;
		rightArm[1] -= 0.5; // ���� ���·� ���ƿ� ������ �������� ��ħ
	}
	if (rightArmMoveToggle && rightArm[0] >= 60) // �������� ���κ��� 60�� �̻��̰�, �������� ���� ���·� �ξ�� �� ��
	{
		rightArmMove = false; // �� �̻� �������� ������ �ʵ��� ��
	}
	if (rightArm[0] <= 20) // �������� ���� ���·� ���ƿ��� ��
	{
		rightArmMoveToggle = false; // �� �̻� �������� ��ġ�� �ʵ��� ��
	}


	if (leftArmMove && leftArm[0] > -60) // ������ �����̶�� ����� ���� ��
	{
		leftArm[0] -= 0.5;
		leftArm[1] -= 0.5; // ������ ���κ��� -60���� �Ǳ� ������ ������ ���� ����
	}
	else if (leftArmMoveToggle && !leftArmMove && leftArm[0] < -20) // ������ ���� ���·� �ֶ�� ����� ���� ��
	{
		leftArm[0] += 0.5;
		leftArm[1] += 0.5; // ������ ���κ��� -20���� �Ǳ� ������ ������ ��ħ
	}
	if (leftArmMove && leftArm[0] <= -60) // ������ ���κ��� -60�� �����̰�, ������ ���� ���·� �ξ�� �� ��
	{
		leftArmMove = false; // �� �̻� ������ ���� �ʵ��� ��
	}
	if (leftArm[0] >= -20) // ������ ���� ���·� ���ƿ��� ��
	{
		leftArmMoveToggle = false; // �� �̻� ������ ��ġ�� �ʵ��� ��
	}

	if (rightLegMove && rightLeg < 50) // �����ٸ��� �����̶�� ����� ���� ��
	{
		rightLeg += 0.5; // �����ٸ��� �̷�� ���� 50���� �� ������ �ٱ����� ����

		if (body > -0.6)
		{
			body -= 0.01; // �ٸ��� ������ ���� �κ��� ��ġ�� ������
		}
	}
	else if (rightLegMoveToggle && !rightLegMove && rightLeg > 20) // �����ٸ��� ���� ���·� �ֶ�� ����� ���� ��
	{
		rightLeg -= 0.5; // �����ٸ��� �̷�� ���� 20���� �� ������ ������ ����

		if (body < 0)
		{
			body += 0.01; // �ٸ��� ������ ���� �κ��� ��ġ�� �ö�
		}
	}
	if (rightLegMoveToggle && rightLeg >= 50) // �����ٸ��� �̷�� ���� 50�� �̻��̰� �����ٸ��� ���� ���·� �ξ�� �� ��
	{
		rightLegMove = false; // �� �̻� �����ٸ��� �ٱ����� �������� �ʵ��� ��
	}
	if (rightLeg <= 20) // �����ٸ��� ���� ���·� ���ƿ��� ��
	{
		rightLegMoveToggle = false; // �� �̻� �����ٸ��� ������ ������ �ʵ��� ��
	}

	if (leftLegMove && leftLeg > -60) // �޴ٸ��� �����̶�� ����� ���� ��
	{
		leftLeg -= 0.5; // �޴ٸ��� �̷�� ���� -60���� �� ������ �ٱ����� ����

		if (body > -0.6)
		{
			body -= 0.01; // �ٸ��� ������ ���� �κ��� ��ġ�� ������
		}
	}
	else if (leftLegMoveToggle && !leftLegMove && leftLeg < -20) // �޴ٸ��� ���� ���·� �ֶ�� ����� ���� ��
	{
		leftLeg += 0.5; // �޴ٸ��� �̷�� ���� -20���� �� ������ ������ ����

		if (body < 0)
		{
			body += 0.01; // �ٸ��� ������ ���� �κ��� ��ġ�� �ö�
		}
	}
	if (leftLegMove && leftLeg <= -60) // �޴ٸ��� �̷�� ���� -60�� �����̰� �޴ٸ��� ���� ���·� �ֶ�� ����� ���� ��
	{
		leftLegMove = false; // �� �̻� �޴ٸ��� �ٱ����� �������� �ʵ��� ��
	}
	if (leftLeg >= -20) // �޴ٸ��� ���� ���·� ���ƿ��� ��
	{
		leftLegMoveToggle = false; // �� �̻� �޴ٸ��� ������ ������ �ʵ��� ��
	}

	// '������[0] = true'�� �� ��ǥ�迡�� ��� ������, '������[1] = true'�� �� ���� ������ �̵�
	if (moveCameraY[0]) // Keyboard Event�� �ش� ������ true�� �ٲ���� ��
	{
		cameraY += 0.01; // ī�޶� ���� �����ؼ� ������
	}
	else if (moveCameraY[1]) // Keyboard Event�� �ش� ������ true�� �ٲ���� ��
	{
		cameraY -= 0.01; // ī�޶� �Ʒ��� �����ؼ� ������
	}

	if (moveCameraX[0]) // Keyboard Event�� �ش� ������ true�� �ٲ���� ��
	{
		cameraX += 0.01; // ī�޶� ���������� �����ؼ� ������
	}
	else if (moveCameraX[1]) // Keyboard Event�� �ش� ������ true�� �ٲ���� ��
	{
		cameraX -= 0.01; // ī�޶� �������� �����ؼ� ������
	}

	if (moveCameraZ[0]) // Keyboard Event�� �ش� ������ true�� �ٲ���� ��
	{
		cameraZ += 0.01;
	}
	else if (moveCameraZ[1]) // Keyboard Event�� �ش� ������ true�� �ٲ���� ��
	{
		cameraZ -= 0.01;
	}

	if (moveFocusX[0]) // Keyboard Event�� �ش� ������ true�� �ٲ���� ��
	{
		focusX += 0.01; // ������ ���������� �����ؼ� ������
	}
	else if (moveFocusX[1]) // Keyboard Event�� �ش� ������ true�� �ٲ���� ��
	{
		focusX -= 0.01; // ������ �������� �����ؼ� ������
	}

	if (moveFocusY[0]) // Keyboard Event�� �ش� ������ true�� �ٲ���� ��
	{
		focusY += 0.01; // ������ �������� �����ؼ� ������
	}
	else if (moveFocusY[1]) // Keyboard Event�� �ش� ������ true�� �ٲ���� ��
	{
		focusY -= 0.01; // ������ �Ʒ��� �����ؼ� ������
	}

	if (moveFocusZ[0]) // Keyboard Event�� �ش� ������ true�� �ٲ���� ��
	{
		focusZ += 0.01; // ������ ������ �����ؼ� ������
	}
	else if (moveFocusZ[1]) // Keyboard Event�� �ش� ������ true�� �ٲ���� ��
	{
		focusZ -= 0.01; // ������ �ڷ� �����ؼ� ������
	}

	glutPostRedisplay(); // Display Event�� �߻����� �κ� �ٽ� �׸��� (Idle�� �� Display Event�� ��� �߻��ϹǷ� Keyboard callback���� ���� glutPostRedisplay�� �������� �ʾƵ� ��)
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); // Window OS�� ���� ����, GLUT Library �ʱ�ȭ
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // Display Mode ���� (Ʈ�� �÷� ��� & 2���� ���� ���)
	glutInitWindowPosition(0, 0); // �������� ��ġ ����
	glutInitWindowSize(500, 500); // �������� ũ�� ����
	glutCreateWindow("Can Robot Modeling"); // ������ â ���� �� �̸� ����
	MyInit(); // �ʱ� ���� ����
	glutDisplayFunc(MyDisplay); // Display Event�� �߻��� ������ MyDisplay�� ȣ���ϵ��� ���
	glutReshapeFunc(MyReshape); // ȭ���� �ٽ� �׷��� �� ������ MyReshape�� ȣ���ϵ��� ���
	glutKeyboardFunc(MyKeyboard); // �Ϲ�Ű�� ���� Keyboard Event�� �߻��� ������ MyKeyboard�� ȣ���ϵ��� ���
	glutSpecialFunc(MySpecialKey); // Ư��Ű�� ���� Keyboard Event�� �߻��� ������ MySpecialKey�� ȣ���ϵ��� ���
	glutIdleFunc(MyIdle); // Event�� ������ MyIdle�� ȣ���ϵ��� ���
	glutMainLoop(); // GLUT Event ó�� Loop ����
	return 0;
}