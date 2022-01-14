/*******************************************************************************************************/
/*                                           HW#1 : 3D Sierpinski Gasket                               */
/*  작성자 : 이승현                                                             날짜 : 2021년 9월 20일 */
/*                                                                                                     */
/* 문제 정의 :                                                                                         */
/* 3D Sierpinski Gasket을 구현하고, Reshape callback을 사용하여 왜곡 문제를 해결한다.                  */
/* 기능 :                                                                                              */
/* 1. (0, 0, 0), (500, 0, 0), (250, 250 * √3, 0), (250, 250 / 3 * √3, 500 / 3 * √3)을 꼭짓점으로    */
/*    갖는 정사면체를 X, Y축 기준으로 각각 40, -20°만큼 회전하여 해당 사면체를 입체적으로 그린다.     */
/*    사면체의 내부에 위치한 점 p와 사면체의 꼭짓점 중 임의의 한 꼭지점 간의 중점을 점 p로 찍고, 다시  */
/*    점 p와 사면체의 꼭짓점 중 임의의 한 꼭지점 간의 중점을 점 p로 찍는 과정을 50000번 반복하여       */
/*    3D tetrahedron Gasket을 구현한다.                                                                */
/*    이때 z축에서 작은 수를 가진 점일 수록 빨간색을, 큰 수를 가진 점일 수록 초록색을 띤다.            */
/* 2. MyReshape 콜백함수를 통해 가시부피와 뷰폿과의 종횡비를 일치시키고, glutReshapeFunc를 통해        */
/*    MyReshape콜백함수를 등록한다. 이때 화면의 중심은 (0, 0, 0)이다.                                  */
/*******************************************************************************************************/

#define RADIAN 3.14159 / 180.0 // 라디안 정의
#include <GL/glut.h>
#include <stdlib.h> // rand() 함수 사용 용도
#include <math.h> // sqrt(), fabs() 함수 사용 용도

// 초기 설정
void MyInit()
{ 
	glClearColor(1.0, 1.0, 1.0, 1.0); // 하얀배경으로 세팅
	glColor3f(1.0, 0.0, 0.0); // 빨간점으로 세팅

	glMatrixMode(GL_PROJECTION); // 투영행렬 선택
	glLoadIdentity(); // 현재 투영행렬을 항등행렬로 초기화
	glOrtho(0.0, 500.0, 0.0, 500.0, 1, -1); // 행렬변환

	glMatrixMode(GL_MODELVIEW);  // 모델뷰행렬 선택
	glLoadIdentity(); // 현재 모델뷰 행렬을 항등행렬로 초기화
}

// X축 기준으로 x°만큼 좌표 회전
void RotateX(float vertex[3], float x)
{
	float y, z;
	y = vertex[1];
	z = vertex[2];
	vertex[1] = y * cosf(x * RADIAN) - z * sinf(x * RADIAN);
	vertex[2] = y * sinf(x * RADIAN) + z * cosf(x * RADIAN);
}

// Y축 기준으로 y°만큼 좌표 회전
void RotateY(float vertex[3], float y)
{
	float x, z;
	x = vertex[0];
	z = vertex[2];
	vertex[0] = z * sinf(y * RADIAN) + x * cosf(y * RADIAN);
	vertex[2] = z * cosf(y * RADIAN) - x * sinf(y * RADIAN);
}

// Z축 기준으로 z°만큼 좌표 회전
void RotateZ(float vertex[3], float z)
{
	float x, y;
	x = vertex[0];
	y = vertex[1];
	vertex[0] = x * cosf(z * RADIAN) - y * sinf(z * RADIAN);
	vertex[1] = x * sinf(z * RADIAN) + y * cosf(z * RADIAN);
}

