#include "musiccdtofile.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QToolButton>
#include <QPushButton>
#include <QHeaderView>
#include <QTableWidget>
#include <QLineEdit>

musiccdtofile::musiccdtofile(QWidget *parent) :
    QDialog(parent)
{

    QVBoxLayout *lo_music_to_file = new QVBoxLayout();

    QGroupBox *gb_top = new QGroupBox();
    gb_top->setTitle("CD Driver");

    QHBoxLayout *lo_top = new QHBoxLayout();

    QLabel *l_ikon = new QLabel();
    l_ikon->setText("?ikon");
    l_ikon->setFixedWidth(60);

    QComboBox *cbb_driver = new QComboBox();
    cbb_driver->setFixedWidth(250);
    cbb_driver->addItem("driver");

    QToolButton *tb_eject = new QToolButton();
    tb_eject->setIcon(QIcon::fromTheme("media-eject"));

    QToolButton *tb_refresh = new QToolButton();
    tb_refresh->setIcon(QIcon::fromTheme("gtk-refresh"));

    QLabel *l_ikon2 = new QLabel();
    l_ikon2->setText("?ikon2");
    l_ikon2->setFixedWidth(60);

    QPushButton *pb_convert = new QPushButton("Convert");
    pb_convert->setEnabled(false);
    pb_convert->setFixedWidth(180);

    lo_top->addWidget(l_ikon,Qt::AlignLeft);
    lo_top->addWidget(cbb_driver,Qt::AlignLeft);
    lo_top->addWidget(tb_eject,Qt::AlignLeft);
    lo_top->addWidget(tb_refresh,0,Qt::AlignLeft);
    lo_top->addWidget(l_ikon2);
    lo_top->addWidget(pb_convert,Qt::AlignRight);

    gb_top->setLayout(lo_top);
    gb_top->setStyleSheet("QGroupBox{border: 1px solid #ccc;border-radius:8px;margin-top:0.5em}"
                             "QGroupBox::title{subcontrol-origin:margin;left:10px;padding: 0 3px 0 3px}");

    //-------------

    QHBoxLayout *lo_bottom =new QHBoxLayout();

    QVBoxLayout *lo_bottom_left = new QVBoxLayout();

    QToolButton *tb_checkAll = new QToolButton();
    tb_checkAll->setIcon(QIcon::fromTheme("dialog-yes"));

    QToolButton *tb_uncheckAll = new QToolButton();
    tb_uncheckAll->setIcon(QIcon::fromTheme("dialog-no"));

    QComboBox *cbb_format = new QComboBox();
    cbb_format->addItem("mp3");
    cbb_format->setFixedWidth(100);

    QHBoxLayout *lo_bottom_left_top = new QHBoxLayout();
    lo_bottom_left_top->addWidget(tb_checkAll, Qt::AlignLeft);
    lo_bottom_left_top->addWidget(tb_uncheckAll,0, Qt::AlignLeft);
    lo_bottom_left_top->addWidget(cbb_format, Qt::AlignRight);

    QTableWidget *tw_table = new QTableWidget();
    tw_table->setColumnCount(3);
    tw_table->setHorizontalHeaderLabels(QString("Title;Duration;Range").split(";"));
    tw_table->verticalHeader()->hide();
    tw_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    tw_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    lo_bottom_left->addLayout(lo_bottom_left_top);
    lo_bottom_left->addWidget(tw_table);

    lo_bottom->addLayout(lo_bottom_left);

    //--bottom right
    QVBoxLayout *lo_bottom_right = new QVBoxLayout();


    QPushButton *pb_quality = new QPushButton();
    pb_quality->setText("High quality");

    QLabel *l_p = new QLabel();
    l_p->setText("?pixmap");
    l_p->setFixedSize(100,40);

    QLineEdit *le_edit = new QLineEdit();
    le_edit->setText("Track");

    QPushButton *pb_rename = new QPushButton("Rename track");

    lo_bottom_right->addWidget(pb_quality);
    lo_bottom_right->addWidget(l_p);
    lo_bottom_right->addWidget(le_edit);
    lo_bottom_right->addWidget(pb_rename);
    lo_bottom_right->setContentsMargins(50,0,50,0);

    QWidget *w_right = new QWidget();

    w_right->setLayout(lo_bottom_right);
    w_right->setFixedWidth(300);

    lo_bottom->addWidget(w_right);

    QGroupBox *gb_bottom = new QGroupBox();
    gb_bottom->setTitle("Output setting");
    gb_bottom->setLayout(lo_bottom);
    gb_bottom->setStyleSheet("QGroupBox{border: 1px solid #ccc;border-radius:8px;margin-top:0.5em}"
                                                   "QGroupBox::title{subcontrol-origin:margin;left:10px;padding: 0 3px 0 3px}");

    lo_music_to_file->addWidget(gb_top);
    lo_music_to_file->addWidget(gb_bottom);
    setLayout(lo_music_to_file);
    setFixedSize(750,450);
    setWindowTitle("Music CD to Audio File");
}

