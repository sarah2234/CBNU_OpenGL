/*******************************************************************************************************/
/*                                 HW#5-1 : gluLookAt()의 실시간 제어(1)                               */
/*  작성자 : 이승현                                                            날짜 : 2021년 10월 31일 */
/*                                                                                                     */
/* 문제 정의 :                                                                                         */
/* 1. 시점 좌표계를 Keyboard Callback 함수로 실시간 제어가 가능하도록 구현한다.                        */
/* 기능 :                                                                                              */
/* 1. ↑ 키를 누르면 Camera의 Y축 좌표가 0.01씩 연속적으로 증가                                        */
/* 2. ↓ 키를 누르면 Camera의 Y축 좌표가 0.01씩 연속적으로 감소                                        */
/* 3. ← 키를 누르면 Camera의 X축 좌표가 0.01씩 연속적으로 감소                                        */
/* 4. → 키를 누르면 Camera의 X축 좌표가 0.01씩 연속적으로 증가                                        */
/* 5. a 또는 A 키를 누르면 초점(Focus)의 X축 좌표가 0.01씩 연속적으로 증가                             */
/* 6. f 또는 F 키를 누르면 초점(Focus)의 X축 좌표가 0.01씩 연속적으로 감소                             */
/* 7. r 또는 R 키를 누르면 초점(Focus)의 Y축 좌표가 0.01씩 연속적으로 증가                             */
/* 8. v 또는 V 키를 누르면 초점(Focus)의 Y축 좌표가 0.01씩 연속적으로 감소                             */
/* 9. z 또는 Z 키를 누르면 초점(Focus)의 Z축 좌표가 0.01씩 연속적으로 증가                             */
/* 10. t 또는 T 키를 누르면 초점(Focus)의 Z축 좌표가 0.01씩 연속적으로 감소                            */
/* 11: s 또는 S 키를 누르면 초기 변환 상태로 되돌아감                                                  */
/*******************************************************************************************************/

// 0.1일 때 속도가 너무 빨라 0.01로 수정하였습니다.

#include <GL/glut.h>

bool moveCameraX[2], moveCameraY[2], moveFocusX[2], moveFocusY[2], moveFocusZ[2]; // 카메라 및 초점의 위치를 제어하는 변수들
GLdouble cameraX, cameraY, focusX, focusY, focusZ; // 카메라 및 초점의 위치를 제어하는 변수들

// 초기 설정
void MyInit()
{
    glClearColor(0.0, 0.0, 0.0, 0.0); // 화면을 검은색으로 지우기

    // 초기 화면에서 카메라와 초점을 움직이지 않도록 설정
    // '변수명[0] = true'일 때 좌표계에서 양수 쪽으로, '변수명[1] = true'일 때 음수 쪽으로 이동
    for (int i = 0; i < 2; i++)
    {
        moveCameraX[i] = false;
        moveCameraY[i] = false;
        moveFocusX[i] = false;
        moveFocusY[i] = false;
        moveFocusZ[i] = false;
    }
    
    // 초기 화면에서의 카메라 및 초점 위치 설정
    cameraX = 0.0;
    cameraY = 3.5;
    focusX = 0.0;
    focusY = 0.0;
    focusZ = 0.0;
}

// 물체 그리기
void DrawGround() {
    glColor3f(0.5, 0.5, 0.5); // Teapot을 받치는 판의 색깔 지정
    glBegin(GL_POLYGON); // 다각형 그리기 시작(판 그리기)
    glVertex3f(-2.0, -0.71, 2.0); // 판(사각형)을 이루는 4개의 꼭지점의 위치 지정
    glVertex3f(2.0, -0.71, 2.0);
    glVertex3f(2.0, -0.71, -2.0);
    glVertex3f(-2.0, -0.71, -2.0);
    glEnd(); // 다각형 그리기 끝내기

    glColor3f(0.3, 0.3, 0.3); // 판 위의 격자무늬의 색깔 지정
    glBegin(GL_LINES); // 선 그리기 시작
    for (float x = -2.0; x <= 2.2; x += 0.2) { // 판 전체에 세로선 생성
        glVertex3f(x, -0.7, -2.0); // 선을 이루는 2개의 꼭지점의 위치 지정
        glVertex3f(x, -0.7, 2.0);
    }
    
    for (float z = -2.0; z <= 2.2; z += 0.2) { // 판 전체에 가로선 생성
        glVertex3f(-2.0, -0.7, z); // 선을 이루는 2개의 꼭지점의 위치 지정
        glVertex3f(2.0, -0.7, z);
    }
    glEnd(); // 선 그리기 끝내기
}

