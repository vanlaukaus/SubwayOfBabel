/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QLabel *headerLabel;
    QGroupBox *controlGroup;
    QHBoxLayout *horizontalLayout;
    QPushButton *botControlButton;
    QPushButton *llmControlButton;
    QPushButton *settingsButton;
    QGroupBox *languageGroup;
    QGridLayout *gridLayout;
    QCheckBox *englishCheck;
    QCheckBox *germanCheck;
    QCheckBox *frenchCheck;
    QCheckBox *japaneseCheck;
    QCheckBox *chineseCheck;
    QCheckBox *turkishCheck;
    QCheckBox *kazakhCheck;
    QCheckBox *hindiCheck;
    QCheckBox *vietnameseCheck;
    QGroupBox *logGroup;
    QVBoxLayout *verticalLayout_3;
    QTextEdit *logView;
    QLineEdit *statusField;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1058, 1000);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setObjectName("verticalLayout");
        headerLabel = new QLabel(centralWidget);
        headerLabel->setObjectName("headerLabel");
        headerLabel->setMaximumSize(QSize(16777215, 100));
        QFont font;
        font.setFamilies({QString::fromUtf8("Courier New")});
        font.setPointSize(32);
        font.setBold(true);
        headerLabel->setFont(font);
        headerLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(headerLabel);

        controlGroup = new QGroupBox(centralWidget);
        controlGroup->setObjectName("controlGroup");
        horizontalLayout = new QHBoxLayout(controlGroup);
        horizontalLayout->setObjectName("horizontalLayout");
        botControlButton = new QPushButton(controlGroup);
        botControlButton->setObjectName("botControlButton");
        botControlButton->setMinimumSize(QSize(0, 60));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        botControlButton->setFont(font1);

        horizontalLayout->addWidget(botControlButton);

        llmControlButton = new QPushButton(controlGroup);
        llmControlButton->setObjectName("llmControlButton");
        llmControlButton->setMinimumSize(QSize(0, 60));
        llmControlButton->setFont(font1);

        horizontalLayout->addWidget(llmControlButton);

        settingsButton = new QPushButton(controlGroup);
        settingsButton->setObjectName("settingsButton");
        settingsButton->setMinimumSize(QSize(0, 60));
        settingsButton->setFont(font1);

        horizontalLayout->addWidget(settingsButton);


        verticalLayout->addWidget(controlGroup);

        languageGroup = new QGroupBox(centralWidget);
        languageGroup->setObjectName("languageGroup");
        gridLayout = new QGridLayout(languageGroup);
        gridLayout->setObjectName("gridLayout");
        englishCheck = new QCheckBox(languageGroup);
        englishCheck->setObjectName("englishCheck");

        gridLayout->addWidget(englishCheck, 0, 0, 1, 1);

        germanCheck = new QCheckBox(languageGroup);
        germanCheck->setObjectName("germanCheck");

        gridLayout->addWidget(germanCheck, 0, 1, 1, 1);

        frenchCheck = new QCheckBox(languageGroup);
        frenchCheck->setObjectName("frenchCheck");

        gridLayout->addWidget(frenchCheck, 0, 2, 1, 1);

        japaneseCheck = new QCheckBox(languageGroup);
        japaneseCheck->setObjectName("japaneseCheck");

        gridLayout->addWidget(japaneseCheck, 1, 0, 1, 1);

        chineseCheck = new QCheckBox(languageGroup);
        chineseCheck->setObjectName("chineseCheck");

        gridLayout->addWidget(chineseCheck, 1, 1, 1, 1);

        turkishCheck = new QCheckBox(languageGroup);
        turkishCheck->setObjectName("turkishCheck");

        gridLayout->addWidget(turkishCheck, 1, 2, 1, 1);

        kazakhCheck = new QCheckBox(languageGroup);
        kazakhCheck->setObjectName("kazakhCheck");

        gridLayout->addWidget(kazakhCheck, 2, 0, 1, 1);

        hindiCheck = new QCheckBox(languageGroup);
        hindiCheck->setObjectName("hindiCheck");

        gridLayout->addWidget(hindiCheck, 2, 1, 1, 1);

        vietnameseCheck = new QCheckBox(languageGroup);
        vietnameseCheck->setObjectName("vietnameseCheck");

        gridLayout->addWidget(vietnameseCheck, 2, 2, 1, 1);


        verticalLayout->addWidget(languageGroup);

        logGroup = new QGroupBox(centralWidget);
        logGroup->setObjectName("logGroup");
        verticalLayout_3 = new QVBoxLayout(logGroup);
        verticalLayout_3->setObjectName("verticalLayout_3");
        logView = new QTextEdit(logGroup);
        logView->setObjectName("logView");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(logView->sizePolicy().hasHeightForWidth());
        logView->setSizePolicy(sizePolicy);
        logView->setMinimumSize(QSize(0, 500));
        logView->setMaximumSize(QSize(16777215, 500));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Consolas")});
        font2.setPointSize(10);
        logView->setFont(font2);
        logView->setStyleSheet(QString::fromUtf8("QTextEdit {\n"
"            background-color: #1E1E1E;\n"
"            color: #FFFFFF;\n"
"            border: 1px solid #3E3E3E;\n"
"            border-radius: 4px;\n"
"            padding: 5px;\n"
"          }"));
        logView->setReadOnly(true);

        verticalLayout_3->addWidget(logView);


        verticalLayout->addWidget(logGroup);

        statusField = new QLineEdit(centralWidget);
        statusField->setObjectName("statusField");
        statusField->setMaximumSize(QSize(16777215, 50));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Courier New")});
        font3.setPointSize(12);
        font3.setItalic(true);
        statusField->setFont(font3);
        statusField->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"         background-color: #F0F0F0;\n"
"         border: 2px solid #CCCCCC;\n"
"         border-radius: 4px;\n"
"         padding: 5px;\n"
"       }"));
        statusField->setReadOnly(true);

        verticalLayout->addWidget(statusField);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Subway of Babel Controller", nullptr));
        headerLabel->setText(QCoreApplication::translate("MainWindow", "== Subway of Babel Controller v1.0 ==", nullptr));
        botControlButton->setText(QCoreApplication::translate("MainWindow", "Start Bot", nullptr));
        llmControlButton->setText(QCoreApplication::translate("MainWindow", "Start LLM", nullptr));
        settingsButton->setText(QCoreApplication::translate("MainWindow", "Save Config", nullptr));
        languageGroup->setTitle(QCoreApplication::translate("MainWindow", "Active Languages", nullptr));
        englishCheck->setText(QCoreApplication::translate("MainWindow", "English", nullptr));
        germanCheck->setText(QCoreApplication::translate("MainWindow", "German", nullptr));
        frenchCheck->setText(QCoreApplication::translate("MainWindow", "French", nullptr));
        japaneseCheck->setText(QCoreApplication::translate("MainWindow", "Japanese", nullptr));
        chineseCheck->setText(QCoreApplication::translate("MainWindow", "Chinese", nullptr));
        turkishCheck->setText(QCoreApplication::translate("MainWindow", "Turkish", nullptr));
        kazakhCheck->setText(QCoreApplication::translate("MainWindow", "Kazakh", nullptr));
        hindiCheck->setText(QCoreApplication::translate("MainWindow", "Hindi", nullptr));
        vietnameseCheck->setText(QCoreApplication::translate("MainWindow", "Vietnamese", nullptr));
        logGroup->setTitle(QCoreApplication::translate("MainWindow", "System Logs", nullptr));
        statusField->setPlaceholderText(QCoreApplication::translate("MainWindow", "System status will appear here...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
