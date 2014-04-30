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
#include <assert.h>
#include "eccUtils.h"
#include "gfpoly.h"
#include "gfprime.h"
#include "eccCommonUnitTests.h"

using namespace SilverBayTech;

static void lengthConstructorTest(void)
{
    GFPoly<GFPrime<11> > objUnderTest(3);

    assert(objUnderTest.getNumCoef() == 3);
    assert(objUnderTest[0].toInt() == 0);
    assert(objUnderTest[1].toInt() == 0);
    assert(objUnderTest[2].toInt() == 0);
}

static const uint32_t UINT_CONSTRUCTOR_DATA[] = { 1, 2, 3, 4};
static void uintConstructorTest(void)
{
    GFPoly<GFPrime<11> > objUnderTest(UINT_CONSTRUCTOR_DATA, ARRAY_LENGTH(UINT_CONSTRUCTOR_DATA));

    assert(objUnderTest.getNumCoef() == ARRAY_LENGTH(UINT_CONSTRUCTOR_DATA));

    for (uint32_t i = 0; i < ARRAY_LENGTH(UINT_CONSTRUCTOR_DATA); i++)
    {
        assert(objUnderTest[ARRAY_LENGTH(UINT_CONSTRUCTOR_DATA) - i - 1].toInt() == UINT_CONSTRUCTOR_DATA[i]);
    }
}

static const GFPrime<11> GF_CONSTRUCTOR_DATA[] = { GFPrime<11>(3), GFPrime<11>(4), GFPrime<11>(5) };
static void gfConstructorTest(void)
{
    GFPoly<GFPrime<11> > objUnderTest(GF_CONSTRUCTOR_DATA, ARRAY_LENGTH(GF_CONSTRUCTOR_DATA));

    assert(objUnderTest.getNumCoef() == ARRAY_LENGTH(GF_CONSTRUCTOR_DATA));

    for (uint32_t i = 0; i < ARRAY_LENGTH(GF_CONSTRUCTOR_DATA); i++)
    {
        assert(objUnderTest[ARRAY_LENGTH(GF_CONSTRUCTOR_DATA) - i - 1] == GF_CONSTRUCTOR_DATA[i]);
    }
}

static void copyConstructorTest(void)
{
    GFPoly<GFPrime<11> > master(GF_CONSTRUCTOR_DATA, ARRAY_LENGTH(GF_CONSTRUCTOR_DATA));
    GFPoly<GFPrime<11> > objUnderTest(master);

    assert(objUnderTest.getNumCoef() == ARRAY_LENGTH(GF_CONSTRUCTOR_DATA));

    for (uint32_t i = 0; i < ARRAY_LENGTH(GF_CONSTRUCTOR_DATA); i++)
    {
        assert(objUnderTest[ARRAY_LENGTH(GF_CONSTRUCTOR_DATA) - i - 1] == GF_CONSTRUCTOR_DATA[i]);
    }
}

static void assignmentTest(void)
{
    GFPoly<GFPrime<11> > master(GF_CONSTRUCTOR_DATA, ARRAY_LENGTH(GF_CONSTRUCTOR_DATA));
    GFPoly<GFPrime<11> > objUnderTest;

    objUnderTest = master;

    assert(objUnderTest.getNumCoef() == ARRAY_LENGTH(GF_CONSTRUCTOR_DATA));

    for (uint32_t i = 0; i < ARRAY_LENGTH(GF_CONSTRUCTOR_DATA); i++)
    {
        assert(objUnderTest[ARRAY_LENGTH(GF_CONSTRUCTOR_DATA) - i - 1] == GF_CONSTRUCTOR_DATA[i]);
    }
}

static void assignment_sameInstance(void)
{
    GFPoly<GFPrime<11> > objUnderTest(GF_CONSTRUCTOR_DATA, ARRAY_LENGTH(GF_CONSTRUCTOR_DATA));

    objUnderTest = objUnderTest;

    assert(objUnderTest.getNumCoef() == ARRAY_LENGTH(GF_CONSTRUCTOR_DATA));

    for (uint32_t i = 0; i < ARRAY_LENGTH(GF_CONSTRUCTOR_DATA); i++)
    {
        assert(objUnderTest[ARRAY_LENGTH(GF_CONSTRUCTOR_DATA) - i - 1] == GF_CONSTRUCTOR_DATA[i]);
    }
}

static const uint32_t EQUALITY_DATA1[] = { 1, 2, 3, 4};
static const uint32_t EQUALITY_DATA2[] = { 1, 2, 3, 5};
static const uint32_t EQUALITY_DATA3[] = { 0, 1, 2, 3, 4};
static const uint32_t EQUALITY_DATA4[] = { 1, 1, 2, 3, 4};

