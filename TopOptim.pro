#-------------------------------------------------
#
# Project created by QtCreator 2013-07-09T22:24:18
#
#-------------------------------------------------

QT       += core gui opengl
QT += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TopOptim
TEMPLATE = app
CONFIG += c++11

INCLUDEPATH += tmp/moc/release_shared

SOURCES += main.cpp\
    model.cpp \
    face.cpp \
    part.cpp \
    vertex.cpp \
    filemanager.cpp \
    optimalizationmanager.cpp \
    ga/GATreeGenome.C \
    ga/GATreeBASE.C \
    ga/GATree.C \
    ga/GAStringGenome.C \
    ga/GAStatistics.C \
    ga/GASStateGA.C \
    ga/GASimpleGA.C \
    ga/GASelector.C \
    ga/GAScaling.C \
    ga/GARealGenome.C \
    ga/garandom.C \
    ga/GAPopulation.C \
    ga/GAParameter.C \
    ga/GAListGenome.C \
    ga/GAListBASE.C \
    ga/GAList.C \
    ga/GAIncGA.C \
    ga/GAGenome.C \
    ga/gaerror.C \
    ga/GADemeGA.C \
    ga/GADCrowdingGA.C \
    ga/GABinStr.C \
    ga/gabincvt.C \
    ga/GABin2DecGenome.C \
    ga/GABaseGA.C \
    ga/GAAllele.C \
    ga/GA3DBinStrGenome.C \
    ga/GA3DArrayGenome.C \
    ga/GA2DBinStrGenome.C \
    ga/GA2DArrayGenome.C \
    ga/GA1DBinStrGenome.C \
    ga/GA1DArrayGenome.C \
    group.cpp \
    configurationwindow.cpp \
    gui/modelview.cpp \
    gui/mainwindow.cpp \
    gui/geometry.cpp \
    configurations.cpp \
    optimalizationwindow.cpp \
    optimconfigwindow.cpp \
    optimalizationgal.cpp \
    genomecollection.cpp

HEADERS  += mainwindow.h \
    errorCodes.h \
    model.h \
    face.h \
    part.h \
    vertex.h \
    filemanager.h \
    optimalizationmanager.h \
    ga/gaversion.h \
    ga/gatypes.h \
    ga/GATreeGenome.h \
    ga/GATreeBASE.h \
    ga/GATree.h \
    ga/GAStringGenome.h \
    ga/GAStatistics.h \
    ga/GASStateGA.h \
    ga/GASimpleGA.h \
    ga/GASelector.h \
    ga/GAScaling.h \
    ga/GARealGenome.h \
    ga/garandom.h \
    ga/GAPopulation.h \
    ga/GAParameter.h \
    ga/GANode.h \
    ga/GAMask.h \
    ga/GAListGenome.h \
    ga/GAListBASE.h \
    ga/GAList.h \
    ga/GAIncGA.h \
    ga/gaid.h \
    ga/GAGenome.h \
    ga/GAEvalData.h \
    ga/gaerror.h \
    ga/GADemeGA.h \
    ga/GADCrowdingGA.h \
    ga/gaconfig.h \
    ga/GABinStr.h \
    ga/gabincvt.h \
    ga/GABin2DecGenome.h \
    ga/GABaseGA.h \
    ga/GAArray.h \
    ga/GAAllele.h \
    ga/GA3DBinStrGenome.h \
    ga/GA3DArrayGenome.h \
    ga/GA2DBinStrGenome.h \
    ga/GA2DArrayGenome.h \
    ga/GA1DBinStrGenome.h \
    ga/GA1DArrayGenome.h \
    ga/ga.h \
    group.h \
    configurationwindow.h \
    modelview.h \
    gui/modelview.h \
    gui/mainwindow.h \
    gui/geometry.h \
    configurations.h \
    optimalizationwindow.h \
    optimconfigwindow.h \
    ga/std_stream.h \
    ioptimalizationmanager.h \
    optimalizationgal.h \
    genomecollection.h

FORMS    += gui/mainwindow.ui \
    configurationwindow.ui \


LIBRARIES = H:/Magisterka/Biblioteki

POCO = $$LIBRARIES/poco-1.4.6p1-all
BOOST = $$LIBRARIES/boost
OPENCVPATH = $$LIBRARIES/opencv/opencv_bin/install
FFMPEGPATH = $$LIBRARIES/ffmpeg/ffmpeg-20141128-git-cfd83a8
GENETICLIBRARY = $$LIBRARIES/GeneticLibrary

win32:CONFIG(release, debug|release): LIBS += -L$$POCO/lib/ -lPocoXML
else:win32:CONFIG(debug, debug|release): LIBS += -L$$POCO/lib/ -lPocoXMLd
else:unix: LIBS += -L$$POCO/lib/ -lPocoXML

INCLUDEPATH += $$POCO/XML/include
DEPENDPATH += $$POCO/XML/include

win32:CONFIG(release, debug|release): LIBS += -L$$POCO/lib/ -lPocoFoundation
else:win32:CONFIG(debug, debug|release): LIBS += -L$$POCO/lib/ -lPocoFoundationd
else:unix: LIBS += -L$$POCO/lib/ -lPocoFoundation

INCLUDEPATH += $$POCO/Foundation/include
DEPENDPATH += $$POCO/Foundation/include


win32:CONFIG(release, debug|release): LIBS += -L$$BOOST/lib/release -llibboost_system-vc100-mt-1_54
else:win32:CONFIG(debug, debug|release): LIBS += -L$$BOOST/lib/debug -llibboost_system-vc100-mt-1_54
else:unix: LIBS += -L$$BOOST/lib/ -llibboost_system-vc100-mt-1_54

INCLUDEPATH += $$BOOST/include/boost-1_54
DEPENDPATH += $$BOOST/include/boost-1_54

INCLUDEPATH += $$OPENCVPATH/include

RESOURCES += \
    gui/shaders.qrc

OPENCVLIBPATH = $$OPENCVPATH/x64/mingw/bin

LIBS += -L$$OPENCVLIBPATH \
    libopencv_core2410d \
    libopencv_highgui2410d \
    libopencv_imgproc2410d \
    libopencv_features2d2410d \
    libopencv_calib3d2410d

INCLUDEPATH += $$GENETICLIBRARY/GeneticLibrary/source
# -L$$GENETICLIBRARY/build/Debug \

#LIBS += -l$$GENETICLIBRARY/build/Debug/GeneticLibrary





