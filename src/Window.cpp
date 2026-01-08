#include "Window.h"
#include <iostream>
#include "stb/stb_image.h"

void framebuffer_resize_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

namespace KE
{
	int Window::createWindow(int width, int height, std::string_view title)
	{
		if (!glfwInit())
		{
			std::cerr << "Failed to create GLFW\n";
			glfwTerminate();
		}

		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_RESIZABLE, true);

		m_handle = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);

		if (!m_handle)
		{
			std::cerr << "Failed to create window\n";
			glfwTerminate();
			return -1;
		}

		glfwMakeContextCurrent(m_handle);

		glewExperimental = GL_TRUE;

		if (glewInit() != GLEW_OK)
		{
			std::cerr << "Failed to create glew\n";
			return -1;
		}

		glfwSetFramebufferSizeCallback(m_handle, framebuffer_resize_callback);

		return 0;
	}

	void Window::destroyWindow()
	{
		if (m_handle)
		{
			glfwDestroyWindow(m_handle);
			m_handle = nullptr;
		}
	}

	Window::Window(int width, int height, std::string_view title) : m_width(width), m_height(height), m_title(title)
	{
		if (createWindow(width, height, title) != -1)
		{
			std::cout << "Created the Window correctly\n";
		}
	}


	Window::~Window()
	{
		destroyWindow();
	}

	bool Window::shouldClose() const
	{
		return glfwWindowShouldClose(m_handle);
	}

	void Window::swapBuffers() const
	{
		glfwSwapBuffers(m_handle);
	}

	void Window::pollEvents() const
	{
		glfwPollEvents();
	}

	void Window::clear(float r, float g, float b, float a) const
	{
		glClearColor(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::setWindowIcon(std::string_view path)
	{
		int width = 0, height = 0, nrChannels = 0;

		stbi_uc* data = stbi_load(path.data(), &width, &height, &nrChannels, 0);

		if (!data)
		{
			std::cerr << "Failed to load window icon: " << path << "\n";
		}

		GLFWimage icon;

		icon.width = width;
		icon.height = height;
		icon.pixels = data;

		glfwSetWindowIcon(m_handle, 1, &icon);

		stbi_image_free(data);
	}
}
