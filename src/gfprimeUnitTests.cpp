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

#include <iostream>
#include <sstream>
#include <assert.h>
#include "eccUtils.h"
#include "gfprime.h"
#include "eccCommonUnitTests.h"

using namespace SilverBayTech;
using namespace std;

static void zeroArgConstructor_createsZero(void)
{
    GFPrime<11> objUnderTest;

    assert(objUnderTest.toInt() == 0);
}

static void intArgConstructor_createsValue(void)
{
    GFPrime<11> objUnderTest(5);

    assert(objUnderTest.toInt() == 5);
}

static void intArgConstructor_modsInput(void)
{
    GFPrime<11> objUnderTest(89);

    assert(objUnderTest.toInt() == 1);
}

static void copyConstructor_copies(void)
{
    GFPrime<11> origin(5);
    GFPrime<11> objUnderTest(origin);

    assert(objUnderTest.toInt() == 5);
}

static void assignmentOperator_copies(void)
{
    GFPrime<11> origin(5);
    GFPrime<11> objUnderTest;

    objUnderTest = origin;

    assert(objUnderTest.toInt() == 5);
}

static void additionOperator_moduloArithmetic(void)
{
    for (uint32_t i = 0; i < GFPrime<11>::FIELD_SIZE; i++)
    {
        for (uint32_t j = 0; j < GFPrime<11>::FIELD_SIZE; j++)
        {
            GFPrime<11> objUnderTest = GFPrime<11>(i) + GFPrime<11>(j);

            assert(objUnderTest.toInt() == (i + j) % GFPrime<11>::FIELD_SIZE);
        }
    }
}

static void additionEqualsOperator_moduloArithmetic(void)
{
    for (uint32_t i = 0; i < GFPrime<11>::FIELD_SIZE; i++)
    {
        for (uint32_t j = 0; j < GFPrime<11>::FIELD_SIZE; j++)
        {
            GFPrime<11> objUnderTest(i);
            objUnderTest += GFPrime<11>(j);

            assert(objUnderTest.toInt() == (i + j) % GFPrime<11>::FIELD_SIZE);
        }
    }
}

static void subtractionOperator_moduloArithmetic(void)
{
    for (uint32_t i = 0; i < GFPrime<11>::FIELD_SIZE; i++)
    {
        for (uint32_t j = 0; j < GFPrime<11>::FIELD_SIZE; j++)
        {
            GFPrime<11> objUnderTest = GFPrime<11>(i) - GFPrime<11>(j);

            assert(objUnderTest.toInt() == (GFPrime<11>::FIELD_SIZE + i - j) % GFPrime<11>::FIELD_SIZE);
        }
    }
}

static void subtractionOperator_equalsAddingInverse(void)
{
    for (uint32_t i = 0; i < GFPrime<11>::FIELD_SIZE; i++)
    {
        for (uint32_t j = 0; j < GFPrime<11>::FIELD_SIZE; j++)
        {
            GFPrime<11> subtract = GFPrime<11>(i) - GFPrime<11>(j);
            GFPrime<11> addInverse = GFPrime<11>(i) + -GFPrime<11>(j);

            assert(subtract.toInt() == addInverse.toInt());
        }
    }
}

static void subtractionEqualsOperator_moduloArithmetic(void)
{
    for (uint32_t i = 0; i < GFPrime<11>::FIELD_SIZE; i++)
    {
        for (uint32_t j = 0; j < GFPrime<11>::FIELD_SIZE; j++)
        {
            GFPrime<11> objUnderTest(i);
            objUnderTest -= GFPrime<11>(j);

            assert(objUnderTest.toInt() == (GFPrime<11>::FIELD_SIZE + i - j) % GFPrime<11>::FIELD_SIZE);
        }
    }
}

static void multiplicationOperator_moduloArithmetic(void)
{
    for (uint32_t i = 0; i < GFPrime<11>::FIELD_SIZE; i++)
    {
        for (uint32_t j = 0; j < GFPrime<11>::FIELD_SIZE; j++)
        {
            GFPrime<11> objUnderTest = GFPrime<11>(i) * GFPrime<11>(j);

            assert(objUnderTest.toInt() == (i * j) % GFPrime<11>::FIELD_SIZE);
        }
    }
}

