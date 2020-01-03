#ifndef GITVIEW_HPP
#define GITVIEW_HPP

    #include <QWidget>
    #include <QTableWidget>
    #include <QGridLayout>

    class GitView : public QWidget
    {
        Q_OBJECT

        public:
            explicit GitView(QWidget *parent = nullptr);
            ~GitView();
            void clean();
            void viewStatus(QString status);

        private:
            QGridLayout* m_layout;
    };

#endif // GITVIEW_HPP
