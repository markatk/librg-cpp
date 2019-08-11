/*
 * File: server.cpp
 * Author: MarkAtk
 * Date: 01.08.2019
 *
 * Copyright 2019 MarkAtk
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <iostream>

#include <librg-cpp/librg-cpp.h>

class Server : public librg_cpp::Server {
public:
    explicit Server(std::shared_ptr<librg_cpp::Context> context) : librg_cpp::Server(std::move(context), 12345) {

    }

    ~Server() override = default;

protected:
    void onConnectionRequest(const std::unique_ptr<librg_cpp::Event> &event) override {
        std::cout << "Connection requested: " << event->data()->readInt64() << std::endl;
    }

    void onConnectionAccept(const std::unique_ptr<librg_cpp::Event> &event) override {
        std::cout << "Connection accepted" << std::endl;
    }

    void onConnectionDisconnect(const std::unique_ptr<librg_cpp::Event> &event) override {
        std::cout << "Disconnected" << std::endl;
    }

    void onConnectionTimeout(const std::unique_ptr<librg_cpp::Event> &event) override {
        std::cout << "Timeout" << std::endl;
    }
};

int main(int argc, char **argv) {
    std::cout << "librg-cpp server example " << LIBRG_CPP_VERSION << std::endl;

    auto context = std::make_shared<librg_cpp::Context>(true, 64, 32);
    if (context->initialize() != LIBRG_CPP_NO_ERROR) {
        std::cerr << "Unable to initialize librg context" << std::endl;

        return EXIT_FAILURE;
    }

    Server server(context);

    if (server.start() != LIBRG_CPP_NO_ERROR) {
        std::cerr << "Unable to start server" << std::endl;

        return EXIT_FAILURE;
    }

    while (true) {
        server.tick();
    }

    // clean up
    server.stop();
    context->deinitialize();

    return EXIT_SUCCESS;
}
