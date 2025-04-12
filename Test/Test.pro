TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++17

INCLUDEPATH += "../Codice/Modello logico/Headers"
INCLUDEPATH += include

SOURCES += "Modello Logico/testBiblioteca.cpp" \
           "mainTest.cpp" \
           "../Codice/Modello logico/Sorgenti/Biblioteca.cpp" \
           "../Codice/Modello logico/Sorgenti/Libro.cpp" \
           "../Codice/Modello logico/Sorgenti/Media.cpp"

QT += core gui xml
