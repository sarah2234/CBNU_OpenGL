/*******************************************************************************************************/
/*                                       HW#4-1 : 로봇 손-팔 모델링                                    */
/*  작성자 : 이승현                                                            날짜 : 2021년 10월 26일 */
/*                                                                                                     */
/* 문제 정의 :                                                                                         */
/* 행렬 스택을 이용하여 로봇의 손과 팔을 구현한다.                                                     */
/* 기능 :                                                                                              */
/* 1. 1을 누르면 첫 번째 손가락을 움직인다.                                                            */
/* 2. 2를 누르면 두 번째 손가락을 움직인다.                                                            */
/* 3. 3을 누르면 세 번째 손가락을 움직인다.                                                            */
/* 4. 4를 누르면 모든 손가락이 움직인다.                                                               */
/* 5. s 또는 S를 누르면 움직이던 손가락이 멈춘다.                                                      */
/* 6. 마우스 좌클릭을 하면 어깨, 팔꿈치 및 모든 손가락을 움직여서 Robot Arm이 회전한다.                */
/* 7. 마우스 우클릭을 하면 어깨, 팔꿈치 및 모든 손가락을 움직여서 Roboat Arm이 원래 자세로 돌아간다.   */
/*******************************************************************************************************/

#include <gl/glut.h>
#include <math.h>
#define PI 3.14159265

static float shoulder = 0, elbow = 0; // 어깨와 팔꿈치를 회전시킬 때의 각도
static float finger[3][3]; // 각각의 손가락 마디를 회전시킬 때의 각도
static bool shoulderFlip, elbowFlip, shoulderFlipBackward, elbowFlipBackward; // 어깨와 팔꿈치를 회전시킬지 컨트롤하는 변수
static bool fingerFlip[3], fingerFlipBackward[3], fingerFlipToggle[3]; // 손가락을 어떻게 움직일지 컨트롤하는 변수

// 초기 설정
void MyInit()
{
	glClearColor(0, 0, 0, 1); // 검은색으로 화면 지우기
	glShadeModel(GL_FLAT); // flat shading으로 선택 (각지게 그림)
	for (int i = 0; i < 3; i++) // 초기 화면에서는 손가락이 움직이지 않도록 함
	{
		fingerFlip[i] = false; 
		fingerFlipBackward[i] = false;
	}
	shoulderFlip = false; // 초기 화면에서는 어깨가 움직이지 않도록 함
	elbowFlip = false; // 초기 화면에서는 팔꿈치가 움직이지 않도록 함
}

