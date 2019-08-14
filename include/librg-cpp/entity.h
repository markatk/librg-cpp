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

    class Entity {
    private:
        librg_entity *_entity;
        bool _initialized;
        std::shared_ptr<Context> _context;

    public:
        Entity(uint32_t type, const std::shared_ptr<Context> &context);
        virtual ~Entity();

        uint32_t id() const;
        uint32_t type() const;
        uint64_t flags() const;

#ifdef LIBRG_CPP_USE_LINALG
        void setPosition(linalg::aliases::float3 position);
        linalg::aliases::float3 position() const;
#else
        void setPosition(zpl_vec3 position);
        zpl_vec3 position() const;
#endif

        void setControlPeer(const std::shared_ptr<Peer> &peer);
        void removeControlPeer();
        void ignoreNextControlUpdate();
        std::shared_ptr<Peer> controlPeer() const;

#ifdef LIBRG_FEATURE_ENTITY_VISIBILITY
        void setVisibility(librg_visibility state);
        librg_visibility visibility() const;
        void setVisibilityFor(const std::shared_ptr<Entity> &target, librg_visibility state);
        librg_visibility visibilityFor(const std::shared_ptr<Entity> &target) const;
#endif

#ifdef LIBRG_FEATURE_VIRTUAL_WORLDS
        void setWorld(uint32_t world);
        uint32_t world() const;
#endif

        bool isAlive() const;
        bool isClient() const;
        bool hasVisibility() const;
        bool hasQueried() const;
        bool isControlled() const;
        bool isControlRequested() const;
        bool isMarkedRemoval() const;
        bool isUnused() const;

    private:
        Entity(librg_entity *entity, const std::shared_ptr<Context> &context);

        friend class Context;
    };
}
