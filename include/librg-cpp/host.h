/*
 * File: host.h
 * Author: MarkAtk
 * Date: 05.08.2019
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

#include <memory>
#include <librg.h>

namespace librg_cpp {
    const unsigned int MAX_HOST_LENGTH = 64;

    class Context;

    class Host {
    protected:
        std::shared_ptr<Context> _context;
        librg_address _address;
        char _host[MAX_HOST_LENGTH + 1];

    public:
        explicit Host(std::shared_ptr<Context> context);
        virtual ~Host() = default;

        void tick();

        [[nodiscard]] bool isConnected() const;

    protected:
        [[nodiscard]] librg_ctx *context() const;
    };
}
