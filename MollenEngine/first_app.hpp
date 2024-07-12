#ifndef FIRST_APP_H
#define FIRST_APP_H

#include "window.hpp"

namespace mve {
	class FirstApp {
	public:
		static constexpr size_t WIDTH = 800;
		static constexpr size_t HEIGHT = 600;

		void run();

	private:
		Window Window{ WIDTH, HEIGHT, "Hello Vulkan!" };
	};
}

#endif