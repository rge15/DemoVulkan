#pragma once
#include <utilities/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>

struct GraphicPipelineConfig
{
    private:
        Vector<VkDynamicState> _dynamicStates {
            VK_DYNAMIC_STATE_VIEWPORT , VK_DYNAMIC_STATE_SCISSOR
        };

        VkPipelineColorBlendAttachmentState _colorBlendAttach {};

    public:

        VkPipelineDynamicStateCreateInfo _dynamicInfo {};

        VkPipelineVertexInputStateCreateInfo _vertexInputInfo {};

        VkPipelineInputAssemblyStateCreateInfo _assemblyInfo {};

        VkPipelineViewportStateCreateInfo _viewportScissorInfo {};

        VkPipelineRasterizationStateCreateInfo _rasterInfo {};

        VkPipelineMultisampleStateCreateInfo _msaaInfo {};

        VkPipelineColorBlendStateCreateInfo _colorInfo  {};

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
