set(library_name dareflcore)

add_library(${library_name} STATIC "")

add_subdirectory(mainwindow)
add_subdirectory(model)
add_subdirectory(resources)
add_subdirectory(grapheditor)
add_subdirectory(importdatawidgets)
add_subdirectory(layereditor)
add_subdirectory(materialeditor)
add_subdirectory(quicksimeditor)
add_subdirectory(sldeditor)
add_subdirectory(welcomeview)

target_link_libraries(${library_name} PUBLIC MVVM::View Qt5::Core Qt5::Gui Qt5::Widgets)

