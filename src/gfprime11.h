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

#ifndef GFPRIME11_DOT_H
#define GFPRIME11_DOT_H

#include "gfprime.h"

/*
 *  These two arrays provide the EXP and LOG values for GFPrime<11>
 *  using primitive element 2.  This file should be included in one
 *  place in any project using GFPrime<11>.
 */

const uint32_t SilverBayTech::GFPrime<11>::EXP_TABLE[] = {
        1, 2, 4, 8, 5, 10, 9, 7,
        3, 6, 1,
}; 

const uint32_t SilverBayTech::GFPrime<11>::LOG_TABLE[] = {
        0, 0, 1, 8, 2, 4, 9, 7,
        3, 6, 5,
};

#endif //GFPRIME11_DOT_H
