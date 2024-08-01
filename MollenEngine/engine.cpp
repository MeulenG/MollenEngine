#include "engine.hpp"
#include "device.hpp"

//std
#include <stdexcept>
#include <array>


namespace mve {
	MollenEngine::MollenEngine() {
		createPipelineLayout();
		createPipeline();
		createCommandBuffers();
	}

	MollenEngine::~MollenEngine() {
		vkDestroyPipelineLayout(device.device(), pipeLineLayout, nullptr);
	}

	void MollenEngine::run() {

		while (!Window.shouldClose()) {
			glfwPollEvents();
			drawFrame();
		}

		vkDeviceWaitIdle(device.device());
	}
	void MollenEngine::createPipelineLayout() {
		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pSetLayouts = nullptr;
		pipelineLayoutInfo.pushConstantRangeCount = 0;
		pipelineLayoutInfo.pPushConstantRanges = nullptr;
		if (vkCreatePipelineLayout(device.device(), &pipelineLayoutInfo, nullptr, &pipeLineLayout) != VK_SUCCESS) 
		{
			throw std::runtime_error("failed to create pipeline layout!");
		}
	}

	void MollenEngine::createPipeline() {
		auto pipelineConfig = Pipeline::defaultPiplineConfigInfo(swapChain.width(), swapChain.height());
		pipelineConfig.renderPass = swapChain.getRenderPass();
		pipelineConfig.pipelineLayout = pipeLineLayout;
		pipeLine = std::make_unique<Pipeline>(
			device,
			"simple_shader.vert.spv",
			"simple_shader.frag.spv",
			pipelineConfig);
	}

	void MollenEngine::createCommandBuffers() {
		commandBuffers.resize(swapChain.imageCount());

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = device.getCommandPool();
		allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

		if (vkAllocateCommandBuffers(device.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to allocate command buffers!");
		}

		for (size_t i = 0; i < commandBuffers.size(); i++)
		{
			VkCommandBufferBeginInfo beginInfo{};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

			if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS)
			{
				throw std::runtime_error("failed to begin recording command buffer!");
			}

			VkRenderPassBeginInfo renderPassInfo{};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = swapChain.getRenderPass();
			renderPassInfo.framebuffer = swapChain.getFrameBuffer(i);

			renderPassInfo.renderArea.offset = { 0, 0 };
			renderPassInfo.renderArea.extent = swapChain.getSwapChainExtent();

			std::array<VkClearValue, 2> clearValues{};
			clearValues[0].color = { 0.1f, 0.1f, 0.1f, 0.1f };
			clearValues[1].depthStencil = { 1.0f, 0 };
			renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
			renderPassInfo.pClearValues = clearValues.data();

			vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

			pipeLine->bind(commandBuffers[i]);
			vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

			vkCmdEndRenderPass(commandBuffers[i]);
			if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS)
			{
				throw std::runtime_error("failed to end command buffer!");
			}
		}
	}

	void MollenEngine::drawFrame() {
		uint32_t imageIndex;
		auto result = swapChain.acquireNextImage(&imageIndex);

		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
		{
			throw std::runtime_error("failed to acquire swap chain image!");
		}

		result = swapChain.submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);
		if (result != VK_SUCCESS)
		{
			throw std::runtime_error("failed to present swap chain image");
		}
	}
}

