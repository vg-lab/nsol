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

echo BUILD_GENERATOR: ${BUILD_GENERATOR}
echo JAMBS_TARGETS: ${JAMBS_TARGETS}
echo GENERATOR_EXTRA_OPTIONS: ${GENERATOR_EXTRA_OPTIONS}


# Delete possible traces from old builds
rm -rf jambs Debug* Release*


if [[ -n "${JAMBS_TARGETS}" ]]; then

    echo Jambs additional dependencies processing

    #Download JAMBS and configs
    git clone git@gitlab.gmrv.es:common/jambs.git
    cd jambs
    for config in `cat ../.jambs_configs`; do
        echo "Cloning config " $config
        git clone $config
    done

    # Build dependencies via JAMBS for all build types
    for BUILD_TYPE in Debug Release; do
        BUILD_DIR=${BUILD_TYPE}.${BUILD_GENERATOR}
        cmake -E make_directory "${BUILD_DIR}"
        cd "${BUILD_DIR}"
        cmake .. \
              -DJAMBS_TARGETS="$JAMBS_TARGETS" \
              -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
              -G"$BUILD_GENERATOR"
        cmake --build . --config ${BUILD_TYPE} -- ${GENERATOR_EXTRA_OPTIONS}
        cd ..
    done

    # Get out of JAMBS directory
    cd ..

fi


# Build project
for BUILD_TYPE in Debug Release; do
    BUILD_DIR=${BUILD_TYPE}.${BUILD_GENERATOR}
    cmake -E make_directory "${BUILD_DIR}"
    cd "${BUILD_DIR}"

    cmake ..\
          -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
          -G"$BUILD_GENERATOR" \
          -DCMAKE_PREFIX_PATH="`pwd`/../jambs/${BUILD_DIR}/install"

    cmake --build . --config ${BUILD_TYPE} -- ${GENERATOR_EXTRA_OPTIONS}

    if [[ -n ${RUN_TESTS} ]]; then
        cmake --build . --target tests --config ${BUILD_TYPE} -- ${GENERATOR_EXTRA_OPTIONS}
    fi

    cd ..

done
