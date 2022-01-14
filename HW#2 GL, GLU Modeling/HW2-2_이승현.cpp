/*******************************************************************************************************/
/*                                           HW#2-2. GLU Modeling                                      */
/*  작성자 : 이승현                                                             날짜 : 2021년 9월 29일 */
/*                                                                                                     */
/* 문제 정의 :                                                                                         */
/*  Display List를 사용하여 4개의 3D Primitive(Sphere, Cylinder, Disk, PartialDisk)를 구현하고,        */
/*  각각의 Primitive에 다양한 Draw Style을 적용한다.                                                   */
/* 기능 :                                                                                              */
/* 1. 3D Primitive를 구현할 때 Display List를 사용하여 프로그램의 속도를 향상시킨다.                   */
/* 2. gluSphere 함수를 사용하여 반지름이 1.5인 구를 그린다.                                            */
/* 3. gluCylinder 함수를 사용하여 밑면이 1.5이고 높이가 2.0인 원기둥을 그린다.                         */
/* 4. gluDisk 함수를 사용하여 안쪽 원의 반지름이 0.5, 바깥쪽 원의 반지름이 1.5인 disk를 그린다.        */
/* 5. gluPartialDisk 함수를 사용하여 4번 Disk의 90도만큼에 해당하는 partial disk를 그린다.             */
/* 6. 각각의 도형에 대하여 다양한 DrawStyle(GLU_FILL, GLU_LINE, GLU_SILHOUETTE, GLU_POINT)을 지정한다. */
/* 7. MyInit 함수에서 빛과 표면에 대한 설정을 한다.                                                    */
/* 8. MyReshape 함수에서 뷰폿과 가시부피의 종횡비를 일치시켜 왜곡 문제를 해결한다.                     */
/*******************************************************************************************************/

// * main 함수에서 My___DisplayList의 주석을 지우면 각각 다른 도형을 화면에서 볼 수 있습니다.

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

int MyListID[4]; // Display List 생성 (Display List는 정수 ID에 의해 식별됨)

GLUquadricObj* sphere = gluNewQuadric(); // Sphere를 생성하기 위해 새로운 Quadric Object 생성
GLUquadricObj* cylinder = gluNewQuadric(); // Cylinder를 생성하기 위해 새로운 Quadric Object 생성
GLUquadricObj* disk = gluNewQuadric(); // Disk를 생성하기 위해 새로운 Quadric Object 생성
GLUquadricObj* partialDisk = gluNewQuadric(); // Partial disk를 생성하기 위해 새로운 Quadric Object 생성

// 초기 설정 (4개의 Display List 생성 및 조명 설정) 
void MyInit()
{
    MyListID[0] = glGenLists(4); // 4개의 Display List ID를 만들어 첫 번째 아이디를 MyListID[0]에 저장
    for (int i = 1; i < 4; i++)
        MyListID[i] = MyListID[i - 1] + 1; // 나머지 3개의 Display List ID를 MyListID 배열에 저장

    GLfloat mat_ambient[] = { 1.0, 0.0, 0.0, 1.0 }; // RGBA 반사를 지정
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 }; // RGBA 반사를 지정
    GLfloat mat_shininess[] = { 50.0 }; // 값이 클 수록 표면이 매끄러워짐 (0 ~ 128)
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 }; // 조명 위치 지정
    GLfloat model_ambient[] = { 1.0, 0.0, 0.0, 1.0 }; // 전체 화면의 RGBA 강도 지정

    glClearColor(0.0, 0.0, 0.0, 0.0); // 화면을 검은색으로 지우기

    // glMaterialfv : 재질 정의 (GL_FRONT를 인수로 받아 겉면에 대한 재질 정의)
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient); // GL_AMBIENT : 주변광의 세기 (특정 방향 없이 모든 점에서 균일한 광도)
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); // GL_SPECULAR : 반사광의 세기 (거울면처럼 반질반질한 느낌 표현)
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess); // GL_SHININESS : 선명도 (표면의 매끄러운 정도)
    glLightfv(GL_LIGHT0, GL_POSITION, light_position); // 조명의 위치 설정
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient); // 조명 모델 매개 변수 설정 (조명 효과 모델을 설정하여 주변광 사용)

    glEnable(GL_LIGHTING); // 조명 사용
    glEnable(GL_LIGHT0); // 조명 중 0 번 조명 사용
    glEnable(GL_DEPTH_TEST); // 은면 제거 (시점에서 더 가까운 면만 보이도록 함)
}

