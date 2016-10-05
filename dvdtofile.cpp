#include "dvdtofile.h"
#include <QGridLayout>
#include <QGroupBox>
#include <QFileDialog>
#include <QIcon>
#include <QStorageInfo>
#include <QRegExp>
#include <QHeaderView>
#include <QDebug>
#include <QLabel>


dvdtofile::dvdtofile(QWidget *parent) :
    QDialog(parent)
{


    QVBoxLayout *lo_dtf = new QVBoxLayout();
    QGridLayout *lo_top = new QGridLayout();

    rb_dvd = new QRadioButton();
    rb_dvd->setText("DVD");
    rb_dvd->setChecked(1);
    rb_dvd->setFixedWidth(80);
    connect(rb_dvd,SIGNAL(toggled(bool)),this,SLOT(radioDVDAct(bool)));

//    QLabel *lb_ic_cd = new QLabel();
//    lb_ic_cd->setPixmap(QIcon::fromTheme("folder"));
    QHBoxLayout *lo_cbb_cdrom = new QHBoxLayout();
    cbb_cdrom = new QComboBox();
    cbb_cdrom->setFixedWidth(280);
    lo_cbb_cdrom->addWidget(cbb_cdrom);


    connect(cbb_cdrom,SIGNAL(activated(int)),this,SLOT(getDVDInfo()));

    //adding mounted drive
   addMountedDrive();


   //load data
   getDVDInfo();


    tb_eject = new QToolButton();
    tb_eject->setIcon(QIcon::fromTheme("media-eject"));
    connect(tb_eject,SIGNAL(clicked(bool)),this,SLOT(ejectDrive()));

    tb_ref1 = new QToolButton();
    tb_ref1->setIcon(QIcon::fromTheme("view-refresh"));
    connect(tb_ref1,SIGNAL(clicked(bool)),this,SLOT(addMountedDrive()));

    pb_convert = new QPushButton("Convert");
    pb_convert->setEnabled(0);
    pb_convert->setFixedWidth(100);

    rb_folder= new QRadioButton();
    rb_folder->setText("Folder");
    rb_folder->setFixedWidth(80);
    connect(rb_folder,SIGNAL(toggled(bool)),this,SLOT(radioFolderAct(bool)));


    le_folder = new QLineEdit();
    le_folder->setEnabled(0);
    le_folder->setFixedWidth(280);

    tb_openf = new QToolButton();
    tb_openf->setIcon(QIcon::fromTheme("folder_open"));
    tb_openf->setEnabled(0);
    connect(tb_openf,SIGNAL(clicked(bool)),this,SLOT(getDirectory()));

    tb_ref2 = new QToolButton();
    tb_ref2->setIcon(QIcon::fromTheme("gtk-refresh"));
    tb_ref2->setEnabled(0);

    videoInfo = new QLabel(this);
   // videoInfo->setText("kuda");



   // lo_top->setColumnMinimumWidth(1,200);
            lo_top->addWidget(rb_dvd,0,0);
    lo_top->addLayout(lo_cbb_cdrom,0,1);
    lo_top->addWidget(tb_eject,0,2);
   // lo_top->setColumnStretch(1,200);
    lo_top->addWidget(tb_ref1,0,3);
    lo_top->addWidget(pb_convert,0,4,Qt::AlignRight);
    lo_top->addWidget(rb_folder,1,0);
    lo_top->addWidget(le_folder,1,1);
    lo_top->addWidget(tb_openf,1,2);
    lo_top->addWidget(tb_ref2,1,3);
    lo_top->addWidget(videoInfo,1,4,Qt::AlignCenter);

    QGroupBox *gr_top = new QGroupBox();
    gr_top->setStyleSheet("QGroupBox{border: 1px solid #ccc;border-radius:8px;margin-top:0.5em}"
                          "QGroupBox::title{subcontrol-origin:margin;left:10px;padding: 0 3px 0 3px}");
    gr_top->setTitle("DVD Driver");
    gr_top->setLayout(lo_top);




    QHBoxLayout *lo_bottom = new QHBoxLayout();

    QVBoxLayout *lo_bottom_left = new QVBoxLayout();
    QVBoxLayout *lo_bottom_right = new QVBoxLayout();

    QHBoxLayout *lo_left_top = new QHBoxLayout();

    tb_checkAll = new QToolButton();
    tb_checkAll->setEnabled(0);
    tb_checkAll->setToolTip("Select All");
    tb_checkAll->setIcon(QIcon::fromTheme("dialog-yes"));
    connect(tb_checkAll, SIGNAL(clicked(bool)), SLOT(checkAllTitle()));

    tb_uncheckAll = new QToolButton();
    tb_uncheckAll->setEnabled(0);
    tb_uncheckAll->setToolTip("Unselect All");
    tb_uncheckAll->setIcon(QIcon::fromTheme("dialog-no"));
    connect(tb_uncheckAll,SIGNAL(clicked(bool)),SLOT(uncheckAllTitle()));

    pb_set_range = new QPushButton("Set Range");
    pb_set_range->setEnabled(0);
    pb_set_range->setFixedWidth(100);


    tb_table = new QTableWidget;
    tb_table->setColumnCount(3);
    tb_table->setHorizontalHeaderLabels(QString("Title;Duration;Range").split(";"));
    tb_table->verticalHeader()->hide();
    tb_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    tb_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    lo_left_top->addWidget(tb_checkAll,Qt::AlignLeft);
    lo_left_top->addWidget(tb_uncheckAll,0,Qt::AlignLeft);
    lo_left_top->addWidget(pb_set_range,Qt::AlignRight);

    lo_bottom_left->addLayout(lo_left_top);
    lo_bottom_left->addWidget(tb_table);

    //----------------- bootom right


   // QVBoxLayout *lo_right = new QVBoxLayout();

    QLabel *lb_quality = new QLabel();
    lb_quality->setText("High quality and size");
    lb_quality->setAlignment(Qt::AlignCenter);

    QHBoxLayout *lo_format_setting = new QHBoxLayout();

    QComboBox *cbb_format =new QComboBox();
    cbb_format->addItem("MP4");
    cbb_format->addItem("MKV");
    QPushButton *pb_setting = new QPushButton("Output Setting");
    lo_format_setting->addWidget(cbb_format);
    lo_format_setting->addWidget(pb_setting);

    QGroupBox *gr_subt = new QGroupBox();
    gr_subt->setTitle("Subtitle language");
    QHBoxLayout *lo_subt = new QHBoxLayout();

    cbb_subt = new QComboBox();
    cbb_subt->addItem("None");

    lo_subt->addWidget(cbb_subt);
    gr_subt->setLayout(lo_subt);

    QHBoxLayout *lo_au_stream = new QHBoxLayout();
    QGroupBox *gr_au_stream = new QGroupBox();
    gr_au_stream->setTitle("Audio stream");

    cbb_au_stream = new QComboBox(this);
    cbb_au_stream->addItem("Default");

    lo_au_stream->addWidget(cbb_au_stream);

    gr_au_stream->setLayout(lo_au_stream);

    QHBoxLayout *lo_file_title = new QHBoxLayout();
    QGroupBox *gr_file_title = new QGroupBox();

    le_file_title = new QLineEdit();

    lo_file_title->addWidget(le_file_title);
    gr_file_title->setTitle("File title");
    gr_file_title->setLayout(lo_file_title);


    lo_bottom_right->addWidget(lb_quality);
    lo_bottom_right->addLayout(lo_format_setting);
    lo_bottom_right->addWidget(gr_subt);
    lo_bottom_right->addWidget(gr_au_stream);
    lo_bottom_right->addWidget(gr_file_title);

    lo_bottom->addLayout(lo_bottom_left);
    lo_bottom->addLayout(lo_bottom_right);

    QGroupBox *gr_bottom = new QGroupBox();
    gr_bottom->setLayout(lo_bottom);
    gr_bottom->setTitle("Output Setting");
    gr_bottom->setStyleSheet("QGroupBox{border: 1px solid #ccc;border-radius:8px;margin-top:0.5em}"
                             "QGroupBox::title{subcontrol-origin:margin;left:10px;padding: 0 3px 0 3px}");




lo_dtf->addWidget(gr_top);
lo_dtf->addWidget(gr_bottom);

    setLayout(lo_dtf);
    setFixedSize(800,500);
    setWindowTitle("DVD to Video File");
}

