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
#include "data.h"

#include "result.h"
#include "utility.h"

#include <cassert>

librg_cpp::Client::Client(std::shared_ptr<Context> context) : librg_cpp::Host(std::move(context)) {
    assert(context->isServer() == false);
}

librg_cpp::Client::~Client() {
    disconnect();
}

int librg_cpp::Client::connect(const std::string &host, int32_t port) {
    assert(_context != nullptr);
    assert(port >= 0);

    if (_context->isInitialized() == false) {
        return LIBRG_CPP_CONTEXT_UNINITIALIZED;
    }

    if (isConnected()) {
        return LIBRG_CPP_CLIENT_ALREADY_CONNECTED;
    }

    _address.port = port;

#ifdef WIN32
    strcpy_s(_address.host, MAX_HOST_LENGTH, host.c_str());
#else
    strncpy(_address.host, host.c_str(), MAX_HOST_LENGTH);
#endif

    auto result = librg_network_start(context(), _address);
    if (result == 0) {
        return LIBRG_CPP_NO_ERROR;
    } else if (result == -1) {
        return LIBRG_CPP_HOST_CREATION_FAILED;
    } else if (result == -2) {
        return LIBRG_CPP_CLIENT_PEER_CREATION_FAILED;
    }

    // This should only be returned when librg changes error messages
    return LIBRG_CPP_UNKNOWN_ERROR;
}

void librg_cpp::Client::disconnect() {
    assert(_context != nullptr);

    if (isConnected() == false) {
        return;
    }

    librg_network_stop(context());
}

bool librg_cpp::Client::isConnected() const {
    return Host::isConnected();
}

void librg_cpp::Client::tick() {
    Host::tick();
}

void librg_cpp::Client::sendMessage(uint16_t id, void *data, size_t size) {
    assert(data != nullptr);

    sendMessageToAll(id, data, size);
}

void librg_cpp::Client::sendMessage(uint16_t id, const std::shared_ptr<Data> &data) {
    assert(data != nullptr);

    sendMessageToAll(id, data->raw(), data->writePosition());
}
