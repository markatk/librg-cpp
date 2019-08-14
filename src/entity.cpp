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
#include "peer.h"

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

#ifdef LIBRG_CPP_USE_LINALG
void librg_cpp::Entity::setPosition(linalg::aliases::float3 position) {
    assert(_entity != nullptr);

    _entity->position = zpl_vec3f(position.x, position.y, position.z);
}

linalg::aliases::float3 librg_cpp::Entity::position() const {
    assert(_entity != nullptr);

    return linalg::aliases::float3(_entity->position.x, _entity->position.y, _entity->position.z);
}
#else
void librg_cpp::Entity::setPosition(zpl_vec3 position) {
    assert(_entity != nullptr);

    _entity->position = position;
}

zpl_vec3 librg_cpp::Entity::position() const {
    assert(_entity != nullptr);

    return _entity->position;
}
#endif

void librg_cpp::Entity::setControlPeer(const std::shared_ptr<Peer> &peer) {
    assert(_entity != nullptr);
    assert(peer != nullptr);

    librg_entity_control_set(&_context->_context, id(), peer->_peer);
}

void librg_cpp::Entity::removeControlPeer() {
    assert(_entity != nullptr);

    librg_entity_control_remove(&_context->_context, id());
}

void librg_cpp::Entity::ignoreNextControlUpdate() {
    assert(_entity != nullptr);

    librg_entity_control_ignore_next_update(&_context->_context, id());
}

std::shared_ptr<librg_cpp::Peer> librg_cpp::Entity::controlPeer() const {
    assert(_entity != nullptr);

    auto peer = librg_entity_control_get(&_context->_context, id());
    if (peer == nullptr) {
        return nullptr;
    }

    return _context->getPeer(peer);
}

#ifdef LIBRG_FEATURE_ENTITY_VISIBILITY
void librg_cpp::Entity::setVisibility(librg_visibility state) {
    assert(_entity != nullptr);

    librg_entity_visibility_set(&_context->_context, id(), state);
}

librg_visibility librg_cpp::Entity::visibility() const {
    assert(_entity != nullptr);

    return librg_entity_visibility_get(&_context->_context, id());
}

void librg_cpp::Entity::setVisibilityFor(const std::shared_ptr<Entity> &target, librg_visibility state) {
    assert(_entity != nullptr);
    assert(target != nullptr);

    librg_entity_visibility_set_for(&_context->_context, id(), target->id(), state);
}

librg_visibility librg_cpp::Entity::visibilityFor(const std::shared_ptr<Entity> &target) const {
    assert(_entity != nullptr);
    assert(target != nullptr);

    return librg_entity_visibility_get_for(&_context->_context, id(), target->id());
}
#endif

#ifdef LIBRG_FEATURE_VIRTUAL_WORLDS
void librg_cpp::Entity::setWorld(uint32_t world) {
    assert(_entity != nullptr);

    librg_entity_world_set(&_context->_context, id(), world);
}

uint32_t librg_cpp::Entity::world() const {
    assert(_entity != nullptr);

    return librg_entity_world_get(&_context->_context, id());
}
#endif

bool librg_cpp::Entity::isAlive() const {
    assert(_entity != nullptr);

    return _entity->flags & (uint64_t) LIBRG_ENTITY_ALIVE;
}

bool librg_cpp::Entity::isClient() const {
    assert(_entity != nullptr);

    return _entity->flags & (uint64_t) LIBRG_ENTITY_CLIENT;
}

bool librg_cpp::Entity::hasVisibility() const {
    assert(_entity != nullptr);

    return _entity->flags & (uint64_t) LIBRG_ENTITY_VISIBILITY;
}

bool librg_cpp::Entity::hasQueried() const {
    assert(_entity != nullptr);

    return _entity->flags & (uint64_t) LIBRG_ENTITY_QUERIED;
}

bool librg_cpp::Entity::isControlled() const {
    assert(_entity != nullptr);

    return _entity->flags & (uint64_t) LIBRG_ENTITY_CONTROLLED;
}

bool librg_cpp::Entity::isControlRequested() const {
    assert(_entity != nullptr);

    return _entity->flags & (uint64_t) LIBRG_ENTITY_CONTROL_REQUESTED;
}

bool librg_cpp::Entity::isMarkedRemoval() const {
    assert(_entity != nullptr);

    return _entity->flags & (uint64_t) LIBRG_ENTITY_MARKED_REMOVAL;
}

bool librg_cpp::Entity::isUnused() const {
    assert(_entity != nullptr);

    return _entity->flags & (uint64_t) LIBRG_ENTITY_UNUSED;
}
