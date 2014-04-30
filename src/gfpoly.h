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

#ifndef GFPOLY_DOT_H
#define GFPOLY_DOT_H

#include <vector>
#include <ostream>
#include <stdint.h>

namespace SilverBayTech
{
    template<typename GF>
    class GFPoly
    {
    public:
        /*
         *  Initializes a polynomial with the specified number of coefficients,
         *  all zero.
         */
        GFPoly(size_t numCoef = 1)
            :   _coefficients(numCoef)
        {
        }

        /*
         *  Initializes a polynomial with the specified coefficients.  The input
         *  coefficients are listed with the highest exponent first.
         */
        GFPoly(const GF *pCoef, size_t numCoef)
            :   _coefficients(numCoef)
        {
            for (size_t i = 0; i < numCoef; i++, pCoef++)
            {
                size_t index = numCoef - i - 1;
                _coefficients[index] = *pCoef;
            }
        }

        /*
         *  Initializes a polynomial with the specified coefficients.  The input
         *  coefficients are listed with the highest exponent first.
         */
        GFPoly(const uint32_t *pCoef, size_t numCoef)
            :   _coefficients(numCoef)
        {
            for (size_t i = 0; i < numCoef; i++, pCoef++)
            {
                size_t index = numCoef - i - 1;
                _coefficients[index] = GF(*pCoef);
            }
        }

        /*
         *  Copy constructor
         */

        GFPoly(const GFPoly<GF>& other)
            :   _coefficients(other._coefficients)
        {
        }

        /*
         *  Assignment operator
         */
        GFPoly<GF>& operator=(const GFPoly<GF>& other)
        {
            if (this != &other)
            {
                _coefficients = other._coefficients;
            }

            return *this;
        }

        /*
         *  Equality operations.  Two polynomials are equal if all coefficients
         *  are equal, or if all coefficients of the shorter match the longer and
         *  all "extra" coefficients of the longer are zero.  (In other words,
         *  leading zeros do not cause a polynomial to be "different."
         */

        bool operator==(const GFPoly<GF>& other) const
        {
            if (this == &other)
            {
                return true;
            }

            const GFPoly<GF> *pLonger = this;
            const GFPoly<GF> *pShorter = &other;
            if (pLonger->getNumCoef() < pShorter->getNumCoef())
            {
                pLonger = &other;
                pShorter = this;
            }

            size_t shorterCount = pShorter->getNumCoef();
            for (size_t i = 0; i < shorterCount; i++)
            {
                if (_coefficients[i] != other._coefficients[i])
                {
                    return false;
                }
            }

            size_t longerCount = pLonger->getNumCoef();
            for (size_t i = shorterCount; i < longerCount; i++)
            {
                if (pLonger->_coefficients[i].toInt() != 0)
                {
                    return false;
                }
            }

            return true;
        }

        bool operator!=(const GFPoly<GF>& other) const
        { 
            return !(*this == other);
        }


        /*
         *  Subscript operations - returns the appropriate coefficient.
         *  Caller is responsible for not "going off the end."
         */
        GF& operator[](size_t n)
        {
            return _coefficients[n];
        }

        const GF& operator[](size_t n) const
        {
            return _coefficients[n];
        }

        /*
         *  Number of coefficients.
         */
        size_t getNumCoef() const
        {
            return _coefficients.size();
        }

        /*
         *  Evaluate the polynomial at the specified value
         */
        GF eval(const GF& value) const
        {
            GF output = (*this)[0];

            size_t thisCount = getNumCoef();
            for (size_t i = 1; i < thisCount; i++)
            {
                GF coef = (*this)[i];
                output += coef * value.pow(i);
            }

            return output;
        }

        /*
         *  Multiply this polynomial by another.
         */
        GFPoly<GF> operator *(const GFPoly<GF>& other) const
        {
            size_t thisCount = getNumCoef();
            size_t otherCount = other.getNumCoef();
            size_t outputCount = thisCount + otherCount - 1;
            GFPoly<GF> output(outputCount);

            for (size_t i = 0; i < thisCount; i++)
            {
                GF thisCoef = (*this)[i];
                for (size_t j = 0; j < otherCount; j++)
                {
                    output[i+j] = output[i+j] + thisCoef * other[j];
                }
            }

            return output;
        }

