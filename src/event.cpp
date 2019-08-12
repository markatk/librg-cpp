/*
 * File: event.cpp
 * Author: MarkAtk
 * Date: 11.08.2019
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

#include "event.h"

#include "data.h"
#include "context.h"

#include <cassert>

librg_cpp::Event::Event(librg_event *event, const std::shared_ptr<Context> &context) {
    assert(event != nullptr);
    assert(context != nullptr);

    _event = event;
    _context = context;
    _data = std::make_shared<Data>(_event->data);
    _entity = context->getEntity(_event->entity);

    if (_event->peer != nullptr) {
        _peer = context->getPeer(_event->peer);
    }
}

uint32_t librg_cpp::Event::id() const {
    assert(_event != nullptr);

    return _event->id;
}

std::shared_ptr<librg_cpp::Context> librg_cpp::Event::context() const {
    return _context;
}

std::shared_ptr<librg_cpp::Data> librg_cpp::Event::data() const {
    return _data;
}

std::shared_ptr<librg_cpp::Entity> librg_cpp::Event::entity() const {
    return _entity;
}

std::shared_ptr<librg_cpp::Peer> librg_cpp::Event::peer() const {
    return _peer;
}

uint64_t librg_cpp::Event::flags() const {
    assert(_event != nullptr);

    return _event->flags;
}

void librg_cpp::Event::setUserData(void *ptr) {
    assert(_event != nullptr);

    _event->user_data = ptr;
}

void *librg_cpp::Event::userData() const {
    assert(_event != nullptr);

    return _event->user_data;
}

void librg_cpp::Event::reject() {
    assert(_event != nullptr);

    librg_event_reject(_event);
}

bool librg_cpp::Event::isRejected() const {
    assert(_event != nullptr);

    return _event->flags & (uint64_t) LIBRG_EVENT_REJECTED;
}

bool librg_cpp::Event::isRejectable() const {
    assert(_event != nullptr);

    return librg_event_rejectable(_event);
}

bool librg_cpp::Event::isSucceeded() const {
    assert(_event != nullptr);

    return librg_event_succeeded(_event);
}

bool librg_cpp::Event::isRemote() const {
    assert(_event != nullptr);

    return _event->flags & (uint64_t) LIBRG_EVENT_REMOTE;
}

bool librg_cpp::Event::isLocal() const {
    assert(_event != nullptr);

    return _event->flags & (uint64_t) LIBRG_EVENT_LOCAL;
}
