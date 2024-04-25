set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/submodule/cmake-sphinx/cmake/Modules")

find_package(Doxygen REQUIRED)
find_package(Sphinx REQUIRED breathe)

set(DOXYGEN_GENERATE_HTML NO)
set(DOXYGEN_GENERATE_XML YES)
doxygen_add_docs(doxygen
    ${PROJECT_SOURCE_DIR}/includes
    COMMENT "Generate man pages")


sphinx_add_docs(
  Isochrone_Sphinx_documentation
  BREATHE_PROJECTS doxygen
  BUILDER html
  SOURCE_DIRECTORY source
)