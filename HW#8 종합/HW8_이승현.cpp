/*******************************************************************************************************/
/*                                  HW#8 : 지금까지 배운 기술 종합                                     */
/*  작성자 : 이승현                                                            날짜 : 2021년 12월 09일 */
/*                                                                                                     */
/* 문제 정의 :                                                                                         */
/* 지금까지 수행한 실습과제의 내용을 종합하여 객체를 모델링하고, 콜백프로그래밍, 모델변환, 시점변환,   */
/* 투영변환, 뷰폿변환, 가시성검사, 조명, 텍스춰 등 수업시간에 배웠던 기술이 모두 쓰일 수 있도록        */
/* 프로그램을 만들어보시오.                                                                            */
/* 기능 :                                                                                              */
/* 1. x축에서의 마우스의 움직임을 따라 춘식이가 얼굴을 움직입니다.                                     */
/* 2. 마우스 우클릭으로 나타는 메뉴 중,‘Feed’를 선택하면 춘식이가 사과를 먹습니다.                   */
/* 3. 메뉴 중 ‘Play’를 누르면 춘식이가 물속에서 즐거워하는 듯한 모습을 보입니다.                     */
/* 4. 메뉴 중 ‘Stop’을 누르면 춘식이가 하던 것을 멈춥니다.                                           */
/* 5. 춘식이의 포만감과 행복지수는 실시간으로 하단에서 확인할 수 있습니다.                             */
/* 6. 키보드의 오른쪽과 왼쪽 방향키로 카메라를 회전시켜 춘식이의 모습을 360도에서 볼 수 있습니다.      */
/*******************************************************************************************************/

#include <stdio.h>
#include <gl/glut.h>
#include <math.h>
#include <gl/GLAUX.H>
#pragma comment(lib, "glaux.lib")
#pragma comment (lib,"legacy_stdio_definitions.lib")
#define PI 3.14159

GLsizei width = 1024, height = 700;
GLfloat ref_plane[4] = { 1, 1, 1, 0 }; // 텍스처 기준 평면
float full = 100, happiness = 100; // 포만감, 행복도
bool feed = false, play = false; // 먹기, 놀기
GLfloat camera[3]; // 카메라 초점 방향
GLfloat headAngle[4], rightArmAngle[4], leftArmAngle[4]; // 신체의 각도
GLfloat chunsikPos[3], tubePos[3]; // 신체, 튜브의 위치
bool bodyToggle, headToggle, rightArmToggle, leftArmToggle; // 신체 움직임 제어
const GLfloat global_ambient[] = { 0.4, 0.4, 0.4, 1.0 }; // 전역 주변광
const GLfloat ambient[] = { 1.0, 1.0, 1.0, 1.0 }; // 주변광
const GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 }; // 반사광
const GLfloat diffuse[] = { 0.6, 0.6, 0.6, 1.0 }; // 분산광
const GLfloat chunsik_specular[] = { 0, 0, 0, 1.0 }; // 춘식이의 반사광
const GLfloat tube_specular[] = { 0.8, 0.8, 0.8, 1.0 }; // 튜브의 반사광
const GLfloat sun_emission[] = { 0.5, 0.5, 0.5, 1.0 }; // 태양의 발광색
const GLfloat emission[] = { 0, 0, 0, 1.0 }; // 기타 물체에 대한 발광색
GLfloat light_position[] = { 0.0, 0.0, 1.0, 1.0 }; // 조명의 위치

GLUquadricObj* qobj = gluNewQuadric(); // 새로운 Quadric 생성

// 춘식이 움직임 초기화하는 함수
void MyChunsikMovingInit()
{
	for (int i = 0; i < 3; i++)
	{
		chunsikPos[i] = 0; // 춘식이 위치 초기화
	}
	tubePos[0] = -0.9;
	tubePos[1] = -0.5;
	tubePos[2] = -0.8; // 튜브 위치 초기화

	feed = false;
	play = false;
	bodyToggle = false;
	headToggle = false;
	rightArmToggle = false;
	leftArmToggle = false; // 움직임 제어 초기화

	for (int i = 0; i < 4; i++)
	{
		headAngle[i] = 0;
		rightArmAngle[i] = 0;
		leftArmAngle[i] = 0; // 신체의 각도 초기화
	}
}

// 일정 시간이 지나고 호출되는 함수
void MyTimer(int value)
{
	if (full > -1)
		full -= 0.005; // 먹고 있지 않을 때 춘식이의 포만감 하락
	if (happiness > -1)
		happiness -= 0.005; // 놀고 있지 않을 때 춘식이의 행복지수 하락
	glutPostRedisplay(); // Display Event 발생
	glutTimerFunc(20, MyTimer, 1); // 20밀리초마다 MyTimer 호출
}

