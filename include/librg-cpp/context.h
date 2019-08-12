/*
 * File: context.h
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

#pragma once

#include <librg.h>
#include <memory>

namespace librg_cpp {
    template<class T, class P>
    class Pool;

    class Peer;
    class Entity;

    class Context : private std::enable_shared_from_this<Context> {
    private:
        librg_ctx _context;
        bool _initialized;

        std::shared_ptr<Pool<librg_peer, Peer>> _peerPool;
        std::shared_ptr<Pool<librg_entity, Entity>> _entityPool;

    public:
        explicit Context(bool isServer = true, double tickDelay = 32.0, unsigned short maxClients = 16);
        virtual ~Context();

        int initialize();
        void deinitialize();
        bool isInitialized() const;

        void setServer(bool isServer);
        void setTickDelay(double delay);
        void setMaxClients(unsigned short maxClients);
        void setMaxEntities(unsigned short maxClients);
        bool isServer() const;
        double tickDelay() const;
        unsigned short maxClients() const;
        unsigned short maxEntities() const;

        void reset();

    private:
        void setUserData(void *ptr);
        void *userData() const;

        std::shared_ptr<Peer> getPeer(librg_peer *peer);
        std::shared_ptr<Entity> getEntity(librg_entity *entity);

        friend class Host;
        friend class Entity;
        friend class Event;
        friend class Message;
    };
}
