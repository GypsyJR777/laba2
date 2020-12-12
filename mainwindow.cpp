#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ok_clicked(){
    std::string word = ui->new_word->text().toStdString();
    if (word != ""){
        words.insertNode(word);
        display();
    } else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("Введите слово");
        msgBox.exec();
    }
    ui->new_word->clear();
}

void MainWindow::on_del_clicked(){
    std::string word = ui->new_word->text().toStdString();
    if (word != ""){
        words.deleteNode(word);
        display();
    } else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("Введите слово");
        msgBox.exec();
    }
    ui->new_word->clear();
}

void MainWindow::on_save_triggered(){
    QString file_name = QFileDialog::getSaveFileName(0, "Сохраним в", default_directory, "*.txt");
    std::string file = file_name.toStdString();
    words.toFile(file);
}

void MainWindow::on_load_triggered(){
    QString file_name = QFileDialog::getOpenFileName(0, "Откроем", default_directory, "*.txt");
    std::string file = file_name.toStdString();
    words.intoFile(file);
    size = words.sizeofMap();
    display();
}

void MainWindow::display(){
    size++;
    std::string line = "";
    for (int i = 1; i <= size; ++i) {
        if(words.get(i) != ""){
            line += words.get(i) + "\n";
        }
    }
    QStringList list;
    list << QString::fromStdString(line);
    QStringListModel *model = new QStringListModel(this);
    model->setStringList(list);
    ui->listAll->setModel(model);
}
