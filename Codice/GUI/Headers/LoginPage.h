#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QFrame>
#include <QKeyEvent>

class LoginPage : public QWidget {
    Q_OBJECT
public:
    explicit LoginPage(QWidget *parent = nullptr);

    QString getUsername() const;
    QString getPassword() const;
    void showErrorMessage(const QString &message);
    void clearErrorMessage();
    void resetToDefaultState();
    
signals:
    void loginAttempted();

private:
    QLineEdit *usernameField;
    QLineEdit *passwordField;
    QPushButton *loginButton;
    QLabel *errorLabel;

private slots:
    void onLoginButtonClicked();

protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // LOGINPAGE_H