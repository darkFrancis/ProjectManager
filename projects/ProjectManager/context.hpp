#ifndef CONTEXT_HPP
#define CONTEXT_HPP

    #include <QString>

    class Context
    {
        public:
            static Context* Instance();
            void setProject(QString project_file);
            QString project();

        private:
            Context();
            static Context* m_instance;
            QString m_project_file;
    };

#endif // CONTEXT_HPP
