#ifndef ABOUT
#define ABOUT

#include <QDialog>
#include <QStackedLayout>
#include <QProcess>
#include <QTextEdit>
#include <QLabel>

class about : public QDialog
{
    Q_OBJECT

public :
    explicit about(QWidget *parent = 0);
    ~about();

private :
    QStackedLayout *stack_tentang;

public slots :
       void on_btn_author_clicked();
       void on_btn_license_clicked();
       void on_btn_credit_clicked();
};

#endif // ABOUT

