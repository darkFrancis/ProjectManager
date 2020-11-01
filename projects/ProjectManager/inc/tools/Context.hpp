/**
 * @file Context.hpp
 * @brief Definition de la classe Context
 * @author Dark Francis
 * @date 26/10/2020
 */
#ifndef CONTEXT_HPP
#define CONTEXT_HPP

    #include <QString>
    #include "InitParser.hpp"

    /**
     * @brief La classe Context défini le contexte de l'exécution.
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
            bool removeSubProject(const QString& val);
            QString lastSearch() const;
            QString projectDir() const;
            QString doxyfile() const;
            QString doxygenTemplateDir() const;
            QStringList subProjects() const;
            QString projectHiddenDirName() const;

        private:
            void init();
            QString fileInProjectDir(const QString file) const;

        private:
            static Context* m_instance; /**< Pointeur vers l'instance de la classe Context. */
            QString m_lastSearch; /**< Dernière recherche effectuée. */
            QString m_projectDir; /**< Fichier du projet */
            QStringList m_subProjectList; /**< Liste des sous-projets utilisés pour la documentation. */
            InitParser m_parser; /**< Parser de fichier INI */
    };

    #define qCtx Context::Instance() /**< Pointeur vers l'instance de la classe Context. */

#endif // CONTEXT_HPP
