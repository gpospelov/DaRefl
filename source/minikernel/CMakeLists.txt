set(library_name minikernel)

add_library(${library_name} SHARED "")

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
target_include_directories(${library_name} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/..>)
