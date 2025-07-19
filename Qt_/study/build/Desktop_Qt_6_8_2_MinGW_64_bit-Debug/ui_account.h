/********************************************************************************
** Form generated from reading UI file 'account.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACCOUNT_H
#define UI_ACCOUNT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Account
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QComboBox *roleComboBox;
    QPushButton *confirmButton;
    QPushButton *backButton;

    void setupUi(QDialog *Account)
    {
        if (Account->objectName().isEmpty())
            Account->setObjectName("Account");
        Account->resize(400, 600);
        Account->setStyleSheet(QString::fromUtf8("\n"
"    QDialog {\n"
"        background-color: #2c3e50;\n"
"    }\n"
"    QLabel {\n"
"        color: #ecf0f1;\n"
"        font-size: 14pt;\n"
"        font-weight: bold;\n"
"    }\n"
"    QLineEdit {\n"
"        background-color: #ecf0f1;\n"
"        color: #2c3e50;\n"
"        font-size: 12pt;\n"
"        padding: 5px;\n"
"        border-radius: 5px;\n"
"    }\n"
"    QComboBox {\n"
"        background-color: #ecf0f1;\n"
"        color: #2c3e50;\n"
"        font-size: 12pt;\n"
"        padding: 5px;\n"
"        border-radius: 5px;\n"
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
        verticalLayoutWidget = new QWidget(Account);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(50, 50, 300, 500));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        titleLabel = new QLabel(verticalLayoutWidget);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        usernameEdit = new QLineEdit(verticalLayoutWidget);
        usernameEdit->setObjectName("usernameEdit");

        verticalLayout->addWidget(usernameEdit);

        passwordEdit = new QLineEdit(verticalLayoutWidget);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(passwordEdit);

        roleComboBox = new QComboBox(verticalLayoutWidget);
        roleComboBox->addItem(QString());
        roleComboBox->addItem(QString());
        roleComboBox->setObjectName("roleComboBox");
        roleComboBox->setEditable(false);

        verticalLayout->addWidget(roleComboBox);

        confirmButton = new QPushButton(verticalLayoutWidget);
        confirmButton->setObjectName("confirmButton");

        verticalLayout->addWidget(confirmButton);

        backButton = new QPushButton(verticalLayoutWidget);
        backButton->setObjectName("backButton");

        verticalLayout->addWidget(backButton);


        retranslateUi(Account);

        QMetaObject::connectSlotsByName(Account);
    } // setupUi

    void retranslateUi(QDialog *Account)
    {
        Account->setWindowTitle(QCoreApplication::translate("Account", "\320\220\320\272\320\272\320\260\321\203\320\275\321\202", nullptr));
        titleLabel->setText(QCoreApplication::translate("Account", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\264\320\260\320\275\320\275\321\213\320\265 \320\260\320\272\320\272\320\260\321\203\320\275\321\202\320\260", nullptr));
        usernameEdit->setPlaceholderText(QCoreApplication::translate("Account", "\320\230\320\274\321\217 \320\260\320\272\320\272\320\260\321\203\320\275\321\202\320\260", nullptr));
        passwordEdit->setPlaceholderText(QCoreApplication::translate("Account", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        roleComboBox->setItemText(0, QCoreApplication::translate("Account", "\320\243\321\207\320\265\320\275\320\270\320\272", nullptr));
        roleComboBox->setItemText(1, QCoreApplication::translate("Account", "\320\237\321\200\320\265\320\277\320\276\320\264\320\260\320\262\320\260\321\202\320\265\320\273\321\214", nullptr));

        confirmButton->setText(QCoreApplication::translate("Account", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\264\320\270\321\202\321\214", nullptr));
        backButton->setText(QCoreApplication::translate("Account", "\320\235\320\260\320\267\320\260\320\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Account: public Ui_Account {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACCOUNT_H
