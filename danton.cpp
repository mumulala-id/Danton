/*Danton converter
A tool for converting your media files to
all the popular formats
Copyright © 2015 by Muhammad Mukharom

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 3
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.*/



#include "danton.h"
#include "dvdtofile.h"
#include "disctoiso.h"
#include "dialogconversion.h"
#include "musiccdtofile.h"
#include "mediainfo.h"
#include <QDir>
#include <QIcon>
#include <QSettings>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QHeaderView>
#include <QStatusBar>
#include <QFileDialog>
#include <QDebug>

using namespace std;

int g_mediaType;
QString g_target_format;

QString globpro_string;
QString g_output_path;
//QString last_dir;

bool delete_original=false;
bool stop_button_clicked=false;
bool globpro_hasbeendeleted=false;
bool append_name=false;
bool open_folder_at_finish=false;



//----------
int error_count=0;
int current_file=0;
int sudah_komplit=0;

int kualitas_gambar=0;

bool conversion_process_on=false;
bool save_to_source=false;

bool overwrite_file=false;
bool poweroff_computer=false;
bool show_noty_succes=false;
bool show_noty_error=false;

float duration_secs=0;
int current_durration=0;

QString all_errors="";
QString current_file_errors="";

danton::danton(QWidget *parent) :
    QMainWindow(parent)
{
    menuNtoolbar();
    readSetting();
    createCentralWidget();
    buatStatusBar();

    setWindowTitle("Danton converter");
}


