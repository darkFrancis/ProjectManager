/**
 * @file InitParser.hpp
 * @brief Definition de la classe InitParser
 * @author Dark Francis
 * @date 26/10/2020
 */
#ifndef INITPARSER_HPP
#define INITPARSER_HPP

    #include <QString>
    #include <QMap>

    class InitParser;

    class InitGroup
    {
        public:
            InitGroup(const QString& title = "");
            bool contains(const QString& key) const;
            QString get(const QString& key) const;
            QString title() const;
            bool add(const QString& key, const QString& value);
            QString toString() const;

        private:
            QString m_title;
            QMap<QString,QString> m_mapValues; /**< Map des couples clé/valeur lus. */
    };

    /**
     * @brief La classe InitParser permet de parser un fichier de type INI.
     */
    class InitParser
    {
        public:
            InitParser();
            bool loadIni(const QString& file);
            bool saveIni(const QString& file) const;
            void reset();
            bool contains(const QString& key) const;
            InitGroup get(const QString& key) const;
            InitGroup emptyGroup() const;
            void setGroup(const InitGroup& group);

        private:
            QMap<QString,InitGroup> m_groupMap; /**< Map des groupes dans le fichier INI */
    };

#endif // INITPARSER_HPP
