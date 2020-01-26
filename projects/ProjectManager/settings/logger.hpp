/**
 * @file logger.hpp
 * @brief Définition des fonctions de log
 * @author Dark Francis
 * @date 21/12/2019
 */
#ifndef LOGGER_HPP
#define LOGGER_HPP

    #include <QString>
    #include <QFile>
    #include <QTextStream>
    #include <QDateTime>

    #define FILE_LOGGER QString("projectmanager.log")/**< Fichier de log */

    void create_logger();
    void logger(QString msg);

#endif // LOGGER_HPP
