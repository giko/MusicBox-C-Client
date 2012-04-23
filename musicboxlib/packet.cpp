#include "rapidjson/prettywriter.h"     // for stringify JSON
#include "rapidjson/filestream.h"       // wrapper of C stream for prettywriter as output
#include "rapidjson/filewritestream.h"
#include <iostream>
#include <sstream>
#include "packet.h"

using namespace musicbox;

string Packet::getActionString() const {
    switch(action){
    case GETAUDIOBYTRACK:
        return "GETAUDIOBYTRACK";
    case LOGIN:
        return "LOGIN";
    case SEARCH:
        return "SEARCH";
    case LISTENING:
        return "LISTENING";
    case LOGINBYTOKEN:
        return "LOGINBYTOKEN";
    case LOGINBYCODE:
        return "LOGINBYCODE";
    case GETSONGBYID:
        return "GETSONGBYID";
    case GETURLBYTRACK:
        return "GETURLBYTRACK";
    case CHATMESSAGE:
        return "CHATMESSAGE";
    case GETTOPSONGSBYARTISTID:
        return "GETTOPSONGSBYARTISTID";
    case GETTOPSONGSBYARTISTNAME:
        return "GETTOPSONGSBYARTISTNAME";
    case ADDTOLIBRARY:
        return "ADDTOLIBRARY";
    case SEARCHBYTAG:
        return "SEARCHBYTAG";
    }

    std::cerr << "Error: Action enum hasn't such member!" << std::endl;
    return NULL;
}

Packet::Packet(Action act, string msg){
    action = act;
    message = msg;
}

template <typename Writer>
void Packet::Serialize(Writer& writer) const {
    writer.StartObject();

    writer.String("action");
    writer.String(getActionString().c_str(), (rapidjson::SizeType)getActionString().length());

    writer.String("message");
    writer.String(message.c_str(), (rapidjson::SizeType)message.length());

    writer.EndObject();
}

string Packet::toString(){
    std::stringstream s;
    rapidjson::Writer<std::stringstream> writer(s);             // Can also use Writer for condensed formatting
    Serialize(writer);
    return s.str();
}