// Display Event가 발생했을 때 호출되는 callback 함수
void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT); // 화면에서 그림 지우기
	glMatrixMode(GL_MODELVIEW); // 모델뷰 행렬 선택
	glLoadIdentity(); // 모델뷰 행렬를 항등 행렬로 초기화
	glPushMatrix(); // 현재 변환 행렬을 행렬 스택에 저장

	glTranslatef(-2.0, 0.0, 0.0); // Robot Arm의 전체 위치 조정
	glRotatef(20, 1.0, 0.0, 0.0); // x축을 기준으로 20도 회전 (Robot Arm을 좀 더 입체적으로 보기 위함)
	glPushMatrix(); // 현재 변환 행렬을 행렬 스택에 저장

	// 어깨 아래
	glTranslatef(-1.0, 0.0, 0.0); // Pivot 지정 및 객체 이동
	glRotatef((GLfloat)shoulder, 0.0, 1.0, 0.0); // 윗팔을 shoulder°만큼 회전
	glTranslatef(1.0, 0.0, 0.0); // Pivot으로 지정할 위치를 원점으로 이동
	glPushMatrix(); // 현재 변환 행렬을 행렬 스택에 저장
	glColor3f(1.0, 1.0, 1.0); // 흰색으로 칠하기
	glScalef(2.0, 0.4, 1.0); // 윗팔 크기 지정
	glutWireCube(1.0); // 현재 변환 행렬을 기준으로 3D 육면체 그리기 
	glPopMatrix(); // 현재 변환 행렬을 행렬 스텍에서 제거

	// 팔꿈치 아래
	glTranslatef(1.0, 0.0, 0.0); // 팔 위치 지정
	glRotatef((GLfloat)elbow, 0.0, 1.0, 0.0); // 아랫팔의 길이의 반만큼 이동한 곳에서 elbow°만큼 회전
	glTranslatef(1.0, 0.0, 0.0); // x축에서 1.0만큼 객체 이동 (아랫팔의 x축 길이의 반)
	glPushMatrix(); // 현재 변환 행렬을 행렬 스택에 저장
	glColor3f(1.0, 1.0, 1.0); // 흰색으로 칠하기
	glScalef(2.0, 0.4, 1.0); // 아랫팔 크기 지정
	glutWireCube(1.0); // 현재 변환 행렬을 기준으로 3D 육면체 그리기
	glPopMatrix(); // 현재 변환 행렬을 행렬 스텍에서 제거

	// 손가락 그리기
	glTranslatef(0.6, 0.0, 0.0); // 손가락이 최종적으로 팔의 끝 부분에 위치하도록 함
	glPushMatrix(); // 현재 변환 행렬을 행렬 스택에 저장
	
	// 가운데 손가락의 첫 번째 마디
	glTranslatef(0.4, 0.0, 0.0); // 현재 손가락 마디가 같은 손가락의 다른 마디의 끝에 오도록 함
	glRotatef(finger[1][0], 0.0, 1.0, 0.0); // 가운데 손가락의 첫 번째 마디를 finger[1][0]°만큼 회전
	glTranslatef(0.4, 0.0, 0.0); // 손가락 길이의 반만큼 이동하여 마디의 왼쪽 끝에 원점 위치 (elbow가 회전함에 따라 손가락의 위치도 변경하도록 함)
	glPushMatrix(); // 현재 변환 행렬을 행렬 스택에 저장
	glScalef(0.8, 0.1, 0.25); // 손가락 마디 크기 지정
	glutWireCube(1.0); // 손가락 마디 그리기
	glPopMatrix(); // 현재 변환 행렬을 행렬 스텍에서 제거
	
	// 가운데 손가락의 두 번째 마디
	glTranslatef(0.4, 0.0, 0.0); // 현재 손가락 마디가 같은 손가락의 다른 마디의 끝에 오도록 함
	glRotatef(finger[1][1], 0.0, 1.0, 0.0); // 가운데 손가락의 두 번째 마디를 finger[1][1]°만큼 회전
	glTranslatef(0.4, 0.0, 0.0); // 손가락 길이의 반만큼 이동하여 마디의 왼쪽 끝에 원점 위치
	glPushMatrix(); // 현재 변환 행렬을 행렬 스택에 저장
	glScalef(0.8, 0.1, 0.25); // 손가락 마디 크기 지정
	glutWireCube(1.0); // 손가락 마디 그리기
	glPopMatrix(); // 현재 변환 행렬을 행렬 스텍에서 제거

	// 가운데 손가락의 세 번째 마디
	glTranslatef(0.4, 0.0, 0.0); // 현재 손가락 마디가 같은 손가락의 다른 마디의 끝에 오도록 함
	glRotatef(finger[1][2], 0.0, 1.0, 0.0); // 가운데 손가락의 세 번째 마디를 finger[1][2]°만큼 회전
	glTranslatef(0.4, 0.0, 0.0); // 손가락 길이의 반만큼 이동하여 마디의 왼쪽 끝에 원점 위치
	glScalef(0.8, 0.1, 0.25); // 손가락 마디 크기 지정
	glutWireCube(1.0); // 손가락 마디 그리기
	glPopMatrix(); // 현재 변환 행렬을 행렬 스택에서 제거
	glPushMatrix(); // 현재 변환 행렬을 행렬 스택에 저장

	// 윗쪽 손가락 그리기
	glRotatef(20, 0.0, 0.0, 1.0); // 윗쪽 손가락을 가운데 손가락보다 20도 위로 있도록 함
	glPushMatrix(); // 현재 변환 행렬을 행렬 스택에 저장

	// 윗쪽 손가락의 첫 번째 마디
	glTranslatef(0.4, 0.0, 0.0); // 현재 손가락 마디가 같은 손가락의 다른 마디의 끝에 오도록 함
	glRotatef(finger[0][0], 0.0, 1.0, 0.0); // 윗쪽 손가락의 첫 번째 마디를 finger[0][0]°만큼 회전
	glTranslatef(0.4, 0.0, 0.0); // 손가락 길이의 반만큼 이동하여 마디의 왼쪽 끝에 원점 위치
	glPushMatrix(); // 현재 변환 행렬을 행렬 스택에 저장
	glScalef(0.8, 0.1, 0.25); // 손가락 마디 크기 지정
	glutWireCube(1.0); // 손가락 마디 그리기
	glPopMatrix(); // 현재 변환 행렬을 행렬 스텍에서 제거

	// 윗쪽 손가락의 두 번째 마디
	glTranslatef(0.4, 0.0, 0.0); // 현재 손가락 마디가 같은 손가락의 다른 마디의 끝에 오도록 함
	glRotatef(finger[0][1], 0.0, 1.0, 0.0); // 윗쪽 손가락의 두 번째 마디를 finger[0][1]°만큼 회전
	glTranslatef(0.4, 0.0, 0.0); // 손가락 길이의 반만큼 이동하여 마디의 왼쪽 끝에 원점 위치
	glPushMatrix(); // 현재 변환 행렬을 행렬 스택에 저장
	glScalef(0.8, 0.1, 0.25); // 손가락 마디 크기 지정
	glutWireCube(1.0); // 손가락 마디 그리기
	glPopMatrix(); // 현재 변환 행렬을 행렬 스텍에서 제거

	// 윗쪽 손가락의 세 번째 마디
	glTranslatef(0.4, 0.0, 0.0); // 현재 손가락 마디가 같은 손가락의 다른 마디의 끝에 오도록 함
	glRotatef(finger[0][2], 0.0, 1.0, 0.0); // 윗쪽 손가락의 세 번째 마디를 finger[0][2]°만큼 회전
	glTranslatef(0.4, 0.0, 0.0); // 손가락 길이의 반만큼 이동하여 마디의 왼쪽 끝에 원점 위치
	glPushMatrix(); // 현재 변환 행렬을 행렬 스택에 저장
	glScalef(0.8, 0.1, 0.25); // 손가락 마디 크기 지정
	glutWireCube(1.0); // 손가락 마디 그리기
	glPopMatrix(); // 현재 변환 행렬을 행렬 스텍에서 제거
	glPopMatrix(); // 현재 변환 행렬을 행렬 스텍에서 제거
	glPopMatrix(); // 현재 변환 행렬을 행렬 스텍에서 제거

	// 아랫쪽 손가락 그리기
	glRotatef(-20, 0.0, 0.0, 1.0); // 아랫쪽 손가락을 가운데 손가락보다 20도 아래로 있도록 함
	glPushMatrix(); // 현재 변환 행렬을 행렬 스택에 저장

	// 아랫쪽 손가락의 첫 번째 마디
	glTranslatef(0.4, 0.0, 0.0); // 현재 손가락 마디가 같은 손가락의 다른 마디의 끝에 오도록 함
	glRotatef(finger[2][0], 0.0, 1.0, 0.0); // 아랫쪽 손가락의 첫 번째 마디를 finger[2][0]°만큼 회전
	glTranslatef(0.4, 0.0, 0.0); // 손가락 길이의 반만큼 이동하여 마디의 왼쪽 끝에 원점 위치
	glPushMatrix(); // 현재 변환 행렬을 행렬 스택에 저장
	glScalef(0.8, 0.1, 0.25); // 손가락 마디 크기 지정
	glutWireCube(1.0); // 손가락 마디 그리기
	glPopMatrix(); // 현재 변환 행렬을 행렬 스텍에서 제거

	// 아랫쪽 손가락의 두 번째 마디
	glTranslatef(0.4, 0.0, 0.0); // 현재 손가락 마디가 같은 손가락의 다른 마디의 끝에 오도록 함
	glRotatef(finger[2][1], 0.0, 1.0, 0.0); // 아랫쪽 손가락의 두 번째 마디를 finger[2][1]°만큼 회전
	glTranslatef(0.4, 0.0, 0.0); // 손가락 길이의 반만큼 이동하여 마디의 왼쪽 끝에 원점 위치
	glPushMatrix(); // 현재 변환 행렬을 행렬 스택에 저장
	glScalef(0.8, 0.1, 0.25); // 손가락 마디 크기 지정
	glutWireCube(1.0); // 손가락 마디 그리기
	glPopMatrix(); // 현재 변환 행렬을 행렬 스텍에서 제거

	// 아랫쪽 손가락의 세 번째 마디
	glTranslatef(0.4, 0.0, 0.0); // 현재 손가락 마디가 같은 손가락의 다른 마디의 끝에 오도록 함
	glRotatef(finger[2][2], 0.0, 1.0, 0.0); // 아랫쪽 손가락의 세 번째 마디를 finger[2][2]°만큼 회전
	glTranslatef(0.4, 0.0, 0.0); // 손가락 길이의 반만큼 이동하여 마디의 왼쪽 끝에 원점 위치
	glPushMatrix(); // 현재 변환 행렬을 행렬 스택에 저장
	glScalef(0.8, 0.1, 0.25); // 손가락 마디 크기 지정
	glutWireCube(1.0); // 손가락 마디 그리기
	glPopMatrix(); // 현재 변환 행렬을 행렬 스텍에서 제거
	glPopMatrix(); // 현재 변환 행렬을 행렬 스텍에서 제거
	glPopMatrix(); // 현재 변환 행렬을 행렬 스텍에서 제거
	glPopMatrix(); // 현재 변환 행렬을 행렬 스텍에서 제거
	glPopMatrix(); // 현재 변환 행렬을 행렬 스텍에서 제거
	glPopMatrix(); // 현재 변환 행렬을 행렬 스텍에서 제거 (항등 행렬만 남음)

	glutSwapBuffers(); // 전면 버퍼와 후면 버퍼를 교체하여 후면 버퍼에 준비해둔 그림이 나타남
}

