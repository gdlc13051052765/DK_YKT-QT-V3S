#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_emitBtn_clicked();
    void mainWidgetStr(QString &);

private:
    Ui::Dialog *ui;
signals:
    void getStr(QString &str);
};

#endif // DIALOG_H
