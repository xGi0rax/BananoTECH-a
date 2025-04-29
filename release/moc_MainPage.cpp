/****************************************************************************
** Meta object code from reading C++ file 'MainPage.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Codice/GUI/Headers/MainPage.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainPage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN8MainPageE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN8MainPageE = QtMocHelpers::stringData(
    "MainPage",
    "goToLoginPage",
    "",
    "goToAddPage",
    "goToDetailsPage",
    "Media*",
    "media",
    "onBackButtonClicked",
    "onMediaTypeChanged",
    "onApplyFiltersClicked",
    "onClearFiltersClicked",
    "onAddMediaButtonClicked",
    "onEditButtonClicked",
    "onDeleteButtonClicked"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN8MainPageE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   74,    2, 0x06,    1 /* Public */,
       3,    0,   75,    2, 0x06,    2 /* Public */,
       4,    1,   76,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       7,    0,   79,    2, 0x08,    5 /* Private */,
       8,    0,   80,    2, 0x08,    6 /* Private */,
       9,    0,   81,    2, 0x08,    7 /* Private */,
      10,    0,   82,    2, 0x08,    8 /* Private */,
      11,    0,   83,    2, 0x08,    9 /* Private */,
      12,    0,   84,    2, 0x08,   10 /* Private */,
      13,    0,   85,    2, 0x08,   11 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ZN8MainPageE.offsetsAndSizes,
    qt_meta_data_ZN8MainPageE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN8MainPageE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainPage, std::true_type>,
        // method 'goToLoginPage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'goToAddPage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'goToDetailsPage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Media *, std::false_type>,
        // method 'onBackButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onMediaTypeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onApplyFiltersClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onClearFiltersClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onAddMediaButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onEditButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onDeleteButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainPage *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->goToLoginPage(); break;
        case 1: _t->goToAddPage(); break;
        case 2: _t->goToDetailsPage((*reinterpret_cast< std::add_pointer_t<Media*>>(_a[1]))); break;
        case 3: _t->onBackButtonClicked(); break;
        case 4: _t->onMediaTypeChanged(); break;
        case 5: _t->onApplyFiltersClicked(); break;
        case 6: _t->onClearFiltersClicked(); break;
        case 7: _t->onAddMediaButtonClicked(); break;
        case 8: _t->onEditButtonClicked(); break;
        case 9: _t->onDeleteButtonClicked(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (MainPage::*)();
            if (_q_method_type _q_method = &MainPage::goToLoginPage; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (MainPage::*)();
            if (_q_method_type _q_method = &MainPage::goToAddPage; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (MainPage::*)(Media * );
            if (_q_method_type _q_method = &MainPage::goToDetailsPage; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject *MainPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN8MainPageE.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MainPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void MainPage::goToLoginPage()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MainPage::goToAddPage()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MainPage::goToDetailsPage(Media * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
