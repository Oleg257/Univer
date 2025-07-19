/********************************************************************************
** Form generated from reading UI file 'createtestdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATETESTDIALOG_H
#define UI_CREATETESTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CreateTestDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QLineEdit *testTitleEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *cancelButton;
    QPushButton *createButton;

    void setupUi(QDialog *CreateTestDialog)
    {
        if (CreateTestDialog->objectName().isEmpty())
            CreateTestDialog->setObjectName("CreateTestDialog");
        CreateTestDialog->resize(400, 200);
        CreateTestDialog->setStyleSheet(QString::fromUtf8("\n"
"    QDialog {\n"
"        background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #4e54c8, stop:1 #8f94fb);\n"
"    }\n"
"    QLabel {\n"
"        font-size: 14pt;\n"
"        color: white;\n"
"    }\n"
"    QLineEdit {\n"
"        background-color: #ecf0f1;\n"
"        border: 1px solid #bdc3c7;\n"
"        border-radius: 5px;\n"
"        padding: 5px;\n"
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
        verticalLayout = new QVBoxLayout(CreateTestDialog);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(CreateTestDialog);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        testTitleEdit = new QLineEdit(CreateTestDialog);
        testTitleEdit->setObjectName("testTitleEdit");

        verticalLayout->addWidget(testTitleEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        cancelButton = new QPushButton(CreateTestDialog);
        cancelButton->setObjectName("cancelButton");

        horizontalLayout->addWidget(cancelButton);

        createButton = new QPushButton(CreateTestDialog);
        createButton->setObjectName("createButton");

        horizontalLayout->addWidget(createButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(CreateTestDialog);

        QMetaObject::connectSlotsByName(CreateTestDialog);
    } // setupUi

    void retranslateUi(QDialog *CreateTestDialog)
    {
        CreateTestDialog->setWindowTitle(QCoreApplication::translate("CreateTestDialog", "\320\241\320\276\320\267\320\264\320\260\320\275\320\270\320\265 \321\202\320\265\321\201\321\202\320\260", nullptr));
        titleLabel->setText(QCoreApplication::translate("CreateTestDialog", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\275\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \321\202\320\265\321\201\321\202\320\260:", nullptr));
        cancelButton->setText(QCoreApplication::translate("CreateTestDialog", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
        createButton->setText(QCoreApplication::translate("CreateTestDialog", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateTestDialog: public Ui_CreateTestDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATETESTDIALOG_H
