/*******************************************************************************************************/
/*                                     HW#3-2. Keyboard Callback 응용II                                */
/*  작성자 : 이승현                                                             날짜 : 2021년 10월 6일 */
/*                                                                                                     */
/* 문제 정의 :                                                                                         */
/* 1. Keyboard Callback을 이용하여 사각형의 움직임을 구현한다.                                         */
/* 2. Special Keyboard Callback을 이용하여 사각형의 크기를 조절한다.                                   */
/* 3. Display Callback을 이용하여 사각형이 창 밖을 벗어나지 않도록 한다.                               */
/* 기능 :                                                                                              */
/* 1. 마우스의 왼쪽 버튼을 클릭하면 사각형이 0.01씩 연속적으로 움직인다.                               */
/* 2. 마우스의 오른쪽 버튼을 클릭하면 이동하고 있는 사각형이 멈춘다.                                   */
/* 3. 창의 크기를 바꿨을 때 사각형이 창 밖 영역으로 넘어가지 않도록 한다.                              */
/* 4. 사각형의 크기를 고려하여 창 밖 영역으로 넘어가지 않도록 한다.                                    */
/*******************************************************************************************************/

#include <GL/glut.h>

GLfloat moveX, moveY; // 사각형의 위치를 설정하기 위한 변수
GLfloat sizeX, sizeY; // 사각형의 크기를 설정하기 위한 변수
GLint red = 1, blue = 1; // 사각형의 색깔을 설정하기 위한 변수
GLfloat windowWidth, windowHeight; // 현재 창 크기에 대한 값을 저장

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

	// 사각형의 크기가 창을 넘어설 때 사각형의 크기를 창의 크기만큼 설정
	if (sizeX > windowWidth / 2 - 0.5 || sizeY > windowHeight / 2 - 0.5)
	{
		sizeX = windowWidth / 2 - 0.5;
		sizeY = windowHeight / 2 - 0.5;
	}

	// 사각형이 창의 바깥 영역에 위치하면 사각형이 창의 내부에 위치할 수 있도록 조정
	if (-0.5 + moveX - sizeX < -windowWidth / 2) // 왼쪽 아래 점의 x좌표가 바깥 영역에 있을 때 조정
		moveX = 0.5 + sizeX - windowWidth / 2;
	if (-0.5 + moveY - sizeY < -windowHeight / 2) // 왼쪽 아래 점의 y 좌표가 바깥 영역에 있을 때 조정
		moveY = 0.5 + sizeY - windowHeight / 2;
	if (0.5 + moveX + sizeX > windowWidth / 2) // 오른쪽 위 점의 x좌표가 바깥 영역에 있을 때 조정
		moveX = -0.5 - sizeX + windowWidth / 2;
	if (0.5 + moveY + sizeY > windowHeight / 2) // 오른쪽 위 점의 y 좌표가 바깥 영역에 있을 때 조정
		moveY = -0.5 - sizeY + windowHeight / 2;

	glBegin(GL_POLYGON); // 사각형 그리기 시작
	glVertex3f(-0.5 + moveX - sizeX, -0.5 + moveY - sizeY, 0.0); // 왼쪽 아래
	glVertex3f(0.5 + moveX + sizeX, -0.5 + moveY - sizeY, 0.0); // 오른쪽 아래
	glVertex3f(0.5 + moveX + sizeX, 0.5 + moveY + sizeY, 0.0); // 오른쪽 위
	glVertex3f(-0.5 + moveX - sizeX, 0.5 + moveY + sizeY, 0.0); // 왼쪽 위
	glEnd(); // 사각형 그리기 끝내기
	glFlush(); // 현재 상태 변수를 기준으로 파이프라인 프로세스 실행
}

// 화면을 새로 그려야 할 때 사각형의 비율이 동일하도록 맞추고, 사각형의 위치를 재조정하는 함수
void MyReshape(int width, int height)
{
	GLfloat widthFactor = (GLfloat)width / (GLfloat)500;
	GLfloat heightFactor = (GLfloat)height / (GLfloat)500;
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// 창의 크기가 바뀌어도 사각형의 크기는 맞추도록 함
	glOrtho(-1 * widthFactor, 1 * widthFactor, -1 * heightFactor, 1 * heightFactor, -1, 1); 

	windowWidth = 2 * widthFactor; // 창 가로 길이
	windowHeight = 2 * heightFactor; // 창 세로 길이
}

// 키보드에서 키를 입력받아 처리하는 함수
void MyKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
	case 'A': // a나 A를 입력받으면 사각형이 창의 왼쪽면에 닿을 때까지 왼쪽으로 움직임
		if(-0.5 + moveX - sizeX > -windowWidth / 2)
			moveX -= 0.1;
		break;
	case 'f':
	case 'F': // f나 F를 입력받으면 사각형이 창의 오른쪽면에 닿을 때까지 오른쪽으로 움직임
		if (0.5 + moveX + sizeX < windowWidth / 2)
			moveX += 0.1;
		break;
	case 'r':
	case 'R': // r나 R를 입력받으면 사각형이 창의 아래쪽면에 닿을 때까지 아래쪽으로 움직이고 사각형이 빨간색으로 바뀜
		if (-0.5 + moveY - sizeY > -windowHeight / 2)
			moveY -= 0.1;
		red = 1;
		blue = 0;
		break;
	case 'v':
	case 'V': // v나 V를 입력받으면 사각형이 창의 위쪽면에 닿을 때까지 위쪽으로 움직임
		if (0.5 + moveY + sizeY < windowHeight / 2)
			moveY += 0.1;
		break;
	case 'b':
	case 'B': // b나 B를 입력받으면 사각형이 파란색으로 바뀜
		red = 0;
		blue = 1;
		break;
	case 'Q':
		exit(0); break;
	case 'q':
		exit(0); break;
	case 27: // esc
		exit(0); break; // Q, q, esc를 누르면 종료
	}
	glutPostRedisplay(); // 강제로 Display Event 발생시킴
}

// 특수키를 입력받아 처리하는 함수
void MySpecialKey(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_PAGE_UP: // Pg Up 키를 입력 받았을 때
		if (sizeX < windowWidth / 2 - 0.5 && sizeY < windowHeight / 2 - 0.5)
		{
			sizeX += 0.05; // (0.1 / 2) 크기만큼 양옆, 위아래 늘려주기
			sizeY += 0.05;
		}
		break;
	case GLUT_KEY_PAGE_DOWN:
		if (sizeX > -0.5 && sizeY > -0.5) // Pg Down 키를 입력 받았을 때
		{
			sizeX -= 0.05; // (0.1 / 2) 크기만큼 양옆, 위아래 줄이기
			sizeY -= 0.05;
		}
		break;
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
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);
	glutSpecialFunc(MySpecialKey);
	glutMainLoop(); // GLUT Event 처리 Loop 진입
	return 0;
}