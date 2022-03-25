// This file is part of NOIR.
//
// Copyright (c) 2022 Haderech Pte. Ltd.
// SPDX-License-Identifier: AGPL-3.0-or-later
//
#include <noir/rpc/websocket/websocket.h>
#include <appbase/application.hpp>

namespace noir::rpc {

using namespace std;
using namespace appbase;

using connection_ptr = websocketpp::server<websocketpp::config::asio>::connection_ptr;
using message_ptr = websocketpp::server<websocketpp::config::asio>::message_ptr;

void websocket::add_message_api(const std::string& path, message_handler handler, int priority) {
  add_message_handler(path, handler, priority);
}

void websocket::add_message_handler(const std::string& path, message_handler& handler, int priority) {
  message_handlers[path] = make_app_thread_message_handler(handler, priority);
}

internal_message_handler websocket::make_app_thread_message_handler(message_handler next, int priority) {
  auto next_ptr = std::make_shared<message_handler>(std::move(next));
  return [priority, next_ptr = std::move(next_ptr)](connection_ptr conn, const string& payload, message_sender then) {
    message_sender wrapped_then = [then = std::move(then)](string msg) { then(std::move(msg)); };

    app().post(priority, [next_ptr, conn = std::move(conn), payload, wrapped_then = std::move(wrapped_then)]() mutable {
      try {
        (*next_ptr)(payload, std::move(wrapped_then));
      } catch (...) {
        conn->send("Internal Server Error");
      }
    });
  };
}

message_sender websocket::make_message_sender(connection_ptr conn, int priority) {
  return [priority, conn = std::move(conn)](const string& msg) {
    app().post(priority, [conn, msg]() {
      try {
        conn->send(msg);
      } catch (...) {
        conn->send("Internal Server Error");
      }
    });
  };
}
} // namespace noir::rpc
