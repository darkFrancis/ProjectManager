/**
 * @file InitParser.cpp
 * @brief Source du parser de fichiers INI
 * @author Dark Francis
 * @date 26/10/2020
 */
#include "tools/InitParser.hpp"

#include <QFile>
#include <QTextStream>

#include "Logger/Logger.hpp"

/**
 * @param title Titre du groupe
 *
 * Constructeur de la classe InitGroup.
 */
InitGroup::InitGroup(const QString& title) :
    m_title(title)
{}

/**
 * @param key Clé recherchée
 * @return @li @b true si la clé est présente
 *         @li @b false sinon
 */
bool InitGroup::contains(const QString& key) const { return m_mapValues.contains(key); }

/**
 * @param key Clé recherchée
 * @return Valeur correspondant à la clé dans le groupe
 * @note Retourne une chaîne de caractères vide si la clé est absente.
 */
QString InitGroup::get(const QString& key) const { return m_mapValues.value(key, ""); }

/**
 * @return #m_title
 */
QString InitGroup::title() const { return m_title; }

/**
 * @param key Clé
 * @param value Valeur
 * @return @li @b true si le couple clé/valeur est bien ajouté
 *         @li @b false sinon
 *
 * Ajoute le couple clé valeur dans le groupe si la clé n'est pas déjà présente.
 */
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

/**
 * @return Groupe au format chaîne de caractères pour écriture dans le fichier INI
 */
QString InitGroup::toString() const
{
    QString text = (m_title != "" ? '[' + m_title + ']' : "");
    for(const QString& key : m_mapValues.keys())
    {
        text += '\n' + key + '=' + m_mapValues.value(key);
    }
    return text;
}

/**
 * Constructeur de la classe InitParser.
 */
InitParser::InitParser()
{}

/**
 * @param file Fichier INI à charger
 * @return @li @b true en cas de réussite
 *         @li @b false sinon
 *
 * Charge le fichier INI ainsi que ses groupes et couples clé/valeur.
 */
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

/**
 * @param file Fichier INI à enregistrer
 * @return @li @b true en cas de réussite
 *         @li @b false sinon
 *
 * Enregistre les groupes dans le ficheir INI.
 */
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

/**
 * Efface les groupes de la structure INI.
 */
void InitParser::reset() { m_groupMap.clear(); }

/**
 * @param key Clé recherchée
 * @return @li @b true si la clé est présente
 *         @li @b false sinon
 */
bool InitParser::contains(const QString& key) const { return m_groupMap.contains(key); }

/**
 * @param key Clé recherchée
 * @return Groupe correspondant à la clé dans le groupe
 * @note Retourne un groupe vide si la clé est absente.
 */
InitGroup InitParser::get(const QString& key) const { return m_groupMap.value(key); }

/**
 * @return Groupe correspondant à la clé vide
 */
InitGroup InitParser::emptyGroup() const { return m_groupMap.value(""); }

/**
 * @param group Groupe à ajouter
 *
 * Ajoute le groupe dans la liste des roupes pour enregistrement.
 */
void InitParser::setGroup(const InitGroup& group) { m_groupMap[group.title()] = group; }
