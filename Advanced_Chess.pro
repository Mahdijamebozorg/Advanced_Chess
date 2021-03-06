QT += quick

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        backend.cpp \
        main.cpp \
        src/Bishop.cpp \
        src/Cell.cpp \
        src/ChessBoard.cpp \
        src/Chessman.cpp \
        src/Filemanager.cpp \
        src/Functions.cpp \
        src/GameManager.cpp \
        src/King.cpp \
        src/Knight.cpp \
        src/Pawn.cpp \
        src/Queen.cpp \
        src/Rook.cpp \
        src/User.cpp \

RESOURCES += \
    qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

includeS += \
    include/Bishop.hpp \
    include/Cell.hpp \
    include/ChessBoard.hpp \
    include/Chessman.hpp \
    include/Exceptions.hpp \
    include/GameManager.hpp \
    include/King.hpp \
    include/Knight.hpp \
    include/Pawn.hpp \
    include/Queen.hpp \
    include/Rook.hpp \
    include/User.hpp \
    backend.hpp \
    include/Bishop.hpp \
    include/Cell.hpp \
    include/ChessBoard.hpp \
    include/Chessman.hpp \
    include/Exceptions.hpp \
    include/GameManager.hpp \
    include/King.hpp \
    include/Knight.hpp \
    include/Pawn.hpp \
    include/Queen.hpp \
    include/Rook.hpp \
    include/User.hpp

DISTFILES += \
    Images/Black/BBishop.png \
    Images/Black/BKing.png \
    Images/Black/BKnight.png \
    Images/Black/BPawn.png \
    Images/Black/BQueen.png \
    Images/Black/BRook.png \
    Images/login.jpg

HEADERS += \
    backend.hpp \
    include/Bishop.hpp \
    include/Cell.hpp \
    include/ChessBoard.hpp \
    include/Chessman.hpp \
    include/Exceptions.hpp \
    include/Filemanager.hpp \
    include/GameManager.hpp \
    include/King.hpp \
    include/Knight.hpp \
    include/Pawn.hpp \
    include/Queen.hpp \
    include/Rook.hpp \
    include/User.hpp \