// 3D Sierpinski Gasket 구현
void MyDisplay(void)
{
	float vertices[4][3] = { {0.0, 0.0, 0.0},
		{500.0,0.0,0.0},
		{250.0, 250.0 * sqrt(3), 0.0},
		{250.0, 250.0 / 3 * sqrt(3), 500.0 / 3 * sqrt(6)} }; // 초기 정사면체의 꼭지점 좌표
	float minZ = vertices[0][2], maxZ = vertices[0][2];
	for (int i = 0; i < 4; i++)
	{
		RotateX(vertices[i], 40); // 모든 점에 대해 X축 기준으로 40°회전
		RotateY(vertices[i], -20); // 모든 점에 대해 Y축 기준으로 -20°회전
		RotateZ(vertices[i], 0); // Z축 기준으로는 회전하지 않는다.
		if (minZ > vertices[i][2])
			minZ = vertices[i][2]; // 회전 후 꼭지점 중 z축에서 가장 작은 값을 가지는 점의 z축 좌표를 minZ에 저장
		if (maxZ < vertices[i][2])
			maxZ = vertices[i][2]; // 회전 후 꼭지점 중 z축에서 가장 큰 값을 가지는 점의 z축 좌표를 maxZ에 저장
	}
	float rangeZ = maxZ - minZ; // rangeZ = z축 범위

	int i, j;
	float p[3] = { 250.0, 125.0, 150.0 };  // 찍힐 포인트
	RotateX(p, 40); // 점 p를 X축 기준으로 40°회전
	RotateY(p, -20); //점 p를 Y축 기준으로 -20°회전
	RotateZ(p, 0); // Z축 기준으로는 회전하지 않는다.

	glClear(GL_COLOR_BUFFER_BIT); // 색 버퍼 삭제하여 윈도우에서 그림 제거

	for (j = 0; j < 50000; j++)
	{
		i = rand() % 4; // 임의의 점 선택
		// 새로 선택된 점과 현재 점을 기준으로 새로운 점 위치 계산 
		p[0] = (p[0] + vertices[i][0]) / 2.0; // x 좌표
		p[1] = (p[1] + vertices[i][1]) / 2.0; // y 좌표
		p[2] = (p[2] + vertices[i][2]) / 2.0; // z 좌표

		glBegin(GL_POINTS); // 점 그리기 시작 (glBegin과 glEnd 사이에서 정점 정의)
		// z축 상 큰 값을 가지는 점일 수록 초록색, 작은 값을 가지는 점일 수록 빨간색을 띤다.
		if (minZ < 0)
			glColor3f(1.0 - (p[2] + fabs(minZ)) / rangeZ, (p[2] + fabs(minZ)) / rangeZ, 0.0);
		else
			glColor3f(1.0 - (p[2] - minZ) / rangeZ, (p[2] - minZ) / rangeZ, 0.0);
		glVertex3fv(p); // 찍힐 위치에 점 찍기
		glEnd(); // 점 그리기 끝내기
	}

	glFlush(); // 아직 실행되지 않은 명령을 모두 실행 (현재 상태변수를 기준으로 파이프라인 프로세스 실행)
}

void MyReshape(int NewWidth, int NewHeight)
{ 
	glViewport(0, 0, NewWidth, NewHeight); // glViewport: 뷰폿 설정 (뷰폿 사각형의 왼쪽 아래 모퉁이의 픽셀값과 뷰폿의 너비, 높이를 인수로 입력받음)
	GLfloat Widthfactor = (GLfloat)NewWidth / (GLfloat)500; // 바뀐 뷰폿의 너비에 대한 비율
	GLfloat Heightfactor = (GLfloat)NewHeight / (GLfloat)500; // 바뀐 뷰폿의 높이에 대한 비율
	glMatrixMode(GL_PROJECTION); // 투영행렬 선택
	glLoadIdentity(); // 현재 투영행렬을 항등 행렬로 초기화
	// glOrtho: 늘어난 뷰폿 비율만큼 가시부피의 종횡비를 조정
	glOrtho(-600.0 * Widthfactor, 600.0 * Widthfactor, -600.0 * Heightfactor, 600.0 * Heightfactor, -600.0, 600.0);
} 

void main(int argc, char** argv)
{
	glutInit(&argc, argv); // Window OS와 세션을 연결하고 GLUT Library를 초기화
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Display Mode 설정 (단일 버퍼 창을 만들고 RGB 모드로 설정)
	glutInitWindowSize(500, 500); // Window 창 크기를 (500, 500)으로 설정
	glutInitWindowPosition(0, 0); // Window 창 위치를 (0, 0)으로 설정
	glutCreateWindow("Sierpinski Gasket"); // 이름이 "Sierpinski Gasket"인 Window 창 생성
	MyInit(); // 초기 설정
	glutDisplayFunc(MyDisplay); // Window를 그릴 때마다 MyDisplay 함수를 호출하도록 콜백함수 등록
	glutReshapeFunc(MyReshape); // Window의 크기를 변경할 때마다 MyReshape 함수를 호출하도록 콜백함수 등록
	glutMainLoop(); // GLUT Event 처리 Loop 진입 (함수가 계속 실행되면서 발생한 메시지를 받아 메시지 처리함수를 호출)
}
