/*******************************************************************************************************/
/*                                           HW#2-1. GL Modeling                                       */
/*  작성자 : 이승현                                                             날짜 : 2021년 9월 29일 */
/*                                                                                                     */
/* 문제 정의 :                                                                                         */
/* 10 개의 2D Primitive(Points, Lines, LineStrip, LineLoop, TriangleFan, Triangles, TriangleStrip,     */
/* Polygon, Quads, QuadStrip)을 구현한다.                                                              */
/* 기능 :                                                                                              */
/* 1. glBegin 함수에 GL_POINTS를 인수로 입력받고, glGetFloatv 함수를 이용해 점의 크기에 대한           */
/*    상태 변수 값을 받아와 점의 크기를 조정하여 6개의 점을 그린다.                                    */
/* 2. glBegin 함수에 GL_LINES를 인수로 입력받아 3개의 선분을 그린다.                                   */
/* 3. glBegin 함수에 GL_LINESTRIP를 인수로 입력받아 5개의 선분이 서로 연결되도록 그린다.               */
/*    (첫 번째 점과 마지막 점은 서로 연결되지 않는다.)                                                 */
/* 4. glBegin 함수에 GL_LINELOOP를 인수로 입력받아 6개의 모든 점이 연결되도록 6개의 선분을 그린다.     */
/* 5. glBegin 함수에 GL_TRIANGLE_FAN를 인수로 입력받아 하나의 꼭지점을 공유하는 4개의 삼각형을 그린다. */
/* 6. glBegin 함수에 GL_TRIANGLES를 인수로 입력받아 각각 3개의 정점으로 그려지는 삼각형 2개를 그린다.  */
/* 7. glBegin 함수에 GL_TRIANGLE_STRIP를 인수로 입력받아 삼각형들이 모두 연결된 상태로 그린다.         */
/* 8. glBegin 함수에 GL_POLYGON를 인수로 입력받아 정육면체(다각형)를 그린다.                           */
/* 9. glBegin 함수에 GL_QUADS를 인수로 입력받아 각각 4개의 정점으로 그려지는 사각형 2개를 그린다.      */
/* 10. glBegin 함수에 GL_QUAD_STRIP를 인수로 입력받아 사각형들이 모두 연결된 상태로 그린다.            */
/*******************************************************************************************************/

// * MyDisplay 함수에서 2D Primitive들에 대한 주석이 있습니다.

#include <GL/glut.h>
#include <math.h>