// Sphere에 대한 Display List 생성하고, GLU_FILL으로 그리기
void MySphereDisplayList()
{
    glNewList(MyListID[0], GL_COMPILE); // sphere에 대한 Display List 생성
   
    glMatrixMode(GL_MODELVIEW); // 모델뷰 행렬 선택
    glLoadIdentity(); // 모델뷰 행렬을 항등 행렬로 초기화

    glEnable(GL_LIGHTING); // 조명 사용

    glShadeModel(GL_SMOOTH); // 표면을 부드럽게 만듦 (기본값)

    gluQuadricTexture(sphere, GL_FALSE); // Texture 좌표를 사용할 것인지 설정 (인수 : Texture 좌표를 생성하지 않음(Default))

    gluQuadricNormals(sphere, GLU_SMOOTH); // 법선 벡터 제어
    gluQuadricOrientation(sphere, GLU_OUTSIDE); // 법선 벡터 내부 및 외부와 같은 방향 지정

    gluQuadricDrawStyle(sphere, GLU_FILL); // Solid 형태의 Modeling으로 Draw Style 지정
    //gluQuadricDrawStyle(sphere, GLU_LINE); // Wire-frame 형태의 Modeling으로 Draw Style 지정
    //gluQuadricDrawStyle(sphere, GLU_SILHOUETTE); // 외부 모서리 Modeling으로 Draw Style 지정
    //gluQuadricDrawStyle(sphere, GLU_POINT); // 점들의 집합으로 만든 Modeling으로 Draw Style 지정
    
    gluSphere(sphere, 1.5, 50, 50); // 반지름이 1.5인 구를 그림
    glEndList(); // Display List의 끝 표시
}

// Cylinder에 대한 Display List 생성하고, GLU_LINE으로 그리기
void MyCylinderDisplayList()
{
    glNewList(MyListID[1], GL_COMPILE); // cylinder에 대한 Display List 생성

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_LIGHTING);

    glShadeModel(GL_SMOOTH);
    
    gluQuadricTexture(cylinder, GL_FALSE);

    gluQuadricNormals(cylinder, GLU_SMOOTH);
    gluQuadricOrientation(cylinder, GLU_OUTSIDE);

    //gluQuadricDrawStyle(cylinder, GLU_FILL);
    gluQuadricDrawStyle(cylinder, GLU_LINE);
    //gluQuadricDrawStyle(cylinder, GLU_SILHOUETTE);
    //gluQuadricDrawStyle(cylinder, GLU_POINT);

    glRotatef(60.0f, 0.5f, 1.0f, 0.0f); // 실린더의 모습을 입체적으로 보기 위해 회전시킴
    gluCylinder(cylinder, 1.5, 1.5, 2.0, 50, 50); // 밑면의 반지름이 1.5이고 길이가 2.0인 원기둥을 그림

    glEndList(); // Display List의 끝
}

// Disk에 대한 Display List 생성하고, GLU_SILHOUETTE으로 그리기
void MyDiskDisplayList()
{
    glNewList(MyListID[2], GL_COMPILE); // disk에 대한 Display List 생성

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_LIGHTING);

    glShadeModel(GL_SMOOTH);
    
    gluQuadricTexture(disk, GL_FALSE);

    gluQuadricNormals(disk, GLU_SMOOTH);
    gluQuadricOrientation(disk, GLU_OUTSIDE);

    //gluQuadricDrawStyle(disk, GLU_FILL);
    //gluQuadricDrawStyle(disk, GLU_LINE); 
    gluQuadricDrawStyle(disk, GLU_SILHOUETTE);
    //gluQuadricDrawStyle(disk, GLU_POINT);

    glRotatef(60.0f, 0.5f, 1.0f, 0.0f);
    gluDisk(disk, 0.5, 1.5, 20, 20); // 안쪽 원의 반지름이 0.5이고 바깥쪽 원의 반지름이 1.5인 Disk 그림
    glEndList(); // Display List의 끝
}

