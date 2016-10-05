#ifndef DVDTOFILE_H
#define DVDTOFILE_H

#include <QDialog>
#include <QRadioButton>
#include <QComboBox>
#include <QToolButton>
#include <QPushButton>
#include <QTableWidget>
#include <QProcess>
#include <QLineEdit>
#include <QLabel>
#include <QTableWidgetItem>
#include <QProgressDialog>

class dvdtofile : public QDialog
{
    Q_OBJECT
public:
    explicit dvdtofile(QWidget *parent=0);

public slots:
    void radioDVDAct(bool);
    void radioFolderAct(bool);
    void getDirectory();
    void addMountedDrive();
    void ejectDrive();
    void getDVDInfo();
    void readDataDVD();
    void uncheckAllTitle();
    void checkAllTitle();
    void showLoadDial();
    void closeLoadDial();

private:
    QRadioButton *rb_dvd;
    QComboBox *cbb_cdrom;
    QRadioButton *rb_folder;
    QLineEdit *le_folder;
    QToolButton *tb_eject;
    QToolButton *tb_ref1 ;
    QToolButton *tb_openf ;
    QToolButton *tb_ref2 ;
    QTableWidget *tb_table;

    QProcess *pr_infoDVD;
    QLabel *videoInfo;
    QComboBox *cbb_au_stream;
    QComboBox *cbb_subt;
    QPushButton *pb_convert;
    QToolButton *tb_checkAll;
    QToolButton *tb_uncheckAll;
    QPushButton *pb_set_range;
    QLineEdit *le_file_title;

    QProgressDialog *pd_load;
    //QProgressDialog *pd_load;
};

#endif // DVDTOFILE_H
