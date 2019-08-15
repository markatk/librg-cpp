/*
 * File: message.h
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
#include <memory>

namespace librg_cpp {
    class Context;
    class Data;
    class Peer;

    /**
     * A single message send between server and client.
     *
     * Messages are custom events defined by the user. For librg events use see the event class.
     */
    class Message {
    private:
        librg_message *_message;
        std::shared_ptr<Context> _context;
        std::shared_ptr<Data> _data;
        std::shared_ptr<Peer> _peer;

    public:
        /**
         * Cleanup message.
         */
        virtual ~Message() = default;

        /**
         * Get identifier of the message.
         *
         * Message identifiers are expected to be LIBRG_EVENT_LAST or higher.
         *
         * @return Identifier of the message.
         */
        uint32_t id() const;

        /**
         * Get the context used by the message.
         *
         * For more information see context tutorial.
         * // TODO: Add context tutorial
         *
         * @return Context used by the message.
         */
        std::shared_ptr<Context> context() const;

        /**
         * Get data of the message.
         *
         * @return Data of the message.
         */
        std::shared_ptr<Data> data() const;

        /**
         * Get the peer of the message.
         *
         * The peer identifies who send the message. On server side it can be used to identify the client, on client side this is always the server.
         *
         * @return Peer of the message.
         */
        std::shared_ptr<Peer> peer() const;

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

    private:
        Message(librg_message *message, const std::shared_ptr<Context> &context);

        friend class Host;
    };
}
