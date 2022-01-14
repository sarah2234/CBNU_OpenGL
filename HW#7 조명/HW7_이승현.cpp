/*******************************************************************************************************/
/*                                 HW#7 : ���� Can Robot�� ���� ȿ�� ����                              */
/*  �ۼ��� : �̽���                                                            ��¥ : 2021�� 11�� 24�� */
/*                                                                                                     */
/* ���� ���� :                                                                                         */
/* 1. �κ��� �޸��� ����� �߰��ϰ�, ������ ������.                                                    */
/* ��� :                                                                                              */
/* 1. �޴����� 'Move Head'�� ������ �Ӹ��� �������ٰ� ���� �ڼ��� ���ƿ´�.                            */
/* 2. �޴����� 'Move Right Arm'�� ������ �������� �������ٰ� ���� �ڼ��� ���ƿ´�.                     */
/* 3. �޴����� 'Move Left Arm'�� ������ ������ �������ٰ� ���� �ڼ��� ���ƿ´�.                        */
/* 4. �޴����� 'Move Right Leg'�� ������ �����ٸ��� �������ٰ� ���� �ڼ��� ���ƿ´�.                   */
/* 5. �޴����� 'Move Left Leg'�� ������ ���ʴٸ��� �������ٰ� ���� �ڼ��� ���ƿ´�.                    */
/* 6. 'r'�̳� 'R'�� ������ �κ��� �ڴ�.                                                                */
/* 7. s'�� 'S'�� ������ �κ��� �������� �����.                                                        */
/* 8. ���콺�� ��Ŭ���ϸ鼭 �������� ������ ������ �ٲ۴�.                                             */
/* 9. ���콺�� ���� �������� ������ cutoff�� �ٲ۴�.                                                   */
/*******************************************************************************************************/

#include <gl/glut.h>
#include <gl/freeglut_ext.h>

bool headMoveDirection[2], leftArmMoveDirection[2], rightArmMoveDirection[2], leftLegMoveDirection[2], rightLegMoveDirection[2]; // ������ ��ü ������ �������� �����ϱ� ���� ����
float head, leftArm[2], rightArm[2], leftLeg[2], rightLeg[2], body; // ������ ��ü ������ �����̴� ������ ���ϱ� ���� ����
bool run; // �ٴ� ���θ� �����ϴ� ����

GLint Width = 500, Height = 500; // ȭ���� ũ��
const GLfloat global_ambient[] = { 0.4, 0.4, 0.4, 1.0 }; // ���� �ֺ���
const GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 }; // �ֺ���
const GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 }; // �ݻ籤
const GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 }; // �л걤
GLfloat light_position[] = { 0.0, 0.0, 1.0, 1.0 }; // ������ ��ġ
GLfloat light_direction[] = { 0.0, 0.0, -1.0 }; // ������ ����
GLfloat light_cutoff = 90.0; // ���� ����

// �ʱ� ȭ�� ����
void MyInit()
{
	// �ʱ� ȭ�鿡�� ��� ��ü �κ��� �������� �ʵ��� ��
	for (int i = 0; i < 2; i++)
	{
		headMoveDirection[i] = false;
		leftArmMoveDirection[i] = false;
		rightArmMoveDirection[i] = false;
		leftLegMoveDirection[i] = false;
		rightLegMoveDirection[i] = false;
	}

	// �ʱ� ȭ�鿡���� �Ӹ�, ��, �ٸ� ����
	head = 0;
	leftArm[0] = 0;
	leftArm[1] = 0;
	rightArm[0] = 0;
	rightArm[1] = 0;
	leftLeg[0] = 0;
	leftLeg[1] = 0;
	rightLeg[0] = 0;
	rightLeg[1] = 0;
	body = 0;

	run = false; // �ʱ� ȭ�鿡�� �κ��� �޸��� ����
}

// �޴��� ������
void MyMenu(int value)
{
	switch (value)
	{
	case 1:
		MyInit();
		headMoveDirection[0] = true; // ù ��° �޴� Ŭ�� �� �Ӹ��� ������
		break;
	case 2:
		MyInit();
		rightArmMoveDirection[0] = true; // �� ��° �޴� Ŭ�� �� �������� ������
		break;
	case 3:
		MyInit();
		leftArmMoveDirection[0] = true; // �� ��° �޴� Ŭ�� �� ������ ������
		break;
	case 4:
		MyInit();
		rightLegMoveDirection[0] = true; // �� ��° �޴� Ŭ�� �� �����ٸ��� ������
		break;
	case 5:
		MyInit();
		leftLegMoveDirection[0] = true; // �ټ� ��° �޴� Ŭ�� �� �޴ٸ��� ������
		break;
	}
}

