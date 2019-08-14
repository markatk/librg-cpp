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
#include <vector>

#ifdef LIBRG_CPP_USE_LINALG
#include <linalg.h>
#endif

namespace librg_cpp {
    template<class T, class P>
    class Pool;

    class Peer;
    class Entity;

    /**
     * Library context.
     * 
     * This class is the main library context used by all classes.
     */
    class Context : private std::enable_shared_from_this<Context> {
    private:
        librg_ctx _context;
        bool _initialized;

        std::shared_ptr<Pool<librg_peer, Peer>> _peerPool;
        std::shared_ptr<Pool<librg_entity, Entity>> _entityPool;

        std::vector<std::shared_ptr<Entity>> _collectEntities;

    public:
        /**
         * Create a context.
         * 
         * This should be the first step using the library.
         * 
         * @param isServer If true the context is initialized as a server, otherwise as a client.
         * @param tickDelay Delay between update ticks.
         * @param maxClients Maximum nummer of clients.
         */
        explicit Context(bool isServer = true, double tickDelay = 32.0, uint16_t maxClients = 16);

        /**
         * Deconstruct the context.
         * 
         * If the context is still initialized it will be deinitialized.
         */
        virtual ~Context();

        /**
         *
         * 
         * @return
         */
        uint32_t initialize();

        /**
         * Cleanup the context.
         *
         * Hosts should be stopped before this, as this should be the last step in the application before termination.
         * If the context is already cleanup or has never been initialized, nothing happens.
         */
        void deinitialize();

        /**
         * Check if the context is initialized.
         *
         * @return True if the context is initialized, otherwise false.
         */
        bool isInitialized() const;

        /**
         * Set whether the context is initialized as server or client.
         *
         * @param isServer If true the context will be a for a server, otherwise for a client.
         */
        void setServer(bool isServer);

        /**
         * Set the network tick delay.
         *
         * The network tick delay is the time in milliseconds between update calls.
         * Default value is 32.
         *
         * @param delay Delay in milliseconds between updates.
         */
        void setTickDelay(double delay);

        /**
         * Set the maximum number of clients.
         *
         * This limits the number of clients connected at the same time.
         * Default value is 16.
         *
         * @param maxClients Maximum number of clients.
         */
        void setMaxClients(uint16_t maxClients);

        /**
         * Set the maximum number of entities.
         *
         * This limits the number of entities managed by the server at the same time.
         * Default value is 8192.
         *
         * @param maxEntities Maximum number of entities.
         */
        void setMaxEntities(uint16_t maxEntities);

        /**
         * Check whether the context is for a server.
         *
         * @return True if the context is set for a server, otherwise false.
         */
        bool isServer() const;

        /**
         * Get the network update delay.
         *
         * @return Update delay in milliseconds.
         */
        double tickDelay() const;

        /**
         * Get the maximum number of clients.
         *
         * @return Maximum number of clients.
         */
        uint16_t maxClients() const;

        /**
         * Get the maximum number of entities.
         *
         * @return Maximum number of entities.
         */
        uint16_t maxEntities() const;

#ifdef LIBRG_CPP_USE_LINALG
        /**
         * Set world size.
         *
         * Entities position are limited to the world size.
         *
         * @param size Size of the world.
         */
        void setWorldSize(linalg::aliases::float3 size);

        /**
         * Set the minimum branch size.
         *
         * @param size Minimum size of branches.
         */
        void setMinBranchSize(linalg::aliases::float3 size);

        /**
         * Get the world size.
         *
         * @return Size of the world.
         */
        linalg::aliases::float3 worldSize() const;

        /**
         * Get the minimum branch size.
         *
         * @return Minimum size of branches.
         */
        linalg::aliases::float3 minBranchSize() const;
#else
        /**
         * Set world size.
         *
         * Entities position are limited to the world size.
         *
         * @param size Size of the world.
         */
        void setWorldSize(zpl_vec3 size);

        /**
         * Set the minimum branch size.
         *
         * @param size Minimum size of branches.
         */
        void setMinBranchSize(zpl_vec3 size);

        /**
         * Get the world size.
         *
         * @return Size of the world.
         */
        zpl_vec3 worldSize() const;

        /**
         * Get the minimum branch size.
         *
         * @return Minimum size of branches.
         */
        zpl_vec3 minBranchSize() const;
#endif

        /**
         * Get an entity by it's id.
         *
         * @attention Entity id's may be reused when an entity is destroyed and a new one created.
         *
         * @param id Entity id of the entity to get.
         * @return An entity or null if none was found.
         */
        std::shared_ptr<Entity> getEntity(uint32_t id);

        /**
         * Get an entity by it's peer.
         *
         * Each peer has an entity associated with it which can be get with this.
         *
         * @param peer Network peer to get the entity for.
         * @return An entity (or null if none was found which is unlikely).
         */
        std::shared_ptr<Entity> getEntity(const std::shared_ptr<Peer> &peer);

        /**
         * Get all entities matching the given flags.
         *
         * @param flags Flags to match the entities against.
         * @return List of entities matching the given flags.
         */
        std::vector<std::shared_ptr<Entity>> getEntities(uint64_t flags);

        /**
         * Get all entities which are visible to the given target.
         *
         * @param entity Target entity to get the visible entities for.
         * @return List of entities visible to the target.
         */
        std::vector<std::shared_ptr<Entity>> getStreamedEntities(const std::shared_ptr<Entity> &entity);

        /**
         * Get the execution time.
         *
         * If the context is a server, the time since startup will be returned.
         * If the context is a client, the server sync time is returned.
         *
         * Ideally calling this on both sides will return the same time.
         *
         * @return Time in seconds.
         */
        double time();

        /**
         * Reset the context settings to default.
         *
         * Default settings:
         * - Mode: Server
         * - TickDelay: 32
         * - WorldSize: 5000
         * - MinBranchSize: 50
         * - MaxConnections: 16
         * - MaxEntities: 8192
         */
        void reset();

    private:
        void setUserData(void *ptr);
        void *userData() const;

        std::shared_ptr<Peer> getPeer(librg_peer *peer);
        std::shared_ptr<Entity> getEntity(librg_entity *entity);

        static void collectEntity(struct librg_ctx *context, struct librg_entity *entity);

        friend class Host;
        friend class Entity;
        friend class Event;
        friend class Message;
    };
}
