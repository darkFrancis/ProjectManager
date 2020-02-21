#ifndef CONFLICTWINDOW_HPP
#define CONFLICTWINDOW_HPP

    #include <QMainWindow>
    #include <QTextEdit>
    #include <QMouseEvent>
    #include <QListWidgetItem>

    #define KEY_CURRENT QString("<<<<<<<")
    #define KEY_TOMERGE QString(">>>>>>>")
    #define KEY_CONTROL QString("=======")
    #define KEY_LENGTH  7

    namespace Ui {
    class ConflictWindow;
    }

    class ConflictTextEdit : public QTextEdit
    {
        Q_OBJECT

        public:
            ConflictTextEdit(QWidget *parent = nullptr);
            void mousePressEvent(QMouseEvent *e);
            void mouseReleaseEvent(QMouseEvent *e);
            bool isModified() { return m_modified; }
            bool save();

        public slots:
            void addDocument(QString file_name);

        signals:
            void linkActivated(QString link);

        private:
            QString m_clicked_anchor;
            bool m_modified;
            QString addLink(QString text, QString branch, bool is_current);
    };

    class ConflictWindow : public QMainWindow
    {
        Q_OBJECT

        public:
            ConflictWindow(QWidget *parent = nullptr, QStringList files = QStringList());
            ~ConflictWindow();

        private slots:
            void linkClicked(QString link);
            void on_listWidget_itemClicked(QListWidgetItem *item);

        private:
            Ui::ConflictWindow *ui;
            ConflictTextEdit* m_text_edit;
    };

#endif // CONFLICTWINDOW_HPP
