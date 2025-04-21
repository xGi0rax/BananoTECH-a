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
#include <QListWidgetItem>
#include <QPixmap>
#include <QPainter>

class MainPage : public QWidget {
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = nullptr);
    void onMediaSelected(QListWidgetItem *item);

private slots:
    void onMediaTypeChanged(int index);
    void onBackButtonClicked();
    void onApplyFiltersClicked(); // Slot per applicare i filtri
    void onClearFiltersClicked(); // Slot per cancellare i filtri

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
    QPushButton *applyFiltersButton; // Pulsante per applicare i filtri
    QPushButton *clearFiltersButton; // Pulsante per eliminare i filtri

    // Sezione centrale
    QLineEdit *searchBar;
    QListWidget *mediaList;

    // Sezione destra
    QPixmap originalPixmap;
    QLabel *mediaImageLabel;
    QLabel *mediaInfoLabel;
    QPushButton *borrowButton;
    QPushButton *detailsButton;
    QLabel *mediaTitleLabel;
    QLabel *mediaAuthorLabel;
    QLabel *mediaYearLabel;
    QLabel *mediaRatingLabel;
    QPushButton *editMediaButton; 

    // Layout
    QVBoxLayout *mainLayout;
    QHBoxLayout *topBarLayout;
    QVBoxLayout *filtersLayout;
    QVBoxLayout *centerLayout;
    QVBoxLayout *previewLayout;
    QHBoxLayout *contentLayout;

    QGroupBox *filtersGroupBox;
    QGroupBox *previewGroupBox;

    void setupUI(); // metodo per configurare l'interfaccia utente
    // void setupFilters(); // metodo per configurare i filtri
    void updateGenreComboBox(); // metodo per aggiornare la combobox dei generi in base al tipo di media selezionato
    // void updateMediaList(); // metodo per aggiornare la lista dei media in base ai filtri selezionati

protected:
    void resizeEvent(QResizeEvent* event) override;
    void updateImageSize();
};

#endif // MAINPAGE_H