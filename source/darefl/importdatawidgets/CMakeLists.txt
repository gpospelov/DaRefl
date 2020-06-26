target_sources(${library_name} PRIVATE
    dataselectionmodel.cpp
    dataselectionmodel.h
    dataviewmodel.cpp
    dataviewmodel.h
    datarowstrategy.cpp
    datarowstrategy.h
    importdataeditor.cpp
    importdataeditor.h
)

target_include_directories(${library_name} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
