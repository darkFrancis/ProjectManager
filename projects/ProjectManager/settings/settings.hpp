#ifndef SETTINGS_HPP
#define SETTINGS_HPP

    #include <QString>
    #include <QList>

    #define SETTINGS_FILE           QString("config/settings.conf")
    #define COLORS_FILE             QString("config/colors.conf")
    #define COMPILER_FILE           QString("config/compiler.conf")

    #define COMPILE_OVERALL         QString("overall_options")
    #define COMPILE_LANGUAGE_C      QString("c_language")
    #define COMPILE_LANGUAGE_CXX    QString("cxx_language")

    struct Color
    {
        QString name;
        int red;
        int green;
        int blue;
    };
    typedef struct Color Color;

    struct CompilerOption
    {
        QString option;
        QString brief;
        QString tooltip;
    };
    typedef struct CompilerOption CompilerOption;

    class Settings
    {
        public:
            static Settings* Instance();
            void init(){}
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
            QStringList sourcesExtensions(){return m_sources_extensions;}
            QStringList headersExtensions(){return m_headers_extensions;}
            // Get with no set
            QList<Color>* colors(){return &m_colors;}
            QList<CompilerOption>* overallOptions(){return &m_overall_options;}
            QList<CompilerOption>* languageCOptions(){return &m_language_c_options;}
            QList<CompilerOption>* languageCxxOptions(){return &m_language_cxx_options;}
            // Set
            void setStyle(QString val){m_style = val;}
            void setKeepSize(bool val){m_keep_size = val;}
            void setDoxygenTemplateDir(QString val){m_doxygen_template_dir = val;}
            void setClearScreen(bool val){m_clear_screen = val;}
            void setColorNormal(QString color){m_color_normal = color;}
            void setColorSuccess(QString color){m_color_success = color;}
            void setColorError(QString color){m_color_error = color;}
            void setSourcesExtensions(QStringList exts){m_sources_extensions = exts;}
            void setHeadersExtensions(QStringList exts){m_headers_extensions = exts;}

        private:
            Settings();
            void create();
            void init_color();
            void init_compiler_options();
            void add_color(QString name, int red, int green, int blue);
            void add_compiler_option(QString key_word, QString option, QString brief, QString tooltip);
            static Settings* m_instance;
            // View
            QString m_style;
            bool m_keep_size;
            // Doxygen
            QString m_doxygen_template_dir;
            // Compiler
            bool m_clear_screen;
            QString m_color_normal;
            QString m_color_success;
            QString m_color_error;
            QStringList m_sources_extensions;
            QStringList m_headers_extensions;
            // Static config (no set)
            QList<Color> m_colors;
            QList<CompilerOption> m_overall_options;
            QList<CompilerOption> m_language_c_options;
            QList<CompilerOption> m_language_cxx_options;
    };

#endif // SETTINGS_HPP
