/*
 * File: result.h
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

// TODO: Change result into enum?
// TODO: Document results
#define LIBRG_CPP_NO_ERROR                      0
#define LIBRG_CPP_UNKNOWN_ERROR                 1
#define LIBRG_CPP_CONTEXT_UNINITIALIZED         2
#define LIBRG_CPP_CONTEXT_INITIALIZE_FAILED     3
#define LIBRG_CPP_CONTEXT_ALREADY_INITIALIZED   4
#define LIBRG_CPP_HOST_CREATION_FAILED          5
#define LIBRG_CPP_SERVER_ALREADY_STARTED        6
#define LIBRG_CPP_CLIENT_PEER_CREATION_FAILED   7
#define LIBRG_CPP_CLIENT_ALREADY_CONNECTED      8