void dvdtofile::radioDVDAct(bool s){
    if(s){
        cbb_cdrom->setEnabled(1);
        le_folder->setEnabled(0);
        tb_eject->setEnabled(1);
        tb_ref1->setEnabled(1);
        tb_openf->setEnabled(0);
        tb_ref2->setEnabled(0);
        cbb_subt->clear();
        cbb_au_stream->clear();
        tb_table->clearContents();
        tb_table->setRowCount(0);
        le_file_title->clear();

        getDVDInfo();

    }

}

void dvdtofile::radioFolderAct(bool f){
    if(f){
        le_folder->setEnabled(true);
        cbb_cdrom->setEnabled(false);
        tb_eject->setEnabled(0);
        tb_ref1->setEnabled(0);
        tb_openf->setEnabled(1);
        tb_ref2->setEnabled(1);
        cbb_subt->clear();
        cbb_subt->addItem("None");
        cbb_au_stream->clear();
        cbb_au_stream->addItem("Default");
        tb_table->clearContents();
        tb_table->setRowCount(0);
        le_file_title->clear();

    }
}

void dvdtofile::getDirectory(){
    QString x = QFileDialog::getExistingDirectory(this,"Choose Directory", QDir::homePath());
    if(!x.isEmpty())
        le_folder->setText(x);
}

