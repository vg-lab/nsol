source_group(\\ FILES CMakeLists.txt)

set(NSOL_PUBLIC_HEADERS ${COMMON_INCLUDES}
Axon.h
Column.h
Container/Columns.h
Container/Dendrites.h
Container/MiniColumns.h
Container/Neurites.h
Container/Neurons.h
Container/Nodes.h
Container/Sections.h
Container/Segments.h
Dendrite.h
error.h
MiniColumn.h
Neurite.h
Neuron.h
NeuronMorphology.h
Node.h
NsolTypes.h
Reader/BBPSDKReader.h
Reader/SwcReader.h
Section.h
Segment.h
Soma.h
Spine.h
Stats/AxonStats.h
Stats/AxonCachedStats.h
Stats/DendriteStats.h
Stats/DendriteCachedStats.h
Stats/Cached.h
Stats/NeuronMorphologyStats.h
Stats/NeuronMorphologyCachedStats.h
Stats/NeuriteStats.h
Stats/NeuriteCachedStats.h
Stats/NeuriteCachedStats.cpp
Stats/NodeCached.h
Stats/SectionStats.h
Stats/SectionCachedStats.h
Stats/SegmentStats.h
Stats/SegmentCachedStats.h
Synapse.h
Writer/SwcWriter.h
)

set(NSOL_HEADERS )

set(NSOL_SOURCES ${COMMON_SOURCES}
Axon.cpp
Column.cpp
Dendrite.cpp
MiniColumn.cpp
Neurite.cpp
Neuron.cpp
NeuronMorphology.cpp
Node.cpp
Section.cpp
Segment.cpp
Soma.cpp
#Stats/DendriteStats.cpp
Stats/NeuronMorphologyStats.cpp
Stats/NeuronMorphologyCachedStats.cpp
Stats/NeuriteStats.cpp
Stats/NeuriteCachedStats.cpp
Stats/NodeCached.cpp
Stats/SectionStats.cpp
Stats/SectionCachedStats.cpp
Stats/SegmentStats.cpp
Stats/SegmentCachedStats.cpp
)

if (BBPSDK_FOUND)
  set(NSOL_LINK_LIBRARIES ${BBPSDK_LIBRARIES})
endif()

common_library(nsol)
set(NSOL_LINK_LIBRARIES "${NSOL_LINK_LIBRARIES}" PARENT_SCOPE)
