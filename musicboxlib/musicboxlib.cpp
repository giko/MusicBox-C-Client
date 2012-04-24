// musicboxlib.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "musicboxlib.h"
#include "packet.h"
#include "mb_handler.h"

// This is the constructor of a class that has been exported.
// see musicboxlib.h for the class definition
CMusicBox::CMusicBox()
{
	return;
}

bool CMusicBox::Connect(const char *uri){
	try {
		//std::cout << string(uri);

		musicbox_client_handler_ptr handler(new musicbox_client_handler(this));
		client::connection_ptr con;
		client endpoint(handler);

		string uristr(uri);

		std::cout << uristr;

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
	CMusicBoxHandler NewMusicBox(void){
		return new CMusicBox;
	}

	bool MusicBoxConnect(CMusicBoxHandler handler, const char *url){
		return handler->Connect(url);
	}

	void MusicBoxSetCallback(CMusicBoxHandler handler, enum CallbackType type, mb_callback cb){
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
}