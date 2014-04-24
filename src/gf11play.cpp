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
#include "gf11.h"

using namespace std;
using SilverBayTech::GF11;

void verifyAdditiveInverse(const GF11& symbol)
{
    for (uint32_t i = 0; i < GF11::FIELD_SIZE; i++)
    {
        GF11 attempt(i);
        GF11 sum = attempt + symbol;
        if (sum == GF11(0))
        {
            return;
        }
    }

    cerr << "Did not find additive inverse for GF11(" << symbol << ")";
}

void verifyAdditiveInverses()
{
    for (uint32_t i = 0; i < GF11::FIELD_SIZE; i++)
    {
        verifyAdditiveInverse(GF11(i));
    }
}

void verifyMultiplicativeInverse(const GF11& symbol)
{
    for (uint32_t i = 0; i < GF11::FIELD_SIZE; i++)
    {
        GF11 attempt(i);
        GF11 sum = attempt * symbol;
        if (sum == GF11(1))
        {
            return;
        }
    }

    cerr << "Did not find multiplicative inverse for GF11(" << symbol << ")";
}

void verifyMultiplicativeInverses()
{
    for (uint32_t i = 1; i < GF11::FIELD_SIZE; i++)
    {
        verifyMultiplicativeInverse(GF11(i));
    }
}

void printFirstRow(const char *op)
{
    cout << op;
    for (uint32_t i = 0; i < GF11::FIELD_SIZE; i++)
    {
        cout << '\t' << GF11(i);
    }
    cout << '\n';
}

void printAdditionTable()
{
    printFirstRow("+");
    for (uint32_t i = 0; i < GF11::FIELD_SIZE; i++)
    {
        GF11 value1(i);
        fputs((const char *)value1, stdout);

        for (uint32_t j = 0; j < GF11::FIELD_SIZE; j++)
        {
            GF11 value2(j);
            GF11 sum = value1 + value2;

            cout << '\t' << sum;
        }
        cout << '\n';
    }
}

void printMultiplicationTable()
{
    printFirstRow("*");
    for (uint32_t i = 0; i < GF11::FIELD_SIZE; i++)
    {
        GF11 value1(i);
        fputs((const char *)value1, stdout);

        for (uint32_t j = 0; j < GF11::FIELD_SIZE; j++)
        {
            GF11 value2(j);
            GF11 product = value1 * value2;

            cout << '\t' << product;
        }
        cout << '\n';
    }
}

void printPowerTable()
{
    cout << "N";

    for (uint32_t i = 0; i < GF11::FIELD_SIZE; i++)
    {
        cout << '\t' << GF11(i) << "^N";
    }

    cout << '\n';

    for (uint32_t i = 0; i <=GF11::FIELD_SIZE; i++)
    {
        cout << i;

        for (uint32_t j = 0; j < GF11::FIELD_SIZE; j++)
        {
            cout << '\t' << GF11(j).pow(i);
        }

        cout << '\n';
    }
}

void printPowersOfTwo()
{
    cout << "N\t2N\tN\t2N\n";
    for (uint32_t i = 0; i < GF11::FIELD_SIZE; i++)
    {
        cout << i << '\t' << GF11(2).pow(i) << '\t' << i + GF11::FIELD_SIZE << '\t' << GF11(2).pow(i + GF11::FIELD_SIZE) << '\n';
    }
}

void printExpLogTable()
{
    GF11 exp[GF11::FIELD_SIZE];
    uint32_t log[GF11::FIELD_SIZE];

    log[0] = 0;

    for (uint32_t i = 0; i < GF11::FIELD_SIZE; i++)
    {
        exp[i] = GF11(2).pow(i);
        log[exp[i].toInt()] = i;
    }

    cout << "N\t2^N\ta\tlog a\n";
    for (uint32_t i = 0; i < GF11::FIELD_SIZE; i++)
    {
        cout << i << '\t' << exp[i] << '\t' << GF11(i) << '\t' << log[i] << '\n';
    }
}

int main(void)
{
    verifyAdditiveInverses();
    verifyMultiplicativeInverses();

    printAdditionTable();
    cout << '\n';

    printMultiplicationTable();
    cout << '\n';

    printPowerTable();
    cout << '\n';

    printPowersOfTwo();
    cout << '\n';

    printExpLogTable();
    cout << '\n';

    cout << "Done";
    return 0;
}
