/*
 * File: message.cpp
 * Author: MarkAtk
 * Date: 12.08.2019
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

#include "message.h"

#include "context.h"
#include "data.h"

#include <cassert>

librg_cpp::Message::Message(librg_message *message, const std::shared_ptr<Context> &context) {
    assert(message != nullptr);
    assert(context != nullptr);

    _message = message;
    _context = context;
    _data = std::make_shared<Data>(_message->data);
}

uint32_t librg_cpp::Message::id() const {
    return _message->id;
}

std::shared_ptr<librg_cpp::Context> librg_cpp::Message::context() const {
    return _context;
}

std::shared_ptr<librg_cpp::Data> librg_cpp::Message::data() const {
    return _data;
}

void librg_cpp::Message::setUserData(void *ptr) {
    _message->user_data = ptr;
}

void *librg_cpp::Message::userData() const {
    return _message->user_data;
}
