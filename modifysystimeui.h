#ifndef MODIFYSYSTIMEUI_H
#define MODIFYSYSTIMEUI_H

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
#include <QTimer>
#include <QGroupBox>
#include <QGridLayout>
#include "sqlite3.h"


namespace Ui {
class modifySysTimeUi;
}

class modifySysTimeUi : public QDialog
{
    Q_OBJECT

public:
    explicit modifySysTimeUi(QWidget *parent = 0);
    ~modifySysTimeUi();

private:
    Ui::modifySysTimeUi *ui;
    QLineEdit *sysTimeEdit;
    QTimer *updateSysTimeTimer;

    bool judgeDateValidity(QString str)  ;

private slots:
    void updateSysTimeHandle();
    void keyPressEvent(QKeyEvent *ev);
};

#endif // MODIFYSYSTIMEUI_H
