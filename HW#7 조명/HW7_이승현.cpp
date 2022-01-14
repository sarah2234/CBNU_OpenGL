/*******************************************************************************************************/
/*                                 HW#7 : 전신 Can Robot에 조명 효과 구현                              */
/*  작성자 : 이승현                                                            날짜 : 2021년 11월 24일 */
/*                                                                                                     */
/* 문제 정의 :                                                                                         */
/* 1. 로봇이 달리는 모션을 추가하고, 조명을 입힌다.                                                    */
/* 기능 :                                                                                              */
/* 1. 메뉴에서 'Move Head'를 누르면 머리가 움직였다가 원래 자세로 돌아온다.                            */
/* 2. 메뉴에서 'Move Right Arm'를 누르면 오른팔이 움직였다가 원래 자세로 돌아온다.                     */
/* 3. 메뉴에서 'Move Left Arm'를 누르면 왼팔이 움직였다가 원래 자세로 돌아온다.                        */
/* 4. 메뉴에서 'Move Right Leg'를 누르면 오른다리가 움직였다가 원래 자세로 돌아온다.                   */
/* 5. 메뉴에서 'Move Left Leg'를 누르면 왼쪽다리가 움직였다가 원래 자세로 돌아온다.                    */
/* 6. 'r'이나 'R'을 누르면 로봇이 뛴다.                                                                */
/* 7. s'나 'S'를 누르면 로봇이 움직임을 멈춘다.                                                        */
/* 8. 마우스를 좌클릭하면서 움직여서 광원의 각도를 바꾼다.                                             */
/* 9. 마우스의 휠을 움직여서 광원의 cutoff를 바꾼다.                                                   */
/*******************************************************************************************************/

#include <gl/glut.h>
#include <gl/freeglut_ext.h>

bool headMoveDirection[2], leftArmMoveDirection[2], rightArmMoveDirection[2], leftLegMoveDirection[2], rightLegMoveDirection[2]; // 각각의 신체 부위의 움직임을 제어하기 위한 변수
float head, leftArm[2], rightArm[2], leftLeg[2], rightLeg[2], body; // 각각의 신체 부위의 움직이는 각도를 정하기 위한 변수
bool run; // 뛰는 여부를 설정하는 변수

GLint Width = 500, Height = 500; // 화면의 크기
const GLfloat global_ambient[] = { 0.4, 0.4, 0.4, 1.0 }; // 전역 주변광
const GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 }; // 주변광
const GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 }; // 반사광
const GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 }; // 분산광
GLfloat light_position[] = { 0.0, 0.0, 1.0, 1.0 }; // 조명의 위치
GLfloat light_direction[] = { 0.0, 0.0, -1.0 }; // 조명의 방향
GLfloat light_cutoff = 90.0; // 조명 각도

// 초기 화면 설정
void MyInit()
{
	// 초기 화면에서 모든 신체 부분이 움직이지 않도록 함
	for (int i = 0; i < 2; i++)
	{
		headMoveDirection[i] = false;
		leftArmMoveDirection[i] = false;
		rightArmMoveDirection[i] = false;
		leftLegMoveDirection[i] = false;
		rightLegMoveDirection[i] = false;
	}

	// 초기 화면에서의 머리, 팔, 다리 각도
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

	run = false; // 초기 화면에서 로봇은 달리지 않음
}

// 메뉴를 설정함
void MyMenu(int value)
{
	switch (value)
	{
	case 1:
		MyInit();
		headMoveDirection[0] = true; // 첫 번째 메뉴 클릭 시 머리를 움직임
		break;
	case 2:
		MyInit();
		rightArmMoveDirection[0] = true; // 두 번째 메뉴 클릭 시 오른팔을 움직임
		break;
	case 3:
		MyInit();
		leftArmMoveDirection[0] = true; // 세 번째 메뉴 클릭 시 왼팔을 움직임
		break;
	case 4:
		MyInit();
		rightLegMoveDirection[0] = true; // 네 번째 메뉴 클릭 시 오른다리를 움직임
		break;
	case 5:
		MyInit();
		leftLegMoveDirection[0] = true; // 다섯 번째 메뉴 클릭 시 왼다리를 움직임
		break;
	}
}

