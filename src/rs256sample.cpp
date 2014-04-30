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
#include "eccUtils.h"
#include "gfbinary.h"
#include "gfpoly.h"
#include "gfbinary256.h"

using namespace SilverBayTech;
using namespace std;

typedef GFBinary<256> GF256;
static const uint32_t INPUT[] = {0x10, 0x20, 0x0C, 0x56, 0x61, 0x80, 0xEC, 0x11, 0xEC, 0x11, 0xEC, 0x11, 0xEC, 0x11, 0xEC, 0x11};

GFPoly<GF256> buildGenerator(void)
{
    GFPoly<GF256> generator(1);
    generator[0] = 1;

    for (uint32_t i = 0; i < 10; i++)
    {
        GFPoly<GF256> root(2);
        root[0] = -GF256(2).pow(i);
        root[1] = 1;

        generator = generator * root;
    }

    return generator;
}

int main(void)
{
    GFPoly<GF256> message(INPUT, ARRAY_LENGTH(INPUT));

    cout << "Message polynomial: " << message << '\n';

    GFPoly<GF256> generator = buildGenerator();

    cout << "Generator polynomial: " << generator << '\n';

    GFPoly<GF256> result = message << (generator.getNumCoef() - 1);

    GFPoly<GF256> remainder = result % generator;

    cout << "Remainder: " << remainder << '\n';

    result = result - remainder;

    cout << "Result: " << result << '\n';

    for (uint32_t i = 0; i < 10; i++)
    {
        cout << "At 2^" << i << ": " << result.eval(GF256(2).pow(i)) << '\n';
    }

    return 0;
}
