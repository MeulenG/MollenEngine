#ifndef WINDOW_H
#define WINDOW_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace mve {
	class Window {

	public:
		Window(size_t w, size_t h, std::string name);
		~Window();

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		bool shouldClose() { return glfwWindowShouldClose(window); }

	private:
		void initWindow();

		const size_t width;
		const size_t height;

		std::string windowName;
		GLFWwindow* window;
	};
}

#endif