static void equalityOperator_sameInstance(void)
{
    GFPoly<GFPrime<11> > one(EQUALITY_DATA1, ARRAY_LENGTH(EQUALITY_DATA1));

    assert(one == one);
    assert(!(one != one));
}

static void equalityOperator_sameLengthEqual(void)
{
    GFPoly<GFPrime<11> > one(EQUALITY_DATA1, ARRAY_LENGTH(EQUALITY_DATA1));
    GFPoly<GFPrime<11> > two(EQUALITY_DATA1, ARRAY_LENGTH(EQUALITY_DATA1));

    assert(one == two);
    assert(two == one);
    assert(!(one != two));
    assert(!(two != one));
}

static void equalityOperator_sameLengthNotEqual(void)
{
    GFPoly<GFPrime<11> > one(EQUALITY_DATA1, ARRAY_LENGTH(EQUALITY_DATA1));
    GFPoly<GFPrime<11> > two(EQUALITY_DATA2, ARRAY_LENGTH(EQUALITY_DATA2));

    assert(!(one == two));
    assert(!(two == one));
    assert(one != two);
    assert(two != one);
}

static void equalityOperator_differentLengthEqual(void)
{
    GFPoly<GFPrime<11> > one(EQUALITY_DATA1, ARRAY_LENGTH(EQUALITY_DATA1));
    GFPoly<GFPrime<11> > two(EQUALITY_DATA3, ARRAY_LENGTH(EQUALITY_DATA3));

    assert(one == two);
    assert(two == one);
    assert(!(one != two));
    assert(!(two != one));
}

static void equalityOperator_differentLengthNotEqual(void)
{
    GFPoly<GFPrime<11> > one(EQUALITY_DATA1, ARRAY_LENGTH(EQUALITY_DATA1));
    GFPoly<GFPrime<11> > two(EQUALITY_DATA4, ARRAY_LENGTH(EQUALITY_DATA4));

    assert(!(one == two));
    assert(!(two == one));
    assert(one != two);
    assert(two != one);
}

static const uint32_t EVAL_COEF[] = { 1, 2, 3, 4};
static const uint32_t EVAL_DATA[][2] = 
{
    { 0, 4 },
    { 1, 10 },
    { 2, 4 },
    { 3, 3 },
    { 4, 2 },
    { 5, 7 },
    { 6, 2 },
    { 7, 4 },
    { 8, 8 },
    { 9, 9 },
    { 10, 2 },
};

static void evalTest(void)
{
    GFPoly<GFPrime<11> > objUnderTest(EVAL_COEF, ARRAY_LENGTH(EVAL_COEF));

    for (size_t i = 0; i < ARRAY_LENGTH(EVAL_DATA); i++)
    {
        GFPrime<11> input(EVAL_DATA[i][0]);
        GFPrime<11>expected(EVAL_DATA[i][1]);

        GFPrime<11> actual = objUnderTest.eval(input);

        assert(actual == expected);
    }
}

static const uint32_t TIMES_INPUT1[] = { 1, 2, 3 };
static const uint32_t TIMES_INPUT2[] = { 1, 4 };
static const uint32_t TIMES_CONSTANT_OUTPUT[] = { 2, 4, 6 };
static const uint32_t TIMES_POLY_OUTPUT[] = { 1, 6, 0, 1 };

static void timesConstantTest(void)
{
    GFPoly<GFPrime<11> > input(TIMES_INPUT1, ARRAY_LENGTH(TIMES_INPUT1));
    GFPoly<GFPrime<11> > expected(TIMES_CONSTANT_OUTPUT, ARRAY_LENGTH(TIMES_CONSTANT_OUTPUT));

    GFPoly<GFPrime<11> > output = input * GFPrime<11>(2);

    assert(output == expected);
}

static void timesPolyTest(void)
{
    GFPoly<GFPrime<11> > input1(TIMES_INPUT1, ARRAY_LENGTH(TIMES_INPUT1));
    GFPoly<GFPrime<11> > input2(TIMES_INPUT2, ARRAY_LENGTH(TIMES_INPUT2));
    GFPoly<GFPrime<11> > expected(TIMES_POLY_OUTPUT, ARRAY_LENGTH(TIMES_POLY_OUTPUT));

    GFPoly<GFPrime<11> > objUnderTest = input1 * input2;
    assert(objUnderTest == expected);

    objUnderTest = input2 * input1;

    assert(objUnderTest == expected);
}

static const uint32_t SHIFT_INPUT[] = { 1, 2, 3 };
static const uint32_t SHIFT_OUTPUT[] = { 1, 2, 3, 0, 0, 0 };
static void shiftTest(void)
{
    GFPoly<GFPrime<11> > input(SHIFT_INPUT, ARRAY_LENGTH(SHIFT_INPUT));
    GFPoly<GFPrime<11> > expected(SHIFT_OUTPUT, ARRAY_LENGTH(SHIFT_OUTPUT));

    GFPoly<GFPrime<11> > output = input << 3;

    assert(output == expected);
}

