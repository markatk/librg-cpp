/*
 * File: data.h
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

#pragma once

#include <librg.h>

#define DECL_DATA_METHODS(NAME, TYPE) void write ## NAME (TYPE value); \
    void write ## NAME ## At(TYPE value, size_t position); \
    TYPE read ## NAME (); \
    TYPE read ## NAME ## At (size_t position)

namespace librg_cpp {
    class Data {
    private:
        librg_data *_data;
        bool _initialized;

    public:
        Data();
        explicit Data(librg_data *data);
        virtual ~Data();

        void writePointer(void *pointer, size_t size);
        void writePointerAt(void *pointer, size_t size, size_t position);
        bool readPointer(void *pointer, size_t size);
        bool readPointerAt(void *pointer, size_t size, size_t position);

        DECL_DATA_METHODS(Int8, int8_t);
        DECL_DATA_METHODS(UInt8, uint8_t);
        DECL_DATA_METHODS(Int16, int16_t);
        DECL_DATA_METHODS(UInt16, uint16_t);
        DECL_DATA_METHODS(Int32, int32_t);
        DECL_DATA_METHODS(UInt32, uint32_t);
        DECL_DATA_METHODS(Int64, int64_t);
        DECL_DATA_METHODS(UInt64, uint64_t);
        DECL_DATA_METHODS(Float, float);
        DECL_DATA_METHODS(Double, double);
        DECL_DATA_METHODS(Bool, bool);

        void reset();
        void grow(size_t minSize);
        void free();

        void setWritePosition(size_t position);
        void setReadPosition(size_t position);
        [[nodiscard]] size_t writePosition() const;
        [[nodiscard]] size_t readPosition() const;
        [[nodiscard]] size_t capacity() const;
    };
}
