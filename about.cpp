#include "about.h"
#include <QFile>
#include <QTextStream>
#include <QPushButton>

about::about(QWidget *parent) :
    QDialog(parent)
{

    QVBoxLayout *lo_tentang = new QVBoxLayout(this);
    stack_tentang = new QStackedLayout;

    QFrame *fr_danton = new QFrame;
    QGridLayout *lo_danton = new QGridLayout(fr_danton);
    QVBoxLayout *lo_logo = new QVBoxLayout;
    QLabel *label_logo = new QLabel;
    label_logo->setPixmap(QPixmap(":/usr/share/danton/icons/danton.png"));
    lo_logo->addWidget(label_logo);

    QVBoxLayout *lo_description = new QVBoxLayout;
    QLabel *l_description = new QLabel;
    l_description->setText(tr("<font size=32>Danton Converter</font><br/>"
                                 "<font size=18>0.0.2 Alpha</font><br/><br/>"
                                 "Danton Converter adalah aplikasi bebas dan sumber terbuka untuk mengubah berbagai jenis berkas multimedia berdasarkan mesin FFmpeg dan Imagemagick"));
    l_description->setWordWrap(true);
    l_description->setAlignment(Qt::AlignTop);
    lo_description->addWidget(l_description);

    lo_danton->addLayout(lo_logo,0,0);
    lo_danton->addLayout(lo_description,0,1);

    fr_danton->setLayout(lo_danton);

// ----------------- frame author
    QFrame *fr_author = new QFrame;
    QVBoxLayout *lo_author = new QVBoxLayout;

    QTextEdit *teks_author = new QTextEdit;
    teks_author->setText("Tim danton memberitahukan siapa saja yang sudah berkontribusi :<br/><br/>"
                         "Programming------------------<br/>"
                         "Muhammad Mukharom(mumulala)<br/><br/>"
                         //your name should be here :D
                         "Donatur----------------------<br/>");
    teks_author->setReadOnly(true);
    lo_author->addWidget(teks_author);
    fr_author->setLayout(lo_author);


    //----------------frame lisensi
    QFrame *fr_lisensi = new QFrame;
    QVBoxLayout *lo_lisensi = new QVBoxLayout;
    QTextEdit *teks_lisensi = new QTextEdit;

    QString lisensi_txt = ":/usr/share/danton/license.txt";
    QFile file(lisensi_txt);
    file.open(QFile::ReadOnly | QFile::Text);

    QTextStream ReadFile(&file);

    teks_lisensi->setText(ReadFile.readAll());
    teks_lisensi->setReadOnly(true);
    lo_lisensi->addWidget(teks_lisensi);

    fr_lisensi->setLayout(lo_lisensi);
    //-----------------frame credit

    QFrame *fr_credit = new QFrame;
    QVBoxLayout *lo_credit = new QVBoxLayout;

    QTextEdit *te_credit = new QTextEdit;
    te_credit->setText("Qt<br/>"
                         "FFmpeg - Copyright(c) 2000-2015  the FFmpeg developer- LGPL2.1 or later<br/>"
                         "Imagemagick - Copyright(c) 1999-2015 Imagemagick Studio LLC - ImageMagick<br/>"
                         "FormatJunkie - Copyright © 2012 by Alex Solanos and Leon Vytanos<br/>"
                         "MediaInfo<br/>"
                         "libdvdread<br/>"
                         "HandBrakeCLI<br/>"
                         "ABCDE");
    te_credit->setReadOnly(true);
    lo_credit->addWidget(te_credit);
    fr_credit->setLayout(lo_credit);

//------------------
    QHBoxLayout *lo_tombol = new QHBoxLayout;

    QPushButton *pb_author = new QPushButton("Author");

    connect(pb_author, SIGNAL(clicked(bool)), this, SLOT(on_btn_author_clicked()));

    QPushButton *pb_lisensi = new QPushButton("Lisensi");

    connect(pb_lisensi, SIGNAL(clicked(bool)), this, SLOT(on_btn_license_clicked()));

    QPushButton *pb_credit = new QPushButton("Credit");

    connect(pb_credit, SIGNAL(clicked(bool)), this, SLOT(on_btn_credit_clicked()));

    lo_tombol->addWidget(pb_author);
    lo_tombol->addWidget(pb_lisensi);
    lo_tombol->addWidget(pb_credit);

    stack_tentang->addWidget(fr_danton);
    stack_tentang->addWidget(fr_author);
    stack_tentang->addWidget(fr_lisensi);
    stack_tentang->addWidget(fr_credit);


    lo_tentang->addLayout(stack_tentang);
    lo_tentang->addLayout(lo_tombol);

    setLayout(lo_tentang);
    setFixedSize(600,400);
    setWindowTitle("About Danton");


}
about::~about(){

}

void about::on_btn_author_clicked()
{
    stack_tentang->setCurrentIndex(1);
}
void about::on_btn_license_clicked()
{
    stack_tentang->setCurrentIndex(2);
}
void about::on_btn_credit_clicked()
{
    stack_tentang->setCurrentIndex(3);
}
