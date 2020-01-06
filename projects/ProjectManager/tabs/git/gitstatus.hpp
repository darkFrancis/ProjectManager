#ifndef GITSTATUS_HPP
#define GITSTATUS_HPP

    #include <QWidget>
    #include <QLabel>

    namespace Ui {
        class GitStatus;
    }

    enum GitStatusType
    {
        Index,
        WorkTree,
        IndexAndWorkTree,
        Ignored,
        Untracked
    };

    class GitStatus : public QWidget
    {
        Q_OBJECT

        public:
            explicit GitStatus(QWidget *parent = nullptr, QString line = "");
            ~GitStatus();
            void newLine(QString line);
            QString file();
            QString statusStr();
            GitStatusType statusType();
            void setChecked(bool checked = true);
            bool isChecked();
            void setNameFor(GitStatusType type);

        signals:
            void diff(QString);

        private slots:
            void on_label_file_linkActivated(const QString &link);

        private:
            Ui::GitStatus *ui;
            QString m_status_str;
            GitStatusType m_type;

            void setFile(QString file);
            void setStatus(QString status);
            QString getStatusName(QChar status);
    };

#endif // GITSTATUS_HPP
