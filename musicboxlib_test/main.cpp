#include <iostream>
#include "musicboxlib.h"
#include <locale.h>
#include "jsonlib.h"

using std::cout;
using std::cin;
using std::endl;
CMusicBoxHandler handler;

void onMessage(const PRoot msg){
    if (Json_getString(Json_getChildFromRoot(msg, "action")) == "MESSAGE"){
        cout << Json_getString(Json_getChildFromRoot(msg, "message"));
    }

    cout << Json_getString(Json_getChildFromRoot(msg, "action"));
}

void onConnect(const char *msg){
    cout << "Connected: " << msg << endl;
    MusicBoxSend(handler, musicbox::LOGIN, "4f66e89b3d5c1ff58608901553d5dbdb4accd2ecd7cbff765e34a4becfe96d1c");
    MusicBoxSend(handler, musicbox::CHATMESSAGE, "Урааа");
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
    MusicBoxSetOnMessage(handler, &onMessage);
    MusicBoxConnect(handler, "ws://localhost/musicbox") ;
    for(;;){
    }
    //MusicBoxClose(handler);
    //MusicBoxSetCallback(handler, OnClose, &oncl);
}