TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++17

INCLUDEPATH += "../Codice/Modello logico/Headers"
INCLUDEPATH += include

SOURCES += "Modello Logico/testBiblioteca.cpp" \
           "Modello Logico/testJsonIO.cpp" \
           "Modello Logico/testXmlIO.cpp" \
           "mainTest.cpp" \
           "../Codice/Modello logico/Sorgenti/Biblioteca.cpp" \
           "../Codice/Modello logico/Sorgenti/XmlIO.cpp" \
           "../Codice/Modello logico/Sorgenti/JsonIO.cpp" \
           "../Codice/Modello logico/Sorgenti/Libro.cpp" \
           "../Codice/Modello logico/Sorgenti/Vinile.cpp" \
           "../Codice/Modello logico/Sorgenti/Film.cpp" \
           "../Codice/Modello logico/Sorgenti/Rivista.cpp" \
           "../Codice/Modello logico/Sorgenti/GiocoDaTavolo.cpp" \
           "../Codice/Modello logico/Sorgenti/Media.cpp"

QT += core gui xml
