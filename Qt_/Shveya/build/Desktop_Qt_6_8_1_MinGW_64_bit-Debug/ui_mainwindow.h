/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *ordersTab;
    QVBoxLayout *ordersLayout;
    QTableView *ordersTable;
    QHBoxLayout *ordersButtonsLayout;
    QPushButton *addOrderButton;
    QPushButton *toggleEditOrdersButton;
    QPushButton *deleteOrderButton;
    QWidget *ClientsTab;
    QVBoxLayout *ClientsLayout;
    QTableView *ClientsTable;
    QHBoxLayout *ClientsButtonsLayout;
    QPushButton *addClientsButton;
    QPushButton *editClientsButton;
    QPushButton *deleteClientsButton;
    QWidget *TypeOrdersTab;
    QVBoxLayout *TypeOrdersLayout;
    QTableView *TypeOrdersTable;
    QHBoxLayout *TypeOrdersButtonsLayout;
    QPushButton *addTypeOrdersButton;
    QPushButton *editTypeOrdersButton;
    QPushButton *deleteTypeOrdersButton;
    QWidget *materialsTab;
    QVBoxLayout *materialsLayout;
    QTableView *materialsTable;
    QHBoxLayout *materialsButtonsLayout;
    QPushButton *addMaterialButton;
    QPushButton *editMaterialButton;
    QPushButton *deleteMaterialButton;
    QWidget *reportTab;
    QVBoxLayout *reportLayout;
    QLabel *reportLabel;
    QPushButton *generateReportButton;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setTabPosition(QTabWidget::TabPosition::North);
        tabWidget->setTabShape(QTabWidget::TabShape::Rounded);
        ordersTab = new QWidget();
        ordersTab->setObjectName("ordersTab");
        ordersLayout = new QVBoxLayout(ordersTab);
        ordersLayout->setObjectName("ordersLayout");
        ordersTable = new QTableView(ordersTab);
        ordersTable->setObjectName("ordersTable");
        ordersTable->setProperty("columnCount", QVariant(5));

        ordersLayout->addWidget(ordersTable);

        ordersButtonsLayout = new QHBoxLayout();
        ordersButtonsLayout->setObjectName("ordersButtonsLayout");
        addOrderButton = new QPushButton(ordersTab);
        addOrderButton->setObjectName("addOrderButton");

        ordersButtonsLayout->addWidget(addOrderButton);

        toggleEditOrdersButton = new QPushButton(ordersTab);
        toggleEditOrdersButton->setObjectName("toggleEditOrdersButton");

        ordersButtonsLayout->addWidget(toggleEditOrdersButton);

        deleteOrderButton = new QPushButton(ordersTab);
        deleteOrderButton->setObjectName("deleteOrderButton");

        ordersButtonsLayout->addWidget(deleteOrderButton);


        ordersLayout->addLayout(ordersButtonsLayout);

        tabWidget->addTab(ordersTab, QString());
        ClientsTab = new QWidget();
        ClientsTab->setObjectName("ClientsTab");
        ClientsLayout = new QVBoxLayout(ClientsTab);
        ClientsLayout->setObjectName("ClientsLayout");
        ClientsTable = new QTableView(ClientsTab);
        ClientsTable->setObjectName("ClientsTable");
        ClientsTable->setProperty("columnCount", QVariant(3));

        ClientsLayout->addWidget(ClientsTable);

        ClientsButtonsLayout = new QHBoxLayout();
        ClientsButtonsLayout->setObjectName("ClientsButtonsLayout");
        addClientsButton = new QPushButton(ClientsTab);
        addClientsButton->setObjectName("addClientsButton");

        ClientsButtonsLayout->addWidget(addClientsButton);

        editClientsButton = new QPushButton(ClientsTab);
        editClientsButton->setObjectName("editClientsButton");

        ClientsButtonsLayout->addWidget(editClientsButton);

        deleteClientsButton = new QPushButton(ClientsTab);
        deleteClientsButton->setObjectName("deleteClientsButton");

        ClientsButtonsLayout->addWidget(deleteClientsButton);


        ClientsLayout->addLayout(ClientsButtonsLayout);

        tabWidget->addTab(ClientsTab, QString());
        TypeOrdersTab = new QWidget();
        TypeOrdersTab->setObjectName("TypeOrdersTab");
        TypeOrdersLayout = new QVBoxLayout(TypeOrdersTab);
        TypeOrdersLayout->setObjectName("TypeOrdersLayout");
        TypeOrdersTable = new QTableView(TypeOrdersTab);
        TypeOrdersTable->setObjectName("TypeOrdersTable");
        TypeOrdersTable->setProperty("columnCount", QVariant(3));

        TypeOrdersLayout->addWidget(TypeOrdersTable);

        TypeOrdersButtonsLayout = new QHBoxLayout();
        TypeOrdersButtonsLayout->setObjectName("TypeOrdersButtonsLayout");
        addTypeOrdersButton = new QPushButton(TypeOrdersTab);
        addTypeOrdersButton->setObjectName("addTypeOrdersButton");

        TypeOrdersButtonsLayout->addWidget(addTypeOrdersButton);

        editTypeOrdersButton = new QPushButton(TypeOrdersTab);
        editTypeOrdersButton->setObjectName("editTypeOrdersButton");

        TypeOrdersButtonsLayout->addWidget(editTypeOrdersButton);

        deleteTypeOrdersButton = new QPushButton(TypeOrdersTab);
        deleteTypeOrdersButton->setObjectName("deleteTypeOrdersButton");

        TypeOrdersButtonsLayout->addWidget(deleteTypeOrdersButton);


        TypeOrdersLayout->addLayout(TypeOrdersButtonsLayout);

        tabWidget->addTab(TypeOrdersTab, QString());
        materialsTab = new QWidget();
        materialsTab->setObjectName("materialsTab");
        materialsLayout = new QVBoxLayout(materialsTab);
        materialsLayout->setObjectName("materialsLayout");
        materialsTable = new QTableView(materialsTab);
        materialsTable->setObjectName("materialsTable");
        materialsTable->setProperty("columnCount", QVariant(3));

        materialsLayout->addWidget(materialsTable);

        materialsButtonsLayout = new QHBoxLayout();
        materialsButtonsLayout->setObjectName("materialsButtonsLayout");
        addMaterialButton = new QPushButton(materialsTab);
        addMaterialButton->setObjectName("addMaterialButton");

        materialsButtonsLayout->addWidget(addMaterialButton);

        editMaterialButton = new QPushButton(materialsTab);
        editMaterialButton->setObjectName("editMaterialButton");

        materialsButtonsLayout->addWidget(editMaterialButton);

        deleteMaterialButton = new QPushButton(materialsTab);
        deleteMaterialButton->setObjectName("deleteMaterialButton");

        materialsButtonsLayout->addWidget(deleteMaterialButton);


        materialsLayout->addLayout(materialsButtonsLayout);

        tabWidget->addTab(materialsTab, QString());
        reportTab = new QWidget();
        reportTab->setObjectName("reportTab");
        reportLayout = new QVBoxLayout(reportTab);
        reportLayout->setObjectName("reportLayout");
        reportLabel = new QLabel(reportTab);
        reportLabel->setObjectName("reportLabel");
        reportLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        reportLayout->addWidget(reportLabel);

        generateReportButton = new QPushButton(reportTab);
        generateReportButton->setObjectName("generateReportButton");

        reportLayout->addWidget(generateReportButton);

        tabWidget->addTab(reportTab, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 18));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionExit);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\243\321\207\320\265\321\202 \320\267\320\260\320\272\320\260\320\267\320\276\320\262 \320\270 \320\274\320\260\321\202\320\265\321\200\320\270\320\260\320\273\320\276\320\262", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", nullptr));
        ordersTable->setProperty("horizontalHeaderLabels", QVariant(QStringList{
            QCoreApplication::translate("MainWindow", "ID", nullptr),
            QCoreApplication::translate("MainWindow", "\320\232\320\273\320\270\320\265\320\275\321\202", nullptr),
            QCoreApplication::translate("MainWindow", "\320\234\320\260\321\202\320\265\321\200\320\270\320\260\320\273", nullptr),
            QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276", nullptr),
            QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\202\321\203\321\201", nullptr)}));
        addOrderButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\267\320\260\320\272\320\260\320\267", nullptr));
        toggleEditOrdersButton->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\267\320\260\320\272\320\260\320\267", nullptr));
        deleteOrderButton->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\267\320\260\320\272\320\260\320\267", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(ordersTab), QCoreApplication::translate("MainWindow", "\320\227\320\260\320\272\320\260\320\267\321\213", nullptr));
        ClientsTable->setProperty("horizontalHeaderLabels", QVariant(QStringList{
            QCoreApplication::translate("MainWindow", "ID", nullptr),
            QCoreApplication::translate("MainWindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr),
            QCoreApplication::translate("MainWindow", "\320\236\321\201\321\202\320\260\321\202\320\276\320\272", nullptr)}));
        addClientsButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\272\320\273\320\270\320\265\320\275\321\202\320\260", nullptr));
        editClientsButton->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\272\320\273\320\270\320\265\320\275\321\202\320\260", nullptr));
        deleteClientsButton->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\272\320\273\320\270\320\265\320\275\321\202\320\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(ClientsTab), QCoreApplication::translate("MainWindow", "\320\232\320\273\320\270\320\265\320\275\321\202\321\213", nullptr));
        TypeOrdersTable->setProperty("horizontalHeaderLabels", QVariant(QStringList{
            QCoreApplication::translate("MainWindow", "ID", nullptr),
            QCoreApplication::translate("MainWindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr),
            QCoreApplication::translate("MainWindow", "\320\236\321\201\321\202\320\260\321\202\320\276\320\272", nullptr)}));
        addTypeOrdersButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\203\321\201\320\273\321\203\320\263\321\203", nullptr));
        editTypeOrdersButton->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \321\203\321\201\320\273\321\203\320\263\321\203", nullptr));
        deleteTypeOrdersButton->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\203\321\201\320\273\321\203\320\263\320\270", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(TypeOrdersTab), QCoreApplication::translate("MainWindow", "\320\243\321\201\320\273\321\203\320\263\320\270", nullptr));
        materialsTable->setProperty("horizontalHeaderLabels", QVariant(QStringList{
            QCoreApplication::translate("MainWindow", "ID", nullptr),
            QCoreApplication::translate("MainWindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr),
            QCoreApplication::translate("MainWindow", "\320\236\321\201\321\202\320\260\321\202\320\276\320\272", nullptr)}));
        addMaterialButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\274\320\260\321\202\320\265\321\200\320\270\320\260\320\273", nullptr));
        editMaterialButton->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\274\320\260\321\202\320\265\321\200\320\270\320\260\320\273", nullptr));
        deleteMaterialButton->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\274\320\260\321\202\320\265\321\200\320\270\320\260\320\273", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(materialsTab), QCoreApplication::translate("MainWindow", "\320\234\320\260\321\202\320\265\321\200\320\270\320\260\320\273\321\213", nullptr));
        reportLabel->setText(QCoreApplication::translate("MainWindow", "\320\227\320\264\320\265\321\201\321\214 \320\261\321\203\320\264\320\265\321\202 \320\276\321\202\320\276\320\261\321\200\320\260\320\266\320\260\321\202\321\214\321\201\321\217 \320\276\321\202\321\207\320\265\321\202 \320\276 \320\267\320\260\320\272\320\260\320\267\320\260\321\205 \320\270 \320\274\320\260\321\202\320\265\321\200\320\270\320\260\320\273\320\260\321\205.", nullptr));
        generateReportButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\263\320\265\320\275\320\265\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\276\321\202\321\207\320\265\321\202", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(reportTab), QCoreApplication::translate("MainWindow", "\320\236\321\202\321\207\320\265\321\202", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