// 화면을 다시 그려야 할 때 호출되는 callback 함수
void MyReshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); // 뷰폿 설정
	glMatrixMode(GL_PROJECTION); // 투영 행렬 선택
	glLoadIdentity(); // 투영 행렬을 항등 행렬로 초기화
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0); // 원근 투영 생성
	glTranslatef(0.0, 0.0, -5.0); // z축에서 -5.0만큼 이동
}

void MyIdle()
{
	if (shoulderFlip) // 어깨를 안으로 움직이라는 지시가 있음
	{
		if (shoulder < 20)
		{
			shoulder += 0.1; // 20도가 되기 전까지 어깨를 안으로 움직이기
		}
	}
	else if (shoulderFlipBackward) // 어깨를 밖으로 움직이라는 지시가 있음
	{
		if (0 < shoulder)
		{
			shoulder -= 0.1; // 0도가 되기 전까지 어깨를 밖으로 움직이기
		}
	}

	if (elbowFlip) // 팔을 안으로 접으라는 지시가 있음
	{
		if (elbow < 20)
		{
			elbow += 0.1; // 20도가 되기 전까지 팔을 안으로 접기
		}
	}
	else if (elbowFlipBackward) // 팔을 밖으로 펼치라는 지시가 있음
	{
		if (0 < elbow)
		{
			elbow -= 0.1; // 0도가 되기 전까지 팔을 펼치기
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (finger[i][0] >= 20 && fingerFlip[i] && fingerFlipToggle[i])
		{
			// 손가락을 연속적으로 움직여야 하고, 손가락이 접힐 만큼 접혔을 때 손가락을 펼치도록 함
			fingerFlipBackward[i] = true;
			fingerFlip[i] = false;
		}
		else if (finger[i][0] <= 0 && fingerFlipBackward[i] && fingerFlipToggle[i])
		{
			// 손가락을 연속적으로 움직여야 하고, 손가락이 펼쳐질 만큼 펼쳐졌을 때 손가락을 접도록 함
			fingerFlipBackward[i] = false;
			fingerFlip[i] = true;
		}

		for (int j = 0; j < 3 && finger[i][j] < 20 && fingerFlip[i]; j++)
		{
			finger[i][j] += 0.1; // 손가락을 20도까지 접기
		}

		for (int j = 0; j < 3 && finger[i][j] > 0 && fingerFlipBackward[i]; j++)
		{
			finger[i][j] -= 0.1; // 손가락을 0도까지 펼치기
		}
	}

	glutPostRedisplay(); // Display Event 발생시키기
}

// Keyboard Event가 발생했을 때 호출되는 callback 함수
void MyKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		if (fingerFlipToggle[0])
			break; // 이미 손가락이 연속적으로 움직이고 있으면 건너뛰기
		fingerFlip[0] = true; // 윗쪽 손가락 접기
		fingerFlipBackward[0] = false; // 윗쪽 손가락 접기
		fingerFlipToggle[0] = true; // 윗쪽 손가락을 연속적으로 움직이기
		break;
	case '2':
		if (fingerFlipToggle[1])
			break; // 이미 손가락이 연속적으로 움직이고 있으면 건너뛰기
		fingerFlip[1] = true; // 가운데 손가락 접기
		fingerFlipBackward[1] = false; // 가운데 손가락 접기
		fingerFlipToggle[1] = true; // 가운데 손가락을 연속적으로 움직이기
		break;
	case '3':
		if (fingerFlipToggle[2])
			break; // 이미 손가락이 연속적으로 움직이고 있으면 건너뛰기
		fingerFlip[2] = true; // 아랫쪽 손가락 접기
		fingerFlipBackward[2] = false; // 아랫쪽 손가락 접기
		fingerFlipToggle[2] = true; // 아랫쪽 손가락을 연속적으로 움직이기
		break;
	case '4':
		for (int i = 0; i < 3; i++)
		{
			// 모든 손가락에 대해 연속적으로 접으라고 명령
			if (!fingerFlipToggle[i]) // 손가락이 연속적으로 움직이고 있으면 해당 손가락 건너뛰기
			{
				fingerFlip[i] = true; 
				fingerFlipBackward[i] = false;
				fingerFlipToggle[i] = true;
			}
		}
		break;
	case 'S':
	case 's':
		// 모든 손가락에 대해 멈추라고 명령
		for (int i = 0; i < 3; i++)
		{
			fingerFlip[i] = false;
			fingerFlipBackward[i] = false;
			fingerFlipToggle[i] = false;
		}
		break;
	}
}

