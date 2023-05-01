#pragma once
#include <utilities/Includes/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>

/**
 * @brief Class that contains all the basic Render Pipeline Configuration
 */
struct GraphicPipelineConfig
{

    //! Pipeline Dynamic COnfig states
    private:
        Vector<VkDynamicState> dynamicStates_ {
            VK_DYNAMIC_STATE_VIEWPORT , VK_DYNAMIC_STATE_SCISSOR
        };

        //! Color Blend Attachment
        VkPipelineColorBlendAttachmentState colorBlendAttach_ {};
    public:

        //! Dynamic States info Config
        VkPipelineDynamicStateCreateInfo dynamicInfo_ {};

        //! Vertex Input Config
        VkPipelineVertexInputStateCreateInfo vertexInputInfo_ {};

        //! Input Assembly Config
        VkPipelineInputAssemblyStateCreateInfo assemblyInfo_ {};

        //! Viewport & Scissor Config
        VkPipelineViewportStateCreateInfo viewportScissorInfo_ {};

        //! Raster Config
        VkPipelineRasterizationStateCreateInfo rasterInfo_ {};

        //! Multisample Config
        VkPipelineMultisampleStateCreateInfo msaaInfo_ {};

        //! Color Blend Config
        VkPipelineColorBlendStateCreateInfo colorInfo_  {};

    public:
        /**
         * @brief Construct a new Graphic Pipeline Config object
         * and inits all the config states
         */
        GraphicPipelineConfig() noexcept;

        /**
         * @brief Destroy the Graphic Pipeline Config
         */
        ~GraphicPipelineConfig() = default;

    private:
        /**
         * @brief Fill the config info of the Dynamic States
         */
        void
        configDynamicStates() noexcept;

        /**
         * @brief Fill the config info of the Vertex Input
         */
        void
        configVertexInput() noexcept;

        /**
         * @brief Fill the config info of the Input Assembly
         */
        void
        configInputAssembly() noexcept;

        /**
         * @brief Fill the config info of the Viewpor & Scissor
         */
        void
        configViewportScissor() noexcept;

        /**
         * @brief Fill the config info of the Raster
         */
        void
        configRasterizer() noexcept;

        /**
         * @brief Fill the config info of the Multisample
         */
        void
        configMultisample() noexcept;

        /**
         * @brief Fill the config info of the Color Blending
         */
        void
        configColorBlending() noexcept;

};
