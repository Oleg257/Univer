/********************************************************************************
** Form generated from reading UI file 'menu.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENU_H
#define UI_MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Menu
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *testsTab;
    QVBoxLayout *verticalLayout_2;
    QListWidget *testsList;
    QPushButton *selectTestButton;
    QWidget *createTestsTab;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *spacerItem;
    QPushButton *createTestButton;
    QPushButton *editTestButton;
    QPushButton *deleteTestButton;
    QSpacerItem *spacerItem1;
    QPushButton *exitButton;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Menu)
    {
        if (Menu->objectName().isEmpty())
            Menu->setObjectName("Menu");
        Menu->resize(800, 600);
        Menu->setStyleSheet(QString::fromUtf8("\n"
"    QMainWindow {\n"
"        background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #4e54c8, stop:1 #8f94fb);\n"
"    }\n"
"    QTabWidget::pane {\n"
"        border: none;\n"
"    }\n"
"    QTabBar {\n"
"        background-color: #2c3e50;\n"
"        font-size: 14pt;\n"
"        color: white;\n"
"    }\n"
"    QTabBar::tab {\n"
"        background-color: #2c3e50;\n"
"        color: white;\n"
"        padding: 10px 20px; /* \320\243\320\262\320\265\320\273\320\270\321\207\320\265\320\275\320\275\321\213\320\265 \320\276\321\202\321\201\321\202\321\203\320\277\321\213 */\n"
"        border-top-left-radius: 5px;\n"
"        border-top-right-radius: 5px;\n"
"        margin-right: 5px; /* \320\236\321\202\321\201\321\202\321\203\320\277 \320\274\320\265\320\266\320\264\321\203 \320\262\320\272\320\273\320\260\320\264\320\272\320\260\320\274\320\270 */\n"
"    }\n"
"    QTabBar::tab:selected {\n"
"        background-color: #3498db;\n"
"    }\n"
"    QListWidget {\n"
"        background-c"
                        "olor: #ecf0f1;\n"
"        border: 1px solid #bdc3c7;\n"
"        border-radius: 5px;\n"
"        font-size: 12pt;\n"
"    }\n"
"    QPushButton {\n"
"        background-color: #3498db;\n"
"        color: white;\n"
"        font-size: 14pt;\n"
"        font-weight: bold;\n"
"        border: none;\n"
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
"    #exitButton {\n"
"        background-color: #e74c3c;\n"
"        color: white;\n"
"        font-size: 14pt;\n"
"        font-weight: bold;\n"
"        border: none;\n"
"        border-radius: 10px;\n"
"        padding: 10px;\n"
"        min-width: 150px;\n"
"        margin: 10px;\n"
"    }\n"
"    #exitButton:hover {\n"
"        background-color: #c0392b;\n"
"    }\n"
"    #exitButton:pressed {\n"
"        background-color: #d35400;\n"
""
                        "    }\n"
"   "));
        centralWidget = new QWidget(Menu);
        centralWidget->setObjectName("centralWidget");
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setTabPosition(QTabWidget::TabPosition::North);
        testsTab = new QWidget();
        testsTab->setObjectName("testsTab");
        verticalLayout_2 = new QVBoxLayout(testsTab);
        verticalLayout_2->setObjectName("verticalLayout_2");
        testsList = new QListWidget(testsTab);
        testsList->setObjectName("testsList");

        verticalLayout_2->addWidget(testsList);

        selectTestButton = new QPushButton(testsTab);
        selectTestButton->setObjectName("selectTestButton");

        verticalLayout_2->addWidget(selectTestButton);

        tabWidget->addTab(testsTab, QString());
        createTestsTab = new QWidget();
        createTestsTab->setObjectName("createTestsTab");
        verticalLayout_3 = new QVBoxLayout(createTestsTab);
        verticalLayout_3->setObjectName("verticalLayout_3");
        spacerItem = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(spacerItem);

        createTestButton = new QPushButton(createTestsTab);
        createTestButton->setObjectName("createTestButton");

        verticalLayout_3->addWidget(createTestButton);

        editTestButton = new QPushButton(createTestsTab);
        editTestButton->setObjectName("editTestButton");

        verticalLayout_3->addWidget(editTestButton);

        deleteTestButton = new QPushButton(createTestsTab);
        deleteTestButton->setObjectName("deleteTestButton");

        verticalLayout_3->addWidget(deleteTestButton);

        spacerItem1 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(spacerItem1);

        tabWidget->addTab(createTestsTab, QString());

        verticalLayout->addWidget(tabWidget);

        exitButton = new QPushButton(centralWidget);
        exitButton->setObjectName("exitButton");

        verticalLayout->addWidget(exitButton);

        Menu->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Menu);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        Menu->setMenuBar(menuBar);
        statusBar = new QStatusBar(Menu);
        statusBar->setObjectName("statusBar");
        Menu->setStatusBar(statusBar);

        retranslateUi(Menu);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Menu);
    } // setupUi

    void retranslateUi(QMainWindow *Menu)
    {
        Menu->setWindowTitle(QCoreApplication::translate("Menu", "\320\234\320\265\320\275\321\216", nullptr));
#if QT_CONFIG(tooltip)
        testsList->setToolTip(QCoreApplication::translate("Menu", "\320\241\320\277\320\270\321\201\320\276\320\272 \320\264\320\276\321\201\321\202\321\203\320\277\320\275\321\213\321\205 \321\202\320\265\321\201\321\202\320\276\320\262", nullptr));
#endif // QT_CONFIG(tooltip)
        selectTestButton->setText(QCoreApplication::translate("Menu", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \321\202\320\265\321\201\321\202", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(testsTab), QCoreApplication::translate("Menu", "\320\242\320\265\321\201\321\202\321\213", nullptr));
        createTestButton->setText(QCoreApplication::translate("Menu", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \321\202\320\265\321\201\321\202", nullptr));
        editTestButton->setText(QCoreApplication::translate("Menu", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \321\202\320\265\321\201\321\202", nullptr));
        deleteTestButton->setText(QCoreApplication::translate("Menu", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\202\320\265\321\201\321\202", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(createTestsTab), QCoreApplication::translate("Menu", "\320\241\320\276\320\267\320\264\320\260\320\275\320\270\320\265 \321\202\320\265\321\201\321\202\320\276\320\262", nullptr));
        exitButton->setText(QCoreApplication::translate("Menu", "\320\222\321\213\320\271\321\202\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Menu: public Ui_Menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_H
