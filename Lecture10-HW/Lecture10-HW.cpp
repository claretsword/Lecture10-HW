#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

float moveFactor = 0.0f;
float scaleFactor = 1.0f;

void errorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    {
        moveFactor += 0.01f;
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    {
        scaleFactor += 0.1f;
    }
}

void render()
{
    float bigRadius = 0.5f * scaleFactor; // 큰 원의 반지름 계산
    float smallRadius = 0.15f * scaleFactor; // 첫 번째 작은 원의 반지름 계산
    float extraSmallRadius = 0.15f * scaleFactor; // 세로로 축소된 작은 원의 반지름 계산
    int numSegments = 360; // 세그먼트 수 (세그먼트가 많을수록 원이 부드럽게 그려집니다)

    // 경과 시간에 기반한 회전 각도 계산
    float time = glfwGetTime();
    float rotationAngle = (360.0f / 30.0f) * fmod(time, 30.0f); // 30초 주기로 360도 회전

    // 변환 적용: 자전
    glPushMatrix();
    glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);

    // 큰 원의 채우기 색상 (RGB: 255, 217, 102)
    glColor3ub(255, 217, 102); // 밝은 주황색으로 큰 원을 채움
    glBegin(GL_POLYGON); // 큰 원을 채우기 위해 GL_POLYGON을 사용합니다.
    for (int i = 0; i < numSegments; ++i)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(numSegments); // 각도 계산
        float x = bigRadius * cosf(theta); // x 좌표
        float y = bigRadius * sinf(theta); // y 좌표
        glVertex2f(x, y); // 정점 추가
    }
    glEnd();

    // 큰 원의 외곽선 색상 (RGB: 255, 140, 0)
    glColor3ub(255, 140, 0); // 진한 주황색으로 큰 원의 외곽선을 그립니다
    glBegin(GL_LINE_LOOP); // 외곽선을 그리기 위해 GL_LINE_LOOP을 사용합니다.
    for (int i = 0; i < numSegments; ++i)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(numSegments); // 각도 계산
        float x = bigRadius * cosf(theta); // x 좌표
        float y = bigRadius * sinf(theta); // y 좌표
        glVertex2f(x, y); // 정점 추가
    }
    glEnd();

    // 첫 번째 작은 원의 채우기 색상 (RGB: 255, 230, 153)
    glColor3ub(255, 230, 153); // 밝은 색으로 작은 원을 채움
    float smallCenterX = -0.25f * scaleFactor; // 큰 원의 중심에서 더 왼쪽으로 이동
    float smallCenterY = 0.0f; // y 좌표는 중심과 동일
    glBegin(GL_POLYGON); // 작은 원을 채우기 위해 GL_POLYGON을 사용합니다.
    for (int i = 0; i < numSegments; ++i)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(numSegments); // 각도 계산
        float x = smallRadius * cosf(theta) + smallCenterX; // x 좌표
        float y = smallRadius * sinf(theta) + smallCenterY; // y 좌표
        glVertex2f(x, y); // 정점 추가
    }
    glEnd();

    
    glBegin(GL_LINE_LOOP); // 외곽선을 그리기 위해 GL_LINE_LOOP을 사용합니다.
    for (int i = 0; i < numSegments; ++i)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(numSegments); // 각도 계산
        float x = smallRadius * cosf(theta) + smallCenterX; // x 좌표
        float y = smallRadius * sinf(theta) + smallCenterY; // y 좌표
        glVertex2f(x, y); // 정점 추가
    }
    glEnd();

    
    // 추가 작은 원의 채우기 색상 (RGB: 255, 192, 0)
    glColor3ub(255, 192, 0); // 밝은 색으로 추가 작은 원을 채움
    float extraSmallCenterX = 0.2f * scaleFactor; // 큰 원의 중심에서 오른쪽으로 이동
    float extraSmallCenterY = -0.25f * scaleFactor; // 큰 원의 중심에서 더 아래로 이동

    // 변환 적용: 이동 -> 회전 -> 스케일링
    glPushMatrix();
    glTranslatef(extraSmallCenterX, extraSmallCenterY, 0.0f); // 위치 이동
    glRotatef(45.0f, 0.0f, 0.0f, 1.0f); // 45도 회전
    glScalef(1.0f, 0.25f, 1.0f); // 세로로 축소

    glBegin(GL_POLYGON); // 추가 작은 원을 채우기 위해 GL_POLYGON을 사용합니다.
    for (int i = 0; i < numSegments; ++i)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(numSegments); // 각도 계산
        float x = extraSmallRadius * cosf(theta); // x 좌표
        float y = extraSmallRadius * sinf(theta); // y 좌표
        glVertex2f(x, y); // 정점 추가
    }
    glEnd();

    
   
    // 조금 더 진한 색으로 추가 작은 원의 외곽선을 그립니다
    glBegin(GL_LINE_LOOP); // 외곽선을 그리기 위해 GL_LINE_LOOP을 사용합니다.
    for (int i = 0; i < numSegments; ++i)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(numSegments); // 각도 계산
        float x = extraSmallRadius * cosf(theta); // x 좌표
        float y = extraSmallRadius * sinf(theta); // y 좌표
        glVertex2f(x, y); // 정점 추가
    }
    glEnd();

    glPopMatrix(); // 변환 행렬 복원

    glPopMatrix(); // 자전 변환 복원
    

    // 지구의 중심 좌표 및 크기 설정
    float earthCenterX = 0.8f * scaleFactor; // 태양에서 오른쪽으로 이동
    float earthCenterY = 0.0f * scaleFactor; // 태양에서 조금 위로 이동
    float earthSize = 0.2f * scaleFactor; // 정사각형의 크기 설정

    // 변환 적용: 이동
    glPushMatrix();
    glTranslatef(earthCenterX, earthCenterY, 0.0f);

    // 정사각형의 선 색상 (검은색)
    glColor3ub(0, 0, 0); // 검은색으로 선을 그립니다.

    // 정사각형의 내부 색상 (RGB: 91, 155, 213)
    // 밝은 색으로 정사각형을 채웁니다.
    glBegin(GL_POLYGON);
    glColor3ub(91, 155, 213);
    // 정사각형의 네 꼭지점을 추가합니다.
    glVertex2f(-earthSize / 2, -earthSize / 2); // 왼쪽 아래
    glVertex2f(earthSize / 2, -earthSize / 2); // 오른쪽 아래
    glVertex2f(earthSize / 2, earthSize / 2); // 오른쪽 위
    glVertex2f(-earthSize / 2, earthSize / 2); // 왼쪽 위
    glEnd();

    // 정사각형의 외곽선 색상 (검은색)
    glColor3ub(0, 0, 0); // 검은색으로 외곽선을 그립니다.
    glBegin(GL_LINE_LOOP);
    // 정사각형의 네 꼭지점을 추가합니다.
    glVertex2f(-earthSize / 2, -earthSize / 2); // 왼쪽 아래
    glVertex2f(earthSize / 2, -earthSize / 2); // 오른쪽 아래
    glVertex2f(earthSize / 2, earthSize / 2); // 오른쪽 위
    glVertex2f(-earthSize / 2, earthSize / 2); // 왼쪽 위
    glEnd();

    glPopMatrix(); // 변환 행렬 복원
}

int main(void)
{
    // glfw 라이브러리 초기화
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(1600, 800, "MuSoeunEngine", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        render();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
