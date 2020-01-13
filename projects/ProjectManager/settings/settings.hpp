#ifndef SETTINGS_HPP
#define SETTINGS_HPP

    #include <QString>

    #define SETTINGS_FILE QString("settings.conf")

    class Settings
    {
        public:
            static Settings* Instance();
            void save();
            void load();
            // Get
            QString style(){return m_style;}
            bool keepSize(){return m_keep_size;}
            QString doxygenTemplateDir(){return m_doxygen_template_dir;}
            bool clearScreen(){return m_clear_screen;}
            // Set
            void setStyle(QString val){m_style = val;}
            void setKeepSize(bool val){m_keep_size = val;}
            void setDoxygenTemplateDir(QString val){m_doxygen_template_dir = val;}
            void setClearScreen(bool val){m_clear_screen = val;}

        private:
            Settings(){load();}
            void create();
            static Settings* m_instance;
            // View
            QString m_style;
            bool m_keep_size;
            // Doxygen
            QString m_doxygen_template_dir;
            // Compiler
            bool m_clear_screen;
    };

#endif // SETTINGS_HPP
