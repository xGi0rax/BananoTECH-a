#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include "LoginPage.h"
#include "LibraryChoicePage.h"
#include "MainPage.h"
#include "AddPage.h"
#include "ModifyPage.h"
#include "DetailsPage.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoginButtonClicked();
    void switchToLoginPage(); // Slot per tornare alla LoginPage
    void switchToLibraryChoicePage(); // Slot per la pagina di scelta biblioteca
    void onLibraryReady(Biblioteca* biblioteca); // Slot per gestire la biblioteca 
    void switchToMainPage(); // Slot per passare alla MainPage
    void switchToAddPage(); // Slot per passare alla AddPage
    void switchToModifyPage(Media* media); // Slot per passare alla ModifyPage
    void switchToDetailsPage(Media* media); // Slot per passare alla DetailsPage

private:
    QStackedWidget *stackedWidget;

    // Pagina di login
    LoginPage *loginPage;

    // Pagina di scelta della biblioteca
    LibraryChoicePage *libraryChoicePage;

    // Pagina principale
    MainPage *mainPage;

    // Pagina di aggiunta media
    AddPage *addPage;

    // Pagina di modifica dei media
    ModifyPage *modifyPage;
    
    // Pagina dettagli media
    DetailsPage *detailsPage;

    Biblioteca *biblioteca; // Oggetto Biblioteca per gestire i media

    // Metodi per setuppare le pagine
    void setupLoginPage();
    void setupLibraryChoicePage();
    void setupMainPage(Biblioteca* biblio);
    void setupAddPage();
    void setupModifyPage();
    void setupDetailsPage();

    bool validateLogin(const QString &username, const QString &password);
};

#endif // MAINWINDOW_H