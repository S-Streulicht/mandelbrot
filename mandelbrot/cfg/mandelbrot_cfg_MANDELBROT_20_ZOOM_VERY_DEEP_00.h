///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022 - 2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_20_ZOOM_VERY_DEEP_00_2022_02_24_H
  #define MANDELBROT_CFG_MANDELBROT_20_ZOOM_VERY_DEEP_00_2022_02_24_H

  // At the moment, this is my personal best deep dive with relatively
  // high precision. This deep dive features magnification of
  // approximately 1e310, which is 1 and 310 zeros. Generating this
  // image took about 15 hours on my machine.

  // TBD: Try to zoom even deeper with higher precision and more iterations.
  // The remarkable video here: https://www.youtube.com/watch?v=pCpLWbHVNhk
  // makes use of the same high-precision coordinate (shown below).
  // The author of that video, for instance, reports and beautifully
  // depicts achieving a deep zoom of approximately 1e1091 at this
  // staggeringly high-precision coordinate.

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_20_ZOOM_VERY_DEEP_00";

  constexpr int  MANDELBROT_CALCULATION_DIGITS10    =     365;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =   60000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "4.4E-311";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "4.4E-311";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "+0.360240443437614363236125244449545308482607807958585750488375814740195346059218100311752936722773426396233731729724987737320035372683285317664532401218521579554288661726564324134702299962817029213329980895208036363104546639698106204384566555001322985619004717862781192694046362748742863016467354574422779443226982622356594130430232458472420816652623492974891730419252651127672782407292315574480207005828774566475024380960675386215814315654794021855269375824443853463117354448779647099224311848192893972572398662626725254769950976527431277402440752868498588785436705371093442460696090720654908973712759963732914849861213100695402602927267843779747314419332179148608587129105289166676461292845685734536033692577618496925170576714796693411776794742904333484665301628662532967079174729170714156810530598764525260869731233845987202037712637770582084286587072766838497865108477149114659838883818795374195150936369987302574377608649625020864292915913378927790344097552591919409137354459097560040374880346637533711271919419723135538377394364882968994646845930838049998854075817859391340445151448381853615103761584177161812057928";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "-0.6413130610648031748603750151793020665794949522823052595561775430644485741727536902556370230689681162370740565537072149790106973211105273740851993394803287437606238596262287731075999483940467161288840614581091294325709988992269165007394305732683208318834672366947550710920088501655704252385244481168836426277052232593412981472237968353661477793530336607247738951625817755401065045362273039788332245567345061665756708689359294516668271440525273653083717877701237756144214394870245598590883973716531691124286669552803640414068523325276808909040317617092683826521501539932397262012011082098721944643118695001226048977430038509470101715555439047884752058334804891389685530946112621573416582482926221804767466258346014417934356149837352092608891639072745930639364693513216719114523328990690069588676087923656657656023794484324797546024248328156586471662631008741349069961493817600100133439721557969263221185095951241491408756751582471307537382827924073746760884081704887902040036056611401378785952452105099242499241003208013460878442953408648178692353788153787229940221611731034405203519945313911627314900851851072122990492499999999999999999991";

  #include <mandelbrot/cfg/mandelbrot_cfg.h>

#endif // MANDELBROT_CFG_MANDELBROT_20_ZOOM_VERY_DEEP_00_2022_02_24_H
