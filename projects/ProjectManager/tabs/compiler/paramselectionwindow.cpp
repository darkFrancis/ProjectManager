#include "paramselectionwindow.hpp"
#include "ui_paramselectionwindow.h"
#include "settings/settings.hpp"
#include <QMessageBox>
#include <QStandardItemModel>

ParamSelectionWindow::ParamSelectionWindow(QWidget *parent, QString param_type) :
    QMainWindow(parent),
    ui(new Ui::ParamSelectionWindow)
{
    ui->setupUi(this);
    m_kw = param_type;

    QList<CompilerOption>* option_list = nullptr;
    QStandardItemModel* model = new QStandardItemModel();
    model->setHorizontalHeaderLabels(QStringList() << "Option" << "Description");
    if(m_kw == COMPILE_OVERALL)
    {
        option_list = Settings::Instance()->overallOptions();
    }
    else if(m_kw == COMPILE_LANGUAGE_C)
    {
        option_list = Settings::Instance()->languageCOptions();
    }
    else if(m_kw == COMPILE_LANGUAGE_CXX)
    {
        option_list = Settings::Instance()->languageCxxOptions();
    }
    else
    {
        QMessageBox::warning(this,
                             "Mauvais paramètre",
                             "Erreur, impossible de trouver les options pour " + param_type);
    }

    if(option_list)
    {
        QStandardItem* item = nullptr;
        CompilerOption current_option;
        for(int i = 0; i < option_list->length(); i++)
        {
            current_option = option_list->at(i);
            item = new QStandardItem(current_option.option);
            item->setToolTip(HTML_BEGIN + current_option.tooltip + HTML_END);
            model->setItem(i, 0, item);
            item = new QStandardItem(current_option.brief);
            item->setToolTip(HTML_BEGIN + current_option.tooltip + HTML_END);
            model->setItem(i, 1, item);
        }
    }
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnToContents(0);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->selectRow(0);
}

ParamSelectionWindow::~ParamSelectionWindow()
{
    delete ui;
}

void ParamSelectionWindow::on_pushButton_close_clicked()
{
    this->close();
}

void ParamSelectionWindow::on_pushButton_ok_clicked()
{
    emit selected(m_kw, ui->tableView->model()->index(ui->tableView->currentIndex().row(), 0).data().toString());
    this->close();
}
