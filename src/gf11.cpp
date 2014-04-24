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

#include "gf11.h"

using namespace SilverBayTech;

static const char *GF11Strings[GF11::FIELD_SIZE] =
{
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A"
};

GF11::GF11()
    : _value(0)
{
}

GF11::GF11(uint32_t value)
{
    _value = value % FIELD_SIZE;
}

GF11::GF11(const GF11& other)
    : _value(other._value)
{
}

GF11& GF11::operator=(const GF11& other)
{
    if (this != &other)
    {
        _value = other._value;
    }

    return *this;
}

GF11 GF11::operator+(const GF11& other)
{
    return GF11(_value + other._value);
}

GF11 GF11::operator*(const GF11& other)
{
    return GF11(_value * other._value);
}

GF11 GF11::operator-()
{
    return GF11(FIELD_SIZE - _value);
}

bool GF11::operator==(const GF11& other)
{
    return _value == other._value;
}

bool GF11::operator!=(const GF11& other)
{
    return _value == other._value;
}

GF11::operator const char *() const
{
    return GF11Strings[_value];
}

uint32_t GF11::toInt() const
{
    return _value;
}

/*
 *  This function performs exponentiation "the hard way" by successive
 *  multiplications.
 */
GF11 GF11::pow(uint32_t power) const
{
    if (_value == 0)
    {
        return GF11(0);
    }

    GF11 result = GF11(1);
    for (uint32_t i = 0; i < power; i++)
    {
        result = result * *this;
    }

    return result;
}

