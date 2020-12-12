#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QStringListModel>
#include <QFileDialog>

#include "hashnode.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void display();

private slots:
    void on_ok_clicked();
    void on_del_clicked();
    void on_save_triggered();
    void on_load_triggered();

private:
    Ui::MainWindow *ui;
    HashMap<int, std::string> words;
    int size = 0;
    const QString default_directory = "/home/gypsyjr/laba2_2/";
};
#endif // MAINWINDOW_H
