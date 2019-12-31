#include "gitview.hpp"
#include "ui_gitview.h"

GitView::GitView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GitView)
{
    ui->setupUi(this);
}

GitView::~GitView()
{
    delete ui;
}

void GitView::clean()
{
    for(QObject* obj : m_layout->children())
    {
        delete obj;
    }
    delete m_layout;
}

void GitView::viewStatus(QString status)
{
    clean();
    m_table_widget = new QTableWidget(this);
    m_table_widget->setColumnCount(3);
    QStringList ligns = status.split(QChar('\n'));
    for(QString lign : ligns)
    {
        lign = lign.simplified();
        int idx = lign.indexOf(QChar(':'));
        if(idx != -1)
        {
            QString key_word = lign.left(idx);
            if(key_word == KEY_NEW)
            {

            }
        }
    }
}
