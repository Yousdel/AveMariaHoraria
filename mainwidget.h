#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

class SettingsWidget;
class TimerWidgets;

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private slots:
    void on_whats_this_pushButton_clicked();

    void on_settings_pushButton_clicked();

    void on_begin_pushButton_clicked();

    void on_stop_pushButton_clicked();
    //----------------------user definitions------------
    void readAutomatic();

private:
    Ui::MainWidget *ui;
    bool stop{false};
    TimerWidgets *timerWidgets;
    SettingsWidget *settingsWidget;


protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // MAINWIDGET_H
