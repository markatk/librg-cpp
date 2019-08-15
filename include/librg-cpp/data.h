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

#define DECL_DATA_METHODS(NAME, TYPE) /** Write TYPE to the data. @param value Value to write to the data. */ \
    void write ## NAME (TYPE value); \
    /** Write TYPE to the data at given position. @param value Value to write to the data. @param position Position to write the data at. */ \
    void write ## NAME ## At(TYPE value, size_t position); \
    /** Read TYPE from the data. */ \
    TYPE read ## NAME (); \
    /** Read TYPE from the data at the given position. @param position Position to read the data at. */ \
    TYPE read ## NAME ## At (size_t position)

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
         * Write raw data.
         *
         * @param pointer Pointer to the raw data.
         * @param size Size in bytes of the raw data.
         */
        void writePointer(void *pointer, size_t size);

        /**
         * Write raw data at given position.
         *
         * @param pointer Pointer to the raw data.
         * @param size Size in bytes of the raw data.
         * @param position Position to write the raw data at.
         */
        void writePointerAt(void *pointer, size_t size, size_t position);

        /**
         * Read raw data.
         *
         * @param pointer Pointer to fill the raw data in.
         * @param size Size in bytes to read.
         * @return True if the amount of bytes could be read, otherwise false.
         */
        bool readPointer(void *pointer, size_t size);

        /**
         * Read raw data.
         *
         * @param pointer Pointer to fill the raw data in.
         * @param size Size in bytes to read.
         * @param position Position to read the raw data at.
         * @return True if the amount of bytes could be read, otherwise false.
         */
        bool readPointerAt(void *pointer, size_t size, size_t position);

        DECL_DATA_METHODS(Int8, int8_t);
        DECL_DATA_METHODS(UInt8, uint8_t);
        DECL_DATA_METHODS(Int16, int16_t);
        DECL_DATA_METHODS(UInt16, uint16_t);
        DECL_DATA_METHODS(Int32, int32_t);
        DECL_DATA_METHODS(UInt32, uint32_t);
        DECL_DATA_METHODS(Int64, int64_t);
        DECL_DATA_METHODS(UInt64, uint64_t);
        DECL_DATA_METHODS(Float, float);
        DECL_DATA_METHODS(Double, double);
        DECL_DATA_METHODS(Bool, bool);

        /**
         * Reset the data.
         *
         * This clears every data written to and resets both read and write positions.
         */
        void reset();

        /**
         * Grow the data to the given minimum size.
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
         * The capacity is the actual amount if written bytes to the data.
         *
         * @return Number of bytes written to the data.
         */
        size_t capacity() const;

    private:
        explicit Data(librg_data *data);

        void free();

        friend class Event;
        friend class Message;
    };
}
