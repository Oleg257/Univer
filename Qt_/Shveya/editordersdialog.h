#ifndef EDITORDERSDIALOG_H
#define EDITORDERSDIALOG_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class EditOrdersDialog;
}

class EditOrdersDialog : public QDialog {
    Q_OBJECT

public:
    explicit EditOrdersDialog(QSqlTableModel *orderModel, QWidget *parent = nullptr);
    ~EditOrdersDialog();

private slots:
    void onSaveChanges();

private:
    Ui::EditOrdersDialog *ui;
    QSqlTableModel *model;
};

#endif // EDITORDERSDIALOG_H