void danton::menuNtoolbar()
{

    start_action = new QAction(QIcon::fromTheme("stock_media-play"),tr("Start"), this);
    start_action->setEnabled(false);
    connect(start_action, SIGNAL(triggered()), this, SLOT(onBtnStartClicked()));

    stop_action = new QAction(QIcon::fromTheme("stock_media-stop"),tr("Stop"), this);
    stop_action->setEnabled(false);
    connect(stop_action, SIGNAL(triggered(bool)), this,SLOT(onStopBtnClicked()));

    clear_list_action = new QAction(QIcon::fromTheme("edit-clear"),tr("Clear"), this);
    clear_list_action->setEnabled(false);
    connect(clear_list_action, SIGNAL(triggered()), this, SLOT(clearMainTable()));

    delete_action = new QAction(QIcon::fromTheme("edit-delete"),tr("Delete"), this);
    delete_action->setEnabled(false);
    connect(delete_action,SIGNAL(triggered(bool)),this,SLOT(deleteRowMainTable()));

    pick_folder_action = new QAction(QIcon::fromTheme("folder"),tr("Output folder"), this);
    connect(pick_folder_action, SIGNAL(triggered()), this, SLOT(output_dir()));

    preference_action = new QAction(QIcon::fromTheme("stock_properties"),tr("Option"), this);
    connect(preference_action, SIGNAL(triggered()),this, SLOT(settingDialog()));
    
    QAction *exit_action = new QAction(QIcon::fromTheme("window-close"),tr("Quit"), this);
    exit_action->setShortcut(tr("Ctrl+Q"));
    connect(exit_action, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
    
    QAction *help_action = new QAction(QIcon::fromTheme("help"),tr("Bantuan"), this);
    QAction *about_action = new QAction(QIcon::fromTheme("info"),tr("Tentang"), this);
    connect(about_action, SIGNAL(triggered()), this, SLOT(showAbout()));


    QMenu *main_menu;
    main_menu = menuBar()->addMenu("Tugas");
    main_menu->addAction(start_action);
    main_menu->addAction(stop_action);
    main_menu->addAction(preference_action);
    main_menu->addSeparator();
    main_menu->addAction(exit_action);



    QMenu *help_menu;
    help_menu = menuBar()->addMenu("Bantuan");
    help_menu->addAction(help_action);
    help_menu->addAction(about_action);


    QToolBar *tool_bar = addToolBar("Main");
    tool_bar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    tool_bar->setMovable(false);
    tool_bar->setContextMenuPolicy(Qt::PreventContextMenu);
    tool_bar->addAction(pick_folder_action);
    tool_bar->addAction(preference_action);
    tool_bar->addSeparator();
    tool_bar->addAction(delete_action);
    tool_bar->addAction(clear_list_action);
    tool_bar->addSeparator();
    tool_bar->addAction(stop_action);
    tool_bar->addAction(start_action);
}

void danton::buildIcon(QToolButton *x, const QString &nm, const QString &icnm){
// icon for file format
    QSize icsz(72,72);
    QSize tbtnsz(100, 100);

       x->setFixedSize(tbtnsz);
       x->setIcon(QIcon::fromTheme(icnm));
       x->setIconSize(icsz);
       x->setText(nm);
       x->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

}

void danton::createCategoryBtn(QPushButton *p,const QString &i, const QString &x){
//create QPushbutton with icon left align and text center align, this is for categoy button
    QHBoxLayout *l = new QHBoxLayout(p);
    QLabel *lbIc = new QLabel(p);

    lbIc->setPixmap(QPixmap(i).scaled(24,24,Qt::KeepAspectRatio,Qt::SmoothTransformation));

    l->addWidget(lbIc);
    l->setContentsMargins(10,4,4,4);
    p->setLayout(l);
    p->setText(x);
    p->setFixedHeight(32);
}

void danton::createCentralWidget(){

    QWidget *central_widget = new QWidget(this);

    QHBoxLayout *lo_central_widget = new QHBoxLayout(central_widget);
    lo_central_widget->setMargin(0);
    lo_central_widget->setSpacing(0);

    QFrame *fr_left_col = new QFrame(central_widget);
    fr_left_col->setFixedWidth(380);


    //isi kiri
    QVBoxLayout *lo_col_icon = new QVBoxLayout(fr_left_col);
    lo_col_icon->setSpacing(0);
    lo_col_icon->setMargin(0);

    QPushButton *btn_video_cat = new QPushButton(this);

    createCategoryBtn(btn_video_cat,":/usr/share/danton/icons/video.png","Video");

    connect(btn_video_cat,SIGNAL(clicked(bool)), this, SLOT(on_btn_cat_video_clicked()));
    //widget isi ikon2 video

    wg_ic_video = new QWidget(central_widget);

    QGridLayout *lo_ic_video = new QGridLayout(wg_ic_video);

            QToolButton *btnVmp4 = new QToolButton(this);
            buildIcon(btnVmp4,"-> MP4","video-x-generic");
            connect(btnVmp4, SIGNAL(clicked()),this, SLOT(on_btnV_mp4_clicked()));
            connect(btnVmp4, SIGNAL(clicked()),this, SLOT(openDialogConv()));

            QToolButton *btnVavi = new QToolButton(this);
            buildIcon(btnVavi,"-> AVI","video-x-generic");
            connect(btnVavi, SIGNAL(clicked()),this, SLOT(on_btnV_avi_clicked()));
            connect(btnVavi, SIGNAL(clicked()),this, SLOT(openDialogConv()));

            QToolButton *btnV3gp = new QToolButton(this);
            buildIcon(btnV3gp,"-> 3GP","video-x-generic");
            connect(btnV3gp, SIGNAL(clicked()),this, SLOT(on_btnV_3gp_clicked()));
            connect(btnV3gp, SIGNAL(clicked()),this, SLOT(openDialogConv()));

            QToolButton *btnVwebm = new QToolButton(this);
            buildIcon(btnVwebm,"-> WEBM","video-x-generic");
            connect(btnVwebm, SIGNAL(clicked()),this, SLOT(on_btnV_webm_clicked()));
            connect(btnVwebm, SIGNAL(clicked()),this, SLOT(openDialogConv()));

            QToolButton *btnVgif = new QToolButton(this);
            buildIcon(btnVgif,"-> GIF","video-x-generic");
            connect(btnVgif, SIGNAL(clicked()),this, SLOT(on_btnV_gif_clicked()));
            connect(btnVgif, SIGNAL(clicked()),this, SLOT(openDialogConv()));

            QToolButton *btnVwmv = new QToolButton(this);
            buildIcon(btnVwmv,"-> WMV","video-x-generic");
            connect(btnVwmv, SIGNAL(clicked()),this, SLOT(on_btnV_wmv_clicked()));
            connect(btnVwmv, SIGNAL(clicked()),this, SLOT(openDialogConv()));

            QToolButton *btnVmkv = new QToolButton(this);
            buildIcon(btnVmkv,"-> MKV","video-x-generic");
            connect(btnVmkv, SIGNAL(clicked()),this, SLOT(on_btnV_mkv_clicked()));
            connect(btnVmkv, SIGNAL(clicked()),this, SLOT(openDialogConv()));

            QToolButton *btnVmpg = new QToolButton(this);
            buildIcon(btnVmpg,"-> MPG","video-x-generic");
            connect(btnVmpg, SIGNAL(clicked()),this, SLOT(on_btnV_mpg_clicked()));
            connect(btnVmpg, SIGNAL(clicked()),this, SLOT(openDialogConv()));

            QToolButton *btnVvob = new QToolButton(this);
            buildIcon(btnVvob,"-> VOB","video-x-generic");
            connect(btnVvob, SIGNAL(clicked()),this, SLOT(on_btnV_vob_clicked()));
            connect(btnVvob, SIGNAL(clicked()),this, SLOT(openDialogConv()));

            QToolButton *btnVmov = new QToolButton(this);
            buildIcon(btnVmov,"-> MOV","video-x-generic");
            connect(btnVmov, SIGNAL(clicked()),this, SLOT(on_btnV_mov_clicked()));
            connect(btnVmov, SIGNAL(clicked()),this, SLOT(openDialogConv()));

            QToolButton *btnVflv = new QToolButton(this);
            buildIcon(btnVflv,"-> FLV","video-x-generic");
            connect(btnVflv, SIGNAL(clicked()),this, SLOT(on_btnV_flv_clicked()));
            connect(btnVflv, SIGNAL(clicked()),this, SLOT(openDialogConv()));

            QToolButton *btnVswf = new QToolButton(this);
            buildIcon(btnVswf,"-> SWF","video-x-generic");
            connect(btnVswf, SIGNAL(clicked()),this, SLOT(on_btnV_swf_clicked()));
            connect(btnVswf, SIGNAL(clicked()),this, SLOT(openDialogConv()));
            //btnV ikon

            lo_ic_video->addWidget(btnVmp4, 0, 1);
            lo_ic_video->addWidget(btnVavi, 0, 2);
            lo_ic_video->addWidget(btnV3gp, 0, 3);
            lo_ic_video->addWidget(btnVwebm, 1, 1);
            lo_ic_video->addWidget(btnVmkv, 1, 2);
            lo_ic_video->addWidget(btnVgif, 1, 3);
            lo_ic_video->addWidget(btnVwmv, 2, 1);
            lo_ic_video->addWidget(btnVmpg, 2, 2);
            lo_ic_video->addWidget(btnVvob, 2, 3);
            lo_ic_video->addWidget(btnVmov, 3, 1);
            lo_ic_video->addWidget(btnVflv, 3, 2);
            lo_ic_video->addWidget(btnVswf, 3, 3);
            lo_ic_video->setHorizontalSpacing(0);

            wg_ic_video->setLayout(lo_ic_video);
            wg_ic_video->setVisible(sh_video);

// audio------------------------
        QPushButton *btn_audio_cat = new QPushButton(central_widget);
        createCategoryBtn(btn_audio_cat,":/usr/share/danton/icons/audio.png","Audio");

        connect(btn_audio_cat,SIGNAL(clicked(bool)), this, SLOT(on_btn_cat_audio_clicked()));

            wg_ic_audio = new QWidget(central_widget);

            QGridLayout *lo_ic_audio = new QGridLayout(wg_ic_audio);

            QToolButton *btnAmp3 = new QToolButton(this);
            buildIcon(btnAmp3, "-> MP3","audio-x-generic");
            connect(btnAmp3, SIGNAL(clicked()),this, SLOT(on_btnA_mp3_clicked()));
            connect(btnAmp3, SIGNAL(clicked()),this, SLOT(openDialogConv()));

            QToolButton *btnAwma = new QToolButton(this);
            buildIcon(btnAwma,"-> WMA","audio-x-generic");
            connect(btnAwma, SIGNAL(clicked()),this, SLOT(on_btnA_wma_clicked()));
            connect(btnAwma, SIGNAL(clicked()),this, SLOT(openDialogConv()));

            QToolButton *btnAape = new QToolButton(this);
            buildIcon(btnAape, "-> APE","audio-x-generic");
            connect(btnAape, SIGNAL(clicked()),this, SLOT(on_btnA_ape_clicked()));
            connect(btnAape, SIGNAL(clicked()),this, SLOT(openDialogConv()));

            QToolButton *btnAflac = new QToolButton(this);
            buildIcon(btnAflac,"-> FLAC","audio-x-generic");
            connect(btnAflac, SIGNAL(clicked()),this, SLOT(on_btnA_flac_clicked()));
            connect(btnAflac, SIGNAL(clicked()),this, SLOT(openDialogConv()));

            QToolButton *btnAaac = new QToolButton(this);
            buildIcon(btnAaac,"-> AAC","audio-x-generic");
            connect(btnAaac, SIGNAL(clicked()),this, SLOT(on_btnA_aac_clicked()));
            connect(btnAaac, SIGNAL(clicked()),this, SLOT(openDialogConv()));

            QToolButton *btnAmmf = new QToolButton(this);
            buildIcon(btnAmmf,"-> MMF","audio-x-generic");
            connect(btnAmmf, SIGNAL(clicked()),this, SLOT(on_btnA_mmf_clicked()));
            connect(btnAmmf, SIGNAL(clicked()),this, SLOT(openDialogConv()));

            QToolButton *btnAamr = new QToolButton(this);
            buildIcon(btnAamr,"-> AMR","audio-x-generic");
            connect(btnAamr, SIGNAL(clicked()),this, SLOT(on_btnA_amr_clicked()));
            connect(btnAamr, SIGNAL(clicked()),this, SLOT(openDialogConv()));

            QToolButton *btnAm4a = new QToolButton(this);
            buildIcon(btnAm4a,"-> M4A","audio-x-generic");
            connect(btnAm4a, SIGNAL(clicked()),this, SLOT(on_btnA_m4a_clicked()));
            connect(btnAm4a, SIGNAL(clicked()),this, SLOT(openDialogConv()));

            QToolButton *btnAm4r = new QToolButton(this);
            buildIcon(btnAm4r,"-> M4R","audio-x-generic");
            connect(btnAm4r, SIGNAL(clicked()),this, SLOT(on_btnA_m4r_clicked()));
            connect(btnAm4r, SIGNAL(clicked()),this, SLOT(openDialogConv()));

            QToolButton *btnAogg = new QToolButton(this);
            buildIcon(btnAogg,"-> OGG","audio-x-generic");
            connect(btnAogg, SIGNAL(clicked()),this, SLOT(on_btnA_ogg_clicked()));
            connect(btnAogg, SIGNAL(clicked()),this, SLOT(openDialogConv()));

            QToolButton *btnAwav = new QToolButton(this);
            buildIcon(btnAwav,"-> WAV","audio-x-generic");
            connect(btnAwav, SIGNAL(clicked()),this, SLOT(on_btnA_wav_clicked()));
            connect(btnAwav, SIGNAL(clicked()),this, SLOT(openDialogConv()));

            QToolButton *btnAmp2 = new QToolButton(this);
            buildIcon(btnAmp2,"-> MP2","audio-x-generic");
            connect(btnAmp2, SIGNAL(clicked()),this, SLOT(on_btnA_mp2_clicked()));
            connect(btnAmp2, SIGNAL(clicked()),this, SLOT(openDialogConv()));

    lo_ic_audio->addWidget(btnAmp3,  1, 1);
    lo_ic_audio->addWidget(btnAwma,  1, 2);
    lo_ic_audio->addWidget(btnAape,  1, 3);
    lo_ic_audio->addWidget(btnAflac, 2, 1);
    lo_ic_audio->addWidget(btnAaac,  2, 2);
    lo_ic_audio->addWidget(btnAmmf,  2, 3);
    lo_ic_audio->addWidget(btnAm4a,  3, 1);
    lo_ic_audio->addWidget(btnAm4r,  3, 2);
    lo_ic_audio->addWidget(btnAamr,  3, 3);
    lo_ic_audio->addWidget(btnAogg,  4, 1);
    lo_ic_audio->addWidget(btnAwav,  4, 2);
    lo_ic_audio->addWidget(btnAmp2,  4, 3);


    wg_ic_audio->setLayout(lo_ic_audio);
    wg_ic_audio->setVisible(sh_audio);

// image----------------------------
    QPushButton *btn_cat_img = new QPushButton(this);
    createCategoryBtn(btn_cat_img,":/usr/share/danton/icons/images.png","Picture");
    connect(btn_cat_img, SIGNAL(clicked()), this, SLOT(on_btn_cat_img_clicked()));

    wg_ic_image = new QWidget(central_widget);

            QToolButton *btnPwebp = new QToolButton(this);
            buildIcon(btnPwebp,"-> WEBP","image-x-generic");
            connect(btnPwebp, SIGNAL(clicked()),this, SLOT(on_btnP_webp_clicked()));
            connect(btnPwebp, SIGNAL(clicked()),this, SLOT(openDialogConv()));

            QToolButton *btnPjpg = new QToolButton(this);
            buildIcon(btnPjpg,"-> JPG","image-x-generic");
            connect(btnPjpg, SIGNAL(clicked()),this, SLOT(on_btnP_jpg_clicked()));
            connect(btnPjpg, SIGNAL(clicked()),this, SLOT(openDialogConv()));

            QToolButton *btnPpng = new QToolButton(this);
            buildIcon(btnPpng,"-> PNG","image-x-generic");
            connect(btnPpng, SIGNAL(clicked()), this, SLOT(on_btnP_png_clicked()));
            connect(btnPpng, SIGNAL(clicked()), this, SLOT(openDialogConv()));

            QToolButton *btnPico = new QToolButton(this);
            buildIcon(btnPico,"-> ICO","image-x-generic");
            connect(btnPico, SIGNAL(clicked()), this, SLOT(on_btnP_ico_clicked()));
            connect(btnPico, SIGNAL(clicked()), this, SLOT(openDialogConv()));

            QToolButton *btnPbmp = new QToolButton(this);
            buildIcon(btnPbmp,"-> BMP","image-x-generic");
            connect(btnPbmp, SIGNAL(clicked()), this, SLOT(on_btnP_bmp_clicked()));
            connect(btnPbmp, SIGNAL(clicked()), this, SLOT(openDialogConv()));

            QToolButton *btnPgif = new QToolButton(this);
            buildIcon(btnPgif,"-> GIF","image-x-generic");
            connect(btnPgif, SIGNAL(clicked()), this, SLOT(on_btnP_gif_clicked()));
            connect(btnPgif, SIGNAL(clicked()), this, SLOT(openDialogConv()));

            QToolButton *btnPtif = new QToolButton(this);
            buildIcon(btnPtif,"-> TIF","image-x-generic");
            connect(btnPtif, SIGNAL(clicked()), this, SLOT(on_btnP_tif_clicked()));
            connect(btnPtif, SIGNAL(clicked()), this, SLOT(openDialogConv()));

            QToolButton *btnPpcx = new QToolButton(this);
            buildIcon(btnPpcx,"-> PCX","image-x-generic");
            connect(btnPpcx, SIGNAL(clicked()), this, SLOT(on_btnP_pcx_clicked()));
            connect(btnPpcx, SIGNAL(clicked()), this, SLOT(openDialogConv()));

            QToolButton *btnPtga = new QToolButton(this);
            buildIcon(btnPtga,"-> TGA","image-x-generic");
            connect(btnPtga, SIGNAL(clicked()), this, SLOT(on_btnP_tga_clicked()));
            connect(btnPtga, SIGNAL(clicked()), this, SLOT(openDialogConv()));

    QGridLayout *lo_col_image = new QGridLayout(wg_ic_image);

    lo_col_image->addWidget(btnPwebp, 0, 0);
    lo_col_image->addWidget(btnPjpg,  0, 1);
    lo_col_image->addWidget(btnPpng,  0, 2);
    lo_col_image->addWidget(btnPico,  1, 0);
    lo_col_image->addWidget(btnPbmp,  1, 1);
    lo_col_image->addWidget(btnPgif,  1, 2);
    lo_col_image->addWidget(btnPtif,  2, 0);
    lo_col_image->addWidget(btnPpcx,  2, 1);
    lo_col_image->addWidget(btnPtga,  2, 2);


    wg_ic_image->setLayout(lo_col_image);
    wg_ic_image->setVisible(sh_pict);

// CD/DVD-------------------------------------
    QPushButton *btn_cat_cd = new QPushButton();
    createCategoryBtn(btn_cat_cd,":/usr/share/danton/icons/cd.png","ROM Device/DVD/CD/ISO");
    connect(btn_cat_cd, SIGNAL(clicked()), this, SLOT(on_btn_cat_cd_clicked()));

    wg_ic_cd = new QWidget;

    QVBoxLayout *lo_wg_cd = new QVBoxLayout;

    QToolButton *btn_dvd_to_file = new QToolButton;
    btn_dvd_to_file->setText("DVD to Video file");
    btn_dvd_to_file->setIcon(QIcon::fromTheme("media-cdrom"));
    btn_dvd_to_file->setIconSize(QSize(72,72));
    btn_dvd_to_file->setFixedSize(200,100);
    btn_dvd_to_file->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    connect(btn_dvd_to_file,SIGNAL(clicked(bool)),this,SLOT(dvdToFile()));

    QToolButton *btn_cd_to_file = new QToolButton;
    btn_cd_to_file->setText("Music CD to Audio file");
    btn_cd_to_file->setIcon(QIcon::fromTheme("media-cdrom"));
    btn_cd_to_file->setIconSize(QSize(72,72));
    btn_cd_to_file->setFixedSize(200,100);
    btn_cd_to_file->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    connect(btn_cd_to_file,SIGNAL(clicked(bool)),this,SLOT(cdToFile()));

    QToolButton *btn_disc_to_file = new QToolButton;
    btn_disc_to_file->setText("DVD/CD to ISO/CSO");
    btn_disc_to_file->setIcon(QIcon::fromTheme("media-cdrom"));
    btn_disc_to_file->setIconSize(QSize(72,72));
    btn_disc_to_file->setFixedSize(200,100);
    btn_disc_to_file->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    connect(btn_disc_to_file,SIGNAL(clicked(bool)),this,SLOT(discToISO()));

    QToolButton *btn_iso_to_cso = new QToolButton;
    btn_iso_to_cso->setText("ISO to CSO");
    btn_iso_to_cso->setIcon(QIcon::fromTheme("media-cdrom"));
    btn_iso_to_cso->setIconSize(QSize(72,72));
    btn_iso_to_cso->setFixedSize(200,100);
    btn_iso_to_cso->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    connect(btn_iso_to_cso, SIGNAL(clicked(bool)),this,SLOT(onBtnCSOClicked()));
    connect(btn_iso_to_cso,SIGNAL(clicked(bool)),this,SLOT(openDialogConv()));


    lo_wg_cd->addWidget(btn_dvd_to_file);
    lo_wg_cd->addWidget(btn_cd_to_file);
    lo_wg_cd->addWidget(btn_disc_to_file);
    lo_wg_cd->addWidget(btn_iso_to_cso);

    wg_ic_cd->setLayout(lo_wg_cd);
    wg_ic_cd->setVisible(sh_disc);

//Advance---------------------------------------
    QPushButton *pb_advance = new QPushButton();
    createCategoryBtn(pb_advance,":/usr/share/danton/icons/multimedia.png","Advance");
    connect(pb_advance,SIGNAL(clicked(bool)),this,SLOT(on_btn_advance_clicked()));

    QGridLayout *lo_advance = new QGridLayout();

    QToolButton *tb_v_joiner = new QToolButton();
    tb_v_joiner->setText("Video joiner");
    tb_v_joiner->setIcon(QIcon(":/usr/share/danton/icons/videojoin.png"));
    tb_v_joiner->setIconSize(QSize(72,72));
    tb_v_joiner->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    tb_v_joiner->setFixedSize(200,100);

    QToolButton *tb_rename = new QToolButton();
    tb_rename->setText("Rename");
    tb_rename->setIcon(QIcon(":/usr/share/danton/icons/rename.png"));
    tb_rename->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    tb_rename->setIconSize(QSize(72,72));
    tb_rename->setFixedSize(100,100);

    QToolButton *tb_a_joiner = new QToolButton();
    tb_a_joiner->setText("Audio joiner");
    tb_a_joiner->setIcon(QIcon(":/usr/share/danton/icons/audiojoin.png"));
    tb_a_joiner->setIconSize(QSize(72,72));
    tb_a_joiner->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    tb_a_joiner->setFixedSize(200,100);

    QToolButton *tb_mux = new QToolButton();
    tb_mux->setText("mux");
    tb_mux->setIcon(QIcon(":/usr/share/danton/icons/mux.png"));
    tb_mux->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    tb_mux->setIconSize(QSize(72,72));
    tb_mux->setFixedSize(100,100);

    QToolButton *tb_media_info = new QToolButton();
    tb_media_info->setText("Media Info");
    tb_media_info->setIcon(QIcon(":/usr/share/danton/icons/mediainfo.png"));
    tb_media_info->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    tb_media_info->setIconSize(QSize(72,72));
    tb_media_info->setFixedSize(200,100);
    connect(tb_media_info,SIGNAL(clicked(bool)),this,SLOT(on_btn_mediainfo_clicked()));

    lo_advance->addWidget(tb_v_joiner,0,0);
    lo_advance->addWidget(tb_rename,0,1);
    lo_advance->addWidget(tb_a_joiner,1,0);
    lo_advance->addWidget(tb_mux,1,1);
    lo_advance->addWidget(tb_media_info,2,0);
    lo_advance->setHorizontalSpacing(0);
   // lo_advance->setVerticalSpacing(0);

    wg_ic_advance = new QWidget();
    wg_ic_advance->setLayout(lo_advance);
    wg_ic_advance->setVisible(sh_advance);

    lo_col_icon->addWidget(btn_video_cat);
    lo_col_icon->addWidget(wg_ic_video);
    lo_col_icon->addWidget(btn_audio_cat);
    lo_col_icon->addWidget(wg_ic_audio);
    lo_col_icon->addWidget(btn_cat_img);
    lo_col_icon->addWidget(wg_ic_image);
    lo_col_icon->addWidget(btn_cat_cd);
    lo_col_icon->addWidget(wg_ic_cd);
    lo_col_icon->addWidget(pb_advance);
    lo_col_icon->addWidget(wg_ic_advance);
    lo_col_icon->setSpacing(0);

   fr_left_col->setLayout(lo_col_icon);

   //isi frame kanan alias tabel
   main_table = new QTableWidget(central_widget);
   main_table->setColumnCount(5);
   main_table->setHorizontalHeaderLabels(QString("Sumber;size;Target;Status Konversi;Keluaran").split(";"));
   main_table->setColumnWidth(1,100);
   main_table->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
   main_table->setColumnWidth(1,100);
   main_table->setColumnWidth(2,100);
   main_table->setColumnWidth(3,140);
   main_table->horizontalHeader()->setSectionResizeMode(4,QHeaderView::Stretch);
   main_table->verticalHeader()->hide();
   main_table->setSelectionBehavior(QAbstractItemView::SelectRows);
   main_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
   main_table->setAlternatingRowColors(true);
   main_table->setSelectionMode(QAbstractItemView::MultiSelection);
   main_table->setContextMenuPolicy(Qt::CustomContextMenu);
   connect(main_table, SIGNAL(customContextMenuRequested(QPoint)),SLOT(rightClickMenu(QPoint)));

   proses_konversi = new QProcess(this);
   image_conversion = new QProcess(this);

   connect(proses_konversi, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutputProcess()));
   connect(proses_konversi, SIGNAL(readyReadStandardError()), this, SLOT(readOutputProcess()));
   connect(proses_konversi, SIGNAL(finished(int)), this, SLOT(mainProcess(int)));

   connect(image_conversion, SIGNAL(readyReadStandardOutput()), this, SLOT(image_conversion_output()));
   connect(image_conversion, SIGNAL(readyReadStandardError()), this, SLOT(image_conversion_output()));
   connect(image_conversion, SIGNAL(finished(int)), this, SLOT(mainProcess(int)));

   lo_central_widget->addWidget(fr_left_col);
   lo_central_widget->addWidget(main_table);
   lo_central_widget->setMargin(0);

   central_widget->setLayout(lo_central_widget);

   this->setCentralWidget(central_widget);
}

