# nsol

## git master

## 0.4.0

* [!86] Updated license file to LGPLv3.
* [!85] Added method to force the recompute of the soma parameters
* [!84] Fixed neuron transformation matrix load error
* [!81] Connectivity load improvement
* [!83] Added support to load mvd3 format circuit files in BrionReader and DataSet.…
* [!82] Fix clone method for Dendrite and Axon objects

## 0.3.0

* [!79] Spelling
* [!78] Added neuron transform matrix compute nan check in the BrionReader
* [!77] Documenting method loadMorphology of VectorsReader
* [!69] Asc loader
* [!74] Added functionality to load morphology from vectors
* [!73] Avoid expose id as reference
* [!72] Avoid include complete Eigen on each compilation
* [!71] Fixed Doxygen warnings.
* [!70] Vasculature
* [!68] Refactored swc loader
* [!65] Section class refactorized to support graph structures.

## 0.2.0

* [!67] Changed version to 0.2.0. Updated Changelog.md. (doc)
* [!66] Fixed brion morphology loader special case. Added loaders comparison test. (bug)
* [!64] Minor changes in doc (doc)
* [!63] Bump Brion and update BrionReader accordingly. (building)
* [!59] Test stats. (testing)
* [!61] Bugfix: reorder parameters in git clone. (doc)
* [!60] Changed CMake to submodule. Fixes for CPack and install exporting examples code. Clean-ups. (building)
* [!49] Added data structures and loaders for connectivity data.
* [!58] Updated README.md and Changelog.md. Changed FiReS subproject url to Github. (building)(doc)
* [!53] Added CI coverage.
* [!57] License gplv3.
* [!56] Updated Windows CI config (building)
* [!55] Clean-ups and updates in examples. Removed BBPSDK old references. Removed Factory.h.
* [!54] Move CI to sierra and vs14.
* [!52] New method to adapt the trace fixing the intersected bifurcations
* [!50] Fixes for GCC6 warnings.
* [!48] Fixed unnused params in XMLSceneReader
* [!47] Added options for examples and tests
* [!46] Changed neuron loader reposition false by default. Fixed soma reposition in BrionReader
* [!44] Fixing bug: rotation matrix of the neurons. (bug)
* [!45] Fixed compute of soma params for file with 3 nodes per soma
* [!43] Optional brion
* [!42] Xml Scene Writer
* [!41] Adapt to FiReS casing. Change CI optional deps building.
* [!39] Morphology simplifier
* [!40] Changed vmmlib to eigen.
* [!38] Fixed warning for GCC 4.9
* [!37] Added checking for enough fields in swc input files. Improved log class and upda…
* [!33] Radius stat
* [!35] Axon
* [!34] Added more neuron types. Renamed HIERARCHY to CORTICAL_HIERARCHY. Added a contai…
* [!32] Added a tool for extracting stats (to console or csv) from all the neurons of a DataSet.
* [!30] Yml
* [!29] Gitlab CI .YML
* [!28] Updated to new fires naming (feature is now called property).
* [!27] Fixed const methods and parameters. Removed tabs. Clean-ups.
* [!26] Neuron types
* [!25] Change neuron type. Get directly from bbpsdk
* [!24] Added load option only HIERARCHY
* [!22] Cmake update
* [!19] First attempt to use a general Object class and an ObjectWithProperties class. Also Log class added.
* [!16] Qt5 compile option
* [!15] Load data
* [!14] Added reposition on load. API modify SwcReader::readFile() -> readMorphology
* [!13] Added first steps to load a XML scene. Added example scene.xml file in testData.…
* [!11] Data set swc
* [!9] Added load flags enum and fixed DataSet and BBPSDK reader to use it (only MORPHO…
* [!8] Added DataSet class and example. Fixed cppcheck errors. Clean-ups.
* [!7] Fixed cppcheck errors.
* [!6] Added the option to specify target and types when loading a BlueConfig file. Clean-ups.
* [!5] Vs10
* [!4] Subproject
