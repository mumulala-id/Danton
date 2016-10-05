#include "mediainfo.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QDir>
#include <QLabel>
#include <QGroupBox>
#include <QClipboard>
#include <QApplication>

mediainfo::mediainfo(QWidget *parent) :
    QDialog(parent)
{

    QLabel *l_ikon = new QLabel();
    l_ikon->setText("?ikon");
    l_ikon->setFixedWidth(60);

    le_filename = new QLineEdit();
    QPushButton *browse_button = new QPushButton(tr("Browse"));
    connect(browse_button, SIGNAL(clicked(bool)), this, SLOT(openFileMediaInfo()));
    QHBoxLayout *lo_nama_file = new QHBoxLayout;

    lo_nama_file->addWidget(l_ikon);
    lo_nama_file->addWidget(le_filename);
    lo_nama_file->addWidget(browse_button);

    QGroupBox *gr_file = new QGroupBox();
    gr_file->setStyleSheet("QGroupBox{border: 1px solid #ccc;border-radius:8px;margin-top:0.5em}");
    gr_file->setLayout(lo_nama_file);


   te_output = new QTextEdit();
   te_output->ensureCursorVisible();
   te_output->setLineWrapMode(QTextEdit::NoWrap);

    QFont font = QFont("Courier");
    font.setStyleHint(QFont::Monospace);
    font.setPointSize(8);
    font.setFixedPitch(true);
    te_output->setFont(font);

    QHBoxLayout *lo_bottom = new QHBoxLayout();

    QPushButton *pb_clipboard = new QPushButton("Clipboard");
    pb_clipboard->setFixedWidth(150);
    connect(pb_clipboard,SIGNAL(clicked(bool)),this,SLOT(toClipboard()));

    QPushButton *pb_ok = new QPushButton("OK");
    pb_ok->setFixedWidth(150);
    connect(pb_ok,SIGNAL(clicked(bool)),this,SLOT(accept()));

    lo_bottom->addWidget(pb_clipboard,0,Qt::AlignLeft);
    lo_bottom->addWidget(pb_ok,Qt::AlignRight);

    QVBoxLayout *lo_media_info = new QVBoxLayout();
    lo_media_info->addWidget(gr_file);
    lo_media_info->addWidget(te_output);
    lo_media_info->addLayout(lo_bottom);
    this->setLayout(lo_media_info);
    this->setFixedSize(780,460);
    this->setWindowTitle("media info");

}

void mediainfo::openFileMediaInfo(){

    QString file = QFileDialog::getOpenFileName(this,"Choose files", QDir::homePath(), "All file(*.*)");
    if(!file.isEmpty()){
    le_filename->setText(file);

   proceed();
    }
}


void mediainfo::proceed(){

    get_info_media = new QProcess();
    get_info_media->start("mediainfo", QStringList()<<le_filename->text());

    connect(get_info_media, SIGNAL(readyReadStandardOutput()), this, SLOT(readMediaOutput()));
    connect(get_info_media,SIGNAL(readyReadStandardError()), this, SLOT(readMediaOutput()));

}

void mediainfo::readMediaOutput()
{

   te_output->setText(get_info_media->readAllStandardOutput());

}

void mediainfo::setFile(QString f){

    le_filename->setText(f);
    proceed();

}

void mediainfo::toClipboard(){

    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(te_output->toPlainText());

}
