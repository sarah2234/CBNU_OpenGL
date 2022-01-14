/*******************************************************************************************************/
/*                                       HW#4-2 : ���� Can Robot �𵨸�                                */
/*  �ۼ��� : �̽���                                                            ��¥ : 2021�� 10�� 27�� */
/*                                                                                                     */
/* ���� ���� :                                                                                         */
/* 1. ��� ������ �̿��Ͽ� Can Robot�� �����Ѵ�.                                                       */
/* ��� :                                                                                              */
/* 1. �޴����� 'Move Head'�� ������ �Ӹ��� �������ٰ� ���� �ڼ��� ���ƿ´�.                            */
/* 2. �޴����� 'Move Right Arm'�� ������ �������� �������ٰ� ���� �ڼ��� ���ƿ´�.                     */
/* 3. �޴����� 'Move Left Arm'�� ������ ������ �������ٰ� ���� �ڼ��� ���ƿ´�.                        */
/* 4. �޴����� 'Move Right Leg'�� ������ �����ٸ��� �������ٰ� ���� �ڼ��� ���ƿ´�.                   */
/* 5. �޴����� 'Move Left Leg'�� ������ ���ʴٸ��� �������ٰ� ���� �ڼ��� ���ƿ´�.                    */
/*******************************************************************************************************/

#include <gl/glut.h>

bool headMove, leftArmMove, rightArmMove, leftLegMove, rightLegMove; // ������ ��ü ������ �������� �����ϱ� ���� ����
bool headMoveToggle, leftArmMoveToggle, rightArmMoveToggle, leftLegMoveToggle, rightLegMoveToggle; // ������ ��ü ������ �������� �����ϱ� ���� ����
float head, leftArm[2], rightArm[2], leftLeg, rightLeg, body; // ������ ��ü ������ �����̴� ������ ���ϱ� ���� ����

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

	GLint menuID = glutCreateMenu(MyMenu); // �޴� ����
	glutAddMenuEntry("Move Head", 1); // ù ��° �޴� ����
	glutAddMenuEntry("Move Right Arm", 2); // �� ��° �޴� ����
	glutAddMenuEntry("Move Left Arm", 3); // �� ��° �޴� ����
	glutAddMenuEntry("Move Right Leg", 4); // �� ��° �޴� ����
	glutAddMenuEntry("Move Left Leg", 5); // �ټ� ��° �޴� ����
	glutAttachMenu(GLUT_RIGHT_BUTTON); // ���콺 ��Ŭ���� �ϸ� �޴��� ��Ÿ��
}

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
	glTranslatef(0.0, body, 0.0); // �ٸ� �����ӿ� ���� �κ��� ��ġ ����
	glRotatef(20, 0, 1, 1); // �κ� ��ü ȸ��
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
	glTranslatef(0.0, -0.35 / 2 , 0.0); // �޼��� ������ ���� ��ġ�ϵ��� ��
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
	glTranslatef(0.0, 0.0, -4.0); // z�࿡�� -4.0��ŭ �̵� (3D Primitive���� ���̵��� ��)
}

// Keyboard Event�� �߻����� �� ȣ��Ǵ� callback �Լ�
void MyKeyboard(unsigned char key, int x, int y)
{
	if (key == 's' || key == 'S')
	{
		// 's'�� 'S'�� ������ �����̴� ��ü�� ����
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

	glutPostRedisplay(); // Display Event�� �߻����� �κ� �ٽ� �׸���
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
	glutKeyboardFunc(MyKeyboard); // Keyboard Event�� �߻��� ������ MyKeyboard�� ȣ���ϵ��� ���
	glutIdleFunc(MyIdle); // Event�� ������ MyIdle�� ȣ���ϵ��� ���
	glutMainLoop(); // GLUT Event ó�� Loop ����
	return 0;
}