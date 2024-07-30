#ifndef FIRST_APP_H
#define FIRST_APP_H

#include "window.hpp"
#include "pipeline.hpp"
#include "swap_chain.hpp"
#include "device.hpp"

// std
#include <memory>
#include <vector>

namespace mve {
	class FirstApp {
	public:
		static constexpr size_t WIDTH = 800;
		static constexpr size_t HEIGHT = 600;

		FirstApp();
		~FirstApp();

		FirstApp(const FirstApp&) = delete;
		FirstApp& operator=(const FirstApp&) = delete;

		void run();

	private:
		void createPipelineLayout();
		void createPipeline();
		void createCommandBuffers();
		void drawFrame();

		Window Window{ WIDTH, HEIGHT, "Hello Vulkan!" };
		Device device{ Window };
		SwapChain swapChain{ device , Window.getExtent() };
		std::unique_ptr<Pipeline> pipeLine;
		VkPipelineLayout pipeLineLayout;
		std::vector<VkCommandBuffer> commandBuffers;
	};
}

#endif