#pragma once

#include <string>

using std::string;

namespace musicbox {
    enum Action {
        GETAUDIOBYTRACK, LOGIN, SEARCH, LISTENING, LOGINBYTOKEN, LOGINBYCODE, GETSONGBYID, GETURLBYTRACK, CHATMESSAGE,
        GETTOPSONGSBYARTISTID, GETTOPSONGSBYARTISTNAME, ADDTOLIBRARY, SEARCHBYTAG
    };

    class Packet{
    public:
        string getActionString() const;
        Packet(Action act, string msg);
        string toString();
    protected:
        template <typename Writer>
        void Serialize(Writer& writer) const;
    private:
        Action action;
        string message;
    };
}