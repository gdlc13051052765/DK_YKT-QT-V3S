/********************************************************************************
** Form generated from reading UI file 'mainconsumeinterface.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINCONSUMEINTERFACE_H
#define UI_MAINCONSUMEINTERFACE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_mainConsumeInterface
{
public:

    void setupUi(QDialog *mainConsumeInterface)
    {
        if (mainConsumeInterface->objectName().isEmpty())
            mainConsumeInterface->setObjectName(QString::fromUtf8("mainConsumeInterface"));
        mainConsumeInterface->resize(400, 300);

        retranslateUi(mainConsumeInterface);

        QMetaObject::connectSlotsByName(mainConsumeInterface);
    } // setupUi

    void retranslateUi(QDialog *mainConsumeInterface)
    {
        mainConsumeInterface->setWindowTitle(QApplication::translate("mainConsumeInterface", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class mainConsumeInterface: public Ui_mainConsumeInterface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINCONSUMEINTERFACE_H
