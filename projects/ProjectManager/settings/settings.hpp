#ifndef SETTINGS_HPP
#define SETTINGS_HPP

    #include <QString>
    #include <QList>

    #define SETTINGS_FILE QString("settings.conf")

    struct Color
    {
        QString name;
        QString hex_name;
    };
    typedef struct Color Color;

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
            QString colorNormal(){return m_color_normal;}
            QString colorSuccess(){return m_color_success;}
            QString colorError(){return m_color_error;}
            QList<Color>* colors(){return &m_colors;}
            // Set
            void setStyle(QString val){m_style = val;}
            void setKeepSize(bool val){m_keep_size = val;}
            void setDoxygenTemplateDir(QString val){m_doxygen_template_dir = val;}
            void setClearScreen(bool val){m_clear_screen = val;}
            void setColorNormal(QString color){m_color_normal = color;}
            void setColorSuccess(QString color){m_color_success = color;}
            void setColorError(QString color){m_color_error = color;}

        private:
            Settings(){load();}
            void create();
            void init_color();
            void add_color(QString name, QString hex_name);
            static Settings* m_instance;
            // View
            QString m_style;
            bool m_keep_size;
            // Doxygen
            QString m_doxygen_template_dir;
            // Compiler
            bool m_clear_screen;
            QList<Color> m_colors;
            QString m_color_normal;
            QString m_color_success;
            QString m_color_error;
    };

#endif // SETTINGS_HPP