void danton::buatStatusBar(){

    QWidget *widget_bawah = new QWidget(this);
    QHBoxLayout *menu_bottom = new QHBoxLayout(widget_bawah);
    output_text_btn =new QPushButton(widget_bawah);
    output_text_btn->setFixedWidth(200);
    output_text_btn->setIcon(QIcon::fromTheme("folder"));
    output_text_btn->setText(g_output_path);
    output_text_btn->setStyleSheet("text-align:left");
    output_text_btn->setToolTip("Open output folder");
    connect(output_text_btn, SIGNAL(clicked()),this,SLOT(openFolderOutput()));

    lb_count = new QLabel(widget_bawah);
    lb_count->setText("Processed :--/--");

    lb_count_error = new QLabel(widget_bawah);
    lb_count_error->setText("Error :--");

    lb_elapsedtime = new QLabel;
    lb_elapsedtime->setText("elapsed");

    cb_poweroff = new QCheckBox(widget_bawah);
    cb_poweroff->setText(tr("After converting : Power off computer"));
    connect(cb_poweroff,SIGNAL(toggled(bool)),this,SLOT(shutdown_status(bool)));

    menu_bottom->addWidget(output_text_btn);
    menu_bottom->addWidget(lb_count);
    menu_bottom->addWidget(lb_count_error);
    menu_bottom->addWidget(lb_elapsedtime);
    menu_bottom->addWidget(cb_poweroff);
//    menu_bottom->setMargin(0);
    widget_bawah->setLayout(menu_bottom);
    statusBar()->addPermanentWidget(widget_bawah,1);

}

