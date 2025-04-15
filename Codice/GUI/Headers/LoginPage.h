#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QFrame>

class LoginPage : public QWidget {
    Q_OBJECT
public:
    explicit LoginPage(QWidget *parent = nullptr);

    QString getUsername() const;
    QString getPassword() const;
    void showErrorMessage(const QString &message);
    void clearErrorMessage();
    
signals:
    void loginAttempted();

private:
    QLineEdit *usernameField;
    QLineEdit *passwordField;
    QPushButton *loginButton;
    QLabel *errorLabel;

private slots:
    void onLoginButtonClicked();
};

#endif // LOGINPAGE_H