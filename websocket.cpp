#include "websocket.hpp"
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <iostream>

void WebSocketClient::connect(const std::string& u) {
    uri = u;
}

void WebSocketClient::on_message(const std::function<void(const std::string&)>& cb) {
    message_callback = cb;
}

void WebSocketClient::run() {
    running = true;
    worker = std::thread([this]() {
        try {
            while (running) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                if (message_callback)
                    message_callback("{\"timestamp\":\"2025-05-04T10:39:13Z\",\"asks\":[[\"95445.5\",\"9.06\"]],\"bids\":[[\"95445.4\",\"1104.23\"]]}");
            }
        } catch (const std::exception& e) {
            std::cerr << "WebSocket error: " << e.what() << std::endl;
        }
    });
}

void WebSocketClient::stop() {
    running = false;
    if (worker.joinable()) worker.join();
}