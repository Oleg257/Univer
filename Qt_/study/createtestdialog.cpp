#include "createtestdialog.h"
#include "ui_createtestdialog.h"
#include <QMessageBox>

CreateTestDialog::CreateTestDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::CreateTestDialog)
{
    ui->setupUi(this);
}

CreateTestDialog::~CreateTestDialog()
{
    delete ui;
}

QString CreateTestDialog::getTestTitle() const
{
    return ui->testTitleEdit->text(); // Возвращаем текст из поля ввода
}

void CreateTestDialog::on_createButton_clicked()
{
    if (ui->testTitleEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите название теста!");
        return;
    }

    accept(); // Закрываем окно с результатом Accepted
}

void CreateTestDialog::on_cancelButton_clicked()
{
    reject(); // Закрываем окно с результатом Rejected
}
