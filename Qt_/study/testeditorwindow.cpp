#include "testeditorwindow.h"
#include "ui_testeditorwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QCheckBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QWidget>

TestEditorWindow::TestEditorWindow(QSqlDatabase &database, int testId, QWidget *parent)
    : QDialog(parent), ui(new Ui::TestEditorWindow), db(database), testId(testId), currentQuestionIndex(0)
{
    ui->setupUi(this);

    // Загружаем данные теста
    loadTestData();
}

TestEditorWindow::~TestEditorWindow()
{
    delete ui;
}

void TestEditorWindow::loadTestData()
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

void TestEditorWindow::loadQuestions()
{
    questions.clear();
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
    }

    updateQuestionCounter();
    showCurrentQuestion();
}

void TestEditorWindow::updateQuestionCounter()
{
    int totalQuestions = questions.size();
    ui->questionCounterLabel->setText(QString("Вопрос %1 из %2").arg(currentQuestionIndex + 1).arg(totalQuestions));
}

void TestEditorWindow::showCurrentQuestion()
{
    if (currentQuestionIndex >= 0 && currentQuestionIndex < questions.size()) {
        const auto &question = questions[currentQuestionIndex];
        ui->questionEdit->setPlainText(question.text); // Отображаем текст вопроса
        loadAnswers(question.id); // Загружаем ответы для текущего вопроса
    } else {
        ui->questionEdit->clear(); // Очищаем текстовое поле, если вопроса нет
    }
}

void TestEditorWindow::saveCurrentQuestion()
{
    saveCurrentAnswers(); // Сохраняем ответы

    if (currentQuestionIndex < 0 || currentQuestionIndex >= questions.size()) {
        return; // Нет выбранного вопроса
    }

    const auto &question = questions[currentQuestionIndex];
    QString questionText = ui->questionEdit->toPlainText();

    QSqlQuery query(db);
    query.prepare("UPDATE questions SET text = :text WHERE id = :id");
    query.bindValue(":text", questionText);
    query.bindValue(":id", question.id);

    if (!query.exec()) {
        qDebug() << "Database error during saving question:" << query.lastError().text();
        QMessageBox::critical(this, "Ошибка", "Не удалось сохранить вопрос!");
        return;
    }

    questions[currentQuestionIndex].text = questionText;
}

void TestEditorWindow::saveCurrentAnswers()
{
    for (const auto &answer : answers) {
        QSqlQuery query(db);

        if (answer.id == 0) {
            // Если ID равен 0, это новый ответ — выполняем INSERT
            query.prepare("INSERT INTO answers (question_id, text, is_correct) VALUES (:question_id, :text, :is_correct)");
            query.bindValue(":question_id", questions[currentQuestionIndex].id);
            query.bindValue(":text", answer.text);
            query.bindValue(":is_correct", answer.isCorrect);
        } else {
            // Если ID существует, обновляем существующий ответ — выполняем UPDATE
            query.prepare("UPDATE answers SET text = :text, is_correct = :is_correct WHERE id = :id");
            query.bindValue(":text", answer.text);
            query.bindValue(":is_correct", answer.isCorrect);
            query.bindValue(":id", answer.id);
        }

        if (!query.exec()) {
            qDebug() << "Database error during saving answer:" << query.lastError().text();
            QMessageBox::critical(this, "Ошибка", "Не удалось сохранить ответ!");
            return;
        }
    }
}

void TestEditorWindow::loadAnswers(int questionId)
{
    answers.clear(); // Очищаем текущие ответы

    QSqlQuery query(db);
    query.prepare("SELECT id, text, is_correct FROM answers WHERE question_id = :question_id ORDER BY id");
    query.bindValue(":question_id", questionId);

    if (!query.exec()) {
        qDebug() << "Database error during loading answers:" << query.lastError().text();
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить ответы!");
        return;
    }

    while (query.next()) {
        int answerId = query.value(0).toInt();
        QString answerText = query.value(1).toString();
        bool isCorrect = query.value(2).toBool();
        answers.append({answerId, answerText, isCorrect});
    }

    showAnswers(); // Отображаем ответы в интерфейсе
}

void TestEditorWindow::showAnswers()
{
    QLayoutItem *item;
    while ((item = ui->answersGridLayout->takeAt(0)) != nullptr) {
        delete item->widget(); // Удаляем старые виджеты
        delete item;
    }

    for (int i = 0; i < answers.size(); ++i) {
        const auto &answer = answers[i];

        // Создаем контейнер для ответа
        QWidget *answerWidget = new QWidget(this);
        QHBoxLayout *answerLayout = new QHBoxLayout(answerWidget);

        // Чекбокс для правильности ответа
        QCheckBox *correctCheckBox = new QCheckBox(this);
        correctCheckBox->setChecked(answer.isCorrect);
        connect(correctCheckBox, &QCheckBox::stateChanged, [this, i](int state) {
            answers[i].isCorrect = (state == Qt::Checked);
        });

        // Поле для текста ответа
        QLineEdit *answerEdit = new QLineEdit(this);
        answerEdit->setText(answer.text);
        connect(answerEdit, &QLineEdit::textChanged, [this, i](const QString &text) {
            answers[i].text = text;
        });

        // Добавляем элементы в макет
        answerLayout->addWidget(correctCheckBox);
        answerLayout->addWidget(answerEdit);

        // Добавляем контейнер в сетку
        ui->answersGridLayout->addWidget(answerWidget, i / 2, i % 2); // Расположение по сетке
    }
}

