/*
 * File: peer.h
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

#pragma once

#include <librg.h>
#include <string>
#include <memory>

namespace librg_cpp {
    /**
     * Peer represents a network peer connection.
     */
    class Peer {
    private:
        librg_peer *_peer;

    public:
        /**
         * Cleanup peer.
         */
        virtual ~Peer() = default;

        /**
         * Get IP address of the peer.
         *
         * If the address can not be resolved "unknown" is returned.
         *
         * @return Resolved address of the peer.
         */
        std::string ip() const;

    private:
        explicit Peer(librg_peer *peer);

        friend class Context;
        friend class Host;
        friend class Server;
        friend class Entity;
    };
}
