/*
 * File: entity.cpp
 * Author: MarkAtk
 * Date: 16.08.2019
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

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <librg-cpp/librg-cpp.h>

TEST_CASE("Entity", "[entity]") {
    auto context = std::make_shared<librg_cpp::Context>();

    REQUIRE(context->initialize() == LIBRG_CPP_NO_ERROR);

    SECTION("Create an entity") {
        auto entity = context->createEntity(0);

        REQUIRE(entity != nullptr);
        REQUIRE(entity->type() == 0);
        REQUIRE(entity->controlPeer() == nullptr);
        REQUIRE(entity->position() == linalg::aliases::float3());
        REQUIRE(entity->world() == 0);
    }

    SECTION("Destroy an entity") {
        auto entity = context->createEntity(0);

        REQUIRE(context->destroyEntity(entity) == true);
    }

    SECTION("Entity type") {
        auto entity = context->createEntity(12);

        REQUIRE(entity->type() == 12);
    }

    SECTION("Entity id assignment") {
        for (auto i = 0; i < 10; i++) {
            auto entity = context->createEntity(0);

            REQUIRE(entity != nullptr);
            REQUIRE(entity->id() == i);
        }
    }

    SECTION("Check flags") {
        auto entity = context->createEntity(0);

        REQUIRE(entity->flags() == LIBRG_ENTITY_ALIVE);
        REQUIRE(entity->isClient() == false);
        REQUIRE(entity->hasVisibility() == false);
        REQUIRE(entity->isControlled() == false);
        REQUIRE(entity->isControlRequested() == false);
    }

    SECTION("Set and get position") {
        auto entity = context->createEntity(0);

        REQUIRE(entity->position() == linalg::aliases::float3());

        entity->setPosition(linalg::aliases::float3(1.f, 2.f, 3.f));

        REQUIRE(entity->position() == linalg::aliases::float3(1.f, 2.f, 3.f));
    }
}
