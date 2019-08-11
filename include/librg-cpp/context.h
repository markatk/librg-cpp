/*
 * File: context.h
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

#include <librg.h>

namespace librg_cpp {
    class Context {
    private:
        librg_ctx _context;
        bool _initialized;

    public:
        explicit Context(bool isServer = true, double tickDelay = 32.0, unsigned short maxClients = 16);
        virtual ~Context();

        int initialize();
        void deinitialize();
        [[nodiscard]] bool isInitialized() const;

        void setServer(bool isServer);
        void setTickDelay(double delay);
        void setMaxClients(unsigned short maxClients);
        void setMaxEntities(unsigned short maxClients);
        [[nodiscard]] bool isServer() const;
        [[nodiscard]] double tickDelay() const;
        [[nodiscard]] unsigned short maxClients() const;
        [[nodiscard]] unsigned short maxEntities() const;

        void reset();

    private:
        void setUserData(void *ptr);
        [[nodiscard]] void *userData() const;

        friend class Host;
        friend class Entity;
    };
}
