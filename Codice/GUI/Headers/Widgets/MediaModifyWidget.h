#ifndef MEDIAMODIFYWIDGET_H
#define MEDIAMODIFYWIDGET_H

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

class MediaModifyWidget : public QWidget {
    Q_OBJECT

public:
    explicit MediaModifyWidget(QWidget* parent = nullptr);
    virtual ~MediaModifyWidget() = default;
    
    // Metodi virtuali da implementare nelle classi derivate
    virtual bool validateData() = 0;
    virtual bool applyChanges() = 0;

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
    void setupBaseUI(const QString &detailsTitle);
    virtual void addSpecificFields() = 0; // Metodo virtuale puro
    void addStandardFields();

     // Stili comuni
    QString getLabelStyle() const { return "QLabel { font-size: 14px; }"; }
    QString getInputStyle() const { return "QLineEdit, QSpinBox, QComboBox, QDoubleSpinBox, QDateEdit { font-size: 14px; padding: 6px; min-height: 28px; }"; }
};

#endif // MEDIAMODIFYWIDGET_H