// Display Event�� �߻��� �� ȣ��Ǵ� callback �Լ�
void MyDisplay()
{
	glClearColor(0.0, 0.0, 0.0, 0.0); // ���������� ȭ�� �����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // �� ����, ���� ���۸� �����Ͽ� ȭ�鿡�� �׸� �����
	glMatrixMode(GL_MODELVIEW); // �𵨺� ��� ����
	glLoadIdentity(); // �𵨺� ����� �׵� ��ķ� �ʱ�ȭ

	glEnable(GL_LIGHTING); // ���� ���
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient); // ���� �ֺ��� ���ϱ� (ī�޶� ������Ŵ)
	gluLookAt(2, 0, 4, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // ī�޶� ��ġ ����
	glEnable(GL_LIGHT0); // 0�� ���� ���
	glLightfv(GL_LIGHT0, GL_POSITION, light_position); // 0�� ���� ��ġ ���ϱ�
	glLightfv(GL_LIGHT0, GL_AMBIENT, mat_ambient); // �ֺ��� ���ϱ�
	glLightfv(GL_LIGHT0, GL_DIFFUSE, mat_diffuse); // �л걤 ���ϱ�
	glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular); // �ݻ籤 ���ϱ�
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.5); // ���� ���� ȿ�� ���ϱ�
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction); // ������ ���� ���ϱ�
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, light_cutoff); // ������ ���� ���ϱ�
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 5.0);	// ���� ���� ���ϱ�
	
	glEnable(GL_COLOR_MATERIAL); // ��ü�� ������ �������� ��
	glEnable(GL_DEPTH_TEST); // ���� ����
	glFrontFace(GL_CCW); // �ո� ���� 
	glEnable(GL_CULL_FACE); // �� ������ ������ �ʴ� �޺κ� ����
	glEnable(GL_NORMALIZE); // ���͸� ���� ���ͷ� �ٲٱ� (glScalef ��� �� ���� ���Ϳ� ������ ����, �̴� ���� ��꿡 ������ ��ħ)
	glShadeModel(GL_SMOOTH); // Gouraud Shading

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient); // �ֺ����� ���� ��ü�� ���� ���ϱ�
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse); // �л걤�� ���� ��ü�� ���� ���ϱ�
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular); // �ݻ籤�� ���� ��ü�� ���� ���ϱ�
	glMaterialf(GL_FRONT, GL_SHININESS, 50); // ��ü�� ���� ��� ���ϱ�

	glPushMatrix(); // ���� ���� ��ȯ ��� ����
	glColor3f(0.2, 0.5, 0.5); // �� ���� ����
	glRotatef(body, 1.0, 0.0, 0.0); // body�� ���� ���� �յڷ� ������
	glPushMatrix(); // ���� ���� ȸ�� ��� ����
	glScalef(1.0, 1.5, 1.0); // �� ũ�� ����
	glutSolidCube(1.0); // ��
	glPopMatrix(); // �� �׸��� ��
	glPushMatrix(); // �� ��ű��� ���� ��ȯ ��� ����
	glTranslatef(0.0, 0.2, 0.5); // ��ű��� ��ġ ����
	glColor3f(0.5, 0.0, 0.0); // ��ű� ���� ����
	glutSolidTorus(0.05, 0.3, 20, 20); // �� ���κ��� ��ű� �׸���
	glRotatef(45, 0, 0, 1); // �� ���κ��� ��ű� ȸ��(���̾� ���)
	glTranslatef(0.0, 0.0, -0.1); // ��ű��� ��ġ ����
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
	glColor3f(0.8, 0.0, 0.0); // ������ ��
	glutSolidCube(1.0); // �� �׸���
	glPopMatrix(); // �Կ� ���� ��ȯ ��� ����
	glPopMatrix(); // �� ��ġ�� ���� ��ȯ ��� ����
	glPopMatrix(); // ���� ���� ȸ�� ��� ����

	glColor3f(0.3, 0.8, 0.8); // ���� ���� ����
	glPushMatrix(); // �� �׸���
	glTranslatef(-1.0 / 2 - 0.15 / 2, 0.3, 0.0); // �� ��ġ ����(���� ���ʿ� �پ�����)
	glTranslatef(0.15 / 2, 0.35 / 2, 0.0); // ȸ�� �� ���� �ڸ��� ���ƿ�
	glRotatef(leftArm[0], 1, 0, 0); // �� ������ leftArm[0]����ŭ ������ �����̱�
	glTranslatef(-0.15 / 2, -0.35 / 2, 0.0); // ������ ���� ����� pivot���� �Ͽ� ȸ��
	glPushMatrix(); // ������ ���� �κп� ���� ��ȯ ��� ����
	glScalef(0.15, 0.35, 0.15); // ������ ũ�� ����
	glutSolidCube(1.0); // ����(����) �׸���
	glPopMatrix(); // ������ ���� �κ��� ũ�⿡ ���� ������ ��ȯ ��Ŀ��� ����
	glPushMatrix(); // ������ ���� �κ��� ��ȯ ��Ŀ� ���� ������ ������ ä�� ������ �Ʒ��� �κ� �׸���
	glTranslatef(0.0, -0.35, 0.0); // �� ��ġ ����(�� ���κ��� �Ʒ��� �پ�����)
	glTranslatef(0.15 / 2, 0.35 / 2, 0.0); // ȸ�� �� ���� �ڸ��� ���ƿ�
	glRotatef(leftArm[1], 1, 0, 0); // ������ �Ʒ����� leftArm[1]����ŭ �Ʒ����� �����̱�
	glTranslatef(-0.15 / 2, -0.35 / 2, 0.0); // ������ ���� ����� pivot���� �Ͽ� ȸ��
	glPushMatrix(); // ������ �Ʒ��� �κп� ���� ��ȯ ��� ����
	glScalef(0.15, 0.35, 0.15); // ������ ũ�� ����
	glutSolidCube(1.0); // ����(�Ʒ���) �׸���
	glPopMatrix(); // ������ �Ʒ��� �κ��� ũ�⿡ ���� ������ ��ȯ ��Ŀ��� ����
	glTranslatef(0.0, -0.35 / 2, 0.0); // �޼��� ������ ���� ��ġ�ϵ��� ��
	glColor3f(0.2, 0.5, 0.5); // �޼� ���� ����
	glutSolidCube(0.2); // �޼� �׸���
	glFrontFace(GL_CW); // �������� �ո� ����
	glTranslatef(-0.4, -0.2, 0.5); // �������� ��ġ ����
	glRotatef(230, 0, 1, 0); // �����ڸ� y�� �������� 230�� ȸ��
	glColor3f(0.5, 0.2, 0.3); // �������� ���� ����
	glutSolidTeapot(0.4); // �޼տ� �����ڸ� ��� �ִ� ���·� �׸���
	glPopMatrix(); // ������ + �޼� + ������ �Ʒ��� �κп� ���� ��ȯ ��� ����
	glPopMatrix(); // ������ ���� �κп� ���� ��ȯ ��� ����(�޼� + ���� �׸��� ��)

	glFrontFace(GL_CCW); // �κ��� �ո� ����
	glPushMatrix(); // ������ + ������ �׸���
	glColor3f(0.3, 0.8, 0.8); // �������� ���� ����
	glTranslatef(1.0 / 2 + 0.15 / 2, 0.2, 0.0); // �������� ���� �����ʿ� �پ��ֵ��� ��
	glTranslatef(-0.15 / 2, 0.7 / 2, 0.0); // ȸ�� �� ���� �ڸ��� ���ƿ�
	glRotatef(rightArm[0], 1, 0, 0); // �� ������ rightArm[0]�� ��ŭ ������ �����̱�
	glTranslatef(0.15 / 2, -0.7 / 2, 0.0); // �������� ���� ����� pivot���� �Ͽ� ȸ��
	glPushMatrix(); // �������� ���� �κп� ���� ��ȯ ��� ����
	glScalef(0.15, 0.35, 0.15); // �������� ũ�� ����
	glutSolidCube(1.0); // ������(����) �׸���
	glPopMatrix(); // �������� ���� �κ��� ũ�⿡ ���� ������ ��ȯ ��Ŀ��� ����
	glPushMatrix(); // �������� ���� �κ��� ��ȯ ��Ŀ� ���� ������ ������ ä�� �������� �Ʒ��� �κ� �׸���
	glTranslatef(0.0, -0.35, 0.0); // �� ��ġ ����(�� ���κ��� �Ʒ��� �پ�����)
	glTranslatef(-0.15 / 2, 0.35 / 2, 0.0); // ȸ�� �� ���� �ڸ��� ���ƿ�
	glRotatef(rightArm[1], 1, 0, 0); // ������ �Ʒ����� rightArm[1]����ŭ �Ʒ����� �����̱�
	glTranslatef(0.15 / 2, -0.35 / 2, 0.0); // �������� ���� ����� pivot���� �Ͽ� ȸ��
	glPushMatrix(); // �������� �Ʒ��� �κп� ���� ��ȯ ��� ����
	glScalef(0.15, 0.35, 0.15); // �������� ũ�� ����
	glutSolidCube(1.0); // ������(�Ʒ���) �׸���
	glPopMatrix(); // �������� �Ʒ��� �κ��� ũ�⿡ ���� ������ ��ȯ ��Ŀ��� ����
	glTranslatef(0.0, -0.35 / 2, 0.0); // �������� �������� ���� ��ġ�ϵ��� ��
	glColor3f(0.2, 0.5, 0.5); // ������ ���� ����
	glutSolidCube(0.2); // ������ �׸���
	glPopMatrix(); // ������ + �������� �Ʒ��� �κп� ���� ��ȯ ��� ����
	glPopMatrix(); // �������� ���� �κп� ���� ��ȯ ��� ����(������ + ������ �׸��� ��)

	glPushMatrix(); // �ٸ� �׸���
	glTranslatef(0.0, -1.5 / 2 - 0.5 / 2, 0.0); // �� �ٸ��� ��ġ ����
	glPushMatrix(); // �� �ٸ��� ��ġ�� ���� ��ȯ ��� ����
	glTranslatef(-0.3, 0.0, 0.0); // �޴ٸ��� ���� ���ʿ� �پ��ֵ��� ����
	glColor3f(0.3, 0.8, 0.8); // �޴ٸ��� ���� ����
	glTranslatef(0.0, 1.0 / 2, 0.0); // ȸ�� �� ���� �ڸ��� ���ƿ�
	glRotatef(leftLeg[0], 1, 0, 0); // leftLeg[0]����ŭ �޴ٸ��� ���� �κ��� �����̱�
	glTranslatef(0.0, -1.0 / 2, 0.0); // �ٸ��� ��� ����� pivot���� �Ͽ� ȸ��
	glPushMatrix(); // �޴ٸ��� ���� �κп� ���� ��ȯ ��� ����
	glScalef(0.15, 0.5, 0.15); // �޴ٸ��� ���� �κ� ũ�� ����
	glutSolidCube(1.0); // �޴ٸ��� ���� �κ� �׸���
	glPopMatrix(); // �޴ٸ��� ���� �κп� ���� ũ�� ��� ����
	glPushMatrix(); // �޴ٸ��� ���� �κ��� ��ȯ ��Ŀ� ���� ������ ������ ä�� �޴ٸ��� �Ʒ��� �κ� �׸���
	glTranslatef(0.0, -0.5 / 2, 0.0); // �޴ٸ��� �Ʒ��� �κ��� ��ġ ����
	glRotatef(leftLeg[1], 1, 0, 0); // leftLeg[1]����ŭ �޴ٸ��� �Ʒ��� �κ��� �����̱�
	glTranslatef(0.0, -0.5 / 2, 0.0); // �ٸ��� ��� ����� pivot���� �Ͽ� ȸ��
	glPushMatrix(); // �޴ٸ��� �Ʒ��� �κп� ���� ��ȯ ��� ����
	glScalef(0.15, 0.5, 0.15); // �޴ٸ��� �Ʒ��� �κ� ũ�� ����
	glutSolidCube(1.0); // �޴ٸ��� �Ʒ��� �κ� �׸���
	glPopMatrix(); // �޴ٸ� ũ�⿡ ���� ��ȯ ��� ���� (�޴ٸ��� ȸ��, ��ġ�� ���� ������ ����Ǿ� ����)
	glTranslatef(-(0.15 - 0.15) / 2, -0.5 / 2 - 0.15 / 2, 0.1); // �޹��� �޴ٸ��� ���� ��ġ��
	glScalef(0.2, 0.15, 0.5); // �޹��� ũ�� ����
	glColor3f(0.2, 0.5, 0.5); // �޹� ���� ����
	glutSolidCube(1.0); // �޹� �׸���
	glPopMatrix(); 
	glPopMatrix(); // �޴ٸ� + �޹߿� ���� ��ȯ ��� ����
	glTranslatef(0.3, 0.0, 0.0); // �����ٸ��� ���� �����ʿ� �پ��ֵ��� ����
	glColor3f(0.3, 0.8, 0.8); // �����ٸ��� ���� ����
	glTranslatef(0.0, 1.0 / 2, 0.0); // ȸ�� �� ���� �ڸ��� ���ƿ�
	glRotatef(rightLeg[0], 1, 0, 0); // rightLeg[0]����ŭ �����ٸ��� �����̱�
	glTranslatef(0.0, -1.0 / 2, 0.0); // �ٸ��� ��� ����� pivot���� �Ͽ� ȸ��
	glPushMatrix(); // �����ٸ��� ���� ��ȯ ��� ����
	glScalef(0.15, 0.5, 0.15); // �����ٸ��� ũ�� ����
	glutSolidCube(1.0); // �����ٸ��� ���� �κ� �׸���
	glPopMatrix(); // �����ٸ��� ���� �κп� ���� ũ�� ��� ����
	glPushMatrix(); // �����ٸ��� ���� �κ��� ��ȯ ��Ŀ� ���� ������ ������ ä�� �����ٸ��� �Ʒ��� �κ� �׸���
	glTranslatef(0.0, -0.25, 0.0); // �����ٸ��� �Ʒ��� �κ��� ��ġ ����
	glRotatef(rightLeg[1], 1, 0, 0); // rightLeg[1]����ŭ �����ٸ��� �Ʒ��� �κ��� �����̱�
	glTranslatef(0.0, -0.25, 0.0); // �ٸ��� ��� ����� pivot���� �Ͽ� ȸ��
	glPushMatrix(); // �����ٸ��� �Ʒ��� �κп� ���� ��ȯ ��� ����
	glScalef(0.15, 0.5, 0.15); // �����ٸ��� �Ʒ��� �κ� ũ�� ����
	glutSolidCube(1.0); // �����ٸ��� �Ʒ��� �κ� �׸���
	glPopMatrix(); // �����ٸ� ũ�⿡ ���� ��ȯ ��� ���� (�����ٸ��� ȸ��, ��ġ�� ���� ������ ����Ǿ� ����)
	glTranslatef((0.15 - 0.15) / 2, -0.5 / 2 - 0.15 / 2, 0.1); // �������� �����ٸ��� ���� ��ġ��
	glScalef(0.2, 0.15, 0.5); // �������� ũ�� ����
	glColor3f(0.2, 0.5, 0.5); // ������ ���� ����
	glutSolidCube(1.0); // ������ �׸���
	glPopMatrix(); // �����ٸ� + �����߿� ���� ��ȯ ��� ����
	glPopMatrix(); // �� �ٸ��� ��ġ�� ���� ��ȯ ��� ����

	glutSwapBuffers(); // ���� ���ۿ� �ĸ� ���۸� �ٲ㼭 ȭ�鿡 ���
}

