#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringListModel>

#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList *pList = new QStringList;
    *pList << "C++" << "Python" << "Java" << "C#" << "PHP" << "JavaScript";

    QStandardItemModel *pModel = new QStandardItemModel(pList->size(), 1, this);

    for (int i = 0; i < pModel->rowCount(); ++i)
    {
        QModelIndex index = pModel->index(i,0);
        QString str = pList->at(i);
        pModel->setData( index, str, Qt::DisplayRole);
        pModel->setData( index, QIcon(":/icon/"+str), Qt::DecorationRole);
    }

    ui->listView->setModel(pModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_checkBox_clicked(bool checked)
{
    if (checked) ui->listView->setViewMode(QListView::IconMode);
    else ui->listView->setViewMode(QListView::ListMode);
}


void MainWindow::on_addPushButton_clicked()
{
    //pModel->appendRow(new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_DirHomeIcon)), "Добавьте запись"));
    QModelIndex index = ui->listView->currentIndex();
    //QModelIndex index1 = index.siblingAtRow(index.row()+1);
    ui->listView->model()->insertRow(index.row());
    ui->listView->model()->setData(index, QIcon(QApplication::style()->standardIcon(QStyle::SP_DirHomeIcon)), Qt::DecorationRole);
    ui->listView->model()->setData(index, "Добавьте запись", Qt::DisplayRole);
}


void MainWindow::on_removePushButton_clicked()
{
    QModelIndex index = ui->listView->currentIndex();
    if (index.isValid()) ui->listView->model()->removeRow(index.row());
}

