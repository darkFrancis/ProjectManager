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

    /**
     * @class Parser
     * @brief La classe Parser permet de lire les fichiers de données.
     *
     * Les informations des fichiers de données doivent être de la forme clé=valeur.
     * Les lignes vides ou après un @b # seront ignorées.
     * Ces informations sont stockées et utilisables jusqu'à ce que la fonction Parser::close soit appelée.
     * Tant que cette fonction n'est pas appelée, aucun autre fichier ne peut être lu.
     * @n Header : parser.hpp
     */
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
            static Parser* m_instance;/**< Pointeur vers l'instance de la classe Parser */
            QMap<QString, QString> m_map;/**< Liste de couples clé/valeur */
            bool m_used;/**< Booléen d'utilisation du Parser */
    };

#endif // PARSER_HPP
