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

        protected:
            Parser();
            ~Parser();
            static Parser* m_instance;
            QMap<QString, QString> m_map;
    };

#endif // PARSER_HPP
