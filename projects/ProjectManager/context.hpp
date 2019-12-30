#ifndef CONTEXT_HPP
#define CONTEXT_HPP

    #include <QString>

    class Context
    {
        public:
            static Context* Instance();
            void setProject(QString project_file);
            void setLastSearch(QString last_search);
            void loadProject();
            QString project();
            QString lastSearch();
            QString doxyfile();
            bool isOpen();

        private:
            Context();
            static Context* m_instance;
            // Files
            QString m_project_file;
            QString m_doxyfile;
            bool m_open;
            // Options
            // Last
            QString m_last_search;
    };

#endif // CONTEXT_HPP
