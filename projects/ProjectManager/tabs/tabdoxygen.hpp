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

        private:
            Ui::TabDoxygen *ui;
    };

#endif // TABDOXYGEN_HPP
