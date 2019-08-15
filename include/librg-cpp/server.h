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

    /**
     * Server class.
     *
     * In most cases create a subclass and overwrite existing event methods of this to handle incoming network events.
     */
    class Server : public Host {
    public:
        /**
         * Create a new network server.
         *
         * @attention The context needs to be setup for server.
         *
         * @param context Network context to work with.
         * @param port Port to listen on.
         * @param host Host interface to listen on. By default all interfaces are used.
         */
        Server(std::shared_ptr<Context> context, uint16_t port, const std::string &host = "::1");

        /**
         * Cleanup server.
         *
         * If the server is still running, it will be stopped and all clients will be disconnected.
         */
        ~Server() override;

        /**
         * Start the server.
         *
         * @attention The context must be initialized before calling this method.
         *
         * @return Returns LIBRG_CPP_NO_ERROR if the server was started, otherwise an error result.
         */
        uint32_t start();

        /**
         * Stop the server.
         *
         * If the server is not running, nothing happens.
         */
        void stop();

        /**
         * Kick a client.
         *
         * The peer must NOT be null.
         *
         * @param peer Peer to kick from the server.
         */
        void kick(const std::shared_ptr<Peer> &peer);

        /**
         * Send a message to a client.
         *
         * Use this method if you do your own serialization, see message tutorial.
         * // TODO: Add message tutorial
         *
         * @param id Identifier of the message.
         * @param peer Peer to send the message to.
         * @param data Raw data of the message.
         * @param size Size in bytes of the data.
         */
        void sendMessage(uint16_t id, const std::shared_ptr<Peer> &peer, void *data, size_t size) override;

        /**
         * Send a message to a client.
         *
         * Use this method if you want to use the librg serialization, see message tutorial.
         * // TODO: Add message tutorial
         *
         * @param id Identifier of the message.
         * @param peer Peer to send the message to.
         * @param data Data of the message.
         */
        void sendMessage(uint16_t id, const std::shared_ptr<Peer> &peer, const std::shared_ptr<Data> &data);

        /**
         * Send a message to all clients.
         *
         * Use this method if you do your own serialization, see message tutorial.
         * // TODO: Add message tutorial
         *
         * @param id Identifier of the message.
         * @param data Raw data of the message.
         * @param size Size in bytes of the data.
         */
        void sendMessageToAll(uint16_t id, void *data, size_t size) override;

        /**
         * Send a message to all clients.
         *
         * Use this method if you want to use the librg serialization, see message tutorial.
         * // TODO: Add message tutorial
         *
         * @param id Identifier of the message.
         * @param data Data of the message.
         */
        void sendMessageToAll(uint16_t id, const std::shared_ptr<Data> &data);

        /**
         * Send a message to all except one client.
         *
         * Use this method if you do your own serialization, see message tutorial.
         * // TODO: Add message tutorial
         *
         * @param id Identifier of the message.
         * @param peer Peer to not send the message to.
         * @param data Raw data of the message.
         * @param size Size in bytes of the data.
         */
        void sendMessageExcept(uint16_t id, const std::shared_ptr<Peer> &peer, void *data, size_t size) override;

        /**
         * Send a message to all except one client.
         *
         * Use this method if you want to use the librg serialization, see message tutorial.
         * // TODO: Add message tutorial
         *
         * @param id Identifier of the message.
         * @param peer Peer to not send the message to.
         * @param data Data of the message.
         */
        void sendMessageExcept(uint16_t id, const std::shared_ptr<Peer> &peer, const std::shared_ptr<Data> &data);

        /**
         * Send a message to all clients in streaming range of the given entity.
         *
         * Use this method if you do your own serialization, see message tutorial.
         * // TODO: Add message tutorial
         *
         * @param id Identifier of the message.
         * @param entity Target entity to stream the message from.
         * @param data Raw data of the message.
         * @param size Size in bytes of the data.
         */
        void sendMessageInStream(uint16_t id, const std::shared_ptr<Entity> &entity, void *data, size_t size) override;

        /**
         * Send a message to all clients in streaming range of the given entity.
         *
         * Use this method if you want to use the librg serialization, see message tutorial.
         * // TODO: Add message tutorial
         *
         * @param id Identifier of the message.
         * @param entity Target entity to stream the message from.
         * @param data Data of the message.
         */
        void sendMessageInStream(uint16_t id, const std::shared_ptr<Entity> &entity, const std::shared_ptr<Data> &data);

        /**
         * Send a message to all except one client in streaming range of the given entity.
         *
         * Use this method if you do your own serialization, see message tutorial.
         * // TODO: Add message tutorial
         *
         * @param id Identifier of the message.
         * @param entity Target entity to stream the message from.
         * @param peer Peer to not send the message to.
         * @param data Raw data of the message.
         * @param size Size in bytes of the data.
         */
        void sendMessageInStreamExcept(uint16_t id, const std::shared_ptr<Entity> &entity, const std::shared_ptr<Peer> &peer, void *data, size_t size) override;

        /**
         * Send a message to all except one client in streaming range of the given entity.
         *
         * Use this method if you want to use the librg serialization, see message tutorial.
         * // TODO: Add message tutorial
         *
         * @param id Identifier of the message.
         * @param entity Target entity to stream the message from.
         * @param peer Peer to not send the message to.
         * @param data Data of the message.
         */
        void sendMessageInStreamExcept(uint16_t id, const std::shared_ptr<Entity> &entity, const std::shared_ptr<Peer> &peer, const std::shared_ptr<Data> &data);

        /**
         * Set the port of the server.
         *
         * @param port Port of the server.
         */
        void setPort(uint16_t port);

        /**
         * Set the host interface of the server.
         *
         * @param host Host interface of the server.
         */
        void setHost(const std::string &host);

        /**
         * Get the port of the server.
         *
         * @return Port of the server.
         */
        uint16_t port() const;

        /**
         * Get the host interface of the server.
         *
         * @return Host interface of the server.
         */
        std::string host() const;
    };
}
