#include <iostream>
#include "musicboxlib.h"
#include <clocale>
#include "boost\thread.hpp"

using std::cout;
using std::cin;
using std::endl;
CMusicBoxHandler handler;
void onMessage(const char *msg){
	cout << msg << endl;
}

void onConnect(const char *msg){
	cout << "Connected to: " << msg << endl;
	MusicBoxSend(handler, "бля");
}

void onError(const char *msg){
	cout << msg << endl;
}

int main() {

	setlocale(LC_ALL, "");

	//CMusicBox* mb = new CMusicBox;

	////setting callbacks
	//mb->onMessage = &onMessage;
	//mb->onConnect = &onConnect;
	//mb->onError = &onError;

	////Connect & run without thread
	////mb->Connect("ws://localhost/musicbox");

	////starting MusicBox WS task in thread
	//boost::thread t(boost::bind(&CMusicBox::Connect, mb, "ws://localhost/musicbox"));

	//t.join();
	//system("PAUSE");
	//return 0;

	handler = NewMusicBox();

	MusicBoxSetCallback(handler, OnConnect, &onConnect);
	MusicBoxSetCallback(handler, OnError, &onError);
	MusicBoxSetCallback(handler, OnMessage, &onMessage);
	 MusicBoxConnect(handler, "ws://localhost/musicbox") ;
	handler->main_thread->join();
	//MusicBoxClose(handler);
	//MusicBoxSetCallback(handler, OnClose, &oncl);
}