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

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoginButtonClicked();

private:
    QStackedWidget *stackedWidget;

    // Pagina di login
    QWidget *loginPage;
    QLineEdit *usernameField;
    QLineEdit *passwordField;
    QPushButton *loginButton;
    QLabel *errorLabel;

    // Pagina principale
    QWidget *mainPage;
    QLabel *welcomeLabel;
    QVBoxLayout *mainLayout;

    Biblioteca *biblioteca; // Oggetto Biblioteca per gestire i media

    void setupLoginPage();
    void setupMainPage();
    bool validateLogin(const QString &username, const QString &password);
};

#endif // MAINWINDOW_H