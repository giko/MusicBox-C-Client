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

bool CMusicBox::Connect(const char *uri){
	try {
		musicbox_client_handler_ptr handlerex(new musicbox_client_handler(this));

		//I hope, god doesn't seen this
		handler = handlerex;

		client::connection_ptr con;
		client endpoint(handler);

		string uristr(uri);

		con = endpoint.get_connection(uristr);

		endpoint.connect(con);

		boost::thread t(boost::bind(&client::run, &endpoint, false));

		char line[512];
		while (std::cin.getline(line, 512)) {
			handler->send(line);
		}
		t.join();
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
		return false;
	}

	return true;
}


extern "C" {
	CMusicBoxHandler MUSICBOXLIB_API NewMusicBox(void){
		return new CMusicBox();
	}

	PChar MUSICBOXLIB_API MusicBoxConnect(CMusicBoxHandler handler, const PChar url){
		boost::thread t(boost::bind(&CMusicBox::Connect, *handler, url));

		return "running";
	}

	void MUSICBOXLIB_API MusicBoxSetCallback(CMusicBoxHandler handler, enum CallbackType type, mb_callback cb){
		switch (type)
		{
		case OnConnect:
			handler->onConnect = cb;
			break;
		case OnMessage:
			handler->onMessage = cb;
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

	void MUSICBOXLIB_API MusicBoxClose(CMusicBoxHandler handler){
		if (handler->handler){
			handler->handler->close();
		}
	}

	void MUSICBOXLIB_API MusicBoxSend(CMusicBoxHandler handler, PChar msg){
		if (handler->handler){
			handler->handler->send(string(msg));
		}
	}
}