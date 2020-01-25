#ifndef LOGGER_HPP
#define LOGGER_HPP

    #include <QString>
    #include <QFile>
    #include <QTextStream>
    #include <QDateTime>

    #define FILE_LOGGER QString("projectmanager.log")

    void create_logger();
    void logger(QString msg);

#endif // LOGGER_HPP
