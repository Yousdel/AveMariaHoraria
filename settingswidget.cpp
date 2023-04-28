#include "settingswidget.h"
#include "ui_settingswidget.h"

#include "files.h"
#include <QSettings>

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
    bool b{};
    Files::readStartupSelection(b);
    ui->startupAppCheckBox->setChecked(b);
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
    Files::saveStartupSelection(ui->startupAppCheckBox->isChecked());
    emit saved();
    ui->savePushButton->setText("Salvado");
    ui->savePushButton->setEnabled(false);
}

void SettingsWidget::on_startupAppCheckBox_clicked()
{
    enableSaveButton();
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);

    if (ui->startupAppCheckBox->checkState()) {
        QString value = QCoreApplication::applicationFilePath(); //get absolute path of running exe
        const QString apostroph {"\""};

        value.replace("/","\\");
        value = apostroph + value + apostroph + " --argument";

        //write value to the register
        settings.setValue("name", value);
    }
    else {
        settings.remove("name");
    }
}

void SettingsWidget::enableSaveButton()
{
    ui->savePushButton->setEnabled(true);
    ui->savePushButton->setText("Guardar");
}