// ȭ���� �ٽ� �׷��� �� �� ȣ��Ǵ� callback �Լ�
void MyReshape(int w, int h)
{
	Width = w; // �ٲ� ȭ���� �ʺ� ����
	Height = h; // �ٲ� ȭ���� ���� ����
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
	case 's':
	case 'S':
		// 's'�� 'S'�� ������ �����̴� ��ü�� ����
		for (int i = 0; i < 2; i++)
		{
			headMoveDirection[i] = false;
			leftArmMoveDirection[i] = false;
			rightArmMoveDirection[i] = false;
			leftLegMoveDirection[i] = false;
			rightLegMoveDirection[i] = false;
		}
		run = false;
		break;
	case 'r':
	case 'R':
		// 'r'�� 'R'�� ������ �κ��� �޸�
		if (run)
			return; // �̹� �޸��� ������ �Լ� ����
		run = true; // �޸��� ����
		body = 20; // ���� ������ ����
		rightArmMoveDirection[0] = true; // �������� ������ �����̱�
		rightArmMoveDirection[1] = false;
		leftArmMoveDirection[0] = false;
		leftArmMoveDirection[1] = true; // ������ �ڷ� �����̱�
		rightLegMoveDirection[0] = false;
		rightLegMoveDirection[1] = true; // �����ٸ��� �ڷ� �����̱�
		leftLegMoveDirection[0] = true; // �޴ٸ��� ������ �����̱�
		leftLegMoveDirection[1] = false;
		break;
	}
}

