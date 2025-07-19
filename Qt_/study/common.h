#ifndef COMMON_H
#define COMMON_H

#include <QString>

// Определение структуры Question
struct Question {
    int id;          // ID вопроса
    QString text;    // Текст вопроса
};

// Определение структуры Answer
struct Answer {
    int id;          // ID ответа
    QString text;    // Текст ответа
    bool isCorrect;  // Флаг правильности
    bool isSelected; // Флаг выбора пользователем
};

#endif // COMMON_H
