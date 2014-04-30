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

typedef GFPrime<929> GF929;
static const uint32_t INPUT[] = {5, 453, 178, 121, 239};

int main(void)
{
    GFPoly<GF929> message(INPUT, ARRAY_LENGTH(INPUT));

    cout << "Message polynomial: " << message << '\n';

    GFPoly<GF929> root1(2);
    root1[0] = -GF929(3);
    root1[1] = 1;

    cout << "Root polynomial 1: " << root1 << '\n';

    GFPoly<GF929> root2(2);
    root2[0] = -GF929(3).pow(2);
    root2[1] = 1;

    cout << "Root polynomial 2: " << root2 << '\n';

    GFPoly<GF929> root3(2);
    root3[0] = -GF929(3).pow(3);
    root3[1] = 1;

    cout << "Root polynomial 3: " << root3 << '\n';

    GFPoly<GF929> root4(2);
    root4[0] = -GF929(3).pow(4);
    root4[1] = 1;

    cout << "Root polynomial 4: " << root4 << '\n';

    GFPoly<GF929> generator = root1 * root2 * root3 * root4;

    cout << "Generator polynomial: " << generator << '\n';

    GFPoly<GF929> result = message << 4;

    GFPoly<GF929> remainder = result % generator;

    cout << "Remainder: " << remainder << '\n';

    result = result - remainder;

    cout << "Result: " << result << '\n';

    cout << "At 3: " << result.eval(GF929(3)) << '\n';
    cout << "At 3^2: " << result.eval(GF929(3).pow(2)) << '\n';
    cout << "At 3^3: " << result.eval(GF929(3).pow(3)) << '\n';
    cout << "At 3^4: " << result.eval(GF929(3).pow(4)) << '\n';

    return 0;
}