// 춘식이에게 먹이를 줄 때 호출되는 함수
void FeedChunsik()
{
	if (!feed)
		return; // 먹이를 줄 때가 아니면 함수 종료

	if (full < 1)
		full += 0.01; // 먹고 있는 도중에 포만감 상승
	if (happiness > -1)
		happiness -= 0.001; // 놀고 있지 않으므로 행복지수 하락

	headAngle[1] = 1; // x축으로 머리 움직이기
	if (headToggle == false && headAngle[0] < 10) // 머리 앞으로 숙일 수 있을 때
	{
		headAngle[0] += 1; // 머리 앞으로 숙이기
		if (headAngle[0] >= 10) // 머리가 충분히 숙여졌을 때
			headToggle = true; // 머리 뒤로 젖히기
	}
	else if (headToggle == true && headAngle[0] > 0) // 머리 뒤로 젖힐 수 있을 때
	{
		headAngle[0] -= 1; // 머리 뒤로 젖히기
		if (headAngle[0] <= 0) // 머리가 충분히 젖혀졌을 때
			headToggle = false; // 머리 앞으로 숙이기
	}

	if (rightArmAngle[1] == 0 || leftArmAngle[1] == 0) // 팔이 아직 안 움직여진 상태
	{
		rightArmAngle[1] = 1; // x축으로 오른팔 움직이기
		rightArmAngle[0] = -90; // 오른팔 앞으로 내밀기
		leftArmAngle[1] = 1; // x축으로 왼팔 움직이기
		leftArmAngle[0] = -90; // 왼팔 앞으로 내밀기
	}
	else // 두 팔을 앞으로 내밀었을 때
	{
		if (rightArmToggle == false && rightArmAngle[0] > -110) // 오른팔을 위로 더 들 수 있을 때
		{
			rightArmAngle[0] -= 2;
			leftArmAngle[0] -= 2; // 오른팔, 왼팔 모두 위로 들기
			if (rightArmAngle[0] <= -110) // 오른팔이 충분히 위로 들려졌을 때
				rightArmToggle = true; // 오른팔 내리기

		}
		else if (rightArmToggle == true && rightArmAngle[0] < -90) // 오른팔을 밑으로 내려야 할 때
		{
			rightArmAngle[0] += 2;
			leftArmAngle[0] += 2; // 오른팔, 왼팔 모두 밑으로 내리기
			if (rightArmAngle[0] >= -90) // 오른팔이 충분히 밑으로 내려졌을 때
				rightArmToggle = false; // 오른팔 들기
		}
	}

	glutPostRedisplay(); // Display Event 발생
}

// 춘식이와 놀아줄 때 호출되는 함수
void PlayWithChunsik()
{
	if (!play)
		return; // 놀아줄 때가 아니면 함수 종료

	if (happiness < 1)
		happiness += 0.01; // 놀고 있으므로 행복지수 상승
	if (full > -1)
		full -= 0.001; // 먹고 있지 않으므로 행복지수 하락

	tubePos[0] = 0;
	tubePos[1] = -0.7;
	tubePos[2] = 0; // 튜브를 춘식이가 있는 곳으로 위치

	if (bodyToggle == false && chunsikPos[1] < 0.1) // 춘식이 몸을 위로 들 수 있을 때
	{
		chunsikPos[1] += 0.015; // 춘식이를 위로 들기
		if (chunsikPos[1] >= 0.1) // 춘식이가 위로 충분히 들려졌을 때
			bodyToggle = true; // 춘식이 아래로 내리기
	}
	else if (bodyToggle == true && chunsikPos[1] > -0.1) // 춘식이 몸을 아래로 내릴 수 있을 때
	{
		chunsikPos[1] -= 0.015; // 춘식이를 아래로 내리기
		if (chunsikPos[1] <= -0.1) // 춘식이가 아래로 충분히 내려졌을 때
			bodyToggle = false; // 춘식이 위로 들기
	}

	leftArmAngle[3] = 1; // x축 기준으로 왼팔 움직이기
	rightArmAngle[3] = 1; // x축 기준으로 오른팔 움직이기
	if (rightArmToggle == false && rightArmAngle[0] > -90) // 오른팔을 들 수 있을 때
	{
		leftArmAngle[0] += 2; // 왼팔 들기
		rightArmAngle[0] -= 2; // 오른팔 들기
		if (rightArmAngle[0] <= -90) // 오른팔이 충분히 위로 들려졌을 때
		{
			leftArmToggle = true;
			rightArmToggle = true; // 오른팔, 왼팔 내리기
		}
	}
	else if (rightArmToggle == true && rightArmAngle[0] < 0) // 오른팔을 아래로 내려야 할 때
	{
		leftArmAngle[0] -= 2; // 왼팔 내리기
		rightArmAngle[0] += 2; // 오른팔 내리기
		if (rightArmAngle[0] >= 0) // 오른팔이 충분히 아래로 내려졌을 때
		{
			leftArmToggle = false;
			rightArmToggle = false; // 오른팔, 왼팔 내리기
		}
	}

	glutPostRedisplay(); // Display Event 발생
}

