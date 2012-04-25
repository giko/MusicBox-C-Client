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

#include "musicboxlib.h"
#include "roles\client.hpp"
#include "websocketpp.hpp"

using std::string;
using websocketpp::client;

typedef void (*mb_callback) (const char *msg);

class CMusicBox {
	class musicbox_client_handler : public client::handler {
	public:
		musicbox_client_handler(CMusicBox *mb);
		void on_open(connection_ptr con);
		void on_close(connection_ptr con);
		void on_message(connection_ptr con, message_ptr msg);
		void send(const std::string &msg);
		void close();
		void on_fail(connection_ptr con);

	private:
		CMusicBox *musicbox_handler;
		connection_ptr connection;
	};

	typedef boost::shared_ptr<musicbox_client_handler> musicbox_client_handler_ptr;
public:
	CMusicBox(void);
	bool Connect(const char *url);
	mb_callback onConnect;
	mb_callback onMessage;
	mb_callback onError;
	mb_callback onClose;
	//TODO: make it private!
	musicbox_client_handler_ptr handler;
};

typedef CMusicBox *CMusicBoxHandler;
typedef char *PChar;

enum CallbackType{
	OnConnect, OnMessage, OnError, OnClose
};

#define EXPORTCALL __declspec(dllexport) _stdcall

extern "C" {
	CMusicBoxHandler MUSICBOXLIB_API  NewMusicBox(void);
	PChar MUSICBOXLIB_API  MusicBoxConnect(CMusicBoxHandler handler, const PChar url);
	void MUSICBOXLIB_API  MusicBoxSetCallback(CMusicBoxHandler handler, enum CallbackType type, mb_callback cb);
	void MUSICBOXLIB_API MusicBoxClose(CMusicBoxHandler handler);
	void MUSICBOXLIB_API MusicBoxSend(CMusicBoxHandler handler, PChar msg);
}