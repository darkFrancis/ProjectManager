#ifndef GITVIEW_HPP
#define GITVIEW_HPP

    #include <QWidget>
    #include <QTableWidget>
    #include <QGridLayout>
    #include <QList>
    #include "gitstatus.hpp"

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
            QList<GitStatus> m_status_list;
    };

#endif // GITVIEW_HPP