// 메뉴 선택에 따라 반응하는 함수
void MyMenu(int value)
{
	switch (value)
	{
	case 1: // 메뉴에서 Feed를 선택했을 시
		MyChunsikMovingInit(); // 춘식이 움직임 초기화
		feed = true;
		play = false;
		glutIdleFunc(FeedChunsik); // 춘식이에게 먹이를 먹이기
		break;
	case 2: // 메뉴에서 Play를 선택했을 시
		MyChunsikMovingInit(); // 춘식이 움직임 초기화
		feed = false;
		play = true;
		glutIdleFunc(PlayWithChunsik); // 춘식이와 놀아주기
		break;
	case 3: // 메뉴에서 Stop을 선택했을 시
		MyChunsikMovingInit(); // 춘식이 움직임 초기화
		feed = false;
		play = false; // 모든 행동 멈추기
		// 아무런 행동도 하지 않기
		break;
	}
}

// 초기 설정 적용하는 함수
void MyInit()
{
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // 원근에 따른 텍스춰 보정을 위한 함수

	GLint menuID = glutCreateMenu(MyMenu); // 메뉴 생성
	glutAddMenuEntry("Feed", 1); // 첫 번째 메뉴 생성
	glutAddMenuEntry("Play", 2); // 두 번째 메뉴 생성
	glutAddMenuEntry("Stop", 3); // 세 번째 메뉴 생성
	glutAttachMenu(GLUT_RIGHT_BUTTON); // 마우스 우클릭을 하면 메뉴가 나타남

	camera[0] = 90; // 카메라 위치 설정
	camera[1] = 0;
	camera[2] = 90;

	width = 1024; // 창 너비 설정
	height = 700; // 창 높이 설정

	full = 0.8; // 춘식이 포만감 초기화
	happiness = 0.8; // 춘식이 행복지수 초기화

	MyChunsikMovingInit(); // 춘식이 움직임 초기화
}

// bmp 이미지를 불러오는 함수
AUX_RGBImageRec* LoadBMP(const char* Filename) {
	FILE* File = NULL;
	if (!Filename) return NULL; // 파일 이름 지정되어있지 않으면 함수 종료
	fopen_s(&File, Filename, "r"); // 파일 읽기 모드로 열기

	int size = strlen(Filename); // 파일 이름의 길이
	wchar_t* w_Filename = new wchar_t[size]; // 파일 이름의 길이만큼 할당

	for (int i = 0; i < size; ++i)  
		w_Filename[i] = Filename[i]; // 파일 이름을 유니코드 문자열로 변환
	w_Filename[size] = NULL; // 마지막에는 NULL로 마무리

	if (File) { // 파일 읽기 성공
		fclose(File); // 파일 닫기
		return auxDIBImageLoad(w_Filename); // 이미지 로드
	}
	return NULL;
}

// 텍스처 이미지를 적용하는 함수
void LoadGLTextures(const char name[40]) {
	AUX_RGBImageRec* textureImage;

	if (textureImage = LoadBMP(name)) // 이미지 불러오기
	{ 
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, textureImage->sizeX, textureImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, textureImage->data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // 확대되었을 때 텍스처가 부드럽게 출력
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // 축소되었을 때 텍스처가 부드럽게 출력

		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR); // s축으로 자동으로 좌표 매핑
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR); // t축으로 자동으로 좌표 매핑
		glEnable(GL_TEXTURE_GEN_S); // s축으로 생성 활성화
		glEnable(GL_TEXTURE_GEN_T); // t축으로 생성 활성화
		glEnable(GL_TEXTURE_2D); // 텍스처 입히기
	}

	if (textureImage) { // 이미지 불러오기 성공하였을 때
		if (textureImage->data) {
			free(textureImage->data); // 메모리 해제
		}
		free(textureImage); // 메모리 해제
	}
}

