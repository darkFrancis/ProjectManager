#ifndef CONFLICTWINDOW_HPP
#define CONFLICTWINDOW_HPP

    #include <QMainWindow>
    #include <QTextEdit>
    #include <QListWidgetItem>
    #include <QToolTip>

    #define KEY_CURRENT     QString("<<<<<<<")
    #define KEY_TOMERGE     QString(">>>>>>>")
    #define KEY_CONTROL     QString("=======")
    #define KEY_LENGTH      7
    #define CLASS_CURRENT   QString("current")
    #define CLASS_TOMERGE   QString("to_merge")

    namespace Ui {
    class ConflictWindow;
    }

    class ConflictWindow : public QMainWindow
    {
        Q_OBJECT

        public:
            ConflictWindow(QWidget *parent = nullptr, QStringList files = QStringList());
            ~ConflictWindow();

        private slots:
            void on_textBrowser_conflict_anchorClicked(const QUrl &arg1);
            void on_listWidget_files_itemClicked(QListWidgetItem *item);
            void on_textBrowser_conflict_highlighted(const QString &arg1);
            void addDocument(QString filename);
            void showTooltip(QString link);

        private:
            Ui::ConflictWindow *ui;
            QString m_clicked_anchor;
            bool m_modified;

            QString addLink(QString text, QString branch, bool is_current);
            QString getStyle();
            bool save();
    };

#endif // CONFLICTWINDOW_HPP
