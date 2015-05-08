##############################################################
#
# Building script for gitlabci
# Grupo de Modelado y Realidad Virtual (GMRV)
# Universidad Rey Juan Carlos - URJC
#
##############################################################

# Variables to be set before calling
# BUILD_GENERATOR: cmake generator to be used
# JAMBS_TARGETS: dependencies to be build (semicolon separated)
# GENERATOR_EXTRA_OPTIONS: options to be passed to the native generator

# Delete possible traces from old builds
rm -rf jambs Debug* Release*

#Download JAMBS and configs
git clone git@gitlab.gmrv.es:common/jambs.git
cd jambs
git clone git@gitlab.gmrv.es:common/jambs-config-nsviz.git
git clone git@gitlab.gmrv.es:common/jambs-config-hbp.git

# Build dependencies via JAMBS for all build types
for BUILD_TYPE in Debug Release; do
    BUILD_DIR=${BUILD_TYPE}.${BUILD_GENERATOR}
    cmake -E make_directory "${BUILD_DIR}"
    cd "${BUILD_DIR}"
    cmake .. \
        -DJAMBS_TARGETS="$JAMBS_TARGETS" \
        -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
        -G"$BUILD_GENERATOR"
    cmake --build . -- ${GENERATOR_EXTRA_OPTIONS}
    cd ..
done

# Get out of JAMBS directory
cd ..

# Build project
for BUILD_TYPE in Debug Release; do
    BUILD_DIR=${BUILD_TYPE}.${BUILD_GENERATOR}
    cmake -E make_directory "${BUILD_DIR}"
    cd "${BUILD_DIR}"

    cmake .. -DCMAKE_PREFIX_PATH="`pwd`/../jambs/${BUILD_DIR}/install"
    cmake --build . -- ${GENERATOR_EXTRA_OPTIONS}
    cmake --build . --target tests -- ${GENERATOR_EXTRA_OPTIONS}
    cd ..
done
