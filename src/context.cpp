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

librg_cpp::Context::Context(bool isServer, double tickDelay, unsigned short maxClients) : _context({0}) {
    _initialized = false;

    reset();

    setServer(isServer);
    setTickDelay(tickDelay);
    setMaxClients(maxClients);
}

librg_cpp::Context::~Context() {
    deinitialize();
}

int librg_cpp::Context::initialize() {
    if (isInitialized()) {
        return -1;
    }

    return librg_init(&_context);
}

void librg_cpp::Context::deinitialize() {
    if (isInitialized() == false) {
        return;
    }

    librg_free(&_context);
}

bool librg_cpp::Context::isInitialized() const {
    return _initialized;
}

void librg_cpp::Context::setServer(bool isServer) {
    _context.mode = isServer ? LIBRG_MODE_SERVER : LIBRG_MODE_CLIENT;
}

void librg_cpp::Context::setTickDelay(double delay) {
    _context.tick_delay = delay;
}

void librg_cpp::Context::setMaxClients(unsigned short maxClients) {
    _context.max_connections = maxClients;
}

void librg_cpp::Context::setMaxEntities(unsigned short maxEntities) {
    _context.max_entities = maxEntities;
}

bool librg_cpp::Context::isServer() const {
    return _context.mode == LIBRG_MODE_SERVER;
}

double librg_cpp::Context::tickDelay() const {
    return _context.tick_delay;
}

unsigned short librg_cpp::Context::maxClients() const {
    return _context.max_connections;
}

unsigned short librg_cpp::Context::maxEntities() const {
    return _context.max_entities;
}

void librg_cpp::Context::reset() {
    _context.mode = LIBRG_MODE_SERVER;
    _context.tick_delay = 32;
    _context.world_size = zpl_vec3f(5000.f, 5000.f, 5000.f);
    _context.min_branch_size = zpl_vec3f(50.f, 50.f, 50.f);
    _context.max_connections = 16;
    _context.max_entities = 8192;
}