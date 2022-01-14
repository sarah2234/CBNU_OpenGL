/*******************************************************************************************************/
/*                                     HW#3-6. Timer Callback 응용                                     */
/*  작성자 : 이승현                                                             날짜 : 2021년 10월 6일 */
/*                                                                                                     */
/* 문제 정의 :                                                                                         */
/* 1. Timer Callback을 이용하여 사각형이 양옆으로 연속적으로 움직이도록 한다.                          */
/* 2. Mouse Callback을 이용하여 마우스 왼쪽 키를 누르면 움직이는 도형이 멈추도록 한다.                 */
/* 3. Reshape CAllback을 이용하여 사각형이 윈도우 영역을 벗어나지 않도록 한다.                         */
/* 기능 :                                                                                              */
/* 1. 사각형이 좌우로 deltaX만큼 움직이도록 한다.                                                      */
/* 2. 사각형이 창의 옆면에 닿았을 때 원래 움직이던 방향의 반대 방향으로 움직여서 창 밖 영역으로        */
/*    넘어가지 않도록 한다.                                                                            */
/* 3. 사각형이 창의 오른쪽에 닿으면 파란색으로, 왼쪽에 닿으면 빨간색으로 변한다.                       */
/* 4. 창의 크기를 바꿨을 때 사각형이 창 밖 영역으로 넘어가지 않도록 한다.                              */
/* 5. 마우스를 좌클릭하였을 때 움직이는 사각형이 멈추도록 한다.                                        */
/*******************************************************************************************************/


#include <gl/glut.h>

GLfloat deltaX; // 사각형을 x축으로 움직이기 위한 변수
GLfloat windowWidth, windowHeight; // 창의 크기에 대한 정보를 저장하는 변수
GLboolean stop = false; // 우클릭하면 사각형이 움직이지 않도록 하는 변수
GLboolean left = false, right = true; // 사각형의 움직임에 대한 방향을 설정하는 변수
GLfloat red = 1.0, blue = 0.0; // 사각형이 창의 오른쪽에 부딪히면 파란색, 왼쪽에 부딪히면 빨간색으로 변하도록 하는 변수

// Display Event가 일어날 때 사각형을 그리도록 하는 함수
void MyDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT); // 화면에서 그림 지우기
    glBegin(GL_POLYGON); // 사각형 그리기
    glColor3f(red, 0.0, blue); // 사각형 색깔 지정
    glVertex3f(-1.0 + deltaX, -0.5, 0.0); // 사각형이 x축 기준으로 deltaX만큼 움직이도록 설정
    glVertex3f(0.0 + deltaX, -0.5, 0.0);
    glVertex3f(0.0 + deltaX, 0.5, 0.0);
    glVertex3f(-1.0 + deltaX, 0.5, 0.0);
    glEnd(); // 그리기 끝내기
    glutSwapBuffers(); // 백 버퍼와 전면 버퍼를 서로 전환하여 사각형을 화면에 그림
}

// 화면을 새로 그려야 할 때 창의 크기에 대한 정보를 저장하고, 사각형의 비율과 위치를 재조정하는 함수
void MyReshape(int w, int h)
{
    GLfloat widthFactor = (GLfloat)w / (GLfloat)300;
    GLfloat heightFactor = (GLfloat)h / (GLfloat)300;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION); // 투영 행렬 선택
    glLoadIdentity(); // 투영 행렬을 항등 행렬로 초기화
    glOrtho(-1 * widthFactor, 1 * widthFactor, -1 * heightFactor, 1 * heightFactor, -1, 1); // 가시부피를 뷰폿의 종횡비에 맞추기

    windowWidth = 2 * widthFactor;
    windowHeight = 2 * heightFactor;

    if (-1.0 + deltaX < -windowWidth / 2)
    {
        deltaX = 1.0 - windowWidth / 2; // 사각형이 창의 왼쪽 바깥에 위치하면 창의 왼쪽 면에 맞닿도록 위치 조정
    }
    else if (deltaX > windowWidth / 2)
    {
        deltaX = windowWidth / 2; // 사각형이 창의 오른쪽 바깥에 위치하면 창의 오른쪽 면에 맞닿도록 위치 조정
    }
}

// 마우스 좌클릭 이벤트를 처리하는 함수
void MyMouse(GLint button, GLint state, GLint x, GLint y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
        stop = true; // 마우스 좌클릭을 하였을 때 사각형 멈추기
	}
}

// 시간에 대한 처리를 하는 함수
void MyTimer(int value) {
    if (0.0 + deltaX > windowWidth / 2) 
    {
        right = false;
        left = true; // 사각형이 창의 오른쪽 면에 닿았을 때 사각형이 왼쪽으로 움직이도록 함

        blue = 1.0; // 사각형이 창의 오른쪽 면에 닿았을 때 사각형이 파란색으로 변함
        red = 0.0;
    }
    if (-1.0 + deltaX < -windowWidth / 2)
    {
        right = true; // 사각형이 창의 왼쪽 면에 닿았을 때 사각형이 오른쪽으로 움직이도록 함
        left = false;

        blue = 0.0; 
        red = 1.0; // 사각형이 창의 오른쪽 면에 닿았을 때 사각형이 빨간색으로 변함
    }
    if (!stop) // 마우스 좌클릭하기 전까지 deltaX 값에 따라 사각형이 계속 움직임
    {
        if (right)
            deltaX += 0.1; // 창의 오른쪽 경계에 닿기 전까지 사각형이 오른쪽으로 이동
        else if (left)
            deltaX -= 0.1; // 창의 왼쪽 경계에 닿기 전까지 사각형이 왼쪽으로 이동
    }

    glutPostRedisplay(); // Display Event를 강제로 발생시킴
    glutTimerFunc(40, MyTimer, 1); // 40밀리초마다 MyTimer 호출
}

void main(int argc, char** argv)
{
    glutInit(&argc, argv); // Window OS 세션과 연결하고 GLUT Library 초기화
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // 트루컬러 모드와 더블 버퍼를 사용하도록 Display Mode 설정
    glutInitWindowPosition(0, 0); // 창 위치 설정
    glutInitWindowSize(300, 300); // 창 크기 설정
    glutCreateWindow("Timer Callback"); // 창 이름 설정과 함께 창 생성
    glClearColor(1.0, 1.0, 1.0, 1.0); // 흰색으로 화면 지우기
    glutDisplayFunc(MyDisplay); // Display Event가 일어날 때마다 MyDisplay 호출하도록 등록
    glutReshapeFunc(MyReshape); // 화면을 새로 그려야 할 때마다 MyReshape 호출하도록 등록
    glutMouseFunc(MyMouse); // Mouse Event가 일어날 때마다 MyMouse 호출하도록 등록
    glutTimerFunc(40, MyTimer, 1); // 40밀리초 이후에 MyTimer 호출하도록 등록
    glutMainLoop(); // GLUT Event 처리 Loop 진입
    return;
}