/*******************************************************************************************************/
/*                                       HW#4-2 : 전신 Can Robot 모델링                                */
/*  작성자 : 이승현                                                            날짜 : 2021년 10월 27일 */
/*                                                                                                     */
/* 문제 정의 :                                                                                         */
/* 1. 행렬 스택을 이용하여 Can Robot을 구현한다.                                                       */
/* 기능 :                                                                                              */
/* 1. 메뉴에서 'Move Head'를 누르면 머리가 움직였다가 원래 자세로 돌아온다.                            */
/* 2. 메뉴에서 'Move Right Arm'를 누르면 오른팔이 움직였다가 원래 자세로 돌아온다.                     */
/* 3. 메뉴에서 'Move Left Arm'를 누르면 왼팔이 움직였다가 원래 자세로 돌아온다.                        */
/* 4. 메뉴에서 'Move Right Leg'를 누르면 오른다리가 움직였다가 원래 자세로 돌아온다.                   */
/* 5. 메뉴에서 'Move Left Leg'를 누르면 왼쪽다리가 움직였다가 원래 자세로 돌아온다.                    */
/*******************************************************************************************************/

#include <gl/glut.h>

bool headMove, leftArmMove, rightArmMove, leftLegMove, rightLegMove; // 각각의 신체 부위의 움직임을 제어하기 위한 변수
bool headMoveToggle, leftArmMoveToggle, rightArmMoveToggle, leftLegMoveToggle, rightLegMoveToggle; // 각각의 신체 부위의 움직임을 제어하기 위한 변수
float head, leftArm[2], rightArm[2], leftLeg, rightLeg, body; // 각각의 신체 부위의 움직이는 각도를 정하기 위한 변수

// 메뉴를 설정함
void MyMenu(int value)
{
	switch (value)
	{
	case 1:
		headMove = true; // 첫 번째 메뉴 클릭 시 머리를 움직임
		headMoveToggle = true; // 머리를 움직였다가 원래 상태로 돌아오도록 함
		break;
	case 2:
		rightArmMove = true; // 두 번째 메뉴 클릭 시 오른팔을 움직임
		rightArmMoveToggle = true; // 오른팔을 움직였다가 원래 상태로 돌아오도록 함
		break;
	case 3:
		leftArmMove = true; // 세 번째 메뉴 클릭 시 왼팔을 움직임
		leftArmMoveToggle = true; // 왼팔을 움직였다가 원래 상태로 돌아오도록 함
		break;
	case 4:
		rightLegMove = true; // 네 번째 메뉴 클릭 시 오른다리를 움직임
		rightLegMoveToggle = true; // 오른다리를 움직였다가 원래 상태로 돌아오도록 함
		break;
	case 5:
		leftLegMove = true; // 다섯 번째 메뉴 클릭 시 왼다리를 움직임
		leftLegMoveToggle = true; // 왼다리를 움직였다가 원래 상태로 돌아오도록 함
		break;
	}
}

// 초기 화면 설정
void MyInit()
{
	// 초기 화면에서 모든 신체 부분이 움직이지 않도록 함
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

	// 초기 화면에서의 머리, 팔, 다리 각도
	head = 0;
	leftArm[0] = -20;
	leftArm[1] = 0;
	rightArm[0] = 20;
	rightArm[1] = 0;
	leftLeg = -20;
	rightLeg = 20;
	body = 0;

	GLint menuID = glutCreateMenu(MyMenu); // 메뉴 생성
	glutAddMenuEntry("Move Head", 1); // 첫 번째 메뉴 생성
	glutAddMenuEntry("Move Right Arm", 2); // 두 번째 메뉴 생성
	glutAddMenuEntry("Move Left Arm", 3); // 세 번째 메뉴 생성
	glutAddMenuEntry("Move Right Leg", 4); // 네 번째 메뉴 생성
	glutAddMenuEntry("Move Left Leg", 5); // 다섯 번째 메뉴 생성
	glutAttachMenu(GLUT_RIGHT_BUTTON); // 마우스 우클릭을 하면 메뉴가 나타남
}

