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

    class Host {
    protected:
        std::shared_ptr<Context> _context;
        librg_address _address;
        char _host[MAX_HOST_LENGTH + 1];

        // TODO: Wrap event with class
        std::map<int, std::function<void(librg_event *)>> _eventCallbacks;

    public:
        explicit Host(std::shared_ptr<Context> context);
        virtual ~Host() = default;

        void tick();

        [[nodiscard]] bool isConnected() const;

    protected:
        virtual void onConnectionInitialize(librg_event *event);
        virtual void onConnectionRequest(librg_event *event);
        virtual void onConnectionRefuse(librg_event *event);
        virtual void onConnectionAccept(librg_event *event);
        virtual void onConnectionDisconnect(librg_event *event);
        virtual void onConnectionTimeout(librg_event *event);
        virtual void onConnectionTimeSync(librg_event *event);
        virtual void onEntityCreate(librg_event *event);
        virtual void onEntityUpdate(librg_event *event);
        virtual void onEntityRemove(librg_event *event);
        virtual void onClientStreamerAdd(librg_event *event);
        virtual void onClientStreamerRemove(librg_event *event);
        virtual void onClientStreamerUpdate(librg_event *event);

        void registerEvent(int id, std::function<void(librg_event *)> callback);

        [[nodiscard]] librg_ctx *context() const;

    private:
        static void onEvent(librg_event *event);
    };
}
