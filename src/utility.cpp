/*
 * File: utility.cpp
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

#include "utility.h"

void librg_cpp::setOption(librg_options option, uint32_t value) {
    librg_option_set(option, value);
}

uint32_t librg_cpp::getOption(librg_options option) {
    return librg_option_get(option);
}

double librg_cpp::standardDeviation(std::vector<double> values) {
    return librg_standard_deviation(values.data(), values.size());
}
