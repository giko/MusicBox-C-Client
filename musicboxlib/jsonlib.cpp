#pragma once

#include "jsonlib.h"
#include <string>

extern "C" {
    PNode MUSICBOXLIB_API Json_getChildFromRoot(const PRoot node, const PChar name){
        return &((*node)[name]);
    }

    PNode MUSICBOXLIB_API Json_getChild(const PNode node, const PChar name){
        return &((*node)[name]);
    }
    PChar MUSICBOXLIB_API Json_getString(const PNode node){
        return (PChar) (node->GetString());
    }
}