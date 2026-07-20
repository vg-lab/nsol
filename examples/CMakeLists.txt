if(NSOL_WITH_EXAMPLES)

  # Function to create and install an example application
  function(add_project_example)
    set(options)
    set(oneValueArgs TARGET_NAME)
    set(multiValueArgs SOURCES LINK_LIBRARIES)
    cmake_parse_arguments(PARSE_ARGV 0 ARG "${options}" "${oneValueArgs}" "${multiValueArgs}")

    if(NOT ARG_TARGET_NAME OR NOT ARG_SOURCES)
      message(FATAL_ERROR "TARGET_NAME and SOURCES are required arguments")
    endif()

    add_executable(${ARG_TARGET_NAME} ${ARG_SOURCES})
    target_link_libraries(${ARG_TARGET_NAME} PRIVATE ${PROJECT_NAME} ${ARG_LINK_LIBRARIES})

    # Get current parent scope value and create a local copy
    set(PROJECT_EXAMPLES_FILES_VAR "${${PROJECT_NAME}_EXAMPLES_FILES}")
    set(current_examples ${PROJECT_EXAMPLES_FILES_VAR})
    
    # Convert to CMake list and append new sources
    list(APPEND current_examples ${ARG_SOURCES})
    
    # Remove duplicates and update parent scope
    list(REMOVE_DUPLICATES current_examples)
    set(${PROJECT_NAME}_EXAMPLES_FILES "${current_examples}" PARENT_SCOPE)

    # Create all examples target
    if(NOT TARGET ${PROJECT_NAME}_all_examples)
      add_custom_target(${PROJECT_NAME}_all_examples)
    endif()

    # Add example to global examples target
    add_dependencies(${PROJECT_NAME}_all_examples ${ARG_TARGET_NAME})
  endfunction()

  # Add examples
  add_project_example(
    TARGET_NAME nsolExampleSwcReader
    SOURCES
      SwcReader.cpp
  )

  add_project_example(
    TARGET_NAME nsolExampleAscToSwcTest
    SOURCES
      AscToSwcTest.cpp
  )

  add_project_example(
    TARGET_NAME nsolExampleExtractNeuronStats
    SOURCES
      extractNeuronStats.cpp
  )

  add_project_example(
    TARGET_NAME nsolExampleSectionStats
    SOURCES
      sectionStats.cpp
  )

  add_project_example(
    TARGET_NAME nsolExampleRadiusStat
    SOURCES
      radiusStat.cpp
  )

  add_project_example(
    TARGET_NAME nsolExampleNeuriteStats
    SOURCES
      neuriteStats.cpp
  )

  add_project_example(
    TARGET_NAME nsolExampleNeuronStats
    SOURCES
      neuronStats.cpp
  )

  add_project_example(
    TARGET_NAME nsolExampleMiniColumnStats
    SOURCES
      miniColumnStats.cpp
  )

  add_project_example(
    TARGET_NAME nsolExampleColumnStats
    SOURCES
      columnStats.cpp
  )

  add_project_example(
    TARGET_NAME nsolExampleDataset
    SOURCES
      dataset.cpp
  )

  add_project_example(
    TARGET_NAME nsolExampleSimplifier
    SOURCES
      simplifier.cpp
  )

  add_project_example(
    TARGET_NAME nsolExampleBlueConfig2XmlScene
    SOURCES
      blueConfig2XmlScene.cpp
  )

  if(NSOL_USE_HDF5)
    add_project_example(
      TARGET_NAME nsolExampleVasculatureMorphologyReader
      SOURCES
        vasculatureMorphologyReader.cpp
    )
  endif()

  if(NSOL_USE_QT5CORE)
    add_project_example(
      TARGET_NAME nsolExampleScene
      SOURCES
        scene.cpp
    )
  endif()

  if(NSOL_USE_BRION)
    add_project_example(
      TARGET_NAME nsolExampleBrionMorphologyReader
      SOURCES
        brionMorphologyReader.cpp
    )

    add_project_example(
      TARGET_NAME nsolExampleBrionCircuitLoader
      SOURCES
        brionCircuitLoader.cpp
    )

    add_project_example(
      TARGET_NAME nsolExampleConnectivityMatrix
      SOURCES
        nsolConnectivityMatrix.cpp
    )

    add_project_example(
      TARGET_NAME nsolExampleBlueConfigConnectivityToTxt
      SOURCES
        BlueConfigConnectivityToTxt.cpp
    )

    add_project_example(
      TARGET_NAME nsolExampleCircuitLoaderSummary
      SOURCES
        nsolCircuitLoaderSummary.cpp
    )
  endif()

  # Define installation directory variables
  include(GNUInstallDirs)

  # Install examples source files
  install(FILES ${${PROJECT_NAME}_EXAMPLES_FILES}
    DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME_LOWER}/examples
    COMPONENT ${PROJECT_NAME}_examples
  )

endif()
