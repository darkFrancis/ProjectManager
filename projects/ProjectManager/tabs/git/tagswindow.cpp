#include "tagswindow.hpp"
#include "ui_tagswindow.h"

TagsWindow::TagsWindow(QWidget *parent, QStringList tags) :
    QMainWindow(parent),
    ui(new Ui::TagsWindow)
{
    ui->setupUi(this);
    ui->listWidget_tags->addItems(tags);
    ui->listWidget_tags->sortItems();
}

TagsWindow::~TagsWindow()
{
    delete ui;
}

void TagsWindow::on_pushButton_add_clicked()
{

}

void TagsWindow::on_pushButton_push_clicked()
{

}

void TagsWindow::on_pushButton_remove_clicked()
{

}
