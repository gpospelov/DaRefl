
add_subdirectory(Basics)
add_subdirectory(Computation)
add_subdirectory(Fit)
add_subdirectory(Material)
add_subdirectory(MultiLayer)
add_subdirectory(Parametrization)
add_subdirectory(Scattering)
add_subdirectory(Vector)
add_subdirectory(Tools)

target_sources(${library_name} PRIVATE
#     Exceptions.h
#     Exceptions.cpp
#     Material.h
#     Material.cpp
#     Slice.h
#     Slice.cpp
)
