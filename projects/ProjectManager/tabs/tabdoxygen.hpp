#ifndef TABDOXYGEN_HPP
#define TABDOXYGEN_HPP

    #include <QWidget>

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
    };

#endif // TABDOXYGEN_HPP
