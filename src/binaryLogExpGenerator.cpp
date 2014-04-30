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
 *  with a binary number of elements.
 *
 *  Unlike some of the other samples in this project it does not need to
 *  be recompiled to change the size of the field - it takes this as a
 *  command line parameters.
 */

#include <iostream>
#include <assert.h>

using namespace std;

unsigned int GF_SIZE;
unsigned int GF_POLYNOMIAL;
unsigned int *EXP_TABLE = 0;
unsigned int *LOG_TABLE = 0;

bool analyzePolynomial(const char *pBits)
{
    assert(pBits != NULL);

    if (strlen(pBits) < 3)
    {
        cerr << "Polynomial bit field must have at least three elements\n";
        return false;
    }

    if (*pBits != '1')
    {
        cerr << "Polynomial bit field must begin with a '1'\n";
        return false;
    }

    GF_SIZE = 1;
    GF_POLYNOMIAL = 0;

    while(*pBits != '\0')
    {
        GF_SIZE <<= 1;
        GF_POLYNOMIAL <<= 1;

        switch(*pBits)
        {
        case '0':
            break;
        case '1':
            GF_POLYNOMIAL |= 1;
            break;
        default:
            cerr << "Only '1' and '0' allowed in polynomial bit field\n";
            return false;
        }

        pBits++;
    }

    GF_SIZE >>= 1;

    return true;
}

void generateExpTable(void)
{
    EXP_TABLE[0] = 1;

    for (unsigned int i = 1; i < GF_SIZE; i++)
    {
        EXP_TABLE[i] = EXP_TABLE[i-1] << 1;
        if (EXP_TABLE[i] >= GF_SIZE)
        {
            EXP_TABLE[i] ^= GF_POLYNOMIAL;
        }
    }
}

/*
 *  Generate the log table by inverting the exponentiation table.
 *  Log(0) is arbitrarily set to zero, since that value won't be found
 *  in the exponentiation table.
 */

void generateLogTable()
{
    LOG_TABLE[0] = 0;

    for (unsigned int i = 0; i < GF_SIZE - 1; i++)
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
    cerr << "binaryLogExpGenerator primePolyBitField\n";
}


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        usage();
        return 1;
    }

    if (!analyzePolynomial(argv[1]))
    {
        return 1;
    }

    cout << "GF(" << GF_SIZE << ") with prime polynomial " << argv[1] << "\n\n";

    EXP_TABLE = new unsigned int[GF_SIZE];
    LOG_TABLE = new unsigned int[GF_SIZE];

    generateExpTable();
    generateLogTable();

    dumpTable("EXP_TABLE", EXP_TABLE, GF_SIZE);
    dumpTable("LOG_TABLE", LOG_TABLE, GF_SIZE);

    delete[] EXP_TABLE;
    delete[] LOG_TABLE;

    return 0;
}
