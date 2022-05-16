//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Copyright (c) Lawrence Livermore National Security, LLC and other Ascent
// Project developers. See top-level LICENSE AND COPYRIGHT files for dates and
// other details. No copyright assignment is required to contribute to Ascent.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//-----------------------------------------------------------------------------
///
/// file: ascent_png_decoder.cpp
///
//-----------------------------------------------------------------------------

#include "png_decoder.hpp"
#include <apcomp/error.hpp>
#include <apcomp/utils/lodepng.h>

// standard includes
#include <stdlib.h>


namespace apcomp
{

//-----------------------------------------------------------------------------
PNGDecoder::PNGDecoder()
{}

//-----------------------------------------------------------------------------
PNGDecoder::~PNGDecoder()
{
}


void
PNGDecoder::Decode(unsigned char *&rgba,
                   int &width,
                   int &height,
                   const std::string &file_name)
{
  unsigned w,h;
  unsigned int res = apcomp::lodepng_decode32_file(&rgba, &w, &h, file_name.c_str());
  if(res)
  {
    throw Error("PNGDecoder: failed to decode '" + file_name + "'");
  }

  width = w;
  height = h;
}

} // namespace apcomp