void danton::readSetting(){

    QSettings setting("danton", "danton");
    delete_original=setting.value("delete_original").toBool();
    overwrite_file=setting.value("overwrite_file").toBool();
    save_to_source=setting.value("save_to_source").toBool();
    append_name=setting.value("append_name").toBool();
    poweroff_computer=setting.value("poweroff_computer").toBool();
    open_folder_at_finish=setting.value("open_folder_at_finish").toBool();
    show_noty_succes=setting.value("show_noty_succes").toBool();
    show_noty_error=setting.value("show_noty_error").toBool();
   // last_dir=setting.value("last_dir").toString();
    g_output_path=setting.value("output_dir").toString();
    if(g_output_path.isEmpty())
        g_output_path=QDir::homePath();
    if(setting.contains("wg_ic_video")){
    sh_video= setting.value("wg_ic_video").toBool();
    sh_audio=setting.value("wg_ic_audio").toBool();
    sh_pict= setting.value("wg_ic_image").toBool();
    sh_disc= setting.value("wg_ic_cd").toBool();
    sh_advance=setting.value("wg_ic_advance").toBool();
    }
}

void danton::rightClickMenu(const QPoint &pos){

    QMenu menu(this);
    QAction *output_setting_act = menu.addAction("Pengaturan keluaran");
    output_setting_act->setEnabled(false);

    QAction *ops_menu_act =  menu.addAction("Opsi");
    ops_menu_act->setEnabled(false);

    QAction *lihat_berkas_asli = menu.addAction("Lihat berkas sumber");
    lihat_berkas_asli->setEnabled(false);
    connect(lihat_berkas_asli, SIGNAL(triggered(bool)), this, SLOT(buka_berkas_sumber()));

    QAction *lihat_output_file = menu.addAction("Lihat berkas keluaran");
    lihat_output_file->setEnabled(false);
    menu.addSeparator();

    QAction *source_folder_act = menu.addAction("Buka folder sumber");
    source_folder_act->setEnabled(false);

    QAction *folder_keluaran = menu.addAction("Buka folder keluaran");
    folder_keluaran->setEnabled(false);
    connect(folder_keluaran, SIGNAL(triggered(bool)),SLOT(openFolderOutput()));
    menu.exec(main_table->viewport()->mapToGlobal(pos));
}

