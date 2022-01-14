/*******************************************************************************************************/
/*                                 HW#6 : glViewport()을 통한 뷰폿변환                                 */
/*  작성자 : 이승현                                                             날짜 : 2021년 11월 9일 */
/*                                                                                                     */
/* 문제 정의 :                                                                                         */
/* 2개 이상의 물체를 한 뷰폿에 그리고, 한 윈도우에 4개의 뷰폿을 띄워 서로 비교한다.                    */
/* 기능 :                                                                                              */
/* 1. 우상단과 좌하단의 뷰폿에 Teapot과 Sphere 두 물체를 그린다.                                       */
/* 2. 우상단의 뷰폿은 원근투영으로 설정한다.                                                           */
/* 3. 좌하단의 뷰폿은 평행투영으로 설정한다.                                                           */
/* 4. Mouse Callback을 통해 마우스가 해당 뷰폿이 있는 위치에서 좌클릭으로 화면을 드래그하면            */ 
/*    카메라가 마우스의 움직임에 따라 x, y축에서 이동한다.                                             */
/* 5. Mouse Callback을 통해 마우스가 해당 뷰폿이 있는 위치에서 앞뒤로 스크롤하면                       */
/*    카메라가 마우스의 움직임에 따라 z축에서 이동한다. (이동 범위에 제한 설정)                        */
/* 6. 각각의 뷰폿 내 Teapot의 위치는 뷰폿의 중심으로, Sphere은 Teapot의 뒤로 고정한다.                 */
/* 7. ReShape Callback과 Display Callback을 통해 윈도우 크기 변환에 따른 물체 왜곡을 방지한다.         */ 
/*******************************************************************************************************/

#include <GL/glut.h>

GLfloat Width, Height;
GLfloat size[2];
GLfloat camera1[3], camera2[3];
GLint mousePos[2];

void MyInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // 흰색으로 화면 지우기

    glGetFloatv(GL_LINE_WIDTH_RANGE, size); // 선 두께의 범위를 size에 저장

    camera1[0] = 0;
    camera1[1] = 0;
    camera1[2] = 1.5;

    camera2[0] = 5.0;
    camera2[1] = 5.0;
    camera2[2] = 5.0;
}

