/*
 * File: utility.h
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
#include <vector>

namespace librg_cpp {
    /**
     * Set the global option.
     *
     * @param option Option to set the value for.
     * @param value Value to set for given option.
     */
    void setOption(librg_options option, uint32_t value);

    /**
     * Get the global option.
     *
     * @param option Option to get the value of.
     * @return Value of the given option.
     */
    uint32_t getOption(librg_options option);

    /**
     * Calculate standard deviation from given values.
     *
     * @param values Values to get standard deviation for.
     * @return Standard deviation of the given values.
     */
    double standardDeviation(std::vector<double> values);
}
