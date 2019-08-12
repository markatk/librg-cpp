/*
 * File: host.h
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

#pragma once

#include <memory>
#include <librg.h>
#include <functional>
#include <map>

namespace librg_cpp {
    const unsigned int MAX_HOST_LENGTH = 64;

    class Context;
    class Event;
    class Message;

    class Host {
    protected:
        std::shared_ptr<Context> _context;
        librg_address _address;
        char _host[MAX_HOST_LENGTH + 1];

        std::map<int, std::function<void(const std::unique_ptr<Event> &)>> _eventCallbacks;
        std::map<int, std::function<void(const std::unique_ptr<Message> &)>> _messageCallbacks;

    public:
        explicit Host(std::shared_ptr<Context> context);
        virtual ~Host() = default;

        void tick();

        [[nodiscard]] bool isConnected() const;

    protected:
        void sendMessageToAll(uint32_t id, void *data, size_t size);
        void sendMessageInStream(uint32_t id, uint32_t entityId, void *data, size_t size);

        virtual void onConnectionInitialize(const std::unique_ptr<Event> &event);
        virtual void onConnectionRequest(const std::unique_ptr<Event> &event);
        virtual void onConnectionRefuse(const std::unique_ptr<Event> &event);
        virtual void onConnectionAccept(const std::unique_ptr<Event> &event);
        virtual void onConnectionDisconnect(const std::unique_ptr<Event> &event);
        virtual void onConnectionTimeout(const std::unique_ptr<Event> &event);
        virtual void onConnectionTimeSync(const std::unique_ptr<Event> &event);
        virtual void onEntityCreate(const std::unique_ptr<Event> &event);
        virtual void onEntityUpdate(const std::unique_ptr<Event> &event);
        virtual void onEntityRemove(const std::unique_ptr<Event> &event);
        virtual void onClientStreamerAdd(const std::unique_ptr<Event> &event);
        virtual void onClientStreamerRemove(const std::unique_ptr<Event> &event);
        virtual void onClientStreamerUpdate(const std::unique_ptr<Event> &event);

        void registerEvent(int id, std::function<void(const std::unique_ptr<Event> &)> callback);
        void registerMessage(int id, std::function<void(const std::unique_ptr<Message> &)> callback);

        [[nodiscard]] librg_ctx *context() const;

    private:
        static void onEvent(librg_event *event);
        static void onMessage(librg_message *message);
    };
}
