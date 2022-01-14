/*******************************************************************************************************/
/*                                       HW#3-5 : Idle Callback 응용                                   */
/*  작성자 : 이승현                                                             날짜 : 2021년 10월 6일 */
/*                                                                                                     */
/* 문제 정의 :                                                                                         */
/* 1. Special Keyboard Callback을 이용하여 사각형이 움직일 방향을 설정한다.                            */
/* 2. Idle Callback을 이용하여 사각형이 연속적으로 움직이도록 한다.                                    */
/* 3. Display Callback을 이용하여 사각형이 창 밖의 영역으로 넘어가지 않도록 한다.                      */
/* 기능 :                                                                                              */
/* 1. ↑ : 사각형이 위쪽으로 0.01 이동                                                                 */
/* 2. ↓ : 사각형이 아래쪽으로 0.01 이동                                                               */
/* 3. ← : 사각형이 왼쪽으로 0.01 이동                                                                 */
/* 4. → : 사각형이 오른쪽으로 0.01 이동                                                               */
/* 5. 창의 크기를 바꿨을 때 사각형이 창 밖 영역으로 넘어가지 않도록 한다.                              */
/*******************************************************************************************************/

// 사각형의 움직이는 속도가 빨라 0.01로 맞추었습니다.

#include <gl/glut.h>

GLfloat deltaX = 0.0, deltaY = 0.0; // 사각형이 x축, y축 기준으로 움직이기 위한 변수
GLfloat windowWidth, windowHeight; // 창의 크기에 대한 정보를 저장하는 변수

// Display Event가 일어날 때 사각형을 그리도록 하는 함수
void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT); // 화면에서 그림 삭제
    glColor3f(0.0, 0.5, 0.8); // 해당 색으로 사각형 색깔 설정

    // 사각형이 창의 바깥 영역에 위치하면 사각형이 창의 내부에 위치할 수 있도록 조정
    if (-0.5 + deltaX < -windowWidth / 2) // 왼쪽 아래 점의 x좌표가 바깥 영역에 있을 때 조정
        deltaX = 0.5 - windowWidth / 2;
    if (-0.5 + deltaY < -windowHeight / 2) // 왼쪽 아래 점의 y 좌표가 바깥 영역에 있을 때 조정
        deltaY = 0.5 - windowHeight / 2;
    if (0.5 + deltaX > windowWidth / 2) // 오른쪽 위 점의 x좌표가 바깥 영역에 있을 때 조정
        deltaX = -0.5 + windowWidth / 2;
    if (0.5 + deltaY > windowHeight / 2) // 오른쪽 위 점의 y 좌표가 바깥 영역에 있을 때 조정
        deltaY = -0.5 + windowHeight / 2;

	glBegin(GL_POLYGON); // 사각형 그리기
    glVertex3f(-0.5 + deltaX, -0.5 + deltaY, 0.0); // 해당 사각형은 x축에서 deltaX만큼 이동, y축에서 deltaY만큼 이동
    glVertex3f(0.5 + deltaX, -0.5 + deltaY, 0.0);
    glVertex3f(0.5 + deltaX, 0.5 + deltaY, 0.0);
    glVertex3f(-0.5 + deltaX, 0.5 + deltaY, 0.0);
    glEnd(); // 그리기 끝내기
    glutSwapBuffers(); // 전면 버퍼와 후면 버퍼를 교체하여 후면 버퍼에 준비해둔 그림이 나타남
}

// 화면을 새로 그려야 할 때 창의 크기에 대한 정보를 저장하고, 사각형의 비율과 위치를 재조정하는 함수
void MyReshape(int w, int h)
{
    GLfloat widthFactor = (GLfloat)w / (GLfloat)300;
    GLfloat heightFactor = (GLfloat)h / (GLfloat)300;

    glViewport(0, 0, w, h); // 뷰폿 설정

    glMatrixMode(GL_PROJECTION); // 투영 행렬 선택
    glLoadIdentity(); // 투영 행렬을 항등 행렬로 초기화
    glOrtho(-1 * widthFactor, 1 * widthFactor, -1 * heightFactor, 1 * heightFactor, -1, 1); // 가시부피를 뷰폿의 종횡비에 맞추기

    windowWidth = 2 * widthFactor;
    windowHeight = 2 * heightFactor;
}

