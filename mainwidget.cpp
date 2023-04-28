#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QCloseEvent>
#include <QTime>
#include "whatsthisdialog.h"
#include "timerwidgets.h"
#include "settingswidget.h"
#include "files.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget), stop(0x0)
{
    ui->setupUi(this);
    settingsWidget = new SettingsWidget();
    settingsWidget->hide();

    timerWidgets = new TimerWidgets(ui->lcdNumber,
                         ui->lcdNumber_2,
                         ui->label_3,
                         this);
    connect(settingsWidget, &SettingsWidget::saved, [&](){
        timerWidgets->updateFromFile();
    });
    readAutomatic();
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
        timerWidgets->stopEverything();
}

void MainWidget::on_settings_pushButton_clicked()
{
    settingsWidget->show();
}

void MainWidget::on_begin_pushButton_clicked()
{
    stop=0x0;
    timerWidgets->activate();
    ui->begin_pushButton->setEnabled(0x0);
}

void MainWidget::on_stop_pushButton_clicked()
{
    stop=0x1;
    timerWidgets->disable();
    ui->begin_pushButton->setEnabled(0x1);
}

void MainWidget::readAutomatic()
{
    bool automatic {timerWidgets->automatic()};
    ui->begin_pushButton->setEnabled(!automatic);
    if (automatic) timerWidgets->activate();
}
