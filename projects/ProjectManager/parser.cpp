#include "parser.hpp"
#include "settings/logger.hpp"

Parser* Parser::m_instance = nullptr;

Parser* Parser::Instance()
{
    if(!m_instance)
        m_instance = new Parser();
    return m_instance;
}

Parser::Parser()
{
    logger(__PRETTY_FUNCTION__);
    m_map.clear();
    m_used = false;
}

bool Parser::load(QString filename)
{
    logger(__PRETTY_FUNCTION__);
    if(m_used)
        return false;

    m_map.clear();
    QFile file(filename);
    if(file.open(QIODevice::Text | QIODevice::ReadOnly))
    {
        QString text = file.readAll();
        QStringList ligns = text.split(QChar('\n'));
        for(int i = 0; i < ligns.length(); i++)
        {
            QString lign = ligns[i];

            // Comments
            int idx = lign.indexOf(QChar('#'));
            if(idx > -1)
            {
                lign = lign.left(idx);
            }
            lign = lign.simplified();

            if(lign.length() > 0)
            {
                QStringList param = lign.split(QChar('='));
                if(param.length() > 1)
                {
                    while(param[1].right(2) == " \\")
                    {
                        param[1] = param[1].left(param[1].length()-2);
                        i++;
                        QString new_param = ligns[i];
                        idx = new_param.indexOf(QChar('#'));
                        if(idx > -1)
                        {
                            new_param = new_param.left(idx);
                        }
                        new_param = new_param.simplified();
                        param[1] += " " + new_param;
                    }
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
    logger("    get_value " + key);
    if(m_map.contains(key))
    {
        return m_map.value(key);
    }
    return "";
}

void Parser::close()
{
    logger(__PRETTY_FUNCTION__);
    m_used = false;
}

bool Parser::isUsed()
{
    return m_used;
}
