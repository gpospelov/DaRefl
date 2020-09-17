
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
    simulationview_v1.cpp
    simulationview_v1.h
    simulationview_v2.cpp
    simulationview_v2.h
    styleutils.cpp
    styleutils.h
)

