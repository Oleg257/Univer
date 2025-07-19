#ifndef TESTPASSWINDOW_H
#define TESTPASSWINDOW_H

#include <QDialog>
#include <QSqlDatabase>
#include <QString>
#include <QVector>
#include "common.h"

namespace Ui {
class TestPassWindow;
}

class TestPassWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TestPassWindow(QSqlDatabase &database, int testId, int userId, QWidget *parent = nullptr);
    ~TestPassWindow();

signals:
    void testFinished(double percentage); // Сигнал для передачи процента выполнения теста

private slots:
    void on_backButton_clicked();
    void on_nextButton_clicked();
    void on_exitButton_clicked();

private:
    Ui::TestPassWindow *ui;
    QSqlDatabase db;
    int testId;
    int currentUserId;
    int currentQuestionIndex;
    QVector<Question> questions;
    QVector<QVector<Answer>> allAnswers;

    void loadTestData();
    void loadQuestions();
    void showCurrentQuestion();
    void saveSelectedAnswers();
    void saveResults(double score);
};

#endif // TESTPASSWINDOW_H
