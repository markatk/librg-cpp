/*
 * File: client.cpp
 * Author: MarkAtk
 * Date: 05.08.2019
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

#include "client.h"

#include "context.h"

librg_cpp::Client::Client(std::shared_ptr<Context> context) : librg_cpp::Host(std::move(context)) {

}

librg_cpp::Client::~Client() {
    disconnect();
}

int librg_cpp::Client::connect(const std::string &host, int port) {
    if (_context->isInitialized() == false) {
        return -1;
    }

    if (isConnected()) {
        return -1;
    }

    _address.port = port;
    strcpy_s(_address.host, MAX_HOST_LENGTH, host.c_str());

    return librg_network_start(context(), _address);
}

void librg_cpp::Client::disconnect() {
    if (isConnected() == false) {
        return;
    }

    librg_network_stop(context());
}
