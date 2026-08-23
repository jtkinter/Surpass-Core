#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>

// 读取glsl源文件
std::string readShaderFile(const std::string& filepath)
{
	std::ifstream file(filepath);
	if (!file.is_open())
	{
		std::cerr << "错误：无法打开着色器文件: " << filepath << std::endl;
		return "";
	}

	std::stringstream ss;
	ss << file.rdbuf();
	return ss.str();
}

// 创造并编译着色器
unsigned int compileShader(unsigned int type, const char* source)
{
	unsigned int shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, nullptr);

	int success;
	char infoLog[512];
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cerr << (type == GL_VERTEX_SHADER ? "顶点" : "片段") << "着色器编译失败: " << infoLog << std::endl;
	}
	return shader;
}

// 创建着色器程序
unsigned int createShaderProgram(const char* vertexSrc, const char* fragmentSrc)
{
	unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexSrc);			// 编译顶点着色器
	unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSrc);	// 编译片段着色器
	
	// 链接着色器程序
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "着色器程序链接失败: " << infoLog << std::endl;
	}

	// 清理着色器对象
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

int main()
{
	if (!glfwInit())
	{
		std::cerr << "GLFW 初始化失败" << std::endl;
		return -1;
	}

	// 配置GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 创建窗口
	GLFWwindow* window = glfwCreateWindow(800, 600, "Surpass Engine", NULL, NULL);
	if (!window)
	{
		std::cerr << "窗口创建失败" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// 初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "GLAD 初始化失败" << std::endl;
		return -1;
	}

	// 设置顶点
	float vertices[] = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f,  0.5f
	};

	// 设置渲染索引
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	// 创建顶点数据对象
	unsigned int attribute;
	glGenVertexArrays(1, &attribute);
	glBindVertexArray(attribute);

	// 创建顶点缓冲对象
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 创建索引数据对象
	unsigned int element;
	glGenBuffers(1, &element);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 设置数据格式
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 解绑
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	std::string vertexShaderSource = readShaderFile("res/shader/vertex.vert");
	std::string fragmentShaderSource = readShaderFile("res/shader/fragment.frag");
	if (vertexShaderSource.empty() || fragmentShaderSource.empty())
		return -1;

	const char* vertexShaderSrc = vertexShaderSource.c_str();
	const char* fragmentShaderSrc = fragmentShaderSource.c_str();

	unsigned int shaderProgram = createShaderProgram(vertexShaderSrc, fragmentShaderSrc);

	// 获取uniform位置，缓存起来避免每帧查询
	int greenLocation = glGetUniformLocation(shaderProgram, "uGreen");

	// 循环
	while (!glfwWindowShouldClose(window))
	{
		float time = (float)glfwGetTime();
		float green = (sin(time) + 1.0f) / 2.0f;

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(attribute);

		// 绘制图像
		glUseProgram(shaderProgram);
		glUniform1f(greenLocation, green);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &attribute);
	glDeleteBuffers(1, &buffer);
	glDeleteBuffers(1, &element);
	glDeleteProgram(shaderProgram);
	glfwTerminate();

	return 0;
}