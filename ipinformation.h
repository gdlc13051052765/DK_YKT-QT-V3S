#ifndef IPINFORMATION_H
#define IPINFORMATION_H

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
class ipInformation;
}

class ipInformation : public QDialog
{
    Q_OBJECT

public:
    explicit ipInformation(QWidget *parent = 0);
    ~ipInformation();

private slots:
    void keyPressEvent(QKeyEvent *ev);
    bool eventFilter(QObject *watched, QEvent *event);
    void save_ipInformation_to_config_db(void);

private:
    Ui::ipInformation *ui;
    QLineEdit *localIpEdit;
    QLineEdit *remoteIpEdit;
    QLineEdit *ipPortEdit;
};

#endif // IPINFORMATION_H
