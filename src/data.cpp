/*
 * File: data.cpp
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

#include "data.h"

#include <cassert>

#define GEN_DATA_METHODS(NAME, TYPE, FUNC) void librg_cpp::Data::write ## NAME (TYPE value) { assert(_data != nullptr); librg_data_w ## FUNC (_data, value); } \
    void librg_cpp::Data::write ## NAME ## At(TYPE value, size_t pos) { assert(_data != nullptr); assert(pos >= 0); librg_data_w ## FUNC ## _at(_data, value, pos); } \
    TYPE librg_cpp::Data::read ## NAME () { assert(_data != nullptr); return librg_data_r ## FUNC (_data); } \
    TYPE librg_cpp::Data::read ## NAME ## At(size_t pos) { assert(data != nullptr); assert(pos >= 0); return librg_data_r ## FUNC ## _at(_data, pos); }

librg_cpp::Data::Data() {
    _data = librg_data_init_new();
    _initialized = true;
}

librg_cpp::Data::Data(librg_data *data) {
    assert(data != nullptr);

    _data = data;
    _initialized = false;
}

librg_cpp::Data::~Data() {
    if (_initialized == false) {
        return;
    }

    free();
}

void librg_cpp::Data::writePointer(void *pointer, size_t size) {
    assert(_data != nullptr);
    assert(pointer != nullptr);
    assert(size > 0);

    librg_data_wptr(_data, pointer, size);
}

void librg_cpp::Data::writePointerAt(void *pointer, size_t size, size_t position) {
    assert(_data != nullptr);
    assert(pointer != nullptr);
    assert(size > 0);
    assert(position >= 0);

    librg_data_wptr(_data, pointer, size);
}

bool librg_cpp::Data::readPointer(void *pointer, size_t size) {
    assert(_data != nullptr);
    assert(pointer != nullptr);
    assert(size > 0);

    return librg_data_rptr(_data, pointer, size);
}

bool librg_cpp::Data::readPointerAt(void *pointer, size_t size, size_t position) {
    assert(_data != nullptr);
    assert(pointer != nullptr);
    assert(size > 0);
    assert(position >= 0);

    return librg_data_rptr(_data, pointer, size);
}

GEN_DATA_METHODS(Int8, int8_t, i8)
GEN_DATA_METHODS(UInt8, uint8_t, u8)
GEN_DATA_METHODS(Int16, int16_t, i16)
GEN_DATA_METHODS(UInt16, uint16_t, u16)
GEN_DATA_METHODS(Int32, int32_t, i32)
GEN_DATA_METHODS(UInt32, uint32_t, u32)
GEN_DATA_METHODS(Int64, int64_t, i64)
GEN_DATA_METHODS(UInt64, uint64_t, u64)
GEN_DATA_METHODS(Float, float, f32)
GEN_DATA_METHODS(Double, double, f64)
GEN_DATA_METHODS(Bool, bool, b8)

void librg_cpp::Data::reset() {
    assert(_data != nullptr);

    librg_data_reset(_data);
}

void librg_cpp::Data::grow(size_t minSize) {
    assert(_data != nullptr);
    assert(minSize >= 0);

    librg_data_grow(_data, minSize);
}

void librg_cpp::Data::free() {
    assert(_data != nullptr);

    librg_data_free(_data);
}

void *librg_cpp::Data::raw() const {
    assert(_data != nullptr);

    return _data->rawptr;
}

void librg_cpp::Data::setWritePosition(size_t position) {
    assert(_data != nullptr);
    assert(position >= 0);

    librg_data_set_wpos(_data, position);
}

void librg_cpp::Data::setReadPosition(size_t position) {
    assert(_data != nullptr);
    assert(position >= 0);

    librg_data_set_rpos(_data, position);
}

size_t librg_cpp::Data::writePosition() const {
    assert(_data != nullptr);

    return librg_data_get_wpos(_data);
}

size_t librg_cpp::Data::readPosition() const {
    assert(_data != nullptr);

    return librg_data_get_rpos(_data);
}

size_t librg_cpp::Data::capacity() const {
    assert(_data != nullptr);

    return librg_data_capacity(_data);
}
