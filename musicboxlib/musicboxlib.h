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

#include "roles\client.hpp"
#include "websocketpp.hpp"
#include "packet.h"
#include "jsonlib.h"

using std::string;
using websocketpp::client;

typedef boost::shared_ptr<client> client_handler_ptr;
typedef void (*mb_callback) (const char *msg);
typedef void (*mb_onmessage) (const PRoot);
typedef boost::thread *PThread;
typedef char *PChar;

class CMusicBox {
    class musicbox_client_handler : public client::handler {
    public:
        musicbox_client_handler(CMusicBox *mb);
        void on_open(connection_ptr con);
        void on_close(connection_ptr con);
        void on_message(connection_ptr con, message_ptr msg);
        void on_fail(connection_ptr con);
        void send(const std::string &msg);
        void send(const musicbox::Packet *packet);
        void send(const musicbox::Action action, const std::string &msg);
        void close();
        
    private:
        CMusicBox *musicbox_handler;
        connection_ptr connection;
    };

    typedef boost::shared_ptr<musicbox_client_handler> musicbox_client_handler_ptr;
public:
    CMusicBox(void);
    void Connect(const char *url);
    mb_callback onConnect;
    mb_onmessage onMessage;
    mb_callback onError;
    mb_callback onClose;
    //TODO: make it private!
    musicbox_client_handler_ptr handler;
    PThread main_thread;
private:
    client_handler_ptr endpoint;
    client::connection_ptr con;
};

typedef CMusicBox *CMusicBoxHandler;

enum CallbackType{
    OnConnect, OnMessage, OnError, OnClose
};

extern "C" {
    CMusicBoxHandler MUSICBOXLIB_API  NewMusicBox(void);
    void MUSICBOXLIB_API  MusicBoxConnect(CMusicBoxHandler handler, const PChar url);
    void MUSICBOXLIB_API  MusicBoxSetCallback(CMusicBoxHandler handler, enum CallbackType type, mb_callback cb);
    void MUSICBOXLIB_API  MusicBoxSetOnMessage(CMusicBoxHandler handler, mb_onmessage cb);
    void MUSICBOXLIB_API MusicBoxClose(CMusicBoxHandler handler);
    void MUSICBOXLIB_API MusicBoxSend(CMusicBoxHandler handler, musicbox::Action action, PChar msg);
}