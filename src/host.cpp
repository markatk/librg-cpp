/*
 * File: host.cpp
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

#include "internal/host.h"

#include "context.h"
#include "event.h"
#include "message.h"
#include "peer.h"
#include "entity.h"

#include <cassert>
#include <utility>
#include <memory>

librg_cpp::Host::Host(std::shared_ptr<Context> context) {
    assert(context != nullptr);

    _context = std::move(context);
    _address.host = _host;
    _host[0] = '\0';

    _context->setUserData(this);

    // register all events
    librg_event_add(this->context(), LIBRG_CONNECTION_INIT, onEvent);
    librg_event_add(this->context(), LIBRG_CONNECTION_REQUEST, onEvent);
    librg_event_add(this->context(), LIBRG_CONNECTION_REFUSE, onEvent);
    librg_event_add(this->context(), LIBRG_CONNECTION_ACCEPT, onEvent);
    librg_event_add(this->context(), LIBRG_CONNECTION_DISCONNECT, onEvent);
    librg_event_add(this->context(), LIBRG_CONNECTION_TIMEOUT, onEvent);
    librg_event_add(this->context(), LIBRG_CONNECTION_TIMESYNC, onEvent);
    librg_event_add(this->context(), LIBRG_ENTITY_CREATE, onEvent);
    librg_event_add(this->context(), LIBRG_ENTITY_UPDATE, onEvent);
    librg_event_add(this->context(), LIBRG_ENTITY_REMOVE, onEvent);
    librg_event_add(this->context(), LIBRG_CLIENT_STREAMER_ADD, onEvent);
    librg_event_add(this->context(), LIBRG_CLIENT_STREAMER_REMOVE, onEvent);
    librg_event_add(this->context(), LIBRG_CLIENT_STREAMER_UPDATE, onEvent);

    // register own methods as callbacks
    registerEvent(LIBRG_CONNECTION_INIT, [this](const std::unique_ptr<Event> &event) { onConnectionInitialize(event); });
    registerEvent(LIBRG_CONNECTION_REQUEST, [this](const std::unique_ptr<Event> &event) { onConnectionRequest(event); });
    registerEvent(LIBRG_CONNECTION_REFUSE, [this](const std::unique_ptr<Event> &event) { onConnectionRefuse(event); });
    registerEvent(LIBRG_CONNECTION_ACCEPT, [this](const std::unique_ptr<Event> &event) { onConnectionAccept(event); });
    registerEvent(LIBRG_CONNECTION_DISCONNECT, [this](const std::unique_ptr<Event> &event) { onConnectionDisconnect(event); });
    registerEvent(LIBRG_CONNECTION_TIMEOUT, [this](const std::unique_ptr<Event> &event) { onConnectionTimeout(event); });
    registerEvent(LIBRG_CONNECTION_TIMESYNC, [this](const std::unique_ptr<Event> &event) { onConnectionTimeSync(event); });
    registerEvent(LIBRG_ENTITY_CREATE, [this](const std::unique_ptr<Event> &event) { onEntityCreate(event); });
    registerEvent(LIBRG_ENTITY_UPDATE, [this](const std::unique_ptr<Event> &event) { onEntityUpdate(event); });
    registerEvent(LIBRG_ENTITY_REMOVE, [this](const std::unique_ptr<Event> &event) { onEntityRemove(event); });
    registerEvent(LIBRG_CLIENT_STREAMER_ADD, [this](const std::unique_ptr<Event> &event) { onClientStreamerAdd(event); });
    registerEvent(LIBRG_CLIENT_STREAMER_REMOVE, [this](const std::unique_ptr<Event> &event) { onClientStreamerRemove(event); });
    registerEvent(LIBRG_CLIENT_STREAMER_UPDATE, [this](const std::unique_ptr<Event> &event) { onClientStreamerUpdate(event); });
}

void librg_cpp::Host::tick() {
    assert(_context != nullptr);

    librg_tick(context());
}

bool librg_cpp::Host::isConnected() const {
    assert(_context != nullptr);

    return librg_is_connected(context()) != 0;
}

void librg_cpp::Host::sendMessage(uint16_t id, const std::shared_ptr<Peer> &peer, void *data, size_t size) {
    assert(_context != nullptr);
    assert(peer != nullptr);
    assert(data != nullptr);

    librg_message_send_to(context(), id, peer->_peer, data, size);
}

void librg_cpp::Host::sendMessageToAll(uint16_t id, void *data, size_t size) {
    assert(_context != nullptr);
    assert(data != nullptr);

    librg_message_send_all(context(), id, data, size);
}

void librg_cpp::Host::sendMessageExcept(uint16_t id, const std::shared_ptr<Peer> &peer, void *data, size_t size) {
    assert(_context != nullptr);
    assert(peer != nullptr);
    assert(data != nullptr);

    librg_message_send_except(context(), id, peer->_peer, data, size);
}

void librg_cpp::Host::sendMessageInStream(uint16_t id, const std::shared_ptr<Entity> &entity, void *data, size_t size) {
    assert(_context != nullptr);
    assert(entity != nullptr);
    assert(data != nullptr);

    librg_message_send_instream(context(), id, entity->id(), data, size);
}

void librg_cpp::Host::sendMessageInStreamExcept(uint16_t id, const std::shared_ptr<Entity> &entity, const std::shared_ptr<Peer> &peer, void *data, size_t size) {
    assert(_context != nullptr);
    assert(entity != nullptr);
    assert(peer != nullptr);
    assert(data != nullptr);

    librg_message_send_instream_except(context(), id, entity->id(), peer->_peer, data, size);
}

void librg_cpp::Host::onConnectionInitialize(const std::unique_ptr<Event> &event) {
    // Do nothing by default
}

void librg_cpp::Host::onConnectionRequest(const std::unique_ptr<Event> &event) {
    // Do nothing by default
}

void librg_cpp::Host::onConnectionRefuse(const std::unique_ptr<Event> &event) {
    // Do nothing by default
}

void librg_cpp::Host::onConnectionAccept(const std::unique_ptr<Event> &event) {
    // Do nothing by default
}

void librg_cpp::Host::onConnectionDisconnect(const std::unique_ptr<Event> &event) {
    // Do nothing by default
}

void librg_cpp::Host::onConnectionTimeout(const std::unique_ptr<Event> &event) {
    // Do nothing by default
}

void librg_cpp::Host::onConnectionTimeSync(const std::unique_ptr<Event> &event) {
    // Do nothing by default
}

void librg_cpp::Host::onEntityCreate(const std::unique_ptr<Event> &event) {
    // Do nothing by default
}

void librg_cpp::Host::onEntityUpdate(const std::unique_ptr<Event> &event) {
    // Do nothing by default
}

void librg_cpp::Host::onEntityRemove(const std::unique_ptr<Event> &event) {
    // Do nothing by default
}

void librg_cpp::Host::onClientStreamerAdd(const std::unique_ptr<Event> &event) {
    // Do nothing by default
}

void librg_cpp::Host::onClientStreamerRemove(const std::unique_ptr<Event> &event) {
    // Do nothing by default
}

void librg_cpp::Host::onClientStreamerUpdate(const std::unique_ptr<Event> &event) {
    // Do nothing by default
}

void librg_cpp::Host::registerEvent(uint32_t id, std::function<void(const std::unique_ptr<Event> &)> callback) {
    assert(callback != nullptr);

    _eventCallbacks[id] = std::move(callback);
}

void librg_cpp::Host::unregisterEvent(uint32_t id, std::function<void(const std::unique_ptr<Event> &)> callback) {
    assert(callback != nullptr);

    auto it = _eventCallbacks.find(id);
    if (it == _eventCallbacks.end()) {
        return;
    }

    _eventCallbacks.erase(it);
}

void librg_cpp::Host::registerMessage(uint16_t id, std::function<void(const std::unique_ptr<Message> &)> callback) {
    assert(_context != nullptr);
    assert(id >= LIBRG_EVENT_LAST);
    assert(callback != nullptr);

    _messageCallbacks[id] = std::move(callback);

    librg_network_add(context(), id, onMessage);
}

void librg_cpp::Host::unregisterMessage(uint16_t id, std::function<void(const std::unique_ptr<Message> &)> callback) {
    assert(_context != nullptr);
    assert(id >= LIBRG_EVENT_LAST);
    assert(callback != nullptr);

    auto it = _messageCallbacks.find(id);
    if (it == _messageCallbacks.end()) {
        return;
    }

    _messageCallbacks.erase(it);
}

librg_ctx *librg_cpp::Host::context() const {
    assert(_context != nullptr);

    return &_context->_context;
}

void librg_cpp::Host::onEvent(librg_event *event) {
    assert(event != nullptr);

    auto host = reinterpret_cast<Host *>(event->ctx->user_data);
    assert(host != nullptr);

    auto callback = host->_eventCallbacks[event->id];
    if (callback == nullptr) {
        return;
    }

    // wrap event
    // Do not use std::make_unique to be C++11 compliant
    auto wrappedEvent = std::unique_ptr<Event>(new Event(event, host->_context));

    callback(wrappedEvent);
}

void librg_cpp::Host::onMessage(librg_message *message) {
    assert(message != nullptr);

    auto host = reinterpret_cast<Host *>(message->ctx->user_data);
    assert(host != nullptr);

    auto callback = host->_messageCallbacks[message->id];
    if (callback == nullptr) {
        return;
    }

    // wrap event
    // Do not use std::make_unique to be C++11 compliant
    auto wrappedMessage = std::unique_ptr<Message>(new Message(message, host->_context));

    callback(wrappedMessage);
}
