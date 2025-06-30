#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <QCloseEvent>
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
    void switchToLoginPage(); // Slot per passare alla LoginPage
    void switchToLibraryChoicePage(); // Slot per passare alla pagina di scelta biblioteca
    void switchToMainPage(); // Slot per passare alla MainPage
    void switchToAddPage(); // Slot per passare alla AddPage
    void switchToModifyPage(Media* media); // Slot per passare alla ModifyPage
    void switchToDetailsPage(Media* media); // Slot per passare alla DetailsPage
    void onLibraryReady(Biblioteca* biblioteca, const QString& filePath, bool isNew); // Slot per gestire la biblioteca 
    void prendiInPrestitoMedia(Media* media); // Slot per prendere in prestito un media
    void restituisciMedia(Media* media); // Slot per restituire un media

private:
    QStackedWidget *stackedWidget; // StackedWidget per gestire le pagine

    LoginPage *loginPage; // Pagina di login
    LibraryChoicePage *libraryChoicePage; // Pagina di scelta della biblioteca
    MainPage *mainPage; // Pagina principale
    AddPage *addPage; // Pagina di aggiunta media
    ModifyPage *modifyPage; // Pagina di modifica dei media
    DetailsPage *detailsPage; // Pagina dettagli media

    Biblioteca *biblioteca; // Oggetto Biblioteca per gestire i media
    QString loadedFilePath; // Traccia il percorso del file caricato
    bool isNewLibrary; // Indica se si sta creando una nuova biblioteca
    bool hasUnsavedChanges; // Indica se ci sono modifiche non salvate

    // Metodi per setuppare le pagine
    void setupLoginPage();
    void setupLibraryChoicePage();
    void setupMainPage(Biblioteca* biblio);
    void setupAddPage();
    void setupModifyPage();
    void setupDetailsPage();

    // Metodo per validare le credenziali di login
    bool validateLogin(const QString &username, const QString &password);
    bool checkUnsavedChanges();

protected:
    void closeEvent(QCloseEvent *event) override; // Gestione dell'evento di chiusura della finestra
};

#endif // MAINWINDOW_H