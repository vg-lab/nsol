

source_group(\\ FILES CMakeLists.txt)

set(NSOL_PUBLIC_HEADERS ${COMMON_INCLUDES}
Node.h
Column.h
Soma.h
Writer/SwcWriter.h
Neurite.h
Container/Sections.h
Container/Dendrites.h
Container/Columns.h
Container/MiniColumns.h
Container/Neurites.h
Container/Segments.h
Container/Neurons.h
Container/Nodes.h
Section.h
NeuronMorphology.h
Segment.h
Reader/SwcReader.h
Reader/BBPSDKReader.h
NsolTypes.h
MiniColumn.h
Neuron.h
Axon.h
Spine.h
Dendrite.h
Synapse.h
)

set(NSOL_HEADERS )

set(NSOL_SOURCES ${COMMON_SOURCES}
NeuronMorphology.cpp
MiniColumn.cpp
Neuron.cpp
Node.cpp
Dendrite.cpp
Axon.cpp
Soma.cpp
Neurite.cpp
Column.cpp
Segment.cpp
Section.cpp
)

if (BBPSDK_FOUND)
  set(NSOL_LINK_LIBRARIES ${BBPSDK_LIBRARIES})
endif()

common_library(nsol)
set(NSOL_LINK_LIBRARIES "${NSOL_LINK_LIBRARIES}" PARENT_SCOPE)