#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "renderer.h"
#include "vertex-buffer.h"
#include "vertex-buffer-layout.h"
#include "vertex-array.h"
#include "index-buffer.h"
#include "shader.h"

void GLFW_error(int error, const char* description)
{
    fputs(description, stderr);
}

int main()
{
	GLFWwindow* window;

    glfwSetErrorCallback(GLFW_error);

	// initialize glfw library
	if(!glfwInit())
	{
		std::cout << "unable to initialize glfw" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(1024, 768, "Hello World", nullptr, nullptr);
	if(!window)
	{
		
		std::cout << "unable to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// make the window's context current
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// initialize glew library
	if(glewInit() != GLEW_OK)
	{
		std::cout << "Unable to initialize glew library" << std::endl;
		glfwTerminate();
		return -1;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

    float positions[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray vertexArray;
    VertexBuffer vertexBuffer(positions, 4 * 2 * sizeof(float));
    VertexBufferLayout layout;
    layout.push<float>(2);
    vertexArray.addBuffer(vertexBuffer, layout);

    IndexBuffer indexBuffer(indices, 6);

    Shader shader("res/shader/basic.shader");
    float r = 0.0f;
    float increment = 0.01f;

    shader.unbind();
    vertexArray.unbind();
    vertexBuffer.unbind();
    indexBuffer.unbind();

    // loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // render here
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        shader.bind();
        shader.setUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
        vertexArray.bind();
        indexBuffer.bind();

        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        if (r > 1.0f)
            increment = -0.01f;
        else if (r < 0.0f)
            increment = 0.01f;

        r += increment;

        // swap front and back buffers
        glfwSwapBuffers(window);

        // poll for and process events
        glfwPollEvents();
    }

	glfwTerminate();
	return 0;
}
