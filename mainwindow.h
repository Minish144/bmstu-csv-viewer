#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMessageBox>
#include <string>
#include <vector>

QT_BEGIN_NAMESPACE

namespace Ui { class MainWindow; }

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void on_selectButton_clicked();

    void on_loadButton_clicked();

    void on_calcButton_clicked();

    void fillTable(std::vector<std::vector<std::string>> regionMatrix);

    void errorMessage();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
