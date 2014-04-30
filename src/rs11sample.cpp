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
#include "gfprime.h"
#include "gfpoly.h"

using namespace SilverBayTech;
using namespace std;

typedef GFPrime<11> GF11;

static const uint32_t INPUT[] = {8, 6, 7, 5, 3, 0, 9};

int main(void)
{
    GFPoly<GF11> message(INPUT, ARRAY_LENGTH(INPUT));

    cout << "Message polynomial: " << message << '\n';

    GFPoly<GF11> root1(2);
    root1[0] = -GF11(2);
    root1[1] = 1;

    cout << "Root polynomial 1: " << root1 << '\n';

    GFPoly<GF11> root2(2);
    root2[0] = -GF11(2).pow(2);
    root2[1] = 1;

    cout << "Root polynomial 2: " << root2 << '\n';

    GFPoly<GF11> generator = root1 * root2;

    cout << "Generator polynomial: " << generator << '\n';

    GFPoly<GF11> work = message << 2;

    cout << "Work: " << work << '\n';
    while(work.getNumCoef() >= generator.getNumCoef())
    {
        GF11 factor = work[work.getNumCoef() - 1];
        cout << "Factor: " << factor << '\n';
        uint32_t currentShift = work.getNumCoef() - generator.getNumCoef();
        GFPoly<GF11> subtract = (generator << currentShift) * factor;
        cout << "Subtract: " << subtract << '\n';
        work = work - subtract;
        work.trimLeadingZeros();
        cout << "Work: " << work << '\n';
    }

    GFPoly<GF11> result = message << (generator.getNumCoef() - 1);
    result = result - work;

    cout << "Result: " << result << '\n';

    cout << "At 2: " << result.eval(GF11(2)) << '\n';
    cout << "At 2^2: " << result.eval(GF11(2).pow(2)) << '\n';

    return 0;
}
