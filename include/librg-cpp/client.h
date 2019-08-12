/*
 * File: client.h
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

#include "host.h"

#include <string>

namespace librg_cpp {
    class Data;

    class Client : public Host {
    public:
        explicit Client(std::shared_ptr<Context> context);
        ~Client() override;

        int connect(const std::string &host, int port);
        void disconnect();

        void sendMessage(uint16_t id, void *data, size_t size);
        void sendMessage(uint16_t id, const std::shared_ptr<Data> &data);
    };
}
