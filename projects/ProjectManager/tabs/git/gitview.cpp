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
    for(QObject* obj : m_layout->children())
    {
        delete obj;
    }
    delete m_layout;
}

void GitView::viewStatus(QString status)
{
    clean();
    QStringList ligns = status.split(QChar('\n'));
    for(QString lign : ligns)
    {
        if(lign != "")
        {

        }
    }
}
