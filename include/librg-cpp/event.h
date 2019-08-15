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

    /**
     * A single event send between server and client.
     *
     * Events are defined by librg and handle general communication. For custom events use see messages.
     */
    class Event {
    private:
        librg_event *_event;
        std::shared_ptr<Context> _context;
        std::shared_ptr<Data> _data;
        std::shared_ptr<Entity> _entity;
        std::shared_ptr<Peer> _peer;

    public:
        /**
         * Cleanup event.
         */
        virtual ~Event() = default;

        /**
         * Identifier of the event.
         *
         * Event identifiers are expected to be lower than LIBRG_EVENT_LAST.
         *
         * @return Identifier of the event.
         */
        uint32_t id() const;

        /**
         * Get the context used by the event.
         *
         * For more information see context tutorial.
         * // TODO: Add context tutorial
         *
         * @return Context used by the event.
         */
        std::shared_ptr<Context> context() const;

        /**
         * Get the data of the event.
         *
         * @return Data of the event.
         */
        std::shared_ptr<Data> data() const;

        /**
         * Get the entity of the event.
         *
         * @return Entity of the event.
         */
        std::shared_ptr<Entity> entity() const;

        /**
         * Get the peer of the event.
         *
         * The peer identifies who send the event. On server side it can be used to identify the client, on client side this is always the server.
         *
         * @return Peer of the event.
         */
        std::shared_ptr<Peer> peer() const;

        /**
         * Get the flags of the event.
         *
         * Possible flag values are:
         * - LIBRG_EVENT_REJECTED = 1
         * - LIBRG_EVENT_REJECTABLE = 2
         * - LIBRG_EVENT_REMOTE = 4
         * - LIBRG_EVENT_LOCAL = 8
         * // TODO: Add event flag documentation
         *
         * @return Flags of the event.
         */
        uint64_t flags() const;

        /**
         * Set a custom user data.
         *
         * @param ptr Pointer to the custom data.
         */
        void setUserData(void *ptr);

        /**
         * Get the custom user data.
         *
         * @return Pointer of the custom data.
         */
        void *userData() const;

        /**
         * Reject the event.
         *
         * If the event is not rejectable, nothing happens.
         */
        void reject();

        /**
         * Check if the event was rejected.
         *
         * @return True if the event was rejected, otherwise false.
         */
        bool isRejected() const;

        /**
         * Check if the event was not rejected.
         *
         * @return True if the event was not rejected, otherwise false.
         */
        bool isSucceeded() const;

        /**
         * Check if the event is rejectable.
         *
         * This is independent of the actual reject state.
         *
         * @return True if the event can be rejected, otherwise false.
         */
        bool isRejectable() const;

        /**
         * Check if the event is a remote event.
         *
         * Remote events are always received events.
         *
         * @return True if the event is a remote event, otherwise false.
         */
        bool isRemote() const;

        /**
         * Check if the event is a local event.
         *
         * Local events are always send events.
         *
         * @return True if the event is a local event, otherwise false.
         */
        bool isLocal() const;

    private:
        Event(librg_event *event, const std::shared_ptr<Context> &context);

        friend class Host;
    };
}
