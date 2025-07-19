/********************************************************************************
** Form generated from reading UI file 'TestSelectionWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTSELECTIONWINDOW_H
#define UI_TESTSELECTIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TestSelectionWindow
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QListWidget *testsList;
    QHBoxLayout *horizontalLayout;
    QPushButton *cancelButton;
    QPushButton *selectButton;

    void setupUi(QDialog *TestSelectionWindow)
    {
        if (TestSelectionWindow->objectName().isEmpty())
            TestSelectionWindow->setObjectName("TestSelectionWindow");
        TestSelectionWindow->resize(600, 400);
        TestSelectionWindow->setStyleSheet(QString::fromUtf8("\n"
"    QDialog {\n"
"        background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #4e54c8, stop:1 #8f94fb);\n"
"    }\n"
"    QLabel {\n"
"        font-size: 16pt;\n"
"        font-weight: bold;\n"
"        color: white;\n"
"    }\n"
"    QListWidget {\n"
"        background-color: #ecf0f1;\n"
"        border: 1px solid #bdc3c7;\n"
"        border-radius: 5px;\n"
"        font-size: 12pt;\n"
"    }\n"
"    QPushButton {\n"
"        background-color: #3498db;\n"
"        color: white;\n"
"        font-size: 12pt;\n"
"        font-weight: bold;\n"
"        border: none;\n"
"        border-radius: 5px;\n"
"        padding: 10px;\n"
"        min-width: 100px;\n"
"        margin: 10px;\n"
"    }\n"
"    QPushButton:hover {\n"
"        background-color: #2980b9;\n"
"    }\n"
"    QPushButton:pressed {\n"
"        background-color: #1abc9c;\n"
"    }\n"
"   "));
        verticalLayout = new QVBoxLayout(TestSelectionWindow);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(TestSelectionWindow);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        testsList = new QListWidget(TestSelectionWindow);
        testsList->setObjectName("testsList");

        verticalLayout->addWidget(testsList);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        cancelButton = new QPushButton(TestSelectionWindow);
        cancelButton->setObjectName("cancelButton");

        horizontalLayout->addWidget(cancelButton);

        selectButton = new QPushButton(TestSelectionWindow);
        selectButton->setObjectName("selectButton");

        horizontalLayout->addWidget(selectButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(TestSelectionWindow);

        QMetaObject::connectSlotsByName(TestSelectionWindow);
    } // setupUi

    void retranslateUi(QDialog *TestSelectionWindow)
    {
        TestSelectionWindow->setWindowTitle(QCoreApplication::translate("TestSelectionWindow", "\320\222\321\213\320\261\320\276\321\200 \321\202\320\265\321\201\321\202\320\260", nullptr));
        titleLabel->setText(QCoreApplication::translate("TestSelectionWindow", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \321\202\320\265\321\201\321\202:", nullptr));
#if QT_CONFIG(tooltip)
        testsList->setToolTip(QCoreApplication::translate("TestSelectionWindow", "\320\241\320\277\320\270\321\201\320\276\320\272 \320\264\320\276\321\201\321\202\321\203\320\277\320\275\321\213\321\205 \321\202\320\265\321\201\321\202\320\276\320\262", nullptr));
#endif // QT_CONFIG(tooltip)
        cancelButton->setText(QCoreApplication::translate("TestSelectionWindow", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
        selectButton->setText(QCoreApplication::translate("TestSelectionWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TestSelectionWindow: public Ui_TestSelectionWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTSELECTIONWINDOW_H
