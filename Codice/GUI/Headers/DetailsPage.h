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

#include "Widgets/FilmDetailsWidget.h"
#include "Widgets/LibroDetailsWidget.h"
#include "Widgets/VinileDetailsWidget.h"
#include "Widgets/RivistaDetailsWidget.h"
#include "Widgets/GiocoDetailsWidget.h"

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
    QLabel* copiesLabel;
    QPushButton* backButton;
    QPushButton* borrowButton;
    QPushButton* returnButton;
    QVBoxLayout* specificDetailsLayout;

    QWidget* currentDetailsWidget;

    void setupUI();
    void updateUI();
    void clearSpecificDetails();
    void setupSpecificDetails(Media* media);
    QWidget* createViewWidgetForMedia(Media* media);
};

#endif // DETAILSPAGE_H