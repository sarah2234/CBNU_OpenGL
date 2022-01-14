/*******************************************************************************************************/
/*                                     HW#3-3. Mouse Callback 응용                                     */
/*  작성자 : 이승현                                                             날짜 : 2021년 10월 6일 */
/*                                                                                                     */
/* 문제 정의 :                                                                                         */
/* 1. Mouse Callback을 이용하여 좌클릭과 우클릭으로 사각형의 움직임을 제어한다.                        */
/* 2. Idle Callback을 이용하여 사각형이 연속적으로 움직이도록 한다.                                    */
/* 3. Display Callback을 이용하여 사각형이 창 밖을 벗어나지 않도록 한다.                               */
/* 기능 :                                                                                              */
/* 1. 마우스의 왼쪽 버튼을 클릭하면 사각형이 0.01씩 연속적으로 움직인다.                               */
/* 2. 마우스의 오른쪽 버튼을 클릭하면 이동하고 있는 사각형이 멈춘다.                                   */
/* 3. 창의 크기를 바꿨을 때 사각형이 창 밖 영역으로 넘어가지 않도록 한다.                              */
/*******************************************************************************************************/

// 사각형의 움직이는 속도가 빨라 0.01로 맞추었습니다.

#include <GL/glut.h>

GLfloat moveX; // 사각형의 위치를 설정하기 위한 변수
GLfloat windowWidth; // 현재 창 크기에 대한 값을 저장

// 초기 설정
void MyInit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0); // 흰색으로 화면 지우기

	glMatrixMode(GL_PROJECTION); // 투영 행렬 선택
	glLoadIdentity(); // 투영 행렬을 항등 행렬로 초기화
	glOrtho(-1.0, 1.0, -1.0, -1.0, -1.0, 1.0); // 직교 투영을 만듦
}

// Display Event가 발생할 때 창에서 그림을 지우고 사각형을 그리는 함수
void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT); // 색 버퍼를 삭제하여 창에서 그림 삭제
	glColor3f(0.5, 0.5, 0.5); // 사각형을 회색으로 설정

	if (0.5 + moveX > windowWidth / 2)
	{
		moveX = -0.5 + windowWidth / 2; // 사각형이 창의 오른쪽 바깥에 위치하면 창의 오른쪽 면에 맞닿도록 위치 조정
	}

	glBegin(GL_POLYGON); // 사각형 그리기 시작
	
	glVertex3f(-0.5 + moveX, -0.5, 0.0); // 왼쪽 아래
	glVertex3f(0.5 + moveX, -0.5, 0.0); // 오른쪽 아래
	glVertex3f(0.5 + moveX, 0.5, 0.0); // 오른쪽 위
	glVertex3f(-0.5 + moveX, 0.5, 0.0); // 왼쪽 위
	glEnd(); // 사각형 그리기 끝내기
	glutSwapBuffers();
}

// 화면을 새로 그려야 할 때 사각형의 비율이 동일하도록 맞추고, 사각형의 위치를 재조정하는 함수
void MyReshape(int width, int height)
{
	GLfloat widthFactor = (GLfloat)width / (GLfloat)500;
	GLfloat heightFactor = (GLfloat)height / (GLfloat)500;
	glViewport(0, 0, width, height); // 뷰폿 설정

	glMatrixMode(GL_PROJECTION); // 투영 행렬 선택
	glLoadIdentity(); // 투영 행렬을 항등 행렬로 초기화
	// 창의 크기가 바뀌어도 사각형의 크기는 맞추도록 함
	glOrtho(-1 * widthFactor, 1 * widthFactor, -1 * heightFactor, 1 * heightFactor, -1, 1);

	windowWidth = 2 * widthFactor; // 창 가로 길이
}

// 키보드에서 키를 입력받아 처리하는 함수
void MyKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'Q':
		exit(0); break;
	case 'q':
		exit(0); break;
	case 27: // esc
		exit(0); break; // Q, q, esc를 누르면 종료
	}
	
	glutPostRedisplay(); // 강제로 Display Event 발생시킴
}

// Idle일 때 사각형이 왼쪽으로 움직이도록 하는 함수
void MoveToTheLeft(void)
{
	if (0.5 + moveX < windowWidth / 2)
		moveX += 0.01; // 사각형이 창 밖을 아직 넘어서지 않으면 연속적으로 오른쪽으로 움직이도록 함
	glutPostRedisplay(); // 강제로 Display Event 발생시킴
}

// 마우스 클릭할 때에 대한 이벤트를 처리하는 함수
void MyMouseClick(GLint button, GLint state, GLint x, GLint y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		glutIdleFunc(MoveToTheLeft); // 좌클릭을 하면 해당 Idle Callback 함수를 호출하여 사각형이 연속적으로 왼쪽으로 움직임 
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		glutIdleFunc(NULL); // 우클릭을 하면 사각형의 움직임에 대한 어떠한 설정도 하지 않음
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); // Window OS 세션과 연결하고 GLUT Library 초기화
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // Display Mode 설정
	glutInitWindowPosition(0, 0); // 창 위치 설정
	glutInitWindowSize(500, 500); // 창 크기 설정
	glutCreateWindow("Keyboard Callback-1"); // 창 생성 및 이름 설정
	MyInit(); // 초기 설정
	glutDisplayFunc(MyDisplay); // Display Event가 일어날 때마다 MyDisplay 호출하도록 등록
	glutReshapeFunc(MyReshape); // 화면을 새로 그려야 할 때마다 MyReshape 호출하도록 등록
	glutKeyboardFunc(MyKeyboard); // 키보드로부터 키를 입력받을 때마다 MyKeyboard 호출하도록 등록
	glutMouseFunc(MyMouseClick); // 마우스를 클릭할 때마다 MyMouseClick 호출하도록 등록
	glutMainLoop(); // GLUT Event 처리 Loop 진입
	return 0;
}