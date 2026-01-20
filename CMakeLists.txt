cmake_minimum_required(VERSION 3.16)

project(DigitalAudioWorkstation VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(DigitalAudioWorkstation
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        widgets/projectcontroller.h widgets/projectcontroller.cpp widgets/projectcontroller.ui


        graphics/arrangementview.h graphics/arrangementview.cpp

        core/musictimemanager.h core/musictimemanager.cpp
        core/musictime.h core/musictime.cpp
        core/gridmanager.h core/gridmanager.cpp
        core/ringbuffer.h core/ringbuffer.cpp
        core/transport.h core/transport.cpp
        core/math.h
        core/parameter.h core/parameter.cpp
        core/structs.h core/structs.cpp
        core/projectassetmanager.h core/projectassetmanager.cpp
        core/mixer.h core/mixer.cpp

        audio/audioassetmanager.h audio/audioassetmanager.cpp
        audio/audiostructs.h
        audio/audioengine.h audio/audioengine.cpp
        audio/audionode.h audio/audionode.cpp
        audio/audiotrack.h audio/audiotrack.cpp
        audio/audioclipmanager.cpp
        audio/audioclipmanager.h
        graphics/basesceneclip.h graphics/basesceneclip.cpp
        graphics/basegraphicstrack.h graphics/basegraphicstrack.cpp
        graphics/audiographicstrack.h graphics/audiographicstrack.cpp
        graphics/globalscene.h graphics/globalscene.cpp
        graphics/audiosceneclip.h graphics/audiosceneclip.cpp
        graphics/playhead.h graphics/playhead.cpp
        graphics/timelineselector.h graphics/timelineselector.cpp
        midi/midistructs.h
        midi/midiassetmanager.h midi/midiassetmanager.cpp
        midi/midiparser.h midi/midiparser.cpp
        midi/midiplaybackengine.h midi/midiplaybackengine.cpp
        core/node.h
        core/clipmanager.h core/clipmanager.cpp
        core/idmanager.h core/idmanager.cpp
        midi/midiclipmanager.h midi/midiclipmanager.cpp
        midi/midinode.h midi/midinode.cpp
        instruments/instrumentnode.h instruments/instrumentnode.cpp
        core/track.h core/track.cpp
        midi/miditrack.h midi/miditrack.cpp
        instruments/adsr.h instruments/adsr.cpp



    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET DigitalAudioWorkstation APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(DigitalAudioWorkstation SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(DigitalAudioWorkstation
            ${PROJECT_SOURCES}
        )
    endif()
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(RT_AUDIO REQUIRED rtaudio)


add_subdirectory(lib/midifile)
target_include_directories(DigitalAudioWorkstation PRIVATE ${RT_AUDIO_INCLUDE_DIRS})

target_include_directories(DigitalAudioWorkstation PRIVATE lib/midifile/include)

target_link_libraries(DigitalAudioWorkstation PRIVATE ${RT_AUDIO_LIBRARIES})

target_link_libraries(DigitalAudioWorkstation PRIVATE asound pthread)

target_link_libraries(DigitalAudioWorkstation PRIVATE sndfile)

target_link_libraries(DigitalAudioWorkstation PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(DigitalAudioWorkstation PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(DigitalAudioWorkstation PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(DigitalAudioWorkstation PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(DigitalAudioWorkstation PRIVATE midifile)


if(WIN32)
    target_compile_defintions(midiFile PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.DigitalAudioWorkstation)
endif()
set_target_properties(DigitalAudioWorkstation PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS DigitalAudioWorkstation
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(DigitalAudioWorkstation)
endif()
