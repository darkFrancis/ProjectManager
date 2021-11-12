/**
 * @file logger.cpp
 * @brief Définition des fonctions de log
 * @author Dark Francis
 * @date 21/12/2019
 */
#include "logger.hpp"

void logger(QString msg)
{
    #ifdef _DEBUG
        QFile file(FILE_LOGGER);
        if(file.open(QIODevice::Text | QIODevice::WriteOnly | QIODevice::Append))
        {
            QTextStream stream(&file);
            stream << QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss.zzz | ") << msg << endl;
            file.close();
        }
    #endif // _DEBUG
}

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
