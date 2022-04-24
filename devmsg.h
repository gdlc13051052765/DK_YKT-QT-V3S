#ifndef DEVMSG_H
#define DEVMSG_H

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
class devMsg;
}

class devMsg : public QDialog
{
    Q_OBJECT

public:
    explicit devMsg(QWidget *parent = 0);
    ~devMsg();

private slots:
    void keyPressEvent(QKeyEvent *ev);
    void save_devMsg_to_config_db(void);

private:
    Ui::devMsg *ui;
    QLineEdit *devIdEdit;
    QLineEdit *matchCodeEdit;
    QLineEdit *versionEdit;
    QLineEdit *cardKeyCodeEdit;
    QLineEdit *calCardKeyEdit;
};

#endif // DEVMSG_H
