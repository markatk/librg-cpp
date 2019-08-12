/*
 * File: pool.h
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

#include <map>
#include <memory>
#include <librg.h>
#include <stdexcept>
#include <cassert>

namespace librg_cpp {
    class Context;

    template<class T, class P>
    class Pool {
    private:
        std::map<T *, std::shared_ptr<P>> _entries;

    public:
        Pool() = default;
        virtual ~Pool() = default;

        void add(T *value, const std::shared_ptr<P> &entry) {
            assert(value != nullptr);
            assert(entry != nullptr);

            _entries[value] = entry;
        }

        std::shared_ptr<P> get(T *value) const {
            assert(value != nullptr);

            try {
                return _entries.at(value);
            } catch (std::out_of_range &) {
                return nullptr;
            }
        }
    };
}
