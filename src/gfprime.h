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

#ifndef GRPRIME_DOT_H
#define GRPRIME_DOT_H
#include <stdint.h>
#include <iostream>

namespace SilverBayTech
{
    /*
     *  A template class that implements a Galois Field with a prime number
     *  of elements using standard modulo arithmetic, plus tables for log
     *  and exp operations.  Those tables must be provided externally - 
     *  the template can't generate them, however the program 
     *  primeLogExpGenerator can produce the required values.
     */

    template<unsigned int SIZE>
    class GFPrime
    {
    public:
        /*
         *  Constructor that builds an element of arbitrary value.
         *  The value passed in will be reduced modulo SIZE.
         */
        GFPrime(uint32_t value = 0) 
            : _value(value % SIZE)
        { 
        }

        /*
         *  Copy constructor
         */
        GFPrime(const GFPrime<SIZE>& other) 
            : _value(other._value)
        {
        }

        /*
         *  Assignment operator.
         */
        GFPrime<SIZE>& operator=(const GFPrime<SIZE>& other) 
        { 
            if (&other != this) 
            { 
                _value = other._value;
            } 
            return *this; 
        }

        /*
         *  "Addition-like" operations.
         */
        GFPrime<SIZE> operator+(const GFPrime<SIZE>& other) const
        { 
            return GFPrime<SIZE>(_value + other._value); 
        }

        GFPrime<SIZE>& operator+=(const GFPrime<SIZE>& other)
        {
            _value = (_value + other._value) % SIZE;
            return *this;
        }

        /*
         *  "Subtraction-like" operations.
         */
        GFPrime<SIZE> operator-(const GFPrime<SIZE>& other) const
        { 
            return GFPrime<SIZE>(SIZE + _value - other._value); 
        }

        GFPrime<SIZE>& operator-=(const GFPrime<SIZE>& other)
        {
            _value = (SIZE + _value - other._value) % SIZE;
            return *this;
        }

        /*
         *  "Multiplication-like" operations.
         */

        GFPrime<SIZE> operator*(const GFPrime<SIZE>& other)  const
        { 
            return GFPrime<SIZE>(_value * other._value); 
        }

        GFPrime<SIZE>& operator*=(const GFPrime<SIZE>& other)
        {
            _value = (_value * other._value) % SIZE;
            return *this;
        }

        /*
         *  "Division-like" operations.
         */

        GFPrime<SIZE> operator/(const GFPrime<SIZE>& other)  const
        { 
            if (_value == 0)
            {
                return GFPrime<SIZE>(0);
            }

            uint32_t logOfResult = SIZE - 1 + this->log() - other.log();
            return GFPrime<SIZE>::exp(logOfResult);
        }

        GFPrime<SIZE>& operator/=(const GFPrime<SIZE>& other)
        {
            if (_value != 0)
            {
                uint32_t logOfResult = SIZE - 1 + this->log() - other.log();
                _value = GFPrime<SIZE>::EXP_TABLE[logOfResult % (SIZE - 1)];
            }

            return *this;
        }

        /*
         *  Unary negation - returns the additive inverse.
         */
        GFPrime<SIZE> operator-() const
        { 
            return GFPrime<SIZE>(SIZE - _value); 
        }

        /*
         *  Comparison operations.
         */
        bool operator==(const GFPrime<SIZE>& other) const
        { 
            return _value == other._value; 
        }
        bool operator!=(const GFPrime<SIZE>& other) const
        { 
            return _value != other._value; 
        }

        /*
         *  Get the underlying integer value.
         */
        uint32_t toInt() const 
        { 
            return _value; 
        }

        /*
         *  Computes "primitive element to the nth power".  This is the
         *  antilog function.  It depends on the EXP_TABLE[] array,
         *  which has to be declared by the user.
         */
        static GFPrime<SIZE> exp(uint32_t power)
        {
            return GFPrime<SIZE>(EXP_TABLE[power % (SIZE - 1)]);
        }

        /*
         *  Logarithm of this element, base "primitive element."
         *  Depends on the LOG_TABLE[] array, which has to be declared
         *  by the user.
         */
        uint32_t log() const
        {
            return LOG_TABLE[_value];
        }

        /*
         *  Computes this element to the nth power.
         */
        GFPrime<SIZE> pow(uint32_t power) const
        {
            if (_value == 0)
            {
                return GFPrime<SIZE>(0);
            }

            return GFPrime<SIZE>::exp(log() * power);
        }

        static const uint32_t FIELD_SIZE = SIZE;

    private:
        /*
         *  This is the underlying value of an element.  A smaller data type
         *  may be used, if required, however, If (SIZE-1)*(SIZE-1) does not fit 
         *  inside the data type used:
         *      1) it may be necessary to "upcast" inside the multiplication
         *         function to avoid truncation during multiplication.
         *      2) The constructor taking an integer must use a data type that
         *         matches this "upcast", and must then downcast after doing
         *         the modulo operation.
         *  Alternately, once the EXP and LOG tables are worked out, multiplication
         *  can be re-defined via log and exp.
         */
        uint32_t _value;

        static const uint32_t EXP_TABLE[];
        static const uint32_t LOG_TABLE[];
    };

    template<unsigned int SIZE>
    std::ostream& operator<< (std::ostream& stream, const GFPrime<SIZE>& item)
    {
        stream << item.toInt();
        return stream;
    }
}

#endif  // GRPRIME_DOT_H
