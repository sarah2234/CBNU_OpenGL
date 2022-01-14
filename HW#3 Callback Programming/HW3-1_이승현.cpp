/*******************************************************************************************************/
/*                                       HW#3-1 : Keyboard Callback 응용I                              */
/*  작성자 : 이승현                                                             날짜 : 2021년 10월 6일 */
/*                                                                                                     */
/* 문제 정의 :                                                                                         */
/* 사각형을 그린 후 Keyboard Callback을 통해 해당 사각형의 움직임 및 색깔 바꾸는 기능을 구현한다.      */
/* 기능 :                                                                                              */
/* 1. a 또는 A를 누르면 사각형이 왼쪽으로 0.1씩 이동한다.                                              */
/* 2. f 또는 F를 누르면 사각형이 오른쪽으로 0.1씩 이동한다.                                            */
/* 3. r 또는 R을 누르면 사각형이 아래로 0.1씩 이동하고, 빨간색으로 바뀐다.                             */
/* 4. v 또는 V를 누르면 사각형이 위로 0.1씩 이동한다.                                                  */
/* 5. b 또는 B를 누르면 사각형이 파란색으로 바뀐다.                                                    */
/*******************************************************************************************************/

#include <GL/glut.h>

GLfloat moveX;
GLfloat moveY;
GLint red = 1;
GLint blue = 1;

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
	glColor3f(red, 0, blue); // 초기 색깔은 핑크색으로 설정

	glBegin(GL_POLYGON); // 사각형 그리기 시작
	glVertex3f(-0.5 + moveX, -0.5 + moveY, 0.0);
	glVertex3f(0.5 + moveX, -0.5 + moveY, 0.0);
	glVertex3f(0.5 + moveX, 0.5 + moveY, 0.0);
	glVertex3f(-0.5 + moveX, 0.5 + moveY, 0.0);
	glEnd(); // 사각형 그리기 끝내기
	glFlush(); // 현재 상태 변수를 기준으로 파이프라인 프로세스 실행
}

// 화면을 새로 그려야 할 때 사각형의 비율이 동일하도록 맞추는 함수
void MyReshape(int width, int height)
{
	glViewport(0, 0, width, height); // 뷰폿 설정

	glMatrixMode(GL_PROJECTION); // 투영 행렬 선택
	glLoadIdentity(); // 투영 행렬을 항등 행렬로 초기화
	glOrtho(-1 , 1 , -1 * height / width, 1 * height / width, -1, 1); // 가시부피를 뷰폿의 종횡비에 맞추기
}

// 키보드를 이용하여 사각형을 움직이도록 하는 함수
void MyKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
	case 'A': // a나 A를 입력받으면 사각형이 왼쪽으로 움직임
		moveX -= 0.1;
		break;
	case 'f':
	case 'F': // f나 f를 입력받으면 사각형이 오른쪽으로 움직임
		moveX += 0.1;
		break;
	case 'r':
	case 'R': // r나 R를 입력받으면 사각형이 아래쪽으로 움직이고 빨간색으로 변함
		moveY -= 0.1;
		red = 1;
		blue = 0;
		break;
	case 'v':
	case 'V': // v나 V를 입력받으면 사각형이 위쪽으로 움직임
		moveY += 0.1;
		break;
	case 'b':
	case 'B': // b나 B를 입력받으면 사각형이 파란색으로 변함
		red = 0;
		blue = 1;
		break;
	case 'Q':
		exit(0); break;
	case 'q':
		exit(0); break;
	case 27: // esc
		exit(0); break; // Q, q, esc를 누르면 프로그램 종료
	}
	glutPostRedisplay(); // 강제로 Display Event 발생시킴
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); // Window OS 세션과 연결하고 GLUT Library 초기화
	glutInitDisplayMode(GLUT_RGB); // Display Mode 설정
	glutInitWindowPosition(0, 0); // 창 위치 설정
	glutInitWindowSize(500, 500); // 창 크기 설정
	glutCreateWindow("Keyboard Callback-1"); // 창 생성 및 이름 설정
	MyInit(); // 초기 설정
	glutDisplayFunc(MyDisplay); // Display Event가 일어날 때마다 MyDisplay 호출하도록 등록
	glutReshapeFunc(MyReshape); // 화면을 새로 그려야 할 때마다 MyReshape 호출하도록 등록
	glutKeyboardFunc(MyKeyboard); // Keyboard Event가 일어날 때마다 MyKeyboard 호출하도록 등록
	glutMainLoop(); // GLUT Event 처리 Loop 진입
	return 0;
}