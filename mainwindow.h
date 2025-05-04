#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "edit.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <QMainWindow>
#include <QColor>
#include <QFile>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateDictionary(const QString &newText);
    std::map<std::string, std::string> loadWords(const std::string& filename);
    std::string findMeaning(const std::string& word, const std::map<std::string, std::string>& words);

private slots:
    void on_pushButton_edit_clicked();

    void on_pushButton_serch_clicked();

    void on_pushButton_color_clicked();

private:
    Ui::MainWindow *ui;
    Edit *editWindow;
};
#endif // MAINWINDOW_H
