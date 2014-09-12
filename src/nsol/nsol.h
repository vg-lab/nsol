/**
 * @file    nsol.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NSOL_NSOL__
#define __NSOL_NSOL__


// Ontology elements
#include <nsol/Axon.h>
#include <nsol/Dendrite.h>
#include <nsol/Neurite.h>
#include <nsol/Neuron.h>
#include <nsol/Node.h>
#include <nsol/Section.h>
#include <nsol/Segment.h>
#include <nsol/Synapse.h>
#include <nsol/Soma.h>
#include <nsol/Spine.h>
#include <nsol/NsolTypes.h>

// Containers
#include <nsol/Container/Sections.h>
#include <nsol/Container/Segments.h>
#include <nsol/Container/Neurites.h> 
#include <nsol/Container/Dendrites.h> 
#include <nsol/Container/Columns.h>
#include <nsol/Container/MiniColumns.h>

// Reader
#include <nsol/Reader/SwcReader.h>
#include <nsol/Reader/BBPSDKReader.h>
// Writer
#include <nsol/Writer/SwcWriter.h>


#endif