void danton::buka_berkas_sumber(){

    int row = main_table->currentRow();
    QString berkas_sumber = main_table->item(row, 0)->toolTip();

    QProcess *pc_open_file_source = new QProcess;
    pc_open_file_source->start("xdg-open", QStringList()<< berkas_sumber);
}

void danton::deleteRowMainTable()
{
   QList<QTableWidgetItem *> items = main_table->selectedItems();

   while(!items.isEmpty())
   {
       main_table->removeRow(items[0]->row());
       items = main_table->selectedItems();
   }

    if(main_table->rowCount()==0)
    {
        delete_action->setEnabled(false);
        clear_list_action->setEnabled(false);
        start_action->setEnabled(false);
    }
    //update current count main table
    update_counter();
}

void danton::on_btn_cat_video_clicked(){

    wg_ic_audio->hide();
    wg_ic_image->hide();
    wg_ic_cd->hide();
    wg_ic_advance->hide();
    wg_ic_video->show();
}

void danton::on_btn_cat_audio_clicked(){

    wg_ic_video->hide();
    wg_ic_image->hide();
    wg_ic_cd->hide();
    wg_ic_advance->hide();
    wg_ic_audio->show();
}

void danton::on_btn_cat_img_clicked(){

    wg_ic_video->hide();
    wg_ic_audio->hide();
    wg_ic_cd->hide();
    wg_ic_advance->hide();
    wg_ic_image->show();
}

void danton::on_btn_cat_cd_clicked()
{
    wg_ic_video->hide();
    wg_ic_audio->hide();
    wg_ic_image->hide();
    wg_ic_advance->hide();
    wg_ic_cd->show();

}

void danton::on_btn_advance_clicked(){
    wg_ic_video->hide();
    wg_ic_audio->hide();
    wg_ic_image->hide();
    wg_ic_cd->hide();
    wg_ic_advance->show();
}

void danton::on_btnV_mp4_clicked(){
    g_target_format = "mp4";
    g_mediaType = 1;

}
void danton::on_btnV_avi_clicked(){
    g_target_format = "avi";
    g_mediaType = 1;
}

void danton::on_btnV_3gp_clicked(){
    g_target_format = "3gp";
    g_mediaType = 1;
}
void danton::on_btnV_webm_clicked(){
    g_target_format = "webm";
    g_mediaType = 1;
}
void danton::on_btnV_mkv_clicked(){
    g_target_format = "mkv";
    g_mediaType = 1;
}

void danton::on_btnV_gif_clicked(){
    g_target_format = "gif";
    g_mediaType = 1;
}
void danton::on_btnV_wmv_clicked(){
    g_target_format = "wmv";
    g_mediaType = 1;
}
void danton::on_btnV_mpg_clicked(){
    g_target_format = "mpg";
    g_mediaType = 1;
}
void danton::on_btnV_vob_clicked(){
    g_target_format = "vob";
    g_mediaType = 1;
}
void danton::on_btnV_mov_clicked(){
    g_target_format = "mov";
    g_mediaType = 1;
}
void danton::on_btnV_flv_clicked(){
    g_target_format = "flv";
    g_mediaType = 1;
}
void danton::on_btnV_swf_clicked(){
    g_target_format = "swf";
    g_mediaType = 1;
}

void danton::on_btnA_mp3_clicked(){
    g_target_format = "mp3";
    g_mediaType = 2;
}
void danton::on_btnA_wma_clicked(){
    g_target_format = "wma";
    g_mediaType = 2;
}
void danton::on_btnA_ape_clicked(){
    g_target_format = "ape";
    g_mediaType = 2;
}
void danton::on_btnA_flac_clicked(){
    g_target_format = "flac";
    g_mediaType = 2;
}
void danton::on_btnA_aac_clicked(){
    g_target_format ="aac";
    g_mediaType = 2;
}
void danton::on_btnA_mmf_clicked(){
    g_target_format ="mmf";
    g_mediaType = 2;
}
void danton::on_btnA_amr_clicked(){
    g_target_format = "amr";
    g_mediaType = 2;
}
void danton::on_btnA_m4a_clicked(){
    g_target_format = "m4a";
    g_mediaType = 2;
}
void danton::on_btnA_m4r_clicked()
{
    g_target_format = "m4r";
    g_mediaType = 2;
}
void danton::on_btnA_ogg_clicked(){
    g_target_format = "ogg";
    g_mediaType = 2;
}
void danton::on_btnA_wav_clicked(){
    g_target_format = "wav";
    g_mediaType = 2;
}
void danton::on_btnA_mp2_clicked(){
    g_target_format = "mp2";
    g_mediaType = 2;
}

