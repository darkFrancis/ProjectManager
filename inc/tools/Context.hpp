/**
 * @file Context.hpp
 * @brief Définition du contexte d'utilisation
 * @author Dark Francis
 * @date 26/10/2020
 */
#ifndef CONTEXT_HPP
#define CONTEXT_HPP

    #include <QString>
    #include "InitParser.hpp"

    /**
     * @header_table Context.hpp @end_table
     * @brief La classe Context défini le contexte de l'exécution.
     *
     * Cette classe ne peut être instanciée qu'une seule fois dans l'application.
     * Une exception est levée lors d'une seconde création. Elle sert à lire le
     * fichier INI et les fichiers de projets. Les différentes informations sont
     * accessibles ensuite dans toute l'application.
     */
    class Context
    {
        public:
            Context();
            ~Context();
            static Context* Instance();
            void loadSubProjects();
            bool saveSubProjects() const;
            void save();

        public: // GET/SET
            void setLastSearch(const QString& val);
            void setProjectDir(const QString& dir);
            void addSubProject(const QString& val);
            void setProjectDescription(const QString& project, const QString& description);
            bool removeSubProject(const QString& val);
            QString lastSearch() const;
            QString projectDir() const;
            QString pathFromProject(const QString& absolutePath) const;
            QString doxyfile() const;
            QString doxygenTemplateDir() const;
            QStringList subProjects() const;
            QString projectDescription(const QString& project) const;
            QString projectHiddenDirName() const;

        private:
            void init();
            QString fileInProjectDir(const QString file) const;

        private:
            static Context* m_instance; /**< Pointeur vers l'instance de la classe Context. */
            QString m_lastSearch; /**< Dernière recherche effectuée. */
            QString m_projectDir; /**< Dossier du projet */
            QMap<QString,QString> m_subProjectList; /**< Liste des sous-projets utilisés pour la documentation avec leur description. */
            InitParser m_parser; /**< Parser de fichier INI */
    };

    #define qCtx Context::Instance() /**< Pointeur vers l'instance de la classe Context. */

#endif // CONTEXT_HPP