// Display Event가 발생할 때 호출되는 callback 함수
void MyDisplay()
{
	glClearColor(0.0, 0.0, 0.0, 0.0); // 검은색으로 화면 지우기
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 색 버퍼, 깊이 버퍼를 삭제하여 화면에서 그림 지우기
	glMatrixMode(GL_MODELVIEW); // 모델뷰 행렬 선택
	glLoadIdentity(); // 모델뷰 행렬을 항등 행렬로 초기화

	glEnable(GL_LIGHTING); // 조명 사용
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient); // 전역 주변광 정하기 (카메라에 고정시킴)
	gluLookAt(2, 0, 4, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // 카메라 위치 지정
	glEnable(GL_LIGHT0); // 0번 광원 사용
	glLightfv(GL_LIGHT0, GL_POSITION, light_position); // 0번 광원 위치 정하기
	glLightfv(GL_LIGHT0, GL_AMBIENT, mat_ambient); // 주변광 정하기
	glLightfv(GL_LIGHT0, GL_DIFFUSE, mat_diffuse); // 분산광 정하기
	glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular); // 반사광 정하기
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.5); // 빛의 감쇠 효과 정하기
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction); // 광원의 방향 정하기
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, light_cutoff); // 광원의 각도 정하기
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 5.0);	// 광원 지수 정하기
	
	glEnable(GL_COLOR_MATERIAL); // 물체의 색상이 나오도록 함
	glEnable(GL_DEPTH_TEST); // 은면 제거
	glFrontFace(GL_CCW); // 앞면 설정 
	glEnable(GL_CULL_FACE); // 각 도형의 보이지 않는 뒷부분 제거
	glEnable(GL_NORMALIZE); // 벡터를 단위 벡터로 바꾸기 (glScalef 사용 시 법선 벡터에 영향이 가고, 이는 조명 계산에 영향을 미침)
	glShadeModel(GL_SMOOTH); // Gouraud Shading

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient); // 주변광에 대한 물체의 재질 정하기
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse); // 분산광에 대한 물체의 재질 정하기
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular); // 반사광에 대한 물체의 재질 정하기
	glMaterialf(GL_FRONT, GL_SHININESS, 50); // 물체의 광택 계수 정하기

	glPushMatrix(); // 몸에 관한 변환 행렬 시작
	glColor3f(0.2, 0.5, 0.5); // 몸 색깔 지정
	glRotatef(body, 1.0, 0.0, 0.0); // body에 따라 몸이 앞뒤로 움직임
	glPushMatrix(); // 몸에 대한 회전 행렬 저장
	glScalef(1.0, 1.5, 1.0); // 몸 크기 지정
	glutSolidCube(1.0); // 몸
	glPopMatrix(); // 몸 그리기 끝
	glPushMatrix(); // 몸 장신구에 대한 변환 행렬 시작
	glTranslatef(0.0, 0.2, 0.5); // 장신구의 위치 지정
	glColor3f(0.5, 0.0, 0.0); // 장신구 색깔 지정
	glutSolidTorus(0.05, 0.3, 20, 20); // 몸 윗부분의 장신구 그리기
	glRotatef(45, 0, 0, 1); // 몸 윗부분의 장신구 회전(다이아 모양)
	glTranslatef(0.0, 0.0, -0.1); // 장신구의 위치 지정
	glutSolidCube(0.3); // 몸 윗부분의 장신구 그리기
	glPopMatrix(); // 몸 윗부분의 장신구에 대한 변환 행렬 삭제
	glPushMatrix(); // 몸 아랫부분의 장신구에 대한 변환 행렬 시작
	glTranslatef(0.3, -0.5, 0.6); // 장신구의 위치 지정
	glColor3f(0.0, 0.3, 0.3); // 장신구의 색깔 지정
	glutSolidCube(0.1); // 몸 아랫부분의 장신구 그리기
	glPopMatrix(); // 몸 장신구에 대한 변환 행렬 삭제

	glPushMatrix(); // 목 그리기
	glTranslatef(0.0, 1.5 / 2 + 0.2 / 2, 0.0); // 목 위치 지정(몸의 위에 위치함)
	glColor3f(0.1, 0.3, 0.3); // 목 색깔 지정
	glutSolidCube(0.2); // 목
	glTranslatef(0.0, 1.0 / 2, 0.0); // 머리가 목 위에 위치하도록 함
	glTranslatef(0.0, -0.2 / 2 - 1.0 / 2, 0.0); // 회전 후 원래 위치로 돌아옴
	glRotatef(head, 0, 0, 1); // 목 위에서 머리가 head도만큼 회전
	glTranslatef(0.0, 0.2 / 2 + 1.0 / 2, 0.0); // 회전하기 위한 pivot 지정
	glColor3f(0.2, 0.5, 0.5); // 머리 색깔 지정
	glutSolidCube(1.0); // 머리
	glPushMatrix(); // 머리의 움직임에 따라 눈, 입 위치를 달리하도록 머리에 대한 변환행렬 저장
	glTranslatef(-0.3, 0.0, 1.0 / 2); // 머리에 있는 눈의 위치 지정
	glRotatef(90, 0, 0, 1); // Torus를 90도 회전
	glColor3f(0.5, 0.5, 1.0); // 파란색 눈 테두리
	glutSolidTorus(0.08, 0.14, 20, 20); // 왼쪽 눈 그리기
	glColor3f(0.0, 0.0, 0.0); // 검은 눈
	glutSolidSphere(0.08, 20, 20); // 왼쪽 눈동자 그리기
	glColor3f(1.0, 1.0, 1.0); // 흰색 동공
	glTranslatef(0.0, 0.0, 0.055); // 동공을 앞으로 꺼내서 보이도록 함
	glutSolidSphere(0.03, 20, 20); // 왼쪽 동공 그리기
	glPopMatrix(); // 왼쪽 눈에 대한 변환 행렬 삭제
	glPushMatrix(); // 오른쪽 눈에 대한 변환 행렬 시작
	glTranslatef(0.3, 0.0, 1.0 / 2); // 머리에 있는 눈의 위치 지정
	glRotatef(90, 0, 0, 1); // Torus를 90도 회전
	glColor3f(0.5, 0.5, 1.0); // 파란색 눈 테두리
	glutSolidTorus(0.08, 0.14, 20, 20); // 오른쪽 눈 그리기
	glColor3f(0.0, 0.0, 0.0); // 검은 눈
	glutSolidSphere(0.08, 20, 20); // 오른쪽 눈동자 그리기
	glColor3f(1.0, 1.0, 1.0); // 흰색 동공
	glTranslatef(0.0, 0.0, 0.055); // 동공을 앞으로 꺼내서 보이도록 함
	glutSolidSphere(0.03, 20, 20); // 오른쪽 동공 그리기
	glPopMatrix(); // 오른쪽 눈에 대한 변환 행렬 삭제
	glPushMatrix(); // 입에 대한 변환 행렬 시작
	glTranslatef(0.0, -0.25, 1.0 / 2 + 0.1 / 2); // 머리에 있는 입의 위치 지정
	glScalef(0.3, 0.1, 0.1); // 입 크기 지정
	glColor3f(0.8, 0.0, 0.0); // 빨간색 입
	glutSolidCube(1.0); // 입 그리기
	glPopMatrix(); // 입에 대한 변환 행렬 삭제
	glPopMatrix(); // 얼굴 위치에 관한 변환 행렬 삭제
	glPopMatrix(); // 몸에 대한 회전 행렬 삭제

	glColor3f(0.3, 0.8, 0.8); // 왼팔 색깔 지정
	glPushMatrix(); // 팔 그리기
	glTranslatef(-1.0 / 2 - 0.15 / 2, 0.3, 0.0); // 팔 위치 지정(몸의 왼쪽에 붙어있음)
	glTranslatef(0.15 / 2, 0.35 / 2, 0.0); // 회전 후 원래 자리로 돌아옴
	glRotatef(leftArm[0], 1, 0, 0); // 몸 옆에서 leftArm[0]도만큼 윗팔을 움직이기
	glTranslatef(-0.15 / 2, -0.35 / 2, 0.0); // 왼팔은 우측 상단을 pivot으로 하여 회전
	glPushMatrix(); // 왼팔의 위쪽 부분에 대한 변환 행렬 저장
	glScalef(0.15, 0.35, 0.15); // 왼팔의 크기 지정
	glutSolidCube(1.0); // 왼팔(위쪽) 그리기
	glPopMatrix(); // 왼팔의 위쪽 부분의 크기에 대한 정보를 변환 행렬에서 삭제
	glPushMatrix(); // 왼팔의 위쪽 부분의 변환 행렬에 대한 정보를 저장한 채로 왼팔의 아랫쪽 부분 그리기
	glTranslatef(0.0, -0.35, 0.0); // 팔 위치 지정(팔 윗부분의 아래에 붙어있음)
	glTranslatef(0.15 / 2, 0.35 / 2, 0.0); // 회전 후 원래 자리로 돌아옴
	glRotatef(leftArm[1], 1, 0, 0); // 윗팔의 아래에서 leftArm[1]도만큼 아랫팔을 움직이기
	glTranslatef(-0.15 / 2, -0.35 / 2, 0.0); // 왼팔은 우측 상단을 pivot으로 하여 회전
	glPushMatrix(); // 왼팔의 아랫쪽 부분에 대한 변환 행렬 저장
	glScalef(0.15, 0.35, 0.15); // 왼팔의 크기 지정
	glutSolidCube(1.0); // 왼팔(아래쪽) 그리기
	glPopMatrix(); // 왼팔의 아랫쪽 부분의 크기에 대한 정보를 변환 행렬에서 삭제
	glTranslatef(0.0, -0.35 / 2, 0.0); // 왼손이 왼팔의 끝에 위치하도록 함
	glColor3f(0.2, 0.5, 0.5); // 왼손 색깔 지정
	glutSolidCube(0.2); // 왼손 그리기
	glFrontFace(GL_CW); // 주전자의 앞면 설정
	glTranslatef(-0.4, -0.2, 0.5); // 주전자의 위치 지정
	glRotatef(230, 0, 1, 0); // 주전자를 y축 기준으로 230도 회전
	glColor3f(0.5, 0.2, 0.3); // 주전자의 색깔 지정
	glutSolidTeapot(0.4); // 왼손에 주전자를 쥐고 있는 형태로 그리기
	glPopMatrix(); // 주전자 + 왼손 + 왼팔의 아랫쪽 부분에 대한 변환 행렬 삭제
	glPopMatrix(); // 왼팔의 위쪽 부분에 대한 변환 행렬 삭제(왼손 + 왼팔 그리기 끝)

	glFrontFace(GL_CCW); // 로봇의 앞면 설정
	glPushMatrix(); // 오른손 + 오른팔 그리기
	glColor3f(0.3, 0.8, 0.8); // 오른팔의 색상 지정
	glTranslatef(1.0 / 2 + 0.15 / 2, 0.2, 0.0); // 오른팔은 몸의 오른쪽에 붙어있도록 함
	glTranslatef(-0.15 / 2, 0.7 / 2, 0.0); // 회전 후 원래 자리로 돌아옴
	glRotatef(rightArm[0], 1, 0, 0); // 몸 옆에서 rightArm[0]도 만큼 윗팔을 움직이기
	glTranslatef(0.15 / 2, -0.7 / 2, 0.0); // 오른팔은 좌측 상단을 pivot으로 하여 회전
	glPushMatrix(); // 오른팔의 윗쪽 부분에 대한 변환 행렬 저장
	glScalef(0.15, 0.35, 0.15); // 오른팔의 크기 지정
	glutSolidCube(1.0); // 오른팔(위쪽) 그리기
	glPopMatrix(); // 오른팔의 위쪽 부분의 크기에 대한 정보를 변환 행렬에서 삭제
	glPushMatrix(); // 오른팔의 위쪽 부분의 변환 행렬에 대한 정보를 저장한 채로 오른팔의 아랫쪽 부분 그리기
	glTranslatef(0.0, -0.35, 0.0); // 팔 위치 지정(팔 윗부분의 아래에 붙어있음)
	glTranslatef(-0.15 / 2, 0.35 / 2, 0.0); // 회전 후 원래 자리로 돌아옴
	glRotatef(rightArm[1], 1, 0, 0); // 윗팔의 아래에서 rightArm[1]도만큼 아랫팔을 움직이기
	glTranslatef(0.15 / 2, -0.35 / 2, 0.0); // 오른팔은 좌측 상단을 pivot으로 하여 회전
	glPushMatrix(); // 오른팔의 아랫쪽 부분에 대한 변환 행렬 저장
	glScalef(0.15, 0.35, 0.15); // 오른팔의 크기 지정
	glutSolidCube(1.0); // 오른팔(아래쪽) 그리기
	glPopMatrix(); // 오른팔의 아랫쪽 부분의 크기에 대한 정보를 변환 행렬에서 삭제
	glTranslatef(0.0, -0.35 / 2, 0.0); // 오른손이 오른팔의 끝에 위치하도록 함
	glColor3f(0.2, 0.5, 0.5); // 오른손 색깔 지정
	glutSolidCube(0.2); // 오른손 그리기
	glPopMatrix(); // 오른손 + 오른팔의 아랫쪽 부분에 대한 변환 행렬 삭제
	glPopMatrix(); // 오른팔의 위쪽 부분에 대한 변환 행렬 삭제(오른손 + 오른팔 그리기 끝)

	glPushMatrix(); // 다리 그리기
	glTranslatef(0.0, -1.5 / 2 - 0.5 / 2, 0.0); // 두 다리의 위치 지정
	glPushMatrix(); // 두 다리의 위치에 대한 변환 행렬 저장
	glTranslatef(-0.3, 0.0, 0.0); // 왼다리는 몸의 왼쪽에 붙어있도록 지정
	glColor3f(0.3, 0.8, 0.8); // 왼다리의 색상 지정
	glTranslatef(0.0, 1.0 / 2, 0.0); // 회전 후 원래 자리로 돌아옴
	glRotatef(leftLeg[0], 1, 0, 0); // leftLeg[0]도만큼 왼다리의 위쪽 부분을 움직이기
	glTranslatef(0.0, -1.0 / 2, 0.0); // 다리의 가운데 상단을 pivot으로 하여 회전
	glPushMatrix(); // 왼다리의 위쪽 부분에 대한 변환 행렬 저장
	glScalef(0.15, 0.5, 0.15); // 왼다리의 위쪽 부분 크기 지정
	glutSolidCube(1.0); // 왼다리의 위쪽 부분 그리기
	glPopMatrix(); // 왼다리의 위쪽 부분에 대한 크기 행렬 삭제
	glPushMatrix(); // 왼다리의 위쪽 부분의 변환 행렬에 대한 정보를 저장한 채로 왼다리의 아래쪽 부분 그리기
	glTranslatef(0.0, -0.5 / 2, 0.0); // 왼다리의 아래쪽 부분의 위치 지정
	glRotatef(leftLeg[1], 1, 0, 0); // leftLeg[1]도만큼 왼다리의 아래쪽 부분을 움직이기
	glTranslatef(0.0, -0.5 / 2, 0.0); // 다리의 가운데 상단을 pivot으로 하여 회전
	glPushMatrix(); // 왼다리의 아래쪽 부분에 대한 변환 행렬 저장
	glScalef(0.15, 0.5, 0.15); // 왼다리의 아래쪽 부분 크기 지정
	glutSolidCube(1.0); // 왼다리의 아래쪽 부분 그리기
	glPopMatrix(); // 왼다리 크기에 대한 변환 행렬 삭제 (왼다리의 회전, 위치에 대한 정보는 저장되어 있음)
	glTranslatef(-(0.15 - 0.15) / 2, -0.5 / 2 - 0.15 / 2, 0.1); // 왼발은 왼다리의 끝에 위치함
	glScalef(0.2, 0.15, 0.5); // 왼발의 크기 지정
	glColor3f(0.2, 0.5, 0.5); // 왼발 색깔 지정
	glutSolidCube(1.0); // 왼발 그리기
	glPopMatrix(); 
	glPopMatrix(); // 왼다리 + 왼발에 대한 변환 행렬 삭제
	glTranslatef(0.3, 0.0, 0.0); // 오른다리는 몸의 오른쪽에 붙어있도록 지정
	glColor3f(0.3, 0.8, 0.8); // 오른다리의 색상 지정
	glTranslatef(0.0, 1.0 / 2, 0.0); // 회전 후 원래 자리로 돌아옴
	glRotatef(rightLeg[0], 1, 0, 0); // rightLeg[0]도만큼 오른다리를 움직이기
	glTranslatef(0.0, -1.0 / 2, 0.0); // 다리의 가운데 상단을 pivot으로 하여 회전
	glPushMatrix(); // 오른다리에 대한 변환 행렬 저장
	glScalef(0.15, 0.5, 0.15); // 오른다리의 크기 지정
	glutSolidCube(1.0); // 오른다리의 윗쪽 부분 그리기
	glPopMatrix(); // 오른다리의 위쪽 부분에 대한 크기 행렬 삭제
	glPushMatrix(); // 오른다리의 위쪽 부분의 변환 행렬에 대한 정보를 저장한 채로 오른다리의 아래쪽 부분 그리기
	glTranslatef(0.0, -0.25, 0.0); // 오른다리의 아래쪽 부분의 위치 지정
	glRotatef(rightLeg[1], 1, 0, 0); // rightLeg[1]도만큼 오른다리의 아래쪽 부분을 움직이기
	glTranslatef(0.0, -0.25, 0.0); // 다리의 가운데 상단을 pivot으로 하여 회전
	glPushMatrix(); // 오른다리의 아래쪽 부분에 대한 변환 행렬 저장
	glScalef(0.15, 0.5, 0.15); // 오른다리의 아래쪽 부분 크기 지정
	glutSolidCube(1.0); // 오른다리의 아래쪽 부분 그리기
	glPopMatrix(); // 오른다리 크기에 대한 변환 행렬 삭제 (오른다리의 회전, 위치에 대한 정보는 저장되어 있음)
	glTranslatef((0.15 - 0.15) / 2, -0.5 / 2 - 0.15 / 2, 0.1); // 오른발은 오른다리의 끝에 위치함
	glScalef(0.2, 0.15, 0.5); // 오른발의 크기 지정
	glColor3f(0.2, 0.5, 0.5); // 오른발 색깔 지정
	glutSolidCube(1.0); // 오른발 그리기
	glPopMatrix(); // 오른다리 + 오른발에 대한 변환 행렬 삭제
	glPopMatrix(); // 두 다리의 위치에 대한 변환 행렬 삭제

	glutSwapBuffers(); // 전면 버퍼와 후면 버퍼를 바꿔서 화면에 출력
}