// Display Event 발생 시 호출되는 함수
void MyDisplay()
{
	GLfloat widthFactor = (GLfloat)width / (GLfloat)500; // 바뀐 뷰폿의 너비에 대한 비율
	GLfloat heightFactor = (GLfloat)height / (GLfloat)500; // 바뀐 뷰폿의 높이에 대한 비율

	// 첫 번째 뷰폿
	glMatrixMode(GL_PROJECTION); // 투영 행렬 선택
	glLoadIdentity(); // 투영 행렬을 항등 행렬로 초기화
	glOrtho(-3.0 * widthFactor, 3.0 * widthFactor, -3.0 * heightFactor, 3.0 * heightFactor, -3.0, 3.0); // 직교 투영 생성
	glViewport(0, 0, (GLsizei)width, height / 5); // 뷰폿 설정
	glClearColor(1, 1, 1, 1); // 흰색으로 화면 지우기
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 색 버퍼, 깊이 버퍼를 삭제하여 화면에서 그림 지우기
	glDisable(GL_LIGHTING); // 조명 끄기
	glMatrixMode(GL_MODELVIEW); // 모델뷰 행렬 선택
	glLoadIdentity(); // 모델뷰 행렬을 항등 행렬로 초기화
	glPushMatrix(); // 행복지수 그리기 시작
	glColor3f(1, 0, 0); // 행복지수 색깔 지정
	glBegin(GL_QUADS); // 행복지수 그리기
	glVertex3f(-3, -1.2, 0);
	glVertex3f(2.8 * happiness, -1.2, 0);
	glVertex3f(2.8 * happiness, -0.2, 0);
	glVertex3f(-3, -0.2, 0);
	glEnd();
	glPopMatrix(); // 행복지수 그리기 끝내기

	glPushMatrix(); // 포만감 그리기 시작
	glColor3f(1, 0.7, 0.2); // 포만감 색깔 지정
	glBegin(GL_QUADS); // 포만감 그리기 
	glVertex3f(-3, 0, 0);
	glVertex3f(2.8 * full, 0, 0);
	glVertex3f(2.8 * full, 1, 0);
	glVertex3f(-3, 1, 0);
	glEnd();
	glPopMatrix(); // 포만감 그리기 끝내기
	
	// 두 번째
	glScissor(0, 0, 100, (GLsizei)height); // 화면의 일부 자르기
	glEnable(GL_SCISSOR_TEST); // 밖에 있는 fragments 버리기
	glMatrixMode(GL_PROJECTION); // 투영 행렬 선택
	glLoadIdentity(); // 투영 행렬을 항등 행렬로 초기화
	glOrtho(-3.0 * widthFactor, 3.0 * widthFactor, -3.0 * heightFactor, 3.0 * heightFactor, -3.0, 3.0); // 직교 투영 생성
	glViewport(0, 0, (GLsizei)width, (GLsizei)height / 5); // 뷰폿 설정
	glClearColor(1, 1, 1, 1); // 흰색으로 화면 지우기
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 색 버퍼, 깊이 버퍼를 삭제하여 화면에서 그림 지우기

	// 세 번째 뷰폿
	glScissor(100, height / 5, (GLsizei)width, (GLsizei)height * 4 / 5); // 화면의 일부 자르기
	glEnable(GL_SCISSOR_TEST); // 밖에 있는 fragments 버리기
	glMatrixMode(GL_PROJECTION); // 투영 행렬 선택
	glLoadIdentity(); // 투영 행렬을 항등 행렬로 초기화
	gluPerspective(65.0, (GLfloat)width / (GLfloat)height, 1.0, 20.0); // 원근 투영 생성
	glViewport(0, 0, (GLsizei)width, (GLsizei)height); // 뷰폿 설정
	glClearColor(0.4, 0.9, 1, 1); // 하늘색으로 화면 지우기
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 색 버퍼, 깊이 버퍼를 삭제하여 화면에서 그림 지우기
	glMatrixMode(GL_MODELVIEW); // 모델뷰 행렬 선택
	glLoadIdentity(); // 모델뷰 행렬을 항등 행렬로 초기화

	glEnable(GL_LIGHTING); // 조명 사용
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient); // 전역 주변광 정하기 (카메라에 고정시킴)
	gluLookAt(2 * cosf(camera[0] * PI / 180), 0, 2 * sinf(camera[2] * PI / 180), 0, 0, 0, 0.0, 1.0, 0.0); // 카메라 위치 지정
	glEnable(GL_LIGHT0); // 0번 광원 사용
	glLightfv(GL_LIGHT0, GL_POSITION, light_position); // 0번 광원 위치 정하기
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient); // 주변광 정하기
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse); // 분산광 정하기
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular); // 반사광 정하기
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.5); // 빛의 감쇠 효과 정하기

	glEnable(GL_COLOR_MATERIAL); // 물체의 색상이 나오도록 함
	glFrontFace(GL_CCW); // 앞면 설정 
	glEnable(GL_CULL_FACE); // 후면 제거 모드 활성화
	glCullFace(GL_BACK); // 후면 제거
	glEnable(GL_DEPTH_TEST); // 은면 제거
	glDepthFunc(GL_LESS); // fragment의 depth value가 저장된 depth value보다 미만면 통과
	glEnable(GL_NORMALIZE); // 벡터를 단위 벡터로 바꾸기 (glScalef 사용 시 법선 벡터에 영향이 가고, 이는 조명 계산에 영향을 미침)
	glShadeModel(GL_SMOOTH); // Gouraud Shading

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient); // 주변광에 대한 물체의 재질 정하기
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, chunsik_specular); // 반사광에 대한 춘식이의 재질 정하기
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission); // 물체들의 발광색 지정

	glLineWidth(6); // 선 두께 지정

	// 춘식이 그리기
	glPushMatrix(); // 춘식이 그리기 시작
	glTranslated(chunsikPos[0], chunsikPos[1], chunsikPos[2]); // 춘식이 위치 지정

	// 몸 그리기
	glPushMatrix(); // 몸 윗부분 그리기 시작
	glColor3d(0.85, 0.65, 0.45); // 몸 색깔 지정
	glTranslated(0, -0.6, 0); // 몸 위치 지정
	glPushMatrix(); // 몸 위치에 대한 변환 행렬 저장
	glRotated(-90, 1, 0, 0); // 몸 윗부분 회전
	glScaled(1, 1, 0.8); // 몸 윗부분 크기 지정
	gluCylinder(qobj, 0.38, 0.3, 0.4, 50, 50); // 몸 윗부분 그리기
	glPopMatrix(); // 몸 윗부분 그리기 끝내기
	glColor3d(0.5, 0.2, 0.1); // 몸 아랫부분 색깔 지정
	glTranslated(0, -0.32, 0); // 몸 아랫부분 위치 지정
	glRotated(-90, 1, 0, 0); // 몸 아랫부분 회전
	glScaled(1, 1, 0.8); // 몸 아랫부분 크기 지정
	gluCylinder(qobj, 0.46, 0.38, 0.4, 50, 50); // 몸 아랫부분 그리기
	glPopMatrix(); // 몸 그리기 끝내기

	 // 팔 + 손바닥 그리기
	if (feed == true) // 먹고 있을 때 사과 쥐고 있기
	{
		glPushMatrix(); // 사과 그리기 시작
		glColor3f(1, 0.3, 0.3); // 사과 색깔 지정
		glTranslated(0, -0.25, 0.5); // 사과 위치 지정
		glMatrixMode(GL_TEXTURE); // 텍스처 행렬 선택
		glLoadIdentity(); // 택스처 행렬을 항등 행렬로 초기화
		glTranslated(0.5, 0.5, 0.0); // 텍스처 이동
		LoadGLTextures("apple texture.bmp"); // 사과에 텍스처 입히기
		gluSphere(qobj, 0.15, 50, 50); // 사과 그리기
		glMatrixMode(GL_MODELVIEW); // 모델뷰 행렬 선택
		glPopMatrix(); // 사과 그리기 끝내기
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
		glDisable(GL_TEXTURE_2D); // 텍스처 그만 입히기
	}
	glPushMatrix(); // 오른쪽에 있는 팔 그리기
	glColor3d(0.85, 0.65, 0.45); // 팔 색 지정
	glTranslated(-0.45, -0.56, 0); // 어깨가 몸에 붙어있도록 위치
	glTranslated(0, (1.6 * 0.15) / 2, 0); // 팔 원위치
	glRotated(rightArmAngle[0], rightArmAngle[1], rightArmAngle[2], rightArmAngle[3]); // 팔 회전
	glTranslated(0, -(1.6 * 0.15) / 2, 0); // 어깨에서 팔 회전
	glRotated(50, 0, 1, 0); // 어깨가 몸에 붙어있도록 회전
	glRotated(-20, 0, 0, 1); // 어깨가 몸에 붙어있도록 회전
	glPushMatrix(); // 팔에 대한 위치 및 회전 변환 행렬 저장
	glScaled(0.9, 1.6, 0.9); // 팔의 크기 지정
	gluSphere(qobj, 0.15, 50, 50); // 팔 그리기
	glPopMatrix(); // 팔 그리기 끝내기

	// 손바닥 그리기
	glColor3f(0.9, 0.5, 0.5); // 손바닥 색깔 지정
	glTranslated(0, -0.08, 0.13); // 손바닥이 팔의 아래에 위치하도록 지정
	glRotated(10, 1, 0, 0); // 손바닥의 각도 지정
	glBegin(GL_POLYGON); // 손바닥 그리기
	for (int i = 0; i < 360; i++)
	{
		double radian = i * PI / 180;
		glVertex3f(0.04 * cos(radian), 0.04 * sin(radian), 0);
	}
	glEnd(); // 손바닥 그리기 끝내기
	glBegin(GL_POLYGON); // 첫 번째 손가락 그리기
	for (int i = 0; i < 360; i++)
	{
		double radian = i * PI / 180;
		glVertex3f(0.016 * cos(radian) - 0.04, 0.016 * sin(radian) - 0.05, 0);
	}
	glEnd(); // 첫 번째 손가락 그리기 끝내기
	glBegin(GL_POLYGON); // 두 번째 손가락 그리기
	for (int i = 0; i < 360; i++)
	{
		double radian = i * PI / 180;
		glVertex3f(0.016 * cos(radian), 0.016 * sin(radian) - 0.06, 0);
	}
	glEnd(); // 두 번째 손가락 그리기 끝내기
	glBegin(GL_POLYGON); // 세 번째 손가락 그리기
	for (int i = 0; i < 360; i++)
	{
		double radian = i * PI / 180;
		glVertex3f(0.016 * cos(radian) + 0.04, 0.016 * sin(radian) - 0.05, 0);
	}
	glEnd(); // 세 번째 손가락 그리기 끝내기
	if (play == true) // 놀고 있을 때 깃발 쥐고 있기
	{
		// 깃발 그리기
		glDisable(GL_CULL_FACE);
		glPushMatrix(); // 깃발 그리기
		glColor3f(0.9, 0.4, 0.0); // 막대 색깔 지정
		glPushMatrix(); // 깃발에 대한 변환 행렬 저장
		glRotated(90, 1, 0, 0); // 막대 회전
		gluCylinder(qobj, 0.06, 0.06, 1, 50, 50); // 막대 그리기
		glPopMatrix(); // 막대 그리기 끝내기
		glColor3f(1, 1, 1); // 깃발 색깔 지정
		glBegin(GL_TRIANGLES); // 깃발 그리기
		glVertex3f(0, -0.4 - 0.6, 0);
		glVertex3f(0, -0.6, 0);
		glVertex3f(-0.5, -0.2 - 0.6, 0);
		glEnd(); // 깃발 그리기 끝내기
		glPopMatrix(); // 깃발 그리기 끝내기
		glEnable(GL_CULL_FACE);
	}
	glPopMatrix(); // 오른쪽에 있는 팔 그리기 끝내기

	glPushMatrix(); // 왼쪽에 있는 팔 그리기
	glColor3d(0.85, 0.65, 0.45); // 팔 색 지정
	glTranslated(0.45, -0.56, 0); // 어깨가 몸에 붙어있도록 위치
	glTranslated(0, (1.6 * 0.15) / 2, 0); // 팔 원위치
	glRotated(leftArmAngle[0], leftArmAngle[1], leftArmAngle[2], leftArmAngle[3]); // 팔 회전
	glTranslated(0, -(1.6 * 0.15) / 2, 0); // 어깨에서 팔 회전
	glRotated(-50, 0, 1, 0); // 어깨가 몸에 붙어있도록 회전
	glRotated(20, 0, 0, 1); // 어깨가 몸에 붙어있도록 회전
	glPushMatrix(); // 팔에 대한 위치 및 회전 변환 행렬 저장
	glScaled(0.9, 1.6, 0.9); // 팔의 크기 지정
	gluSphere(qobj, 0.15, 50, 50); // 팔 그리기
	glPopMatrix(); // 팔 그리기 끝내기

	// 손바닥 그리기
	glColor3f(0.9, 0.5, 0.5); // 손바닥 색깔 지정
	glTranslated(0, -0.08, 0.13); // 손바닥이 팔의 아래에 위치하도록 지정
	glRotated(10, 1, 0, 0); // 손바닥의 각도 지정
	glBegin(GL_POLYGON); // 손바닥 그리기
	for (int i = 0; i < 360; i++)
	{
		double radian = i * PI / 180;
		glVertex3f(0.04 * cos(radian), 0.04 * sin(radian), 0);
	}
	glEnd(); // 손바닥 그리기 끝내기
	glBegin(GL_POLYGON); // 첫 번째 손가락 그리기
	for (int i = 0; i < 360; i++)
	{
		double radian = i * PI / 180;
		glVertex3f(0.016 * cos(radian) - 0.04, 0.016 * sin(radian) - 0.05, 0);
	}
	glEnd(); // 첫 번째 손가락 그리기 끝내기
	glBegin(GL_POLYGON); // 두 번째 손가락 그리기
	for (int i = 0; i < 360; i++)
	{
		double radian = i * PI / 180;
		glVertex3f(0.016 * cos(radian), 0.016 * sin(radian) - 0.06, 0);
	}
	glEnd(); // 두 번째 손가락 그리기 끝내기
	glBegin(GL_POLYGON); // 세 번째 손가락 그리기
	for (int i = 0; i < 360; i++)
	{
		double radian = i * PI / 180;
		glVertex3f(0.016 * cos(radian) + 0.04, 0.016 * sin(radian) - 0.05, 0);
	}
	glEnd(); // 세 번째 손가락 그리기 끝내기
	glPopMatrix(); // 왼쪽에 있는 팔 그리기 끝내기

	// 얼굴 그리기
	glPushMatrix(); // 얼굴 그리기 시작
	glColor3d(0.85, 0.65, 0.45); // 얼굴 색 지정
	glRotated(headAngle[0], headAngle[1], headAngle[2], headAngle[3]); // 얼굴 회전 각도 지정
	glPushMatrix(); // 얼굴에 대한 회전, 위치 변환 행렬 저장
	glScaled(1.1, 0.95, 1); // 얼굴 크기 지정
	gluSphere(qobj, 0.5, 50, 50); // 얼굴 그리기
	glPopMatrix(); // 얼굴 크기에 대한 변환 행렬 삭제

	// 귀 그리기
	glPushMatrix(); // 오른쪽 귀 그리기 시작
	glTranslated(-0.3, 0.4, 0); // 오른쪽 귀 위치 지정
	gluSphere(qobj, 0.08, 50, 50); // 오른쪽 귀 그리기
	glPopMatrix(); // 오른쪽 귀 그리기 끝내기
	glPushMatrix(); // 왼쪽 귀 그리기 시작
	glTranslated(0.3, 0.4, 0); // 왼쪽 귀 위치 지정
	gluSphere(qobj, 0.08, 50, 50); // 왼쪽 귀 그리기
	glPopMatrix(); // 왼쪽 귀 그리기 끝내기

	// 얼굴 표면 묘사
	glTranslated(0, 0, 0.5); // 얼굴 표면 위에 이목구비 위치
	glScaled(0.85, 0.85, 0.85); // 이목구비 크기 지정

	// 코 그리기
	glPushMatrix(); // 얼굴 표면 묘사에 대한 변환 행렬 저장 및 오른쪽 코 그리기 시작
	glColor3d(1, 1, 1); // 코 색 지정
	glTranslated(-0.05, -0.085, 0); // 오른쪽 코 위치 지정
	glScaled(0.7, 0.6, 0.5); // 오른쪽 코 크기 지정
	gluSphere(qobj, 0.1, 50, 50); // 코 그리기
	glPopMatrix(); // 오른쪽 코 그리기 끝내기
	glPushMatrix(); // 왼쪽 코 그리기 시작
	glTranslated(0.05, -0.085, 0); // 왼쪽 코 위치 지정
	glScaled(0.7, 0.6, 0.5); // 왼쪽 코 크기 지정
	gluSphere(qobj, 0.1, 50, 50); // 코 그리기
	glPopMatrix(); // 왼쪽 코 그리기 끝내기

	// 수염 그리기
	glPushMatrix(); // 수염 그리기 시작
	glColor3d(0, 0, 0); // 수염 색 지정
	glBegin(GL_LINES); // 오른쪽 위 수염 그리기
	glVertex3f(-0.2, -0.035, 0);
	glVertex3f(-0.1, -0.065, 0);
	glEnd(); // 오른쪽 아래 수염 그리기 끝내기
	glBegin(GL_LINES); // 오른쪽 위 수염 그리기
	glVertex3f(-0.2, -0.115, 0);
	glVertex3f(-0.1, -0.085, 0);
	glEnd(); // 오른쪽 아래 수염 그리기 끝내기
	glBegin(GL_LINES); // 왼쪽 위 수염 그리기
	glVertex3f(0.2, -0.035, 0);
	glVertex3f(0.1, -0.065, 0);
	glEnd(); // 왼쪽 아래 수염 그리기 끝내기
	glBegin(GL_LINES); // 왼쪽 위 수염 그리기
	glVertex3f(0.2, -0.115, 0);
	glVertex3f(0.1, -0.085, 0);
	glEnd(); // 왼쪽 아래 수염 그리기 끝내기
	glPopMatrix(); // 수염 그리기 끝내기

	// 눈 그리기
	if (full < 0 || happiness < 0) // 기분이 안 좋을 때
	{
		glPushMatrix(); // 오른쪽의 미간 그리기
		glTranslated(-0.05, 0, 0); // 미간 위치 지정
		glBegin(GL_LINES); // 미간 그리기
		{
			glVertex3f(0, 0.08, 0);
			glVertex3f(0.03, 0.1, 0);
			glVertex3f(0.02, 0.1, 0);
			glVertex3f(0.03, 0.13, 0);
		}
		glEnd();
		glPopMatrix(); // 오른쪽의 미간 그리기 끝내기

		glPushMatrix(); // 왼쪽의 미간 그리기
		glTranslated(0.05, 0, 0); // 미간 위치 지정
		glRotated(180, 0, 1, 0); // 미간 뒤집기
		glBegin(GL_LINES); // 미간 그리기
		{
			glVertex3f(0, 0.08, 0);
			glVertex3f(0.03, 0.1, 0);
			glVertex3f(0.02, 0.1, 0);
			glVertex3f(0.03, 0.13, 0);
		}
		glEnd();
		glPopMatrix(); // 왼쪽의 미간 그리기 끝내기

		glScaled(1.1, 0.8, 0); // 눈 회전
	}
	glBegin(GL_POLYGON); // 오른쪽 눈 그리기
	for (int i = 0; i < 360; i++)
	{
		double radian = i * PI / 180;
		glVertex3f(0.042 * cos(radian) - 0.15, 0.042 * sin(radian) + 0.065, 0);
	}
	glEnd(); // 오른쪽 눈 그리기 끝내기
	glBegin(GL_POLYGON); // 왼쪽 눈 그리기
	for (int i = 0; i < 360; i++)
	{
		double radian = i * PI / 180;
		glVertex3f(0.042 * cos(radian) + 0.15, 0.042 * sin(radian) + 0.065, 0);
	}
	glEnd(); // 왼쪽 눈 그리기 끝내기
	glPopMatrix(); // 얼굴 묘사 끝
	glPopMatrix(); // 춘식이 그리기 끝

	// 배경 그리기
	// 튜브 그리기
	glPushMatrix(); // 튜브 그리기
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tube_specular); // 반사광에 대한 튜브의 재질 정하기
	glMaterialf(GL_FRONT, GL_SHININESS, 20); // 튜브의 광택 계수 정하기
	glColor3f(1, 0.2, 0.2); // 튜브 색 지정
	glTranslated(tubePos[0], tubePos[1], tubePos[2]); // 튜브 위치 지정
	glRotated(90, 1, 0, 0); // 튜브 회전
	glutSolidTorus(0.2, 0.4, 50, 50); // 튜브 그리기
	glPopMatrix(); // 튜브 그리기 끝내기

	// 바다 그리기
	glPushMatrix(); // 바다 그리기
	glColor3f(0, 0.3, 1); // 바다 색 지정
	glTranslated(0, -0.95, 0); // 바다 위치 지정
	glRotated(90, 1, 0, 0); // 바다 회전
	glScaled(10, 10, 0.5); // 바다 크기 지정
	glMatrixMode(GL_TEXTURE); // 텍스처 행렬 선택
	glLoadIdentity(); // 택스처 행렬을 항등 행렬로 초기화
	LoadGLTextures("ocean.bmp");// 바다에 텍스처 입히기
	glutSolidCube(1); // 바다 그리기
	glMatrixMode(GL_MODELVIEW); // 모델뷰 행렬 선택
	glPopMatrix(); // 바다 그리기 끝내기
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D); // 텍스처 그만 입히기

	// 암석 그리기
	glPushMatrix(); // 돌 그리기
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, chunsik_specular); // 반사광에 대한 물체의 재질 정하기 (춘식이와 동일)
	glColor3f(0.1, 0.15, 0.15); // 돌 색 지정
	glTranslated(3, 0, -4); // 돌 위치 지정
	glutSolidDodecahedron(); // 돌 그리기
	glPopMatrix(); // 돌 그리기 끝내기

	// 깃발 그리기
	if (play == false)
	{
		glPushMatrix(); // 깃발 그리기
		glColor3f(0.9, 0.4, 0.0); // 막대 색깔 지정
		glTranslated(-1.5, 0.3, -2); // 깃발 위치 지정
		glPushMatrix(); // 깃발에 대한 변환 행렬 저장
		glRotated(90, 1, 0, 0); // 막대 회전
		gluCylinder(qobj, 0.06, 0.06, 1, 50, 50); // 막대 그리기
		glPopMatrix(); // 막대 그리기 끝내기
		glColor3f(1, 1, 1); // 깃발 색깔 지정
		glBegin(GL_TRIANGLES); // 깃발 그리기
		glVertex3f(0, -0.4, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(-0.5, -0.2, 0);
		glEnd(); // 깃발 그리기 끝내기
		glPopMatrix(); // 깃발 그리기 끝내기
	}

	// 태양 그리기
	glPushMatrix(); // 태양 그리기
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, sun_emission); // 태양의 발광색 정하기 (태양이 광원으로 작용하지 않음)
	glColor3f(1, 0.5, 0.2); // 태양의 색깔 지정
	glTranslated(3, 5, 10); // 태양의 위치 지정
	gluSphere(qobj, 1, 50, 50); // 태양 그리기
	glPopMatrix(); // 태양 그리기 끝내기

	glDisable(GL_SCISSOR_TEST);
	glutSwapBuffers();
}

