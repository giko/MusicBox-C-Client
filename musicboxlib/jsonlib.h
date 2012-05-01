#include "rapidjson/document.h"

#ifdef MUSICBOXLIB_EXPORTS
#define MUSICBOXLIB_API __declspec(dllexport)
#else
#define MUSICBOXLIB_API __declspec(dllimport)
#endif

typedef rapidjson::Value *PNode;
typedef rapidjson::Document *PRoot;
typedef char *PChar;

extern "C" {
    PNode MUSICBOXLIB_API Json_getChildFromRoot(const PRoot node, const PChar name);
    PNode MUSICBOXLIB_API Json_getChild(const PNode node, const PChar name);
    PChar MUSICBOXLIB_API Json_getString(const PNode node);
}