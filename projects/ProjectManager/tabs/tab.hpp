#ifndef TAB_HPP
#define TAB_HPP

    #include <QWidget>

    class Tab : public QWidget
    {
        Q_OBJECT
        public:
            Tab(QWidget *parent = nullptr) : QWidget(parent){}
            ~Tab(){clean();}
            void clean(){}

        signals:
            void apply(Tab*);
    };

#endif // TAB_HPP
