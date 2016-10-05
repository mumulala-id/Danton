#ifndef MEDIAINFO_H
#define MEDIAINFO_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QProcess>

class mediainfo : public QDialog
{
    Q_OBJECT
public:
    explicit mediainfo(QWidget *paremt=0);
private:
     QLineEdit *le_filename;
     QTextEdit *te_output;
     QProcess *get_info_media;


public slots:
     void proceed();
     void openFileMediaInfo();
     void readMediaOutput();
     void setFile(QString);
     void toClipboard();

};

#endif // MEDIAINFO_H
