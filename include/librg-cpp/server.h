/*
 * File: server.h
 * Author: MarkAtk
 * Date: 01.08.2019
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

#include <string>
#include <memory>
#include <librg.h>

namespace librg_cpp {
    const unsigned int MAX_HOST_LENGTH = 64;

    class Context;

    class Server {
    private:
        std::shared_ptr<Context> _context;
        librg_address _address;
        char _host[MAX_HOST_LENGTH + 1];

    public:
        Server(std::shared_ptr<Context> context, int port, const std::string &host = "::1");
        virtual ~Server();

        int start();
        void stop();
        [[nodiscard]] bool isStarted() const;
        void tick();

        void setPort(int port);
        void setHost(const std::string &host);
        [[nodiscard]] int port() const;
        [[nodiscard]] std::string host() const;

    private:
        [[nodiscard]] librg_ctx *context() const;
    };
}
