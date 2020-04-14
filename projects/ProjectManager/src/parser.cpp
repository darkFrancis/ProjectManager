/**
 * @file parser.cpp
 * @brief Définition des fonctions de la classe Parser
 * @author Dark Francis
 * @date 21/12/2019
 */
#include "parser.hpp"
#include "logger.hpp"

Parser* Parser::m_instance = nullptr;

/**
 * @return Un pointeur vers l'unique instance de la classe Parser.
 *
 * Permet d'obtenir un pointeur vers l'instance Parser.@n
 * Si aucune instance de Parser n'a été créée, la créée.
 * Dans tout les cas, cette fonction renvoie un pointeur vers cette instance.
 */
Parser* Parser::Instance()
{
    if(!m_instance)
        m_instance = new Parser();
    return m_instance;
}

/**
 * Constructeur de la classe Parser.@n
 * Initialise les attributs de cette classe:
 * @li Nettoyage de Parser::m_map
 * @li Parser::m_used = @b false
 */
Parser::Parser()
{
    logger(__PRETTY_FUNCTION__);
    m_map.clear();
    m_used = false;
}

/**
 * @param filename Fichier à charger
 * @return @li @b true en cas de succès
 *         @li @b false sinon
 *
 * Cette fonction permet de charger et d'analyser un fichier.@n
 * Si un fichier est déjà chargé, renvoie automatiquement la valeur @b false
 * sans rien effectuer. L'attribut Parser::m_map est nettoyé puis le fichier
 * @c filename est chargé et chaque ligne est analysée ainsi:
 * @li Tout caractère après le caractère @b '#' est ignoré
 * @li Une ligne vide (ou ne contenant que des espaces) est ignorée
 * @li Si une ligne contient un caractère '=', elle est analysée. Tous ce qui
 * se trouve à gauche de ce caractère est considéré comme la clé, ce qui se
 * trouve à droite est considéré comme la valeur. Si la ligne se termine par
 * le symbole @b ' \', la valeur se continue sur la ligne suivante.
 * @li Une ligne analysée est ajoutée à l'attribut Parser::m_map
 *
 * Une fois le fichier lu en entier, l'attribut Parser::m_used passe à @b true.
 */
bool Parser::load(QString filename)
{
    logger(__PRETTY_FUNCTION__);
    if(m_used)
    {
        logger("    ERROR : Parser already used");
        return false;
    }

    m_map.clear();
    QFile file(filename);
    if(file.open(QIODevice::Text | QIODevice::ReadOnly))
    {
        logger("    file " + filename + " opened");
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
                    m_map.insert(param[0].simplified(), param[1].simplified());
                }
            }
        }
        file.close();
        m_used = true;
        return true;
    }
    logger("    Can't open the file " + filename);
    return false;
}

/**
 * @param key Clé demandée
 * @return Valeur correspondant à la clé demandée
 *
 * Cette fonction permet d'obtenir la valeur correspondant à la clé @c kw passée
 * en argument à partir de la map Parser::m_map. Si la clé n'a pas été renseignée,
 * renvoie une chaine de caractères vide.
 */
QString Parser::get(QString key)
{
    logger("    get_value " + key);
    if(m_map.contains(key))
    {
        return m_map.value(key);
    }
    return "";
}

/**
 * Fonction de fermeture.@n
 * Passe l'attribut Parser::m_used à false. Un nouveau fichier peut être chargé.
 */
void Parser::close()
{
    logger(__PRETTY_FUNCTION__);
    m_used = false;
}
