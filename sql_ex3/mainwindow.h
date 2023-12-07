#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>

#include <QSqlTableModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void createTable();
    void setupDatabase();

private:
    Ui::MainWindow *ui;
    QTableWidget* tableWidget;
    QSqlDatabase database;
    QSqlTableModel *model;
};

#endif // MAINWINDOW_H