void dvdtofile::addMountedDrive(){


    foreach (const QStorageInfo &storage, QStorageInfo::mountedVolumes()) {
         if((storage.fileSystemType()=="iso9660" || storage.fileSystemType()=="udf") && storage.bytesTotal()>846960000)

             if(cbb_cdrom->findText(storage.rootPath())==-1)
                cbb_cdrom->addItem(storage.rootPath());
       }
}

void dvdtofile::ejectDrive(){

//    QString program("eject");

//    QStringList arguments;
//    arguments<<cbb_cdrom->currentText();

    QProcess *pr_eject = new QProcess();
    connect(pr_eject,SIGNAL(finished(int)),SLOT(addMountedDrive()));
    pr_eject->start("eject",QStringList()<<cbb_cdrom->currentText());

    cbb_cdrom->clear();
    cbb_subt->clear();
    cbb_au_stream->clear();
    tb_table->clearContents();
    tb_table->setRowCount(0);
    le_file_title->clear();
}


void dvdtofile::getDVDInfo(){

    QString program("lsdvd");
    QStringList path;
    path<<"-v"<<"-a"<<"-s"<<cbb_cdrom->currentText();
    pr_infoDVD = new QProcess();
    connect(pr_infoDVD,SIGNAL(readyReadStandardOutput()),this,SLOT(readDataDVD()));
    connect(pr_infoDVD,SIGNAL(readyReadStandardError()),this,SLOT(readDataDVD()));
    connect(pr_infoDVD,SIGNAL(finished(int)),SLOT(closeLoadDial()));


    pr_infoDVD->start(program, path);

    showLoadDial();

}

