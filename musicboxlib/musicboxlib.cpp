// musicboxlib.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "musicboxlib.h"
#include "packet.h"

// This is the constructor of a class that has been exported.
// see musicboxlib.h for the class definition
CMusicBox::CMusicBox()
{
    return;
}

void CMusicBox::Connect(const char *uri){
    try {
        handler = musicbox_client_handler_ptr (new musicbox_client_handler(this));

        endpoint = client_handler_ptr( new client(handler));

        string uristr(uri);

        con = endpoint->get_connection(uristr);

        endpoint->connect(con);

        main_thread = new boost::thread (boost::bind(&client::run, endpoint, false));
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}


extern "C" {
    CMusicBoxHandler MUSICBOXLIB_API NewMusicBox(void){
        return new CMusicBox();
    }

    void MUSICBOXLIB_API MusicBoxConnect(CMusicBoxHandler handler, const PChar url){
        return handler->Connect(url);
    }

    void MUSICBOXLIB_API MusicBoxSetCallback(CMusicBoxHandler handler, enum CallbackType type, mb_callback cb){
        switch (type)
        {
        case OnConnect:
            handler->onConnect = cb;
            break;
        case OnError:
            handler->onError = cb;
            break;
        case OnClose:
            handler->onClose = cb;
            break;
        default:
            break;
        }
    }

    void MUSICBOXLIB_API MusicBoxSetOnMessage(CMusicBoxHandler handler, mb_onmessage cb){
        handler->onMessage = cb;
    }

    void MUSICBOXLIB_API MusicBoxClose(CMusicBoxHandler handler){
        if (handler->handler){
            handler->handler->close();
        }
        else{
            std::cerr << "Error: No Connection?!";
        }
    }

    void MUSICBOXLIB_API MusicBoxSend(CMusicBoxHandler handler, musicbox::Action action, PChar msg){
        if (handler->handler){
            handler->handler->send(action, string(msg));
        }
        else{
            std::cerr << "Error: No Connection?!";
        }
    }
}