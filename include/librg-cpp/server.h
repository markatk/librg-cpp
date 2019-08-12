/*
 * File: server.h
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

#include "host.h"

#include <string>

namespace librg_cpp {
    class Peer;
    class Data;
    class Entity;

    class Server : public Host {
    public:
        Server(std::shared_ptr<Context> context, uint16_t port, const std::string &host = "::1");
        ~Server() override;

        uint32_t start();
        void stop();

        void kick(const std::shared_ptr<Peer> &peer);

        void sendMessage(uint16_t id, const std::shared_ptr<Peer> &peer, void *data, size_t size) override;
        void sendMessage(uint16_t id, const std::shared_ptr<Peer> &peer, const std::shared_ptr<Data> &data);
        void sendMessageToAll(uint16_t id, void *data, size_t size) override;
        void sendMessageToAll(uint16_t id, const std::shared_ptr<Data> &data);
        void sendMessageExcept(uint16_t id, const std::shared_ptr<Peer> &peer, void *data, size_t size) override;
        void sendMessageExcept(uint16_t id, const std::shared_ptr<Peer> &peer, const std::shared_ptr<Data> &data);
        void sendMessageInStream(uint16_t id, const std::shared_ptr<Entity> &entity, void *data, size_t size) override;
        void sendMessageInStream(uint16_t id, const std::shared_ptr<Entity> &entity, const std::shared_ptr<Data> &data);
        void sendMessageInStreamExcept(uint16_t id, const std::shared_ptr<Entity> &entity, const std::shared_ptr<Peer> &peer, void *data, size_t size) override;
        void sendMessageInStreamExcept(uint16_t id, const std::shared_ptr<Entity> &entity, const std::shared_ptr<Peer> &peer, const std::shared_ptr<Data> &data);

        void setPort(uint16_t port);
        void setHost(const std::string &host);
        uint16_t port() const;
        std::string host() const;
    };
}
