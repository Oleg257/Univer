#ifndef CREATETESTDIALOG_H
#define CREATETESTDIALOG_H

#include <QDialog>

namespace Ui {
class CreateTestDialog;
}

class CreateTestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateTestDialog(QWidget *parent = nullptr);
    ~CreateTestDialog();

    QString getTestTitle() const; // Получить название теста

private slots:
    void on_createButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::CreateTestDialog *ui;
};

#endif // CREATETESTDIALOG_H
