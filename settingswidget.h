#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>

namespace Ui {
class SettingsWidget;
}

class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWidget(QWidget *parent = nullptr);
    ~SettingsWidget();

private slots:
    void on_savePushButton_clicked();

    void on_startupAppCheckBox_clicked();

private:
    Ui::SettingsWidget *ui;
    void enableSaveButton();

signals:
    void saved();
};

#endif // SETTINGSWIDGET_H
