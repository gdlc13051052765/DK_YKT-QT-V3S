/********************************************************************************
** Form generated from reading UI file 'devmsg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVMSG_H
#define UI_DEVMSG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_devMsg
{
public:

    void setupUi(QDialog *devMsg)
    {
        if (devMsg->objectName().isEmpty())
            devMsg->setObjectName(QString::fromUtf8("devMsg"));
        devMsg->resize(400, 300);

        retranslateUi(devMsg);

        QMetaObject::connectSlotsByName(devMsg);
    } // setupUi

    void retranslateUi(QDialog *devMsg)
    {
        devMsg->setWindowTitle(QApplication::translate("devMsg", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class devMsg: public Ui_devMsg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVMSG_H
