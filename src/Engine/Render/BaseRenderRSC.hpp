#pragma once
#include <utilities/Includes/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>
#include <utilities/Engine/engineTypeAlias.hpp>

/**
 * @brief Base Render resources class for all Vulkan Render Resources
 * such as Render Pass or Render Layout   
 */
class BaseRenderRSC
{
protected:
    //! Common render rsc counter
    inline static
    RenderRSCId RSCCounter_ { 0 };

    //! Render Rsc Id
    RenderRSCId rscId_ { RSCCounter_++ };

public:
    /**
     * @brief Get the Render RSC Id object
     * 
     * @return RenderRSCId 
     */
    RenderRSCId getRenderRscId(){ return rscId_; };
};