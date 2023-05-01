#pragma once
#include <type_traits>
#include <Engine/Render/BaseRenderPass.hpp>
#include <Engine/Render/BasePipelineLayout.hpp>

//! Concept TypeTrait for checking if it's a RenderPass obj
template<typename T>
concept RenderPassObj = std::is_base_of< BaseRenderPass ,T>::value;

//! Concept TypeTrait for checking if it's a PipelineLayout obj 
template<typename T>
concept PipeLayoutObj = std::is_base_of< BasePipelineLayout ,T>::value;