// �Լ� ȣ���� ���� �� ó���ϴ� callback �Լ�
void MyIdle()
{
	if (headMoveDirection[0] && head <= 10) // �Ӹ��� �����̶�� ����� ���� ��
	{
		head += 0.5; // head�� 10���� �Ǳ� ������ �����Ͽ� �Ӹ��� �������� ������
	}
	else if (headMoveDirection[1] && head > 0) // �Ӹ��� ���� �ڸ��� �ֶ�� ����� ���� ��
	{
		head -= 0.5; // head�� 0���� �Ǳ� ������ �����Ͽ� �Ӹ��� ���� �ڸ��� ���ƿ�
	}
	else if (head <= 0) // head�� �����·� ���ƿ��� ��
	{
		headMoveDirection[1] = false; // �� �̻� �Ӹ��� ���������� ȸ������ �ʵ��� ��
	}
	if (head >= 10) // head�� 10�� �̻��̰�, �Ӹ��� ���� �ڸ��� �ξ�� �� ��
	{
		headMoveDirection[0] = false; // �� �̻� �Ӹ��� �������� ȸ������ �ʵ��� ��
		headMoveDirection[1] = true; // �Ӹ��� ���������� ȸ���ϵ��� ��
	}

	if (rightArmMoveDirection[0]) // �������� ������ �����̶�� ����� ���� ��
	{
		rightArm[0] -= 2.5; // �������� ���κ��� -40���� �Ǳ� ������ �������� ���� ���
		if (rightArm[1] > -40)
			rightArm[1] -= 2.5; // �������� �Ʒ��κ��� �� ������ ������ ��� ����
	}
	else if (rightArmMoveDirection[1]) // �������� �ڷ� �����̶�� ����� ���� ��
	{
		if (!run) // �ٶ�� ����� ���� ��
		{
			rightArm[0] += 2.5;
			rightArm[1] += 2.5; // �������� ���κ��� -40���� �Ǳ� ������ �������� ��ġ�鼭 �ڷ� ���
		}
		else if (run) // �ٶ�� ����� ���� ��
		{
			rightArm[0] += 2.5; // �������� ���� ä ���� �ڷ� ����
		}
	}
	if (rightArmMoveDirection[0] && rightArm[0] <= -40) // �������� ���κ��� ����� ���� ������� ��
	{
		rightArmMoveDirection[0] = false;
		rightArmMoveDirection[1] = true; // �������� �ڷ� ���
	}
	else if (!run && rightArm[0] >= 0) // (�ٶ�� ��� ����) �������� ���� ���·� ���ƿ��� ��
	{
		rightArmMoveDirection[1] = false; // �� �̻� �������� �ڷ� ���� �ʵ��� ��
	}
	else if (run && rightArm[0] >= 40) // �ٰ� �ִ� ���� �������� ����� �ڷ� ������� ��
	{
		rightArmMoveDirection[0] = true; // �������� ������ ���
		rightArmMoveDirection[1] = false;
	}

	if (leftArmMoveDirection[0]) // ������ ������ �����̶�� ����� ���� ��
	{
		leftArm[0] -= 2.5; // ������ ���κ��� -40���� �Ǳ� ������ ������ ���� ���
		if (leftArm[1] > -40)
			leftArm[1] -= 2.5; // ������ �Ʒ��κ��� �� ������ ������ ��� ����
	}
	else if (leftArmMoveDirection[1]) // ������ �ڷ� �����̶�� ����� ���� ��
	{
		if (!run) // �ٶ�� ����� ���� ��
		{
			leftArm[0] += 2.5;
			leftArm[1] += 2.5; // ������ ���κ��� -40���� �Ǳ� ������ ������ ��ħ
		}
		else if (run) // �ٶ�� ����� ���� ��
		{
			leftArm[0] += 2.5; // ������ ���� ä ���� �ڷ� ����
		}
	}
	if (leftArmMoveDirection[0] && leftArm[0] <= -40) // ������ ���κ��� ����� ���� ������� ��
	{
		leftArmMoveDirection[0] = false;
		leftArmMoveDirection[1] = true; // ������ �ڷ� ���
	}
	else if (!run && leftArm[0] >= 0) // (�ٶ�� ��� ����) ������ ���� ���·� ���ƿ��� ��
	{
		leftArmMoveDirection[1] = false; // �� �̻� ������ �ڷ� ���� �ʵ��� ��
	}
	else if (run && leftArm[0] >= 40) // �ٰ� �ִ� ���� ������ ����� �ڷ� ������� ��
	{
		leftArmMoveDirection[0] = true; // ������ ���� ���
		leftArmMoveDirection[1] = false;
	}
	
	if (rightLegMoveDirection[0]) // �����ٸ��� ������ �����̶�� ����� ���� ��
	{
		rightLeg[0] -= 2.5; // ���ٸ� ������ ���
		if ((!run && rightLeg[0] < 0) || (run && -40 < rightLeg[0] && rightLeg[0] < 0)) // �ٸ��� ������ ��鼭 ����� �� ��
			rightLeg[1] += 2.5; // �Ʒ� �ٸ� ����
		else if ((!run && rightLeg[0] > 0) || (run && 0 < rightLeg[0] && rightLeg[0] < 40)) // �ٸ��� ������ ��鼭 ��� �� ��
			rightLeg[1] -= 2.5; // �Ʒ� �ٸ� ���
	}
	else if (rightLegMoveDirection[1]) // �����ٸ��� �ڷ� �����̶�� ����� ���� ��
	{
		rightLeg[0] += 2.5; // ���ٸ� �ڷ� ���
		if (!run || (run && -40 < rightLeg[0] && rightLeg[0] < 0)) // �ٸ��� �ڷ� ��鼭 ��� �� ��
			rightLeg[1] -= 2.5; // �Ʒ� �ٸ� ���
		else if (run && 0 < rightLeg[0] && rightLeg[0] < 40) // �ٸ��� �ڷ� ��鼭 ����� �� ��
			rightLeg[1] += 2.5; // �Ʒ� �ٸ� ����
	}
	if (rightLegMoveDirection[0] && rightLeg[0] <= -40) // �����ٸ��� ���κ��� ����� ���� ������� ��
	{
		rightLegMoveDirection[0] = false;
		rightLegMoveDirection[1] = true; // �����ٸ��� �ڷ� ���
	}
	else if (!run && rightLeg[0] >= 0) // (�ٶ�� ��� ����) �����ٸ��� ���� ���·� ���ƿ��� ��
	{
		rightLegMoveDirection[1] = false; // �� �̻� �����ٸ��� �ڷ� ���� �ʵ��� ��
	}
	else if (run && rightLeg[0] >= 40) // �ٰ� �ִ� ���� �����ٸ��� ����� �ڷ� ������� ��
	{
		rightLegMoveDirection[0] = true; // �����ٸ��� ���� ���
		rightLegMoveDirection[1] = false;
	}

	if (leftLegMoveDirection[0]) // �޴ٸ��� ������ �����̶�� ����� ���� ��
	{
		leftLeg[0] -= 2.5; // ���ٸ� ������ ���
		if ((!run && leftLeg[0] < 0) || (run && -40 < leftLeg[0] && leftLeg[0] < 0)) // �ٸ��� ������ ��鼭 ����� �� ��
			leftLeg[1] += 2.5; // �Ʒ� �ٸ� ����
		else if ((!run && leftLeg[0] > 0) || (run && 0 < leftLeg[0] && leftLeg[0] < 40)) // �ٸ��� ������ ��鼭 ��� �� ��
			leftLeg[1] -= 2.5; // �Ʒ� �ٸ� ���
	}
	else if (leftLegMoveDirection[1]) // �޴ٸ��� �ڷ� �����̶�� ����� ���� ��
	{
		leftLeg[0] += 2.5; // ���ٸ� �ڷ� ���
		if (!run || (run && -40 < leftLeg[0] && leftLeg[0] < 0)) // �ٸ��� �ڷ� ��鼭 ��� �� ��
			leftLeg[1] -= 2.5; // �Ʒ� �ٸ� ���
		else if (run && 0 < leftLeg[0] && leftLeg[0] < 40) // �ٸ��� �ڷ� ��鼭 ����� �� ��
			leftLeg[1] += 2.5; // �Ʒ� �ٸ� ����
	}
	if (leftLegMoveDirection[0] && leftLeg[0] <= -40) // �޴ٸ��� ���κ��� ����� ���� ������� ��
	{
		leftLegMoveDirection[0] = false;
		leftLegMoveDirection[1] = true; // �޴ٸ��� �ڷ� ���
	}
	else if (!run && leftLeg[0] >= 0) // (�ٶ�� ��� ����) �޴ٸ��� ���� ���·� ���ƿ��� ��
	{
		leftLegMoveDirection[1] = false; // �� �̻� �޴ٸ��� �ڷ� ���� �ʵ��� ��
	}
	else if (run && leftLeg[0] >= 40) // �ٰ� �ִ� ���� �޴ٸ��� ����� �ڷ� ������� ��
	{
		leftLegMoveDirection[0] = true; // �޴ٸ��� ���� ���
		leftLegMoveDirection[1] = false;
	}

	glutPostRedisplay(); // Display Event�� �߻����� �κ� �ٽ� �׸���
}

