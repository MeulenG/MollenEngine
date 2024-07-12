#include "first_app.hpp"

namespace mve {
	void FirstApp::run() {
		while (!Window.shouldClose()) {
			glfwPollEvents();
		}
	}
}