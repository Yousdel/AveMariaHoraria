#include "settingswidget.h"
#include "ui_settingswidget.h"

#include "files.h"

SettingsWidget::SettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWidget)
{
    ui->setupUi(this);
    bool automatic{0x0};
    QTime from,to;
    Files::readAutoTimes(from,to,automatic);
    ui->autoActivateCheckBox->setChecked(automatic);
    ui->from_timeEdit->setTime(from);
    ui->to_timeEdit->setTime(to);
}

SettingsWidget::~SettingsWidget()
{
    delete ui;
}

void SettingsWidget::on_savePushButton_clicked()
{
    Files::saveAutoTimes(ui->from_timeEdit->time(),
                         ui->to_timeEdit->time(),
                         ui->autoActivateCheckBox->isChecked());
    emit saved();
}
