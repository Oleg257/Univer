/********************************************************************************
** Form generated from reading UI file 'testresultswindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTRESULTSWINDOW_H
#define UI_TESTRESULTSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TestResultsWindow
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *testTitleLabel;
    QLabel *totalQuestionsLabel;
    QLabel *correctAnswersLabel;
    QLabel *percentageLabel;
    QTableWidget *statisticsTable;
    QPushButton *finishButton;

    void setupUi(QDialog *TestResultsWindow)
    {
        if (TestResultsWindow->objectName().isEmpty())
            TestResultsWindow->setObjectName("TestResultsWindow");
        TestResultsWindow->resize(800, 600);
        TestResultsWindow->setStyleSheet(QString::fromUtf8("\n"
"    QDialog {\n"
"        background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #4e54c8, stop:1 #8f94fb);\n"
"    }\n"
"    QLabel {\n"
"        font-size: 14pt;\n"
"        color: white;\n"
"        margin: 10px;\n"
"    }\n"
"    QTableWidget {\n"
"        background-color: rgba(255, 255, 255, 0.8);\n"
"        border: 2px solid #3498db;\n"
"        border-radius: 10px;\n"
"        padding: 10px;\n"
"        font-size: 12pt;\n"
"        color: #2c3e50;\n"
"    }\n"
"    QHeaderView::section {\n"
"        background-color: #3498db;\n"
"        color: white;\n"
"        font-size: 12pt;\n"
"        padding: 5px;\n"
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
""
                        "    }\n"
"    QPushButton:pressed {\n"
"        background-color: #1abc9c;\n"
"    }\n"
"   "));
        verticalLayout = new QVBoxLayout(TestResultsWindow);
        verticalLayout->setObjectName("verticalLayout");
        testTitleLabel = new QLabel(TestResultsWindow);
        testTitleLabel->setObjectName("testTitleLabel");
        testTitleLabel->setAlignment(Qt::AlignCenter);
        testTitleLabel->setStyleSheet(QString::fromUtf8("font-size: 18pt; font-weight: bold;"));

        verticalLayout->addWidget(testTitleLabel);

        totalQuestionsLabel = new QLabel(TestResultsWindow);
        totalQuestionsLabel->setObjectName("totalQuestionsLabel");
        totalQuestionsLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(totalQuestionsLabel);

        correctAnswersLabel = new QLabel(TestResultsWindow);
        correctAnswersLabel->setObjectName("correctAnswersLabel");
        correctAnswersLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(correctAnswersLabel);

        percentageLabel = new QLabel(TestResultsWindow);
        percentageLabel->setObjectName("percentageLabel");
        percentageLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(percentageLabel);

        statisticsTable = new QTableWidget(TestResultsWindow);
        if (statisticsTable->columnCount() < 4)
            statisticsTable->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        statisticsTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        statisticsTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        statisticsTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        statisticsTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        statisticsTable->setObjectName("statisticsTable");
        statisticsTable->setColumnCount(4);
        statisticsTable->horizontalHeader()->setVisible(true);
        statisticsTable->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(statisticsTable);

        finishButton = new QPushButton(TestResultsWindow);
        finishButton->setObjectName("finishButton");

        verticalLayout->addWidget(finishButton);


        retranslateUi(TestResultsWindow);

        QMetaObject::connectSlotsByName(TestResultsWindow);
    } // setupUi

    void retranslateUi(QDialog *TestResultsWindow)
    {
        TestResultsWindow->setWindowTitle(QCoreApplication::translate("TestResultsWindow", "\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\321\213 \321\202\320\265\321\201\321\202\320\260", nullptr));
        testTitleLabel->setText(QCoreApplication::translate("TestResultsWindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \321\202\320\265\321\201\321\202\320\260", nullptr));
        totalQuestionsLabel->setText(QCoreApplication::translate("TestResultsWindow", "\320\222\321\201\320\265\320\263\320\276 \320\262\320\276\320\277\321\200\320\276\321\201\320\276\320\262: 0", nullptr));
        correctAnswersLabel->setText(QCoreApplication::translate("TestResultsWindow", "\320\237\321\200\320\260\320\262\320\270\320\273\321\214\320\275\321\213\321\205 \320\276\321\202\320\262\320\265\321\202\320\276\320\262: 0 / 0", nullptr));
        percentageLabel->setText(QCoreApplication::translate("TestResultsWindow", "\320\237\321\200\320\276\321\206\320\265\320\275\321\202 \320\277\321\200\320\260\320\262\320\270\320\273\321\214\320\275\321\213\321\205 \320\276\321\202\320\262\320\265\321\202\320\276\320\262: 0%", nullptr));
        QTableWidgetItem *___qtablewidgetitem = statisticsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("TestResultsWindow", "\320\222\320\276\320\277\321\200\320\276\321\201", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = statisticsTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("TestResultsWindow", "\320\237\321\200\320\260\320\262\320\270\320\273\321\214\320\275\321\213\320\265 \320\276\321\202\320\262\320\265\321\202\321\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = statisticsTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("TestResultsWindow", "\320\222\321\213\320\261\321\200\320\260\320\275\320\275\321\213\320\265 \320\276\321\202\320\262\320\265\321\202\321\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = statisticsTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("TestResultsWindow", "\320\241\321\202\320\260\321\202\321\203\321\201", nullptr));
        finishButton->setText(QCoreApplication::translate("TestResultsWindow", "\320\227\320\260\320\262\320\265\321\200\321\210\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TestResultsWindow: public Ui_TestResultsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTRESULTSWINDOW_H
