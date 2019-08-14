/*
 * File: client.h
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

#include "host.h"

#include <string>

namespace librg_cpp {
    class Data;

    /**
     * Client class.
     */
    class Client : public Host {
    public:
        /**
         * Create a new network client.
         *
         * @attention The context needs to be setup for client.
         *
         * @param context Network context to work with.
         */
        explicit Client(std::shared_ptr<Context> context);

        /**
         * Cleanup client.
         *
         * If the client is still connected the connection will be terminated.
         */
        ~Client() override;

        /**
         * Connect to a server.
         *
         * The methods returns on the start of the connection attempt and does NOT check for any timeout or accepted connection.
         * Use the event methods to check on the connection state.
         *
         * @param host Host to connect to.
         * @param port Port to connect to.
         * @return Returns LIBRG_CPP_NO_ERROR if the connection attempt is started, otherwise an error result.
         */
        int connect(const std::string &host, int32_t port);

        /**
         * Disconnect from the server.
         *
         * If there is no connection, nothing happens.
         */
        void disconnect();

        /**
         * Send a message to the server.
         *
         * Use this method if you do your own serialization.
         *
         * @param id Identifier of the message.
         * @param data Raw data of the message.
         * @param size Size in bytes of the message.
         */
        void sendMessage(uint16_t id, void *data, size_t size);

        /**
         * Send a message to the server.
         *
         * Use this method if you want to use the librg serialization.
         *
         * @param id Identifier of the message.
         * @param data Data of the message.
         */
        void sendMessage(uint16_t id, const std::shared_ptr<Data> &data);
    };
}
