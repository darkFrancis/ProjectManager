/**
 * @file Logger.hpp
 * @brief Definition de la classe Logger
 * @author Dark Francis
 * @date 25/10/2020
 */
#ifndef LOGGER_HPP
#define LOGGER_HPP

    #include <QString>

    /**
     * @brief L'énumération LogLvl défini le niveau de log de référence.
     *
     * Ce niveau de log est utilisé de la façon suivante : si le niveau de log
     * demandé par une fonction est inférieur ou égale à #m_lvl, le log est
     * écrit, sinon, le log est ignoré.
     */
    enum LogLvl : int
    {
        Debug   = 5, /**< Tout est logué */
        Info    = 4, /**< Seuls les logs d'info, de warning et d'erreur sont logués */
        Warning = 3, /**< Seuls les logs de warning et d'erreur sont logués */
        Error   = 2, /**< Seuls les logs d'erreur sont logués */
        Fatal   = 1, /**< Seuls les logs d'erreur fatale sont logués */
        Off     = 0  /**< Rien n'est logué */
    };

    /**
     * @brief La classe Logger définie l'instance de log.
     *
     * Un objet de cette classe doit être créé dans la fonction principale pour
     * pouvoir être utilisé dans le reste du code.
     */
    class Logger
    {
        public:
            Logger();
            ~Logger();
            static Logger* Instance();
            bool createLog(const QString& file, int rotation = 0);
            void closeLog();
            QString currentFile() const;

        public: // log
            void setLogLevel(LogLvl lvl);
            void debug(const QString& msg);
            void info(const QString& msg);
            void warning(const QString& msg);
            void error(const QString& msg);
            void fatal(const QString& msg);

        private:
            void printLog(LogLvl lvl, const QString& msg);
            QString rotationFileName(const QString& file, int rotation);

        private:
            static Logger* m_instance;  /**< Instance unique de la classe Logger */
            LogLvl m_lvl;               /**< Niveau actuel de log */
    };

    #define qLog Logger::Instance()

#endif // LOGGER_HPP
