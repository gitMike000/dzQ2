#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>

#include <QStandardItemModel>

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
       void on_checkBox_clicked(bool checked);

       void on_addPushButton_clicked();

       void on_removePushButton_clicked();

   private:
       Ui::MainWindow *ui;

//       QStringList *pList = new QStringList({"C++", "Python", "Java", "C#", "PHP", "JavaScript"});

//       QStandardItemModel *pModel = new QStandardItemModel(pList->size(), 1, this);
};
#endif // MAINWINDOW_H
