set(SRC
    main.cpp
    systemdconnector.cpp
    systemdconnector.h
    userspaceconnector.cpp
    userspaceconnector.h)

add_executable(glacier-developermode-daemon ${SRC})

target_link_libraries(glacier-developermode-daemon PUBLIC
    Qt5::Core
    Qt5::DBus)

install(FILES
    nemo-developermode-dbus.conf
    DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/dbus-1/system.d/)

install(FILES
    nemodebugmode.service
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/systemd/system/)

install(TARGETS glacier-developermode-daemon RUNTIME
        DESTINATION ${CMAKE_INSTALL_BINDIR})