// Mouse Motion Event�� ó���ϴ� callback �Լ�
void MyMouseMove(int x, int y)
{
	light_direction[0] = (x - Width / 2); // ������ ������ ���콺�� ��ġ�� ���� ����
	light_direction[1] = (Height - y - Height / 2); // GLUT ��ǥ�� ���� y�� ���� GL ��ǥ��� ����
}

// Mouse Event�� ó���ϴ� callback �Լ�
void MyMouse(GLint button, GLint state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) // ��Ŭ�� ���� ��
	{
		glutMotionFunc(MyMouseMove); // ���콺 �������� ó���ϴ� �Լ� ȣ��
		glutPostRedisplay(); // Display Event �߻����� �κ� �ٽ� �׸���
	}
	else if (button == 3 && light_cutoff < 90) // ���� ��ũ������ ��
	{
		light_cutoff += 1; // ������ ���ߴ� ������ �о���
		glutPostRedisplay(); // Display Event �߻����� �κ� �ٽ� �׸���
	}
	else if (button == 4 && light_cutoff > 0) // �Ʒ��� ��ũ������ ��
	{
		light_cutoff -= 1; // ������ ���ߴ� ������ ������
		glutPostRedisplay(); // Display Event �߻����� �κ� �ٽ� �׸���
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); // Window OS�� ���� ����, GLUT Library �ʱ�ȭ
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // Display Mode ���� (Ʈ�� �÷� ��� & 2���� ���� ���)
	glutInitWindowPosition(0, 0); // �������� ��ġ ����
	glutInitWindowSize(500, 500); // �������� ũ�� ����
	glutCreateWindow("Can Robot Modeling"); // ������ â ���� �� �̸� ����
	MyInit(); // �ʱ� ���� ����
	GLint menuID = glutCreateMenu(MyMenu); // �޴� ����
	glutAddMenuEntry("Move Head", 1); // ù ��° �޴� ����
	glutAddMenuEntry("Move Right Arm", 2); // �� ��° �޴� ����
	glutAddMenuEntry("Move Left Arm", 3); // �� ��° �޴� ����
	glutAddMenuEntry("Move Right Leg", 4); // �� ��° �޴� ����
	glutAddMenuEntry("Move Left Leg", 5); // �ټ� ��° �޴� ����
	glutAttachMenu(GLUT_RIGHT_BUTTON); // ���콺 ��Ŭ���� �ϸ� �޴��� ��Ÿ��
	glutDisplayFunc(MyDisplay); // Display Event�� �߻��� ������ MyDisplay�� ȣ���ϵ��� ���
	glutReshapeFunc(MyReshape); // ȭ���� �ٽ� �׷��� �� ������ MyReshape�� ȣ���ϵ��� ���
	glutKeyboardFunc(MyKeyboard); // Keyboard Event�� �߻��� ������ MyKeyboard�� ȣ���ϵ��� ���
	glutMouseFunc(MyMouse); // Mouse Event�� �߻��� ������ MyMouse�� ȣ���ϵ��� ���
	glutIdleFunc(MyIdle); // Event�� ������ MyIdle�� ȣ���ϵ��� ���
	glutMainLoop(); // GLUT Event ó�� Loop ����
	return 0;
}