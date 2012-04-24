#include "mb_handler.h"
#include "rapidjson/document.h"
#include "packet.h"

musicbox_client_handler::musicbox_client_handler(CMusicBox *mb){
    musicbox_handler = mb;
}

void musicbox_client_handler::on_open(connection_ptr con){
    musicbox_handler->onConnect(con->get_host());
    connection = con;
    musicbox::Packet *packet = new musicbox::Packet(musicbox::CHATMESSAGE, "blaaaa");
    send(packet->toString());
}

void musicbox_client_handler::on_message(connection_ptr con, message_ptr msg){
    musicbox_handler->onMessage(msg->get_payload());
    rapidjson::Document document;
    if (document.Parse<0>(msg->get_payload().c_str()).HasParseError()){
        std::cerr << "Error: JSON Parsing error!" << std::endl;
        return;
    }
}

void musicbox_client_handler::on_fail(connection_ptr con){
    musicbox_handler->onError("Failed!");
}

void musicbox_client_handler::send(const std::string &msg) {
    if (!connection) {
        std::cerr << "Error: no connected session" << std::endl;
        return;
    }

    if (msg == "/close") {
        close();
    } else {
        connection->send(msg);
    }
}

void musicbox_client_handler::on_close(connection_ptr con){
  musicbox_handler->onClose("Closed!");
}

void musicbox_client_handler::close() {
    if (!connection) {
        std::cerr << "Error: no connected session" << std::endl;
        return;
    }
    connection->close(websocketpp::close::status::GOING_AWAY,"");
}