#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>

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
    float smallRadius = 0.1f * scaleFactor; // 작은 원의 반지름 계산
    int numSegments = 360; // 세그먼트 수 (원이 될수록 많아질수록 더 부드러운 원이 됨)

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

    // 작은 원의 채우기 색상 (RGB: 255, 230, 153)
    glColor3ub(255, 230, 153); // 밝은 색으로 작은 원을 채움
    float smallCenterX = -0.2f * scaleFactor; // 큰 원의 중심에서 살짝 왼쪽으로 이동
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

    // 작은 원의 외곽선 색상 (RGB: 200, 150, 100)
    glColor3ub(200, 150, 100); // 조금 더 진한 색으로 작은 원의 외곽선을 그립니다
    glBegin(GL_LINE_LOOP); // 외곽선을 그리기 위해 GL_LINE_LOOP을 사용합니다.
    for (int i = 0; i < numSegments; ++i)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(numSegments); // 각도 계산
        float x = smallRadius * cosf(theta) + smallCenterX; // x 좌표
        float y = smallRadius * sinf(theta) + smallCenterY; // y 좌표
        glVertex2f(x, y); // 정점 추가
    }
    glEnd();
}







;


int main(void)
{
	//glfw라이브러리 초기화
	if (!glfwInit())
		return -1;

	GLFWwindow* window;
	window = glfwCreateWindow(1280, 768, "MuSoeunEngine", NULL, NULL);

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