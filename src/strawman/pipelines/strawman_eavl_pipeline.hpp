//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Copyright (c) 2015-2017, Lawrence Livermore National Security, LLC.
// 
// Produced at the Lawrence Livermore National Laboratory
// 
// LLNL-CODE-716457
// 
// All rights reserved.
// 
// This file is part of Strawman. 
// 
// For details, see: http://software.llnl.gov/strawman/.
// 
// Please also read strawman/LICENSE
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
// * Redistributions of source code must retain the above copyright notice, 
//   this list of conditions and the disclaimer below.
// 
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the disclaimer (as noted below) in the
//   documentation and/or other materials provided with the distribution.
// 
// * Neither the name of the LLNS/LLNL nor the names of its contributors may
//   be used to endorse or promote products derived from this software without
//   specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL LAWRENCE LIVERMORE NATIONAL SECURITY,
// LLC, THE U.S. DEPARTMENT OF ENERGY OR CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
// DAMAGES  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
// IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.
// 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


//-----------------------------------------------------------------------------
///
/// file: strawman_eavl_pipeline.hpp
///
//-----------------------------------------------------------------------------

#ifndef STRAWMAN_EAVL_PIPELINE_HPP
#define STRAWMAN_EAVL_PIPELINE_HPP

#include <strawman.hpp>
#include <strawman_pipeline.hpp>


//-----------------------------------------------------------------------------
// -- begin strawman:: --
//-----------------------------------------------------------------------------
namespace strawman
{

class EAVLPipeline : public Pipeline
{
public:
    
    // Creation and Destruction
    EAVLPipeline();
    virtual ~EAVLPipeline();

    // Main pipeline interface methods, which are used by the strawman 
    // interface.

    void  Initialize(const conduit::Node &options);

    void  Publish(const conduit::Node &data);
    void  Execute(const conduit::Node &actions);
    
    void  Cleanup();

private:
    //forward declarations
    class DataAdapter;
    class Renderer;
    class Plot;
    
    
    // actions
    void            AddPlot(const conduit::Node &options);
    void            DrawPlots();
    void            RenderPlot(const int plot_id, conduit::Node &options);


    //filters and mutators
    void            AddFilter(const conduit::Node &options);
    void            BoxFilter(const conduit::Node &options);
    void            IsosurfaceFilter(const conduit::Node &options);
    // TODO: this should be called Recenter
    void            CellToNodeFilter(const conduit::Node &options);
    void            ThresholdFilter(const conduit::Node &options);
    void            ExternalFacesFilter();

    // conduit node that (externally) holds the data from the simulation 
    conduit::Node     m_data; 

    // holds the pipeline's plots
    std::vector<Plot> m_plots;

    // rendering
    Renderer          *m_renderer;

};

//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
// -- end strawman:: --
//-----------------------------------------------------------------------------

#endif
//-----------------------------------------------------------------------------
// -- end header ifdef guard
//-----------------------------------------------------------------------------


