// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MUSICBOXLIB_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
#pragma once

#ifdef MUSICBOXLIB_EXPORTS
#define MUSICBOXLIB_API __declspec(dllexport)
#else
#define MUSICBOXLIB_API __declspec(dllimport)
#endif

#include <string>

using std::string;

class MUSICBOXLIB_API CMusicBox {
public:
    CMusicBox(void);
    bool Connect(string url);
    void (*onConnect) (const string &msg);
    void (*onMessage) (const string &msg);
    void (*onError) (const string &msg);
    void (*onClose) (const string &msg);
};