#include "disctoiso.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QToolButton>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QStorageInfo>
#include <QProcess>
#include <QDebug>

disctoiso::disctoiso(QWidget *parent) :
    QDialog(parent)
{
    QVBoxLayout *lo_dti = new QVBoxLayout();
    QHBoxLayout *lo_dti_top = new QHBoxLayout();
    QGroupBox *gr_top = new QGroupBox();
    //gr_top->setTitle("");

    cbb_driver = new QComboBox();

    getMountedDrive();

    QToolButton *tb_eject = new QToolButton();
    tb_eject->setIcon(QIcon::fromTheme("media-eject"));
    connect(tb_eject,SIGNAL(pressed()),this,SLOT(ejectDrive()));

    QPushButton *pb_refresh = new QPushButton("Refresh");
    pb_refresh->setFixedWidth(100);
    connect(pb_refresh,SIGNAL(pressed()),this,SLOT(getMountedDrive()));

    lo_dti_top->addWidget(cbb_driver);
    lo_dti_top->addWidget(tb_eject);
    lo_dti_top->addWidget(pb_refresh);
    lo_dti_top->setAlignment(pb_refresh, Qt::AlignRight);

    gr_top->setLayout(lo_dti_top);
    gr_top->setStyleSheet("QGroupBox{border: 1px solid #ccc;border-radius:8px;margin-top:0.5em}");

    //bottom
    QVBoxLayout *lo_bottom = new QVBoxLayout();

    QHBoxLayout *lo_bottom_top = new QHBoxLayout();

    QHBoxLayout *lo_bottom_bottom = new QHBoxLayout();

    QComboBox *cbb_iso = new QComboBox();
    cbb_iso->addItem("ISO");
    cbb_iso->addItem("CSO");
    cbb_iso->setFixedWidth(80);

    QLabel *lb_size = new QLabel();
    lb_size->setText("50697M free");

    lo_bottom_top->addWidget(cbb_iso);
    lo_bottom_top->addWidget(lb_size);
    lo_bottom_top->setAlignment(cbb_iso,Qt::AlignLeft);
    lo_bottom_top->setAlignment(lb_size,Qt::AlignRight);

    QLineEdit *le_name = new QLineEdit();

    QPushButton *btn_browse = new QPushButton("Change");

    lo_bottom_bottom->addWidget(le_name);
    lo_bottom_bottom->addWidget(btn_browse);

    lo_bottom->addLayout(lo_bottom_top);
    lo_bottom->addLayout(lo_bottom_bottom);

    QGroupBox *gr_bottom = new QGroupBox();

    gr_bottom->setLayout(lo_bottom);
    gr_bottom->setStyleSheet("QGroupBox{border: 1px solid #ccc;border-radius:8px;margin-top:0.5em}");


    QPushButton *pb_convert = new QPushButton("Convert");
    pb_convert->setFixedWidth(100);


    lo_dti->addWidget(gr_top);
    lo_dti->addWidget(gr_bottom);
    lo_dti->addWidget(pb_convert);
    lo_dti->setAlignment(pb_convert,Qt::AlignCenter);

    setLayout(lo_dti);
    setFixedSize(600,300);
    setWindowTitle("DVD/CD to ISO/CSO");
}

void disctoiso::getMountedDrive(){

    foreach (const QStorageInfo &storage, QStorageInfo::mountedVolumes()) {
         if(storage.fileSystemType()=="iso9660" || storage.fileSystemType()=="udf")

             if(cbb_driver->findText(storage.rootPath())==-1)
                cbb_driver->addItem(storage.rootPath());
       }
}

void disctoiso::ejectDrive(){

    QProcess *p_eject = new QProcess;
    connect(p_eject,SIGNAL(finished(int)),this,SLOT(getMountedDrive()));
    p_eject->start("eject", QStringList()<<cbb_driver->currentText());

}
