#ifndef TESTRESULTSWINDOW_H
#define TESTRESULTSWINDOW_H

#include <QDialog>
#include <QString>
#include <QVector>
#include "common.h"

namespace Ui {
class TestResultsWindow;
}

class TestResultsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TestResultsWindow(const QString &testTitle, int totalQuestions, int correctAnswers,
                               const QVector<Question> &questions, const QVector<QVector<Answer>> &allAnswers, QWidget *parent = nullptr);
    ~TestResultsWindow();

signals:
    void testFinished(double percentage); // Сигнал для передачи процента выполнения теста

private slots:
    void on_finishButton_clicked(); // Обработчик нажатия на кнопку "Завершить"

private:
    Ui::TestResultsWindow *ui;

    void populateStatisticsTable(const QVector<Question> &questions, const QVector<QVector<Answer>> &allAnswers);
};

#endif // TESTRESULTSWINDOW_H
