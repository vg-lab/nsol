# nsol

NeuroScience Objects Library

nsol provides data structures to handle basic neuroscientific data, mainly cortex morphologies and structures such as Spine, Soma, Neuron, Column, etc. It also includes readers and writers to load and store datasets in the SWC format (as used by [NeuroMorpho](http://neuromorpho.org/)) and in XML. Circuits and morphologies can also be read through [Brion](https://github.com/vg-lab/Brion), which is an optional dependency.

nsol is used in projects such as [NeuroScheme](https://github.com/vg-lab/NeuroScheme), [ViSimpl](https://vg-lab.es/visimpl/) and [NeuroLOTs](https://vg-lab.es/neurotessmesh/).

## Building

```bash
git clone https://github.com/vg-lab/nsol.git
cd nsol

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
```

In-source builds are not allowed, so always configure into a separate build directory. If `CMAKE_BUILD_TYPE` is not specified, it defaults to `Debug`, so make sure to build the `Release` version to get the best performance possible.

## CMake options

| Option | Default | Description |
| ------ | ------- | ----------- |
| `BUILD_SHARED_LIBS` | `ON` | Build nsol as a shared library (set to `OFF` for static) |
| `BUILD_DOCS` | `ON` | Generate Doxygen documentation when Doxygen is found |
| `NSOL_WITH_EXAMPLES` | `ON` | Build the programs in `examples/` (only when nsol is the top-level project) |
| `NSOL_WITH_TESTS` | `ON` | Build the tests in `tests/` (only when nsol is the top-level project) |
| `NSOL_OPTIONALS_AS_REQUIRED` | `OFF` | Treat optional dependencies (Qt5Core, HDF5, OpenMP) as required |
| `NSOL_WITH_LOGGING` | `ON` | Enable logging |
| `NSOL_USE_SHARED_PTR` | `OFF` | Use `std::shared_ptr` for nsol objects |
| `NSOL_USE_BRION` | `ON` | Enable Brion support (reading circuits and morphologies) |
| `NSOL_USE_FIRES` | `ON` | Enable FiReS support |

Other options are set automatically depending on whether extra libraries are found, and can be overridden:
 
| Option | Default | Description |
| ------ | ------- | ----------- |
| `NSOL_USE_HDF5` | `ON` if HDF5 is found | Enable HDF5 support |
| `NSOL_USE_QT5CORE` | `ON` if Qt5Core is found | Enable Qt5Core support |
| `NSOL_USE_OPENMP` | `ON` if OpenMP is found | Enable OpenMP parallelization |

Example:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON -DNSOL_USE_BRION=OFF -DNSOL_WITH_EXAMPLES=OFF -DBUILD_DOCS=OFF
```

## Dependencies

nsol resolves its dependencies through CMake. Required dependencies are looked up with `find_package()` and must be installed on your system or made discoverable by adding their install location to `CMAKE_PREFIX_PATH`.

For some optional dependencies, CMake first looks for an installed copy with `find_package()`. Only if it is not found is the dependency downloaded and built using `FetchContent`. This supports two workflows:

- System packages: install the dependencies with your package manager, or point CMake at them with `CMAKE_PREFIX_PATH`.
- Automatic fetching: on a system without them installed, the missing dependencies are fetched automatically during configuration. Each fetched dependency can be skipped by turning off its corresponding `NSOL_USE_*` option (see [CMake options](#cmake-options)).

## Testing

After building nsol, you can run the tests from the build directory:

```bash
ctest --test-dir build
```

The examples are also available in the build tree. For example, to run a simple program that loads a scene description and dumps information about it:

```bash
build/examples/nsolExampleScene build/testData/scene.xml
```

## Using nsol in your project

`nsol` and `nsol::nsol` refer to the same CMake library target; the namespaced form is recommended for downstream projects.

### With `find_package`

Install nsol, then consume it:

```bash
cmake --install build --prefix /your/prefix
```

```cmake
find_package(nsol REQUIRED)
target_link_libraries(my_app PRIVATE nsol::nsol)
```

Add `-DCMAKE_PREFIX_PATH=/your/prefix` when configuring your project if the prefix is not a default search location.

### With `FetchContent`

```cmake
include(FetchContent)
FetchContent_Declare(
  nsol
  GIT_REPOSITORY https://github.com/vg-lab/nsol.git
  GIT_TAG        master  # pin to a tag or commit
)
FetchContent_MakeAvailable(nsol)

target_link_libraries(my_app PRIVATE nsol::nsol)
```

## Documentation

The API documentation is generated from the source with Doxygen. To build it locally (requires Doxygen and `BUILD_DOCS=ON`):

```bash
cmake --build build --target nsol_doxygen
```

The HTML output is written to `build/docs_doxygen/html`.

## License

nsol is released under the [GNU Lesser General Public License v3.0](LICENSE.txt).

Developed at the [Visualization and Graphics Lab (VG-Lab)](https://github.com/vg-lab).
