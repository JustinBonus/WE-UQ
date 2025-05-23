#-------------------------------------------------
#
# Project created by QtCreator 2017-06-06T06:31:52
#
#-------------------------------------------------

include($$PWD/ConanHelper.pri)

QT += core gui charts concurrent network
QT += 3dcore 3drender 3dextras
QT += printsupport opengl widgets webenginewidgets
QT += webenginewidgets

CONFIG += c++17

#Disable m64 flag on windows
win32:QMAKE_CXXFLAGS -= -m64 #TODO: This seems to be cause by smelt Conan package

TARGET = WE_UQ
TEMPLATE = app

DEFINES += _GRAPHICS_Qt3D

QMAKE_APPLE_DEVICE_ARCHS="x86_64"

INCLUDEPATH += StochasticWindModel/include
INCLUDEPATH += Inflow
INCLUDEPATH += ExpertCFD
INCLUDEPATH += ExpertCFD/UI
INCLUDEPATH += ExpertCFD/Analysis
INCLUDEPATH += ExpertCFD/CFDanalysis
INCLUDEPATH += ExpertCFD/SimCenter_widgets
INCLUDEPATH += $$PWD/../VTK/include/vtk-9.2
INCLUDEPATH += /usr/local/include/vtk-9.2


win32 {

    LIBS +=  -lAdvapi32
    RC_ICONS = icons/NHERI-WEuq-Icon.ico
    DEPENDPATH += $$PWD/../VTK/Release/bin
    INCLUDEPATH += $$PWD/../VTK/Release/include/vtk-9.2
    LIBS += -L$$PWD/../VTK/Release/lib \
    -lvtkViewsCore-9.2 \
    -lvtkFiltersCore-9.2 \
    -lvtkFiltersSources-9.2 \
    -lvtkCommonCore-9.2 \
    -lvtkCommonColor-9.2 \
    -lvtkFiltersGeometry-9.2 \
    -lvtkRenderingCore-9.2 \
    -lvtkInteractionStyle-9.2\
    -lvtkCommonTransforms-9.2\
    -lvtkInteractionWidgets-9.2\
    -lvtkRenderingContextOpenGL2-9.2 \
    -lvtkRenderingFreeType-9.2 \
    -lvtkRenderingGL2PSOpenGL2-9.2 \
    -lvtkRenderingAnnotation-9.2 \
    -lvtkCommonExecutionModel-9.2 \
    -lvtkCommonDataModel-9.2 \
    -lvtkGUISupportQt-9.2 \
    -lvtkRenderingOpenGL2-9.2 \
    -lvtkIOGeometry-9.2 \
    -lvtkViewsQt-9.2 \
    -lvtkImagingCore-9.2 \
    -lvtkIOImage-9.2 \
    -lvtkIOLegacy-9.2 \
    -lvtksys-9.2

} else {

mac {

    ICON = icons/NHERI-WEuq-Icon.icns
#    DEPENDPATH += $$PWD/../VTK/lib
#    DEPENDPATH += $$PWD/../VTK/Release/bin
#    INCLUDEPATH += $$PWD/../VTK/Release/include/vtk-9.2
    INCLUDEPATH += $$PWD/../VTK/include/vtk-9.2
    INCLUDEPATH += /usr/local/include/vtk-9.2
    LIBS += -L$$PWD/../VTK/lib
    LIBS += -L/usr/local/lib \
    -lvtkViewsCore-9.2 \
    -lvtkFiltersCore-9.2 \
    -lvtkFiltersSources-9.2 \
    -lvtkCommonCore-9.2 \
    -lvtkCommonColor-9.2 \
    -lvtkFiltersGeometry-9.2 \
    -lvtkRenderingCore-9.2 \
    -lvtkInteractionStyle-9.2\
    -lvtkCommonTransforms-9.2\
    -lvtkInteractionWidgets-9.2\
    -lvtkRenderingContextOpenGL2-9.2 \
    -lvtkRenderingFreeType-9.2 \
    -lvtkRenderingGL2PSOpenGL2-9.2 \
    -lvtkRenderingAnnotation-9.2 \
    -lvtkCommonExecutionModel-9.2 \
    -lvtkCommonDataModel-9.2 \
    -lvtkGUISupportQt-9.2 \
    -lvtkRenderingOpenGL2-9.2 \
    -lvtkIOGeometry-9.2 \
    -lvtkViewsQt-9.2 \
    -lvtkImagingCore-9.2 \
    -lvtkIOImage-9.2 \
    -lvtkIOLegacy-9.2 \
    -lvtksys-9.2
    
    } else {

    INCLUDEPATH += /usr/include/vtk-9.1
    LIBS += -L/lib/x86_64-linux-gnu \
    -lvtkViewsCore-9.1 \
    -lvtkFiltersCore-9.1 \
    -lvtkCommonColor-9.1 \
    -lvtkFiltersSources-9.1 \
    -lvtkCommonCore-9.1 \
    -lvtkFiltersGeometry-9.1 \
    -lvtkRenderingCore-9.1 \
    -lvtkInteractionStyle-9.1\
    -lvtkCommonTransforms-9.1\
    -lvtkInteractionWidgets-9.1\
    -lvtkRenderingAnnotation-9.1 \
    -lvtkRenderingContextOpenGL2-9.1 \
    -lvtkRenderingFreeType-9.1 \
    -lvtkRenderingGL2PSOpenGL2-9.1 \
    -lvtkCommonExecutionModel-9.1 \
    -lvtkCommonDataModel-9.1 \
    -lvtkGUISupportQt-9.1 \
    -lvtkRenderingOpenGL2-9.1 \
    -lvtkIOGeometry-9.1 \
    -lvtkViewsQt-9.1 \
    -lvtkImagingCore-9.1 \
    -lvtkIOImage-9.1 \
    -lvtkIOLegacy-9.1 \
    -lvtksys-9.1
    }
    }