static const uint32_t SUBTRACT_INPUT1[] = { 1, 2, 3 };
static const uint32_t SUBTRACT_INPUT2[] = { 1, 1, 1 };
static const uint32_t SUBTRACT_INPUT3[] = { 1, 2 };

static const uint32_t SUBTRACT_EQUAL_LENGTH[] = { 0, 1, 2 };
static void subtract_equalLength(void)
{
    GFPoly<GFPrime<11> > top(SUBTRACT_INPUT1, ARRAY_LENGTH(SUBTRACT_INPUT1));
    GFPoly<GFPrime<11> > bottom(SUBTRACT_INPUT2, ARRAY_LENGTH(SUBTRACT_INPUT2));
    GFPoly<GFPrime<11> > expected(SUBTRACT_EQUAL_LENGTH, ARRAY_LENGTH(SUBTRACT_EQUAL_LENGTH));

    GFPoly<GFPrime<11> > output = top - bottom;

    assert(output == expected);
}

static const uint32_t SUBTRACT_TOP_LONGER[] = { 1, 1, 1 };
static void subtract_topLonger(void)
{
    GFPoly<GFPrime<11> > top(SUBTRACT_INPUT1, ARRAY_LENGTH(SUBTRACT_INPUT1));
    GFPoly<GFPrime<11> > bottom(SUBTRACT_INPUT3, ARRAY_LENGTH(SUBTRACT_INPUT3));
    GFPoly<GFPrime<11> > expected(SUBTRACT_TOP_LONGER, ARRAY_LENGTH(SUBTRACT_TOP_LONGER));

    GFPoly<GFPrime<11> > output = top - bottom;

    assert(output == expected);
}

static const uint32_t SUBTRACT_BOTTOM_LONGER[] = { 10, 10, 10 };
static void subtract_bottomLonger(void)
{
    GFPoly<GFPrime<11> > top(SUBTRACT_INPUT3, ARRAY_LENGTH(SUBTRACT_INPUT3));
    GFPoly<GFPrime<11> > bottom(SUBTRACT_INPUT1, ARRAY_LENGTH(SUBTRACT_INPUT1));
    GFPoly<GFPrime<11> > expected(SUBTRACT_BOTTOM_LONGER, ARRAY_LENGTH(SUBTRACT_BOTTOM_LONGER));

    GFPoly<GFPrime<11> > output = top - bottom;

    assert(output == expected);
}

static const uint32_t TRIM_NOT_ALL_ZEROS[] = { 0, 0, 1, 2, 3 };
static void trim_notAllZeros(void)
{
    GFPoly<GFPrime<11> > objUnderTest(TRIM_NOT_ALL_ZEROS, ARRAY_LENGTH(TRIM_NOT_ALL_ZEROS));

    objUnderTest.trimLeadingZeros();

    assert(objUnderTest.getNumCoef() == 3);
    assert(objUnderTest[0].toInt() == 3);
    assert(objUnderTest[1].toInt() == 2);
    assert(objUnderTest[2].toInt() == 1);
}

static const uint32_t TRIM_ALL_ZEROS[] = { 0, 0, 0, 0, 0 };
static void trim_allZeros(void)
{
    GFPoly<GFPrime<11> > objUnderTest(TRIM_ALL_ZEROS, ARRAY_LENGTH(TRIM_ALL_ZEROS));

    objUnderTest.trimLeadingZeros();

    assert(objUnderTest.getNumCoef() == 1);
    assert(objUnderTest[0].toInt() == 0);
}

static void trim_leaveLeadingZeros(void)
{
    GFPoly<GFPrime<11> > objUnderTest(TRIM_ALL_ZEROS, ARRAY_LENGTH(TRIM_ALL_ZEROS));

    objUnderTest.trimLeadingZeros(2);

    assert(objUnderTest.getNumCoef() == 2);
    assert(objUnderTest[0].toInt() == 0);
    assert(objUnderTest[1].toInt() == 0);
}

static void trim_leaveMinOne(void)
{
    GFPoly<GFPrime<11> > objUnderTest(TRIM_ALL_ZEROS, ARRAY_LENGTH(TRIM_ALL_ZEROS));

    objUnderTest.trimLeadingZeros(0);

    assert(objUnderTest.getNumCoef() == 1);
    assert(objUnderTest[0].toInt() == 0);
}

