/********************************************************************************
** Form generated from reading UI file 'queryconsumerecord.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUERYCONSUMERECORD_H
#define UI_QUERYCONSUMERECORD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_queryConsumeRecord
{
public:

    void setupUi(QDialog *queryConsumeRecord)
    {
        if (queryConsumeRecord->objectName().isEmpty())
            queryConsumeRecord->setObjectName(QString::fromUtf8("queryConsumeRecord"));
        queryConsumeRecord->resize(400, 300);

        retranslateUi(queryConsumeRecord);

        QMetaObject::connectSlotsByName(queryConsumeRecord);
    } // setupUi

    void retranslateUi(QDialog *queryConsumeRecord)
    {
        queryConsumeRecord->setWindowTitle(QApplication::translate("queryConsumeRecord", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class queryConsumeRecord: public Ui_queryConsumeRecord {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUERYCONSUMERECORD_H
