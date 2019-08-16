/*
 * File: context.cpp
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

TEST_CASE("Default properties", "[context]") {
    librg_cpp::Context context;

    // default constructor values
    REQUIRE(context.isServer() == true);
    REQUIRE(context.tickDelay() == 32.0);
    REQUIRE(context.maxClients() == 16);

    // default values
    REQUIRE(context.worldSize() == linalg::aliases::float3(5000.f));
    REQUIRE(context.minBranchSize() == linalg::aliases::float3(50.f));
    REQUIRE(context.maxEntities() == 8192);
}

TEST_CASE("Change properties", "[context]") {
    librg_cpp::Context context(false, 64.0, 32);

    REQUIRE(context.isServer() == false);
    REQUIRE(context.tickDelay() == 64.0);
    REQUIRE(context.maxClients() == 32);

    context.setWorldSize(linalg::aliases::float3(1000.f, 2000.f, 3000.f));
    REQUIRE(context.worldSize() == linalg::aliases::float3(1000.f, 2000.f, 3000.f));

    context.setMinBranchSize(linalg::aliases::float3(10.f, 20.f, 30.f));
    REQUIRE(context.minBranchSize() == linalg::aliases::float3(10.f, 20.f, 30.f));

    context.setMaxEntities(10000);
    REQUIRE(context.maxEntities() == 10000);
}

TEST_CASE("Property reset", "[context]") {
    librg_cpp::Context context(false, 44.0, 1);
    context.setWorldSize(linalg::aliases::float3(100.f));
    context.setMinBranchSize(linalg::aliases::float3(10.f));
    context.setMaxEntities(10);

    context.reset();

    REQUIRE(context.isServer() == true);
    REQUIRE(context.tickDelay() == 32.0);
    REQUIRE(context.maxClients() == 16);
    REQUIRE(context.worldSize() == linalg::aliases::float3(5000.f));
    REQUIRE(context.minBranchSize() == linalg::aliases::float3(50.f));
    REQUIRE(context.maxEntities() == 8192);
}

TEST_CASE("Initialization", "[context]") {
    librg_cpp::Context context;

    REQUIRE(context.initialize() == LIBRG_CPP_NO_ERROR);
    REQUIRE(context.isInitialized() == true);

    context.deinitialize();
    REQUIRE(context.isInitialized() == false);
}

TEST_CASE("Execution time", "[context]") {
    librg_cpp::Context context;

    REQUIRE(context.time() >= 0.0);
}
