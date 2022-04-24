#ifndef QUERYCONSUMERECORD_H
#define QUERYCONSUMERECORD_H

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

namespace Ui {
class queryConsumeRecord;
}

class queryConsumeRecord : public QDialog
{
    Q_OBJECT

public:
    explicit queryConsumeRecord(QWidget *parent = 0);
    ~queryConsumeRecord();

private:
    Ui::queryConsumeRecord *ui;
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *ev);
};

#endif // QUERYCONSUMERECORD_H