// 화면을 다시 그려야 할 때 호출되는 callback 함수
void MyReshape(int w, int h)
{
	Width = w; // 바뀐 화면의 너비 저장
	Height = h; // 바뀐 화면의 높이 저장
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); // 뷰폿 설정
	glMatrixMode(GL_PROJECTION); // 투영 행렬 선택
	glLoadIdentity(); // 투영 행렬을 항등 행렬로 초기화
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0); // 원근 투영 생성
}

// Keyboard Event가 발생했을 때 호출되는 callback 함수
void MyKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 's':
	case 'S':
		// 's'나 'S'를 누르면 움직이는 신체가 멈춤
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
		// 'r'나 'R'를 누르면 로봇이 달림
		if (run)
			return; // 이미 달리고 있으면 함수 종료
		run = true; // 달리기 시작
		body = 20; // 몸을 앞으로 숙임
		rightArmMoveDirection[0] = true; // 오른팔을 앞으로 움직이기
		rightArmMoveDirection[1] = false;
		leftArmMoveDirection[0] = false;
		leftArmMoveDirection[1] = true; // 왼팔을 뒤로 움직이기
		rightLegMoveDirection[0] = false;
		rightLegMoveDirection[1] = true; // 오른다리를 뒤로 움직이기
		leftLegMoveDirection[0] = true; // 왼다리를 앞으로 움직이기
		leftLegMoveDirection[1] = false;
		break;
	}
}

