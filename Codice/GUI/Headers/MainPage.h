#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QListWidget>
#include <QGroupbox>
#include <QResizeEvent>
#include <QPixmap>
#include <QSizePolicy>
#include <QCheckBox>

class MainPage : public QWidget {
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = nullptr);
    void onMediaSelected(QListWidgetItem *item);

private slots:
    void onMediaTypeChanged(int index);
    void onBackButtonClicked();

signals:
    void goToLoginPage(); // Segnale per notificare il cambio alla LoginPage

private:
    // Barra superiore
    QPushButton *backButton;
    QPushButton *addMediaButton;
    //QPushButton *editModeButton;

    // Sezione sinistra
    QComboBox *mediaTypeComboBox;
    QComboBox *genreComboBox;
    QLineEdit *minYearLineEdit;
    QLineEdit *maxYearLineEdit;
    QLineEdit *ratingLineEdit;
    QLineEdit *languageLineEdit;

    // Sezione centrale
    QLineEdit *searchBar;
    QListWidget *mediaList;

    // Sezione destra
    QLabel *mediaImageLabel;
    QLabel *mediaInfoLabel;
    QPushButton *borrowButton;
    QPushButton *detailsButton;

    QLabel *mediaTitleLabel;
    QLabel *mediaAuthorLabel;
    QLabel *mediaYearLabel;
    QLabel *mediaRatingLabel;
    QPushButton *editMediaButton; 

    void resizeEvent();
    QSize originalPixmapSize;

    // Layout
    QVBoxLayout *mainLayout;
    QHBoxLayout *topBarLayout;
    QVBoxLayout *filtersLayout;
    QVBoxLayout *previewLayout;
    QHBoxLayout *contentLayout;

    void setupUI(); // metodo per configurare l'interfaccia utente
    // void setupFilters(); // metodo per configurare i filtri
    void updateImageSize(); // metodo per aggiornare la dimensione dell'immagine in base alla dimensione del widget
    void updateGenreComboBox(); // metodo per aggiornare la combobox dei generi in base al tipo di media selezionato
    // void updateMediaList(); // metodo per aggiornare la lista dei media in base ai filtri selezionati

protected:
    void resizeEvent(QResizeEvent* event) override;
};

#endif // MAINPAGE_H