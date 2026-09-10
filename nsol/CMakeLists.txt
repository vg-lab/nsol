# Define public headers
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
  Morphology.h
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
  Stats/NodeCached.h
  Stats/SegmentStats.h
  Stats/SomaStats.h
  Synapse.h
  MorphologySynapse.h
  Circuit.h
  Writer/SwcWriter.h
  Writer/XmlSceneWriter.h
  Reader/BrionReader.h
  Reader/SwcReader.h
  Reader/AscReader.h
  Reader/VectorsReader.h
  Reader/XmlSceneReader.h
)

if(HDF5_FOUND AND NSOL_USE_HDF5)
  list(APPEND NSOL_PUBLIC_HEADERS Reader/VasculatureReader.h)
endif()

# Create the includes strings for the unified header
set(HEADER_INCLUDES "")
foreach(header ${NSOL_PUBLIC_HEADERS})
  string(APPEND HEADER_INCLUDES "#include <${PROJECT_NAME_LOWER}/${header}>\n")
endforeach()

# Generate the unified header
configure_file(
  "${PROJECT_SOURCE_DIR}/cmake/unified_header.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME_LOWER}.h"
)

# Get the current Git commit for the version header
find_package(Git)
if(Git_FOUND)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} --no-pager log -n 1 HEAD "--pretty=format:%h"
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    RESULT_VARIABLE git_result
    ERROR_QUIET
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  if(git_result EQUAL 0)
    message(STATUS "Last ${PROJECT_NAME} Git commit: ${GIT_COMMIT_HASH}")
  endif()
endif()

# Generate the version header
configure_file(
  "${PROJECT_SOURCE_DIR}/cmake/version.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/version.h"
)

# Define source files
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
  Stats/NeuriteCachedStats.cpp
)

# Create the target
add_library(${PROJECT_NAME})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
)

# Generate export header
include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME})

# Add sources to the target
target_sources(${PROJECT_NAME}
  PRIVATE
    ${NSOL_SOURCES}
  PUBLIC
    FILE_SET public_headers
    TYPE HEADERS
    BASE_DIRS
      ${PROJECT_SOURCE_DIR}
    FILES
      ${NSOL_PUBLIC_HEADERS}
)

# Add generated sources to the target
target_sources(${PROJECT_NAME}
  PUBLIC
    FILE_SET public_headers_generated
    TYPE HEADERS
    BASE_DIRS
      ${PROJECT_BINARY_DIR}
    FILES
      # Generated headers
      ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME_LOWER}.h
      ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME_LOWER}_export.h
      ${CMAKE_CURRENT_BINARY_DIR}/version.h
)

# Add compile definitions
target_compile_definitions(${PROJECT_NAME}
  PUBLIC
    $<$<BOOL:${NSOL_USE_HDF5}>:NSOL_USE_HDF5>
    $<$<BOOL:${NSOL_USE_QT5CORE}>:NSOL_USE_QT5CORE>
    $<$<BOOL:${NSOL_USE_BRION}>:NSOL_USE_BRION>
    $<$<BOOL:${NSOL_USE_FIRES}>:NSOL_USE_FIRES>
  PRIVATE
    $<$<STREQUAL:${CMAKE_BUILD_TYPE},Debug>:DEBUG>
    $<$<BOOL:${NSOL_WITH_LOGGING}>:NSOL_WITH_LOGGING>
    $<$<BOOL:${NSOL_USE_OPENMP}>:NSOL_USE_OPENMP>
    $<$<BOOL:${NSOL_USE_SHARED_PTR}>:NSOL_USE_SHARED_PTR>
)

# Link libraries
target_link_libraries(${PROJECT_NAME}
  PUBLIC
    Eigen3::Eigen
    "$<$<BOOL:${NSOL_USE_HDF5}>:HDF5::HDF5>"
    "$<$<BOOL:${NSOL_USE_BRION}>:Brain>"
    "$<$<BOOL:${NSOL_USE_BRION}>:Brion>"
    "$<$<BOOL:${NSOL_USE_QT5CORE}>:Qt5::Core>"
    "$<$<BOOL:${NSOL_USE_FIRES}>:FiReS::FiReS>"
  PRIVATE
    "$<$<BOOL:${NSOL_USE_OPENMP}>:OpenMP::OpenMP_CXX>"
)