// Display Event 발생 시 호출되는 callback 함수
void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 색 버퍼와 깊이 버퍼를 삭제하여 화면에서 그림 지우기
    glMatrixMode(GL_MODELVIEW); // 모델뷰 행렬 선택
    glLoadIdentity(); // 모델뷰 행렬을 항등 행렬로 초기화

    gluLookAt(cameraX, cameraY, 3.5, focusX, focusY, focusZ, 0.0, 1.0, 0.0); // 시점 좌표계 정의 (카메라의 위치와 방향 설정)
    
    DrawGround(); // Teapot을 받치는 판 그리기

    glColor3f(1.0, 1.0, 0.0); // Teapot 색깔 지정
    glutWireTeapot(1.0); // Teapot 그리기

    glFlush(); // 현재 상태 변수를 기준으로 파이프라인 프로세스 실행
}

// Keyboard Event 발생 시 호출되는 callback 함수 (일반키 처리)
void MyKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a':
    case 'A': // 'a'나 'A'를 입력했을 시
        moveFocusX[0] = true; // 초점을 오른쪽으로 연속해서 움직임
        moveFocusX[1] = false;
        break;
    case 'f':
    case 'F': // 'f'나 'F'를 입력했을 시
        moveFocusX[0] = false;
        moveFocusX[1] = true; // 초점을 왼쪽으로 연속해서 움직임
        break;
    case 'r':
    case 'R': // 'r'이나 'R'를 입력했을 시
        moveFocusY[0] = true; // 초점을 위쪽으로 연속해서 움직임
        moveFocusY[1] = false;
        break;
    case 'v':
    case 'V': // 'v'나 'V'를 입력했을 시
        moveFocusY[0] = false;
        moveFocusY[1] = true; // 초점을 아래쪽으로 연속해서 움직임
        break;
    case 'z':
    case 'Z': // 'z'나 'Z'를 입력했을 시
        moveFocusZ[0] = true; // 초점을 앞으로 연속해서 움직임
        moveFocusZ[1] = false;
        break;
    case 't':
    case 'T': // 't'나 'T'를 입력했을 시
        moveFocusZ[0] = false;
        moveFocusZ[1] = true; // 초점을 뒤로 연속해서 움직임
        break;
    case 's':
    case 'S': // 's'나 'S'를 입력했을 시
        MyInit(); // 초기 화면으로 돌아감
        break;
    }
}

// Keyboard Event 발생 시 호출되는 callback 함수 (특수키 처리)
void MySpecialKey(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP: // ↑를 입력했을 시
        moveCameraY[0] = true; // 카메라의 위치가 위로 연속해서 움직임
        moveCameraY[1] = false;
        break;
    case GLUT_KEY_DOWN: // ↓를 입력했을 시
        moveCameraY[0] = false; 
        moveCameraY[1] = true; // 카메라의 위치가 밑으로 연속해서 움직임
        break;
    case GLUT_KEY_LEFT: // ←를 입력했을 시
        moveCameraX[0] = false;
        moveCameraX[1] = true; // 카메라의 위치가 왼쪽으로 연속해서 움직임
        break;
    case GLUT_KEY_RIGHT: // →를 입력했을 시
        moveCameraX[0] = true; // 카메라의 위치가 오른쪽으로 연속해서 움직임
        moveCameraX[1] = false;
        break;
    }
}

