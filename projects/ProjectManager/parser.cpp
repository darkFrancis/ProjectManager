#include "parser.hpp"

Parser* Parser::m_instance = nullptr;

Parser* Parser::Instance()
{
    if(!m_instance)
        m_instance = new Parser();
    return m_instance;
}

Parser::Parser()
{
    m_map.clear();
    m_used = false;
}

bool Parser::load(QString filename)
{
    if(m_used)
        return false;

    m_map.clear();
    QFile file(filename);
    if(file.open(QIODevice::Text | QIODevice::ReadOnly))
    {
        QString text = file.readAll();
        QStringList ligns = text.split(QChar('\n'));
        for(QString lign : ligns)
        {
            lign = lign.simplified();
            if(lign.length() > 0
               && lign[0] != QChar('#'))
            {
                QStringList param = lign.split(QChar('='));
                if(param.length() > 1)
                {
                    m_map.insert(param[0], param[1]);
                }
            }
        }
        file.close();
        m_used = true;
        return true;
    }
    return false;
}

QString Parser::get(QString key)
{
    if(m_map.contains(key))
    {
        return m_map.value(key);
    }
    return "";
}

void Parser::close()
{
    m_used = false;
}

bool Parser::isUsed()
{
    return m_used;
}
