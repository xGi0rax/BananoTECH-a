#ifndef MEDIAWIDGET_H
#define MEDIAWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDateEdit>
#include <QScrollArea>
#include <QMessageBox>
#include "../../../Modello logico/Headers/Media.h"

class MediaWidget : public QWidget {
    Q_OBJECT

public:
    explicit MediaWidget(QWidget* parent = nullptr);
    virtual ~MediaWidget() = default;

    // Metodi virtuali da implementare nelle classi derivate
    virtual bool validateData() = 0;  // Validazione dei dati inseriti
    virtual bool applyChanges() = 0;  // Applicazione delle modifiche (per modifyPage)
    virtual Media* createMedia() = 0; // Creazione di un nuovo oggetto Media (per AddPage)
    virtual void setMedia(Media* media) = 0; // Impostazione dell'oggetto Media corrente

protected:
    Media* currentMedia;

    // Elementi UI comuni
    QScrollArea *scrollArea;
    QWidget *scrollWidget;
    QFormLayout *formLayout;

    // Campi comuni
    QLabel *titleLabel;
    QLineEdit *titleEdit;
    QLineEdit *authorEdit;
    QComboBox *genreComboBox;
    QSpinBox *yearEdit;
    QLineEdit *languageEdit;
    QDoubleSpinBox *ratingEdit;

    // Metodi per setup UI
    void setupBaseUI(const QString &title);
    void setCurrentValues();
    virtual void addSpecificFields() = 0; // Implementato nelle classi derivate
    void addStandardFields();
    void onCancelClicked();

    // Stili comuni
    QString getLabelStyle() const;
    QString getInputStyle() const;
};

#endif // MEDIAWIDGET_H