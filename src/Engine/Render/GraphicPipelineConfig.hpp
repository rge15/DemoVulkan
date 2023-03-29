#pragma once
#include <utilities/Includes/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>

struct GraphicPipelineConfig
{
    private:
        Vector<VkDynamicState> dynamicStates_ {
            VK_DYNAMIC_STATE_VIEWPORT , VK_DYNAMIC_STATE_SCISSOR
        };

        VkPipelineColorBlendAttachmentState colorBlendAttach_ {};

    public:

        VkPipelineDynamicStateCreateInfo dynamicInfo_ {};

        VkPipelineVertexInputStateCreateInfo vertexInputInfo_ {};

        VkPipelineInputAssemblyStateCreateInfo assemblyInfo_ {};

        VkPipelineViewportStateCreateInfo viewportScissorInfo_ {};

        VkPipelineRasterizationStateCreateInfo rasterInfo_ {};

        VkPipelineMultisampleStateCreateInfo msaaInfo_ {};

        VkPipelineColorBlendStateCreateInfo colorInfo_  {};

    public:
        GraphicPipelineConfig() noexcept;
        ~GraphicPipelineConfig() = default;

    private:
        void
        configDynamicStates() noexcept;

        void
        configVertexInput() noexcept;

        void
        configInputAssembly() noexcept;

        void
        configViewportScissor() noexcept;

        void
        configRasterizer() noexcept;

        void
        configMultisample() noexcept;

        void
        configColorBlending() noexcept;

};