        /*
         *  Multiply this polynomial by a constant, resulting in a new
         *  polynomial.
         */
        GFPoly<GF> operator *(const GF& value) const
        {
            size_t thisCount = getNumCoef();
            GFPoly<GF> output(thisCount);
            for (size_t i = 0; i < thisCount; i++)
            {
                output[i] = (*this)[i] * value;
            }

            return output;
        }

        /*
         *  Shift this polynomial to the left by the specified amount.
         *  (i.e. equivalent to multiplying by x^n)
         */
        GFPoly<GF> operator <<(size_t n) const
        {
            size_t thisCount = getNumCoef();
            GFPoly<GF> output(thisCount + n);
            for (size_t i = 0; i < thisCount; i++)
            {
                output[i+n] = (*this)[i];
            }

            return output;
        }

        /*
         *  Subtract a polynomial from this one.
         */
        GFPoly<GF> operator-(const GFPoly<GF>& other) const
        {
            size_t thisCount = getNumCoef();
            size_t otherCount = other.getNumCoef();
            size_t outputCount = thisCount;
            if (otherCount > thisCount)
            {
                outputCount = otherCount;
            }

            GFPoly<GF> output(outputCount);
            for (size_t i = 0; i < outputCount; i++)
            {
                GF thisCoef;
                if (i < thisCount)
                {
                    thisCoef = (*this)[i];
                }

                GF otherCoef;
                if (i < otherCount)
                {
                    otherCoef = other[i];
                }

                output[i] = thisCoef - otherCoef;
            }

            return output;
        }

        /*
         *  Remainder when this polyomial is divided by another.
         */
        GFPoly<GF> operator%(const GFPoly<GF>& other) const
        {
            GFPoly<GF> dividend(*this);
            GFPoly<GF> divisor(other);
            divisor.trimLeadingZeros();

            size_t divisorCoefs = divisor.getNumCoef();
            size_t dividendCoefs = dividend.getNumCoef();

            GF leadingDivisorCoef = divisor[divisorCoefs - 1];

            if (divisorCoefs <= dividendCoefs)
            {
                size_t maxShift = dividendCoefs - divisorCoefs;

                for (size_t shift = 0; shift <= maxShift; shift++)
                {
                    GF factor = dividend[dividendCoefs - 1 - shift];
                    if (factor.toInt() != 0)
                    {
                        factor /= leadingDivisorCoef;
                        size_t offset = maxShift - shift;

                        for (size_t i = 0; i < divisorCoefs; i++)
                        {
                            dividend[i + offset] -= divisor[i] * factor;
                        }
                    }
                }
            }

            dividend.trimLeadingZeros(divisorCoefs - 1);

            return dividend;
        }

        /*
         *  Remove any leading zero coefficients.
         *  Will not eliminate the last (constant) coefficient.
         */
        void trimLeadingZeros(uint32_t minCoef = 1)
        {
            if (minCoef == 0)
            {
                minCoef = 1;
            }

            size_t maxNonZeroCoef = 0;
            size_t thisCount = getNumCoef();
            for (size_t i = 0; i < thisCount; i++)
            {
                if ((*this)[i] != GF(0))
                {
                    maxNonZeroCoef = i;
                }
            }

            uint32_t resizeTo = maxNonZeroCoef + 1;
            if (resizeTo < minCoef)
            {
                resizeTo = minCoef;
            }

            _coefficients.resize(resizeTo);
        }

    private:
        std::vector<GF>  _coefficients;
    };

    template<typename GF>
    std::ostream& operator<< (std::ostream& stream, const GFPoly<GF>& poly)
    {
        size_t size = poly.getNumCoef();
        for (size_t i = 0; i < size; i++)
        {
            size_t exponent = size - i - 1;

            if (i > 0)
            {
                stream << '+';
            }
            stream << poly[exponent];
            if (exponent >= 1)
            {
                stream << 'x';
                if (exponent >= 2)
                {
                    stream << '^' << exponent;
                }
            }
        }
        return stream;
    }
}
#endif  // GFPOLY_DOT_H