// 처리할 Event가 없을 때 호출되는 callback 함수
void MyIdle()
{
    // '변수명[0] = true'일 때 좌표계에서 양수 쪽으로, '변수명[1] = true'일 때 음수 쪽으로 이동
    if (moveCameraY[0]) // Keyboard Event로 해당 변수가 true로 바뀌었을 때
    {
        cameraY += 0.01; // 카메라를 위로 연속해서 움직임
    }
    else if (moveCameraY[1]) // Keyboard Event로 해당 변수가 true로 바뀌었을 때
    {
        cameraY -= 0.01; // 카메라를 아래로 연속해서 움직임
    }

    if (moveCameraX[0]) // Keyboard Event로 해당 변수가 true로 바뀌었을 때
    {
        cameraX += 0.01; // 카메라를 오른쪽으로 연속해서 움직임
    }
    else if (moveCameraX[1]) // Keyboard Event로 해당 변수가 true로 바뀌었을 때
    {
        cameraX -= 0.01; // 카메라를 왼쪽으로 연속해서 움직임
    }

    if (moveFocusX[0]) // Keyboard Event로 해당 변수가 true로 바뀌었을 때
    {
        focusX += 0.01; // 초점을 오른쪽으로 연속해서 움직임
    }
    else if (moveFocusX[1]) // Keyboard Event로 해당 변수가 true로 바뀌었을 때
    {
        focusX -= 0.01; // 초점을 왼쪽으로 연속해서 움직임
    }

    if (moveFocusY[0]) // Keyboard Event로 해당 변수가 true로 바뀌었을 때
    {
        focusY += 0.01; // 초점을 위쪽으로 연속해서 움직임
    }
    else if (moveFocusY[1]) // Keyboard Event로 해당 변수가 true로 바뀌었을 때
    {
        focusY -= 0.01; // 초점을 아래로 연속해서 움직임
    }

    if (moveFocusZ[0]) // Keyboard Event로 해당 변수가 true로 바뀌었을 때
    {
        focusZ += 0.01; // 초점을 앞으로 연속해서 움직임
    }
    else if (moveFocusZ[1]) // Keyboard Event로 해당 변수가 true로 바뀌었을 때
    {
        focusZ -= 0.01; // 초점을 뒤로 연속해서 움직임
    }

    glutPostRedisplay(); // Display Event를 강제로 발생시켜 화면에 그림을 다시 그리도록 함
}

// 화면을 다시 그려야 할 때 호출되는 callback 함수
void MyReshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); // 뷰폿 종횡비 설정
    glMatrixMode(GL_PROJECTION); // 투영 행렬 선택
    glLoadIdentity(); // 투영 행렬을 항등 행렬로 초기화
    gluPerspective(45.0, (GLdouble)w / (GLdouble)h, 0.0, 100); // 원근 투영 생성 (뷰폿과의 종횡비를 일치시켜 왜곡 현상 방지)
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Window OS와 세션 연결 & GLUT Library 초기화
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // Display Mode 설정 (트루컬러 모드 & 1개의 버퍼 사용)
    glutInitWindowSize(500, 500); // 윈도우의 크기 지정
    glutInitWindowPosition(0, 0); // 윈도우의 위치 지정
    glutCreateWindow("VCS (View Coordinate System)"); // 윈도우 생성 및 이름 지정
    MyInit(); // 초기 설정 적용
    glutDisplayFunc(MyDisplay); // Display Event가 발생할 때마다 MyDisplay를 호출하도록 등록
    glutReshapeFunc(MyReshape); // 화면을 새로 그려야 할 때마다 MyReshape을 호출하도록 등록
    glutKeyboardFunc(MyKeyboard); // 일반키에 대해 Keyboard Event가 발생할 때마다 MyKeyboard를 호출하도록 등록
    glutSpecialFunc(MySpecialKey); // 특수키에 대해 Keyboard Event가 발생할 때마다 MySpecialKey를 호출하도록 등록
    glutIdleFunc(MyIdle); // 처리할 Event가 없을 때 MyIdle을 호출하도록 등록
    glutMainLoop(); // GLUT Event 처리 Main Loop 진입
    return 0;
}