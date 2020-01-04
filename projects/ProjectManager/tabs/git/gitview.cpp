#include "gitview.hpp"

GitView::GitView(QWidget *parent) :
    QWidget(parent)
{
}

GitView::~GitView()
{
}

void GitView::clean()
{
    QLayoutItem* item;
    while((item = m_layout->itemAt(0)))
    {
        delete item;
    }
    m_status_list.clear();
}

void GitView::viewStatus(QString status)
{
    clean();
    QStringList ligns = status.split(QChar('\n'));
    for(QString lign : ligns)
    {
        if(lign != "")
        {
            m_status_list.append(GitStatus(this, lign));
            m_layout->addWidget(&m_status_list.last());
        }
    }
    /// TODO : add buttons
    this->setLayout(m_layout);
}
