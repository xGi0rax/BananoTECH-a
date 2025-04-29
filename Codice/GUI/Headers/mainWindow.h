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
#include "MainPage.h"
#include "AddPage.h"
#include "DetailsPage.h"  // Aggiungo l'include per la nuova pagina

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoginButtonClicked();
    void switchToLoginPage(); // Slot per tornare alla LoginPage
    void switchToMainPage(); // Slot per passare alla MainPage
    void switchToAddPage(); // Slot per passare alla AddPage
    void switchToDetailsPage(Media* media); // Slot per passare alla DetailsPage

private:
    QStackedWidget *stackedWidget;

    // Pagina di login
    LoginPage *loginPage;

    // Pagina principale
    MainPage *mainPage;

    // Pagina di aggiunta media
    AddPage *addPage;
    
    // Pagina dettagli media
    DetailsPage *detailsPage;

    Biblioteca *biblioteca; // Oggetto Biblioteca per gestire i media

    void setupLoginPage();
    void setupMainPage();
    void setupAddPage();
    void setupDetailsPage();
    bool validateLogin(const QString &username, const QString &password);
};

#endif // MAINWINDOW_H