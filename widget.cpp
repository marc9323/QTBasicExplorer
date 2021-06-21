#include "widget.h"
#include "ui_widget.h"
#include <QString>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // default path
    QString path = "D:/";

    // initialize dir model
    dirModel = new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
    // set path to the model
    dirModel->setRootPath(path);

    // attach the model to a view
    ui->treeView->setModel(dirModel);

    // initialize files mode;
    filesModel = new QFileSystemModel(this);
    filesModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    filesModel->setRootPath(path); // required for model to load file system info

    ui->listView->setModel(filesModel);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_treeView_clicked(const QModelIndex &index)
{

    // capture the path the user clicked on
    // set that to the root path for the view widget - ListView

    // returns QFileInfo object so we can call absoluteFilePath()
    QString path = dirModel->fileInfo(index).absoluteFilePath(); // find by referencing documentation!
    qDebug() << "User clicked on: " << path;
    QModelIndex temp = filesModel->setRootPath(path);
    // set as root index on list view model
   // ui->listView->setRootIndex(filesModel->setRootPath(path)); // returns a model index
    ui->listView->setRootIndex(temp);




}
