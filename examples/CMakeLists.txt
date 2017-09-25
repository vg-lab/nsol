if ( NSOL_WITH_EXAMPLES )

  add_executable(nsolSwcReader SwcReader.cpp)
  target_link_libraries(nsolSwcReader nsol)

  if( BRION_FOUND )
    set( NSOLBRIONMORPHOLOGYREADER_SOURCES brionMorphologyReader.cpp )
    set( NSOLBRIONMORPHOLOGYREADER_LINK_LIBRARIES nsol )
    common_application( nsolBrionMorphologyReader )

    set( NSOLBRIONCIRCUITLOADER_SOURCES brionCircuitLoader.cpp )
    set( NSOLBRIONCIRCUITLOADER_LINK_LIBRARIES nsol )
    common_application( nsolBrionCircuitLoader )

    set( NSOLCONNECTIVITYMATRIX_SOURCES nsolConnectivityMatrix.cpp )
    set( NSOLCONNECTIVITYMATRIX_LINK_LIBRARIES nsol )
    common_application( nsolConnectivityMatrix )

    set( NSOLCIRCUITLOADERSUMMARY_SOURCES nsolCircuitLoaderSummary.cpp )
    set( NSOLCIRCUITLOADERSUMMARY_LINK_LIBRARIES nsol )
    common_application( nsolCircuitLoaderSummary )
  endif( )

  set( NSOLEXTRACTNEURONSTATS_SOURCES extractNeuronStats.cpp )
  set( NSOLEXTRACTNEURONSTATS_LINK_LIBRARIES nsol )
  common_application( nsolExtractNeuronStats )

  set( NSOLSECTIONSTATS_SOURCES sectionStats.cpp )
  set( NSOLSECTIONSTATS_LINK_LIBRARIES nsol )
  common_application( nsolSectionStats )

  set( NSOLRADIUSSTAT_SOURCES radiusStat.cpp )
  set( NSOLRADIUSSTAT_LINK_LIBRARIES nsol )
  common_application( nsolRadiusStat )

  set( NSOLNEURITESTATS_SOURCES neuriteStats.cpp )
  set( NSOLNEURITESTATS_LINK_LIBRARIES nsol )
  common_application( nsolNeuriteStats )

  set( NSOLNEURONSTATS_SOURCES neuronStats.cpp )
  set( NSOLNEURONSTATS_LINK_LIBRARIES nsol )
  common_application( nsolNeuronStats )

  set( NSOLMINICOLUMNSTATS_SOURCES miniColumnStats.cpp )
  set( NSOLMINICOLUMNSTATS_LINK_LIBRARIES nsol )
  common_application( nsolMiniColumnStats )

  set( NSOLDATASET_SOURCES dataset.cpp )
  set( NSOLDATASET_LINK_LIBRARIES nsol )
  common_application( nsolDataset )

  set( NSOLSIMPLIFIER_SOURCES simplifier.cpp )
  set( NSOLSIMPLIFIER_LINK_LIBRARIES nsol )
  common_application( nsolSimplifier )

  set( NSOLBLUECONFIG2XMLSCENE_SOURCES blueConfig2XmlScene.cpp )
  set( NSOLBLUECONFIG2XMLSCENE_LINK_LIBRARIES nsol )
  common_application( nsolBlueConfig2XmlScene )

  if ( QT5CORE_FOUND )
    set( NSOLSCENE_SOURCES scene.cpp )
    set( NSOLSCENE_LINK_LIBRARIES nsol )
    common_application( nsolScene )
  endif( )

endif( NSOL_WITH_EXAMPLES )
