/*
 * File: context.cpp
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

#include "context.h"

#include "result.h"
#include "peer.h"
#include "entity.h"
#include "host.h"

#include <cassert>

librg_cpp::Context::Context(bool isServer, double tickDelay, uint16_t maxClients) : _context({0}) {
    assert(tickDelay > 0);

    _initialized = false;
    _peerPool = std::make_shared<Pool<librg_peer, Peer>>();
    _entityPool = std::make_shared<Pool<librg_entity, Entity>>();

    reset();

    setServer(isServer);
    setTickDelay(tickDelay);
    setMaxClients(maxClients);
}

librg_cpp::Context::~Context() {
    deinitialize();
}

uint32_t librg_cpp::Context::initialize() {
    if (isInitialized()) {
        return LIBRG_CPP_CONTEXT_ALREADY_INITIALIZED;
    }

    if (librg_init(&_context) != 0) {
        return LIBRG_CPP_CONTEXT_INITIALIZE_FAILED;
    }

    _initialized = true;

    return LIBRG_CPP_NO_ERROR;
}

void librg_cpp::Context::deinitialize() {
    if (isInitialized() == false) {
        return;
    }

    librg_free(&_context);

    _initialized = false;
}

bool librg_cpp::Context::isInitialized() const {
    return _initialized;
}

void librg_cpp::Context::setServer(bool isServer) {
    _context.mode = isServer ? LIBRG_MODE_SERVER : LIBRG_MODE_CLIENT;
}

void librg_cpp::Context::setTickDelay(double delay) {
    assert(delay > 0);

    _context.tick_delay = delay;
}

void librg_cpp::Context::setMaxClients(uint16_t maxClients) {
    _context.max_connections = maxClients;
}

void librg_cpp::Context::setMaxEntities(uint16_t maxEntities) {
    _context.max_entities = maxEntities;
}

bool librg_cpp::Context::isServer() const {
    return _context.mode == LIBRG_MODE_SERVER;
}

double librg_cpp::Context::tickDelay() const {
    return _context.tick_delay;
}

uint16_t librg_cpp::Context::maxClients() const {
    return _context.max_connections;
}

uint16_t librg_cpp::Context::maxEntities() const {
    return _context.max_entities;
}

#ifdef LIBRG_CPP_USE_LINALG
void librg_cpp::Context::setWorldSize(linalg::aliases::float3 size) {
    _context.world_size = zpl_vec3f(size.x, size.y, size.z);
}

void librg_cpp::Context::setMinBranchSize(linalg::aliases::float3 size) {
    _context.min_branch_size = zpl_vec3f(size.x, size.y, size.z);
}

linalg::aliases::float3 librg_cpp::Context::worldSize() const {
    return { _context.world_size.x, _context.world_size.y, _context.world_size.z };
}

linalg::aliases::float3 librg_cpp::Context::minBranchSize() const {
    return { _context.min_branch_size.x, _context.min_branch_size.y, _context.min_branch_size.z };
}
#else
void librg_cpp::Context::setWorldSize(zpl_vec3 size) {
    _context.world_size = size;
}

void librg_cpp::Context::setMinBranchSize(zpl_vec3 size) {
    _context.min_branch_size = size;
}

zpl_vec3 librg_cpp::Context::worldSize() const {
    return _context.world_size;
}

zpl_vec3 librg_cpp::Context::minBranchSize() const {
    return _context.min_branch_size;
}
#endif

std::shared_ptr<librg_cpp::Entity> librg_cpp::Context::createEntity(uint32_t type) {
    assert(_entityPool != nullptr);

    auto entity = std::shared_ptr<Entity>(new Entity(type, shared_from_this()));

    _entityPool->add(entity->_entity, entity);

    return entity;
}

bool librg_cpp::Context::destroyEntity(const std::shared_ptr<Entity> &entity) {
    assert(entity != nullptr);
    assert(_entityPool != nullptr);

    if (entity->_initialized == false) {
        return false;
    }

    _entityPool->remove(entity->_entity);

    entity->destroy();

    return true;
}

std::shared_ptr<librg_cpp::Entity> librg_cpp::Context::getEntity(uint32_t id) {
    auto entity = librg_entity_fetch(&_context, id);
    if (entity == nullptr) {
        return nullptr;
    }

    return getEntity(entity);
}

std::shared_ptr<librg_cpp::Entity> librg_cpp::Context::getEntity(const std::shared_ptr<Peer> &peer) {
    assert(peer != nullptr);

    auto entity = librg_entity_find(&_context, peer->_peer);
    if (entity == nullptr) {
        return nullptr;
    }

    return getEntity(entity);
}

std::vector<std::shared_ptr<librg_cpp::Entity>> librg_cpp::Context::getEntities(uint64_t flags) {
    _collectEntities.clear();

    librg_entity_iterate(&_context, flags, collectEntity);

    return _collectEntities;
}

std::vector<std::shared_ptr<librg_cpp::Entity>> librg_cpp::Context::getStreamedEntities(const std::shared_ptr<Entity> &entity) {
    assert(entity != nullptr);

    librg_entity_id *result;
    auto count = librg_entity_query(&_context, entity->id(), &result);

    std::vector<std::shared_ptr<Entity>> entities(count);

    for (size_t i = 0; i < count; i++) {
        entities.push_back(getEntity(result[i]));
    }

    return entities;
}

double librg_cpp::Context::time() {
    return librg_time_now(&_context);
}

void librg_cpp::Context::reset() {
    _context.mode = LIBRG_MODE_SERVER;
    _context.tick_delay = 32;
    _context.world_size = zpl_vec3f(5000.f, 5000.f, 5000.f);
    _context.min_branch_size = zpl_vec3f(50.f, 50.f, 50.f);
    _context.max_connections = 16;
    _context.max_entities = 8192;
}

void librg_cpp::Context::setUserData(void *ptr) {
    _context.user_data = ptr;
}

void *librg_cpp::Context::userData() const {
    return _context.user_data;
}

std::shared_ptr<librg_cpp::Peer> librg_cpp::Context::getPeer(librg_peer *value) {
    assert(value != nullptr);

    auto peer = _peerPool->get(value);
    if (peer == nullptr) {
        peer = std::shared_ptr<Peer>(new Peer(value));

        _peerPool->add(value, peer);
    }

    return peer;
}

std::shared_ptr<librg_cpp::Entity> librg_cpp::Context::getEntity(librg_entity *value) {
    assert(value != nullptr);

    auto entity = _entityPool->get(value);
    if (entity == nullptr) {
        entity = std::shared_ptr<Entity>(new Entity(value, shared_from_this()));

        _entityPool->add(value, entity);
    }

    return entity;
}

void librg_cpp::Context::collectEntity(struct librg_ctx *ctx, struct librg_entity *entity) {
    assert(ctx != nullptr);
    assert(entity != nullptr);

    auto context = reinterpret_cast<Host *>(ctx->user_data)->_context;
    assert(context != nullptr);

    auto wrappedEntity = context->getEntity(entity);
    if (wrappedEntity == nullptr) {
        return;
    }

    context->_collectEntities.push_back(wrappedEntity);
}
