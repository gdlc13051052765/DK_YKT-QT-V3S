/********************************************************************************
** Form generated from reading UI file 'ipinformation.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IPINFORMATION_H
#define UI_IPINFORMATION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_ipInformation
{
public:

    void setupUi(QDialog *ipInformation)
    {
        if (ipInformation->objectName().isEmpty())
            ipInformation->setObjectName(QString::fromUtf8("ipInformation"));
        ipInformation->resize(400, 300);

        retranslateUi(ipInformation);

        QMetaObject::connectSlotsByName(ipInformation);
    } // setupUi

    void retranslateUi(QDialog *ipInformation)
    {
        ipInformation->setWindowTitle(QApplication::translate("ipInformation", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ipInformation: public Ui_ipInformation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IPINFORMATION_H
