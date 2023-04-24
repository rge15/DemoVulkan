#pragma once
#include <utilities/Includes/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>
#include <utilities/Engine/engineTypeAlias.hpp>

class BaseRenderRSC
{
protected:
    inline static
    RenderRSCId RSCCounter_ { 0 };

    RenderRSCId rscId_ { RSCCounter_++ };

public:
    RenderRSCId getRenderRSCId(){ return rscId_; };
};