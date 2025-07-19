#ifndef TESTEDITORWINDOW_H
#define TESTEDITORWINDOW_H

#include <QDialog>
#include <QSqlDatabase>
#include <QString>
#include <QVector>
#include "common.h" // Подключаем общий файл с определениями

namespace Ui {
class TestEditorWindow;
}

class TestEditorWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TestEditorWindow(QSqlDatabase &database, int testId, QWidget *parent = nullptr);
    ~TestEditorWindow();

private slots:
    void on_addQuestionButton_clicked();
    void on_removeQuestionButton_clicked();
    void on_backButton_clicked();
    void on_nextButton_clicked();
    void on_finishButton_clicked();
    void on_exitButton_clicked();
    void on_addAnswerButton_clicked();
    void on_removeAnswerButton_clicked();

private:
    Ui::TestEditorWindow *ui;
    QSqlDatabase db;
    int testId;
    int currentQuestionIndex;
    QVector<Question> questions;
    QVector<Answer> answers;

    void loadTestData();
    void loadQuestions();
    void loadAnswers(int questionId);
    void updateQuestionCounter();
    void showCurrentQuestion();
    void showAnswers();
    void saveCurrentQuestion();
    void saveCurrentAnswers();
};

#endif // TESTEDITORWINDOW_H
