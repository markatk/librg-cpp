/*
 * File: peer.cpp
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

#include "peer.h"

#include <cassert>

#define HOST_NAME_LENGTH 32

librg_cpp::Peer::Peer(librg_peer *peer) {
    assert(peer != nullptr);

    _peer = peer;
}

std::string librg_cpp::Peer::ip() const {
    assert(_peer != nullptr);

    char hostname[HOST_NAME_LENGTH + 1];
    std::string address = "unknown";

    if (enet_address_get_host_ip(&_peer->address, hostname, HOST_NAME_LENGTH) == 0) {
        address = std::string(hostname);
    }

    return address;
}