void danton::on_btnP_webp_clicked(){
    g_target_format = "webp";
    g_mediaType = 3;
}

void danton::on_btnP_jpg_clicked(){
    g_target_format = "jpg";
    g_mediaType = 3;
}

void danton::on_btnP_png_clicked(){
    g_target_format = "png";
    g_mediaType = 3;
}
void danton::on_btnP_ico_clicked(){
    g_target_format = "ico";
    g_mediaType = 3;
}
void danton::on_btnP_bmp_clicked(){
    g_target_format = "bmp";
    g_mediaType = 3;
}
void danton::on_btnP_gif_clicked(){
    g_target_format = "gif";
    g_mediaType = 3;
}
void danton::on_btnP_tif_clicked(){
    g_target_format = "tif";
    g_mediaType = 3;
}
void danton::on_btnP_pcx_clicked(){
    g_target_format = "pcx";
    g_mediaType = 3;
}
void danton::on_btnP_tga_clicked()
{
    g_target_format = "tga";
    g_mediaType = 3;
}

void danton::onBtnCSOClicked(){
    g_target_format="cso";
    g_mediaType=4;
}

void danton::output_dir(){

   QString path = QFileDialog::getExistingDirectory(this,"Pilih folder", QDir::homePath());

        if(!path.isEmpty()){
            g_output_path=path;
            output_text_btn->setText(g_output_path);
            }

}


void danton::openFolderOutput()
{
    QProcess *open_folder = new QProcess(this);
    open_folder->start("xdg-open", QStringList()<<g_output_path);
}

void danton::clearMainTable()
{
    main_table->clearContents();
    main_table->setRowCount(0);
    clear_list_action->setEnabled(false);
    start_action->setEnabled(false);
    delete_action->setEnabled(false);

    //update counter
    sudah_komplit=0;
    update_counter();
}


void danton::createContentMainTable(QStringList file_list_){

    if(main_table->rowCount()==0){

            main_table->setRowCount(file_list_.count());

            for(int i=0; i<file_list_.count();i++){

                QFileInfo file_info;
                QString file = file_list_.at(i);
                file_info.setFile(file);


                    QTableWidgetItem *item_nama = new QTableWidgetItem;
                    item_nama->setText(file_info.fileName());
                    item_nama->setToolTip(file_info.filePath());
                    main_table->setItem(i, 0, item_nama);



                    QTableWidgetItem *item_size = new QTableWidgetItem;
                    float size = (float)file_info.size()/1000000;
                    item_size->setText(QString::number(size, 'f', 1)+" MB");
                    item_size->setTextAlignment(Qt::AlignCenter);

                    main_table->setItem(i, 1, item_size);

                    QTableWidgetItem *item_target = new QTableWidgetItem;
                    item_target->setText(g_target_format);
                    item_target->setTextAlignment(Qt::AlignCenter);
                    main_table->setItem(i, 2, item_target);

                    QTableWidgetItem *item_status = new QTableWidgetItem;
                    item_status->setText(tr("menunggu..."));
                    item_status->setToolTip(tr("menunggu..."));
                    item_status->setTextAlignment(Qt::AlignCenter);
                    main_table->setItem(i, 3, item_status);


           //membuat nama keluaran

                    QString file_name = main_table->item(i,0)->toolTip();
                    QString ekstensi = main_table->item(i, 2)->text();
                    QString nama_keluaran2 = QFileInfo(file_name).completeBaseName().append("."+ekstensi);

                        if(save_to_source){

                            QString source_folder = QFileInfo(file_name).path();
                            QTableWidgetItem *item_keluaran = new QTableWidgetItem;
                            item_keluaran->setText(source_folder+"/"+nama_keluaran2);
                            item_keluaran->setToolTip(source_folder+"/"+nama_keluaran2);
                            main_table->setItem(i, 4, item_keluaran);
                        }
                        else
                        {

                            QTableWidgetItem *item_keluaran = new QTableWidgetItem;
                            item_keluaran->setText(g_output_path+"/"+nama_keluaran2);
                            item_keluaran->setToolTip(g_output_path+"/"+nama_keluaran2);
                            main_table->setItem(i, 4, item_keluaran);
                        }

            }

        start_action->setEnabled(true);
        delete_action->setEnabled(true);
        clear_list_action->setEnabled(true);

 //just for see parameter
    QString ppp;
    dialogConversion dc;//why icant declare this at header
     dc.getParameter(g_target_format,&ppp);
    qDebug()<<"ngintip parameter"<<g_target_format<<ppp.replace(";"," ");
             //end see parameter
        update_counter();
    }
    else{
            //if the table already have content
            int  count_before=main_table->rowCount();
            main_table->setRowCount(main_table->rowCount()+file_list_.count());

                for(int i=0; i<file_list_.count();i++){

                    QFileInfo file_info;
                    QString file = file_list_.at(i);
                    file_info.setFile(file);

                        QTableWidgetItem *item_nama = new QTableWidgetItem;
                        item_nama->setText(file_info.fileName());
                        item_nama->setToolTip(file_info.filePath());
                        main_table->setItem(i+count_before, 0, item_nama);

                        QTableWidgetItem *item_size = new QTableWidgetItem;
                        float size = (float)file_info.size()/1000000;
                        item_size->setText(QString::number(size, 'f', 1)+" MB");
                        item_size->setTextAlignment(Qt::AlignCenter);

                       // main_table->setItem(i, 1, item_size);

                    main_table->setItem(i+count_before, 1, item_size);

                    QTableWidgetItem *item_target = new QTableWidgetItem;
                    item_target->setText(g_target_format);
                    item_target->setTextAlignment(Qt::AlignCenter);
                    main_table->setItem(i+count_before, 2, item_target);

                    QTableWidgetItem *item_status = new QTableWidgetItem;
                    item_status->setText(tr("menunggu..."));
                    item_status->setToolTip(tr("menunggu..."));
                    item_status->setTextAlignment(Qt::AlignCenter);
                    main_table->setItem(i+count_before, 3, item_status);

                    //membuat nama keluaran
                    QString file_name = main_table->item(i+count_before,0)->toolTip();
                    QString ekstensi = main_table->item(i+count_before, 2)->text();
                    QString nama_keluaran2 = QFileInfo(file_name).baseName().append("."+ekstensi);

                            if(save_to_source){
                                //membuat jalur keluaran = jalur sumber

                                QString folder_sumber2 = QFileInfo(file_name).path();

                                QTableWidgetItem *item_keluaran = new QTableWidgetItem;
                                item_keluaran->setText(folder_sumber2+"/"+nama_keluaran2);
                                item_keluaran->setToolTip(folder_sumber2+"/"+nama_keluaran2);
                                main_table->setItem(i+count_before, 4, item_keluaran);
                            }
                            else{
                                QTableWidgetItem *item_keluaran = new QTableWidgetItem;
                                item_keluaran->setText(g_output_path+"/"+nama_keluaran2);
                                item_keluaran->setToolTip(g_output_path+"/"+nama_keluaran2);
                                main_table->setItem(i+count_before, 4, item_keluaran);
                                }
                    }

        }
    update_counter();
    start_action->setEnabled(true);
}

void danton::showAbout(){

         about About;
         About.exec();
}

void danton::openDialogConv(){

   dialogConversion *a = new dialogConversion;
    connect(a,SIGNAL(sendFileList(QStringList)), this, SLOT(createContentMainTable(QStringList)));
    connect(a,SIGNAL(sendOutputFolder(QString)),this,SLOT(receiveOutputFolder(QString)));
    a->show();
}

