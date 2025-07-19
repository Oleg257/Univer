/********************************************************************************
** Form generated from reading UI file 'testpasswindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTPASSWINDOW_H
#define UI_TESTPASSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TestPassWindow
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *topPanelLayout;
    QPushButton *exitButton;
    QSpacerItem *spacerItem;
    QLabel *titleLabel;
    QSpacerItem *spacerItem1;
    QHBoxLayout *testTitleLayout;
    QLabel *testTitleLabel;
    QLabel *testTitleDisplay;
    QVBoxLayout *questionLayout;
    QLabel *questionLabel;
    QLabel *questionDisplay;
    QVBoxLayout *answersLayout;
    QLabel *answersLabel;
    QGridLayout *answersGridLayout;
    QHBoxLayout *questionCounterLayout;
    QLabel *questionCounterLabel;
    QSpacerItem *spacerItem2;
    QPushButton *backButton;
    QPushButton *nextButton;

    void setupUi(QDialog *TestPassWindow)
    {
        if (TestPassWindow->objectName().isEmpty())
            TestPassWindow->setObjectName("TestPassWindow");
        TestPassWindow->resize(800, 600);
        TestPassWindow->setStyleSheet(QString::fromUtf8("\n"
"    QDialog {\n"
"        background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #4e54c8, stop:1 #8f94fb);\n"
"    }\n"
"    QLabel {\n"
"        font-size: 14pt;\n"
"        color: white;\n"
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
"    QCheckBox {\n"
"        color: white;\n"
"        font-size: 12pt;\n"
"    }\n"
"   "));
        verticalLayout = new QVBoxLayout(TestPassWindow);
        verticalLayout->setObjectName("verticalLayout");
        topPanelLayout = new QHBoxLayout();
        topPanelLayout->setObjectName("topPanelLayout");
        exitButton = new QPushButton(TestPassWindow);
        exitButton->setObjectName("exitButton");

        topPanelLayout->addWidget(exitButton);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        topPanelLayout->addItem(spacerItem);

        titleLabel = new QLabel(TestPassWindow);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);

        topPanelLayout->addWidget(titleLabel);

        spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        topPanelLayout->addItem(spacerItem1);


        verticalLayout->addLayout(topPanelLayout);

        testTitleLayout = new QHBoxLayout();
        testTitleLayout->setObjectName("testTitleLayout");
        testTitleLabel = new QLabel(TestPassWindow);
        testTitleLabel->setObjectName("testTitleLabel");

        testTitleLayout->addWidget(testTitleLabel);

        testTitleDisplay = new QLabel(TestPassWindow);
        testTitleDisplay->setObjectName("testTitleDisplay");
        testTitleDisplay->setStyleSheet(QString::fromUtf8("font-size: 14pt; color: white;"));

        testTitleLayout->addWidget(testTitleDisplay);


        verticalLayout->addLayout(testTitleLayout);

        questionLayout = new QVBoxLayout();
        questionLayout->setObjectName("questionLayout");
        questionLabel = new QLabel(TestPassWindow);
        questionLabel->setObjectName("questionLabel");
        questionLabel->setAlignment(Qt::AlignCenter);

        questionLayout->addWidget(questionLabel);

        questionDisplay = new QLabel(TestPassWindow);
        questionDisplay->setObjectName("questionDisplay");
        questionDisplay->setWordWrap(true);
        questionDisplay->setAlignment(Qt::AlignCenter);
        questionDisplay->setStyleSheet(QString::fromUtf8("\n"
"         background-color: rgba(255, 255, 255, 0.8); /* \320\237\320\276\320\273\321\203\320\277\321\200\320\276\320\267\321\200\320\260\321\207\320\275\321\213\320\271 \320\261\320\265\320\273\321\213\320\271 \321\204\320\276\320\275 */\n"
"         border: 2px solid #3498db; /* \320\223\320\276\320\273\321\203\320\261\320\260\321\217 \321\200\320\260\320\274\320\272\320\260 */\n"
"         border-radius: 10px; /* \320\227\320\260\320\272\321\200\321\203\320\263\320\273\320\265\320\275\320\275\321\213\320\265 \321\203\320\263\320\273\321\213 */\n"
"         padding: 10px; /* \320\222\320\275\321\203\321\202\321\200\320\265\320\275\320\275\320\270\320\265 \320\276\321\202\321\201\321\202\321\203\320\277\321\213 */\n"
"         font-size: 16pt; /* \320\240\320\260\320\267\320\274\320\265\321\200 \321\210\321\200\320\270\321\204\321\202\320\260 */\n"
"         color: #2c3e50; /* \320\242\320\265\320\274\320\275\320\276-\321\201\320\270\320\275\320\270\320\271 \321\202\320\265\320\272\321\201\321\202 */\n"
""
                        "        "));

        questionLayout->addWidget(questionDisplay);


        verticalLayout->addLayout(questionLayout);

        answersLayout = new QVBoxLayout();
        answersLayout->setObjectName("answersLayout");
        answersLabel = new QLabel(TestPassWindow);
        answersLabel->setObjectName("answersLabel");

        answersLayout->addWidget(answersLabel);

        answersGridLayout = new QGridLayout();
        answersGridLayout->setObjectName("answersGridLayout");

        answersLayout->addLayout(answersGridLayout);


        verticalLayout->addLayout(answersLayout);

        questionCounterLayout = new QHBoxLayout();
        questionCounterLayout->setObjectName("questionCounterLayout");
        questionCounterLabel = new QLabel(TestPassWindow);
        questionCounterLabel->setObjectName("questionCounterLabel");
        questionCounterLabel->setStyleSheet(QString::fromUtf8("font-size: 12pt; color: white;"));

        questionCounterLayout->addWidget(questionCounterLabel);

        spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        questionCounterLayout->addItem(spacerItem2);

        backButton = new QPushButton(TestPassWindow);
        backButton->setObjectName("backButton");

        questionCounterLayout->addWidget(backButton);

        nextButton = new QPushButton(TestPassWindow);
        nextButton->setObjectName("nextButton");

        questionCounterLayout->addWidget(nextButton);


        verticalLayout->addLayout(questionCounterLayout);


        retranslateUi(TestPassWindow);

        QMetaObject::connectSlotsByName(TestPassWindow);
    } // setupUi

    void retranslateUi(QDialog *TestPassWindow)
    {
        TestPassWindow->setWindowTitle(QCoreApplication::translate("TestPassWindow", "\320\237\321\200\320\276\321\205\320\276\320\266\320\264\320\265\320\275\320\270\320\265 \321\202\320\265\321\201\321\202\320\260", nullptr));
        exitButton->setText(QCoreApplication::translate("TestPassWindow", "\320\222\321\213\320\271\321\202\320\270", nullptr));
        titleLabel->setText(QCoreApplication::translate("TestPassWindow", "\320\237\321\200\320\276\321\205\320\276\320\266\320\264\320\265\320\275\320\270\320\265 \321\202\320\265\321\201\321\202\320\260", nullptr));
        testTitleLabel->setText(QCoreApplication::translate("TestPassWindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \321\202\320\265\321\201\321\202\320\260:", nullptr));
        testTitleDisplay->setText(QCoreApplication::translate("TestPassWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\272\320\260...", nullptr));
        questionLabel->setText(QCoreApplication::translate("TestPassWindow", "\320\222\320\276\320\277\321\200\320\276\321\201:", nullptr));
        questionDisplay->setText(QCoreApplication::translate("TestPassWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\272\320\260...", nullptr));
        answersLabel->setText(QCoreApplication::translate("TestPassWindow", "\320\236\321\202\320\262\320\265\321\202\321\213:", nullptr));
        questionCounterLabel->setText(QCoreApplication::translate("TestPassWindow", "\320\222\320\276\320\277\321\200\320\276\321\201 1 \320\270\320\267 5", nullptr));
        backButton->setText(QCoreApplication::translate("TestPassWindow", "\320\235\320\260\320\267\320\260\320\264", nullptr));
        nextButton->setText(QCoreApplication::translate("TestPassWindow", "\320\222\320\277\320\265\321\200\320\265\320\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TestPassWindow: public Ui_TestPassWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTPASSWINDOW_H