void MyDisplay( ) {
    GLfloat Size[2];
     glClear(GL_COLOR_BUFFER_BIT); // 색 버퍼를 삭제하여 윈도우에서 그림 삭제
     glColor3f(0.5, 0.4, 0.3); // 색깔 설정

     // 1. Points 그리기 (점의 중앙에 정사각형 그리기)
     glGetFloatv(GL_POINT_SIZE, Size); // 상태 변수의 값을 받아옴 (점 크기의 최솟값과 최댓값을 Size에 저장)
     glPointSize(Size[0] * 5); // 점 크기를 최솟값의 5배 크기로 설정

     glBegin(GL_POINTS); // 지정한 Primitive 그리기
     glVertex3f(-0.5, -0.5 * sqrt(3), 0.0); // 점 위치 설정 (v0)
     glVertex3f(0.5, -0.5 * sqrt(3), 0.0); // v1
     glVertex3f(1.0, 0.0, 0.0); // v2
     glVertex3f(0.5, 0.5 * sqrt(3), 0.0); // v3
     glVertex3f(-0.5, 0.5 * sqrt(3), 0.0); // v4
     glVertex3f(-1.0, 0.0, 0.0); // v5
     glEnd(); // 그리기 끝내기

     /*
     // 2. Lines 그리기 (두 점을 연결하는 선분 그리기)
     glBegin(GL_LINES);
     glVertex3f(-0.5, -0.5 * sqrt(3), 0.0); // v0
     glVertex3f(0.5, -0.5 * sqrt(3), 0.0); // v1
     glVertex3f(1.0, 0.0, 0.0); // v2
     glVertex3f(0.5, 0.5 * sqrt(3), 0.0); // v3
     glVertex3f(-0.5, 0.5 * sqrt(3), 0.0); // v4
     glVertex3f(-1.0, 0.0, 0.0); // v5
     glEnd();
     */

     /*
     // 3. LineStrip 그리기 (선분들을 연결하여 그리기, 이때 첫 번째 점과 마지막 점은 연결되지 않음)
     glBegin(GL_LINE_STRIP);
     glVertex3f(-0.5, -0.5 * sqrt(3), 0.0); // v0
     glVertex3f(0.5, -0.5 * sqrt(3), 0.0); // v1
     glVertex3f(1.0, 0.0, 0.0); // v2
     glVertex3f(0.5, 0.5 * sqrt(3), 0.0); // v3
     glVertex3f(-0.5, 0.5 * sqrt(3), 0.0); // v4
     glVertex3f(-1.0, 0.0, 0.0); // v5
     glEnd();
     */

     /*
     // 4. LineLoop 그리기 (첫 번째 점과 마지막 점을 연결하여 모든 선분들이 연결되도록 그리기)
     glBegin(GL_LINE_LOOP);
     glVertex3f(-0.5, -0.5 * sqrt(3), 0.0); // v0
     glVertex3f(0.5, -0.5 * sqrt(3), 0.0); // v1
     glVertex3f(1.0, 0.0, 0.0); // v2
     glVertex3f(0.5, 0.5 * sqrt(3), 0.0); // v3
     glVertex3f(-0.5, 0.5 * sqrt(3), 0.0); // v4
     glVertex3f(-1.0, 0.0, 0.0); // v5
     glEnd();
     */

     /*
     // 5. TriangleFan 그리기 (하나의 꼭지점을 공유하는 일련의 삼각형들 그리기)
     glBegin(GL_TRIANGLE_FAN);
     glVertex3f(-1.0, -1.0, 0.0); // v0
     glVertex3f(1.0, -0.8, 0.0); // v1
     glVertex3f(0.8, -0.5, 0.0); // v2
     glVertex3f(0.7, -0.2, 0.0); // v3
     glVertex3f(0.2, 0.0, 0.0); // v4
     glVertex3f(0.0, 0.0, 0.0); // v5
     glEnd();
     */

     /*
     // 6. Triangles 그리기 (3개의 점으로 삼각형 하나 그리기)
     glBegin(GL_TRIANGLES);
     glVertex3f(-0.5, -0.5 * sqrt(3), 0.0); // v0
     glVertex3f(0.5, -0.5 * sqrt(3), 0.0); // v1
     glVertex3f(1.0, 0.8, 0.0); // v2
     glVertex3f(0.5, 0.5 * sqrt(3), 0.0); // v3
     glVertex3f(-0.5, 0.5 * sqrt(3), 0.0); // v4
     glVertex3f(-1.0, -0.3, 0.0); // v5
     glEnd();
     */

     /*
     // 7. TriangleStrip 그리기 (연결된 일련의 삼각형들을 그리기)
     glBegin(GL_TRIANGLE_STRIP);
     glVertex3f(1.5, -1.2, 0.0); // v0
     glVertex3f(1.0, 1.0, 0.0); // v1
     glVertex3f(0.8, -0.8, 0.0); // v2
     glVertex3f(0.5, 1.0, 0.0); // v3
     glVertex3f(0.2, -1.0, 0.0); // v4
     glVertex3f(-0.5, 0.8, 0.0); // v5
     glVertex3f(-1.0, -1.1, 0.0); // v6
     glEnd();
     */

     /*
     // 8. Polygon 그리기 (임의의 개수의 꼭짓점들을 가진 다각형 그리기, 여기서는 정육각형 그리기)
     glBegin(GL_POLYGON);
     glVertex3f(-0.5, -0.5 * sqrt(3), 0.0); // v0
     glVertex3f(0.5, -0.5 * sqrt(3), 0.0); // v1
     glVertex3f(1.0, 0.0, 0.0); // v2
     glVertex3f(0.5, 0.5 * sqrt(3), 0.0); // v3
     glVertex3f(-0.5, 0.5 * sqrt(3), 0.0); // v4
     glVertex3f(-1.0, 0.0, 0.0); // v5
     glEnd();
     */

     /*
     // 9. Quads 그리기 (4개의 점으로 사각형 하나 그리기)
     glBegin(GL_QUADS);
     glVertex3f(1.0, -1.0, 0.0); // v0
     glVertex3f(1.3, 0.2, 0.0);  // v1
     glVertex3f(0.5, 0.4, 0.0); // v2
     glVertex3f(0.0, -1.0, 0.0); // v3
     glVertex3f(-0.2, 0.0, 0.0); // v4
     glVertex3f(-0.1, 1.2, 0.0); // v5
     glVertex3f(-0.7, 1.0, 0.0); // v6
     glVertex3f(-0.9, 0.4, 0.0); // v7
     glEnd();
     */

     /*
     // 10. QuadStrip 그리기 (연결된 일련의 사각형들 그리기)
     glBegin(GL_QUAD_STRIP);
     glVertex3f(1.0, -1.0, 0.0); // v0
     glVertex3f(1.3, 0.2, 0.0);  // v1
     glVertex3f(0.0, -1.0, 0.0); // v2
     glVertex3f(0.5, 0.4, 0.0); // v3
     glVertex3f(-0.2, 0.0, 0.0); // v4
     glVertex3f(-0.1, 1.2, 0.0); // v5
     glVertex3f(-0.9, 0.4, 0.0); // v6
     glVertex3f(-0.7, 1.0, 0.0); // v7
     glEnd();
     */

     glFlush(); // 아직 실행되지 않은 명령들 모두 실행 (현재 상태 변수를 기준으로 파이프라인 프로세스 실행)
}

int main(int argc, char** argv) {
     glutInit(&argc, argv); // 윈도우 시스템의 세션을 처리 & GLUT 라이브러리 초기화
     glutInitDisplayMode(GLUT_RGBA); // 디스플레이 표면의 주요 특징 결정 (트루 컬러 모드(기본값))
     glutInitWindowSize(500, 500); // 윈도우 창 크기 설정
     glutInitWindowPosition(0, 0); // 윈도우 창 위치 설정
     glutCreateWindow("2D Primitives"); // 윈도우 창 이름 설정
     glClearColor(1.0, 1.0, 1.0, 1.0); // 윈도우 창 배경화면 색깔 설정 (흰색)
     glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0); // 현재 매트릭스와 직교 행렬을 곱함
     glutDisplayFunc(MyDisplay); // 디스플레이 이벤트에 대한 MyDisplay 콜백함수 등록

     glutMainLoop( ); // GLUT Event 처리 Loop 진입 (함수가 실행되면서 발생하는 메세지를 처리하도록 메세지 처리함수 호출)
     return 0;
}