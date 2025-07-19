/********************************************************************************
** Form generated from reading UI file 'orderform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORDERFORM_H
#define UI_ORDERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_OrderForm
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelClientName;
    QLineEdit *lineEditClientName;
    QLabel *labelMaterial;
    QComboBox *comboBoxMaterial;
    QLabel *labelQuantity;
    QSpinBox *spinBoxQuantity;
    QLabel *labelStatus;
    QComboBox *comboBoxStatus;
    QHBoxLayout *horizontalLayoutButtons;
    QPushButton *buttonSave;
    QPushButton *buttonCancel;

    void setupUi(QDialog *OrderForm)
    {
        if (OrderForm->objectName().isEmpty())
            OrderForm->setObjectName("OrderForm");
        OrderForm->resize(400, 300);
        verticalLayout = new QVBoxLayout(OrderForm);
        verticalLayout->setObjectName("verticalLayout");
        labelClientName = new QLabel(OrderForm);
        labelClientName->setObjectName("labelClientName");

        verticalLayout->addWidget(labelClientName);

        lineEditClientName = new QLineEdit(OrderForm);
        lineEditClientName->setObjectName("lineEditClientName");

        verticalLayout->addWidget(lineEditClientName);

        labelMaterial = new QLabel(OrderForm);
        labelMaterial->setObjectName("labelMaterial");

        verticalLayout->addWidget(labelMaterial);

        comboBoxMaterial = new QComboBox(OrderForm);
        comboBoxMaterial->setObjectName("comboBoxMaterial");

        verticalLayout->addWidget(comboBoxMaterial);

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
        labelClientName->setText(QCoreApplication::translate("OrderForm", "\320\230\320\274\321\217 \320\272\320\273\320\270\320\265\320\275\321\202\320\260:", nullptr));
        labelMaterial->setText(QCoreApplication::translate("OrderForm", "\320\234\320\260\321\202\320\265\321\200\320\270\320\260\320\273:", nullptr));
        labelQuantity->setText(QCoreApplication::translate("OrderForm", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276:", nullptr));
        labelStatus->setText(QCoreApplication::translate("OrderForm", "\320\241\321\202\320\260\321\202\321\203\321\201:", nullptr));
        comboBoxStatus->setItemText(0, QCoreApplication::translate("OrderForm", "\320\222 \320\276\320\266\320\270\320\264\320\260\320\275\320\270\320\270", nullptr));
        comboBoxStatus->setItemText(1, QCoreApplication::translate("OrderForm", "\320\222 \320\277\321\200\320\276\321\206\320\265\321\201\321\201\320\265", nullptr));
        comboBoxStatus->setItemText(2, QCoreApplication::translate("OrderForm", "\320\222\321\213\320\277\320\276\320\273\320\275\320\265\320\275\320\276", nullptr));

        buttonSave->setText(QCoreApplication::translate("OrderForm", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        buttonCancel->setText(QCoreApplication::translate("OrderForm", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OrderForm: public Ui_OrderForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDERFORM_H
