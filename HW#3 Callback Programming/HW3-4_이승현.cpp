/*******************************************************************************************************/
/*                                     HW#3-4. Menu Callback 응용                                      */
/*  작성자 : 이승현                                                             날짜 : 2021년 10월 6일 */
/*                                                                                                     */
/* 문제 정의 :                                                                                         */
/* Menu Callback을 이용하여 메뉴를 등록하고, 3D Primitive에 대한 설정을 하도록 한다.                   */
/* 기능 :                                                                                              */
/* 1. 마우스 우클릭으로 Draw Sphere, Draw Torus, Draw Teapot, Change Color, Exit의 메뉴를 구성한다.    */
/* 2. 메뉴를 통해 Sphere, Torus, Teapot을 3D로 그린다.                                                 */
/* 3. 메뉴를 통해 각 Primitive의 색을 빨간색, 초록색, 파란색 중 하나로 바꿀 수 있도록 한다.            */
/* 4. 메뉴를 통해 각 Primitive의 크기를 Small, Large 중 택할 수 있도록 한다.                           */
/*******************************************************************************************************/


#include <gl/glut.h>

GLboolean IsSphere = true, IsTorus = false, IsTeapot = false; // 어떠한 3D Primitive를 그릴 것인지에 대한 변수
GLboolean IsSmall = true, IsLarge = false; // 어떠한 크기로 Primitive를 그릴 것인지에 대한 변수
GLfloat red = 0.5, green = 0.5, blue = 0.5; // 어떠한 색으로 Primitive를 설정할 것인지에 대한 변수

// Display Event를 처리하는 함수
void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT); // 색 버퍼를 삭제하여 화면에서 그림 지우기
    glColor3f(red, green, blue); // 초기 색깔은 회색으로 지정

    if ((IsSphere) && (IsSmall))
        glutWireSphere(0.5, 30, 30); // 작은 크기인 와이어 형태의 구를 그림
    else if ((IsSphere) && (IsLarge))
        glutWireSphere(0.7, 30, 30); // 큰 크기인 와이어 형태의 구를 그림
    else if ((IsTorus) && (IsSmall))
        glutWireTorus(0.1, 0.3, 40, 20); // 작은 크기인 와이어 형태의 토러스를 그림
    else if ((IsTorus) && (IsLarge))
        glutWireTorus(0.2, 0.5, 40, 20); // 큰 크기인 와이어 형태의 토러스를 그림
    else if ((IsTeapot) && (IsSmall))
        glutWireTeapot(0.3); // 작은 크기인 와이어 형태의 주전자를 그림
    else if ((IsTeapot) && (IsLarge))
        glutWireTeapot(0.6); // 큰 크기인 와이어 형태의 주전자를 그림
    glFlush();
}

// 메인 메뉴를 설정함
void MyMainMenu(int entryID) {
    switch (entryID)
    {
    case 1: // 첫 번째('Draw Sphere')를 선택하면 구를 그림
        IsSphere = true;
        IsTorus = false;
        IsTeapot = false;
        break;
    case 2: // 두 번째('Draw Torus')를 선택하면 토러스를 그림
        IsSphere = false;
        IsTorus = true;
        IsTeapot = false;
        break;
    case 3: // 세 번째('Draw Teapot')를 선택하면 주전자를 그림
        IsSphere = false;
        IsTorus = false;
        IsTeapot = true;
        break;
    case 4: // 마지막('Exit')을 선택하면 프로그램 종료
        exit(0);
    }

    glutPostRedisplay(); // Display Event 강제로 발생시키기
}

// 사이즈에 관련된 메뉴를 설정함
void MySizeMenu(int entryID) {
    switch (entryID)
    {
    case 1: // 첫 번째("Small")를 선택하면 3D Primitive를 작게 그림
        IsSmall = true;
        IsLarge = false;
        break;
    case 2: // 두 번째("Large")를 선택하면 3D Primitive를 크게 그림
        IsSmall = false;
        IsLarge = true;
        break;
    }

    glutPostRedisplay(); // Display Event 강제로 발생시키기
}

// 색깔에 대한 메뉴를 설정함
void MyColorMenu(int entryID)
{
    switch (entryID)
    {
    case 1: // 첫 번째("Red")를 선택하면 3D Primitive를 빨간색으로 설정
        red = 1.0;
        green = 0.0;
        blue = 0.0;
        break;
    case 2: // 두 번째("Green")를 선택하면 3D Primitive를 초록색으로 설정
        red = 0.0;
        green = 1.0;
        blue = 0.0;
        break;
    case 3: // 세 번째("Blue")를 선택하면 3D Primitive를 파란색으로 설정
        red = 0.0;
        green = 0.0;
        blue = 1.0;
        break;
    }

    glutPostRedisplay(); // Display Event 강제로 발생시키기
}

// 초기 설정
void MyInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // 화면을 하얀색으로 지우기
    glMatrixMode(GL_PROJECTION); // 투영 행렬 선택
    glLoadIdentity(); // 투영 행렬을 항등 행렬로 초기화

    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // 직교 투영을 만듦

    GLint MySizeID = glutCreateMenu(MySizeMenu); // 크기 설정에 대한 메뉴 콜백 함수를 등록하여 메뉴 아이디 값 리턴
    glutAddMenuEntry("Small", 1); // Primitive를 작게 그리는 메뉴 설정
    glutAddMenuEntry("Large", 2); // Primitive를 크게 그리는 메뉴 설정

    GLint MyColorID = glutCreateMenu(MyColorMenu); // 색깔 설정에 대한 메뉴 콜백 함수를 등록하여 메뉴 아이디 값 리턴
    glutAddMenuEntry("Red", 1); // Primitive를 빨간색으로 그리는 메뉴 설정
    glutAddMenuEntry("Green", 2); // Primitive를 초록색으로 그리는 메뉴 설정
    glutAddMenuEntry("Blue", 3); // Primitive를 파란색으로 그리는 메뉴 설정

    GLint MyMainMenuID = glutCreateMenu(MyMainMenu); // 주 메뉴에 대한 메뉴 콜백 함수를 등록하여 메뉴 아이디 값 리턴
    glutAddMenuEntry("Draw Sphere", 1); // Sphere를 그리는 메뉴 설정
    glutAddMenuEntry("Draw Torus", 2); // Torus를 그리는 메뉴 설정
    glutAddMenuEntry("Draw Teapot", 3); // Teapot를 그리는 메뉴 설정
    glutAddSubMenu("Size", MySizeID); // Size에 대한 서브 메뉴 설정
    glutAddSubMenu("Color", MyColorID); // Color에 대한 서브 메뉴 설정
    glutAddMenuEntry("Exit", 4); // 프로그램 종료 메뉴 설정
    glutAttachMenu(GLUT_RIGHT_BUTTON); // 마우스의 오른쪽 버튼에 메뉴 할당
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Window OS 세션과 연결하고 GLUT Library 초기화
    glutInitDisplayMode(GLUT_RGB); // Display Mode 설정
    glutInitWindowSize(500, 500); // 창 크기 설정
    glutInitWindowPosition(0, 0); // 창 위치 설정
    glutCreateWindow("Menu Callback"); // 창 이름 설정과 함께 창 생성
    MyInit(); // 초기 설정 적용
    glutDisplayFunc(MyDisplay); // Display Event가 일어날 때마다 MyDisplay 호출하도록 등록

    glutMainLoop(); // GLUT Event 처리 Loop 진입
    return 0;
}