// Mouse Event가 발생했을 때 호출되는 callback 함수
void MyMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		// 마우스 좌클릭을 했을 때 어깨, 팔꿈치, 모든 손가락을 안으로 움직이기
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
		// 마우스 우클릭을 했을 때 어깨, 팔꿈치, 모든 손가락을 원상태로 돌리기
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
	glutInit(&argc, argv); // Window OS와 세션 연결 & GLUT Library 초기화
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // Display Mode 설정 (트루 컬러 모드 & 2개의 버퍼 사용)
	glutInitWindowPosition(100, 100); // 윈도우 위치 설정
	glutInitWindowSize(800, 600); // 윈도우 크기 설정
	glutCreateWindow("Robot Arm"); // 윈도우 생성 및 이름 지정
	MyInit(); // 초기화 설정 적용
	glutDisplayFunc(MyDisplay); // Display Event가 발생할 때마다 MyDisplay 호출하도록 등록
	glutReshapeFunc(MyReshape); // 화면을 다시 그려야 할 때마다 MyReshape 호출하도록 등록
	glutKeyboardFunc(MyKeyboard); // Keyboard Event가 발생할 때마다 MyKeyboard 호출하도록 등록
	glutMouseFunc(MyMouse); // Mouse Event가 발생할 때마다 MyMouse 호출하도록 등록
	glutIdleFunc(MyIdle); // 처리하고 있는 이벤트가 없을 때 MyIdle 호출하도록 등록
	glutMainLoop(); // GLUT Event 처리 Loop 진입
	return 0;
}