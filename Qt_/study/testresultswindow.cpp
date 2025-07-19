#include "testresultswindow.h"
#include "ui_testresultswindow.h"
#include <QStringList>

TestResultsWindow::TestResultsWindow(const QString &testTitle, int totalQuestions, int correctAnswers,
                                     const QVector<Question> &questions, const QVector<QVector<Answer>> &allAnswers, QWidget *parent)
    : QDialog(parent), ui(new Ui::TestResultsWindow)
{
    ui->setupUi(this);

    // Подсчет общей статистики
    int totalCorrectAnswers = 0; // Общее количество правильных ответов во всех вопросах
    int userCorrectAnswers = 0;  // Количество правильно выбранных ответов пользователем

    for (const auto &answersForQuestion : allAnswers) {
        int correctCount = 0;       // Количество правильных ответов для вопроса
        int selectedCorrect = 0;    // Количество правильно выбранных ответов

        for (const auto &answer : answersForQuestion) {
            if (answer.isCorrect) {
                correctCount++;
                totalCorrectAnswers++;
                if (answer.isSelected) {
                    selectedCorrect++;
                    userCorrectAnswers++;
                }
            }
        }
    }

    // Вычисляем процент выполнения теста
    double percentage = totalCorrectAnswers > 0 ? (static_cast<double>(userCorrectAnswers) / totalCorrectAnswers) * 100 : 0;

    // Отображаем результаты
    ui->testTitleLabel->setText(testTitle);
    ui->totalQuestionsLabel->setText(QString("Всего вопросов: %1").arg(questions.size()));
    ui->correctAnswersLabel->setText(QString("Правильных ответов: %1 / %2").arg(userCorrectAnswers).arg(totalCorrectAnswers));
    ui->percentageLabel->setText(QString("Процент правильных ответов: %1%").arg(percentage, 0, 'f', 1));

    // Заполняем таблицу статистики
    populateStatisticsTable(questions, allAnswers);

    // Подключаем кнопку "Завершить"
    connect(ui->finishButton, &QPushButton::clicked, this, &TestResultsWindow::on_finishButton_clicked);
}

TestResultsWindow::~TestResultsWindow()
{
    delete ui;
}

void TestResultsWindow::populateStatisticsTable(const QVector<Question> &questions, const QVector<QVector<Answer>> &allAnswers)
{
    ui->statisticsTable->setRowCount(questions.size());

    for (int i = 0; i < questions.size(); ++i) {
        const auto &question = questions[i];
        const auto &answersForQuestion = allAnswers[i];

        // Столбец 1: Вопрос
        QTableWidgetItem *questionItem = new QTableWidgetItem(question.text);
        ui->statisticsTable->setItem(i, 0, questionItem);

        // Столбец 2: Правильные ответы
        QStringList correctAnswers;
        int totalCorrectAnswers = 0; // Общее количество правильных ответов для вопроса

        for (const auto &answer : answersForQuestion) {
            if (answer.isCorrect) {
                correctAnswers.append(answer.text);
                totalCorrectAnswers++;
            }
        }

        QTableWidgetItem *correctAnswersItem = new QTableWidgetItem(correctAnswers.join(", "));
        ui->statisticsTable->setItem(i, 1, correctAnswersItem);

        // Столбец 3: Выбранные ответы
        QStringList selectedAnswers;
        int selectedCorrect = 0;    // Количество правильно выбранных ответов
        int selectedIncorrect = 0;  // Количество неправильно выбранных ответов

        for (const auto &answer : answersForQuestion) {
            if (answer.isSelected) {
                selectedAnswers.append(answer.text);
                if (answer.isCorrect) {
                    selectedCorrect++;
                } else {
                    selectedIncorrect++;
                }
            }
        }

        QTableWidgetItem *selectedAnswersItem = new QTableWidgetItem(selectedAnswers.join(", "));
        ui->statisticsTable->setItem(i, 2, selectedAnswersItem);

        // Столбец 4: Статус
        QString status;

        if (selectedCorrect == totalCorrectAnswers && selectedIncorrect == 0) {
            status = "Полностью правильный";
        } else if (selectedCorrect > 0 && selectedIncorrect == 0) {
            status = "Частично правильный";
        } else {
            status = "Неправильный";
        }

        QTableWidgetItem *statusItem = new QTableWidgetItem(status);
        ui->statisticsTable->setItem(i, 3, statusItem);
    }

    // Настройка ширины столбцов
    ui->statisticsTable->resizeColumnsToContents();
}

void TestResultsWindow::on_finishButton_clicked()
{
    // Извлекаем процент выполнения теста
    double percentage = ui->percentageLabel->text().split(" ")[2].remove('%').toDouble();

    // Генерируем сигнал с процентом выполнения теста
    emit testFinished(percentage);

    // Закрываем окно
    close();
}
