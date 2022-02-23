﻿ckormanyos/mandelbrot
==================

ckormanyos/mandelbrot implements a header-only C++ template library for
extended precision Mandelbrot fractal iterations.

It is intended to be used for so-called _deep_ _dives_ involving multiple-precision
floating-point or fixed-point types.

## Design Goals

The following design goals have been incorporated.
  - ckormanyos/mandelbrot is written in header-only C++11, and compatible through C++11, 14, 17, 20.
  - The inner loop of fractal iteration uses multiple, parallel CPU cores.
  - C++ template design allows flexible use of any appropriate kind of big-number type.
  - Visualization of the result uses color-stretching techniques with the histogram method.
  - Graphical representation uses [Boost.Gil](https://www.boost.org/doc/libs/1_78_0/libs/gil/doc/html/index.html) in combination with the JPEG-6b library.
  - Color schemes can be easily adapted via straightforward creation (or modification) of a skinny derived class.

## Sample Images

### Swirly Seahorses and Mini Mandelbrot

A beautiful iteration result showing swirly seahorses and a mini Mandelbrot image
in black-and-white color representation is shown below. The image
has the following features/parameters.

  - The square image has <img src="https://render.githubusercontent.com/render/math?math=2048\,\times\,2048"> pixels.
  - Centered at the point <img src="https://render.githubusercontent.com/render/math?math=(-0.7453983606667815,\,0.1125046349959942)">.
  - Uses a half-width of <img src="https://render.githubusercontent.com/render/math?math=1.76\,\times\,10^{-12}">.
  - Computed with <img src="https://render.githubusercontent.com/render/math?math=2,000"> iteratons using the `cpp_dec_float` type from [Boost.Multiprecison](https://www.boost.org/doc/libs/1_78_0/libs/multiprecision/doc/html/index.html) instantiated with <img src="https://render.githubusercontent.com/render/math?math=37"> decimal digits of precision.

![](./images/mandelbrot_MANDELBROT_05_SEAHORSES.jpg)

### A Really Deep Dive

My personal best deep dive has a scale of approximately
<img src="https://render.githubusercontent.com/render/math?math=10^{-311}">,
i.e., having a magnification of approximately
<img src="https://render.githubusercontent.com/render/math?math=10^{311}">.
This magnification scale is
<img src="https://render.githubusercontent.com/render/math?math=1">
followed by
<img src="https://render.githubusercontent.com/render/math?math=311">
zeros.

The image showing this deep dive has the following features/parameters and is shown below.

  - The square image has <img src="https://render.githubusercontent.com/render/math?math=1536\,\times\,1536"> pixels.
  - Centered at the point <img src="https://render.githubusercontent.com/render/math?math=(0.3602404434376143632361252444495453084826\ldots,\,-0.6413130610648031748603750151793020665794\ldots"> (see the code for the full precision).
  - Uses a half-width of <img src="https://render.githubusercontent.com/render/math?math=4.4\,\times\,10^{-311}">.
  - Computed with <img src="https://render.githubusercontent.com/render/math?math=60,000"> iteratons using the `gmp_float` type from [Boost.Multiprecison](https://www.boost.org/doc/libs/1_78_0/libs/multiprecision/doc/html/index.html) instantiated with <img src="https://render.githubusercontent.com/render/math?math=365"> decimal digits of precision.

![](./images/mandelbrot_MANDELBROT_20_ZOOM_VERY_DEEP_00.jpg)

## Using ckormanyos/mandelbrot

TBD. Show how to make/use various configurations and also create and show
a few stock configuration examples.

TBD: How much of a _gallery_ should be shown?

## Adaptions of and Notes on JPEG-6b

We use a modified version of jpeg-6b located [here](./jpeg-6b-2022).
According to license agreement, it is referred to as
_the_ _Independent_ _JPEG_ _Group's_ _software_.

See the original _README_ located [here](./jpeg-6b-2022)
for more information, with explicit licensing terms
of _the_ _Independent_ _JPEG_ _Group's_ _software_.
