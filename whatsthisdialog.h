#ifndef WHATSTHISDIALOG_H
#define WHATSTHISDIALOG_H

#include <QDialog>

namespace Ui {
class WhatsThisDialog;
}

class WhatsThisDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WhatsThisDialog(QWidget *parent = nullptr);
    ~WhatsThisDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::WhatsThisDialog *ui;
};

#endif // WHATSTHISDIALOG_H
