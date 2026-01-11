#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <string_view>


namespace KE
{
	class Window
	{
	private:
		GLFWwindow* m_handle = nullptr;
		int m_width = 800, m_height = 600;
		std::string m_title = "";

		int createWindow(int width, int height, std::string_view title);
		void destroyWindow();
	public:
		Window(int width, int height, std::string_view title);
		~Window() noexcept;

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(Window&&) = delete;

		bool shouldClose() const;
		void swapBuffers() const;

		void clear(float r, float g, float b, float a) const;

		void pollEvents() const;

		void setWindowIcon(std::string_view path);

		int getWidth() const { return m_width; }
		int getHeight() const { return m_height; }
		const std::string& getTitle() const { return m_title; }
	};
}
