#ifndef EDIT_H
#define EDIT_H

#include <QDialog>
#include <QString>
#include <QWidget>

namespace Ui {
class Edit;
}

class Edit : public QDialog
{
    Q_OBJECT

public:
    explicit Edit(QWidget *parent = nullptr);
    ~Edit();
    QString getInput();

private slots:
    void on_pushButton_edit_clicked();

signals:
    void dictionaryUpdated(const QString &newText);

private:
    Ui::Edit *ui;
};

#endif // EDIT_H