void TestEditorWindow::on_addQuestionButton_clicked()
{
    // Добавляем новый вопрос в базу данных
    QSqlQuery query(db);
    query.prepare("INSERT INTO questions (test_id, text) VALUES (:test_id, :text)");
    query.bindValue(":test_id", testId);
    query.bindValue(":text", "Новый вопрос");

    if (!query.exec()) {
        qDebug() << "Database error during adding question:" << query.lastError().text();
        QMessageBox::critical(this, "Ошибка", "Не удалось добавить вопрос!");
        return;
    }

    int questionId = query.lastInsertId().toInt(); // Получаем ID нового вопроса
    questions.append({questionId, "Новый вопрос"});
    currentQuestionIndex = questions.size() - 1;
    updateQuestionCounter();
    showCurrentQuestion();
}

void TestEditorWindow::on_removeQuestionButton_clicked()
{
    if (questions.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Нет вопросов для удаления!");
        return;
    }

    // Удаляем текущий вопрос из базы данных
    int questionId = questions[currentQuestionIndex].id;
    QSqlQuery query(db);
    query.prepare("DELETE FROM questions WHERE id = :id");
    query.bindValue(":id", questionId);

    if (!query.exec()) {
        qDebug() << "Database error during removing question:" << query.lastError().text();
        QMessageBox::critical(this, "Ошибка", "Не удалось удалить вопрос!");
        return;
    }

    // Обновляем список вопросов
    questions.removeAt(currentQuestionIndex);

    // Если удалили последний вопрос, переходим к предыдущему
    if (currentQuestionIndex >= questions.size()) {
        currentQuestionIndex = questions.size() - 1;
    }

    updateQuestionCounter();
    showCurrentQuestion();
}

void TestEditorWindow::on_backButton_clicked()
{
    saveCurrentQuestion(); // Сохраняем текущий вопрос

    if (currentQuestionIndex > 0) {
        currentQuestionIndex--;
        updateQuestionCounter();
        showCurrentQuestion();
    } else {
        QMessageBox::warning(this, "Ошибка", "Это первый вопрос!");
    }
}

void TestEditorWindow::on_nextButton_clicked()
{
    saveCurrentQuestion(); // Сохраняем текущий вопрос

    if (currentQuestionIndex < questions.size() - 1) {
        currentQuestionIndex++;
        updateQuestionCounter();
        showCurrentQuestion();
    } else {
        QMessageBox::warning(this, "Ошибка", "Это последний вопрос!");
    }
}

void TestEditorWindow::on_finishButton_clicked()
{
    saveCurrentQuestion(); // Сохраняем текущий вопрос

    QMessageBox::information(this, "Информация", "Редактирование завершено.");
    accept();
}

void TestEditorWindow::on_exitButton_clicked()
{
    saveCurrentQuestion(); // Сохраняем текущий вопрос

    close(); // Закрываем окно
}

void TestEditorWindow::on_addAnswerButton_clicked()
{
    if (currentQuestionIndex < 0 || currentQuestionIndex >= questions.size()) {
        QMessageBox::warning(this, "Ошибка", "Нет выбранного вопроса!");
        return;
    }

    const auto &question = questions[currentQuestionIndex];

    // Добавляем новый ответ в базу данных
    QSqlQuery query(db);
    query.prepare("INSERT INTO answers (question_id, text, is_correct) VALUES (:question_id, :text, :is_correct)");
    query.bindValue(":question_id", question.id);
    query.bindValue(":text", "");
    query.bindValue(":is_correct", false);

    if (!query.exec()) {
        qDebug() << "Database error during adding answer:" << query.lastError().text();
        QMessageBox::critical(this, "Ошибка", "Не удалось добавить ответ!");
        return;
    }

    int answerId = query.lastInsertId().toInt(); // Получаем ID нового ответа
    answers.append({answerId, "", false});

    showAnswers(); // Обновляем интерфейс
}

void TestEditorWindow::on_removeAnswerButton_clicked()
{
    if (answers.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Нет ответов для удаления!");
        return;
    }

    // Удаляем последний ответ из базы данных
    int answerId = answers.last().id;
    QSqlQuery query(db);
    query.prepare("DELETE FROM answers WHERE id = :id");
    query.bindValue(":id", answerId);

    if (!query.exec()) {
        qDebug() << "Database error during removing answer:" << query.lastError().text();
        QMessageBox::critical(this, "Ошибка", "Не удалось удалить ответ!");
        return;
    }

    answers.removeLast(); // Удаляем ответ из списка
    showAnswers();        // Обновляем интерфейс
}
