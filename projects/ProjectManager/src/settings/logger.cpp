/**
 * @file logger.cpp
 * @brief Définition des fonctions de log
 * @author Dark Francis
 * @date 21/12/2019
 */
#include "logger.hpp"

/**
 * @param msg Message à écrire dans le log.
 *
 * Permet d'écrire des message dans le fichier de log. @n
 * Cette fonction n'écrit que si la macro @b _DEBUG est définie. @n
 * L'écriture se fait à la suite du texte déjà écrit. @n
 * Le format d'écriture est le suivant : @b dd-MM-yyyy @b hh:mm:ss.zzz | @a msg
 * @n@n Header : logger.hpp
 */
void logger(QString msg)
{
    #ifdef _DEBUG
        QFile file(FILE_LOGGER);
        if(file.open(QIODevice::Text | QIODevice::WriteOnly | QIODevice::Append))
        {
            QTextStream stream(&file);
            QStringList ligns = msg.split('\n');
            for(int i = 0; i < ligns.length(); i++)
            {
                stream << QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss.zzz | ") << ligns[i] << endl;
            }
            file.close();
        }
    #endif // _DEBUG
}

/**
 * Créé le fichier de log. @n
 * La création ne s'effectue que si la macro@b _DEBUG est définie. @n
 * Si un fichier de log est déjà présent, l'efface.
 * @n@n Header : logger.hpp
 */
void create_logger()
{
    #ifdef _DEBUG
        QFile file(FILE_LOGGER);
        if(file.open(QIODevice::Text | QIODevice::WriteOnly | QIODevice::Truncate))
        {
            file.close();
        }
    #endif // _DEBUG
}
