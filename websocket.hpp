#pragma once
#include <string>
#include <thread>
#include <functional>

class WebSocketClient {
public:
    void connect(const std::string& uri);
    void on_message(const std::function<void(const std::string&)>& callback);
    void run();
    void stop();

private:
    std::string uri;
    std::function<void(const std::string&)> message_callback;
    std::thread worker;
    bool running = false;
};