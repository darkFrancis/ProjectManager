/**
 * @file InitParser.hpp
 * @brief Definition du parser de fichiers INI
 * @author Dark Francis
 * @date 26/10/2020
 */
#ifndef INITPARSER_HPP
#define INITPARSER_HPP

    #include <QString>
    #include <QMap>

    /**
     * @header_table InitParser.hpp @end_table
     * @brief La classe InitGroup défini un groupe dans un fichier INI.
     *
     * Les groupes peuvent être utilisés de deux façons différentes :
     * @li Lors de la lecture d'un fichier INI par un objet InitParser, les groupes
     * peuvent être récupérés pour en lire le titre avec la méthode title() et le
     * contenu avec les méthodes contains() et get().
     * @li lors de l'écriture d'un fichier INI. Les groupe sont créés avec un titre,
     * puis, on leur attribu des éléments avec la méthode add(). Enfin, le groupe est
     * passé à l'objet InitParser qui utilise la méthode toString() lors de
     * l'enregistrement.
     */
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
            QString m_title; /**< Titre du groupe. */
            QMap<QString,QString> m_mapValues; /**< Map des couples clé/valeur lus. */
    };

    /**
     * @header_table InitParser.hpp @end_table
     * @brief La classe InitParser permet de parser un fichier de type INI.
     *
     * L'utilisation se fait comme suit en lecture :
     * @li Définition du parser.
     * @li Utilisation de la méthode loadINI().
     * @li Récupération des groupes avec les méthodes contains(), get() et emptyGroup().
     *
     * L'utilisation se fait comme suit en écriture :
     * @li Définition du parser ou reset().
     * @li Ajout de groupe avec la méthode setGroupe().
     * @li Enregistrement avec la méthode saveIni().
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
