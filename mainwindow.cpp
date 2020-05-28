#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logic.h"
#include <QFileDialog>

#define ERROR "ERROR"

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

void MainWindow::on_selectButton_clicked()
{
    string filepath = QFileDialog::getOpenFileName().toStdString();
    if (checkFilepath(filepath) != ERROR)
        getStringMatrix(readCSV(filepath));
    else
        errorMessage();
}

void MainWindow::on_loadButton_clicked()
{
    string region = ui->regionLineEdit->text().toStdString();
    int year = ui->yearLineEdit->text().toInt();
    vector<vector<string>> regionMatrix = getRegionMatrix(region, year);
    if (!regionMatrix.empty())
    {
        ui->tableWidget->setRowCount(regionMatrix.size());
        fillTable(regionMatrix);
    }
    else
        errorMessage();
}


void MainWindow::on_calcButton_clicked()
{
    if (ui->columnNumberLineEdit->text().isEmpty())
        errorMessage();
    else
    {
        int column = ui->columnNumberLineEdit->text().toInt();
        if (column > 0 && column <= 7 && column != 2)
        {
            ui->maxValueLineEdit->setText(QString::number(getMinMaxValueFromMatrix(column-1)[0]));
            ui->minValueLineEdit->setText(QString::number(getMinMaxValueFromMatrix(column-1)[1]));
            ui->medValueLineEdit->setText(QString::number(getMedianFromMatrix(column-1)));
        }
        else
        {
            errorMessage();
        }
    }
}

void MainWindow::fillTable(vector<vector<string>> regionMatrix)
{
    if (!regionMatrix.empty())
        for (int i = 0; i < regionMatrix.size(); i++)
            for (int j = 0; j < regionMatrix[i].size(); j++)
            {
                QString text = QString::fromStdString(regionMatrix[i][j]);
                QTableWidgetItem *Item = new QTableWidgetItem(text);
                Item -> setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                ui->tableWidget->setItem(i, j, Item);
            }
    else
        errorMessage();
}

void MainWindow::errorMessage()
{
    QMessageBox msgBox;
    msgBox.setText("Ошибка!");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setInformativeText("Попробуйте еще раз");
    msgBox.exec();
}

