#pragma once
#include <utilities/typeAliases.hpp>
#include <Engine/Render/BasicRenderPass.hpp> 
#include <Engine/Renderer.hpp>
#include <Engine/Render/BasicPipelineLayout.hpp>
#include <Engine/Render/ImagePipelineLayout.hpp>
#include <utilities/Engine/renderConcepts.hpp>

//! Engine Renderer Type 
using RendererType = Renderer<BasicPipelineLayout, ImagePipelineLayout>;