void danton::onBtnStartClicked(){

    stop_action->setEnabled(true);

    if(!main_table->rowCount())
        return;

    if(conversion_process_on){
        QMessageBox::warning(this, tr("Galat"), tr("Proses konversi masih berlangsung, tunggu sampai selesai"));
        return;
    }

    conversion_process_on=true;

    int jumlah_file = main_table->rowCount();

    sudah_komplit=0;
    for(int i=0; i<jumlah_file;i++){
        if(main_table->item(i,3)->toolTip()!="Completed"){
            current_file=i;
            sudah_komplit=i;
            break;
        }
    }

    if(current_file==0){
        //that's a completely new conversion
        all_errors.clear();
        error_count=0;
        //ui->show_errors->hide();
    }



    globpro_string="100%";

    mainProcess(0);
    timer();

}

void danton::mainProcess(int return_code){
    //use format junkie algorithme

    if(stop_button_clicked){
        if(current_file!=0)
            main_table->removeCellWidget(current_file-1,3);
        else
            main_table->removeCellWidget(current_file,3);
        globpro_hasbeendeleted=true;
        int to_apply = current_file;
        if(current_file>0)
            to_apply--;
        if(!QFile::remove(g_output_file))
            qDebug() << QString("Error removing file '"+g_output_file+"'\n").toLocal8Bit().data();
        return;
    }

    if(return_code){
        qDebug()<<"gagal"<<globpro_string;
    //proses konversi gagal
        if(all_errors.isEmpty())
            all_errors+="'<b>"+g_input_file+"</b>'<br>";
        else
            all_errors+="\n'<b>"+g_input_file+"</b>'<br>";
        current_file_errors.replace("\n","<br>");
        all_errors+="<font color=red>"+current_file_errors+"</font><br>";

        QTableWidgetItem *item_failed = new QTableWidgetItem;
        item_failed->setText("ERROR");
        //item_failed->setToolTip(current_file_errors);
        item_failed->setTextAlignment(Qt::AlignCenter);
        //item_failed->setBackgroundColor(Qt::red);
        item_failed->setTextColor(Qt::red);
        qDebug()<<"buat statu gagal pada"<<current_file;

        main_table->setItem(current_file-1,3,item_failed);

        //if(show_noty_error)
            //showMessage(main_table->item(to_apply,0)->text()+" error");

        current_file_errors.clear();
        error_count++;
        update_error_count();

    }

    else{

        //IF NOT RETURN CODE
        current_file_errors.clear();
         update_counter();
        sudah_komplit++;

        qDebug()<<"cur file shomessage"<<current_file;
        if(show_noty_succes){
        if(current_file>0 && globpro_string!="Already Exists")
        showMessage(main_table->item(current_file-1,0)->text()+" successfully converted");
        }

        QTableWidgetItem *item_completed = new QTableWidgetItem;
        item_completed->setToolTip("Completed");
        main_table->setItem(current_file-1,3, item_completed);

        /*
          The conversion of the previous file was successful!
          Check if the original (source) file is to be deleted...
        */
//        qDebug()<<"delete original"<<delete_original;
        if(delete_original){
            if(QFile(g_input_file).exists()){
                if(!QFile::remove(g_input_file))
                    qDebug() << QString("Could not delete source file '"+g_input_file+"'\nDo I have the permissions to do so?\n").toLocal8Bit().data();
            }
        }

    }

    if(current_file>main_table->rowCount()-1){
     //semua file sudah di konversikan
        conversion_process_on=false;
        globpro->setFormat(globpro_string);
        globpro->setValue(100);
        QTableWidgetItem *item_progress = new QTableWidgetItem;
        item_progress->setToolTip("Completed");
        main_table->setItem(current_file-1,3, item_progress);

        start_action->setEnabled(false);
        stop_action->setEnabled(false);

        error_count=0;
        actionAfterConvert();
        return;
    }


   if(main_table->item(current_file,3)->toolTip()=="Completed"){

        // file sudah dikonversi, lanjut ke file berikutnya
       current_file++;
       mainProcess(0);
       return;
    }

//qDebug()<<"globpro string"<<globpro_string;
   if(globpro_string=="Already Exists"){

       if(current_file!=0){
           if(globpro_hasbeendeleted){
               globpro = new QProgressBar(this);
               globpro_hasbeendeleted=false;
           }

           QProgressBar *qtpro =new QProgressBar(this);
           qtpro=globpro;
           qtpro->setFormat(globpro_string);
           qtpro->setValue(100);
           main_table->setCellWidget(current_file-1,3,qtpro);
           QTableWidgetItem *item_progress = new QTableWidgetItem;
           item_progress->setToolTip("Completed");
           main_table->setItem(current_file-1,3, item_progress);

           if(show_noty_succes)
           showMessage(main_table->item(current_file-1,0)->text()+" already exist");

       }
    }
           if(!main_table->cellWidget(current_file,3)){
               qDebug()<<"!main_table->cellWidget(current_file,3)";
                QProgressBar *qtpro = new QProgressBar(this);
                main_table->setCellWidget(current_file, 3, qtpro);
                qDebug()<<"curent file"<<current_file;
                qDebug()<<"create prog bar on"<<current_file;
                if(!globpro)
                    globpro = new QProgressBar(this);
                globpro=qtpro;

       }

//action start here

            g_input_file = main_table->item(current_file, 0)->toolTip();
            g_output_file = main_table->item(current_file, 4)->text();
            dialogConversion ww;
            QString nama_format = main_table->item(current_file, 2)->text();
           int cur_media_type=ww.getMediaType(nama_format);
            QString program;
            QStringList arguments;
            QString opsi;


//sortir video-----------------
                        if(cur_media_type==1){
                        program.clear();
                        program = "ffmpeg";

                        arguments.clear();

                        ww.getParameter(nama_format, &opsi);

                        arguments <<"-i"<< g_input_file <<opsi.split(";")<< g_output_file;

                        //get current durration
                        current_durration=ww.getDuration(g_input_file);

                    }

// --------- sortir audio
                      if(cur_media_type==2){
                        program.clear();
                        program = "ffmpeg";
                        arguments.clear();
                        arguments << "-i" << g_input_file;
                        ww.getParameter(nama_format, &opsi);
                        arguments<<opsi.split(";") << g_output_file;

                        //get current durration input file
                        current_durration=ww.getDuration(g_input_file);

                    }

// ---------sortir gambar

                    if(cur_media_type==3){
                        program.clear();
                        program = "convert";
                        arguments.clear();
                        ww.getParameter(nama_format, &opsi);
                        arguments <<"-monitor"<<opsi.split(";")<< g_input_file;
                        arguments<< g_output_file;

                    }


                   /*
                     Checking whether the output_file already exists. If it does, then
                     overwrite it, if it checked so, or proceed to the next file, if not...
                    */
                   if(QFile(g_output_file).exists()){
                       if(overwrite_file){
                           if(!QFile::remove(g_output_file)){
                               qDebug()<<"file"+g_output_file+" sudah ada dan dihapus";
                               qDebug() << QString("Couldn't remove the already existing file '"+g_output_file+"'\n").toLocal8Bit().data();
                               current_file++;
                               globpro_string="Already Exists";
                               mainProcess(0);
                               return;
                           }
                       }
                       else
                       {
                           qDebug()<<"fil sudah ada, dilewati";
                           current_file++;
                           globpro_string="Already Exists";
                           mainProcess(0);
                           return;
                       }
                   }

                   qDebug() << program << arguments;


        globpro_string="100%";
        qDebug()<<"cur media type"<<cur_media_type;
        switch(cur_media_type){
        case 1:
            proses_konversi->start(program, arguments);
            break;
        case 2:
            proses_konversi->start(program, arguments);
            break;
        case 3:
            image_conversion->start(program, arguments);
            break;
        }


       current_file++;

}


