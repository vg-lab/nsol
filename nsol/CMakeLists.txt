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
  DataSet.h
  Dendrite.h
  error.h
  MiniColumn.h
  Neurite.h
  Neuron.h
  NeuronMorphology.h
  Node.h
  NsolTypes.h
  Section.h
  Segment.h
  Soma.h
  Spine.h
  Stats/AxonStats.h
  Stats/AxonCachedStats.h
  Stats/DendriteStats.h
  Stats/DendriteCachedStats.h
  Stats/Cached.h
  Stats/ColumnStats.h
  Stats/MiniColumnStats.h
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
  Stats/SomaStats.h
  Synapse.h
  # templated classes at last
  Writer/SwcWriter.h
  Factory.h
  Reader/BBPSDKReader.h
  Reader/SwcReader.h
  )

set(NSOL_HEADERS )

set(NSOL_SOURCES ${COMMON_SOURCES}
  Axon.cpp
  Column.cpp
  DataSet.cpp
  Dendrite.cpp
  MiniColumn.cpp
  Neurite.cpp
  Neuron.cpp
  NeuronMorphology.cpp
  Node.cpp
  Section.cpp
  Segment.cpp
  Soma.cpp
  Stats/AxonStats.cpp
  Stats/AxonCachedStats.cpp
  Stats/ColumnStats.cpp
  Stats/DendriteStats.cpp
  Stats/DendriteCachedStats.cpp
  Stats/MiniColumnStats.cpp
  Stats/NeuronMorphologyStats.cpp
  Stats/NeuronMorphologyCachedStats.cpp
  Stats/NeuriteStats.cpp
  Stats/NeuriteCachedStats.cpp
  Stats/NodeCached.cpp
  Stats/SectionStats.cpp
  Stats/SectionCachedStats.cpp
  Stats/SegmentStats.cpp
  Stats/SegmentCachedStats.cpp
  Stats/SomaStats.cpp
  )

if (BBPSDK_FOUND)
  set(NSOL_LINK_LIBRARIES ${NSOL_LINK_LIBRARIES} ${BBPSDK_LIBRARIES})
endif()

if (QT5CORE_FOUND)
  set(NSOL_LINK_LIBRARIES ${NSOL_LINK_LIBRARIES} ${Qt5Core_LIBRARIES})
endif()

common_library(nsol)
set(NSOL_LINK_LIBRARIES "${NSOL_LINK_LIBRARIES}" PARENT_SCOPE)
