/********************************************************************************
** Form generated from reading UI file 'orderform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORDERFORM_H
#define UI_ORDERFORM_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_OrderForm
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelClient;
    QComboBox *comboBoxClient;
    QLabel *labelService;
    QComboBox *comboBoxService;
    QLabel *labelQuantity;
    QSpinBox *spinBoxQuantity;
    QLabel *labelStatus;
    QComboBox *comboBoxStatus;
    QLabel *labelDate;
    QDateEdit *dateEdit;
    QHBoxLayout *horizontalLayoutButtons;
    QPushButton *buttonSave;
    QPushButton *buttonCancel;

    void setupUi(QDialog *OrderForm)
    {
        if (OrderForm->objectName().isEmpty())
            OrderForm->setObjectName("OrderForm");
        OrderForm->resize(400, 350);
        verticalLayout = new QVBoxLayout(OrderForm);
        verticalLayout->setObjectName("verticalLayout");
        labelClient = new QLabel(OrderForm);
        labelClient->setObjectName("labelClient");

        verticalLayout->addWidget(labelClient);

        comboBoxClient = new QComboBox(OrderForm);
        comboBoxClient->setObjectName("comboBoxClient");

        verticalLayout->addWidget(comboBoxClient);

        labelService = new QLabel(OrderForm);
        labelService->setObjectName("labelService");

        verticalLayout->addWidget(labelService);

        comboBoxService = new QComboBox(OrderForm);
        comboBoxService->setObjectName("comboBoxService");

        verticalLayout->addWidget(comboBoxService);

        labelQuantity = new QLabel(OrderForm);
        labelQuantity->setObjectName("labelQuantity");

        verticalLayout->addWidget(labelQuantity);

        spinBoxQuantity = new QSpinBox(OrderForm);
        spinBoxQuantity->setObjectName("spinBoxQuantity");
        spinBoxQuantity->setMinimum(1);

        verticalLayout->addWidget(spinBoxQuantity);

        labelStatus = new QLabel(OrderForm);
        labelStatus->setObjectName("labelStatus");

        verticalLayout->addWidget(labelStatus);

        comboBoxStatus = new QComboBox(OrderForm);
        comboBoxStatus->addItem(QString());
        comboBoxStatus->addItem(QString());
        comboBoxStatus->addItem(QString());
        comboBoxStatus->setObjectName("comboBoxStatus");

        verticalLayout->addWidget(comboBoxStatus);

        labelDate = new QLabel(OrderForm);
        labelDate->setObjectName("labelDate");

        verticalLayout->addWidget(labelDate);

        dateEdit = new QDateEdit(OrderForm);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setCalendarPopup(true);
        dateEdit->setDate(QDate(2023, 10, 1));

        verticalLayout->addWidget(dateEdit);

        horizontalLayoutButtons = new QHBoxLayout();
        horizontalLayoutButtons->setObjectName("horizontalLayoutButtons");
        buttonSave = new QPushButton(OrderForm);
        buttonSave->setObjectName("buttonSave");

        horizontalLayoutButtons->addWidget(buttonSave);

        buttonCancel = new QPushButton(OrderForm);
        buttonCancel->setObjectName("buttonCancel");

        horizontalLayoutButtons->addWidget(buttonCancel);


        verticalLayout->addLayout(horizontalLayoutButtons);


        retranslateUi(OrderForm);

        QMetaObject::connectSlotsByName(OrderForm);
    } // setupUi

    void retranslateUi(QDialog *OrderForm)
    {
        OrderForm->setWindowTitle(QCoreApplication::translate("OrderForm", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214/\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\267\320\260\320\272\320\260\320\267", nullptr));
        labelClient->setText(QCoreApplication::translate("OrderForm", "\320\232\320\273\320\270\320\265\320\275\321\202:", nullptr));
        labelService->setText(QCoreApplication::translate("OrderForm", "\320\243\321\201\320\273\321\203\320\263\320\260:", nullptr));
        labelQuantity->setText(QCoreApplication::translate("OrderForm", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276:", nullptr));
        labelStatus->setText(QCoreApplication::translate("OrderForm", "\320\241\321\202\320\260\321\202\321\203\321\201:", nullptr));
        comboBoxStatus->setItemText(0, QCoreApplication::translate("OrderForm", "\320\222 \320\276\320\266\320\270\320\264\320\260\320\275\320\270\320\270", nullptr));
        comboBoxStatus->setItemText(1, QCoreApplication::translate("OrderForm", "\320\222 \320\277\321\200\320\276\321\206\320\265\321\201\321\201\320\265", nullptr));
        comboBoxStatus->setItemText(2, QCoreApplication::translate("OrderForm", "\320\222\321\213\320\277\320\276\320\273\320\275\320\265\320\275\320\276", nullptr));

        labelDate->setText(QCoreApplication::translate("OrderForm", "\320\224\320\260\321\202\320\260:", nullptr));
        buttonSave->setText(QCoreApplication::translate("OrderForm", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        buttonCancel->setText(QCoreApplication::translate("OrderForm", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OrderForm: public Ui_OrderForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDERFORM_H
