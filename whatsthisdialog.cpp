#include "whatsthisdialog.h"
#include "ui_whatsthisdialog.h"

WhatsThisDialog::WhatsThisDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WhatsThisDialog)
{
    ui->setupUi(this);
}

WhatsThisDialog::~WhatsThisDialog()
{
    delete ui;
}

void WhatsThisDialog::on_pushButton_clicked()
{
    accept();
}
