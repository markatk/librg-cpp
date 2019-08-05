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

#include "host.h"

#include "context.h"

librg_cpp::Host::Host(std::shared_ptr<Context> context) {
    _context = std::move(context);
    _address.host = _host;
    _host[0] = '\0';
}

void librg_cpp::Host::tick() {
    librg_tick(context());
}

bool librg_cpp::Host::isConnected() const {
    return librg_is_connected(context()) != 0;
}

librg_ctx *librg_cpp::Host::context() const {
    return &_context->_context;
}
