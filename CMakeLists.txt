cmake_minimum_required(VERSION 3.6.0)

project(glacier-settings-developermode
        VERSION 0.0.1
        DESCRIPTION "Glacier settings pugin to manage developer mode")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include(FeatureSummary)
include(GNUInstallDirs)

set(CMAKE_INSTALL_PREFIX /usr)
set(INSTALL_QML_IMPORT_DIR "${CMAKE_INSTALL_FULL_LIBDIR}/qt/qml"
	CACHE PATH "Custom QML import installation directory")

set(QT_MIN_VERSION "5.11.0")
find_package(Qt5 ${QT_MIN_VERSION} COMPONENTS Gui Qml Quick DBus REQUIRED)

### Sets QT_INSTALL_QML to the directory where QML Plugins should be installed
function(FindQtInstallQml)
    find_program(QMAKE NAMES qmake-qt5 qmake)
    if(NOT QMAKE)
        message(FATAL_ERROR "qmake not found")
    endif()
    execute_process(
        COMMAND ${QMAKE} -query QT_INSTALL_QML
        OUTPUT_VARIABLE PROC_RESULT
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    set(QT_INSTALL_QML ${PROC_RESULT} PARENT_SCOPE)
endfunction()

FindQtInstallQml()

add_subdirectory(org.glacier.developermode)
add_subdirectory(daemon)
add_subdirectory(plugin)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
