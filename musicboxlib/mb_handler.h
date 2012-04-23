#pragma once

#include "musicboxlib.h"
#include "roles\client.hpp"
#include "websocketpp.hpp"

using websocketpp::client;

class musicbox_client_handler : public client::handler {
public:
  musicbox_client_handler(CMusicBox *mb);
  void on_open(connection_ptr con);

  void on_message(connection_ptr con, message_ptr msg);
  void send(const std::string &msg);
  void close();

  void on_fail(connection_ptr con);
private:
  CMusicBox *musicbox_handler;
  connection_ptr connection;
};

typedef boost::shared_ptr<musicbox_client_handler> musicbox_client_handler_ptr;