target_sources(${library_name} PRIVATE
    grapheditor.cpp
    grapheditor.h
    grapheditortoolbar.cpp
    grapheditortoolbar.h
)

target_include_directories(${library_name} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