static void multiplicationEqualsOperator_moduloArithmetic(void)
{
    for (uint32_t i = 0; i < GFPrime<11>::FIELD_SIZE; i++)
    {
        for (uint32_t j = 0; j < GFPrime<11>::FIELD_SIZE; j++)
        {
            GFPrime<11> objUnderTest(i);
            objUnderTest *= GFPrime<11>(j);

            assert(objUnderTest.toInt() == (i * j) % GFPrime<11>::FIELD_SIZE);
        }
    }
}

static void divisionOperator_inverseOfMultiplication(void)
{
    for (uint32_t i = 1; i < GFPrime<11>::FIELD_SIZE; i++)
    {
        for (uint32_t j = 1; j < GFPrime<11>::FIELD_SIZE; j++)
        {
            GFPrime<11> objUnderTest = GFPrime<11>(i) / GFPrime<11>(j);

            assert((objUnderTest * GFPrime<11>(j)).toInt() == i);
        }
    }
}

static void divisionEqualsOperator_inverseOfMultiplication(void)
{
    for (uint32_t i = 1; i < GFPrime<11>::FIELD_SIZE; i++)
    {
        for (uint32_t j = 1; j < GFPrime<11>::FIELD_SIZE; j++)
        {
            GFPrime<11> objUnderTest = GFPrime<11>(i);
            objUnderTest /= GFPrime<11>(j);

            assert((objUnderTest * GFPrime<11>(j)).toInt() == i);
        }
    }
}

static void equalsAndNotEquals(void)
{
    for (uint32_t i = 0; i < GFPrime<11>::FIELD_SIZE; i++)
    {
        GFPrime<11> one(i);

        for (uint32_t j = 0; j < GFPrime<11>::FIELD_SIZE; j++)
        {
            GFPrime<11> two(j);

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
    for (uint32_t i = 1; i < GFPrime<11>::FIELD_SIZE; i++)
    {
        GFPrime<11> objUnderTest(i);
        size_t log = objUnderTest.log();
        GFPrime<11> exp = GFPrime<11>::exp(log);

        assert(objUnderTest.toInt() == exp.toInt());
    }
}

static void powEqualsMultiplication(void)
{
    for (uint32_t i = 1; i < GFPrime<11>::FIELD_SIZE; i++)
    {
        GFPrime<11> objUnderTest(i);

        GFPrime<11> value(1);

        for (size_t j = 0; j < GFPrime<11>::FIELD_SIZE; j++)
        {
            assert(objUnderTest.pow(j) == value);

            value *= objUnderTest;
        }
    }

    GFPrime<11> zero(0);

    for (size_t j = 0; j < GFPrime<11>::FIELD_SIZE; j++)
    {
        assert(zero.pow(j).toInt() == 0);
    }
}

static void outputToStream(void)
{
    for (uint32_t i = 0; i < GFPrime<11>::FIELD_SIZE; i++)
    {
        ostringstream stream;
        stream << GFPrime<11>(i);
        string result = stream.str();

        ostringstream expectedStream;
        expectedStream << i;
        string expected = expectedStream.str();

        assert(result == expected);
    }
}

void gfprimeUnitTests(void)
{
    zeroArgConstructor_createsZero();
    intArgConstructor_createsValue();
    intArgConstructor_modsInput();
    copyConstructor_copies();
    assignmentOperator_copies();
    additionOperator_moduloArithmetic();
    additionEqualsOperator_moduloArithmetic();
    subtractionOperator_moduloArithmetic();
    subtractionEqualsOperator_moduloArithmetic();
    subtractionOperator_equalsAddingInverse();
    multiplicationOperator_moduloArithmetic();
    multiplicationEqualsOperator_moduloArithmetic();
    divisionOperator_inverseOfMultiplication();
    divisionEqualsOperator_inverseOfMultiplication();
    equalsAndNotEquals();
    expInverseOfLog();
    powEqualsMultiplication();
    outputToStream();
}

