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
	class MollenEngine {
	public:
		static constexpr size_t WIDTH = 800;
		static constexpr size_t HEIGHT = 600;

		MollenEngine();
		~MollenEngine();

		MollenEngine(const MollenEngine&) = delete;
		MollenEngine& operator=(const MollenEngine&) = delete;

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
		VkBuffer vertexBuffer;
	};
}

#endif