#ifndef CLIENTS_H
#define CLIENTS_H

#include <QObject>
#include <QSqlTableModel>

class Clients : public QObject {
    Q_OBJECT

public:
    explicit Clients(QObject *parent = nullptr);
    QSqlTableModel *getModel();

    bool addClients(const QString &name, const QString& number);
    bool updateClients(int clientsID, const QString &name, const QString& number);
    bool deleteClients(int clientsID);

    // Новый метод для включения/выключения редактирования
    void setEditable(bool editable);

private:
    QSqlTableModel *model;
};


#endif // CLIENTS_H
