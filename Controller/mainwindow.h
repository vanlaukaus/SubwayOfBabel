#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_botControlButton_clicked();
    void on_llmControlButton_clicked();
    void on_settingsButton_clicked();

private:
    Ui::MainWindow *ui;
    QProcess *botProcess;
    QProcess *llmProcess;
    QSettings *settings;

    void update_ui_state();
    void read_bot_output();
    void read_llm_output();
    void load_settings();
    void save_settings();
    QStringList get_selected_languages();
};

#endif // MAINWINDOW_H
