/*
 * File: data.cpp
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

TEST_CASE("Initialization", "[data]") {
    librg_cpp::Data data;

    REQUIRE(data.readPosition() == 0);
    REQUIRE(data.writePosition() == 0);

    // librg default value
    REQUIRE(data.capacity() == 1024);
}

TEST_CASE("Capacity grow", "[data]") {
    librg_cpp::Data data;

    // librg default value
    REQUIRE(data.capacity() == 1024);

    data.grow(2048);
    REQUIRE(data.capacity() >= 2048);
}

TEST_CASE("Set read and write positions", "[data]") {
    librg_cpp::Data data;

    REQUIRE(data.readPosition() == 0);
    REQUIRE(data.writePosition() == 0);

    data.setWritePosition(12);
    REQUIRE(data.readPosition() == 0);
    REQUIRE(data.writePosition() == 12);

    data.setReadPosition(28);
    REQUIRE(data.readPosition() == 28);
    REQUIRE(data.writePosition() == 12);
}

TEST_CASE("Reset data", "[data]") {
    librg_cpp::Data data;

    data.setWritePosition(55);
    data.setReadPosition(94);

    REQUIRE(data.writePosition() == 55);
    REQUIRE(data.readPosition() == 94);

    data.reset();

    REQUIRE(data.writePosition() == 0);
    REQUIRE(data.readPosition() == 0);
}

TEMPLATE_TEST_CASE_SIG("Integer write and read templates", "[data]", ((typename T, int64_t V), T, V), (int8_t, -64), (uint8_t, 33), (int16_t, -635),
        (uint16_t, 33224), (int32_t, 23782373), (uint32_t, 4), (int64_t, -123721482), (uint64_t, 21472473), (float, 4323), (double, -434)) {
    librg_cpp::Data data;

    data.write<T>(V);
    REQUIRE(data.read<T>() == V);
}

TEMPLATE_TEST_CASE_SIG("Integer write and read templates at position", "[data]", ((typename T, int64_t V), T, V), (int8_t, -56), (uint8_t, 65), (int16_t, -6187),
        (uint16_t, 31138), (int32_t, 617861), (uint32_t, 628), (int64_t, -3871), (uint64_t, 31741387), (float, 45645), (double, -45345)) {
    librg_cpp::Data data;

    data.writeAt<T>(V, 133);
    REQUIRE(data.readAt<T>(133) == V);
}

TEST_CASE("Float write and read", "[data]") {
    librg_cpp::Data data;

    data.write<float>(32.32f);
    REQUIRE(data.read<float>() == 32.32f);
}

TEST_CASE("Double write and read", "[data]") {
    librg_cpp::Data data;

    data.write<double>(132532.3287);
    REQUIRE(data.read<double>() == 132532.3287);
}

TEST_CASE("Boolean write and read", "[data]") {
    librg_cpp::Data data;

    data.write<bool>(true);
    REQUIRE(data.read<bool>() == true);

    data.write<bool>(false);
    REQUIRE(data.read<bool>() == false);
}

TEST_CASE("Read and write position changes", "[data]") {
    librg_cpp::Data data;

    REQUIRE(data.readPosition() == 0);
    REQUIRE(data.writePosition() == 0);

    data.write<int32_t>(264);
    REQUIRE(data.writePosition() == sizeof(int32_t));
    REQUIRE(data.readPosition() == 0);

    data.write<int64_t>(-845);
    REQUIRE(data.writePosition() == sizeof(int32_t) + sizeof(int64_t));
    REQUIRE(data.readPosition() == 0);

    REQUIRE(data.read<int32_t>() == 264);
    REQUIRE(data.writePosition() == sizeof(int32_t) + sizeof(int64_t));
    REQUIRE(data.readPosition() == sizeof(int32_t));

    REQUIRE(data.read<int64_t>() == -845);
    REQUIRE(data.writePosition() == sizeof(int32_t) + sizeof(int64_t));
    REQUIRE(data.readPosition() == sizeof(int32_t) + sizeof(int64_t));
}
