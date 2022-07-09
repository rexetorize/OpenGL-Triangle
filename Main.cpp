#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.6f, 0.02f, 7.0f);\n"
"}\n\0";

int main(void)
{

	//we first initialize glfw
	glfwInit();

	//glfw doesnt know what ver of open gl we are using so we gotta pass it a parameter of the version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//now we create a window
	GLFWwindow* window = glfwCreateWindow(800, 800, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {//error checking for the window
		std::cout << "Failed to create window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	 
	//we need to tell glfw that we want to use this window. We want to make this window a part of the current ctx
	glfwMakeContextCurrent(window);

	//loading GLAD functions
	gladLoadGL();


	glViewport(0, 0, 800, 800);

	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
	};

	//to initialize and store out vertex shaders
	GLuint vertexSahder = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexSahder, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexSahder);

	//to initialize and store out fragment shaders
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	
	//creating a shader prog
	GLuint shaderProg = glCreateProgram();
	glAttachShader(shaderProg, vertexSahder);
	glAttachShader(shaderProg, fragmentShader);
	glLinkProgram(shaderProg);

	glDeleteShader(vertexSahder);
	glDeleteShader(fragmentShader);

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);



	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//configure the vertex attrib to let OPENGL to know how to read the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	//Enable the vertex attrib
	glEnableVertexAttribArray(0);



	//well if the window is not closed then we handle other poll events
	while (!glfwWindowShouldClose(window))
	{	//we are swapping the front buffer with the backbuffer
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProg);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteShader(shaderProg);
	//onclose destroy window
	glfwDestroyWindow(window);

	glfwTerminate();
}