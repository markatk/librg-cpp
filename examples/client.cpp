/*
 * File: client.cpp
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

class Client : public librg_cpp::Client {
private:
    bool _shutdown;

public:
    explicit Client(std::shared_ptr<librg_cpp::Context> context) : librg_cpp::Client(std::move(context)) {
        _shutdown = false;
    }

    ~Client() override = default;

    bool isShutdown() const {
        return _shutdown;
    }

protected:
    void onConnectionRequest(librg_event *event) override {
        std::cout << "Connection requested" << std::endl;
    }

    void onConnectionAccept(librg_event *event) override {
        std::cout << "Connection accepted" << std::endl;
    }

    void onConnectionDisconnect(librg_event *event) override {
        std::cout << "Disconnected" << std::endl;

        _shutdown = true;
    }

    void onConnectionTimeout(librg_event *event) override {
        std::cout << "Timeout" << std::endl;

        _shutdown = true;
    }
};

int main(int argc, char **argv) {
    std::cout << "librg-cpp client example " << LIBRG_CPP_VERSION << std::endl;

    auto context = std::make_shared<librg_cpp::Context>(false, 64);
    if (context->initialize() != LIBRG_CPP_NO_ERROR) {
        std::cerr << "Unable to initialize librg context" << std::endl;

        return EXIT_FAILURE;
    }

    Client client(context);

    if (client.connect("::1", 12345) != LIBRG_CPP_NO_ERROR) {
        std::cerr << "Unable to connect to server" << std::endl;

        return EXIT_FAILURE;
    }

    while (client.isShutdown() == false) {
        client.tick();
    }

    // clean up
    client.disconnect();
    context->deinitialize();

    return EXIT_SUCCESS;
}
