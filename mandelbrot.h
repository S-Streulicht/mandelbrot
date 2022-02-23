///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2015 - 2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_2015_06_15_H
  #define MANDELBROT_2015_06_15_H

  #include <atomic>
  #include <ctime>
  #include <iomanip>
  #include <ostream>
  #include <string>

  #include <boost/gil/extension/io/jpeg/old.hpp>
  #include <boost/gil/image.hpp>
  #include <boost/gil/typedefs.hpp>
  #include <boost/lexical_cast.hpp>

  #include <mandelbrot_color.h>
  #include <parallel_for.h>

  #if(__cplusplus >= 201703L)
  namespace ckormanyos::mandelbrot {
  #else
  namespace ckormanyos { namespace mandelbrot { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  // Declare a base class for the Mandelbrot configuration.
  template<typename NumericType,
           const std::uint_fast32_t MaxIterations>
  class mandelbrot_config_base
  {
  protected:
    using mandelbrot_config_numeric_type = NumericType;

  public:
    static constexpr auto max_iterations = static_cast<std::uint_fast32_t>(MaxIterations);

    mandelbrot_config_base() = delete;

    mandelbrot_config_base(const mandelbrot_config_base& other)
      : my_x_lo  (other.my_x_lo),
        my_x_hi  (other.my_x_hi),
        my_y_lo  (other.my_y_lo),
        my_y_hi  (other.my_y_hi),
        my_width (other.my_width),
        my_height(other.my_height) { }

    mandelbrot_config_base(const mandelbrot_config_numeric_type& xl,
                           const mandelbrot_config_numeric_type& xh,
                           const mandelbrot_config_numeric_type& yl,
                           const mandelbrot_config_numeric_type& yh)
      : my_x_lo  (xl),
        my_x_hi  (xh),
        my_y_lo  (yl),
        my_y_hi  (yh),
        my_width (my_x_hi - my_x_lo),
        my_height(my_y_hi - my_y_lo) { }

    auto operator=(const mandelbrot_config_base& other) -> mandelbrot_config_base&
    {
      if(this != &other)
      {
        my_x_lo   = other.my_x_lo;
        my_x_hi   = other.my_x_hi;
        my_y_lo   = other.my_y_lo;
        my_y_hi   = other.my_y_hi;
        my_width  = other.my_width;
        my_height = other.my_height;
      }

      return *this;
    }

    auto operator=(mandelbrot_config_base&& other) noexcept -> mandelbrot_config_base&
    {
      my_x_lo   = other.my_x_lo;
      my_x_hi   = other.my_x_hi;
      my_y_lo   = other.my_y_lo;
      my_y_hi   = other.my_y_hi;
      my_width  = other.my_width;
      my_height = other.my_height;

      return *this;
    }

    virtual ~mandelbrot_config_base() = default;

    auto x_lo() const -> const mandelbrot_config_numeric_type& { return my_x_lo; }
    auto x_hi() const -> const mandelbrot_config_numeric_type& { return my_x_hi; }
    auto y_lo() const -> const mandelbrot_config_numeric_type& { return my_y_lo; }
    auto y_hi() const -> const mandelbrot_config_numeric_type& { return my_y_hi; }

    auto get_width () -> const mandelbrot_config_numeric_type& { return my_width; }
    auto get_height() -> const mandelbrot_config_numeric_type& { return my_height; }

    virtual auto step() const -> const mandelbrot_config_numeric_type& = 0;

    auto integral_width() const -> std::uint_fast32_t
    {
      const auto non_rounded_width2 =
        static_cast<std::uint_fast32_t>
        (
          mandelbrot_config_numeric_type(my_width * 2U) / this->step()
        );

      return
        static_cast<std::uint_fast32_t>
        (
          static_cast<std::uint_fast32_t>(non_rounded_width2 + 1U) / 2U
        );
    }

    auto integral_height() const -> std::uint_fast32_t
    {
      const auto non_rounded_height2 =
        static_cast<std::uint_fast32_t>
        (
          mandelbrot_config_numeric_type(my_height * 2U) / this->step()
        );

      return
        static_cast<std::uint_fast32_t>
        (
          static_cast<std::uint_fast32_t>(non_rounded_height2 + 1U) / 2U
        );
    }

  private:
    const mandelbrot_config_numeric_type my_x_lo;
    const mandelbrot_config_numeric_type my_x_hi;
    const mandelbrot_config_numeric_type my_y_lo;
    const mandelbrot_config_numeric_type my_y_hi;
    const mandelbrot_config_numeric_type my_width;
    const mandelbrot_config_numeric_type my_height;
  };

  // Make a template class that represents the Mandelbrot configuration.
  // This class automatically creates sensible parameters based on
  // the resolution of the fixed-point type supplied in the template
  // parameter. If a custom pixel count is required, the step()
  // method can be modified accordingly.
  template<typename NumericType,
           const std::uint_fast32_t MaxIterations,
           const std::uint_fast32_t PixelCountX>
  class mandelbrot_config final : public mandelbrot_config_base<NumericType, MaxIterations>
  {
  private:
    using base_class_type = mandelbrot_config_base<NumericType, MaxIterations>;

  public:
    using mandelbrot_config_numeric_type = typename base_class_type::mandelbrot_config_numeric_type;

    mandelbrot_config(const typename base_class_type::mandelbrot_config_numeric_type& xl,
                      const typename base_class_type::mandelbrot_config_numeric_type& xh,
                      const typename base_class_type::mandelbrot_config_numeric_type& yl,
                      const typename base_class_type::mandelbrot_config_numeric_type& yh)
      : base_class_type(xl, xh, yl, yh),
        my_step(base_class_type::get_width() / PixelCountX) { }

    mandelbrot_config(const std::string& str_xl,
                      const std::string& str_xh,
                      const std::string& str_yl,
                      const std::string& str_yh)
      : base_class_type(boost::lexical_cast<typename base_class_type::mandelbrot_config_numeric_type>(str_xl),
                        boost::lexical_cast<typename base_class_type::mandelbrot_config_numeric_type>(str_xh),
                        boost::lexical_cast<typename base_class_type::mandelbrot_config_numeric_type>(str_yl),
                        boost::lexical_cast<typename base_class_type::mandelbrot_config_numeric_type>(str_yh)),
        my_step(base_class_type::get_width() / PixelCountX) { }

    mandelbrot_config(const char* pc_xl,
                      const char* pc_xh,
                      const char* pc_yl,
                      const char* pc_yh)
      : base_class_type(boost::lexical_cast<typename base_class_type::mandelbrot_config_numeric_type>(std::string(pc_xl)),
                        boost::lexical_cast<typename base_class_type::mandelbrot_config_numeric_type>(std::string(pc_xh)),
                        boost::lexical_cast<typename base_class_type::mandelbrot_config_numeric_type>(std::string(pc_yl)),
                        boost::lexical_cast<typename base_class_type::mandelbrot_config_numeric_type>(std::string(pc_yh))),
        my_step(base_class_type::get_width() / PixelCountX) { }

    mandelbrot_config(const mandelbrot_config& other)
      : base_class_type(static_cast<const base_class_type&>(other)),
        my_step(other.my_step) { }

    mandelbrot_config(mandelbrot_config&& other) noexcept
      : base_class_type(static_cast<base_class_type&&>(other)),
        my_step(other.my_step) { }

    ~mandelbrot_config() final = default;

    auto operator=(const mandelbrot_config& other) -> mandelbrot_config&
    {
      if(this != other)
      {
        static_cast<void>(base_class_type::operator=(static_cast<const base_class_type&>(other)));

        my_step = other.my_step;
      }

      return *this;
    }

    auto operator=(mandelbrot_config&& other) noexcept -> mandelbrot_config&
    {
      static_cast<void>(base_class_type::operator=(static_cast<base_class_type&&>(other)));

      my_step = other.my_step;

      return *this;
    }

  private:
    mandelbrot_config_numeric_type my_step;

    auto step() const -> const mandelbrot_config_numeric_type& final { return my_step; }
  };

  // This class generates the rows of the mandelbrot iteration.
  // The coordinates are set up according to the Mandelbrot configuration.
  template<typename NumericType,
           const std::uint_fast32_t MaxIterations>
  class mandelbrot_generator final
  {
  private:
    using numeric_type = NumericType;

    static constexpr auto max_iterations = static_cast<std::uint_fast32_t>(MaxIterations);

  public:
    using mandelbrot_config_type = mandelbrot_config_base<numeric_type, max_iterations>;

    mandelbrot_generator(const mandelbrot_config_type& config)
      : mandelbrot_config_object   (config),
        mandelbrot_image           (config.integral_width(), config.integral_height()),
        mandelbrot_view            (boost::gil::rgb8_view_t()),
        mandelbrot_iteration_matrix(config.integral_width(),
                                    std::vector<std::uint_fast32_t>(config.integral_height())),
        mandelbrot_color_histogram (max_iterations + 1U, UINT32_C(0))
    {
      mandelbrot_view = boost::gil::view(mandelbrot_image);
    }

    ~mandelbrot_generator() = default;

    static const numeric_type& four()
    {
      static const numeric_type my_value_four(4U);

      return my_value_four;
    }

    void generate_mandelbrot_image(const std::string&                  str_filename,
                                   const color::color_functions_base& color_functions = color::color_functions_bw(),
                                         color::color_stretch_base&   color_stretches = color::color_stretch_histogram_method(),
                                         std::ostream&                 output_stream   = std::cout)
    {
      // Setup the x-axis and y-axis coordinates.

      std::vector<numeric_type> x_values(mandelbrot_config_object.integral_width());
      std::vector<numeric_type> y_values(mandelbrot_config_object.integral_height());

      {
        numeric_type x_coord(mandelbrot_config_object.x_lo());
        numeric_type y_coord(mandelbrot_config_object.y_hi());

        for(auto& x : x_values) { x = x_coord; x_coord += mandelbrot_config_object.step(); }
        for(auto& y : y_values) { y = y_coord; y_coord -= mandelbrot_config_object.step(); }
      }

      std::atomic_flag mandelbrot_iteration_lock = ATOMIC_FLAG_INIT;

      auto unordered_parallel_row_count = static_cast<std::size_t>(0U);

      my_concurrency::parallel_for
      (
        std::size_t(0U),
        y_values.size(),
        [&mandelbrot_iteration_lock, &unordered_parallel_row_count, &output_stream, &x_values, &y_values, this](std::size_t j_row)
        {
          while(mandelbrot_iteration_lock.test_and_set())
          {
            ;
          }

          {
            ++unordered_parallel_row_count;

            const auto percent =
              static_cast<float>
              (
                  static_cast<double>(100.0 * static_cast<double>(unordered_parallel_row_count))
                / static_cast<double>(y_values.size())
              );

            output_stream << "Calculating Mandelbrot image at row "
                          << unordered_parallel_row_count
                          << " of "
                          << y_values.size()
                          << ". Total processed so far: "
                          << std::fixed
                          << std::setprecision(1)
                          << percent
                          << "%. Have patience."
                          << "\r";
          }

          mandelbrot_iteration_lock.clear();

          for(auto i_col = static_cast<std::size_t>(0U); i_col < x_values.size(); ++i_col)
          {
            numeric_type zr (0U);
            numeric_type zi (0U);
            numeric_type zr2(0U);
            numeric_type zi2(0U);

            // Use an optimized complex-numbered multiplication scheme.
            // Thereby reduce the main work of the Mandelbrot iteration to
            // three real-valued multiplications and several real-valued
            // addition/subtraction operations.

            auto iteration_result = static_cast<std::uint_fast32_t>(UINT32_C(0));

            // Perform the iteration sequence for generating the Mandelbrot set.
            // Here is the main work of the program.

            while((iteration_result < max_iterations) && ((zr2 + zi2) < four()))
            {
              // Optimized complex multiply and add.
              zi *= zr;

              zi  = (zi  + zi)  + y_values[j_row];
              zr  = (zr2 - zi2) + x_values[i_col];

              zr2 = zr; zr2 *= zr;
              zi2 = zi; zi2 *= zi;

              ++iteration_result;
            }

            while(mandelbrot_iteration_lock.test_and_set())
            {
              ;
            }

            {
              mandelbrot_iteration_matrix[i_col][j_row] = iteration_result;
              ++mandelbrot_color_histogram[iteration_result];
            }

            mandelbrot_iteration_lock.clear();
          }
        }
      );

      output_stream << std::endl;

      output_stream << "Perform color stretching." << std::endl;
      apply_color_stretches(x_values, y_values, color_stretches);

      output_stream << "Apply color functions." << std::endl;
      apply_color_functions(x_values, y_values, color_functions);

      output_stream << "Write output JPEG file " << str_filename << "." << std::endl;
      boost::gil::jpeg_write_view(str_filename, mandelbrot_view);
    }

  private:
    const mandelbrot_config_type&                      mandelbrot_config_object;

          boost::gil::rgb8_image_t                     mandelbrot_image;
          boost::gil::rgb8_view_t                      mandelbrot_view;

          std::vector<std::vector<std::uint_fast32_t>> mandelbrot_iteration_matrix;
          std::vector<std::uint_fast32_t>              mandelbrot_color_histogram;

    void apply_color_stretches(const std::vector<numeric_type>& x_values,
                               const std::vector<numeric_type>& y_values,
                               color::color_stretch_base& color_stretches)
    {
      color_stretches.init(static_cast<std::uint_fast32_t>(x_values.size() * y_values.size()));

      for(auto& histogram_entry : mandelbrot_color_histogram)
      {
        color_stretches.color_stretch(histogram_entry);
      }
    }

    void apply_color_functions(const std::vector<numeric_type>& x_values,
                               const std::vector<numeric_type>& y_values,
                               const color::color_functions_base& color_functions)
    {
      for(auto j_row = static_cast<std::uint_fast32_t>(UINT32_C(0)); j_row < y_values.size(); ++j_row)
      {
        for(auto i_col = static_cast<std::uint_fast32_t>(UINT32_C(0)); i_col < x_values.size(); ++i_col)
        {
          const auto hist_color = mandelbrot_color_histogram[mandelbrot_iteration_matrix[i_col][j_row]];

          // Get the three hue values.
          const auto color_r = static_cast<std::uint_fast32_t>((hist_color <= 4U) ? hist_color : color_functions.color_function_r(hist_color));
          const auto color_g = static_cast<std::uint_fast32_t>((hist_color <= 4U) ? hist_color : color_functions.color_function_g(hist_color));
          const auto color_b = static_cast<std::uint_fast32_t>((hist_color <= 4U) ? hist_color : color_functions.color_function_b(hist_color));

          // Mix the color from the hue values.
          const auto rh = static_cast<std::uint8_t>((255U * color_r) / UINT32_C(255));
          const auto gh = static_cast<std::uint8_t>((255U * color_g) / UINT32_C(255));
          const auto bh = static_cast<std::uint8_t>((255U * color_b) / UINT32_C(255));

          const boost::gil::rgb8_pixel_t the_color  = boost::gil::rgb8_pixel_t(rh, gh, bh);

          mandelbrot_view(i_col, j_row) = boost::gil::rgb8_pixel_t(the_color);
        }
      }
    }
  };

  #if(__cplusplus >= 201703L)
  } // namespace ckormanyos::mandelbrot
  #else
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_2015_06_15_H