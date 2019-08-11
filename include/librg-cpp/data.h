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

        void reset();
        void grow(size_t minSize);
        void free();

        void setWritePosition(size_t position);
        void setReadPosition(size_t position);
        size_t writePosition() const;
        size_t readPosition() const;
        size_t capacity() const;
    };
}