// 함수 호출이 없을 때 처리하는 callback 함수
void MyIdle()
{
	if (headMoveDirection[0] && head <= 10) // 머리를 움직이라는 명령이 있을 때
	{
		head += 0.5; // head가 10도가 되기 전까지 증가하여 머리를 왼쪽으로 움직임
	}
	else if (headMoveDirection[1] && head > 0) // 머리를 원래 자리로 둬라는 명령이 있을 때
	{
		head -= 0.5; // head가 0도가 되기 전까지 감소하여 머리가 원래 자리로 돌아옴
	}
	else if (head <= 0) // head가 원상태로 돌아왔을 때
	{
		headMoveDirection[1] = false; // 더 이상 머리가 오른쪽으로 회전하지 않도록 함
	}
	if (head >= 10) // head가 10도 이상이고, 머리를 원래 자리로 두어야 할 때
	{
		headMoveDirection[0] = false; // 더 이상 머리가 왼쪽으로 회전하지 않도록 함
		headMoveDirection[1] = true; // 머리가 오른쪽으로 회전하도록 함
	}

	if (rightArmMoveDirection[0]) // 오른팔을 앞으로 움직이라는 명령이 있을 때
	{
		rightArm[0] -= 2.5; // 오른팔의 윗부분이 -40도가 되기 전까지 오른팔을 위로 들기
		if (rightArm[1] > -40)
			rightArm[1] -= 2.5; // 오른팔의 아랫부분이 다 접히기 전까지 계속 접기
	}
	else if (rightArmMoveDirection[1]) // 오른팔을 뒤로 움직이라는 명령이 있을 때
	{
		if (!run) // 뛰라는 명령이 없을 때
		{
			rightArm[0] += 2.5;
			rightArm[1] += 2.5; // 오른팔의 윗부분이 -40도가 되기 전까지 오른팔을 펼치면서 뒤로 들기
		}
		else if (run) // 뛰라는 명령이 있을 때
		{
			rightArm[0] += 2.5; // 오른팔을 접은 채 팔을 뒤로 들음
		}
	}
	if (rightArmMoveDirection[0] && rightArm[0] <= -40) // 오른팔의 윗부분이 충분히 위로 들려졌을 때
	{
		rightArmMoveDirection[0] = false;
		rightArmMoveDirection[1] = true; // 오른팔을 뒤로 들기
	}
	else if (!run && rightArm[0] >= 0) // (뛰라는 명령 없음) 오른팔이 원래 상태로 돌아왔을 때
	{
		rightArmMoveDirection[1] = false; // 더 이상 오른팔을 뒤로 들지 않도록 함
	}
	else if (run && rightArm[0] >= 40) // 뛰고 있는 도중 오른팔이 충분히 뒤로 들려졌을 때
	{
		rightArmMoveDirection[0] = true; // 오른팔을 앞으로 들기
		rightArmMoveDirection[1] = false;
	}

	if (leftArmMoveDirection[0]) // 왼팔을 앞으로 움직이라는 명령이 있을 때
	{
		leftArm[0] -= 2.5; // 왼팔의 윗부분이 -40도가 되기 전까지 왼팔을 위로 들기
		if (leftArm[1] > -40)
			leftArm[1] -= 2.5; // 왼팔의 아랫부분이 다 접히기 전까지 계속 접기
	}
	else if (leftArmMoveDirection[1]) // 왼팔을 뒤로 움직이라는 명령이 있을 때
	{
		if (!run) // 뛰라는 명령이 없을 때
		{
			leftArm[0] += 2.5;
			leftArm[1] += 2.5; // 왼팔의 윗부분이 -40도가 되기 전까지 왼팔을 펼침
		}
		else if (run) // 뛰라는 명령이 있을 때
		{
			leftArm[0] += 2.5; // 왼팔을 접은 채 팔을 뒤로 들음
		}
	}
	if (leftArmMoveDirection[0] && leftArm[0] <= -40) // 왼팔의 윗부분이 충분히 위로 들려졌을 때
	{
		leftArmMoveDirection[0] = false;
		leftArmMoveDirection[1] = true; // 왼팔을 뒤로 들기
	}
	else if (!run && leftArm[0] >= 0) // (뛰라는 명령 없음) 왼팔이 원래 상태로 돌아왔을 때
	{
		leftArmMoveDirection[1] = false; // 더 이상 왼팔을 뒤로 들지 않도록 함
	}
	else if (run && leftArm[0] >= 40) // 뛰고 있는 도중 왼팔이 충분히 뒤로 들려졌을 때
	{
		leftArmMoveDirection[0] = true; // 왼팔을 위로 들기
		leftArmMoveDirection[1] = false;
	}
	
	if (rightLegMoveDirection[0]) // 오른다리를 앞으로 움직이라는 명령이 있을 때
	{
		rightLeg[0] -= 2.5; // 윗다리 앞으로 들기
		if ((!run && rightLeg[0] < 0) || (run && -40 < rightLeg[0] && rightLeg[0] < 0)) // 다리를 앞으로 들면서 접어야 할 때
			rightLeg[1] += 2.5; // 아래 다리 접기
		else if ((!run && rightLeg[0] > 0) || (run && 0 < rightLeg[0] && rightLeg[0] < 40)) // 다리를 앞으로 들면서 펴야 할 때
			rightLeg[1] -= 2.5; // 아래 다리 펴기
	}
	else if (rightLegMoveDirection[1]) // 오른다리를 뒤로 움직이라는 명령이 있을 때
	{
		rightLeg[0] += 2.5; // 윗다리 뒤로 들기
		if (!run || (run && -40 < rightLeg[0] && rightLeg[0] < 0)) // 다리를 뒤로 들면서 펴야 할 때
			rightLeg[1] -= 2.5; // 아래 다리 펴기
		else if (run && 0 < rightLeg[0] && rightLeg[0] < 40) // 다리를 뒤로 들면서 접어야 할 때
			rightLeg[1] += 2.5; // 아래 다리 접기
	}
	if (rightLegMoveDirection[0] && rightLeg[0] <= -40) // 오른다리의 윗부분이 충분히 위로 들려졌을 때
	{
		rightLegMoveDirection[0] = false;
		rightLegMoveDirection[1] = true; // 오른다리를 뒤로 들기
	}
	else if (!run && rightLeg[0] >= 0) // (뛰라는 명령 없음) 오른다리가 원래 상태로 돌아왔을 때
	{
		rightLegMoveDirection[1] = false; // 더 이상 오른다리를 뒤로 들지 않도록 함
	}
	else if (run && rightLeg[0] >= 40) // 뛰고 있는 도중 오른다리가 충분히 뒤로 들려졌을 때
	{
		rightLegMoveDirection[0] = true; // 오른다리를 위로 들기
		rightLegMoveDirection[1] = false;
	}

	if (leftLegMoveDirection[0]) // 왼다리를 앞으로 움직이라는 명령이 있을 때
	{
		leftLeg[0] -= 2.5; // 윗다리 앞으로 들기
		if ((!run && leftLeg[0] < 0) || (run && -40 < leftLeg[0] && leftLeg[0] < 0)) // 다리를 앞으로 들면서 접어야 할 때
			leftLeg[1] += 2.5; // 아래 다리 접기
		else if ((!run && leftLeg[0] > 0) || (run && 0 < leftLeg[0] && leftLeg[0] < 40)) // 다리를 앞으로 들면서 펴야 할 때
			leftLeg[1] -= 2.5; // 아래 다리 펴기
	}
	else if (leftLegMoveDirection[1]) // 왼다리를 뒤로 움직이라는 명령이 있을 때
	{
		leftLeg[0] += 2.5; // 윗다리 뒤로 들기
		if (!run || (run && -40 < leftLeg[0] && leftLeg[0] < 0)) // 다리를 뒤로 들면서 펴야 할 때
			leftLeg[1] -= 2.5; // 아래 다리 펴기
		else if (run && 0 < leftLeg[0] && leftLeg[0] < 40) // 다리를 뒤로 들면서 접어야 할 때
			leftLeg[1] += 2.5; // 아래 다리 접기
	}
	if (leftLegMoveDirection[0] && leftLeg[0] <= -40) // 왼다리의 윗부분이 충분히 위로 들려졌을 때
	{
		leftLegMoveDirection[0] = false;
		leftLegMoveDirection[1] = true; // 왼다리를 뒤로 들기
	}
	else if (!run && leftLeg[0] >= 0) // (뛰라는 명령 없음) 왼다리가 원래 상태로 돌아왔을 때
	{
		leftLegMoveDirection[1] = false; // 더 이상 왼다리를 뒤로 들지 않도록 함
	}
	else if (run && leftLeg[0] >= 40) // 뛰고 있는 도중 왼다리가 충분히 뒤로 들려졌을 때
	{
		leftLegMoveDirection[0] = true; // 왼다리를 위로 들기
		leftLegMoveDirection[1] = false;
	}

	glutPostRedisplay(); // Display Event를 발생시켜 로봇 다시 그리기
}

