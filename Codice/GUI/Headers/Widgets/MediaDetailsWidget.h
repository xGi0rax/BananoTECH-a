#ifndef MEDIADETAILSWIDGET_H
#define MEDIADETAILSWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QScrollArea>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSpacerItem>
#include "../../../Modello logico/Headers/Media.h"

class MediaDetailsWidget : public QWidget {
    Q_OBJECT
    
public:
    explicit MediaDetailsWidget(QWidget *parent = nullptr);
    virtual ~MediaDetailsWidget() = default;
    
    // Metodi virtuali puri che devono essere implementati dalle sottoclassi
    virtual bool validateData() = 0;
    virtual Media* createMedia() = 0;
    
signals:
    void cancelled();
    
protected:
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
    
    QPushButton *saveButton;
    QPushButton *cancelButton;

    // Metodi per setup UI
    void setupBaseUI(const QString &detailsTitle);
    virtual void addSpecificFields() = 0; // Metodo virtuale puro
    void addStandardFields();
    void onCancelClicked();
    
    // Stili comuni
    QString getLabelStyle() const { return "QLabel { font-size: 14px; }"; }
    QString getInputStyle() const { return "QLineEdit, QSpinBox, QComboBox, QDoubleSpinBox, QDateEdit { font-size: 14px; padding: 6px; min-height: 28px; }"; }
};

#endif // MEDIADETAILSWIDGET_H