void MyDisplay()
{
	GLfloat mat_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat mat_specular[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat mat_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat light_position[] = { 10.0f, 15.0f, 10.0f, 0.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position); // 0번 광원 위치 정하기
	glLightfv(GL_LIGHT0, GL_AMBIENT, mat_ambient); // 주변광 정하기
	glLightfv(GL_LIGHT0, GL_DIFFUSE, mat_diffuse); // 분산광 정하기
	glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular); // 반사광 정하기

	glEnable(GL_LIGHTING); // 조명 사용
	glEnable(GL_LIGHT0); // 0번 광원 사용
	glEnable(GL_COLOR_MATERIAL); // 물체의 색상이 나오도록 함

	glEnable(GL_DEPTH_TEST); // 은면 제거
	glFrontFace(GL_CCW); // 앞면 설정 
	glEnable(GL_CULL_FACE); // 각 도형의 보이지 않는 뒷부분 제거


	glClearColor(0.0, 0.0, 0.0, 0.0); // 검은색으로 화면 지우기
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 색 버퍼, 깊이 버퍼를 삭제하여 화면에서 그림 지우기
	glMatrixMode(GL_MODELVIEW); // 모델뷰 행렬 선택
	glLoadIdentity(); // 모델뷰 행렬을 항등 행렬로 초기화
	glTranslatef(0.0, body, 0.0); // 다리 움직임에 따라 로봇의 위치 지정
	glRotatef(20, 0, 1, 1); // 로봇 전체 회전
	glPushMatrix(); // 몸에 관한 변환 행렬 시작
	glColor3f(0.2, 0.5, 0.5); // 몸 색깔 지정
	glScalef(1.0, 1.5, 1.0); // 몸 크기 지정
	glutSolidCube(1.0); // 몸
	glPopMatrix(); // 몸 그리기 끝
	glPushMatrix(); // 몸 장신구에 대한 변환 행렬 시작
	glTranslatef(0.0, 0.2, 0.5); // 장신구의 위치 지정
	glColor3f(0.5, 0.0, 0.0); // 장신구 색깔 지정
	glutSolidTorus(0.05, 0.3, 20, 20); // 몸 윗부분의 장신구 그리기
	glRotatef(45, 0, 0, 1); // 몸 윗부분의 장신구 회전(다이아 모양)
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
	glColor3f(0.5, 0.0, 0.0); // 빨간색 입
	glutSolidCube(1.0); // 입 그리기
	glPopMatrix(); // 입에 대한 변환 행렬 삭제
	glPopMatrix(); // 얼굴 위치에 관한 변환 행렬 삭제

	glColor3f(0.2, 0.5, 0.5); // 팔 색깔 지정
	glPushMatrix(); // 팔 그리기
	glTranslatef(-1.0 / 2 - 0.15 / 2, 0.3, 0.0); // 팔 위치 지정(몸의 왼쪽에 붙어있음)
	glTranslatef(0.15 / 2, 0.35 / 2, 0.0); // 회전 후 원래 자리로 돌아옴
	glRotatef(leftArm[0], 0, 0, 1); // 몸 옆에서 leftArm[0]도만큼 윗팔을 위로 움직이기
	glTranslatef(-0.15 / 2, -0.35 / 2, 0.0); // 왼팔은 우측 상단을 pivot으로 하여 회전
	glPushMatrix(); // 왼팔의 위쪽 부분에 대한 변환 행렬 저장
	glScalef(0.15, 0.35, 0.15); // 왼팔의 크기 지정
	glutSolidCube(1.0); // 왼팔(위쪽) 그리기
	glPopMatrix(); // 왼팔의 위쪽 부분의 크기에 대한 정보를 변환 행렬에서 삭제
	glPushMatrix(); // 왼팔의 위쪽 부분의 변환 행렬에 대한 정보를 저장한 채로 왼팔의 아랫쪽 부분 그리기
	glTranslatef(0.0, -0.35, 0.0); // 팔 위치 지정(팔 윗부분의 아래에 붙어있음)
	glTranslatef(0.15 / 2, 0.35 / 2, 0.0); // 회전 후 원래 자리로 돌아옴
	glRotatef(leftArm[1], 0, 0, 1); // 윗팔의 아래에서 leftArm[1]도만큼 아랫팔을 위로 움직이기
	glTranslatef(-0.15 / 2, -0.35 / 2, 0.0); // 왼팔은 우측 상단을 pivot으로 하여 회전
	glPushMatrix(); // 왼팔의 아랫쪽 부분에 대한 변환 행렬 저장
	glScalef(0.15, 0.35, 0.15); // 왼팔의 크기 지정
	glutSolidCube(1.0); // 왼팔(아래쪽) 그리기
	glPopMatrix(); // 왼팔의 아랫쪽 부분의 크기에 대한 정보를 변환 행렬에서 삭제
	glTranslatef(0.0, -0.35 / 2 , 0.0); // 왼손이 왼팔의 끝에 위치하도록 함
	glutSolidCube(0.2); // 왼손 그리기
	glTranslatef(-0.4, -0.2, 0.0); // 주전자의 위치 지정
	glRotatef(180, 0, 1, 0); // 주전자를 y축 기준으로 180도 회전
	glColor3f(0.5, 0.2, 0.3); // 주전자의 색깔 지정
	glutSolidTeapot(0.4); // 왼손에 주전자를 쥐고 있는 형태로 그리기
	glPopMatrix(); // 주전자 + 왼손 + 왼팔의 아랫쪽 부분에 대한 변환 행렬 삭제
	glPopMatrix(); // 왼팔의 위쪽 부분에 대한 변환 행렬 삭제(왼손 + 왼팔 그리기 끝)

	glPushMatrix(); // 오른손 + 오른팔 그리기
	glColor3f(0.2, 0.5, 0.5); // 오른팔의 색상 지정
	glTranslatef(1.0 / 2 + 0.15 / 2, 0.2, 0.0); // 오른팔은 몸의 오른쪽에 붙어있도록 함
	glTranslatef(-0.15 / 2, 0.7 / 2, 0.0); // 회전 후 원래 자리로 돌아옴
	glRotatef(rightArm[0], 0, 0, 1); // 몸 옆에서 rightArm[0]도 만큼 윗팔을 위로 움직이기
	glTranslatef(0.15 / 2, -0.7 / 2, 0.0); // 오른팔은 좌측 상단을 pivot으로 하여 회전
	glPushMatrix(); // 오른팔의 윗쪽 부분에 대한 변환 행렬 저장
	glScalef(0.15, 0.35, 0.15); // 오른팔의 크기 지정
	glutSolidCube(1.0); // 오른팔(위쪽) 그리기
	glPopMatrix(); // 오른팔의 위쪽 부분의 크기에 대한 정보를 변환 행렬에서 삭제
	glPushMatrix(); // 오른팔의 위쪽 부분의 변환 행렬에 대한 정보를 저장한 채로 오른팔의 아랫쪽 부분 그리기
	glTranslatef(0.0, -0.35, 0.0); // 팔 위치 지정(팔 윗부분의 아래에 붙어있음)
	glTranslatef(-0.15 / 2, 0.35 / 2, 0.0); // 회전 후 원래 자리로 돌아옴
	glRotatef(rightArm[1], 0, 0, 1); // 윗팔의 아래에서 rightArm[1]도만큼 아랫팔을 위로 움직이기
	glTranslatef(0.15 / 2, -0.35 / 2, 0.0); // 오른팔은 좌측 상단을 pivot으로 하여 회전
	glPushMatrix(); // 오른팔의 아랫쪽 부분에 대한 변환 행렬 저장
	glScalef(0.15, 0.35, 0.15); // 오른팔의 크기 지정
	glutSolidCube(1.0); // 오른팔(아래쪽) 그리기
	glPopMatrix(); // 오른팔의 아랫쪽 부분의 크기에 대한 정보를 변환 행렬에서 삭제
	glTranslatef(0.0, -0.35 / 2, 0.0); // 오른손이 오른팔의 끝에 위치하도록 함
	glutSolidCube(0.2); // 오른손 그리기
	glPopMatrix(); // 오른손 + 오른팔의 아랫쪽 부분에 대한 변환 행렬 삭제
	glPopMatrix(); // 오른팔의 위쪽 부분에 대한 변환 행렬 삭제(오른손 + 오른팔 그리기 끝)

	glPushMatrix(); // 다리 그리기
	glTranslatef(0.0, -1.5 / 2 - 1.0 / 2, 0.0); // 두 다리의 위치 지정
	glPushMatrix(); // 두 다리의 위치에 대한 변환 행렬 저장
	glTranslatef(-0.3, 0.0, 0.0); // 왼다리는 몸의 왼쪽에 붙어있도록 지정
	glTranslatef(0.0, 1.0 / 2, 0.0); // 회전 후 원래 자리로 돌아옴
	glRotatef(leftLeg, 0, 0, 1); // leftLeg도만큼 왼다리를 옆으로 움직이기
	glTranslatef(0.0, -1.0 / 2, 0.0); // 다리는 가운데 상단을 pivot으로 하여 회전
	glPushMatrix(); // 왼다리에 대한 변환 행렬 저장
	glScalef(0.15, 1.0, 0.15); // 왼다리의 크기 지정
	glutSolidCube(1.0); // 왼다리 그리기
	glPopMatrix(); // 왼다리 크기에 대한 변환 행렬 삭제 (왼다리의 회전, 위치에 대한 정보는 저장되어 있음)
	glTranslatef(-(0.4 - 0.15) / 2, -1.0 / 2 - 0.15 / 2, 0.0); // 왼발은 왼다리의 끝에 위치함
	glScalef(0.4, 0.15, 0.3); // 왼발의 크기 지정
	glutSolidCube(1.0); // 왼발 그리기
	glPopMatrix(); // 왼다리 + 왼발에 대한 변환 행렬 삭제
	glTranslatef(0.3, 0.0, 0.0); // 오른다리는 몸의 오른쪽에 붙어있도록 지정
	glTranslatef(0.0, 1.0 / 2, 0.0); // 회전 후 원래 자리로 돌아옴
	glRotatef(rightLeg, 0, 0, 1); // rightLeg도만큼 오른다리를 옆으로 움직이기
	glTranslatef(0.0, -1.0 / 2, 0.0); // 다리는 가운데 상단을 pivot으로 하여 회전
	glPushMatrix(); // 오른다리에 대한 변환 행렬 저장
	glScalef(0.15, 1.0, 0.15); // 오른다리의 크기 지정
	glutSolidCube(1.0); // 오른다리 그리기
	glPopMatrix(); // 오른다리 크기에 대한 변환 행렬 삭제 (오른다리의 회전, 위치에 대한 정보는 저장되어 있음)
	glTranslatef((0.4 - 0.15) / 2, -1.0 / 2 - 0.15 / 2, 0.0); // 오른발은 오른다리의 끝에 위치함
	glScalef(0.4, 0.15, 0.3); // 오른발의 크기 지정
	glutSolidCube(1.0); // 오른발 그리기
	glPopMatrix(); // 오른다리 + 오른발에 대한 변환 행렬 삭제
	glPopMatrix(); // 두 다리의 위치에 대한 변환 행렬 삭제
	
	glutSwapBuffers(); // 전면 버퍼와 후면 버퍼를 바꿔서 화면에 출력
}

