set(library_name dareflcore)

add_library(${library_name} STATIC "")

add_subdirectory(mainwindow)
add_subdirectory(model)
add_subdirectory(resources)
add_subdirectory(famousloader)
add_subdirectory(importdataview)
add_subdirectory(layereditor)
add_subdirectory(materialeditor)
add_subdirectory(quicksimeditor)
add_subdirectory(settingsview)
add_subdirectory(sldeditor)
add_subdirectory(welcomeview)

target_link_libraries(${library_name} PUBLIC MVVM::View Qt5::Core Qt5::Gui Qt5::Widgets minikernel)
target_include_directories(${library_name} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/..>)

