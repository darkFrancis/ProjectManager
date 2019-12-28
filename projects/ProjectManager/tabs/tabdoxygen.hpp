#ifndef TABDOXYGEN_HPP
#define TABDOXYGEN_HPP

    #include <QWidget>
    #include <QCheckBox>
    #include <QComboBox>
    #include <QLineEdit>
    #include <QSpinBox>
    #include <QFontComboBox>
    #include <QGroupBox>

    #define DOC_YES QString("YES")
    #define DOC_NO  QString("NO")

    namespace Ui {
        class TabDoxygen;
    }

    class TabDoxygen : public QWidget
    {
        Q_OBJECT

        public:
            explicit TabDoxygen(QWidget *parent = nullptr);
            ~TabDoxygen();
            void init();
            void save();
            void createDoxyfile();

        private:
            Ui::TabDoxygen *ui;
            QString m_doxyfile;
            QTextStream* m_stream;

            // Init tabs
            void init_tabProject();
            void init_tabBuild();
            void init_tabMsg();
            void init_tabInput();
            void init_tabSource();
            void init_tabHtml();
            void init_tabOutput();
            void init_tabProcessor();
            void init_tabExternRef();
            void init_tabGraph();

            // Save tabs
            void save_tabProject();
            void save_tabBuild();
            void save_tabMsg();
            void save_tabInput();
            void save_tabSource();
            void save_tabHtml();
            void save_tabOutput();
            void save_tabProcessor();
            void save_tabExternRef();
            void save_tabGraph();

            // Init Widgets
            void initCheckbox(QString key, QCheckBox* checkbox, bool default_value, bool default_cond = false);
            void initGroupbox(QString key, QGroupBox* groupbox, bool default_value, bool default_cond = false);
            void initCombobox(QString key, QComboBox* combobox, QString default_value = "", bool default_cond = false);
            void initFontCbox(QString key, QFontComboBox* fontcombobox, QString default_value = "", bool default_cond = false);
            void initLineedit(QString key, QLineEdit* lineedit, QString default_value = "", bool default_cond = false);
            void initSpinbox_(QString key, QSpinBox* spinbox, int default_value = 0, bool default_cond = false);

            // Save Widgets
            void saveCheckbox(QString key, QCheckBox* checkbox, bool default_value);
            void saveGroupbox(QString key, QGroupBox* groupbox, bool default_value);
            void saveCombobox(QString key, QComboBox* combobox, QString default_value = "");
            void saveFontCbox(QString key, QFontComboBox* fontcombobox, QString default_value = "");
            void saveLineedit(QString key, QLineEdit* lineedit, QString default_value = "");
            void saveSpinbox_(QString key, QSpinBox* spinbox, int default_value = 0);
    };

#endif // TABDOXYGEN_HPP