// 화면을 다시 그려야 할 때 호출되는 callback 함수
void MyReshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); // 뷰폿 설정
	glMatrixMode(GL_PROJECTION); // 투영 행렬 선택
	glLoadIdentity(); // 투영 행렬을 항등 행렬로 초기화
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0); // 원근 투영 생성
	glTranslatef(0.0, 0.0, -4.0); // z축에서 -4.0만큼 이동 (3D Primitive들이 보이도록 함)
}

// Keyboard Event가 발생했을 때 호출되는 callback 함수
void MyKeyboard(unsigned char key, int x, int y)
{
	if (key == 's' || key == 'S')
	{
		// 's'나 'S'를 누르면 움직이는 신체가 멈춤
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

// 함수 호출이 없을 때 처리하는 callback 함수
void MyIdle()
{
	if (headMove && head < 10) // 머리를 움직이라는 명령이 있을 때
	{
		head += 0.2; // head가 10도가 되기 전까지 증가하여 머리를 왼쪽으로 움직임
	}
	else if (headMoveToggle && !headMove && head > 0) // 머리를 원래 자리로 둬라는 명령이 있을 때
	{
		head -= 0.2; // head가 0도가 되기 전까지 감소하여 머리가 원래 자리로 돌아옴
	}
	if (headMoveToggle && head >= 10) // head가 10도 이상이고, 머리를 원래 자리로 두어야 할 때
	{
		headMove = false; // 더 이상 머리가 왼쪽으로 회전하지 않도록 함
	}
	if (head <= 0) // 머리가 원래 자리로 돌아왔을 때
	{
		headMoveToggle = false; // 더 이상 머리가 오른쪽으로 회전하지 않도록 함
	}
	
	if (rightArmMove && rightArm[0] < 60) // 오른팔을 움직이라는 명령이 있을 때
	{
		rightArm[0] += 0.5;
		rightArm[1] += 0.5; // 오른팔의 윗부분이 60도가 되기 전까지 오른팔을 위로 접음
	}
	else if (rightArmMoveToggle && !rightArmMove && rightArm[0] > 20) // 오른팔을 원래 상태로 둬라는 명령이 있을 때
	{
		rightArm[0] -= 0.5;
		rightArm[1] -= 0.5; // 원래 상태로 돌아올 때까지 오른팔을 펼침
	}
	if (rightArmMoveToggle && rightArm[0] >= 60) // 오른팔의 윗부분이 60도 이상이고, 오른팔을 원래 상태로 두어야 할 때
	{
		rightArmMove = false; // 더 이상 오른팔이 접히지 않도록 함
	}
	if (rightArm[0] <= 20) // 오른팔이 원래 상태로 돌아왔을 때
	{
		rightArmMoveToggle = false; // 더 이상 오른팔을 펼치지 않도록 함
	}
	

	if (leftArmMove && leftArm[0] > -60) // 왼팔을 움직이라는 명령이 있을 때
	{
		leftArm[0] -= 0.5;
		leftArm[1] -= 0.5; // 왼팔의 윗부분이 -60도가 되기 전까지 왼팔을 위로 접음
	}
	else if (leftArmMoveToggle && !leftArmMove && leftArm[0] < -20) // 왼팔을 원래 상태로 둬라는 명령이 있을 때
	{
		leftArm[0] += 0.5;
		leftArm[1] += 0.5; // 왼팔의 윗부분이 -20도가 되기 전까지 왼팔을 펼침
	}
	if (leftArmMove && leftArm[0] <= -60) // 왼팔의 윗부분이 -60도 이하이고, 왼팔을 원래 상태로 두어야 할 때
	{
		leftArmMove = false; // 더 이상 왼팔을 접지 않도록 함
	}
	if (leftArm[0] >= -20) // 왼팔이 원래 상태로 돌아왔을 때
	{
		leftArmMoveToggle = false; // 더 이상 왼팔을 펼치지 않도록 함
	}

	if (rightLegMove && rightLeg < 50) // 오른다리를 움직이라는 명령이 있을 때
	{
		rightLeg += 0.5; // 오른다리가 이루는 각이 50도가 될 때까지 바깥으로 벌림

		if (body > -0.6)
		{
			body -= 0.01; // 다리를 찢음에 따라 로봇의 위치가 내려감
		}
	}
	else if (rightLegMoveToggle && !rightLegMove && rightLeg > 20) // 오른다리를 원래 상태로 둬라는 명령이 있을 때
	{
		rightLeg -= 0.5; // 오른다리가 이루는 각이 20도가 될 때까지 안으로 모음

		if (body < 0)
		{
			body += 0.01; // 다리를 접음에 따라 로봇의 위치가 올라감
		}
	}
	if (rightLegMoveToggle && rightLeg >= 50) // 오른다리가 이루는 각이 50도 이상이고 오른다리를 원래 상태로 두어야 할 때
	{
		rightLegMove = false; // 더 이상 오른다리가 바깥으로 벌려지지 않도록 함
	}
	if (rightLeg <= 20) // 오른다리가 원래 상태로 돌아왔을 때
	{
		rightLegMoveToggle = false; // 더 이상 오른다리를 안으로 모으지 않도록 함
	}

	if (leftLegMove && leftLeg > -60) // 왼다리를 움직이라는 명령이 있을 때
	{
		leftLeg -= 0.5; // 왼다리가 이루는 각이 -60도가 될 때까지 바깥으로 벌림

		if (body > -0.6)
		{
			body -= 0.01; // 다리를 찢음에 따라 로봇의 위치가 내려감
		}
	}
	else if (leftLegMoveToggle && !leftLegMove && leftLeg < -20) // 왼다리를 원래 상태로 둬라는 명령이 있을 때
	{
		leftLeg += 0.5; // 왼다리가 이루는 각이 -20도가 될 때까지 안으로 모음

		if (body < 0)
		{
			body += 0.01; // 다리를 모음에 따라 로봇의 위치가 올라감
		}
	}
	if (leftLegMove && leftLeg <= -60) // 왼다리가 이루는 각이 -60도 이하이고 왼다리를 원래 상태로 둬라는 명령이 있을 때
	{
		leftLegMove = false; // 더 이상 왼다리가 바깥으로 벌려지지 않도록 함
	}
	if (leftLeg >= -20) // 왼다리가 원래 상태로 돌아왔을 때
	{
		leftLegMoveToggle = false; // 더 이상 왼다리가 안으로 모으지 않도록 함
	}

	glutPostRedisplay(); // Display Event를 발생시켜 로봇 다시 그리기
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); // Window OS와 세션 연결, GLUT Library 초기화
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // Display Mode 설정 (트루 컬러 모드 & 2개의 버퍼 사용)
	glutInitWindowPosition(0, 0); // 윈도우의 위치 지정
	glutInitWindowSize(500, 500); // 윈도우의 크기 지정
	glutCreateWindow("Can Robot Modeling"); // 윈도우 창 생성 및 이름 지정
	MyInit(); // 초기 설정 적용
	glutDisplayFunc(MyDisplay); // Display Event가 발생할 때마다 MyDisplay를 호출하도록 등록
	glutReshapeFunc(MyReshape); // 화면을 다시 그려야 할 때마다 MyReshape을 호출하도록 등록
	glutKeyboardFunc(MyKeyboard); // Keyboard Event가 발생할 때마다 MyKeyboard를 호출하도록 등록
	glutIdleFunc(MyIdle); // Event가 없으면 MyIdle을 호출하도록 등록
	glutMainLoop(); // GLUT Event 처리 Loop 진입
	return 0;
}