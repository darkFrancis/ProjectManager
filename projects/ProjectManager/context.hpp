#ifndef CONTEXT_HPP
#define CONTEXT_HPP

    #include <QString>

    class Context
    {
        public:
            static Context* Instance();
            void setProject(QString project_file);
            QString project();
            QString doxyfile();

        private:
            Context();
            static Context* m_instance;
            QString m_project_file;
            QString m_doxyfile;
    };

#endif // CONTEXT_HPP
