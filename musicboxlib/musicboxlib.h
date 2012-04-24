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

typedef void (*mb_callback) (const string &msg);

class MUSICBOXLIB_API CMusicBox {
public:
	CMusicBox(void);
	bool Connect(const char *url);
	mb_callback onConnect;
	mb_callback onMessage;
	mb_callback onError;
	mb_callback onClose;
};

typedef CMusicBox *CMusicBoxHandler;

enum CallbackType{
	OnConnect, OnMessage, OnError, OnClose
};

extern "C" {
	CMusicBoxHandler MUSICBOXLIB_API NewMusicBox(void);
	bool MUSICBOXLIB_API MusicBoxConnect(CMusicBoxHandler handler, const char *url);
	void MUSICBOXLIB_API MusicBoxSetCallback(CMusicBoxHandler handler, enum CallbackType type, mb_callback cb);
}