void DrawScene() {
    glColor3f(0.0, 0.0, 0.0); // 좌표의 색 지정
    glPushMatrix(); // 행렬 스택에 현재 변환 행렬 저장
    glLineWidth(size[0] * 5); // 선 두께 지정 (최솟값의 5배)
    glBegin(GL_LINES); // x축 그리기
    glVertex3f(-2.0, 0.0, 0.0); // 좌표 지정
    glVertex3f(2.0, 0.0, 0.0); // 좌표 지정
    glEnd(); // 그리기 끝내기
    glBegin(GL_LINES); // y축 그리기
    glVertex3f(0.0, -2.0, 0.0); // 좌표 지정
    glVertex3f(0.0, 2.0, 0.0); // 좌표 지정
    glEnd(); // 그리기 끝내기
    glBegin(GL_LINES); // z축 그리기
    glVertex3f(0.0, 0.0, -2.0); // 좌표 지정
    glVertex3f(0.0, 0.0, 2.0); // 좌표 지정
    glEnd(); // 그리기 끝내기
    glPopMatrix(); // 행렬 스택에서 top에 있는 행렬 삭제

    glColor3f(0.3, 0.3, 0.7); // Teapot의 색깔 지정
    glPushMatrix(); // 행렬 스택에 현재 변환 행렬 저장
    glTranslatef(0.0, 0.0, 0.0); // Teapot 위치 조정
    glutWireTeapot(1.0); // Teapot을 1.0의 크기로 그리기
    glPopMatrix(); // 행렬 스택에서 top에 있는 행렬 삭제

    glColor3f(0.5, 0.1, 0.0);
    glPushMatrix();
    glTranslatef(-1.0, 0.0, -1.0);
    glutWireSphere(0.6, 20, 20);
    glPopMatrix();
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 색 버퍼, 깊이 버퍼를 삭제하여 화면에서 그림 지우기
    glColor3f(1.0, 1.0, 1.0); // 색깔 지정
    
    glMatrixMode(GL_PROJECTION); // 투영 행렬 선택
    glLoadIdentity(); // 투영 행렬을 항등 행렬로 초기화

    glOrtho(-2.0, 2.0, -2.0 * Height / Width, 2.0 * Height / Width, 0.5, 5.0); // 직교 투영 생성
    glMatrixMode(GL_MODELVIEW); // 모델뷰 행렬 선택
    glLoadIdentity(); // 모델뷰 행렬을 항등 행렬로 초기화

    glViewport(0, 0, Width / 2, Height / 2); // 좌측 하단에 뷰폿 생성
    glPushMatrix(); // 행렬 스택에 삽입
    gluLookAt(camera1[0], camera1[1], camera1[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    DrawScene();
    glPopMatrix();
    glViewport(Width / 2, 0, Width / 2, Height / 2); // 우측 하단에 뷰폿 생성
    glPushMatrix();
    gluLookAt(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glPopMatrix();
    glViewport(0, Height / 2, Width / 2, Height / 2); // 좌측 상단에 뷰폿 생성
    glPushMatrix();
    gluLookAt(0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
    glPopMatrix();
    glViewport(Width / 2, Height / 2, Width / 2, Height / 2); // 우측 상단에 뷰폿 생성
    glMatrixMode(GL_PROJECTION); // 투영 행렬 선택
    glPushMatrix();
    glLoadIdentity(); // 투영 행렬을 항등 행렬로 초기화
    gluPerspective(30, Width / Height, 3.0, 50.0); // 원근 투영 생성
    glMatrixMode(GL_MODELVIEW); // 모델뷰 행렬 선택
    glPushMatrix();
    gluLookAt(camera2[0], camera2[1], camera2[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    DrawScene();
    glPopMatrix();
    glMatrixMode(GL_PROJECTION); // 투영 행렬 선택
    glPopMatrix();
    glutSwapBuffers(); // 전면 버퍼와 백 버퍼를 교체하여 화면에 그림 그리기
}

void MyReshape(int w, int h) {
    Width = w;
    Height = h;
}

void MyMouseMove1_XY(GLint x, GLint y)
{
    GLint deltaX = x - mousePos[0];
    GLint deltaY = y - mousePos[1];
    camera1[0] = deltaX / 5;
    camera1[1] = deltaY / 5;
    glutPostRedisplay();
}

void MyMouseMove2_XY(GLint x, GLint y)
{
    GLint deltaX = x - mousePos[0];
    GLint deltaY = y - mousePos[1];
    camera2[0] = deltaX / 5;
    camera2[1] = deltaY / 5;
    glutPostRedisplay();
}

void MyMouseMove(GLint x, GLint y)
{
    mousePos[0] = x;
    mousePos[1] = y;
}

void MyMouseClick(GLint button, GLint state, GLint x, GLint y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (x < Width / 2 && y > Height / 2)
            glutMotionFunc(MyMouseMove1_XY);
        else if (x > Width / 2 && y < Height / 2)
            glutMotionFunc(MyMouseMove2_XY);
    }
    else if (button == 3) // 위로 스크롤
    {
        if (x < Width / 2 && y > Height / 2 && camera1[2] >= -6.0)
        {
            camera1[2] -= 0.25;
            glutPostRedisplay();
        }
        else if (x > Width / 2 && y < Height / 2 && camera2[2] >= -15.0)
        {
            camera2[2] -= 0.25;
            glutPostRedisplay();
        }
    }
    else if (button == 4) // 아래로 스크롤
    {
        if (x < Width / 2 && y > Height / 2 && camera1[2] <= 6.0)
        {
            camera1[2] += 0.25;
            glutPostRedisplay();
        }
        else if (x > Width / 2 && y < Height / 2 && camera2[2] <= 15.0)
        {
            camera2[2] += 0.25;
            glutPostRedisplay();
        }
    }
}

int main(int argc, char** argv) {
    Width = 500;
    Height = 500;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Viewpory Partition");
    MyInit();
    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);
    glutPassiveMotionFunc(MyMouseMove);
    glutMouseFunc(MyMouseClick);
    glutMainLoop();
    return 0;
}
