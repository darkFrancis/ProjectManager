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
}

bool Parser::load(QString filename)
{
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
