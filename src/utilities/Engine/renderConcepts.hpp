#pragma once
#include <type_traits>
#include <Engine/Render/BaseRenderPass.hpp>
#include <Engine/Render/BasePipelineLayout.hpp>

template<typename T>
concept RenderPassObj = std::is_base_of< BaseRenderPass ,T>::value;

template<typename T>
concept PipeLayoutObj = std::is_base_of< BasePipelineLayout ,T>::value;