include(../SimCenterCommon/Common/Common.pri)
include(../SimCenterCommon/Workflow/Workflow.pri)
include(../SimCenterCommon/RandomVariables/RandomVariables.pri)
include(../SimCenterCommon/InputSheetBM/InputSheetBM.pri)
include(./WindEvents.pri)

SOURCES += main.cpp \
    WorkflowAppWE.cpp \
    RunWidget.cpp \
    ComponentAndCladdingWindEDP.cpp \
    WindEDP_Selection.cpp \
    StandardWindEDP.cpp

HEADERS  += \
    WorkflowAppWE.h \
    RunWidget.h \
    ComponentAndCladdingWindEDP.h \
    StandardWindEDP.h \
    WindEDP_Selection.h


DISTFILES += \
    WEUQinstaller/InstallScripts/README.txt \
    WEUQinstaller/InstallScripts/makeInstallPackageWEUQ-with-QWT.sh \
    WEUQinstaller/InstallScripts/makeInstallPackageWEUQ.sh \
    WEUQinstaller/config/NHERI-WEuq-Icon.icns \
    WEUQinstaller/config/NHERI-WEuq-Icon.png \
    WEUQinstaller/config/WEUQInstallerLogo.png \
    WEUQinstaller/config/macconfig.xml \
    WEUQinstaller/config/nheri_weuq_icon.ico \
    WEUQinstaller/config/watermark.png \
    WEUQinstaller/config/winconfig.xml \
    WEUQinstaller/packages/nheri.simcenter.python/data/python.fake \
    WEUQinstaller/packages/nheri.simcenter.python/meta/installPython.qs \
    WEUQinstaller/packages/nheri.simcenter.python/meta/license.txt \
    WEUQinstaller/packages/nheri.simcenter.python/meta/package.xml \
    WEUQinstaller/packages/nheri.simcenter.weuq/meta/installWEUQ.qs \
    WEUQinstaller/packages/nheri.simcenter.weuq/meta/license.txt \
    WEUQinstaller/packages/nheri.simcenter.weuq/meta/package.xml \
    wImage2.gif \
    wImage3.gif \
    wImage4.gif \
    wImage1.png \
    wImage_DEDM_HRP_Logo

OTHER_FILES += conanfile.py azure-pipelines.yml

RESOURCES += images.qrc
