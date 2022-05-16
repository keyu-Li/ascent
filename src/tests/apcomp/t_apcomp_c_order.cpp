//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Copyright (c) Lawrence Livermore National Security, LLC and other Ascent
// Project developers. See top-level LICENSE AND COPYRIGHT files for dates and
// other details. No copyright assignment is required to contribute to Ascent.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//-----------------------------------------------------------------------------
///
/// file: t_apcomp_zbuffer.cpp
///
//-----------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "t_config.hpp"
#include "t_utils.hpp"
#include "t_apcomp_test_utils.h"

#include <apcomp/apcomp.hpp>
#include <apcomp/compositor.hpp>

#include <iostream>

using namespace std;


//-----------------------------------------------------------------------------
TEST(apcomp_c_order, apcomp_c_order)
{
  std::string output_dir = prepare_output_dir();
  std::string file_name = "apcomp_c_order";
  std::string output_file = apcomp::join_file_path(output_dir,file_name);
  remove_test_file(output_file);

  apcomp::Compositor compositor;
  auto mode = apcomp::Compositor::CompositeMode::VIS_ORDER_BLEND;
  compositor.SetCompositeMode(mode);

  const int width  = 1024;
  const int height = 1024;
  const int square_size = 300;
  const int num_images  = 4;
  const int y = 500;
  float colors[4][4] = { {1.f, 0.f, 0.f, 0.5f},
                         {0.f, 1.f, 0.f, 0.5f},
                         {0.f, 0.f, 1.f, 0.5f},
                         {0.f, 1.f, 1.f, 0.5f} } ;

  for(int i = 0; i < num_images; ++i)
  {

    std::vector<float> pixels;
    std::vector<float> depths;
    gen_float32_image(pixels,
                      depths,
                      width,
                      height,
                      float(i) * 0.05f,
                      200 + 100*i,
                      y - 50 * i,
                      square_size,
                      colors[i]);

    compositor.AddImage(&pixels[0], &depths[0], width, height, i);
  }
  apcomp::Image image = compositor.Composite();
  image.Save(output_file);

  EXPECT_TRUE(check_test_image(output_file, t_apcomp_baseline_dir()));
}

