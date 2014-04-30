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
 *  This program will generate a set of log/exp tables for a Galois Field
 *  with a prime number of elements.
 *
 *  Unlike some of the other samples in this project it does not need to
 *  be recompiled to change the size of the field - it takes this as a
 *  command line parameters.
 */

#include <iostream>
#include <assert.h>

using namespace std;

unsigned int *EXP_TABLE = 0;
unsigned int *LOG_TABLE = 0;

/*
 *  Tests to see if a number is prime by dividing it by all integers between
 *  two and prime-1 to see if any divide evenly.  Of course, technically we
 *  only need to go up to sqrt(prime), but...
 */

bool isPrime(unsigned int prime)
{
    for (unsigned int i = 2; i < prime; i++)
    {
        unsigned int j = prime / i;
        if (i * j == prime)
        {
            return false;
        }
    }

    return true;
}

/*
 *  Multiply modulo the prime number.  The casting here is to handle the fact that
 *  on some platforms an integer may only be 16 bits, so we do the math at 32 bits
 *  and then cast back.  This allows us to handle fairly large prime numbers.
 *  (although 929 is really the largest we're likely to care about).
 */

unsigned int times(unsigned int a, unsigned int b, unsigned int prime)
{
    return (unsigned int)(((unsigned long)a * (unsigned long)b) % (unsigned long) prime);
}

/*
 *  Tests to see if the provided primitive element is, in fact, primitive for this particular
 *  prime.  It does this by successively exponentiating the primitive element.  If the
 *  value is, indeed, primitive, all the numbers (except 0) less than the prime will be
 *  generated without any repeats.  The "flag" array keeps track of whether we've seen
 *  a particular output before.  If one does repeat, the provided value is not, indeed,
 *  primitive.
 */

bool isPrimitiveElement(unsigned int prime, unsigned int primitiveElement)
{
    assert(prime >= 2);

    bool retval = true;
    bool *flags = new bool[prime];
    memset(flags, 0, prime * sizeof(bool));

    unsigned int value = 1;
    flags[1] = true;

    for (unsigned int i = 2; i < prime; i++)
    {
        value = times(value, primitiveElement, prime);
        if (flags[value])
        {
            retval = false;
            break;
        }

        flags[value] = true;
    }

    delete[] flags;
    return retval;
}

/*
 *  Finds a primitive element less than the prime by successively testing
 *  beginning at two.  If unable to find an element (the prime 2 doesn't have
 *  one, for example) then return zero.
 */

unsigned int findPrimitiveElement(unsigned int prime)
{
    for (unsigned int i = 2; i < prime; i++)
    {
        if (isPrimitiveElement(i, prime))
        {
            return i;
        }
    }

    return 0;
}

/*
 *  Generate the exponentiation table by successively multiplying by the
 *  primitive element.
 */

void generateExpTable(unsigned int prime, unsigned int primitiveElement)
{
    EXP_TABLE[0] = 1;

    for (unsigned int i = 1; i < prime; i++)
    {
        EXP_TABLE[i] = times(EXP_TABLE[i-1], primitiveElement, prime);
    }
}

/*
 *  Generate the log table by inverting the exponentiation table.
 *  Log(0) is arbitrarily set to zero, since that value won't be found
 *  in the exponentiation table.
 */

void generateLogTable(unsigned int prime)
{
    LOG_TABLE[0] = 0;

    for (unsigned int i = 0; i < prime - 1; i++)
    {
        LOG_TABLE[EXP_TABLE[i]] = i;
    }
}

/*
 *  Dump the contents of a table, formatting it (somewhat) nicely for use in code
 */

void dumpTable(const char *name, const unsigned int *table, unsigned int length)
{
    cout << name << "[] = {\n\t";

    for (unsigned int i = 0; i < length; i++)
    {
        cout << table[i] << ", ";

        if ((i % 8) == 7)
        {
            cout << "\n\t";
        }
    }

    cout << "\n};\n\n";
}

void usage(void)
{
    cerr << "Usage:\n";
    cerr << "primeLogExpGenerator prime [primitiveElement]\n";
}

int main(int argc, const char * argv[])
{
    unsigned int prime;
    unsigned int primitiveElement;

    if (argc < 2 || argc > 3)
    {
        usage();
        return 1;
    }

    if (sscanf(argv[1], "%u", &prime) != 1)
    {
        usage();
        return 1;
    }

    if (prime < 2)
    {
        cerr << "Prime must be at least 2";
        return 1;
    }

    if (!isPrime(prime))
    {
         cerr << prime << " is not prime";
         return 1;
    }

    if (argc == 3)
    {
        if (sscanf(argv[2], "%u", &primitiveElement) != 1)
        {
            usage();
            return 1;
        }

        if (!isPrimitiveElement(prime, primitiveElement))
        {
            cerr << primitiveElement << " is not a primitive element for " << prime << "\n";
            return 1;
        }
    }
    else
    {
        primitiveElement = findPrimitiveElement(prime);
        if (primitiveElement == 0)
        {
            cerr << "Could not find a primitive element for " << prime;
            return 1;
        }
        cout << "Using " << primitiveElement << " as primitive element\n\n";
    }

    EXP_TABLE = new unsigned int[prime];
    LOG_TABLE = new unsigned int[prime];

    generateExpTable(prime, primitiveElement);
    generateLogTable(prime);

    dumpTable("EXP_TABLE", EXP_TABLE, prime);
    dumpTable("LOG_TABLE", LOG_TABLE, prime);

    delete[] EXP_TABLE;
    delete[] LOG_TABLE;

    return 0;
}
