#ifndef QUERYDAYCONSUMEMONEY_H
#define QUERYDAYCONSUMEMONEY_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QLineEdit>
#include <QTime>
#include <QTextCodec>
#include <QFontDatabase>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QMessageBox>
#include "sqlite3.h"
#include <qinputdialog.h>

namespace Ui {
class QueryDayConsumeMoney;
}

class QueryDayConsumeMoney : public QDialog
{
    Q_OBJECT

public:
    explicit QueryDayConsumeMoney(QWidget *parent = 0);
    ~QueryDayConsumeMoney();

private:
    Ui::QueryDayConsumeMoney *ui;
    QInputDialog *input_dialog;
    QLineEdit *startDateEdit;
    QLineEdit *endDateEdit;
    QLabel  *dayConsumeMoneyLabel;
    QLineEdit *dayConsumeNumberEdit;
    QLabel  *dayConsumeNumberLabel;
    QLineEdit *dayConsumeMoneyEdit;
    void select_consume_date();
    bool judgeDateValidity(QString src)  ;

private slots:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *ev);
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // QUERYDAYCONSUMEMONEY_H