// 화면 크기가 바뀔 때 호출되는 함수
void MyReshape(int w, int h)
{
	width = w; // 새로운 화면 너비 저장
	height = h; // 새로운 화면 높이 저장
}

// 특수 키 입력 시 호출되는 함수
void MySpecialKey(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_RIGHT: // 오른쪽 방향키를 눌렀을 때
		camera[0] -= 2;
		camera[2] -= 2; // 카메라가 오른쪽으로 회전하도록 설정
		break;
	case GLUT_KEY_LEFT: // 왼쪽 방향키를 눌렀을 때
		camera[0] += 2;
		camera[2] += 2; // 카메라가 왼쪽으로 회전하도록 설정
		break;
	default:
		break;
	}

	glutPostRedisplay(); // Display Event 발생
}

// 마우스를 누르지 않고 움직일 때마다 호출되는 함수
void MyMouseMove(int x, int y)
{
	if (!feed && !play) // 어떠한 행동도 취하고 있지 않을 때
	{
		headAngle[2] = 1; // y축에서 얼굴 움직이기
		headAngle[0] = x / 100 - 4; // 마우스의 x축에서의 움직임에 따라 춘식이 얼굴 움직임
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); // Window OS와 세션 연결, GLUT Library 초기화
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // Display Mode 설정 (트루 컬러 모드 & 2개의 버퍼 사용)
	glutInitWindowPosition(0, 0); // 윈도우의 위치 지정
	glutInitWindowSize(width, height); // 윈도우의 크기 지정
	glutCreateWindow("Tamagotchi"); // 윈도우 창 생성 및 이름 지정
	MyInit(); // 초기 설정 적용
	glutDisplayFunc(MyDisplay); // Display Event가 발생할 때마다 MyDisplay를 호출하도록 등록
	glutReshapeFunc(MyReshape); // 화면을 다시 그려야 할 때마다 MyReshape을 호출하도록 등록
	glutSpecialFunc(MySpecialKey); // (특수키에 대한) Keyboard Event가 발생할 때마다 MySpecialKey를 호출하도록 등록
	glutPassiveMotionFunc(MyMouseMove); // 마우스를 클릭하지 않은 채 움직일 때마다 MyMouseMove를 호출하도록 등록
	glutTimerFunc(20, MyTimer, 1); // 20밀리초 이후에 MyTimer 호출하도록 등록
	glutMainLoop(); // GLUT Event 처리 Loop 진입
	return 0;
}