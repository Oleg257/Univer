/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QPushButton *loginButton;
    QPushButton *createAccountButton;
    QPushButton *exitButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(400, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("\n"
"    QMainWindow {\n"
"        background-color: #2c3e50;\n"
"    }\n"
"    QLabel {\n"
"        color: #ecf0f1;\n"
"        font-size: 16pt;\n"
"        font-weight: bold;\n"
"    }\n"
"    QPushButton {\n"
"        background-color: #3498db;\n"
"        color: #ecf0f1;\n"
"        font-size: 14pt;\n"
"        font-weight: bold;\n"
"        border-radius: 10px;\n"
"        padding: 10px;\n"
"        min-width: 200px;\n"
"        margin: 10px;\n"
"    }\n"
"    QPushButton:hover {\n"
"        background-color: #2980b9;\n"
"    }\n"
"    QPushButton:pressed {\n"
"        background-color: #1abc9c;\n"
"    }\n"
"   "));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        loginButton = new QPushButton(centralwidget);
        loginButton->setObjectName("loginButton");

        verticalLayout->addWidget(loginButton);

        createAccountButton = new QPushButton(centralwidget);
        createAccountButton->setObjectName("createAccountButton");

        verticalLayout->addWidget(createAccountButton);

        exitButton = new QPushButton(centralwidget);
        exitButton->setObjectName("exitButton");

        verticalLayout->addWidget(exitButton);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\264\320\260\320\272\321\202\320\276\321\200 \321\202\320\265\321\201\321\202\320\276\320\262", nullptr));
        titleLabel->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\271\320\264\320\270\321\202\320\265 \320\262 \320\260\320\272\320\272\320\260\321\203\320\275\321\202 \320\270\320\273\320\270 \321\201\320\276\320\267\320\264\320\260\320\271\321\202\320\265 \320\265\320\263\320\276", nullptr));
        loginButton->setText(QCoreApplication::translate("MainWindow", "\320\222\320\276\320\271\321\202\320\270 \320\262 \320\260\320\272\320\272\320\260\321\203\320\275\321\202", nullptr));
        createAccountButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\260\320\272\320\272\320\260\321\203\320\275\321\202", nullptr));
        exitButton->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\271\321\202\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
