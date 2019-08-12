/*
 * File: event.h
 * Author: MarkAtk
 * Date: 11.08.2019
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
    class Data;
    class Context;
    class Entity;
    class Peer;

    class Event {
    private:
        librg_event *_event;
        std::shared_ptr<Context> _context;
        std::shared_ptr<Data> _data;
        std::shared_ptr<Entity> _entity;
        std::shared_ptr<Peer> _peer;

    public:
        Event(librg_event *event, const std::shared_ptr<Context> &context);
        virtual ~Event() = default;

        [[nodiscard]] uint32_t id() const;
        [[nodiscard]] std::shared_ptr<Context> context() const;
        [[nodiscard]] std::shared_ptr<Data> data() const;
        [[nodiscard]] std::shared_ptr<Entity> entity() const;
        [[nodiscard]] std::shared_ptr<Peer> peer() const;
        [[nodiscard]] uint64_t flags() const;

        void setUserData(void *ptr);
        [[nodiscard]] void *userData() const;

        void reject();
        [[nodiscard]] bool isRejected() const;
        [[nodiscard]] bool isSucceeded() const;
        [[nodiscard]] bool isRejectable() const;
        [[nodiscard]] bool isRemote() const;
        [[nodiscard]] bool isLocal() const;
    };
}