// Mouse Motion Event를 처리하는 callback 함수
void MyMouseMove(int x, int y)
{
	light_direction[0] = (x - Width / 2); // 광원의 방향을 마우스의 위치에 따라 설정
	light_direction[1] = (Height - y - Height / 2); // GLUT 좌표계 상의 y축 점을 GL 좌표계로 맞춤
}

// Mouse Event를 처리하는 callback 함수
void MyMouse(GLint button, GLint state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) // 좌클릭 했을 때
	{
		glutMotionFunc(MyMouseMove); // 마우스 움직임을 처리하는 함수 호출
		glutPostRedisplay(); // Display Event 발생시켜 로봇 다시 그리기
	}
	else if (button == 3 && light_cutoff < 90) // 위로 스크롤했을 때
	{
		light_cutoff += 1; // 광원이 비추는 영역이 넓어짐
		glutPostRedisplay(); // Display Event 발생시켜 로봇 다시 그리기
	}
	else if (button == 4 && light_cutoff > 0) // 아래로 스크롤했을 때
	{
		light_cutoff -= 1; // 광원이 비추는 영역이 좁아짐
		glutPostRedisplay(); // Display Event 발생시켜 로봇 다시 그리기
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); // Window OS와 세션 연결, GLUT Library 초기화
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // Display Mode 설정 (트루 컬러 모드 & 2개의 버퍼 사용)
	glutInitWindowPosition(0, 0); // 윈도우의 위치 지정
	glutInitWindowSize(500, 500); // 윈도우의 크기 지정
	glutCreateWindow("Can Robot Modeling"); // 윈도우 창 생성 및 이름 지정
	MyInit(); // 초기 설정 적용
	GLint menuID = glutCreateMenu(MyMenu); // 메뉴 생성
	glutAddMenuEntry("Move Head", 1); // 첫 번째 메뉴 생성
	glutAddMenuEntry("Move Right Arm", 2); // 두 번째 메뉴 생성
	glutAddMenuEntry("Move Left Arm", 3); // 세 번째 메뉴 생성
	glutAddMenuEntry("Move Right Leg", 4); // 네 번째 메뉴 생성
	glutAddMenuEntry("Move Left Leg", 5); // 다섯 번째 메뉴 생성
	glutAttachMenu(GLUT_RIGHT_BUTTON); // 마우스 우클릭을 하면 메뉴가 나타남
	glutDisplayFunc(MyDisplay); // Display Event가 발생할 때마다 MyDisplay를 호출하도록 등록
	glutReshapeFunc(MyReshape); // 화면을 다시 그려야 할 때마다 MyReshape을 호출하도록 등록
	glutKeyboardFunc(MyKeyboard); // Keyboard Event가 발생할 때마다 MyKeyboard를 호출하도록 등록
	glutMouseFunc(MyMouse); // Mouse Event가 발생할 때마다 MyMouse를 호출하도록 등록
	glutIdleFunc(MyIdle); // Event가 없으면 MyIdle을 호출하도록 등록
	glutMainLoop(); // GLUT Event 처리 Loop 진입
	return 0;
}