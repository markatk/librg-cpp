/*
 * File: entity.h
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

#ifdef LIBRG_CPP_USE_LINALG
#include <linalg.h>
#endif

namespace librg_cpp {
    class Context;
    class Peer;

    /**
     * Entity represent everything object in the world to ne synchronized.
     *
     * Entities can either be automatically created (each client has one) or be manually created with context.
     */
    class Entity {
    private:
        librg_entity *_entity;
        bool _initialized;
        std::shared_ptr<Context> _context;

    public:
        /**
         * Cleanup entity.
         */
        virtual ~Entity();

        /**
         * Get the identifier of the entity.
         *
         * @attention Entity identifier may be reused when the entity is destroyed.
         *
         * @return Identifier of the entity.
         */
        uint32_t id() const;

        /**
         * Get the type of the entity.
         *
         * @return Type of the entity.
         */
        uint32_t type() const;

        /**
         * Get the flags of the entity.
         *
         * Possible values are:
         * - LIBRG_ENTITY_ALIVE = 1
         * - LIBRG_ENTITY_CLIENT = 2
         * - LIBRG_ENTITY_VISIBILITY = 4
         * - LIBRG_ENTITY_QUERIED = 8
         * - LIBRG_ENTITY_CONTROLLED = 16
         * - LIBRG_ENTITY_CONTROL_REQUESTED = 32
         * - LIBRG_ENTITY_MARKED_REMOVAL = 64
         * - LIBRG_ENTITY_UNUSED = 128
         * // TODO: Add entity flag documentation
         *
         * @return Flags of the entity.
         */
        uint64_t flags() const;

#ifdef LIBRG_CPP_USE_LINALG
        /**
         * Set the position of the entity.
         *
         * @attention The position must be inside the world size set in context.
         *
         * @param position Position of the entity.
         */
        void setPosition(linalg::aliases::float3 position);

        /**
         * Get the position of the entity.
         *
         * @return Position of the entity.
         */
        linalg::aliases::float3 position() const;
#else
        /**
         * Set the position of the entity.
         *
         * @attention The position must be inside the world size set in context.
         *
         * @param position Position of the entity.
         */
        void setPosition(zpl_vec3 position);

        /**
         * Get the position of the entity.
         *
         * @return Position of the entity.
         */
        zpl_vec3 position() const;
#endif

        /**
         * Set streaming range of the entity.
         *
         * The streaming range determines how far other entities can see this entity.
         *
         * @param range Stream range of the entity.
         */
        void setStreamRange(float range);

        /**
         * Get the streaming range of the entity.
         *
         * The streaming range determines how far other entities can see this entity.
         *
         * @return Stream range of the entity.
         */
        float streamRange() const;

        /**
         * Set a peer to control the entity.
         *
         * The peer is responsible for synchronizing the entity instead of the server. For more information see client synchronization tutorial.
         * // TODO: Add client sync tutorial
         *
         * @attention This can only be set on the server side.
         *
         * @param peer Peer to control the entity with.
         */
        void setControlPeer(const std::shared_ptr<Peer> &peer);

        /**
         * Remove any peer to control from the entity.
         *
         * For more information see client synchronization tutorial.
         * // TODO: Add client sync tutorial
         *
         * @attention This can only be set on the server side.
         */
        void removeControlPeer();

        /**
         * Ignore next (multiple) client updates for the entity.
         *
         * The update events are ignored immediately and will be accepted again after a few ticks (most times 2-3 messages are ignored).
         * In the time of the ignore the server is responsible for synchronizing the entity.
         *
         * This method may be used to force any server-side update for a client controlled entity.
         *
         * For more information see client synchronization tutorial.
         * // TODO: Add client sync tutorial
         *
         * @attention This can only be set on the server side.
         */
        void ignoreNextControlUpdate();

        /**
         * Get the controlling peer of the entity.
         *
         * For more information see client synchronization tutorial.
         * // TODO: Add client sync tutorial
         *
         * @attention This can only be set on the server side.
         *
         * @return Controlling peer or null if the entity is not controlled by any client.
         */
        std::shared_ptr<Peer> controlPeer() const;

#ifdef LIBRG_FEATURE_ENTITY_VISIBILITY
        /**
         * Set the global visibility state of the entity.
         *
         * @attention This can only be set on the server side.
         *
         * @param state Visibility state of the entity.
         */
        void setVisibility(librg_visibility state);

        /**
         * Get the global visibility state of the entity.
         *
         * @attention This can only be get on the server side.
         *
         * @return Visibility state of the entity.
         */
        librg_visibility visibility() const;

        /**
         * Set the visibility state of the entity for a given target.
         *
         * This overwrites the global visibility state.
         *
         * @attention This can only be set on the server side.
         *
         * @param target Target to set the visibility for.
         * @param state Overwritten visibility state of the entity.
         */
        void setVisibilityFor(const std::shared_ptr<Entity> &target, librg_visibility state);

        /**
         * Get the visibility state of the entity for the given target.
         *
         * If the target is the entity LIBRG_DEFAULT_VISIBILITY is returned.
         *
         * @attention This can only be get on the server side.
         *
         * @param target Target to get the visibility for.
         * @return Overwritten visibility state for the target or global visibility of the entity.
         */
        librg_visibility visibilityFor(const std::shared_ptr<Entity> &target) const;
#endif

#ifdef LIBRG_FEATURE_VIRTUAL_WORLDS
        /**
         * Set the virtual world for the entity.
         *
         * @param world Virtual world for the entity.
         */
        void setWorld(uint32_t world);

        /**
         * Get the virtual world of the entity.
         *
         * @return Virtual world of the entity.
         */
        uint32_t world() const;
#endif

        /**
         * Check if the entity belongs to a client.
         *
         * Client entities are special as they are automatically created and must not be destroyed at any time (they are automtically destroyed when the client
         * disconnects).
         *
         * @return True if the entity belongs to a client, otherwise false.
         */
        bool isClient() const;

        /**
         * Check if the entity has visibility overwrites set.
         *
         * @return True if the entity has any visibility overwrites for any other entity, otherwise false.
         */
        bool hasVisibility() const;

        /**
         * Check if the entity is controlled by any client.
         *
         * For more information see client synchronization tutorial.
         * // TODO: Add client sync tutorial
         *
         * @return True if the entity is controlled by a client, otherwise false.
         */
        bool isControlled() const;

        /**
         * Check if the control of the entity has been requested.
         *
         * This is true when the server assigns a client to synchronize the entity but the request was not send yet.
         *
         * @return True when the control was requested, otherwise false.
         */
        bool isControlRequested() const;

    private:
        Entity(uint32_t type, const std::shared_ptr<Context> &context);
        Entity(librg_entity *entity, const std::shared_ptr<Context> &context);

        void destroy();

        friend class Context;
    };
}
