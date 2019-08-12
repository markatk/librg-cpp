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
#include "peer.h"
#include "data.h"

#include <cassert>

librg_cpp::Server::Server(std::shared_ptr<Context> context, uint16_t port, const std::string &host) : librg_cpp::Host(std::move(context)) {
    setPort(port);
    setHost(host);
}

librg_cpp::Server::~Server() {
    stop();
}

uint32_t librg_cpp::Server::start() {
    assert(_context != nullptr);

    if (_context->isInitialized() == false) {
        return -1;
    }

    if (isConnected()) {
        return -1;
    }

    return librg_network_start(context(), _address);
}

void librg_cpp::Server::stop() {
    assert(_context != nullptr);

    if (isConnected() == false) {
        return;
    }

    librg_network_stop(context());
}

void librg_cpp::Server::kick(const std::shared_ptr<Peer> &peer) {
    assert(_context != nullptr);
    assert(peer != nullptr);

    librg_network_kick(context(), peer->_peer);
}

void librg_cpp::Server::sendMessage(uint16_t id, const std::shared_ptr<Peer> &peer, void *data, size_t size) {
    assert(_context != nullptr);
    assert(peer != nullptr);
    assert(data != nullptr);

    Host::sendMessage(id, peer, data, size);
}

void librg_cpp::Server::sendMessage(uint16_t id, const std::shared_ptr<Peer> &peer, const std::shared_ptr<Data> &data) {
    assert(_context != nullptr);
    assert(peer != nullptr);
    assert(data != nullptr);

    Host::sendMessage(id, peer, data->raw(), data->writePosition());
}

void librg_cpp::Server::sendMessageToAll(uint16_t id, void *data, size_t size) {
    assert(_context != nullptr);
    assert(data != nullptr);

    Host::sendMessageToAll(id, data, size);
}

void librg_cpp::Server::sendMessageToAll(uint16_t id, const std::shared_ptr<Data> &data) {
    assert(_context != nullptr);
    assert(data != nullptr);

    Host::sendMessageToAll(id, data->raw(), data->writePosition());
}

void librg_cpp::Server::sendMessageExcept(uint16_t id, const std::shared_ptr<Peer> &peer, void *data, size_t size) {
    assert(_context != nullptr);
    assert(peer != nullptr);
    assert(data != nullptr);

    Host::sendMessageExcept(id, peer, data, size);
}

void librg_cpp::Server::sendMessageExcept(uint16_t id, const std::shared_ptr<Peer> &peer, const std::shared_ptr<Data> &data) {
    assert(_context != nullptr);
    assert(peer != nullptr);
    assert(data != nullptr);

    Host::sendMessageExcept(id, peer, data->raw(), data->writePosition());
}

void librg_cpp::Server::sendMessageInStream(uint16_t id, const std::shared_ptr<Entity> &entity, void *data, size_t size) {
    assert(_context != nullptr);
    assert(entity != nullptr);
    assert(data != nullptr);

    Host::sendMessageInStream(id, entity, data, size);
}

void librg_cpp::Server::sendMessageInStream(uint16_t id, const std::shared_ptr<Entity> &entity, const std::shared_ptr<Data> &data) {
    assert(_context != nullptr);
    assert(entity != nullptr);
    assert(data != nullptr);

    Host::sendMessageInStream(id, entity, data->raw(), data->writePosition());
}

void librg_cpp::Server::sendMessageInStreamExcept(uint16_t id, const std::shared_ptr<Entity> &entity, const std::shared_ptr<Peer> &peer, void *data, size_t size) {
    assert(_context != nullptr);
    assert(entity != nullptr);
    assert(peer != nullptr);
    assert(data != nullptr);

    Host::sendMessageInStreamExcept(id, entity, peer, data, size);
}

void librg_cpp::Server::sendMessageInStreamExcept(uint16_t id, const std::shared_ptr<Entity> &entity, const std::shared_ptr<Peer> &peer, const std::shared_ptr<Data> &data) {
    assert(_context != nullptr);
    assert(entity != nullptr);
    assert(peer != nullptr);
    assert(data != nullptr);

    Host::sendMessageInStreamExcept(id, entity, peer, data->raw(), data->writePosition());
}

void librg_cpp::Server::setPort(uint16_t port) {
    assert(port >= 0);

    _address.port = port;
}

void librg_cpp::Server::setHost(const std::string &host) {
#ifdef WIN32
    strcpy_s(_host, MAX_HOST_LENGTH, host.c_str());
#else
    strncpy(_host, host.c_str(), MAX_HOST_LENGTH);
#endif
}

uint16_t librg_cpp::Server::port() const {
    return _address.port;
}

std::string librg_cpp::Server::host() const {
    return std::string(_address.host);
}
