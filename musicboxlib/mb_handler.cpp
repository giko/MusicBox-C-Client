#include "musicboxlib.h"
#include "rapidjson/document.h"
#include "packet.h"

CMusicBox::musicbox_client_handler::musicbox_client_handler(CMusicBox *mb){
	musicbox_handler = mb;
}

void CMusicBox::musicbox_client_handler::on_open(connection_ptr con){
	connection = con;
	musicbox::Packet *packet = new musicbox::Packet(musicbox::CHATMESSAGE, "blaaaa");
	send(packet->toString());

	musicbox_handler->onConnect("OK!");
}

void CMusicBox::musicbox_client_handler::on_message(connection_ptr con, message_ptr msg){
    musicbox_handler->onMessage(msg->get_payload().c_str());
	rapidjson::Document document;
	if (document.Parse<0>(msg->get_payload().c_str()).HasParseError()){
		musicbox_handler->onError("Error: JSON Parsing error!");
		return;
	}
}

void CMusicBox::musicbox_client_handler::on_fail(connection_ptr con){
	musicbox_handler->onError("Failed!");
}

void CMusicBox::musicbox_client_handler::send(const std::string &msg) {
	if (!connection) {
		musicbox_handler->onError("Error: no connected session");
		return;
	}

	if (msg == "/close") {
		close();
	} else {
		connection->send(msg);
	}
}

void CMusicBox::musicbox_client_handler::on_close(connection_ptr con){
	musicbox_handler->onClose("Closed!");
}

void CMusicBox::musicbox_client_handler::close() {
	if (!connection) {
		musicbox_handler->onError("Error: no connected session");
		return;
	}
	connection->close(websocketpp::close::status::GOING_AWAY,"");
}