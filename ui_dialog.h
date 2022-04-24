/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *emitBtn;
    QLineEdit *EmitLineEdit;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *ReceiveBtn;
    QLineEdit *ReceiveLineEdit;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(586, 445);
        widget = new QWidget(Dialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(40, 110, 321, 61));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        emitBtn = new QPushButton(widget);
        emitBtn->setObjectName(QString::fromUtf8("emitBtn"));

        horizontalLayout->addWidget(emitBtn);

        EmitLineEdit = new QLineEdit(widget);
        EmitLineEdit->setObjectName(QString::fromUtf8("EmitLineEdit"));

        horizontalLayout->addWidget(EmitLineEdit);

        widget1 = new QWidget(Dialog);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(40, 180, 321, 41));
        horizontalLayout_2 = new QHBoxLayout(widget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        ReceiveBtn = new QPushButton(widget1);
        ReceiveBtn->setObjectName(QString::fromUtf8("ReceiveBtn"));

        horizontalLayout_2->addWidget(ReceiveBtn);

        ReceiveLineEdit = new QLineEdit(widget1);
        ReceiveLineEdit->setObjectName(QString::fromUtf8("ReceiveLineEdit"));

        horizontalLayout_2->addWidget(ReceiveLineEdit);

        emitBtn->raise();
        ReceiveBtn->raise();
        EmitLineEdit->raise();
        ReceiveLineEdit->raise();
        ReceiveLineEdit->raise();

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        emitBtn->setText(QApplication::translate("Dialog", "\345\217\221\345\260\204\344\277\241\345\217\267", 0, QApplication::UnicodeUTF8));
        ReceiveBtn->setText(QApplication::translate("Dialog", "\346\216\245\346\224\266\344\277\241\345\217\267", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
