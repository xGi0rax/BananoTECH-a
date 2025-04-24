#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include "../../Modello logico/Headers/Biblioteca.h"
#include "LoginPage.h"
#include "MainPage.h"
#include "AddPage.h"

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

private:
    QStackedWidget *stackedWidget;

    // Pagina di login
    LoginPage *loginPage;

    // Pagina principale
    MainPage *mainPage;

    Biblioteca *biblioteca; // Oggetto Biblioteca per gestire i media

    // Pagina di aggiunta media
    AddPage *addPage;

    void setupLoginPage();
    void setupMainPage();
    void setupAddPage();
    bool validateLogin(const QString &username, const QString &password);
};

#endif // MAINWINDOW_H