// 사각형이 연속적으로 왼쪽으로 움직이도록 하는 함수
void MoveToTheLeft()
{
    if (-0.5 + deltaX > -windowWidth / 2)
        deltaX -= 0.01; // 사각형이 창 내부 영역에 있도록 사각형 움직이기
    glutPostRedisplay(); // 강제로 Display Event를 발생시켜 바뀐 위치에 대한 사각형을 그림
}

// 사각형이 연속적으로 오른쪽으로 움직이도록 하는 함수
void MoveToTheRight()
{
    if (0.5 + deltaX < windowWidth / 2)
        deltaX += 0.01; // 사각형이 창 내부 영역에 있도록 사각형 움직이기
    glutPostRedisplay(); // 강제로 Display Event를 발생시켜 바뀐 위치에 대한 사각형을 그림
}

// 사각형이 연속적으로 위로 움직이도록 하는 함수
void MoveToTheTop()
{
    if (0.5 + deltaY < windowHeight / 2)
        deltaY += 0.01; // 사각형이 창 내부 영역에 있도록 사각형 움직이기
    glutPostRedisplay(); // 강제로 Display Event를 발생시켜 바뀐 위치에 대한 사각형을 그림
}

// 사각형이 연속적으로 아래로 움직이도록 하는 함수
void MoveToTheBottom()
{
    if (-0.5 + deltaY > -windowHeight / 2)
        deltaY -= 0.01; // 사각형이 창 내부 영역에 있도록 사각형 움직이기
    glutPostRedisplay(); // 강제로 Display Event를 발생시켜 바뀐 위치에 대한 사각형을 그림
}

// 키보드의 특수키를 입력받았을 때 호출되는 함수
void MySpecialKey(int key, int x, int y)
{
    // 방향키를 입력받았을 때 큐에 이벤트가 없으면 각각의 방향키에 맞는 callback 함수 호출
    switch (key)
    {
    case GLUT_KEY_LEFT: // 왼쪽 방향키 입력
        glutIdleFunc(MoveToTheLeft); // 사각형이 왼쪽으로 움직임
        break;
    case GLUT_KEY_RIGHT: // 오른쪽 방향키 입력
        glutIdleFunc(MoveToTheRight); // 사각형이 오른쪽으로 움직임
        break;
    case GLUT_KEY_UP: // 위쪽 방향키 입력
        glutIdleFunc(MoveToTheTop); // 사각형이 위쪽으로 움직임
        break;
    case GLUT_KEY_DOWN: // 아래쪽 방향키 입력
        glutIdleFunc(MoveToTheBottom); // 사각형이 아래쪽으로 움직임
        break;
    }
}

void main(int argc, char** argv)
{
    glutInit(&argc, argv); // Window OS 세션과 연결하고 GLUT Library 초기화
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // 트루컬러 모드와 더블 버퍼를 사용하도록 Display Mode 설정
    glutInitWindowPosition(0, 0); // 창 위치 설정
    glutInitWindowSize(300, 300); // 창 크기 설정
    glutCreateWindow("Idle Callback"); // 창 이름 설정과 함께 창 생성
    glutDisplayFunc(MyDisplay); // Display Event가 일어날 때마다 MyDisplay 호출하도록 등록
    glutReshapeFunc(MyReshape); // 화면을 새로 그려야 할 때마다 MyReshape 호출하도록 등록
    glutSpecialFunc(MySpecialKey); // 키보드로부터 특수키를 입력받을 때마다 MySpecialKey 호출하도록 등록
    glutMainLoop(); // GLUT Event 처리 Loop 진입
}