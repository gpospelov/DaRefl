set(library_name minikernel)

add_library(${library_name} SHARED "")

set(export_filename ${DAREFL_AUTOGEN_DIR}/darefl/minikernel_export.h)
generate_export_header(${library_name} EXPORT_FILE_NAME ${export_filename})

add_subdirectory(Basics)
add_subdirectory(Computation)
add_subdirectory(Fit)
add_subdirectory(Material)
add_subdirectory(MultiLayer)
add_subdirectory(Parametrization)
add_subdirectory(Scattering)
add_subdirectory(Vector)
add_subdirectory(Tools)

target_link_libraries(${library_name} PUBLIC Eigen3::Eigen)
target_include_directories(${library_name} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/..>
    $<BUILD_INTERFACE:${DAREFL_AUTOGEN_DIR}>)