// Partial Disk에 대한 Display List 생성하고, GLU_POINT로 그리기
void MyPartialDiskDisplayList()
{
    glNewList(MyListID[3], GL_COMPILE); // partialDisk에 대한 Display List 생성

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_LIGHTING);

    glShadeModel(GL_SMOOTH);
    
    gluQuadricTexture(partialDisk, GL_FALSE);

    gluQuadricNormals(partialDisk, GLU_SMOOTH);
    gluQuadricOrientation(partialDisk, GLU_OUTSIDE);

    //gluQuadricDrawStyle(partialDisk, GLU_FILL);
    //gluQuadricDrawStyle(partialDisk, GLU_LINE); 
    //gluQuadricDrawStyle(partialDisk, GLU_SILHOUETTE);
    gluQuadricDrawStyle(partialDisk, GLU_POINT);

    gluPartialDisk(partialDisk, 0.5, 1.5, 50, 13, 0, 90); // 안쪽 원의 반지름이 0.5이고 바깥쪽 원의 반지름이 1.5인 Disk의 90도만큼 그림

    glEndList(); // Display List의 끝
}

// Display event가 일어날 때 화면을 지우고 Display List를 실행하는 함수
void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 색 버퍼, 깊이 버퍼 삭제하여 화면 지우기

    glCallList(MyListID[0]); // 첫 번째 Display List 실행
    glCallList(MyListID[1]); // 두 번째 Display List 실행
    glCallList(MyListID[2]); // 세 번째 Display List 실행
    glCallList(MyListID[3]); // 네 번째 Display List 실행
    glFlush(); // 아직 실행되지 않은 명령을 모두 실행 (현재 상태변수를 기준으로 파이프라인 프로세스 실행)
}

// 뷰폿과 가시부피의 종횡비를 맞춰서 왜곡 문제 해결하기
void MyReshape(int NewWidth, int NewHeight)
{
    glViewport(0, 0, NewWidth, NewHeight);

    glMatrixMode(GL_PROJECTION); // 투영 행렬 선택
    glLoadIdentity(); // 투영 행렬을 항등 행렬로 초기화

    // 가시부피를 뷰폿의 종횡비에 맞추기
    glOrtho(-3, 3, -3 * (GLfloat)NewHeight / (GLfloat)NewWidth, 3 * (GLfloat)NewHeight / (GLfloat)NewWidth, -10.0, 10.0);
}

int main(int argc, char** argv) {
    glutInit(&argc,argv); // Window OS와 연결하고 GLUT Library 초기화
    glutInitDisplayMode(GLUT_RGB); // Display Mode 설정
    glutInitWindowSize(300, 300); // 창 크기 설정
    glutInitWindowPosition(0, 0); // 창 위치 설정
    glutCreateWindow("3D Primitives Using Display List"); // 창 이름 설정
    glClearColor(1.0, 1.0, 1.0, 1.0); // 화면을 흰색으로 지우기
    MyInit(); // 초기 설정
    glutDisplayFunc(MyDisplay); // Display Even가 발생할 때마다 MyDisplay 호출하도록 등록
    glutReshapeFunc(MyReshape); // 화면을 새로 그려야 할 때마다 MyReshape 호출하도록 등록

    MySphereDisplayList(); // sphere에 대한 Display List 생성
    //MyCylinderDisplayList(); // cylinder에 대한 Display List 생성
    //MyDiskDisplayList(); // disk에 대한 Display List 생성
    //MyPartialDiskDisplayList(); // partialDisk에 대한 Display List 생성

    glutMainLoop(); // GLUT Event 처리 Loop 진입
    return 0;
}
