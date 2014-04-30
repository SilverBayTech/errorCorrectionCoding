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

#ifndef GFBINARY8_DOT_H
#define GFBINARY8_DOT_H

#include "gfbinary.h"

/*
 *  These two arrays provide the EXP and LOG values for GFBinary<8>
 *  using primitive element 2 and prime polynomial x^3+x+1.
 *  This file should be included in one place in any project using 
 *  GFBinary<8>.
 */

const uint32_t SilverBayTech::GFBinary<8>::EXP_TABLE[] = {
        1, 2, 4, 3, 6, 7, 5, 1
}; 

const uint32_t SilverBayTech::GFBinary<8>::LOG_TABLE[] = {
        0, 0, 1, 3, 2, 6, 4, 5
};

#endif //GFBINARY8_DOT_H
