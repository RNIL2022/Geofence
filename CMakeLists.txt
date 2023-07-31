cmake_minimum_required(VERSION 3.16)

project(Serial_delete VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS SerialPort)
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(appSerial_delete
    main.cpp serial.h serial.cpp netcheck.h runnable_net.h nmea.h
)

qt_add_qml_module(appSerial_delete
    URI Serial_delete
    VERSION 1.0
    QML_FILES Main.qml
    RESOURCE_PREFIX /
)
# Resources:
set(resources_resource_files
    "mapbuild.html"
    "reload.png"
    "navigation.png"
)
qt_add_resources(appSerial_delete "resources"
    PREFIX
        "/"
    FILES
        ${resources_resource_files}
)
set_target_properties(appSerial_delete PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
target_link_libraries(appSerial_delete PRIVATE Qt6::SerialPort)
target_link_libraries(appSerial_delete PRIVATE Qt6::Core)
target_link_libraries(appSerial_delete
    PRIVATE Qt6::Quick
)

install(TARGETS appSerial_delete
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
set(INSTALL_DESTDIR "/opt")
install(TARGETS appSerial_delete
    RUNTIME DESTINATION "${INSTALL_DESTDIR}"
    BUNDLE DESTINATION "${INSTALL_DESTDIR}"
    LIBRARY DESTINATION "${INSTALL_DESTDIR}"
)
