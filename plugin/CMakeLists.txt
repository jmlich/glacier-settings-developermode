SET(SRC developmentsettingsplugin.cpp)
SET(HEADERS developmentsettingsplugin.h)

SET(PLUGINS_FILES
    development.qml
    development.svg)

set(CMAKE_AUTOMOC ON)

add_definitions(-DQT_PLUGIN)

add_library(development MODULE ${SRC} ${HEADERS})
target_include_directories(development PUBLIC "/usr/include/glacier-settings/")

target_link_libraries(development
    Qt5::Gui
    Qt5::Qml
    Qt5::Quick
    -lglaciersettings)

install(TARGETS development
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/glacier-settings/)

INSTALL(FILES ${PLUGINS_FILES}
    DESTINATION /usr/share/glacier-settings/plugins/development/)
