#QT += gui-private core-private
QT += gui core widgets opengl xml

HEADERS += wfodisplay.h \
    Vertex/VertexData.h \
    Vertex/Vertex.h \
    Vertex/Normal.h \
    WaveFrontObject/WaveFrontObject.h \
    Face/Face.h \
    Face/FaceData.h \
    mainwindow.h \
    about.h \
    Material/MaterialData.h \
    Material/Material.h \
    Common/wfoutils.h

SOURCES += wfodisplay.cpp main.cpp \
    Vertex/VertexData.cpp \
    Vertex/Vertex.cpp \
    Vertex/Normal.cpp \
    WaveFrontObject/WaveFrontObject.cpp \
    Face/Face.cpp \
    Face/FaceData.cpp \
    mainwindow.cpp \
    about.cpp \
    Material/MaterialData.cpp \
    Material/Material.cpp \
    Common/wfoutils.cpp

OTHER_FILES += \
    vshader.txt \
    fshader.txt

RESOURCES += \
    shaders.qrc

FORMS += \
    mainwindow.ui \
    about.ui

