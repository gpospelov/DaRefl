
add_subdirectory(simulationwidget)

target_sources(${library_name} PRIVATE
    actionmanager.cpp
    actionmanager.h
    collapsiblebar.cpp
    collapsiblebar.h
    collapsiblelistwidget.cpp
    collapsiblelistwidget.h
    dockscontroller.cpp
    dockscontroller.h
    editortoolbar.cpp
    editortoolbar.h
    editorwidget.cpp
    editorwidget.h
    fancytab.cpp
    fancytab.h
    mainbarwidget.cpp
    mainbarwidget.h
    mainwindow.cpp
    mainwindow.h
    refldockwindow.cpp
    refldockwindow.h
    styleutils.cpp
    styleutils.h
)

