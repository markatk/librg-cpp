/*
 * File: entity.cpp
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

#include "entity.h"

#include "context.h"

#include <cassert>

librg_cpp::Entity::Entity(uint32_t type, const std::shared_ptr<Context> &context) {
    assert(context != nullptr);

    _context = context;
    _entity = librg_entity_create(&context->_context, type);
    _initialized = true;
}

librg_cpp::Entity::Entity(librg_entity *entity, const std::shared_ptr<Context> &context) {
    assert(entity != nullptr);
    assert(context != nullptr);

    _context = context;
    _entity = entity;
    _initialized = false;
}

librg_cpp::Entity::~Entity() {
    if (_initialized == false) {
        return;
    }

    assert(_entity != nullptr);
    assert(_context != nullptr);

    librg_entity_destroy(&_context->_context, id());
}

uint32_t librg_cpp::Entity::id() const {
    assert(_entity != nullptr);

    return _entity->id;
}

uint32_t librg_cpp::Entity::type() const {
    assert(_entity != nullptr);

    return _entity->type;
}

uint64_t librg_cpp::Entity::flags() const {
    assert(_entity != nullptr);

    return _entity->flags;
}
