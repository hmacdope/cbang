/******************************************************************************\

          This file is part of the C! library.  A.K.A the cbang library.

                Copyright (c) 2003-2023, Cauldron Development LLC
                               All rights reserved.

         The C! library is free software: you can redistribute it and/or
        modify it under the terms of the GNU Lesser General Public License
       as published by the Free Software Foundation, either version 2.1 of
               the License, or (at your option) any later version.

        The C! library is distributed in the hope that it will be useful,
          but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
                 Lesser General Public License for more details.

         You should have received a copy of the GNU Lesser General Public
                 License along with the C! library.  If not, see
                         <http://www.gnu.org/licenses/>.

        In addition, BSD licensing may be granted on a case by case basis
        by written permission from at least one of the copyright holders.
           You may request written permission by emailing the authors.

                  For information regarding this software email:
                                 Joseph Coffland
                          joseph@cauldrondevelopment.com

\******************************************************************************/

#pragma once

#include <cmath>
#include <cmath>
#include <limits>
#include <cfloat>


namespace cb {
  namespace Math {
#if defined(_WIN32) && !defined(__MINGW32__)

    // Windows doesn't have round()
    inline static double round(double x) {return floor(x + 0.5);}
    inline static float round(float x) {return floorf(x + 0.5);}

    // Or isnan
    inline static bool isnan(double x) {return _isnan(x);}
    inline static bool isnan(float x) {return _isnan(x);}

    // Or isinf
    inline static bool isinf(double x) {return !_finite(x) && !_isnan(x);}
    inline static bool isinf(float x) {return !_finite(x) && !_isnan(x);}

#else
    inline static double round(double x) {return ::round(x);}
    inline static float round(float x) {return roundf(x);}
    inline static bool isnan(double x) {return std::isnan(x);}
    inline static bool isnan(float x) {return std::isnan(x);}
    inline static bool isinf(double x) {return std::isinf(x);}
    inline static bool isinf(float x) {return std::isinf(x);}
#endif

    inline static bool isfinite(double x) {return !(isnan(x) || isinf(x));}
    inline static bool isfinite(float x) {return !(isnan(x) || isinf(x));}


    inline static double nextUp(double x) {
      return nextafter(x, std::numeric_limits<double>::infinity());
    }


    inline static double nextDown(double x) {
      return nextafter(x, -std::numeric_limits<double>::infinity());
    }
  }
}

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
