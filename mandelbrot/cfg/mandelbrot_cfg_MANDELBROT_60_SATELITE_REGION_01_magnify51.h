///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_60_SATELITE_REGION_01_MAGNIFY51_2024_05_02_H
  #define MANDELBROT_CFG_MANDELBROT_60_SATELITE_REGION_01_MAGNIFY51_2024_05_02_H

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_60_SATELITE_REGION_01_magnify51";

  constexpr int  MANDELBROT_CALCULATION_DIGITS10    =      76;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_1D   =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =   50000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.4E-51";

  // This iteration stops at a little Mandelbrot figure
  // at a magnification of approximately 10^{-104}

  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-1.7683830049648722692890015019043698317959353872497374995305914106735151309161730899233435108340865903508510745";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "-0.0035564756051580419085635598914228270868497588929218730141623308457205131419997685780856071519939478350604525";

  #include <mandelbrot/cfg/mandelbrot_cfg.h>

#endif // MANDELBROT_CFG_MANDELBROT_60_SATELITE_REGION_01_MAGNIFY51_2024_05_02_H
