#ifndef LIBRARYCHOICEPAGE_H
#define LIBRARYCHOICEPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include "../../Modello logico/Headers/Biblioteca.h"

class LibraryChoicePage : public QWidget {
    Q_OBJECT

public:
    explicit LibraryChoicePage(QWidget *parent = nullptr);

signals:
    void libraryReady(Biblioteca* biblioteca);
    void goToLoginPage();

private slots:
    void onLoadFileButtonClicked();
    void onNewLibraryButtonClicked();

private:
    QPushButton* loadFileButton;
    QPushButton* newLibraryButton;
    QLabel* titleLabel;
    QLabel* descriptionLabel;
    Biblioteca* biblioteca;

    void setupUI();
};

#endif // LIBRARYCHOICEPAGE_H