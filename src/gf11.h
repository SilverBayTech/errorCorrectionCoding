/*
 *  Copyright (c) 2014 Kevin Hunter
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and 
 *  limitations under the License.
 */

#ifndef GF11_DOT_H
#define GF11_DOT_H
#include <stdint.h>

namespace SilverBayTech
{
    /*
     *  A class that implements a Galois Field of 11 members using
     *  standard mod-11 arithmetic.  Note that instances of this class
     *  are immutable.
     */

    class GF11
    {
    public:
        /*
         *  Constructor that builds a "zero" element.
         */
        GF11();

        /*
         *  Constructor that builds an element of arbitrary value.
         *  The value passed in will be reduced modulo 11.
         */
        GF11(uint32_t value);

        /*
         *  Copy constructor
         */
        GF11(const GF11& other);

        /*
         *  Number of elements in the field.
         */
        static const uint32_t FIELD_SIZE = 11;

        /*
         *  Assignment operator.
         */
        GF11& operator=(const GF11& other);

        /*
         *  "Addition-like" operation.
         */
        GF11 operator+(const GF11& other);

        /*
         *  "Multiplication-like" operation.
         */

        GF11 operator*(const GF11& other);

        /*
         *  Unary negation - returns the additive inverse.
         */
        GF11 operator-();

        /*
         *  Comparison operations.
         */
        bool operator==(const GF11& other);
        bool operator!=(const GF11& other);

        /*
         *  String representation of the element
         */
        operator const char *() const;

        /*
         *  Get the underlying integer value.
         */
        uint32_t toInt() const;

        /*
         *  Raise this element to a power.
         */
        GF11 pow(uint32_t power) const;

    private:
        uint32_t _value;
    };
}

#endif  // GF11_DOT_H