static const uint32_t REMAINDER1[] = { 8, 6, 7, 5, 3, 0, 9, 0, 0 };
static const uint32_t REMAINDER2[] = { 1, 5, 8 };
static const uint32_t REMAINDER3[] = { 1, 0, 8 };
static const uint32_t REMAINDER4[] = { 8, 6, 7, 5, 3, 0, 9, 4, 4 };
static const uint32_t ZERO[] = { 0 };
static const uint32_t DIVISOR_SMALLER[] = { 7, 7 };

static void remainder_divisorSmaller_remaider(void)
{
    GFPoly<GFPrime<11> > numerator(REMAINDER1, ARRAY_LENGTH(REMAINDER1));
    GFPoly<GFPrime<11> > denominator(REMAINDER2, ARRAY_LENGTH(REMAINDER2));

    GFPoly<GFPrime<11> > remainder = numerator % denominator;
    GFPoly<GFPrime<11> > expected(DIVISOR_SMALLER, ARRAY_LENGTH(DIVISOR_SMALLER));

    assert(remainder == expected);
}

static void remainder_divisorSmaller_noRemaider(void)
{
    GFPoly<GFPrime<11> > numerator(REMAINDER4, ARRAY_LENGTH(REMAINDER4));
    GFPoly<GFPrime<11> > denominator(REMAINDER2, ARRAY_LENGTH(REMAINDER2));

    GFPoly<GFPrime<11> > remainder = numerator % denominator;
    GFPoly<GFPrime<11> > expected(ZERO, ARRAY_LENGTH(ZERO));

    assert(remainder == expected);
}

static const uint32_t DIVISOR_EQUAL[] = { 5, 0 };
static void remainder_divisorEqual_remaider(void)
{
    GFPoly<GFPrime<11> > numerator(REMAINDER2, ARRAY_LENGTH(REMAINDER2));
    GFPoly<GFPrime<11> > denominator(REMAINDER3, ARRAY_LENGTH(REMAINDER3));

    GFPoly<GFPrime<11> > remainder = numerator % denominator;
    GFPoly<GFPrime<11> > expected(DIVISOR_EQUAL, ARRAY_LENGTH(DIVISOR_EQUAL));

    assert(remainder == expected);
}

static void remainder_divisorEqual_noRemainder1(void)
{
    GFPoly<GFPrime<11> > numerator(REMAINDER2, ARRAY_LENGTH(REMAINDER2));
    GFPoly<GFPrime<11> > denominator(REMAINDER2, ARRAY_LENGTH(REMAINDER2));

    GFPoly<GFPrime<11> > remainder = numerator % denominator;
    GFPoly<GFPrime<11> > expected(ZERO, ARRAY_LENGTH(ZERO));

    assert(remainder == expected);
}

static void remainder_divisorEqual_noRemainder2(void)
{
    GFPoly<GFPrime<11> > numerator(REMAINDER1, ARRAY_LENGTH(REMAINDER1));   // tests non-1 leading coef
    GFPoly<GFPrime<11> > denominator(REMAINDER1, ARRAY_LENGTH(REMAINDER1));

    GFPoly<GFPrime<11> > remainder = numerator % denominator;
    GFPoly<GFPrime<11> > expected(ZERO, ARRAY_LENGTH(ZERO));

    assert(remainder == expected);
}

static void remainder_divisorLarger(void)
{
    GFPoly<GFPrime<11> > numerator(REMAINDER2, ARRAY_LENGTH(REMAINDER2));
    GFPoly<GFPrime<11> > denominator(REMAINDER1, ARRAY_LENGTH(REMAINDER1));

    GFPoly<GFPrime<11> > remainder = numerator % denominator;
    GFPoly<GFPrime<11> > expected(REMAINDER2, ARRAY_LENGTH(REMAINDER2));

    assert(remainder == expected);
}

void gfpolyUnitTests(void)
{
    lengthConstructorTest();
    uintConstructorTest();
    gfConstructorTest();
    copyConstructorTest();
    assignmentTest();
    assignment_sameInstance();
    equalityOperator_sameInstance();
    equalityOperator_sameLengthEqual();
    equalityOperator_sameLengthNotEqual();
    equalityOperator_differentLengthEqual();
    equalityOperator_differentLengthNotEqual();
    evalTest();
    timesConstantTest();
    timesPolyTest();
    shiftTest();
    subtract_equalLength();
    subtract_topLonger();
    subtract_bottomLonger();
    trim_notAllZeros();
    trim_allZeros();
    trim_leaveLeadingZeros();
    trim_leaveMinOne();
    remainder_divisorLarger();
    remainder_divisorSmaller_remaider();
    remainder_divisorSmaller_noRemaider();
    remainder_divisorEqual_remaider();
    remainder_divisorEqual_noRemainder1();
    remainder_divisorEqual_noRemainder2();
}
