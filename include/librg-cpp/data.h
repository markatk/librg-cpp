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
    /**
     * Data serialization class.
     *
     * Use this class to use the librg (de-)serialization for events and messages.
     */
    class Data {
    private:
        librg_data *_data;
        bool _initialized;

    public:
        /**
         * Create new empty data.
         */
        Data();

        /**
         * Cleanup data.
         */
        virtual ~Data();

        /**
         * Write data.
         *
         * @param value Value to write to the data.
         */
        template<typename T>
        void write(T &&value) {
            librg_data_wptr(_data, &value, sizeof(value));
        }

        /**
         * Write data at given position.
         *
         * @param value Value to write to the data.
         * @param position Position to write the data at.
         */
        template<typename T>
        void writeAt(T &&value, size_t position) {
            librg_data_wptr_at(_data, &value, sizeof(value), position);
        }

        /**
         * Read data.
         *
         * @attention If the data has not enough bytes left to read from, the default value will be returned.
         *
         * @return Value read from the data.
         */
        template<typename T>
        T read() {
            T value;

            librg_data_rptr(_data, &value, sizeof(value));

            return value;
        }

        /**
         * Read data at given position.
         *
         * @attention If the data has not enough bytes left to read from, the default value will be returned.
         *
         * @param position Position to read the data at.
         * @return Value read from the data.
         */
        template<typename T>
        T readAt(size_t position) {
            T value;

            librg_data_rptr_at(_data, &value, sizeof(value), position);

            return value;
        }

        /**
         * Reset the data.
         *
         * This clears every data written to and resets both read and write positions.
         *
         * @attention The capacity is NOT changed.
         */
        void reset();

        /**
         * Grow the data to the given minimum size.
         *
         * The actual size may be greater than given minimum size.
         *
         * @param minSize Minimum size to grow the data to.
         */
        void grow(size_t minSize);

        /**
         * Get the raw address of the data.
         *
         * @warning Use this with care and do not write at it at all.
         *
         * @return Raw address pointer of the data.
         */
        void *raw() const;

        /**
         * Set the write position of the data.
         *
         * @param position Write position of the data.
         */
        void setWritePosition(size_t position);

        /**
         * Set the read position of the data.
         *
         * @param position Read position of the data.
         */
        void setReadPosition(size_t position);

        /**
         * Get the write position of the data.
         *
         * @return Write position of the data.
         */
        size_t writePosition() const;

        /**
         * Get the read position of the data.
         *
         * @return Read position of the data.
         */
        size_t readPosition() const;

        /**
         * Get the capacity of the data.
         *
         * @attention The capacity is NOT the amount of bytes written bytes to the data.
         *
         * @return Number of bytes reserved for the data.
         */
        size_t capacity() const;

    private:
        explicit Data(librg_data *data);

        void free();

        friend class Event;
        friend class Message;
    };
}
