#ifndef GITVIEW_HPP
#define GITVIEW_HPP

    #include <QWidget>
    #include <QTableWidget>
    #include <QGridLayout>

    #define KEY_NEW QString("new file")
    #define KEY_MOD QString("modified")

    namespace Ui {
        class GitView;
    }

    class GitView : public QWidget
    {
        Q_OBJECT

        public:
            explicit GitView(QWidget *parent = nullptr);
            ~GitView();
            void clean();
            void viewStatus(QString status);

        private:
            Ui::GitView *ui;
            QGridLayout* m_layout;
            QTableWidget* m_table_widget;
    };

#endif // GITVIEW_HPP
