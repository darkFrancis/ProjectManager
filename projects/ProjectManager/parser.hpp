/**
 * @file parser.hpp
 * @brief Description de la classe Parser
 * @author Dark Francis
 * @date 21/12/2019
 */
#ifndef PARSER_HPP
#define PARSER_HPP

    #include <QMap>
    #include <QFile>

    class Parser
    {
        public:
            static Parser* Instance();
            bool load(QString filename);
            QString get(QString key);
            void close();
            bool isUsed();

        protected:
            Parser();
            ~Parser();
            static Parser* m_instance;
            QMap<QString, QString> m_map;
            bool m_used;
    };

#endif // PARSER_HPP
