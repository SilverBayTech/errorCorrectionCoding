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
#include "gfprime.h"

/*
 *  This sample file illustrates the use of the GFPrime<T> template class by performing
 *  manipulations on GF11.  It also provides logic via which, with a few alterations,
 *  the LOG and EXP tables for any other field could be computed.  Essentially, you
 *  should be able to:
 *      1) Replace GFPrime<11> with GFPrime<N> where N is a prime number.
 *      2) 
 */

using namespace std;
using SilverBayTech::GFPrime;

/*
 *  These two entries provide the EXP and LOG values for GFPrime<11>.  If you were starting
 *  to use GFPrime for some value other than 11 and needed to get going from scratch,
 *  you could declare these with empty values and run the equivalent buildExpLogTable()
 *  for your prime, which will generate them for you.  (buildExpLogTable() doesn't depend
 *  on the existence of the tables - it does everything via multiplication.) Note that
 *  we include a log value (0) for zero, even though it's technically undefined.  But you
 *  should never be taking the log of zero, so it shouldn't matter to you.  The EXP table
 *  is one shorter, because we assume that all exponents are "modded" before being run
 *  through this table.
 */

const uint32_t GFPrime<11>::EXP_TABLE[10] = {1,2,4,8,5,10,9,7,3,6};
const uint32_t GFPrime<11>::LOG_TABLE[11] = {0,0,1,8,2,4,9,7,3,6,5};

/*
 *  This method tests to see if the candidate is a primitive element for
 *  the Galois Field.  It does this by successively multiplying through
 *  by this element (i.e. computing successive powers of it) and verifying that
 *  all the non-zero elements get generated.
 */

bool isPrimitiveElement(const GFPrime<11>& candidate)
{
    bool generated[GFPrime<11>::FIELD_SIZE];

    for (uint32_t i = 0; i < GFPrime<11>::FIELD_SIZE; i++)
    {
        generated[i] = false;
    }

    GFPrime<11> value(1);

    for (uint32_t i = 0; i < GFPrime<11>::FIELD_SIZE; i++)
    {
        value = value * candidate;
        generated[value.toInt()] = true;
    }

    for (uint32_t i = 1; i < GFPrime<11>::FIELD_SIZE; i++)
    {
        if (!generated[i])
        {
            return false;
        }
    }

    return true;
}

void findPrimitiveElements()
{
    cout << "Primitive elements\n";

    for (uint32_t i = 0; i < GFPrime<11>::FIELD_SIZE; i++)
    {
        GFPrime<11> x(i);

        if (isPrimitiveElement(x))
        {
            cout << i << '\n';
        }
    }
}

/*
 *  This routine builds (and prints out) EXP_TABLE and LOG_TABLE.

 */

void buildExpLogArrays(const GFPrime<11>& primitiveElement)
{
    assert(isPrimitiveElement(primitiveElement));

    GFPrime<11> exp[GFPrime<11>::FIELD_SIZE - 1];
    uint32_t log[GFPrime<11>::FIELD_SIZE];

    log[0] = 0;
    exp[0] = GFPrime<11>(1);

    for (uint32_t i = 1; i < GFPrime<11>::FIELD_SIZE - 1; i++)
    {
        exp[i] = exp[i-1] * primitiveElement;
    }

    for (uint32_t i = 0; i < GFPrime<11>::FIELD_SIZE - 1; i++)
    {
        log[exp[i].toInt()] = i;
    }

    cout << "const uint32_t GFPrime<11>::EXP_TABLE["<<GFPrime<11>::FIELD_SIZE-1<<"] = {";

    for (uint32_t i = 0; i < GFPrime<11>::FIELD_SIZE - 1; i++)
    {
        if (i > 0)
        {
            cout << ',';
        }

        cout << exp[i].toInt();
    }

    cout << "};\n";

    cout << "const uint32_t GFPrime<11>::LOG_TABLE["<<GFPrime<11>::FIELD_SIZE<<"] = {";

    for (uint32_t i = 0; i < GFPrime<11>::FIELD_SIZE; i++)
    {
        if (i > 0)
        {
            cout << ',';
        }

        cout << log[i];
    }

    cout << "};\n";
}

/*
 *  This function confirms that, for all non-zero values, multiplying via
 *  the mod operator (built into the class) is the same as doing it via
 *  log/exp.
 */

void confirmLogExpMultiplication()
{
    for (uint32_t i = 1; i < GFPrime<11>::FIELD_SIZE; i++)
    {
        GFPrime<11> x(i);

        for (uint32_t j = 1; j < GFPrime<11>::FIELD_SIZE; j++)
        {
            GFPrime<11> y(j);

            GFPrime<11> byMod = x * y;
            GFPrime<11> byLog = GFPrime<11>::exp(x.log() + y.log());

            if (byMod != byLog)
            {
                cerr << "Didn't work for " << i << " and " << j << '\n';
            }
        }
   }
}

/*
 *  This function confirms that the pow() function behaves as expected
 *  (i.e. equivalent to successive multiplication).
 */

void confirmPowBehavior()
{
    for (uint32_t i = 0; i  < GFPrime<11>::FIELD_SIZE; i++)
    {
        GFPrime<11> x(i);

        if (i != 0)
        {
            /*
             *  Anything to the zero power is one
             */
            assert(x.pow(0) == GFPrime<11>(1));
        }
        else
        {
            /*
             *  Except zero to the zero power, which we've defined as zero
             *  despite some arguments to the contrary.
             */
            assert(x.pow(0) == GFPrime<11>(0));
        }

        GFPrime<11> value(1);

        /*
         *  Note that we deliberately go farther than the size of the field,
         *  since things should wrap nicely, and exponents aren't constrained
         *  to be field members.
         */
        for (uint32_t j = 1; j < GFPrime<11>::FIELD_SIZE * 2; j++)
        {
            value = value * x;

            assert(x.pow(j) == value);
        }
    }
}

int main(void)
{
    findPrimitiveElements();

    GFPrime<11> primitiveElement(2);

    buildExpLogArrays(primitiveElement);

    confirmLogExpMultiplication();

    confirmPowBehavior();

    cout << "Done";
    return 0;
}
