#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QCloseEvent>
#include "whatsthisdialog.h"
#include "timerwidgets.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget), stop(0x0)
{
    ui->setupUi(this);
    t = new TimerWidgets(ui->lcdNumber,
                   ui->lcdNumber_2,
                   this);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_whats_this_pushButton_clicked()
{
    WhatsThisDialog d;
    d.exec();
}

void MainWidget::closeEvent(QCloseEvent *ev)
{
    if (!stop){
        showMinimized();
        ev->ignore();
    }
    else
        t->stopEverything();
}

void MainWidget::on_settings_pushButton_clicked()
{

}

void MainWidget::on_begin_pushButton_clicked()
{
    stop=0x0;
    t->activate();
    ui->begin_pushButton->setEnabled(0x0);
}

void MainWidget::on_stop_pushButton_clicked()
{
    stop=0x1;
    t->disable();
    ui->begin_pushButton->setEnabled(0x1);
}
