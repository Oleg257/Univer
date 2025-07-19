/********************************************************************************
** Form generated from reading UI file 'testeditorwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTEDITORWINDOW_H
#define UI_TESTEDITORWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TestEditorWindow
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
    QHBoxLayout *questionCounterLayout;
    QLabel *questionCounterLabel;
    QSpacerItem *spacerItem2;
    QPushButton *addQuestionButton;
    QPushButton *removeQuestionButton;
    QVBoxLayout *questionLayout;
    QLabel *questionLabel;
    QTextEdit *questionEdit;
    QVBoxLayout *answersLayout;
    QLabel *answersLabel;
    QGridLayout *answersGridLayout;
    QHBoxLayout *answerButtonsLayout;
    QPushButton *addAnswerButton;
    QPushButton *removeAnswerButton;
    QHBoxLayout *navigationLayout;
    QPushButton *backButton;
    QPushButton *nextButton;
    QPushButton *finishButton;

    void setupUi(QDialog *TestEditorWindow)
    {
        if (TestEditorWindow->objectName().isEmpty())
            TestEditorWindow->setObjectName("TestEditorWindow");
        TestEditorWindow->resize(800, 600);
        TestEditorWindow->setStyleSheet(QString::fromUtf8("\n"
"    QDialog {\n"
"        background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #4e54c8, stop:1 #8f94fb);\n"
"    }\n"
"    QLabel {\n"
"        font-size: 14pt;\n"
"        color: white;\n"
"    }\n"
"    QLineEdit, QTextEdit {\n"
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
"    QCheckBox {\n"
"        color: white;\n"
"        font-size: 12pt;\n"
"    }\n"
"   "));
        verticalLayout = new QVBoxLayout(TestEditorWindow);
        verticalLayout->setObjectName("verticalLayout");
        topPanelLayout = new QHBoxLayout();
        topPanelLayout->setObjectName("topPanelLayout");
        exitButton = new QPushButton(TestEditorWindow);
        exitButton->setObjectName("exitButton");

        topPanelLayout->addWidget(exitButton);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        topPanelLayout->addItem(spacerItem);

        titleLabel = new QLabel(TestEditorWindow);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);

        topPanelLayout->addWidget(titleLabel);

        spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        topPanelLayout->addItem(spacerItem1);


        verticalLayout->addLayout(topPanelLayout);

        testTitleLayout = new QHBoxLayout();
        testTitleLayout->setObjectName("testTitleLayout");
        testTitleLabel = new QLabel(TestEditorWindow);
        testTitleLabel->setObjectName("testTitleLabel");

        testTitleLayout->addWidget(testTitleLabel);

        testTitleDisplay = new QLabel(TestEditorWindow);
        testTitleDisplay->setObjectName("testTitleDisplay");
        testTitleDisplay->setStyleSheet(QString::fromUtf8("font-size: 14pt; color: white;"));

        testTitleLayout->addWidget(testTitleDisplay);


        verticalLayout->addLayout(testTitleLayout);

        questionCounterLayout = new QHBoxLayout();
        questionCounterLayout->setObjectName("questionCounterLayout");
        questionCounterLabel = new QLabel(TestEditorWindow);
        questionCounterLabel->setObjectName("questionCounterLabel");
        questionCounterLabel->setStyleSheet(QString::fromUtf8("font-size: 12pt; color: white;"));

        questionCounterLayout->addWidget(questionCounterLabel);

        spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        questionCounterLayout->addItem(spacerItem2);

        addQuestionButton = new QPushButton(TestEditorWindow);
        addQuestionButton->setObjectName("addQuestionButton");

        questionCounterLayout->addWidget(addQuestionButton);

        removeQuestionButton = new QPushButton(TestEditorWindow);
        removeQuestionButton->setObjectName("removeQuestionButton");

        questionCounterLayout->addWidget(removeQuestionButton);


        verticalLayout->addLayout(questionCounterLayout);

        questionLayout = new QVBoxLayout();
        questionLayout->setObjectName("questionLayout");
        questionLabel = new QLabel(TestEditorWindow);
        questionLabel->setObjectName("questionLabel");

        questionLayout->addWidget(questionLabel);

        questionEdit = new QTextEdit(TestEditorWindow);
        questionEdit->setObjectName("questionEdit");

        questionLayout->addWidget(questionEdit);


        verticalLayout->addLayout(questionLayout);

        answersLayout = new QVBoxLayout();
        answersLayout->setObjectName("answersLayout");
        answersLabel = new QLabel(TestEditorWindow);
        answersLabel->setObjectName("answersLabel");

        answersLayout->addWidget(answersLabel);

        answersGridLayout = new QGridLayout();
        answersGridLayout->setObjectName("answersGridLayout");

        answersLayout->addLayout(answersGridLayout);

        answerButtonsLayout = new QHBoxLayout();
        answerButtonsLayout->setObjectName("answerButtonsLayout");
        addAnswerButton = new QPushButton(TestEditorWindow);
        addAnswerButton->setObjectName("addAnswerButton");

        answerButtonsLayout->addWidget(addAnswerButton);

        removeAnswerButton = new QPushButton(TestEditorWindow);
        removeAnswerButton->setObjectName("removeAnswerButton");

        answerButtonsLayout->addWidget(removeAnswerButton);


        answersLayout->addLayout(answerButtonsLayout);


        verticalLayout->addLayout(answersLayout);

        navigationLayout = new QHBoxLayout();
        navigationLayout->setObjectName("navigationLayout");
        backButton = new QPushButton(TestEditorWindow);
        backButton->setObjectName("backButton");

        navigationLayout->addWidget(backButton);

        nextButton = new QPushButton(TestEditorWindow);
        nextButton->setObjectName("nextButton");

        navigationLayout->addWidget(nextButton);

        finishButton = new QPushButton(TestEditorWindow);
        finishButton->setObjectName("finishButton");

        navigationLayout->addWidget(finishButton);


        verticalLayout->addLayout(navigationLayout);


        retranslateUi(TestEditorWindow);

        QMetaObject::connectSlotsByName(TestEditorWindow);
    } // setupUi

    void retranslateUi(QDialog *TestEditorWindow)
    {
        TestEditorWindow->setWindowTitle(QCoreApplication::translate("TestEditorWindow", "\320\240\320\265\320\264\320\260\320\272\321\202\320\276\321\200 \321\202\320\265\321\201\321\202\320\260", nullptr));
        exitButton->setText(QCoreApplication::translate("TestEditorWindow", "\320\222\321\213\320\271\321\202\320\270", nullptr));
        titleLabel->setText(QCoreApplication::translate("TestEditorWindow", "\320\240\320\265\320\264\320\260\320\272\321\202\320\276\321\200 \321\202\320\265\321\201\321\202\320\260", nullptr));
        testTitleLabel->setText(QCoreApplication::translate("TestEditorWindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \321\202\320\265\321\201\321\202\320\260:", nullptr));
        testTitleDisplay->setText(QCoreApplication::translate("TestEditorWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\272\320\260...", nullptr));
        questionCounterLabel->setText(QCoreApplication::translate("TestEditorWindow", "\320\222\320\276\320\277\321\200\320\276\321\201 1 \320\270\320\267 5", nullptr));
        addQuestionButton->setText(QCoreApplication::translate("TestEditorWindow", "+", nullptr));
        removeQuestionButton->setText(QCoreApplication::translate("TestEditorWindow", "-", nullptr));
        questionLabel->setText(QCoreApplication::translate("TestEditorWindow", "\320\222\320\276\320\277\321\200\320\276\321\201:", nullptr));
        answersLabel->setText(QCoreApplication::translate("TestEditorWindow", "\320\236\321\202\320\262\320\265\321\202\321\213:", nullptr));
        addAnswerButton->setText(QCoreApplication::translate("TestEditorWindow", "+", nullptr));
        removeAnswerButton->setText(QCoreApplication::translate("TestEditorWindow", "-", nullptr));
        backButton->setText(QCoreApplication::translate("TestEditorWindow", "\320\235\320\260\320\267\320\260\320\264", nullptr));
        nextButton->setText(QCoreApplication::translate("TestEditorWindow", "\320\222\320\277\320\265\321\200\320\265\320\264", nullptr));
        finishButton->setText(QCoreApplication::translate("TestEditorWindow", "\320\227\320\260\320\262\320\265\321\200\321\210\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TestEditorWindow: public Ui_TestEditorWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTEDITORWINDOW_H
