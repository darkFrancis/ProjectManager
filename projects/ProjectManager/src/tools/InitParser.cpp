/**
 * @file InitParser.cpp
 * @brief Definition de la classe InitParser
 * @author Dark Francis
 * @date 26/10/2020
 */
#include "InitParser.hpp"

#include <QFile>
#include <QTextStream>

#include "Logger.hpp"

InitGroup::InitGroup(const QString& title) :
    m_title(title)
{}

bool InitGroup::contains(const QString& key) const { return m_mapValues.contains(key); }

QString InitGroup::get(const QString& key) const { return m_mapValues.value(key, ""); }

QString InitGroup::title() const { return m_title; }

bool InitGroup::add(const QString& key, const QString& value)
{
    bool ret = true;
    if(contains(key))
    {
        ret = false;
    }
    m_mapValues[key] = value;
    return ret;
}

QString InitGroup::toString() const
{
    QString text = (m_title != "" ? '[' + m_title + ']' : "");
    for(const QString& key : m_mapValues.keys())
    {
        text += '\n' + key + '=' + m_mapValues.value(key);
    }
    return text;
}

InitParser::InitParser()
{}

bool InitParser::loadIni(const QString& file)
{
    qLog->info("Lecture du fichier INI " + file);
    reset();
    QFile f(file);
    if(f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&f);
        stream.setCodec("UTF-8");
        QStringList lines = stream.readAll().split('\n');
        f.close();

        InitGroup currentGroup;

        for(QString& line : lines)
        {
            line = line.trimmed();
            int idx = line.indexOf('#');
            if(idx >= 0)
            {
                line = line.left(idx).trimmed();
            }

            if(line != "")
            {
                if(line.startsWith('[') && line.endsWith(']'))
                {
                    setGroup(currentGroup);
                    QString title = line.mid(1).chopped(1).trimmed();
                    currentGroup = InitGroup(title);
                }
                else
                {
                    idx = line.indexOf('=');
                    if(idx >= 0)
                    {
                        QString key = line.left(idx).trimmed();
                        QString value = line.mid(idx+1).trimmed();
                        qLog->info(key + '=' + value);
                        if(!currentGroup.add(key, value))
                        {
                            qLog->warning("Une clé précédemment lue a été écrasée !");
                        }
                    }
                }
            }
        }
        setGroup(currentGroup);

        return true;
    }
    else
    {
        qLog->error("Impossible d'ouvrir le fichier INI");
        return false;
    }
}

bool InitParser::saveIni(const QString& file) const
{
    qLog->info("Enregistrement du fichier INI " + file);
    QFile f(file);
    if(f.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        QTextStream stream(&f);
        stream.setCodec("UTF-8");

        for(const InitGroup& group : m_groupMap)
        {
            qLog->info(group.toString());
            stream << "\n\n" + group.toString();
        }

        f.close();
        return true;
    }
    else
    {
        qLog->error("Impossible d'ouvrir le fichier");
        return false;
    }
}

void InitParser::reset() { m_groupMap.clear(); }

bool InitParser::contains(const QString& key) const { return m_groupMap.contains(key); }

InitGroup InitParser::get(const QString& key) const { return m_groupMap.value(key); }

InitGroup InitParser::emptyGroup() const { return m_groupMap.value(""); }

void InitParser::setGroup(const InitGroup& group) { m_groupMap[group.title()] = group; }
