#include "testpasswindow.h"
#include "testresultswindow.h"
#include "ui_testpasswindow.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QCheckBox>
#include <QVBoxLayout>

TestPassWindow::TestPassWindow(QSqlDatabase &database, int testId, int userId, QWidget *parent)
    : QDialog(parent), ui(new Ui::TestPassWindow), db(database), testId(testId), currentUserId(userId), currentQuestionIndex(0)
{
    ui->setupUi(this);

    // Загружаем данные теста
    loadTestData();
}

TestPassWindow::~TestPassWindow()
{
    delete ui;
}

void TestPassWindow::loadTestData()
{
    QSqlQuery query(db);
    query.prepare("SELECT title FROM tests WHERE id = :id");
    query.bindValue(":id", testId);

    if (!query.exec()) {
        qDebug() << "Database error during loading test data:" << query.lastError().text();
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить данные теста!");
        return;
    }

    if (query.next()) {
        QString testTitle = query.value(0).toString();
        ui->testTitleDisplay->setText(testTitle); // Отображаем название теста
    } else {
        QMessageBox::critical(this, "Ошибка", "Тест не найден!");
        reject(); // Закрываем окно
    }

    // Загружаем вопросы
    loadQuestions();
}

void TestPassWindow::loadQuestions()
{
    questions.clear();
    allAnswers.clear();

    QSqlQuery query(db);
    query.prepare("SELECT id, text FROM questions WHERE test_id = :test_id ORDER BY id");
    query.bindValue(":test_id", testId);

    if (!query.exec()) {
        qDebug() << "Database error during loading questions:" << query.lastError().text();
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить вопросы!");
        return;
    }

    while (query.next()) {
        int questionId = query.value(0).toInt();
        QString questionText = query.value(1).toString();
        questions.append({questionId, questionText});

        // Загружаем ответы для текущего вопроса
        QVector<Answer> answers;
        QSqlQuery answersQuery(db);
        answersQuery.prepare("SELECT id, text, is_correct FROM answers WHERE question_id = :question_id ORDER BY id");
        answersQuery.bindValue(":question_id", questionId);

        if (!answersQuery.exec()) {
            qDebug() << "Database error during loading answers:" << answersQuery.lastError().text();
            QMessageBox::critical(this, "Ошибка", "Не удалось загрузить ответы!");
            continue;
        }

        while (answersQuery.next()) {
            int answerId = answersQuery.value(0).toInt();
            QString answerText = answersQuery.value(1).toString();
            bool isCorrect = answersQuery.value(2).toBool();
            answers.append({answerId, answerText, isCorrect, false});
        }

        allAnswers.append(answers);
    }

    currentQuestionIndex = 0;
    showCurrentQuestion();
}