void danton::readOutputProcess()
{

    //read all possible output so as to calculate the percentages...
    QByteArray newData_stdout=proses_konversi->readAllStandardOutput();
    QString stdout=QString::fromLocal8Bit(newData_stdout);
    QByteArray newData_stderr=proses_konversi->readAllStandardError();
    QString stderr=QString::fromLocal8Bit(newData_stderr);
    QString out=stdout+stderr;
    current_file_errors+=out;
   qDebug()<<out;

    if(out.contains("kB time=")){

        QRegExp regex("time=.* ");
        regex.setMinimal(true);


        QStringList list;
        int pos = 0;

        while ((pos = regex.indexIn(out, pos)) != -1)
        {
            list << regex.cap(0).remove(QChar(' '),Qt::CaseInsensitive);
            pos += regex.matchedLength();
        }
        if(!list.count()){
            //error
            return;
        }
        QString current=list.at(0);
        current.replace("time=","");
        QString msecs=current.right(2);
        current.chop(3);
        QStringList time=current.split(":");
        time << msecs;
        float progress_time=time.at(0).toInt()*3600+time.at(1).toInt()*60+time.at(2).toInt()+QString("0."+time.at(3)).toFloat();

        int percent=0;
            percent=progress_time*100/current_durration;
            if(percent>100)
                percent=100;


            globpro->setFormat(QString::number(percent)+"%");
            globpro->setValue(percent);

        }
}

void danton::receiveOutputFolder(QString output_folder)
{
    g_output_path=output_folder;
    output_text_btn->setText(output_folder);

}
void danton::settingDialog(){

    preferences *Preferences = new preferences(this);
    connect(Preferences,SIGNAL(send_new_output(QString)),this,SLOT(receiveOutputFolder(QString)));
    connect(Preferences, SIGNAL(send_delete_orginal(bool)),this, SLOT(receiveDeleteOriginal(bool)));
    connect(Preferences, SIGNAL(send_overwrite(bool)), this, SLOT(receiveOverwrite(bool)));
    connect(Preferences, SIGNAL(send_save_to_source(bool)), this, SLOT(receiveSaveToSource(bool)));
    connect(Preferences, SIGNAL(send_append(bool)), this, SLOT(receiveAppend(bool)));
    connect(Preferences,SIGNAL(send_shutdown_status(bool)),this,SLOT(receive_shutdown_status(bool)));
    connect(Preferences, SIGNAL(send_open_folder(bool)), this, SLOT(receiveOpenFolder(bool)));
    connect(Preferences, SIGNAL(send_notify_success(bool)), this, SLOT(receiveNotifySuccess(bool)));
    connect(Preferences, SIGNAL(send_notify_error(bool)), this, SLOT(receiveNotifyError(bool)));
    Preferences->exec();
}

void danton::receiveDeleteOriginal(bool del_or){
   delete_original =  del_or ;
}

void danton::receiveOverwrite(bool ovw_file){
    overwrite_file = ovw_file;
}

void danton::receiveSaveToSource(bool save_to){
    save_to_source = save_to;
}

void danton::receiveAppend(bool append){
    append_name = append ;
}

void danton::receive_shutdown_status(bool shutdown){

    poweroff_computer=shutdown;

    cb_poweroff->setChecked(shutdown);

}

void danton:: receiveOpenFolder(bool op_fold){
    open_folder_at_finish = op_fold;
}

void danton::receiveNotifySuccess(bool noty_s){
   show_noty_succes = noty_s;
}

void danton::receiveNotifyError(bool noty_e){
    show_noty_error = noty_e;
}

void danton::shutdown_status(bool s){
    poweroff_computer=s;
}

void danton::actionAfterConvert(){
    if(poweroff_computer){
        //shutdown
        QString after_convert_cmd="";
        after_convert_cmd="dbus-send --system --print-reply --dest=org.freedesktop.ConsoleKit /org/freedesktop/ConsoleKit/Manager org.freedesktop.ConsoleKit.Manager.Stop > /dev/null 2> /dev/null&";

        if(system(after_convert_cmd.toLocal8Bit().data()))
         qDebug() << QString("Error running command '"+after_convert_cmd+"'\n").toLocal8Bit().data();
    }
}

void danton::onStopBtnClicked(){

    stop_button_clicked=true;
    conversion_process_on=false;
    if(proses_konversi->isOpen())
        proses_konversi->close();
}

void danton::showMessage(QString message){

        trayMenu = new QMenu;
        trayMenu->addAction("danton");

        trayIcon = new QSystemTrayIcon(this);
        trayIcon->setIcon(QIcon::fromTheme("info"));
        trayIcon->setContextMenu(trayMenu);

        trayIcon->show();
        trayIcon->showMessage("danton", message);

}

void danton::update_counter(){

    lb_count->setText("Processed :"+QString::number(sudah_komplit)+"/"+QString::number(main_table->rowCount()));
}

void danton::update_error_count(){
    lb_count_error->setText("Error :"+QString::number(error_count));
}

void danton::image_conversion_output(){

     QByteArray newData_stdout=image_conversion->readAllStandardOutput();
     QString stdout=QString::fromLocal8Bit(newData_stdout);
     QByteArray newData_stderr=image_conversion->readAllStandardError();
     QString stderr=QString::fromLocal8Bit(newData_stderr);
     QString out=stdout+stderr;
     current_file_errors+=out;
     qDebug()<<"out"<<out;

     if(out.contains("complete")){

             QRegExp regex("\\d+%");
             regex.setMinimal(true);

             QStringList list;
             int pos = 0;

             while ((pos = regex.indexIn(out, pos)) != -1)
             {
                 list << regex.cap(0);
                 pos += regex.matchedLength();
             }
             if(!list.count()){
                 //error
                 return;
             }

             QString current=list.at(0);

             current.chop(1);

            int percent = current.toInt();

                 globpro->setFormat(QString::number(percent)+"%");
                 globpro->setValue(percent);
     }
}

void danton::dvdToFile(){

    dvdtofile dtf;
    dtf.exec();
}

void danton::discToISO(){

    disctoiso dti;
    dti.exec();
}

void danton::cdToFile(){
    musiccdtofile ctd;
    ctd.exec();
}

void danton::on_btn_mediainfo_clicked(){
    mediainfo mi;
    mi.exec();
}

void danton::timer(){

    elapsedtime = new QElapsedTimer;
    elapsedtime->start();
    lb_elapsedtime->setText(QString::number(elapsedtime->elapsed()));
    qDebug()<<"elap"<<elapsedtime->elapsed();


}

void danton::closeEvent(QCloseEvent *){
    QSettings settings("danton", "danton");
    settings.setValue("output_dir",g_output_path);
    settings.setValue("wg_ic_video", wg_ic_video->isVisible());
    settings.setValue("wg_ic_audio", wg_ic_audio->isVisible());
    settings.setValue("wg_ic_image", wg_ic_image->isVisible());
    settings.setValue("wg_ic_cd", wg_ic_cd->isVisible());
    settings.setValue("wg_ic_advance", wg_ic_advance->isVisible());
}
