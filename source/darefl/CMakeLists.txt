set(library_name dareflcore)

if(WIN32)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBA_CORE_BUILD_DLL")
endif()

add_library(${library_name} SHARED "")

# -- Generate header for export --

set(export_filename ${DAREFL_AUTOGEN_DIR}/darefl/darefl_export.h)
generate_export_header(${library_name} EXPORT_FILE_NAME ${export_filename})

add_subdirectory(dataloader)
add_subdirectory(importdataview)
add_subdirectory(layereditor)
add_subdirectory(mainwindow)
add_subdirectory(materialeditor)
add_subdirectory(model)
add_subdirectory(quicksimeditor)
add_subdirectory(resources)
add_subdirectory(settingsview)
add_subdirectory(sldeditor)
add_subdirectory(welcomeview)

target_link_libraries(${library_name} PUBLIC MVVM::View Qt5::Core Qt5::Gui Qt5::Widgets minikernel)
target_include_directories(${library_name} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/..>
    $<BUILD_INTERFACE:${DAREFL_AUTOGEN_DIR}>)
