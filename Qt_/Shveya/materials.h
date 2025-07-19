#ifndef MATERIALS_H
#define MATERIALS_H

#include <QObject>
#include <QSqlTableModel>

class Materials : public QObject {
    Q_OBJECT

public:
    explicit Materials(QObject *parent = nullptr);
    QSqlTableModel *getModel(); // Получение модели для работы с таблицей материалов
    bool addMaterial(const QString &name, int stock); // Добавление нового материала
    bool updateMaterial(int materialID, const QString &name, int stock); // Обновление данных материала
    bool deleteMaterial(int materialID); // Удаление материала
    void setEditable(bool editable); // Включение/выключение режима редактирования
    bool updateStock(int materialID, int delta); // Новый метод для изменения запаса материала

private:
    QSqlTableModel *model; // Модель для работы с таблицей материалов
};

#endif // MATERIALS_H
