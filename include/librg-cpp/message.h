/*
 * File: message.h
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

namespace librg_cpp {
    class Context;
    class Data;

    class Message {
    private:
        librg_message *_message;
        std::shared_ptr<Context> _context;
        std::shared_ptr<Data> _data;

    public:
        Message(librg_message *message, const std::shared_ptr<Context> &context);
        virtual ~Message() = default;

        [[nodiscard]] uint32_t id() const;
        [[nodiscard]] std::shared_ptr<Context> context() const;
        [[nodiscard]] std::shared_ptr<Data> data() const;

        void setUserData(void *ptr);
        [[nodiscard]] void *userData() const;
    };
}
