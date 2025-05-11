#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "edit.h"
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor(57, 115, 93));
    setPalette(pal);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pushButton_edit_clicked()
{
    Edit *editDialog = new Edit(this);
    connect(editDialog, &Edit::dictionaryUpdated, this, &MainWindow::updateDictionary);
    editDialog->exec();
}
void MainWindow::updateDictionary(const QString &newText)
{
    ui->label_meaning->setText(newText);
}




std::map<std::string, std::string> MainWindow::loadWords(const std::string& filename) {
    std::map<std::string, std::string> words;
    QFile file(QString::fromStdString(filename));

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Не удалось открыть файл");
        return words;
    }

    QTextStream in(&file);
    std::string currentWord, currentMeaning;

    while (!in.atEnd()) {
        QString line = in.readLine();
        std::string lineStr = line.toStdString();

        if (lineStr.empty()) {
            if (!currentWord.empty()) {
                words[currentWord] = currentMeaning;
                currentMeaning.clear();
                currentWord.clear();
            }
            continue;
        }

        if (currentWord.empty()) {
            currentWord = lineStr;
        } else {
            currentMeaning += (currentMeaning.empty() ? "" : "\n") + lineStr;
        }
    }

    if (!currentWord.empty()) {
        words[currentWord] = currentMeaning;
    }

    return words;
}
std::string MainWindow::findMeaning(const std::string& word, const std::map<std::string, std::string>& words) {
    auto it = words.find(word);
    return it != words.end() ? it->second : "Слово не найдено";
}
void MainWindow::on_pushButton_serch_clicked()
{
    auto wordsDict = loadWords(":/new/prefix1/dictionary.txt");
    std::string userInput = ui->lineEdit->text().toStdString();
    ui->label->setText(ui->lineEdit->text());
    ui->label_meaning->setText(QString::fromStdString(findMeaning(userInput, wordsDict)));
}




void MainWindow::on_pushButton_color_clicked() {
    static QColor background_color = QColor(57, 115, 93);
    if (background_color == QColor(57, 115, 93)) {
        background_color = QColor(50, 50, 50);
        ui->pushButton_color->setStyleSheet("background-color: rgb(75, 75, 75);border: none;border-radius: 5px; color: rgb(255, 153, 0)");
        ui->pushButton_edit->setStyleSheet("background-color: rgb(75, 75, 75);border: none;border-radius: 5px; color: rgb(255, 153, 0)");
        ui->pushButton_serch->setStyleSheet("background-color: rgb(75, 75, 75);border: none;border-radius: 5px; color: rgb(255, 153, 0)");
        ui->label->setStyleSheet("font: 700 40pt 'American Typewriter'; color:rgb(255, 153, 0)");
        ui->label_meaning->setStyleSheet("font: 700 30pt 'American Typewriter'; color:rgb(255, 153, 0)");
        ui->lineEdit->setStyleSheet("border-radius: 5px; background-color: rgb(75, 75, 75); border: none; font: 700 26pt 'American Typewriter'; color:rgb(255, 153, 0)");
    } else{
        background_color = QColor(57, 115, 93);
        ui->pushButton_color->setStyleSheet("background-color: rgb(255,227,81);border: none;border-radius: 5px; color: rgb(0,0,0)");
        ui->pushButton_edit->setStyleSheet("background-color: rgb(255,227,81);border: none;border-radius: 5px; color: rgb(0,0,0)");
        ui->pushButton_serch->setStyleSheet("background-color: rgb(255,227,81);border: none;border-radius: 5px; color: rgb(0,0,0)");
        ui->label->setStyleSheet("font: 700 40pt 'American Typewriter'; color: rgb(50,50,50)");
        ui->label_meaning->setStyleSheet("font: 700 30pt 'American Typewriter';color: rgb(50,50,50)");
        ui->lineEdit->setStyleSheet("border-radius: 5px; background-color: rgba(136, 160, 131, 207); border: none; font: 700 26pt 'American Typewriter'; color:rgb(50, 50, 50)");
    }
    QPalette pal = palette();
    pal.setColor(QPalette::Window, background_color);
    setPalette(pal);
}

