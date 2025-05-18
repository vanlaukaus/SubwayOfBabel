#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QScrollBar>
#include <QStandardPaths>
#include <QDir>
#include <QJsonDocument>
#include <QJsonArray>
#include <QTimer>
#include <QIcon>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , botProcess(new QProcess(this))
    , llmProcess(new QProcess(this))
    , settings(new QSettings("SubwayOfBabel", "Controller", this))
{
    ui->setupUi(this);

    setWindowIcon(QIcon("C:/SubwayOfBabel/appicon.ico"));

    connect(botProcess, &QProcess::started, [this]() {
        ui->logView->setTextColor(Qt::green);
        ui->logView->append("Bot process started");
        update_ui_state();
    });

    connect(botProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            [this](int exitCode, QProcess::ExitStatus exitStatus) {
                update_ui_state();
            });

    connect(botProcess, &QProcess::readyReadStandardOutput, this, &MainWindow::read_bot_output);
    connect(botProcess, &QProcess::readyReadStandardError, this, &MainWindow::read_bot_output);
    connect(llmProcess, &QProcess::readyReadStandardOutput, this, &MainWindow::read_llm_output);

    load_settings();
    update_ui_state();
}

MainWindow::~MainWindow()
{
    save_settings();
    delete ui;
}

void MainWindow::on_botControlButton_clicked()
{
    if(botProcess->state() == QProcess::Running) {
        botProcess->kill();
        QTimer::singleShot(500, this, [this]() {
            update_ui_state();
        });
    } else {
        QString pythonPath = "C:\\SubwayOfBabel\\venv\\Scripts\\python.exe";
        QString scriptPath = "C:\\SubwayOfBabel\\bot.py";

        if(botProcess->state() == QProcess::NotRunning) {
            botProcess->start(pythonPath, {scriptPath});
        }
    }
    update_ui_state();
}

void MainWindow::on_llmControlButton_clicked()
{
    if(llmProcess->state() == QProcess::Running) {
        llmProcess->kill();
    } else {
#ifdef Q_OS_WIN
        llmProcess->start("wsl", {"ollama", "serve"});
#else
        llmProcess->start("ollama", {"serve"});
#endif
    }
    update_ui_state();
}

void MainWindow::on_settingsButton_clicked()
{
    save_settings();
    QMessageBox::information(this, "Settings Saved",
                             "Language configuration saved successfully.\n"
                             "Changes will take effect shortly.");
}

void MainWindow::update_ui_state()
{
    ui->botControlButton->setText(
        botProcess->state() == QProcess::Running ? "Stop Bot" : "Start Bot");
    ui->llmControlButton->setText(
        llmProcess->state() == QProcess::Running ? "Stop LLM" : "Start LLM");

    QString status;
    if(botProcess->state() == QProcess::Running) status += "Bot: Running | ";
    if(llmProcess->state() == QProcess::Running) status += "LLM: Running";
    ui->statusField->setText(status.isEmpty() ? "Status: Idle" : "Status: " + status);
}

void MainWindow::read_bot_output()
{
    QByteArray output = botProcess->readAllStandardOutput();
    QByteArray error = botProcess->readAllStandardError();

    if(!output.isEmpty()) {
        ui->logView->setTextColor(Qt::white);
        ui->logView->append(QString::fromLocal8Bit(output));
    }

    if(!error.isEmpty()) {
        ui->logView->setTextColor(Qt::darkGreen);
        ui->logView->append(QString::fromLocal8Bit(error));
    }

    QScrollBar *sb = ui->logView->verticalScrollBar();
    sb->setValue(sb->maximum());
}

void MainWindow::read_llm_output()
{
    QByteArray output = llmProcess->readAllStandardOutput();
    if(!output.isEmpty()) {
        ui->logView->setTextColor(Qt::cyan);
        ui->logView->append("[LLM] " + QString::fromLocal8Bit(output));
    }
}

void MainWindow::load_settings() {
    QFile file("C:/SubwayOfBabel/config/languages.json");
    if(file.open(QIODevice::ReadOnly)) {
        QJsonArray langs = QJsonDocument::fromJson(file.readAll()).array();
        ui->logView->append("Loading from: " + QDir::toNativeSeparators(file.fileName()));

        QList<QCheckBox*> checkboxes = findChildren<QCheckBox*>();
        for(QCheckBox* cb : checkboxes) {
            cb->setChecked(false);
        }

        QHash<QString, QCheckBox*> langMap = {
            {"en", ui->englishCheck},
            {"de", ui->germanCheck},
            {"fr", ui->frenchCheck},
            {"ja", ui->japaneseCheck},
            {"zh", ui->chineseCheck},
            {"tr", ui->turkishCheck},
            {"kk", ui->kazakhCheck},
            {"hi", ui->hindiCheck},
            {"vi", ui->vietnameseCheck}
        };

        for(const QJsonValue &val : langs) {
            QString lang = val.toString();
            if(langMap.contains(lang)) {
                langMap[lang]->setChecked(true);
            }
        }
        file.close();
    }
}
void MainWindow::save_settings() {
    QDir configDir("C:/SubwayOfBabel/config");
    if(!configDir.exists()) {
        configDir.mkpath(".");
    }

    QFile file(configDir.filePath("languages.json"));
    if(file.open(QIODevice::WriteOnly)) {
        QJsonArray langArray;
        QStringList langs = get_selected_languages();
        for(const QString &lang : langs) {
            langArray.append(lang);
        }
        file.write(QJsonDocument(langArray).toJson());
        file.close();
        ui->logView->append("Config saved to: " + QDir::toNativeSeparators(file.fileName()));
    } else {
        ui->logView->append("Error saving config: " + file.errorString());
    }
}

QStringList MainWindow::get_selected_languages() {
    QStringList langs;
    if(ui->englishCheck->isChecked()) langs << "en";
    if(ui->germanCheck->isChecked()) langs << "de";
    if(ui->frenchCheck->isChecked()) langs << "fr";
    if(ui->japaneseCheck->isChecked()) langs << "ja";
    if(ui->chineseCheck->isChecked()) langs << "zh";
    if(ui->turkishCheck->isChecked()) langs << "tr";
    if(ui->kazakhCheck->isChecked()) langs << "kk";
    if(ui->hindiCheck->isChecked()) langs << "hi";
    if(ui->vietnameseCheck->isChecked()) langs << "vi";
    return langs;
}

