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

        public: // GET/SET
            void setLastSearch(const QString& val);
            void setProjectFile(const QString& file);
            void setDoxyFile(const QString& file);
            void setDoxygenTemplateDir(const QString& dir);
            QString lastSearch() const;
            QString projectFile() const;
            QString doxyfile() const;
            QString doxygenTemplateDir() const;

        private:
            void init();
            void save();

        private:
            static Context* m_instance; /**< Pointeur vers l'instance de la classe Context. */
            QString m_lastSearch; /**< Dernière recherche effectuée. */
            QString m_projectFile; /**< Fichier du projet */
            QString m_doxyfile; /**< Fichier Doxygen du projet */
            QString m_doxygenTemplateDir; /**< Dossier dans lequel sont créés les templates Doxygen */
            InitParser m_parser; /**< Parser de fichier INI */
    };

    #define qCtx Context::Instance() /**< Pointeur vers l'instance de la classe Context. */

#endif // CONTEXT_HPP
