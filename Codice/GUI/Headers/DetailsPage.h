#ifndef DETAILSPAGE_H
#define DETAILSPAGE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFrame>
#include <QScrollArea>
#include "../../Modello logico/Headers/Media.h"
#include "../../Modello logico/Headers/Film.h"
#include "../../Modello logico/Headers/Libro.h"
#include "../../Modello logico/Headers/Vinile.h"
#include "../../Modello logico/Headers/Rivista.h"
#include "../../Modello logico/Headers/GiocoDaTavolo.h"

class DetailsPage : public QWidget {
    Q_OBJECT

public:
    explicit DetailsPage(QWidget *parent = nullptr);
    void setMedia(Media* media);

signals:
    void goBackToMainPage();
    void mediaBorrowed(Media* media);
    void mediaReturned(Media* media);

private slots:
    void onBackButtonClicked();
    void onBorrowButtonClicked();
    void onReturnButtonClicked();

private:
    Media* currentMedia;
    QLabel* titleLabel;
    QLabel* authorLabel;
    QLabel* genreLabel;
    QLabel* yearLabel;
    QLabel* imageLabel;
    QLabel* availabilityLabel;
    QPushButton* backButton;
    QPushButton* borrowButton;
    QPushButton* returnButton;
    QVBoxLayout* specificDetailsLayout;

    void setupUI();
    void updateUI();
    void clearSpecificDetails();
    void setupSpecificDetails(Media* media);
    void setupFilmDetails(Film* film);
    void setupLibroDetails(Libro* libro);
    void setupVinileDetails(Vinile* vinile);
    void setupRivistaDetails(Rivista* rivista);
    void setupGiocoDetails(GiocoDaTavolo* gioco);
};

#endif // DETAILSPAGE_H