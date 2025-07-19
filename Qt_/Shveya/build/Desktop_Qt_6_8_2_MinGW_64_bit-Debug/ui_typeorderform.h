/********************************************************************************
** Form generated from reading UI file 'typeorderform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TYPEORDERFORM_H
#define UI_TYPEORDERFORM_H

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

class Ui_TypeOrderForm
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelServiceName;
    QLineEdit *lineEditServiceName;
    QLabel *labelMaterial;
    QComboBox *comboBoxMaterial;
    QLabel *labelQuantity;
    QSpinBox *spinBoxQuantity;
    QHBoxLayout *horizontalLayoutButtons;
    QPushButton *buttonSave;
    QPushButton *buttonCancel;

    void setupUi(QDialog *TypeOrderForm)
    {
        if (TypeOrderForm->objectName().isEmpty())
            TypeOrderForm->setObjectName("TypeOrderForm");
        TypeOrderForm->resize(400, 250);
        verticalLayout = new QVBoxLayout(TypeOrderForm);
        verticalLayout->setObjectName("verticalLayout");
        labelServiceName = new QLabel(TypeOrderForm);
        labelServiceName->setObjectName("labelServiceName");

        verticalLayout->addWidget(labelServiceName);

        lineEditServiceName = new QLineEdit(TypeOrderForm);
        lineEditServiceName->setObjectName("lineEditServiceName");

        verticalLayout->addWidget(lineEditServiceName);

        labelMaterial = new QLabel(TypeOrderForm);
        labelMaterial->setObjectName("labelMaterial");

        verticalLayout->addWidget(labelMaterial);

        comboBoxMaterial = new QComboBox(TypeOrderForm);
        comboBoxMaterial->setObjectName("comboBoxMaterial");

        verticalLayout->addWidget(comboBoxMaterial);

        labelQuantity = new QLabel(TypeOrderForm);
        labelQuantity->setObjectName("labelQuantity");

        verticalLayout->addWidget(labelQuantity);

        spinBoxQuantity = new QSpinBox(TypeOrderForm);
        spinBoxQuantity->setObjectName("spinBoxQuantity");
        spinBoxQuantity->setMinimum(1);

        verticalLayout->addWidget(spinBoxQuantity);

        horizontalLayoutButtons = new QHBoxLayout();
        horizontalLayoutButtons->setObjectName("horizontalLayoutButtons");
        buttonSave = new QPushButton(TypeOrderForm);
        buttonSave->setObjectName("buttonSave");

        horizontalLayoutButtons->addWidget(buttonSave);

        buttonCancel = new QPushButton(TypeOrderForm);
        buttonCancel->setObjectName("buttonCancel");

        horizontalLayoutButtons->addWidget(buttonCancel);


        verticalLayout->addLayout(horizontalLayoutButtons);


        retranslateUi(TypeOrderForm);

        QMetaObject::connectSlotsByName(TypeOrderForm);
    } // setupUi

    void retranslateUi(QDialog *TypeOrderForm)
    {
        TypeOrderForm->setWindowTitle(QCoreApplication::translate("TypeOrderForm", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214/\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \321\203\321\201\320\273\321\203\320\263\321\203", nullptr));
        labelServiceName->setText(QCoreApplication::translate("TypeOrderForm", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \321\203\321\201\320\273\321\203\320\263\320\270:", nullptr));
        labelMaterial->setText(QCoreApplication::translate("TypeOrderForm", "\320\234\320\260\321\202\320\265\321\200\320\270\320\260\320\273:", nullptr));
        labelQuantity->setText(QCoreApplication::translate("TypeOrderForm", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276:", nullptr));
        buttonSave->setText(QCoreApplication::translate("TypeOrderForm", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        buttonCancel->setText(QCoreApplication::translate("TypeOrderForm", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TypeOrderForm: public Ui_TypeOrderForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TYPEORDERFORM_H
