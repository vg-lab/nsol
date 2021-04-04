if ( NSOL_WITH_EXAMPLES )

  if( BRION_FOUND )
    set( NSOLBRIONMORPHOLOGYREADER_SOURCES brionMorphologyReader.cpp )
    set( NSOLBRIONMORPHOLOGYREADER_LINK_LIBRARIES nsol )
    common_application( nsolBrionMorphologyReader NOHELP )
    list( APPEND NSOL_EXAMPLES_FILES ${NSOLBRIONMORPHOLOGYREADER_SOURCES} )

    set( NSOLBRIONCIRCUITLOADER_SOURCES brionCircuitLoader.cpp )
    set( NSOLBRIONCIRCUITLOADER_LINK_LIBRARIES nsol )
    common_application( nsolBrionCircuitLoader NOHELP )
    list( APPEND NSOL_EXAMPLES_FILES ${NSOLBRIONCIRCUITLOADER_SOURCES} )

    set( NSOLCONNECTIVITYMATRIX_SOURCES nsolConnectivityMatrix.cpp )
    set( NSOLCONNECTIVITYMATRIX_LINK_LIBRARIES nsol )
    common_application( nsolConnectivityMatrix NOHELP )
    list( APPEND NSOL_EXAMPLES_FILES ${NSOLCONNECTIVITYMATRIX_SOURCES} )

    set( NSOLBLUECONFIGCONNECTIVITYTOTXT_SOURCES BlueConfigConnectivityToTxt.cpp )
    set( NSOLBLUECONFIGCONNECTIVITYTOTXT_LINK_LIBRARIES nsol )
    common_application( nsolBlueConfigConnectivityToTxt NOHELP )
    list( APPEND NSOL_EXAMPLES_FILES ${NSOLBLUECONFIGCONNECTIVITYTOTXT_SOURCES} )

    set( NSOLCIRCUITLOADERSUMMARY_SOURCES nsolCircuitLoaderSummary.cpp )
    set( NSOLCIRCUITLOADERSUMMARY_LINK_LIBRARIES nsol )
    common_application( nsolCircuitLoaderSummary NOHELP )
    list( APPEND NSOL_EXAMPLES_FILES ${NSOLCIRCUITLOADERSUMMARY_SOURCES} )
  endif( )


  set( NSOLSWCREADER_SOURCES SwcReader.cpp )
  set( NSOLSWCREADER_LINK_LIBRARIES nsol )
  common_application( nsolSwcReader NOHELP )
  list( APPEND NSOL_EXAMPLES_FILES ${NSOLSWCREADER_SOURCES} )

  set( NSOLASCTOSWCTEST_SOURCES AscToSwcTest.cpp )
  set( NSOLASCTOSWCTEST_LINK_LIBRARIES nsol )
  common_application( nsolAscToSwcTest NOHELP )
  list( APPEND NSOL_EXAMPLES_FILES ${NSOLASCTOSWCTEST_SOURCES} )

  if( HDF5_FOUND )
    set( NSOLVASCULATUREMORPHOLOGYREADER_SOURCES vasculatureMorphologyReader.cpp )
    set( NSOLVASCULATUREMORPHOLOGYREADER_LINK_LIBRARIES nsol )
    common_application( nsolVasculatureMorphologyReader NOHELP )
    list( APPEND NSOL_EXAMPLES_FILES ${NSOLVASCULATUREMORPHOLOGYREADER_SOURCES} )
  endif( )


  set( NSOLEXTRACTNEURONSTATS_SOURCES extractNeuronStats.cpp )
  set( NSOLEXTRACTNEURONSTATS_LINK_LIBRARIES nsol )
  common_application( nsolExtractNeuronStats NOHELP )
  list( APPEND NSOL_EXAMPLES_FILES ${NSOLEXTRACTNEURONSTATS_SOURCES} )

  set( NSOLSECTIONSTATS_SOURCES sectionStats.cpp )
  set( NSOLSECTIONSTATS_LINK_LIBRARIES nsol )
  common_application( nsolSectionStats NOHELP )
  list( APPEND NSOL_EXAMPLES_FILES ${NSOLSECTIONSTATS_SOURCES} )

  set( NSOLRADIUSSTAT_SOURCES radiusStat.cpp )
  set( NSOLRADIUSSTAT_LINK_LIBRARIES nsol )
  common_application( nsolRadiusStat NOHELP )
  list( APPEND NSOL_EXAMPLES_FILES ${NSOLRADIUSSTAT_SOURCES} )

  set( NSOLNEURITESTATS_SOURCES neuriteStats.cpp )
  set( NSOLNEURITESTATS_LINK_LIBRARIES nsol )
  common_application( nsolNeuriteStats NOHELP )
  list( APPEND NSOL_EXAMPLES_FILES ${NSOLNEURITESTATS_SOURCES} )

  set( NSOLNEURONSTATS_SOURCES neuronStats.cpp )
  set( NSOLNEURONSTATS_LINK_LIBRARIES nsol )
  common_application( nsolNeuronStats NOHELP )
  list( APPEND NSOL_EXAMPLES_FILES ${NSOLNEURONSTATS_SOURCES} )

  set( NSOLMINICOLUMNSTATS_SOURCES miniColumnStats.cpp )
  set( NSOLMINICOLUMNSTATS_LINK_LIBRARIES nsol )
  common_application( nsolMiniColumnStats NOHELP )
  list( APPEND NSOL_EXAMPLES_FILES ${NSOLMINICOLUMNSTATS_SOURCES} )

  set( NSOLCOLUMNSTATS_SOURCES columnStats.cpp )
  set( NSOLCOLUMNSTATS_LINK_LIBRARIES nsol )
  common_application( nsolColumnStats NOHELP )

  set( NSOLDATASET_SOURCES dataset.cpp )
  set( NSOLDATASET_LINK_LIBRARIES nsol )
  common_application( nsolDataset NOHELP )
  list( APPEND NSOL_EXAMPLES_FILES ${NSOLDATASET_SOURCES} )

  set( NSOLSIMPLIFIER_SOURCES simplifier.cpp )
  set( NSOLSIMPLIFIER_LINK_LIBRARIES nsol )
  common_application( nsolSimplifier NOHELP )
  list( APPEND NSOL_EXAMPLES_FILES ${NSOLSIMPLIFIER_SOURCES} )


  set( NSOLBLUECONFIG2XMLSCENE_SOURCES blueConfig2XmlScene.cpp )
  set( NSOLBLUECONFIG2XMLSCENE_LINK_LIBRARIES nsol )
  common_application( nsolBlueConfig2XmlScene NOHELP )
  list( APPEND NSOL_EXAMPLES_FILES ${NSOLBLUECONFIG2XMLSCENE_SOURCES} )

  if ( QT5CORE_FOUND )
    set( NSOLSCENE_SOURCES scene.cpp )
    set( NSOLSCENE_LINK_LIBRARIES nsol )
    common_application( nsolScene NOHELP )
    list( APPEND NSOL_EXAMPLES_FILES ${NSOLSCENE_SOURCES} )
  endif( )

  include(InstallFiles)
  install_files(share/nsol/examples FILES ${NSOL_EXAMPLES_FILES} COMPONENT
    examples )

endif( NSOL_WITH_EXAMPLES )