void dvdtofile::readDataDVD(){

    QByteArray outputStandard =  pr_infoDVD->readAllStandardOutput();
    QString output=QString::fromLocal8Bit(outputStandard);

    if(!output.isEmpty()){
        qDebug()<<"output"<<output;
        int pos;

//Disc title
         QString disc_title;
         QRegExp regdisc("Disc\\sTitle:\\s(\\w+)");
         pos = regdisc.indexIn(output);
         if(pos>-1)
             disc_title=regdisc.cap(1);

 //title
          QStringList title;
          QRegExp regTitle("\\nTitle:\\s(\\w+)");
          pos=regTitle.indexIn(output);
          while((pos=regTitle.indexIn(output,pos))!=-1){
             title << regTitle.cap(1);
             pos +=regTitle.matchedLength();
          }

          qDebug()<<"title"<<title;


//video size
        QString videoSize;
        QRegExp regVideoSize("Width:\\s(\\d+),\\sHeight:\\s(\\d+)");
        pos=regVideoSize.indexIn(output);
        if(pos>-1){
            videoSize=regVideoSize.cap(1).append("x"+regVideoSize.cap(2));

        }
        qDebug()<<"videoSize"<<videoSize;

//duration
        QStringList duration;
        QRegExp regdur("Length:\\s(\\d+:\\d+:\\d+)");
        pos=regdur.indexIn(output);
        while((pos=regdur.indexIn(output,pos))!=-1){
                    duration << regdur.cap(1);
                    pos += regdur.matchedLength();
                }
        qDebug()<<"duration"<<duration;


//fps
        QString fps;
        QRegExp regFPS("FPS:\\s(\\d+|\\d+\\.\\d+)");
        pos = regFPS.indexIn(output);
        if(pos>-1)
            fps= regFPS.cap(1);

        qDebug()<<"fps"<<fps;


//subtitle
        QStringList subtitle;
        QRegExp regSubt("Subtitle:\\s\\d+,\\sLanguage:\\s(\\w+)");
        pos=regSubt.indexIn(output);
        while ((pos= regSubt.indexIn(output,pos))!=-1) {
            subtitle<<regSubt.cap(1).toUpper();
            pos += regSubt.matchedLength();
        }

        QStringList xsub;
        for(int c=0;c<subtitle.count();c++){
            if(!xsub.contains(subtitle.at(c)))
                xsub<<subtitle.at(c);
        }
        qDebug()<<"subt"<<xsub;

//audio
        QStringList audioStream;//is this effective? the pattern is too long.
        QRegExp regAudio("Audio:\\s\\d,\\s(Language:\\s\\w+)\\s-\\s\\w+,\\sFormat:\\s(\\w+),\\sFrequency:\\s\\d+,\\sQuantization:\\s\\w+,\\sChannels:\\s(\\d)");
        pos=regAudio.indexIn(output);
        while((pos=regAudio.indexIn(output,pos))!=-1){
           QString ch = regAudio.cap(3);
           ch.replace("2", "stereo");
           audioStream<<QString().append(regAudio.cap(2)+"("+ch+")"+regAudio.cap(1));
           pos += regAudio.matchedLength();
        }
//avoid double item
        QStringList x;
        for(int i=0;i<audioStream.count();i++){
        if(!x.contains(audioStream.at(i)))
            x<<audioStream.at(i);

        }
        qDebug()<<"audio"<<x;

//apply info
        videoInfo->setText("video size: "+videoSize+" FPS: "+fps);
        cbb_subt->clear();
        cbb_subt->addItem("None");

        cbb_subt->addItems(xsub);
        cbb_au_stream->clear();
        cbb_au_stream->addItem("Default");
        cbb_au_stream->addItems(x);

        le_file_title->setText(disc_title);

        tb_checkAll->setEnabled(1);
        tb_uncheckAll->setEnabled(1);
        pb_convert->setEnabled(1);
        pb_set_range->setEnabled(1);

        for(int t=0;t<title.count();t++){
            tb_table->setRowCount(title.count());

            QTableWidgetItem *item_title = new QTableWidgetItem();
            item_title->setText(title.at(t));
            item_title->setCheckState(Qt::Unchecked);
            //item_title->setTextAlignment(Qt::AlignCenter);

            tb_table->setItem(t,0,item_title);
            QTableWidgetItem *item_length = new QTableWidgetItem();
            item_length->setText(duration.at(t));
            item_length->setTextAlignment(Qt::AlignCenter);
            tb_table->setItem(t,1,item_length);
          }//en for

    }

}

void dvdtofile::uncheckAllTitle(){
    for(int i=0;i<tb_table->rowCount();i++){
    tb_table->item(i,0)->setCheckState(Qt::Unchecked);
    }
}

void dvdtofile::checkAllTitle(){

    for(int i=0;i<tb_table->rowCount();i++){

        tb_table->item(i,0)->setCheckState(Qt::Checked);

    }
}

void dvdtofile::showLoadDial(){

     pd_load = new QProgressDialog();
     pd_load->setRange(0,0);
     pd_load->setModal(1);
     pd_load->setLabelText("Please wait... reading DVD data");
     pd_load->setCancelButton(0);
     pd_load->setWindowFlags(Qt::FramelessWindowHint);
     pd_load->show();

}

void dvdtofile::closeLoadDial(){
    pd_load->accept();
}
