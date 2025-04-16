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

class MainPage : public QWidget {
    Q_OBJECT
public:
    explicit MainPage(QWidget *parent = nullptr);
    void onMediaSelected(QListWidgetItem *item);
private:
    // Barra superiore
    QPushButton *backButton;
    QPushButton *addMediaButton;
    //QPushButton *editModeButton;

    // Sezione sinistra
    QComboBox *mediaTypeComboBox;
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
    QPushButton *editMediaButton;  // Nuovo pulsante modifica

    // Layout
    QVBoxLayout *mainLayout;
    QHBoxLayout *topBarLayout;
    QVBoxLayout *filtersLayout;
    QVBoxLayout *previewLayout;
    QHBoxLayout *contentLayout;

    void setupUI();
    void updateImageSize();

protected:
    void resizeEvent(QResizeEvent* event) override;
};

#endif // MAINPAGE_H