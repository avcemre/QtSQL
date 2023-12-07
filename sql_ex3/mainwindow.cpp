
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVBoxLayout>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    database(QSqlDatabase::addDatabase("QSQLITE")),
    model(nullptr) //Initialize model to nullptr
    //ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    setupDatabase();
    createTable();

    QVBoxLayout *layout = new QVBoxLayout;
    setCentralWidget(new QWidget);
    centralWidget()->setLayout(layout);

    //Create a QTableWidget and set the column count
    QTableWidget *tableWidget  = new QTableWidget;
    //tableWidget->setColumnCount(3);
    tableWidget = new QTableWidget(14, 3, this);

    // Set the headers
    QStringList headers;
    headers << "ID" << "Name" << "Value";
    tableWidget->setHorizontalHeaderLabels(headers);

    //Add the QTableWidget to the Layout
    layout->addWidget(tableWidget);

    for(int row = 0; row < model->rowCount(); ++row)
    {
        for(int col = 0; col < model->columnCount(); ++col){
            QTableWidgetItem *item = new QTableWidgetItem(model->data(model->index(row, col)).toString());
            tableWidget->setItem(row, col, item);
        }
    }
}

MainWindow::~MainWindow()
{
    delete model;
}

void MainWindow::setupDatabase()
{
    database.setDatabaseName("example3.db");

    if(!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        qDebug() << "Connected to the database.";
    }
}

void MainWindow::createTable()
{
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS example_table (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, value INTEGER)");

    if(query.lastError().isValid())
    {
        qDebug() << "Error: Failed to create table." <<  query.lastError();
    }
    else
    {
        qDebug() << "Table created successfully";
    }

    model = new QSqlTableModel(this, database);
    model->setTable("example_table");
    model->select();

    QSqlRecord record = model->record();

    record.setValue("name", "Test");
    record.setValue("value", 2321);

    if(!model->insertRecord(-1, record))
    {
        qDebug() << "Error: Failed to add record." << model->lastError();
    }
    else
    {
        qDebug() << "Record added successfully.";
    }

    model->select();
}
