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

/*
 *  Unit tests for the GFBinary<x> template.
 */

#include <iostream>
#include <sstream>
#include <assert.h>
#include "eccUtils.h"
#include "gfbinary.h"
#include "eccCommonUnitTests.h"

using namespace SilverBayTech;
using namespace std;

static void zeroArgConstructor_createsZero(void)
{
    GFBinary<8> objUnderTest;

    assert(objUnderTest.toInt() == 0);
}

static void intArgConstructor_createsValue(void)
{
    GFBinary<8> objUnderTest(5);

    assert(objUnderTest.toInt() == 5);
}

static void intArgConstructor_modsInput(void)
{
    GFBinary<8> objUnderTest(89);

    assert(objUnderTest.toInt() == 1);
}

static void copyConstructor_copies(void)
{
    GFBinary<8> origin(5);
    GFBinary<8> objUnderTest(origin);

    assert(objUnderTest.toInt() == 5);
}

static void assignmentOperator_copies(void)
{
    GFBinary<8> origin(5);
    GFBinary<8> objUnderTest;

    objUnderTest = origin;

    assert(objUnderTest.toInt() == 5);
}

static void additionOperator_xorArithmetic(void)
{
    for (uint32_t i = 0; i < GFBinary<8>::FIELD_SIZE; i++)
    {
        for (uint32_t j = 0; j < GFBinary<8>::FIELD_SIZE; j++)
        {
            GFBinary<8> objUnderTest = GFBinary<8>(i) + GFBinary<8>(j);

            assert(objUnderTest.toInt() == (i ^ j));
        }
    }
}

static void additionEqualsOperator_xorArithmetic(void)
{
    for (uint32_t i = 0; i < GFBinary<8>::FIELD_SIZE; i++)
    {
        for (uint32_t j = 0; j < GFBinary<8>::FIELD_SIZE; j++)
        {
            GFBinary<8> objUnderTest(i);
            objUnderTest += GFBinary<8>(j);

            assert(objUnderTest.toInt() == (i ^ j));
        }
    }
}

static void subtractionOperator_xorArithmetic(void)
{
    for (uint32_t i = 0; i < GFBinary<8>::FIELD_SIZE; i++)
    {
        for (uint32_t j = 0; j < GFBinary<8>::FIELD_SIZE; j++)
        {
            GFBinary<8> objUnderTest = GFBinary<8>(i) - GFBinary<8>(j);

            assert(objUnderTest.toInt() == (i ^ j));
        }
    }
}

static void subtractionOperator_equalsAddingInverse(void)
{
    for (uint32_t i = 0; i < GFBinary<8>::FIELD_SIZE; i++)
    {
        for (uint32_t j = 0; j < GFBinary<8>::FIELD_SIZE; j++)
        {
            GFBinary<8> subtract = GFBinary<8>(i) - GFBinary<8>(j);
            GFBinary<8> addInverse = GFBinary<8>(i) + -GFBinary<8>(j);

            assert(subtract.toInt() == addInverse.toInt());
        }
    }
}

static void subtractionEqualsOperator_xorArithmetic(void)
{
    for (uint32_t i = 0; i < GFBinary<8>::FIELD_SIZE; i++)
    {
        for (uint32_t j = 0; j < GFBinary<8>::FIELD_SIZE; j++)
        {
            GFBinary<8> objUnderTest(i);
            objUnderTest -= GFBinary<8>(j);

            assert(objUnderTest.toInt() == (i ^ j));
        }
    }
}

static void divisionOperator_inverseOfMultiplication(void)
{
    for (uint32_t i = 1; i < GFBinary<8>::FIELD_SIZE; i++)
    {
        for (uint32_t j = 1; j < GFBinary<8>::FIELD_SIZE; j++)
        {
            GFBinary<8> objUnderTest = GFBinary<8>(i) / GFBinary<8>(j);

            assert((objUnderTest * GFBinary<8>(j)).toInt() == i);
        }
    }
}

static void divisionEqualsOperator_inverseOfMultiplicationEquals(void)
{
    for (uint32_t i = 1; i < GFBinary<8>::FIELD_SIZE; i++)
    {
        for (uint32_t j = 1; j < GFBinary<8>::FIELD_SIZE; j++)
        {
            GFBinary<8> objUnderTest = GFBinary<8>(i);
            objUnderTest /= GFBinary<8>(j);
            objUnderTest *= GFBinary<8>(j);

            assert(objUnderTest.toInt() == i);
        }
    }
}

static void equalsAndNotEquals(void)
{
    for (uint32_t i = 0; i < GFBinary<8>::FIELD_SIZE; i++)
    {
        GFBinary<8> one(i);

        for (uint32_t j = 0; j < GFBinary<8>::FIELD_SIZE; j++)
        {
            GFBinary<8> two(j);

            if (i == j)
            {
                assert(one == two);
                assert(two == one);
                assert(!(one != two));
                assert(!(two != one));
            }
            else
            {
                assert(one != two);
                assert(two != one);
                assert(!(one == two));
                assert(!(two == one));
            }
        }
    }
}

static void expInverseOfLog(void)
{
    for (uint32_t i = 1; i < GFBinary<8>::FIELD_SIZE; i++)
    {
        GFBinary<8> objUnderTest(i);
        size_t log = objUnderTest.log();
        GFBinary<8> exp = GFBinary<8>::exp(log);

        assert(objUnderTest.toInt() == exp.toInt());
    }
}

static void powEqualsMultiplication(void)
{
    for (uint32_t i = 1; i < GFBinary<8>::FIELD_SIZE; i++)
    {
        GFBinary<8> objUnderTest(i);

        GFBinary<8> value(1);

        for (size_t j = 0; j < GFBinary<8>::FIELD_SIZE; j++)
        {
            assert(objUnderTest.pow(j) == value);

            value *= objUnderTest;
        }
    }

    GFBinary<8> zero(0);

    for (size_t j = 0; j < GFBinary<8>::FIELD_SIZE; j++)
    {
        assert(zero.pow(j).toInt() == 0);
    }
}

static void outputToStream(void)
{
    for (uint32_t i = 0; i < GFBinary<256>::FIELD_SIZE; i++)
    {
        ostringstream stream;
        stream << GFBinary<256>(i);
        string result = stream.str();

        ostringstream expectedStream;
        expectedStream << uppercase << hex << i;
        string expected = expectedStream.str();

        assert(result == expected);
    }
}

void gfbinaryUnitTests(void)
{
    zeroArgConstructor_createsZero();
    intArgConstructor_createsValue();
    intArgConstructor_modsInput();
    copyConstructor_copies();
    assignmentOperator_copies();
    additionOperator_xorArithmetic();
    additionEqualsOperator_xorArithmetic();
    subtractionOperator_xorArithmetic();
    subtractionEqualsOperator_xorArithmetic();
    subtractionOperator_equalsAddingInverse();
    divisionOperator_inverseOfMultiplication();
    divisionEqualsOperator_inverseOfMultiplicationEquals();
    equalsAndNotEquals();
    expInverseOfLog();
    powEqualsMultiplication();
    outputToStream();
}

