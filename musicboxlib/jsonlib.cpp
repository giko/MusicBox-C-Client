#pragma once

#include "jsonlib.h"
#include <string>

extern "C" {
    PNode MUSICBOXLIB_API Json_getChildFromRoot(PRoot node, PChar name){
        return &((*node)[name]);
    }

    PNode MUSICBOXLIB_API Json_getChild(PNode node, PChar name){
        return &((*node)[name]);
    }
    PChar MUSICBOXLIB_API Json_getString(PNode node){
        return (PChar) (node->GetString());
    }
}