void TestPassWindow::showCurrentQuestion()
{
    if (currentQuestionIndex < 0 || currentQuestionIndex >= questions.size()) {
        QMessageBox::warning(this, "Ошибка", "Нет вопросов для отображения!");
        return;
    }

    const auto &question = questions[currentQuestionIndex];
    ui->questionDisplay->setText(question.text); // Отображаем текст вопроса

    // Очищаем старые ответы
    QLayoutItem *item;
    while ((item = ui->answersGridLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    // Отображаем новые ответы
    for (int i = 0; i < allAnswers[currentQuestionIndex].size(); ++i) {
        const auto &answer = allAnswers[currentQuestionIndex][i];

        QCheckBox *checkBox = new QCheckBox(answer.text, this);
        checkBox->setChecked(answer.isSelected);
        connect(checkBox, &QCheckBox::stateChanged, [this, i](int state) {
            allAnswers[currentQuestionIndex][i].isSelected = (state == Qt::Checked);
        });

        ui->answersGridLayout->addWidget(checkBox, i / 2, i % 2); // Расположение по сетке
    }

    // Обновляем счетчик вопросов
    ui->questionCounterLabel->setText(QString("Вопрос %1 из %2").arg(currentQuestionIndex + 1).arg(questions.size()));

    // Управление видимостью кнопок
    ui->backButton->setVisible(currentQuestionIndex > 0); // Скрываем кнопку "Назад" на первом вопросе
    if (currentQuestionIndex == questions.size() - 1) {
        ui->nextButton->setText("Завершить"); // Меняем текст кнопки "Вперед" на "Завершить"
    } else {
        ui->nextButton->setText("Вперед");
    }
}

void TestPassWindow::saveSelectedAnswers()
{
    for (int i = 0; i < allAnswers[currentQuestionIndex].size(); ++i) {
        auto &answer = allAnswers[currentQuestionIndex][i];
        // Здесь можно сохранить выбранные ответы в базу данных или использовать их для проверки
        qDebug() << "Answer ID:" << answer.id << ", Selected:" << answer.isSelected;
    }
}

void TestPassWindow::on_backButton_clicked()
{
    saveSelectedAnswers(); // Сохраняем выбранные ответы

    if (currentQuestionIndex > 0) {
        currentQuestionIndex--;
        showCurrentQuestion();
    } else {
        QMessageBox::warning(this, "Ошибка", "Это первый вопрос!");
    }
}

void TestPassWindow::on_nextButton_clicked()
{
    saveSelectedAnswers(); // Сохраняем выбранные ответы

    if (currentQuestionIndex < questions.size() - 1) {
        currentQuestionIndex++;
        showCurrentQuestion();
    } else {
        // Последний вопрос — завершаем тест
        double totalScore = 0; // Общий балл за тест
        double userScore = 0;  // Балл пользователя

        for (const auto &answersForQuestion : allAnswers) {
            int correctCount = 0;       // Количество правильных ответов для вопроса
            int selectedCorrect = 0;    // Количество правильно выбранных ответов
            int selectedIncorrect = 0;  // Количество неправильно выбранных ответов

            for (const auto &answer : answersForQuestion) {
                if (answer.isCorrect) {
                    correctCount++;
                    if (answer.isSelected) {
                        selectedCorrect++;
                    }
                } else if (answer.isSelected) {
                    selectedIncorrect++;
                }
            }

            // Добавляем баллы за вопрос
            if (selectedCorrect == correctCount && selectedIncorrect == 0) {
                userScore += correctCount; // Полный балл за вопрос
            } else if (selectedCorrect > 0 && selectedIncorrect == 0) {
                userScore += (static_cast<double>(selectedCorrect) / correctCount) * correctCount; // Частичный балл
            }

            totalScore += correctCount; // Добавляем максимальный балл за вопрос
        }

        // Вычисляем процент выполнения теста
        double percentage = totalScore > 0 ? (userScore / totalScore) * 100 : 0;

        // Сохраняем результаты
        saveResults(percentage); // Передаем вещественное число

        // Открываем окно с результатами
        TestResultsWindow resultsWindow("Тест завершен", static_cast<int>(totalScore), static_cast<int>(percentage),
                                        questions, allAnswers, this);

        // Подключаем сигнал завершения теста
        connect(&resultsWindow, &TestResultsWindow::testFinished, this, &TestPassWindow::testFinished);

        resultsWindow.exec();

        close(); // Закрываем окно прохождения теста
    }
}

void TestPassWindow::saveResults(double score) // Изменяем тип параметра на double
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO results (user_id, test_id, score) VALUES (:user_id, :test_id, :score)");
    query.bindValue(":user_id", currentUserId);
    query.bindValue(":test_id", testId);
    query.bindValue(":score", score); // Передаем вещественное число

    if (!query.exec()) {
        qDebug() << "Database error during saving results:" << query.lastError().text();
        QMessageBox::critical(this, "Ошибка", "Не удалось сохранить результаты!");
        return;
    }

    qDebug() << "Results saved successfully. User ID:" << currentUserId << ", Test ID:" << testId << ", Score:" << score;
}

void TestPassWindow::on_exitButton_clicked()
{
    saveSelectedAnswers(); // Сохраняем выбранные ответы

    close(); // Закрываем окно
}
