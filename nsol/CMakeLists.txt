source_group(\\ FILES CMakeLists.txt)

set(NSOL_PUBLIC_HEADERS
  Axon.h
  Column.h
  Container/Circuits.h
  Container/Columns.h
  Container/Dendrites.h
  Container/MiniColumns.h
  Container/Neurites.h
  Container/Neurons.h
  Container/Nodes.h
  Container/Sections.h
  Container/Synapses.h
  DataSet.h
  Dendrite.h
  error.h
  ImportanceNode.h
  Log.h
  MiniColumn.h
  Neurite.h
  Neuron.h
  NeuronMorphology.h
  NeuronMorphologySection.h
  Node.h
  NsolTypes.h
  Object.h
  ObjectWithProperties.h
  Section.h
  Simplifier.h
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
  Stats/NeuronMorphologySectionStats.h
  Stats/NeuronMorphologySectionCachedStats.h
  Stats/NeuriteStats.h
  Stats/NeuriteCachedStats.h
  Stats/NeuriteCachedStats.cpp
  Stats/NodeCached.h
  Stats/SegmentStats.h
  Stats/SomaStats.h
  Synapse.h
  MorphologySynapse.h
  Circuit.h
  # templated classes at last
  Writer/SwcWriter.h
  Writer/XmlSceneWriter.h
  Reader/BrionReader.h
  Reader/SwcReader.h
  Reader/AscReader.h
  Reader/XmlSceneReader.h
  )

set(NSOL_HEADERS )

set(NSOL_SOURCES
  Axon.cpp
  Column.cpp
  Container/Neurons.cpp
  Container/Synapses.cpp
  DataSet.cpp
  Dendrite.cpp
  ImportanceNode.cpp
  Log.cpp
  MiniColumn.cpp
  Neurite.cpp
  Neuron.cpp
  NeuronMorphology.cpp
  NeuronMorphologySection.cpp
  Node.cpp
  Object.cpp
  ObjectWithProperties.cpp
  Section.cpp
  Simplifier.cpp
  Soma.cpp
  Stats/AxonStats.cpp
  Stats/AxonCachedStats.cpp
  Stats/ColumnStats.cpp
  Stats/DendriteStats.cpp
  Stats/DendriteCachedStats.cpp
  Stats/MiniColumnStats.cpp
  Stats/NeuronMorphologyStats.cpp
  Stats/NeuronMorphologyCachedStats.cpp
  Stats/NeuronMorphologySectionStats.cpp
  Stats/NeuronMorphologySectionCachedStats.cpp
  Stats/NeuriteStats.cpp
  Stats/NeuriteCachedStats.cpp
  Stats/NodeCached.cpp
  Stats/SegmentStats.cpp
  Stats/SomaStats.cpp
  Synapse.cpp
  MorphologySynapse.cpp
  Circuit.cpp
  Writer/XmlSceneWriter.cpp
  )


if (BRION_FOUND)
  set(NSOL_LINK_LIBRARIES ${NSOL_LINK_LIBRARIES} PUBLIC Brain )
  set(NSOL_LINK_LIBRARIES ${NSOL_LINK_LIBRARIES} PUBLIC Brion )
endif()


if (QT5CORE_FOUND)
  set(NSOL_LINK_LIBRARIES ${NSOL_LINK_LIBRARIES} PUBLIC Qt5::Core)
endif()

if (FIRES_FOUND)
  set(NSOL_LINK_LIBRARIES ${NSOL_LINK_LIBRARIES} PUBLIC FiReS)
endif()

common_library(nsol)
