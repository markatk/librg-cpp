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

#include "server.h"

#include "context.h"

librg_cpp::Server::Server(std::shared_ptr<Context> context, int port, const std::string &host) {
    _context = std::move(context);
    _address.host = _host;

    setPort(port);
    setHost(host);
}

librg_cpp::Server::~Server() {
    stop();
}

int librg_cpp::Server::start() {
    if (isStarted()) {
        return -1;
    }

    if (_context->isInitialized() == false) {
        return -1;
    }

    return librg_network_start(context(), _address);
}

void librg_cpp::Server::stop() {
    if (isStarted() == false) {
        return;
    }

    librg_network_stop(context());
}

bool librg_cpp::Server::isStarted() const {
    return librg_is_connected(context()) != 0;
}

void librg_cpp::Server::tick() {
    librg_tick(context());
}

void librg_cpp::Server::setPort(int port) {
    _address.port = port;
}

void librg_cpp::Server::setHost(const std::string &host) {
    strcpy_s(_host, MAX_HOST_LENGTH + 1, host.c_str());
}

int librg_cpp::Server::port() const {
    return _address.port;
}

std::string librg_cpp::Server::host() const {
    return std::string(_address.host);
}

librg_ctx *librg_cpp::Server::context() const {
    return &_context->_context;
}
