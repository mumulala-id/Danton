#include "dialogconversion.h"
#include "mediainfo.h"
#include <QFrame>
#include <QVBoxLayout>
#include <QAction>
#include <QDir>
#include <QHeaderView>
#include <QTreeWidgetItem>
#include <QFileDialog>
#include <QGroupBox>
#include <QLineEdit>
#include <QSettings>
#include <QDebug>
#include <QListView>
#include <QRadioButton>
#include <QMap>
#include <QTime>
#include <QVideoWidget>
#include <QSlider>
#include <QFrame>
using namespace std;

QString mp3_vol_ctr;
QString wma_vol_ctr;
QString ape_vol_ctr;
QString flac_vol_ctr;
QString aac_vol_ctr;
QString mmf_vol_ctr;
QString m4a_vol_ctr;
QString m4r_vol_ctr;
QString amr_vol_ctr;
QString ogg_vol_ctr;
QString wav_vol_ctr;
QString mp2_vol_ctr;

bool jpg_limit_size=false;
bool jpg_rotate=false;
bool jpg_insert_text=false;

QString jpg_cur_text="Original size";
QString jpg_max_width;
QString jpg_max_heigth;
QString jpg_angle;
QString jpg_font;
QString jpg_text_pos;
QString jpg_text_color;
QString jpg_font_size;
bool jpg_italic;
bool jpg_underline;
QString jpg_tag_string;
bool jpg_insert_wm;//watermark
QString jpg_wm_pos;
QString jpg_wm_size;
QString jpg_wm_file;


bool png_limit_size=false;
bool png_rotate=false;
bool png_insert_text=false;
QString png_cur_text="Original size";
QString png_max_width;
QString png_max_heigth;
QString png_angle;
QString png_font;
QString png_text_pos;
QString png_text_color;
QString png_font_size;
bool png_italic;
bool png_underline;
QString png_tag_string;
bool png_insert_wm;//watermark
QString png_wm_pos;
QString png_wm_size;
QString png_wm_file;

bool ico_limit_size=true;
bool ico_rotate=false;
bool ico_insert_text=false;
QString ico_cur_text="16x16";
QString ico_max_width="16";
QString ico_max_heigth="16";
QString ico_angle;
QString ico_font;
QString ico_text_pos;
QString ico_text_color;
QString ico_font_size;
bool ico_italic;
bool ico_underline;
QString ico_tag_string;
bool ico_insert_wm;//watermark
QString ico_wm_pos;
QString ico_wm_size;
QString ico_wm_file;

bool bmp_limit_size=false;
bool bmp_rotate=false;
bool bmp_insert_text=false;
QString bmp_cur_text="Original size";
QString bmp_max_width;
QString bmp_max_heigth;
QString bmp_angle;
QString bmp_font;
QString bmp_text_pos;
QString bmp_text_color;
QString bmp_font_size;
bool bmp_italic;
bool bmp_underline;
QString bmp_tag_string;
bool bmp_insert_wm;//watermark
QString bmp_wm_pos;
QString bmp_wm_size;
QString bmp_wm_file;

bool tif_limit_size=false;
bool tif_rotate=false;
bool tif_insert_text=false;
QString tif_cur_text="Original size";
QString tif_max_width;
QString tif_max_heigth;
QString tif_angle;
QString tif_font;
QString tif_text_pos;
QString tif_text_color;
QString tif_font_size;
bool tif_italic;
bool tif_underline;
QString tif_tag_string;
bool tif_insert_wm;//watermark
QString tif_wm_pos;
QString tif_wm_size;
QString tif_wm_file;

bool pcx_limit_size=false;
bool pcx_rotate=false;
bool pcx_insert_text=false;
QString pcx_cur_text="Original size";
QString pcx_max_width;
QString pcx_max_heigth;
QString pcx_angle;
QString pcx_font;
QString pcx_text_pos;
QString pcx_text_color;
QString pcx_font_size;
bool pcx_italic;
bool pcx_underline;
QString pcx_tag_string;
bool pcx_insert_wm;//watermark
QString pcx_wm_pos;
QString pcx_wm_size;
QString pcx_wm_file;

bool tga_limit_size=false;
bool tga_rotate=false;
bool tga_insert_text=false;
QString tga_cur_text="Original size";
QString tga_max_width;
QString tga_max_heigth;
QString tga_angle;
QString tga_font;
QString tga_text_pos;
QString tga_text_color;
QString tga_font_size;
bool tga_italic;
bool tga_underline;
QString tga_tag_string;
bool tga_insert_wm;//watermark
QString tga_wm_pos;
QString tga_wm_size;
QString tga_wm_file;

int value_compress=5;

extern int duration_secs;
extern QString g_output_path;
extern int g_mediaType;
extern QString g_target_format;
extern bool save_to_source;
extern bool append_name;
bool additionalFolder=false;
int currenIndex;
int defaultCount;

dialogConversion::dialogConversion(QWidget *parent):
    QDialog(parent)
{
    QVBoxLayout *lo_conv_dialog = new QVBoxLayout(this);

    l_quality = new QLabel(this);

    l_quality->setAlignment(Qt::AlignCenter);

    updateLabelQuality();

    tb_delete_item = new QToolButton(this);
    tb_delete_item->setIcon((QIcon::fromTheme("edit-delete")));
    tb_delete_item->setToolTip(tr("Delete"));
    tb_delete_item->setEnabled(false);
    connect(tb_delete_item, SIGNAL(clicked()), this, SLOT(onBtnDeleteClicked()));

    tb_clear_list = new QToolButton(this);
    tb_clear_list->setIcon(QIcon::fromTheme("edit-clear"));
    tb_clear_list->setToolTip(tr("Clear list"));
    tb_clear_list->setEnabled(false);
    connect(tb_clear_list, SIGNAL(clicked()),this, SLOT(clearTable()));

    tb_play_file = new QToolButton(this);
    tb_play_file->setIcon(QIcon::fromTheme("stock_media-play"));
    tb_play_file->setToolTip(tr("Play"));
    tb_play_file->setEnabled(false);
    connect(tb_play_file, SIGNAL(clicked()), this, SLOT(playFile()));

    if(g_mediaType==4)
        tb_play_file->hide();

    tb_mediainfo = new QToolButton(this);
    tb_mediainfo->setIcon(QIcon::fromTheme("dialog-information"));
    tb_mediainfo->setToolTip(tr("Media info"));
    tb_mediainfo->setEnabled(false);

    //hide when target is image or disc
    if(g_mediaType==3 || g_mediaType==4)
        tb_mediainfo->hide();

    connect(tb_mediainfo,SIGNAL(clicked(bool)),this,SLOT(getMediaInfo()));

    QHBoxLayout *lo_line_tb = new QHBoxLayout;
    lo_line_tb->addWidget(tb_delete_item);
    lo_line_tb->addWidget(tb_clear_list);
    lo_line_tb->addWidget(tb_play_file);
    lo_line_tb->addWidget(tb_mediainfo);
    lo_line_tb->setAlignment(Qt::AlignLeft);

    QFrame *f_button = new QFrame;
    f_button->setLayout(lo_line_tb);

    QPushButton *pb_output_setting = new QPushButton(tr("Output Setting"), this);
    pb_output_setting->setIcon(QIcon::fromTheme("gtk-preferences"));

    switch(g_mediaType){
        case 1:
            connect(pb_output_setting, SIGNAL(clicked(bool)),this,SLOT(video_output_dialog_setting()));
            break;
        case 2:
            connect(pb_output_setting, SIGNAL(clicked(bool)),this,SLOT(audio_output_dialog_setting()));
            break;
        case 3:
            connect(pb_output_setting, SIGNAL(clicked(bool)),this,SLOT(dialog_pict_setting()));
            break;
        case 4:
            connect(pb_output_setting, SIGNAL(clicked(bool)),this,SLOT(cso_output_dialog_setting()));
            break;

    }

    pb_option_on_d_conv = new QPushButton(tr("Option"), this);
    pb_option_on_d_conv->setEnabled(false);
    connect(pb_option_on_d_conv,SIGNAL(clicked(bool)),this,SLOT(dialogOption()));

    if(g_mediaType==3 || g_mediaType==4){
        pb_option_on_d_conv->hide();
    }

    pb_ok = new QPushButton(tr("OK"), this);
    pb_ok->setEnabled(false);
    pb_ok->setIcon(QIcon::fromTheme("forward"));
    connect(pb_ok,SIGNAL(clicked()), this, SLOT(sendToMainTable()));

    QPushButton *add_files = new QPushButton(tr("Tambah berkas"), this);
    add_files->setIcon(QIcon::fromTheme("add"));
    connect(add_files, SIGNAL(clicked()), this, SLOT(chooseFiles()));
    connect(this,SIGNAL(sendtToTable(QStringList)),this,SLOT(createTableContents(QStringList)));

    QGridLayout *lo_top_dc = new QGridLayout;
  //  lo_top_dc->setColumnStretch(1,10);
    lo_top_dc->addWidget(l_quality, 0, 0);
    lo_top_dc->addWidget(pb_output_setting, 0, 1);
    lo_top_dc->addWidget(pb_ok,0,2);
    lo_top_dc->addWidget(f_button, 1, 0);
    lo_top_dc->addWidget(pb_option_on_d_conv,1,1);
    lo_top_dc->addWidget(add_files,1,2);

    //tabel pada dialog konversi
    table_on_d_conv = new QTableWidget(this);

    switch(g_mediaType)
    {
        case 1:
            table_on_d_conv->setColumnCount(6);
            table_on_d_conv->setHorizontalHeaderLabels(QString("Nama;Folder;Size;Video Size;Durasi;Set Range").split(";"));
            table_on_d_conv->horizontalHeader()->setSectionResizeMode(5,QHeaderView::Stretch);
            break;

        case 2:
            table_on_d_conv->setColumnCount(4);
            table_on_d_conv->setHorizontalHeaderLabels(QString("Nama;Folder;size;Durasi").split(";"));
            break;

        case 3:
            table_on_d_conv->setColumnCount(3);
            table_on_d_conv->setHorizontalHeaderLabels(QString("Nama;Folder;size").split(";"));
            break;

        case 4:
            table_on_d_conv->setColumnCount(3);
            table_on_d_conv->setHorizontalHeaderLabels(QString("Nama;Folder;size").split(";"));
            break;
    }

    table_on_d_conv->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    table_on_d_conv->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);

    table_on_d_conv->verticalHeader()->hide();
    table_on_d_conv->setSelectionBehavior(QAbstractItemView::SelectRows);
    table_on_d_conv->setSelectionMode(QAbstractItemView::SingleSelection);
    table_on_d_conv->setEditTriggers(QAbstractItemView::NoEditTriggers);


//bottom
    QCheckBox *cb_append_name = new QCheckBox(this);
    cb_append_name->setText(tr("Append name setting"));
    cb_append_name->setChecked(append_name);
    connect(cb_append_name,SIGNAL(toggled(bool)),this,SLOT(appendName(bool)));

    QLabel *lb_keluaran = new QLabel(this);
    lb_keluaran->setText("Folder keluaran");

   cbb_output_path = new QComboBox(this);
   cbb_output_path->addItem("Add folder");
   cbb_output_path->addItem("Clear list");
   cbb_output_path->addItem("Output to source file folder");
   cbb_output_path->insertSeparator(3);

    QStringList dirs;
    dirs<<QDir::homePath();
    dirs<<QString(QDir::homePath()+"/Videos");
    dirs<<QString(QDir::homePath()+"/Pictures");
    dirs<<QString(QDir::homePath()+"/Music");
    dirs<<QString(QDir::homePath()+"/Documents");
    dirs<<QString(QDir::homePath()+"/Downloads");
    //for indonesian
    dirs<<QString(QDir::homePath()+"/Musik");
    dirs<<QString(QDir::homePath()+"/Unduhan");
    dirs<<QString(QDir::homePath()+"/Gambar");
    dirs<<QString(QDir::homePath()+"/Dokumen");
    dirs<<QString(QDir::homePath()+"/Video");

    for(int i=0;i<dirs.count();i++){
        QDir fold(dirs.at(i));
        if(fold.exists())
        {
            cbb_output_path->addItem(dirs.at(i));
        }
    }

    defaultCount=cbb_output_path->count();

    cbb_output_path->insertSeparator(defaultCount);
    if(cbb_output_path->findText(g_output_path)==-1){
        cbb_output_path->addItem(g_output_path);
    }

    if(additionalFolder){
        cbb_output_path->addItems(additionalFolderList);
    }

    cbb_output_path->setCurrentText(g_output_path);
    currenIndex = cbb_output_path->currentIndex();

    connect(cbb_output_path,SIGNAL(activated(int)),this,SLOT(comboOutputFolder(int)));

    QPushButton *pb_add_folder = new QPushButton(tr("Add folder"), this);
    connect(pb_add_folder, SIGNAL(clicked(bool)),this, SLOT(loadFromFolder()));

    QPushButton *pb_change_folder = new QPushButton(tr("Change folder"), this);
    connect(pb_change_folder, SIGNAL(clicked()), this, SLOT(outputDir()));


    QGridLayout *lo_bottom_dc = new QGridLayout;
    lo_bottom_dc->addWidget(cb_append_name, 0, 0);
    lo_bottom_dc->addWidget(pb_add_folder, 0, 2);
    lo_bottom_dc->addWidget(lb_keluaran,1,0);
    lo_bottom_dc->addWidget(cbb_output_path,1,1);
    lo_bottom_dc->addWidget(pb_change_folder,1,2);

    lo_conv_dialog->addLayout(lo_top_dc);
    lo_conv_dialog->addWidget(table_on_d_conv);
    lo_conv_dialog->addLayout(lo_bottom_dc);

    setLayout(lo_conv_dialog);
    setFixedSize(768,460);
    setModal(true);
    if(g_target_format=="cso")
    setWindowTitle("ISO <--> CSO");
    else
    setWindowTitle("-> "+g_target_format.toUpper());

}

void dialogConversion::chooseFiles()
{
    QStringList files_list_;

    if(last_dir.isEmpty())
        last_dir=QDir::homePath();

    switch (g_mediaType){
        case 1:
            files_list_ = QFileDialog::getOpenFileNames(this,"Choose Video files",last_dir , "Videos(*.mp4 *.avi *mkv *.3gp *.webm *.mkv *.gif *.wmv *.mpg *.vob *.mov *.flv *.swf *.dat *.vob *.VOB);;All files(*) ");
            break;
        case 2 :
            files_list_ = QFileDialog::getOpenFileNames(this,"Choose Audio files", last_dir, "Audios(*.mp3 *.wav *.ogg *.flac *.wma *.aac *.amr *.wav *.mp2);;Videos(*.mp4 *.avi *.mkv *.3gp *.webm *.mkv *.gif *.wmv *.mpg *.vob *.mov *.flv *.swf)");
            break;
        case 3 :
            files_list_ = QFileDialog::getOpenFileNames(this,"Choose Images files", last_dir, "Images(*.webp *.svg *.jpeg *.jpg *.png *.ico *.gif *.tif)");
            break;
        case 4 :
            files_list_ = QFileDialog::getOpenFileNames(this,"Choose ISO files", last_dir, "ISO(*.iso *.ISO)");
            break;
    }

    if(!files_list_.empty())
    last_dir = QFileInfo(files_list_.at(0)).path();
    emit sendtToTable(files_list_);
}

void dialogConversion::createTableContents(const QStringList &files_list){
                //untuk konten tabel pada konversi dialog

   int file_count = files_list.count();

    if(table_on_d_conv->rowCount()==0)
                    {

                    table_on_d_conv->setRowCount(file_count);
                    QFileInfo info_berkas;
                    for(int i=0;i<file_count;i++)
                         {
                            QString berkas = files_list.at(i);
                            info_berkas.setFile(berkas);

                            QTableWidgetItem *item_nama = new QTableWidgetItem;
                            item_nama->setText(info_berkas.fileName());
                            item_nama->setToolTip(info_berkas.filePath());
                            table_on_d_conv->setItem(i, 0, item_nama);

                            QTableWidgetItem *item_folder = new QTableWidgetItem;
                            item_folder->setText(info_berkas.path());
                            table_on_d_conv->setItem(i, 1 , item_folder);

                            QTableWidgetItem *item_size = new QTableWidgetItem;
                            float size = (float)info_berkas.size()/1000000;
                            if(size!=0){
                                         item_size->setText(QString::number(size, 'f', 1)+" MB");
                            }
                            else{
                                         item_size->setText("---");
                                         item_size->setTextColor(QColor("red"));
                            }
                            item_size->setTextAlignment(Qt::AlignCenter);
                            table_on_d_conv->setItem(i, 2, item_size);

                            //duration------------------------------------

                            double duration_secs=getDuration(info_berkas.filePath());

                            int durasi = (int)duration_secs;

                            int hour = durasi/3600;
                            int minute = (durasi%3600)/60;
                            int second = (durasi%3600)%60;

                            if(durasi<60)
                                second=durasi;

                            QString xdurasi = QTime(hour, minute, second).toString("HH:mm:ss");

                            QTableWidgetItem *item_durasi = new QTableWidgetItem;

                            if(durasi!=0){
                                item_durasi->setText(xdurasi);}
                            else{
                                item_durasi->setText("---");
                                item_durasi->setTextColor(QColor("red"));
                            }
                            item_durasi->setTextAlignment(Qt::AlignCenter);

                            if(g_mediaType==1){
                            //video size

                            QString vSize = getVideoSize(info_berkas.filePath());
                            QTableWidgetItem *item_vSize = new QTableWidgetItem;

                            if (!vSize.isEmpty()){
                                item_vSize->setText(vSize);
                            }
                            else{
                                item_vSize->setText("---");
                                item_vSize->setTextColor(QColor("red"));
                            }
                            item_vSize->setTextAlignment(Qt::AlignCenter);

                            table_on_d_conv->setItem(i, 3, item_vSize);

                            table_on_d_conv->setItem(i, 4, item_durasi);
                            }//end video

                            if(g_mediaType==2){
                                //audio
                                table_on_d_conv->setItem(i, 3, item_durasi);
                            }

                         }
                    }
            else{

                int before_count = table_on_d_conv->rowCount();
                table_on_d_conv->setRowCount(before_count+file_count);
                int after_count = table_on_d_conv->rowCount();
                QFileInfo info_berkas;
                for(int i=before_count;i<after_count;i++)
                        {
                            QString berkas = files_list.at(i-before_count);
                            info_berkas.setFile(berkas);

                            QTableWidgetItem *item_nama = new QTableWidgetItem;
                            item_nama->setText(info_berkas.fileName());
                            item_nama->setToolTip(info_berkas.filePath());
                            table_on_d_conv->setItem(i, 0, item_nama);

                            QTableWidgetItem *item_folder = new QTableWidgetItem;
                            item_folder->setText(info_berkas.path());
                            table_on_d_conv->setItem(i, 1 , item_folder);

                            QTableWidgetItem *item_size = new QTableWidgetItem;
                            float size = (float)info_berkas.size()/1000000;
                            if(size!=0){
                                item_size->setText(QString::number(size, 'f', 1)+" MB");
                            }
                            else{
                                item_size->setText("---");
                                item_size->setTextColor(QColor("red"));
                            }

                            item_size->setTextAlignment(Qt::AlignCenter);
                            table_on_d_conv->setItem(i, 2, item_size);

                            // get duration------------------------------------
                            double duration_secs=getDuration(info_berkas.filePath());

                            int durasi = (int)duration_secs;

                            int hour = durasi/3600;
                            int minute = (durasi%3600)/60;

                            int second;

                            if(durasi<60)
                                second=durasi;
                            else
                                second = (durasi%3600)%60;

                            QString xdurasi = QTime(hour, minute, second).toString("HH:mm:ss");

                            QTableWidgetItem *item_durasi = new QTableWidgetItem;
                            if(durasi!=0){
                                item_durasi->setText(xdurasi);
                            }
                            else{
                                item_durasi->setText("---");
                                item_size->setTextColor(QColor("red"));
                            }
                            item_durasi->setTextAlignment(Qt::AlignCenter);

                            if(g_mediaType==1){
                            //video size

                            QString vSize = getVideoSize(info_berkas.filePath());
                            QTableWidgetItem *item_vSize = new QTableWidgetItem;
                             if(!vSize.isEmpty()){
                            item_vSize->setText(vSize);
                             }
                             else{
                              item_vSize->setText("---");
                              item_vSize->setTextColor(QColor("red"));
                             }
                            item_vSize->setTextAlignment(Qt::AlignCenter);

                            table_on_d_conv->setItem(i, 3, item_vSize);
                            table_on_d_conv->setItem(i, 4, item_durasi);
                            }//end video

                            if(g_mediaType==2){
                                table_on_d_conv->setItem(i, 3, item_durasi);

                            }

                        }
                }

            if(table_on_d_conv->rowCount()>0){
                table_on_d_conv->selectRow(0);
                pb_ok->setEnabled(true);
                tb_play_file->setEnabled(true);
                tb_clear_list->setEnabled(true);
                tb_delete_item->setEnabled(true);
                //clear_list_action->setEnabled(true);
                tb_mediainfo->setEnabled(true);
                pb_option_on_d_conv->setEnabled(true);
            }
}

void dialogConversion::getMediaInfo(){

    int row = table_on_d_conv->currentRow();
    mediainfo mi;
    mi.setFile(table_on_d_conv->item(row,0)->toolTip());
    mi.exec();
}

void dialogConversion::video_output_dialog_setting(){

    d_output_setting =  new QDialog(this);
    QVBoxLayout *lo_output_setting = new QVBoxLayout(d_output_setting);

    QGridLayout *grid_atas = new QGridLayout;
    QVBoxLayout *lo_top_left = new QVBoxLayout;

    loadFromSetting();
    cbb_parameter = new QComboBox(d_output_setting);
    if(g_target_format=="mp4"){

            cbb_parameter->addItem("High quality and size");
            cbb_parameter->addItem("Medium quality and size");
            cbb_parameter->addItem("Low Quality and size");
            cbb_parameter->addItem("MPEG4 720p");
            cbb_parameter->addItem("MPEG4 480p");
            cbb_parameter->addItem("MPEG4 360p");
            cbb_parameter->addItem("MPEG4 240p");
            cbb_parameter->addItem("AVC High quality and size");
            cbb_parameter->addItem("AVC Medium quality and size");
            cbb_parameter->addItem("AVC Low quality and size");
            cbb_parameter->addItem("AVC 720p");
            cbb_parameter->addItem("AVC 480p");
            cbb_parameter->addItem("AVC 360p");
            cbb_parameter->addItem("AVC 240p");
            cbb_parameter->setCurrentText(mp4_quality);
            connect(cbb_parameter,SIGNAL(activated(int)),this,SLOT(on_cbb_parameter_mp4_changed(int)));
    }

    if(g_target_format=="avi"){

        cbb_parameter->addItem("High quality and size");
        cbb_parameter->addItem("Medium quality and size");
        cbb_parameter->addItem("Low Quality and size");
        cbb_parameter->addItem("Xvid 720p");
        cbb_parameter->addItem("Xvid 480p");
        cbb_parameter->addItem("Xvid 360p");
        cbb_parameter->addItem("Xvid 240p");
        cbb_parameter->addItem("High quality and size");
        cbb_parameter->addItem("Medium quality and size");
        cbb_parameter->addItem("Low Quality and size");
        cbb_parameter->addItem("DivX 720p");
        cbb_parameter->addItem("DivX 480p");
        cbb_parameter->addItem("DivX 360p");
        cbb_parameter->addItem("DivX 240p");
        cbb_parameter->addItem("AVC High quality and size");
        cbb_parameter->addItem("AVC Medium quality and size");
        cbb_parameter->addItem("AVC Low quality and size");
        cbb_parameter->addItem("AVC 720p");
        cbb_parameter->addItem("AVC 480p");
        cbb_parameter->addItem("AVC 360p");
        cbb_parameter->addItem("AVC 240p");
        cbb_parameter->setCurrentText(avi_quality);
        connect(cbb_parameter,SIGNAL(activated(int)),this,SLOT(on_cbb_parameter_avi_changed(int)));
    }

    if(g_target_format=="3gp"){
        cbb_parameter->addItem("176x144 H263");
        cbb_parameter->addItem("352x288 H263");
        cbb_parameter->addItem("176x144 MPEG4");
        cbb_parameter->addItem("352x288 MPEG4");
        cbb_parameter->setCurrentText(_3gp_quality);
        connect(cbb_parameter,SIGNAL(activated(int)),this,SLOT(on_cbb_parameter_3gp_changed(int)));
    }

    if(g_target_format=="webm"){

        cbb_parameter->addItem("webm");

    }

    if(g_target_format=="mkv"){
        cbb_parameter->addItem("High quality and size");
        cbb_parameter->addItem("Medium quality and size");
        cbb_parameter->addItem("Low quality and size");
        cbb_parameter->addItem("AVC 360p");
        cbb_parameter->addItem("AVC 480p");
        cbb_parameter->addItem("AVC 720p ");
        cbb_parameter->addItem("AVC 1080p");
        cbb_parameter->setCurrentText(mkv_quality);
        connect(cbb_parameter,SIGNAL(activated(int)),this,SLOT(on_cbb_parameter_mkv_changed(int)));
    }

    if(g_target_format=="gif"){
        cbb_parameter->addItem("96p");
        cbb_parameter->addItem("144p");
        cbb_parameter->addItem("240p");
        cbb_parameter->addItem("320i");
        cbb_parameter->setCurrentText(gif_quality);
    }

    if(g_target_format=="wmv"){
        cbb_parameter->addItem("High quality and size");
        cbb_parameter->addItem("Medium quality and size");
        cbb_parameter->addItem("Low quality and size");
        cbb_parameter->addItem("480p");
        cbb_parameter->addItem("360p");
        cbb_parameter->addItem("240p");
        cbb_parameter->setCurrentText(wmv_quality);
        connect(cbb_parameter,SIGNAL(activated(int)),this,SLOT(on_cbb_parameter_wmv_changed(int)));
    }

    if(g_target_format=="mpg"){
        cbb_parameter->addItem("VCD PAL");
        cbb_parameter->addItem("VCD NTSC");
        cbb_parameter->addItem("SVCD PAL");
        cbb_parameter->addItem("SVCD NTSC");
        cbb_parameter->addItem("DVD PAL Small");
        cbb_parameter->addItem("DVD PAL Large");
        cbb_parameter->addItem("DVD NTSC Small");
        cbb_parameter->addItem("DVD NTSC Large");
        cbb_parameter->setCurrentText(mpg_quality);
        connect(cbb_parameter,SIGNAL(activated(int)),this,SLOT(on_cbb_parameter_mpg_changed(int)));
    }

    if(g_target_format=="vob"){
        cbb_parameter->addItem("DVD PAL Small");
        cbb_parameter->addItem("DVD PAL Large");
        cbb_parameter->addItem("DVD NTSC Small");
        cbb_parameter->addItem("DVD NTSC Large");
        cbb_parameter->setCurrentText(vob_quality);
        connect(cbb_parameter,SIGNAL(activated(int)),this,SLOT(on_cbb_parameter_vob_changed(int)));
    }

    if(g_target_format=="mov"){
        cbb_parameter->addItem("High quality and size");
        cbb_parameter->addItem("Medium quality and size");
        cbb_parameter->addItem("Low quality and size");
        cbb_parameter->addItem("320x240");
        cbb_parameter->addItem("640x360 Widescreen");
        cbb_parameter->addItem("640x480");
        cbb_parameter->setCurrentText(mov_quality);
        connect(cbb_parameter,SIGNAL(activated(int)),this,SLOT(on_cbb_parameter_mov_changed(int)));
    }

    if(g_target_format=="flv"){
        cbb_parameter->addItem("320x240");
        cbb_parameter->addItem("640x480");
        cbb_parameter->addItem("176x144");
        cbb_parameter->setCurrentText(flv_quality);
        connect(cbb_parameter,SIGNAL(activated(int)),this,SLOT(on_cbb_parameter_flv_changed(int)));
    }

    if(g_target_format=="swf"){
        cbb_parameter->addItem("320x240");
        cbb_parameter->addItem("640x480");
        cbb_parameter->addItem("176x144");
        cbb_parameter->setCurrentText(swf_quality);
        connect(cbb_parameter,SIGNAL(activated(int)),this,SLOT(on_cbb_parameter_swf_changed(int)));
    }
    lo_top_left->addWidget(cbb_parameter);

    QPushButton *pb_ok_atur_keluaran = new QPushButton("OK", d_output_setting);
    connect(pb_ok_atur_keluaran,SIGNAL(clicked(bool)),this,SLOT(saveParameter()));

    grid_atas->addLayout(lo_top_left,0,0);
    grid_atas->addWidget(pb_ok_atur_keluaran,0,1);

    output_setting_table = new QTreeWidget(d_output_setting);
    output_setting_table->setColumnCount(2);
    output_setting_table->setHeaderLabels(QString("Setting;Value").split(";"));
    output_setting_table->setAlternatingRowColors(true);
    output_setting_table->header()->setSectionResizeMode(QHeaderView::Stretch);

        QTreeWidgetItem *typeItem = new QTreeWidgetItem(output_setting_table);
        typeItem->setText(0, "Type");
        typeItem->setText(1, g_target_format.toUpper());

        QTreeWidgetItem *video_stream_item = new QTreeWidgetItem(output_setting_table);
        video_stream_item->setText(0, "Video stream");
        video_stream_item->setExpanded(true);

                QTreeWidgetItem *video_encoder_item = new QTreeWidgetItem(video_stream_item);
                video_encoder_item->setText(0,"Video encoder");

                cbb_v_encoder = new QComboBox;

                if(g_target_format=="mp4"){
                    cbb_v_encoder->addItem("MPEG4(DivX)");
                    cbb_v_encoder->addItem("MPEG4(Xvid)");
                    cbb_v_encoder->addItem("AVC(H264)");
                    cbb_v_encoder->setCurrentText(mp4_v_encoder);
                }

                else if(g_target_format=="avi"){
                    cbb_v_encoder->addItem("MPEG4(DivX)");
                    cbb_v_encoder->addItem("MPEG4(Xvid)");
                    cbb_v_encoder->addItem("AVC(H264)");
                    cbb_v_encoder->setCurrentText(avi_v_encoder);
                }

                else if(g_target_format=="3gp"){
                    cbb_v_encoder->addItem("MPEG4(DivX)");
                    cbb_v_encoder->addItem("H263");
                    cbb_v_encoder->setCurrentText(_3gp_v_encoder);
                }

                else if(g_target_format=="mkv"){
                    cbb_v_encoder->addItem("MPEG4(DivX)");
                    cbb_v_encoder->addItem("MPEG4(Xvid)");
                    cbb_v_encoder->addItem("AVC(H264)");
                    cbb_v_encoder->addItem("copy");
                    cbb_v_encoder->setCurrentText(mkv_v_encoder);
                }

                else if(g_target_format=="gif"){
                    cbb_v_encoder->addItem("MPEG4 (DivX)");
                    cbb_v_encoder->addItem("MPEG4 (Xvid)");
                    cbb_v_encoder->addItem("AVC(H264)");
                    cbb_v_encoder->addItem("MSMPEG4V2");
                    cbb_v_encoder->addItem("WMV2");
                    cbb_v_encoder->addItem("FLV1");
                    cbb_v_encoder->addItem("MPEG2");
                    cbb_v_encoder->addItem("MJPEG");
                    cbb_v_encoder->addItem("copy");
                }

                else if(g_target_format=="wmv"){
                    cbb_v_encoder->addItem("WMV2");
                    cbb_v_encoder->addItem("MSMPEG4V2");
                    cbb_v_encoder->setCurrentText(wmv_v_encoder);
                 }

                else if(g_target_format=="mpg"){
                    cbb_v_encoder->addItem("MPEG1");
                    cbb_v_encoder->setEnabled(false);
                }

                else if(g_target_format=="vob"){
                    cbb_v_encoder->addItem("MPEG2");
                   }

                else if(g_target_format=="mov"){
                    cbb_v_encoder->addItem("AVC(H264)");
                    cbb_v_encoder->addItem("MPEG4(DivX)");
                    cbb_v_encoder->setCurrentText(mov_v_encoder);
                }

                else if(g_target_format=="flv"){
                    cbb_v_encoder->addItem("FLV1");
                    cbb_v_encoder->setEnabled(false);
                }

                else if(g_target_format=="swf"){
                    cbb_v_encoder->addItem("MPEG4(DivX)");
                    cbb_v_encoder->addItem("MPEG4(Xvid)");
                    cbb_v_encoder->addItem("MSMPEG4V2");
                    cbb_v_encoder->addItem("FLV1");
                    cbb_v_encoder->addItem("MPEG2");
                    cbb_v_encoder->addItem("MJPEG");
                    cbb_v_encoder->addItem("copy");
                    cbb_v_encoder->setCurrentText(swf_v_encoder);
                }
                output_setting_table->setItemWidget(video_encoder_item,1,cbb_v_encoder);

                QTreeWidgetItem *video_size_item = new QTreeWidgetItem(video_stream_item);
                video_size_item->setText(0,"Video size");

                cbb_v_size = new QComboBox;

                if(g_target_format=="mp4" || g_target_format=="avi" || g_target_format=="mkv" || g_target_format=="gif" || g_target_format=="wmv" || g_target_format=="mpg"
                        || g_target_format=="vob" || g_target_format=="mov"|| g_target_format=="flv"|| g_target_format=="swf"){
                    cbb_v_size->addItem("Default");
                    cbb_v_size->addItem("320x240 standard");
                    cbb_v_size->addItem("400x240 mobile standard");
                    cbb_v_size->addItem("480x320 mobile standard");
                    cbb_v_size->addItem("480x272 mobile standard");
                    cbb_v_size->addItem("480x360 mobile standard");
                    cbb_v_size->addItem("720x480 HD Device");
                    cbb_v_size->addItem("720x576 HD Device");
                    cbb_v_size->addItem("1280x720 HQ Device");
                    cbb_v_size->addItem("1920x1080 HQ Device");
                    cbb_v_size->addItem("128x96 subQCIF");
                    cbb_v_size->addItem("176x144 QCIF");
                    cbb_v_size->addItem("352x288 CIF");
                    cbb_v_size->addItem("160x120 QQVGA");
                    cbb_v_size->addItem("320x240 QVGA");
                    cbb_v_size->addItem("640x480 VGA");
                    cbb_v_size->addItem("800x600 SVGA");
                    cbb_v_size->addItem("1024x768 XVGA");
                    cbb_v_size->addItem("50%");
                    cbb_v_size->addItem("200%");
                    cbb_v_size->addItem("360p");
                    cbb_v_size->addItem("480p");
                    cbb_v_size->addItem("720p");
                    cbb_v_size->addItem("1080p");
                    cbb_v_size->addItem("480i");
                    cbb_v_size->addItem("720i");
                    cbb_v_size->addItem("1280i");
                    cbb_v_size->addItem("1920i");
                    }

                QMap<QString, QString> vsizemap;
                vsizemap["mp4"]=mp4_v_size;
                vsizemap["avi"]=avi_v_size;
                vsizemap["mkv"]=mkv_v_size;
                vsizemap["wmv"]=wmv_v_size;
                vsizemap["mpg"]=mpg_v_size;
                vsizemap["vob"]=vob_v_size;
                vsizemap["mov"]=mov_v_size;
                vsizemap["flv"]=flv_v_size;
                vsizemap["swf"]=swf_v_size;
                setComboValue(cbb_v_size,vsizemap[g_target_format]);

                if(g_target_format=="3gp"){
                    cbb_v_size->addItem("128x96");
                    cbb_v_size->addItem("176x144");
                    cbb_v_size->addItem("352x388");
                    cbb_v_size->setCurrentText(_3gp_v_size);
                }

               output_setting_table->setItemWidget(video_size_item,1,cbb_v_size);

                QTreeWidgetItem *video_bitrate_item = new QTreeWidgetItem(video_stream_item);
                video_bitrate_item->setText(0,"Bitrate (KB/s)");

                cbb_v_bitrate = new QComboBox;
                if (g_target_format=="mp4"|| g_target_format=="avi" || g_target_format=="mkv" || g_target_format=="wmv" || g_target_format=="mpg" ||
                        g_target_format=="vob" || g_target_format=="mov" || g_target_format=="flv" || g_target_format=="swf"){
                    cbb_v_bitrate->addItem("Default");
                    cbb_v_bitrate->addItem("256");
                    cbb_v_bitrate->addItem("384");
                    cbb_v_bitrate->addItem("512");
                    cbb_v_bitrate->addItem("768");
                    cbb_v_bitrate->addItem("1024");
                    cbb_v_bitrate->addItem("1200");
                    cbb_v_bitrate->addItem("1600");
                    cbb_v_bitrate->addItem("2400");
                    cbb_v_bitrate->addItem("5000");
                    cbb_v_bitrate->addItem("10000");
                    cbb_v_bitrate->addItem("16000");
                }

                QMap<QString, QString> vbitmap;
                vbitmap["mp4"]=mp4_v_bitrate;
                vbitmap["avi"]=avi_v_bitrate;
                vbitmap["3gp"]=_3gp_v_bitrate;
                vbitmap["mkv"]=mkv_v_bitrate;
                vbitmap["wmv"]=wmv_v_bitrate;
                vbitmap["mpg"]=mpg_v_bitrate;
                vbitmap["vob"]=vob_v_bitrate;
                vbitmap["mov"]=mov_v_bitrate;
                vbitmap["flv"]=flv_v_bitrate;
                vbitmap["swf"]=swf_v_bitrate;
                setComboValue(cbb_v_bitrate, vbitmap[g_target_format]);

                if(g_target_format=="3gp"){
                    cbb_v_bitrate->addItem("Default");
                    cbb_v_bitrate->addItem("96");
                    cbb_v_bitrate->addItem("128");
                    cbb_v_bitrate->addItem("160");
                    cbb_v_bitrate->addItem("192");
                    cbb_v_bitrate->addItem("256");
                    cbb_v_bitrate->addItem("384");
                    cbb_v_bitrate->setCurrentText(_3gp_v_bitrate);
                }

                else if(g_target_format=="gif")
                {
                     cbb_v_bitrate->addItem("Default");
                     cbb_v_bitrate->setEnabled(false);
                }
                output_setting_table->setItemWidget(video_bitrate_item,1,cbb_v_bitrate);

                QTreeWidgetItem *video_fps_item = new QTreeWidgetItem(video_stream_item);
                video_fps_item->setText(0,"FPS");

                cbb_v_fps = new QComboBox;
                cbb_v_fps->addItem("Default");
                cbb_v_fps->addItem("12");
                cbb_v_fps->addItem("15");
                cbb_v_fps->addItem("18");
                cbb_v_fps->addItem("20");
                cbb_v_fps->addItem("23.976");
                cbb_v_fps->addItem("24");
                cbb_v_fps->addItem("25");
                cbb_v_fps->addItem("29.97");
                cbb_v_fps->addItem("30");

                QMap <QString, QString> fpsmap;
                fpsmap["mp4"]=mp4_v_fps;
                fpsmap["avi"]=avi_v_fps_avi;
                fpsmap["3gp"]=_3gp_v_fps;
                fpsmap["mkv"]=mkv_v_fps;
                fpsmap["wmv"]=wmv_v_fps;
                fpsmap["mpg"]=mpg_v_fps;
                fpsmap["vob"]=vob_v_fps;
                fpsmap["mov"]=mov_v_fps;
                fpsmap["flv"]=flv_v_fps;
                fpsmap["swf"]=swf_v_fps;
                cbb_v_fps->setCurrentText(fpsmap[g_target_format]);

                output_setting_table->setItemWidget(video_fps_item,1,cbb_v_fps);

                QTreeWidgetItem *video_ratio_item = new QTreeWidgetItem(video_stream_item);
                video_ratio_item->setText(0,"Aspect ratio");

                cbb_v_ratio = new QComboBox;
                cbb_v_ratio->addItem("Automatic");
                cbb_v_ratio->addItem("Automatic(Width)");
                cbb_v_ratio->addItem("Automatic(height)");
                cbb_v_ratio->addItem("Fully expand");
                cbb_v_ratio->addItem("16:9");
                cbb_v_ratio->addItem("4:3");
                cbb_v_ratio->addItem("3:2");
                cbb_v_ratio->addItem("5:4");

                QMap <QString,QString> vratiomap;
                vratiomap["mp4"]=mp4_v_ratio;
                vratiomap["avi"]=avi_v_ratio;
                vratiomap["3gp"]=_3gp_v_ratio;
                vratiomap["mkv"]=mkv_v_ratio;
                vratiomap["wmv"]=wmv_v_ratio;
                vratiomap["mpg"]=mpg_v_ratio;
                vratiomap["vob"]=vob_v_ratio;
                vratiomap["mov"]=mov_v_ratio;
                vratiomap["flv"]=flv_v_ratio;
                vratiomap["swf"]=swf_v_ratio;
                cbb_v_ratio->setCurrentText(vratiomap[g_target_format]);

                if(g_target_format=="gif")
                {
                    cbb_v_ratio->addItem("Automatic(Width)");
                    cbb_v_ratio->setEnabled(false);
                }
                output_setting_table->setItemWidget(video_ratio_item,1,cbb_v_ratio);

// audio------------------------------------------------------
        QTreeWidgetItem *audio_stream_item = new QTreeWidgetItem(output_setting_table);
        audio_stream_item->setText(0, "Audio stream");
        audio_stream_item->setExpanded(true);

                QTreeWidgetItem *audio_encoder_item = new QTreeWidgetItem(audio_stream_item);
                audio_encoder_item->setText(0,"Audio encoder");

                cbb_a_encoder = new QComboBox;
                if(g_target_format=="mp4"){
                    cbb_a_encoder->addItem("AAC");
                }

                else if(g_target_format=="avi"){
                    cbb_a_encoder->addItem("MP3");
                    cbb_a_encoder->addItem("MP3-VBR");
                    cbb_a_encoder->addItem("MP2");
                    cbb_a_encoder->addItem("AC3");
                    cbb_a_encoder->addItem("WMAv2");
                    cbb_a_encoder->addItem("PCM");
                    cbb_a_encoder->addItem("Copy");
                    cbb_a_encoder->setCurrentText(avi_a_encoder);
                }

                else if (g_target_format=="3gp"){
                    cbb_a_encoder->addItem("AMR_NB");
                    cbb_a_encoder->addItem("AMR_WB");
                    cbb_a_encoder->setCurrentText(_3gp_a_encoder);
                }

                else if(g_target_format=="mkv"){
                    cbb_a_encoder->addItem("AAC");
                    cbb_a_encoder->addItem("MP3");
                    cbb_a_encoder->addItem("AC3");
                    cbb_a_encoder->addItem("copy");
                    cbb_a_encoder->setCurrentText(mkv_a_encoder);
                }

                else if(g_target_format=="wmv"){
                    cbb_a_encoder->addItem("WMAV2");
                }

                else if(g_target_format=="mpg"){
                    cbb_a_encoder->addItem("MP2");
                    cbb_a_encoder->addItem("AC3");
                    cbb_a_encoder->setCurrentText(mpg_a_encoder);
                    cbb_a_encoder->setEnabled(false);
                }

                else if(g_target_format=="vob"){
                    cbb_a_encoder->addItem("AC3");
                    cbb_a_encoder->setCurrentText(vob_a_encoder);
                    cbb_a_encoder->setEnabled(false);
                }

                else if(g_target_format=="mov"){
                    cbb_a_encoder->addItem("AAC");
                    cbb_a_encoder->addItem("MP3");
                    cbb_a_encoder->setCurrentText(mov_a_encoder);
                }

                else if(g_target_format=="flv"){
                    cbb_a_encoder->addItem("MP3");
                    cbb_a_encoder->setEnabled(false);
                }

                else if(g_target_format=="swf"){
                     cbb_a_encoder->addItem("MP3");
                     cbb_a_encoder->addItem("MP3-VBR");
                     cbb_a_encoder->addItem("MP2");
                     cbb_a_encoder->addItem("AC3");
                     cbb_a_encoder->addItem("WMAv2");
                     cbb_a_encoder->addItem("PCM");
                     cbb_a_encoder->addItem("Copy");
                     cbb_a_encoder->setCurrentText(swf_a_encoder);
                }
                output_setting_table->setItemWidget(audio_encoder_item,1,cbb_a_encoder);

                QTreeWidgetItem *sample_rate_item = new QTreeWidgetItem(audio_stream_item);
                sample_rate_item->setText(0,"Sample rate (Hz)");

                cbb_a_srate = new QComboBox;
                if(g_target_format=="mp4" || g_target_format=="avi" || g_target_format=="mkv" || g_target_format=="wmv" || g_target_format=="mpg"
                        || g_target_format=="vob" || g_target_format=="mov" || g_target_format=="flv" || g_target_format=="swf"){
                    cbb_a_srate->addItem("Default");
                    cbb_a_srate->addItem("22050");
                    cbb_a_srate->addItem("44100");
                    cbb_a_srate->addItem("24000");
                    cbb_a_srate->addItem("48000");
                }

                if(g_target_format=="mp4"){
                   setComboValue(cbb_a_srate, mp4_a_a_srate);
                }

                if(g_target_format=="avi"){

                       setComboValue(cbb_a_srate, avi_a_a_srate);
                }

                if(g_target_format=="3gp"){
                    cbb_a_srate->addItem("8000");
                }

                if(g_target_format=="mkv"){

                       setComboValue(cbb_a_srate, mkv_a_a_srate);
                }

                if(g_target_format=="wmv"){
                    setComboValue(cbb_a_srate, wmv_a_a_srate);
                }

                if(g_target_format=="mpg"){
                     setComboValue(cbb_a_srate, mpg_a_a_srate);
                }

                if(g_target_format=="vob"){
                 setComboValue(cbb_a_srate, vob_a_a_srate);
                }
                if(g_target_format=="mov"){
                 setComboValue(cbb_a_srate, mov_a_a_srate);
                }

                if(g_target_format=="flv"){
                 setComboValue(cbb_a_srate, flv_a_a_srate);
                }

                if(g_target_format=="swf"){
                 setComboValue(cbb_a_srate, swf_a_a_srate);
                }

                output_setting_table->setItemWidget(sample_rate_item,1,cbb_a_srate);

                QTreeWidgetItem *audio_bitrate_item = new QTreeWidgetItem(audio_stream_item);
                audio_bitrate_item->setText(0,"Bitrate (KB/s)");

                cbb_a_bitrate = new QComboBox;
                if(g_target_format=="mp4" || g_target_format=="avi" || g_target_format=="mkv" || g_target_format=="wmv" || g_target_format=="mpg"
                        || g_target_format=="vob" || g_target_format=="mov" || g_target_format=="flv" || g_target_format=="swf"){
                    cbb_a_bitrate->addItem("Default");
                    cbb_a_bitrate->addItem("24");
                    cbb_a_bitrate->addItem("32");
                    cbb_a_bitrate->addItem("64");
                    cbb_a_bitrate->addItem("96");
                    cbb_a_bitrate->addItem("128");
                    cbb_a_bitrate->addItem("192");
                    cbb_a_bitrate->addItem("224");
                    cbb_a_bitrate->addItem("256");
                    cbb_a_bitrate->addItem("320");

                }


                else if(g_target_format=="3gp"){
                    cbb_a_bitrate->addItem("12.20");
                    cbb_a_bitrate->addItem("10.20");
                    cbb_a_bitrate->addItem("7.40");
                    cbb_a_bitrate->addItem("4.75");
                    cbb_a_bitrate->setCurrentText(_3gp_a_bitrate);
                }

                            QMap <QString,QString> abit_map;
                            abit_map["mp4"]=mp4_a_bitrate;
                            abit_map["avi"]=avi_a_bitrate;
                            abit_map["mkv"]=mkv_a_bitrate;
                            abit_map["wmv"]=wmv_a_bitrate;
                            abit_map["mpg"]=mpg_a_bitrate;
                            abit_map["vob"]=vob_a_bitrate;
                            abit_map["mov"]=mov_v_bitrate;
                            abit_map["flv"]=flv_a_bitrate;
                            abit_map["swf"]=swf_a_bitrate;

                            setComboValue(cbb_a_bitrate, abit_map[g_target_format]);

                output_setting_table->setItemWidget(audio_bitrate_item,1,cbb_a_bitrate);

                QTreeWidgetItem *audio_channel_item = new QTreeWidgetItem(audio_stream_item);
                audio_channel_item->setText(0,"Audio channel");

                cbb_a_channel = new QComboBox;
                if(g_target_format=="mp4" || g_target_format=="avi" || g_target_format=="mkv" || g_target_format=="wmv" || g_target_format=="mpg"
                        || g_target_format=="vob" || g_target_format=="mov" || g_target_format=="flv"){
                    cbb_a_channel->addItem("Default");
                    cbb_a_channel->addItem("2 stereo");
                    cbb_a_channel->addItem("6 stereo 5.1");
                    cbb_a_channel->addItem("4 stereo");
                    cbb_a_channel->addItem("1 mono");
                }

                if(g_target_format=="3gp"){
                    cbb_a_channel->addItem("1");
                }

                QMap<QString, QString> acmap;
                acmap["mp4"]=mp4_a_channel;
                acmap["avi"]=avi_a_channel;
                acmap["mkv"]=mkv_a_channel;
                acmap["wmv"]=wmv_a_channel;
                acmap["mpg"]=mpg_a_channel;
                acmap["vob"]=vob_a_channel;
                acmap["mov"]=mov_a_channel;
                acmap["flv"]=flv_a_channel;
                acmap["swf"]=swf_a_channel;
                setComboValue(cbb_a_channel, acmap[g_target_format]);

                output_setting_table->setItemWidget(audio_channel_item,1,cbb_a_channel);

                QTreeWidgetItem *disable_a_item = new QTreeWidgetItem(audio_stream_item);
                disable_a_item->setText(0,"Disable audio");

                QComboBox *cbb_disable_audio = new QComboBox;
                cbb_disable_audio->addItem("Yes");
                cbb_disable_audio->addItem("No");
                cbb_disable_audio->setCurrentIndex(1);

                output_setting_table->setItemWidget(disable_a_item,1,cbb_disable_audio);

                QTreeWidgetItem *volume_control_item = new QTreeWidgetItem(audio_stream_item);
                volume_control_item->setText(0,"Volume control (+dB)");

                QComboBox * combo_sound = new QComboBox;
                combo_sound->addItem("12dB");
                combo_sound->addItem("10dB");
                combo_sound->addItem("6dB");
                combo_sound->addItem("3dB");
                combo_sound->addItem("0dB");
                combo_sound->addItem("-3dB");
                combo_sound->addItem("-6dB");
                combo_sound->addItem("-10dB");
                combo_sound->setCurrentIndex(4);

                output_setting_table->setItemWidget(volume_control_item,1,combo_sound);

                QTreeWidgetItem *stream_index_item = new QTreeWidgetItem(audio_stream_item);
                stream_index_item->setText(0,"Audio stream index");

        QTreeWidgetItem *subtitle_item = new QTreeWidgetItem(output_setting_table);
        subtitle_item->setText(0, "Additional subtitle");



        QTreeWidgetItem *watermark_item = new QTreeWidgetItem(output_setting_table);
        watermark_item->setText(0, "Watermark");

            QTreeWidgetItem *watermark1_item = new QTreeWidgetItem(watermark_item);
            watermark1_item->setText(0,"Watermark (jpg;png;bmp)");

            pb_wt = new QPushButton("...");
            connect(pb_wt,SIGNAL(clicked(bool)),this,SLOT(getWatermarkFile()));
            output_setting_table->setItemWidget(watermark1_item,1,pb_wt);



            QTreeWidgetItem *position_item = new QTreeWidgetItem(watermark_item);
            position_item->setText(0,"Position");

            QComboBox *cbb_pos_wt = new QComboBox;
            cbb_pos_wt->addItem("Bottom Right");
            cbb_pos_wt->addItem("Bottom Left");
            cbb_pos_wt->addItem("Top Right");
            cbb_pos_wt->addItem("Top Left");
            cbb_pos_wt->addItem("Center");

            output_setting_table->setItemWidget(position_item,1,cbb_pos_wt);


            QTreeWidgetItem *margin_item = new QTreeWidgetItem(watermark_item);
            margin_item->setText(0,"Margin");

            QComboBox *cbb_margin_wt = new QComboBox;
            cbb_margin_wt->addItem("0%");
            cbb_margin_wt->addItem("5%");
            cbb_margin_wt->addItem("10%");

            output_setting_table->setItemWidget(margin_item,1,cbb_margin_wt);

    lo_output_setting->addLayout(grid_atas);
    lo_output_setting->addWidget(output_setting_table);
    d_output_setting->setWindowTitle(g_target_format.toUpper()+" Setting");
    d_output_setting->setLayout(lo_output_setting);
    d_output_setting->setFixedSize(680,560);
    d_output_setting->exec();
}

 void dialogConversion::setComboValue(QComboBox *c, const QString &s){
     //set combo if the current item doesnt exist in combo list
         if(c->findText(s)==-1){
                insertSpecialItem(c,s);
         }
         else{
                c->setCurrentText(s);
             }
}

void dialogConversion::getWatermarkFile(){
    QString nf = QFileDialog::getOpenFileName(d_output_setting,"Choose file",QDir::homePath(),"Image Files (*.png *.jpg *.bmp)");

    QMap<QString,bool>mapwmb;
    mapwmb["mp4"]=mp4_wm;
    mapwmb["avi"]=avi_wm;

            QMap<QString,QString>mapwmf;
            mapwmf["mp4"]=mp4_wm_file;
            mapwmf["avi"]=avi_wm_file;

    if(!nf.isEmpty()){
         pb_wt->setText(nf);

         mapwmb[g_target_format]=true;
         mapwmf[g_target_format]=nf;
         qDebug()<<"bool_wm"<<mapwmb[g_target_format]<<"file"<<mapwmf[g_target_format];




    }
}

QString dialogConversion::getWatermarkParam(QString f, QString *p){

    struct swm{
        QString file;
        QString wmpos;
        QString wmmargin;
    };

    swm wmf;
    if(f=="mp4"){
        wmf.file=mp4_wm_file;
    }

    else if(f=="avi"){
        wmf.file=avi_wm_file;
    }

    return "-i;"+wmf.file+";-filter_complex"+"\"overlay=x=(main_w-overlay_w)/2:y=(main_h-overlay_h)/2\"";

}

void dialogConversion::audio_output_dialog_setting()
{
    d_output_setting =  new QDialog(this);
    QVBoxLayout *lo_output_setting = new QVBoxLayout;

    QGridLayout *grid_atas = new QGridLayout;
    QVBoxLayout *lo_top_left = new QVBoxLayout;

    loadFromSetting();

    cbb_parameter = new QComboBox;

    if(g_target_format=="mp3" || g_target_format=="wma" ||g_target_format=="aac" || g_target_format=="m4a" || g_target_format=="m4r" || g_target_format=="ogg" || g_target_format=="mp2"){
        cbb_parameter->addItem("High quality");
        cbb_parameter->addItem("Medium quality");
        cbb_parameter->addItem("Low quality");

                    if(g_target_format=="mp3"){
                        cbb_parameter->setCurrentText(mp3_quality);
                        connect(cbb_parameter,SIGNAL(activated(int)),this,SLOT(on_cbb_parameter_mp3_changed(int)));
                    }

                    else if(g_target_format=="wma"){
                        cbb_parameter->setCurrentText(wma_quality);
                        connect(cbb_parameter,SIGNAL(activated(int)),this,SLOT(on_cbb_parameter_wma_changed(int)));
                    }

                    else if(g_target_format=="aac"){
                        cbb_parameter->setCurrentText(aac_quality);
                        connect(cbb_parameter,SIGNAL(activated(int)),this,SLOT(on_cbb_parameter_aac_changed(int)));
                    }

                    else if(g_target_format=="m4a"){
                        cbb_parameter->setCurrentText(m4a_quality);
                        connect(cbb_parameter,SIGNAL(activated(int)),this,SLOT(on_cbb_parameter_m4a_changed(int)));
                    }

                    else if(g_target_format=="m4r"){
                        cbb_parameter->setCurrentText(m4r_quality);
                        connect(cbb_parameter,SIGNAL(activated(int)),this,SLOT(on_cbb_parameter_m4r_changed(int)));
                    }

                    else if(g_target_format=="ogg"){
                        cbb_parameter->setCurrentText(ogg_quality);
                        connect(cbb_parameter,SIGNAL(activated(int)),this,SLOT(on_cbb_parameter_ogg_changed(int)));
                    }

                    else if(g_target_format=="mp2"){
                        cbb_parameter->setCurrentText(mp2_quality);
                        connect(cbb_parameter,SIGNAL(activated(int)),this,SLOT(on_cbb_parameter_mp2_changed(int)));
                    }

                    else if(g_target_format=="ape"){
                        cbb_parameter->addItem("High quality");
                    }
    }

    else if(g_target_format=="flac" || g_target_format=="wav"){
        cbb_parameter->addItem("High quality");
        cbb_parameter->addItem("Medium quality");
        cbb_parameter->addItem("Low quality");
        cbb_parameter->addItem("7.1 Stereo");
        cbb_parameter->addItem("5.1 Stereo");

                if(g_target_format=="flac"){
                            cbb_parameter->setCurrentText(flac_quality);
                            connect(cbb_parameter,SIGNAL(activated(int)),this,SLOT(on_cbb_parameter_flac_changed(int)));
                        }
                if(g_target_format=="wav"){
                            cbb_parameter->setCurrentText(wav_quality);
                                connect(cbb_parameter,SIGNAL(activated(int)),this,SLOT(on_cbb_parameter_wav_changed(int)));
                        }

    }


    else if(g_target_format=="mmf" || g_target_format=="amr"){
        cbb_parameter->addItem("High quality");
        cbb_parameter->addItem("Low quality");

                if(g_target_format=="mmf"){
                       cbb_parameter->setCurrentText(mmf_quality);
                       connect(cbb_parameter,SIGNAL(activated(int)),this,SLOT(on_cbb_parameter_mmf_changed(int)));
                   }
                if(g_target_format=="amr"){
                        cbb_parameter->setCurrentText(amr_quality);
                        connect(cbb_parameter,SIGNAL(activated(int)),this,SLOT(on_cbb_parameter_amr_changed(int)));
                    }
    }

    lo_top_left->addWidget(cbb_parameter);

    QPushButton *pb_ok_atur_keluaran = new QPushButton("OK");
    connect(pb_ok_atur_keluaran,SIGNAL(clicked(bool)),this,SLOT(saveParameter()));


    grid_atas->addLayout(lo_top_left,0,0);
    grid_atas->addWidget(pb_ok_atur_keluaran,0,1);

    output_setting_table = new QTreeWidget;
    output_setting_table->setColumnCount(2);
    output_setting_table->setHeaderLabels(QString("Setting;Value").split(";"));
    output_setting_table->setAlternatingRowColors(true);
    output_setting_table->header()->setSectionResizeMode(QHeaderView::Stretch);



        QTreeWidgetItem *typeItem = new QTreeWidgetItem(output_setting_table);
        typeItem->setText(0, "Type");
        typeItem->setText(1, g_target_format.toUpper());

        QTreeWidgetItem *audio_stream_item = new QTreeWidgetItem(output_setting_table);
        audio_stream_item->setText(0, "Audio stream");
        audio_stream_item->setExpanded(true);


        QTreeWidgetItem *audio_a_srate_item = new QTreeWidgetItem(audio_stream_item);
        audio_a_srate_item->setText(0,"Sample rate (Hz)");

        cbb_a_srate = new QComboBox;

        if(g_target_format=="mp3" || g_target_format=="mp2"){
            cbb_a_srate->addItem("Automatic");
            cbb_a_srate->addItem("48000");
            cbb_a_srate->addItem("44100");
            cbb_a_srate->addItem("22050");
            cbb_a_srate->addItem("11025");
        }


        else if(g_target_format=="wma"|| g_target_format=="ape"|| g_target_format=="flac" || g_target_format=="aac"|| g_target_format=="m4a" || g_target_format=="m4r" || g_target_format=="ogg" || g_target_format=="wav"){
            cbb_a_srate->addItem("Automatic");
            cbb_a_srate->addItem("44100");
            cbb_a_srate->addItem("22050");
            cbb_a_srate->addItem("11025");
        }

        else if(g_target_format=="mmf"){
           cbb_a_srate->addItem("8000");
           cbb_a_srate->addItem("4000");
        }

       else if(g_target_format=="amr"){
           cbb_a_srate->addItem("8000");
           cbb_a_srate->setEnabled(0);
       }

        QMap <QString,QString> srmap;
        srmap["mp3"]=mp3_a_srate;
        srmap["wma"]=wma_a_srate;
        srmap["ape"]=ape_a_srate;
        srmap["flac"]=flac_a_srate;
        srmap["aac"]=aac_a_srate;
        srmap["m4a"]=m4a_a_srate;
        srmap["m4r"]=m4r_a_srate;
        srmap["ogg"]=ogg_a_srate;
        srmap["wav"]=wav_a_srate;
        srmap["mmf"]=mmf_a_srate;
        srmap["mp2"]=mp2_a_srate;

         cbb_a_srate->setCurrentText(srmap[g_target_format]);

         output_setting_table->setItemWidget(audio_a_srate_item,1,cbb_a_srate);


        QTreeWidgetItem *audio_bitrate_item = new QTreeWidgetItem(audio_stream_item);
        audio_bitrate_item->setText(0,"Bitrate ( KB/s");

        cbb_a_bitrate = new QComboBox;

        if(g_target_format=="mp3" || g_target_format=="mp2"){
            cbb_a_bitrate->addItem("Automatic");
            cbb_a_bitrate->addItem("320");
            cbb_a_bitrate->addItem("256");
            cbb_a_bitrate->addItem("224");
            cbb_a_bitrate->addItem("192");
            cbb_a_bitrate->addItem("128");
            cbb_a_bitrate->addItem("96");
            cbb_a_bitrate->addItem("64");
            cbb_a_bitrate->addItem("32");
        }
        if(g_target_format=="mp3")
            cbb_a_bitrate->setCurrentText(mp3_a_bitrate);
        if(g_target_format=="mp2")
            cbb_a_bitrate->setCurrentText(mp2_a_bitrate);

        else if(g_target_format=="wma" || g_target_format=="aac" || g_target_format=="m4a"|| g_target_format=="m4r"|| g_target_format=="ogg"){
            cbb_a_bitrate->addItem("Automatic");
            cbb_a_bitrate->addItem("192");
            cbb_a_bitrate->addItem("128");
            cbb_a_bitrate->addItem("96");
            cbb_a_bitrate->addItem("64");
            cbb_a_bitrate->addItem("32");
        }
        if(g_target_format=="wma")
            cbb_a_bitrate->setCurrentText(wma_a_bitrate);
        if(g_target_format=="aac")
            cbb_a_bitrate->setCurrentText(aac_a_bitrate);
        if(g_target_format=="m4a")
            cbb_a_bitrate->setCurrentText(m4a_a_bitrate);
        if(g_target_format=="m4r")
            cbb_a_bitrate->setCurrentText(m4r_a_bitrate);
        if(g_target_format=="ogg")
            cbb_a_bitrate->setCurrentText(ogg_a_bitrate);

        else if(g_target_format=="ape" || g_target_format=="flac" || g_target_format=="mmf" || g_target_format=="wav"){
            cbb_a_bitrate->addItem("Automatic");
        }
        if(g_target_format=="flac"){
            setComboValue(cbb_a_bitrate,flac_a_bitrate);
        }
        if(g_target_format=="wav")
            cbb_a_bitrate->setEnabled(0);

        if(g_target_format=="amr"){
            cbb_a_bitrate->addItem("12.2");
            cbb_a_bitrate->addItem("6.7");
            setComboValue(cbb_a_bitrate,amr_a_bitrate);
        }

        output_setting_table->setItemWidget(audio_bitrate_item,1,cbb_a_bitrate);

        QTreeWidgetItem *audio_channel_item = new QTreeWidgetItem(audio_stream_item);
        audio_channel_item->setText(0,"Audio channel");

        cbb_a_channel = new QComboBox;
        connect(cbb_a_channel, SIGNAL(currentIndexChanged(QString)),this,SLOT(audioChannelValueConvert()));

        if(g_target_format=="mp3" || g_target_format=="wma" || g_target_format=="aac"|| g_target_format=="m4a"|| g_target_format=="m4r"|| g_target_format=="ogg" || g_target_format=="mp2"){
            cbb_a_channel->addItem("Automatic");
            cbb_a_channel->addItem("2 Stereo");
            cbb_a_channel->addItem("1 Mono");
        }

        else if(g_target_format=="ape"){
            cbb_a_channel->addItem("Automatic");
        }

        else if (g_target_format=="flac"|| g_target_format=="wav"){

            cbb_a_channel->addItem("Automatic");
            cbb_a_channel->addItem("8 Stereo 7.1");
            cbb_a_channel->addItem("6 Stereo 5.1");
            cbb_a_channel->addItem("2 Stereo");
            cbb_a_channel->addItem("1 Mono");
        }

        if(g_target_format=="mmf" || g_target_format=="amr"){
            cbb_a_channel->addItem("Automatic");
            cbb_a_channel->addItem("2 Stereo");
            cbb_a_channel->addItem("1 Mono");
         }

        QMap<QString, QString>acmap;
        acmap["mp3"]=mp3_a_channel;
        acmap["wav"]=mp3_a_channel;
        acmap["flac"]=flac_a_channel;
        acmap["aac"]=aac_a_channel;
        acmap["mmf"]=mmf_a_channel;
        acmap["m4a"]=m4a_a_channel;
        acmap["m4r"]=m4r_a_channel;
        acmap["amr"]=amr_a_channel;
        acmap["ogg"]=ogg_a_channel;
        acmap["wav"]=wav_a_channel;
        acmap["mp2"]=mp2_a_channel;
        setComboValue(cbb_a_channel,acmap[g_target_format]);

        output_setting_table->setItemWidget(audio_channel_item,1,cbb_a_channel);

        QTreeWidgetItem *audio_volume_item = new QTreeWidgetItem(audio_stream_item);
        audio_volume_item->setText(0,"Volume control");

        cbb_volume_ctr = new QComboBox;
        cbb_volume_ctr->addItem("50%");
        cbb_volume_ctr->addItem("100%");
        cbb_volume_ctr->addItem("150%");
        cbb_volume_ctr->addItem("200%");
        cbb_volume_ctr->setCurrentIndex(1);

        QMap<QString, QString> vcmap;
        vcmap["mp3"]=mp3_vol_ctr;
                vcmap["wma"]=wma_vol_ctr;
                vcmap["ape"]=ape_vol_ctr;
                vcmap["flac"]=flac_vol_ctr;
                vcmap["aac"]=aac_vol_ctr;
                vcmap["mmf"]=mmf_vol_ctr;
                vcmap["m4a"]=m4a_vol_ctr;
                vcmap["m4r"]=m4r_vol_ctr;
                vcmap["amr"]=amr_vol_ctr;
                vcmap["ogg"]=ogg_vol_ctr;
                vcmap["wav"]=wav_vol_ctr;
                vcmap["mp2"]=mp2_vol_ctr;
                cbb_volume_ctr->setCurrentText(vcmap[g_target_format]);


        output_setting_table->setItemWidget(audio_volume_item,1,cbb_volume_ctr);

        lo_output_setting->addLayout(grid_atas);
        lo_output_setting->addWidget(output_setting_table);
        d_output_setting->setWindowTitle(g_target_format.toUpper()+" Setting");
        d_output_setting->setLayout(lo_output_setting);
        d_output_setting->setFixedSize(680,560);
        d_output_setting->show();
}


void dialogConversion::dialog_pict_setting(){

    dialog_pict = new QDialog(this);

    QVBoxLayout * lo_pict_dial = new QVBoxLayout(dialog_pict);

    QFrame *frame_top = new QFrame(dialog_pict);
    QHBoxLayout *lo_top = new QHBoxLayout(frame_top);

    cbb_pict_prmtr  =  new QComboBox;
    if(g_target_format=="jpg" || g_target_format=="png" || g_target_format=="bmp" || g_target_format=="tif" || g_target_format=="pcx" || g_target_format=="tga"){

    cbb_pict_prmtr->addItem("Original Size");
    cbb_pict_prmtr->addItem("Max Width 2400 Max Height 1800");
    cbb_pict_prmtr->addItem("Max Width 1024 Max Height 768");
    cbb_pict_prmtr->addItem("Max Width 640 Max Height 480");
    cbb_pict_prmtr->addItem("Max Width 320 Max Height 240");
    cbb_pict_prmtr->addItem("Max Width 176 Max Height 144");
            if(g_target_format=="jpg"){
                cbb_pict_prmtr->setCurrentText(jpg_cur_text);
            }
            else if(g_target_format=="png"){
                cbb_pict_prmtr->setCurrentText(png_cur_text);
            }
            else if(g_target_format=="bmp"){
                cbb_pict_prmtr->setCurrentText(bmp_cur_text);
            }
            else if(g_target_format=="tif"){
                cbb_pict_prmtr->setCurrentText(tif_cur_text);
            }

            else if(g_target_format=="pcx"){
                cbb_pict_prmtr->setCurrentText(pcx_cur_text);
            }

            else if(g_target_format=="tga"){
                cbb_pict_prmtr->setCurrentText(tga_cur_text);
            }

    connect(cbb_pict_prmtr, SIGNAL(activated(int)),this,SLOT(on_cbb_pict_param_changed(int)));


    }

    //gif skip

    if(g_target_format=="ico"){
        cbb_pict_prmtr->addItem("16x16");
        cbb_pict_prmtr->addItem("32x32");
        cbb_pict_prmtr->addItem("48x48");
        cbb_pict_prmtr->addItem("64x64");
        cbb_pict_prmtr->addItem("128x128");
        cbb_pict_prmtr->addItem("256x256");
        cbb_pict_prmtr->setCurrentText(ico_cur_text);
        connect(cbb_pict_prmtr,SIGNAL(activated(int)),this,SLOT(on_cbb_ico_changed(int)));

    }

    QPushButton *btn_ok = new QPushButton("OK");
    connect(btn_ok,SIGNAL(pressed()),this,SLOT(acceptDialogPict()));

    lo_top->addWidget(cbb_pict_prmtr);
    lo_top->addWidget(btn_ok);


    frame_top->setLayout(lo_top);

    QGridLayout *lo_operation = new QGridLayout;

    //QIcon icon_img = QIcon::fromTheme("image");

    cb_size_limit = new QCheckBox;
    cb_size_limit->setText("Limit Size");
    connect(cb_size_limit,SIGNAL(toggled(bool)),this,SLOT(size_limit_img(bool)));

    QLabel *lb_max_w = new QLabel("Max Width");

    QLabel *lb_angle = new QLabel("Angle");

    le_max_w = new QLineEdit;
    le_max_w->setFixedWidth(60);
    le_max_w->setEnabled(false);

    le_max_h = new QLineEdit;
    le_max_h->setFixedWidth(60);
    le_max_h->setEnabled(false);

    if(g_target_format=="jpg" && jpg_limit_size){
       cb_size_limit->setChecked(true);
        le_max_w->setText(jpg_max_width);
        le_max_h->setText(jpg_max_heigth);
    }

    else if(g_target_format=="png" && png_limit_size){
       cb_size_limit->setChecked(true);
        le_max_w->setText(png_max_width);
        le_max_h->setText(png_max_heigth);
    }

    else if(g_target_format=="ico" && ico_limit_size){
        cb_size_limit->setChecked(true);
         le_max_w->setText(ico_max_width);
         le_max_h->setText(ico_max_heigth);

    }
    else if(g_target_format=="bmp" && bmp_limit_size){
       cb_size_limit->setChecked(true);
        le_max_w->setText(bmp_max_width);
        le_max_h->setText(bmp_max_heigth);
    }

    else if(g_target_format=="tif" && tif_limit_size){
       cb_size_limit->setChecked(true);
        le_max_w->setText(tif_max_width);
        le_max_h->setText(tif_max_heigth);
    }

    else if(g_target_format=="pcx" && pcx_limit_size){
       cb_size_limit->setChecked(true);
        le_max_w->setText(pcx_max_width);
        le_max_h->setText(pcx_max_heigth);
    }

    else if(g_target_format=="tga" && tga_limit_size){
       cb_size_limit->setChecked(true);
        le_max_w->setText(tga_max_width);
        le_max_h->setText(tga_max_heigth);
    }

    cb_rotate = new QCheckBox;
    cb_rotate->setText("Rotate");
    connect(cb_rotate,SIGNAL(toggled(bool)),this,SLOT(rotate_img(bool)));

    cbb_angle = new QComboBox;
    cbb_angle->setFixedWidth(60);
    cbb_angle->addItem("0");
    cbb_angle->addItem("-90");
    cbb_angle->addItem("90");
    cbb_angle->addItem("180");
    cbb_angle->setEnabled(false);

    if(g_target_format=="jpg" && jpg_rotate){
            cb_rotate->setChecked(true);
        cbb_angle->setCurrentText(jpg_angle);
        }

    if(g_target_format=="png" && png_rotate){
            cb_rotate->setChecked(true);
        cbb_angle->setCurrentText(png_angle);
        }

    if(g_target_format=="ico" && ico_rotate){
        cb_rotate->setChecked(true);
    cbb_angle->setCurrentText(ico_angle);
    }

    if(g_target_format=="bmp" && bmp_rotate){
        cb_rotate->setChecked(true);
    cbb_angle->setCurrentText(bmp_angle);
    }

    if(g_target_format=="tif" && tif_rotate){
        cb_rotate->setChecked(true);
        cbb_angle->setCurrentText(tif_angle);
    }

    if(g_target_format=="pcx" && pcx_rotate){
        cb_rotate->setChecked(true);
        cbb_angle->setCurrentText(pcx_angle);
    }

    if(g_target_format=="tga" && tga_rotate){
        cb_rotate->setChecked(true);
        cbb_angle->setCurrentText(tga_angle);
    }
    QLabel *lb_max_h = new QLabel("Max heigth");

   // lo_operation->addWidget(icon_img,0,0);
    lo_operation->addWidget(cb_size_limit,1,1);
    lo_operation->addWidget(cb_rotate,2,1);
    lo_operation->addWidget(lb_max_w,1,2,Qt::AlignRight);
    lo_operation->addWidget(lb_angle,2,2 , Qt::AlignRight);
    lo_operation->addWidget(le_max_w,1,3,Qt::AlignLeft);
    lo_operation->addWidget(cbb_angle,2,3,Qt::AlignLeft);
    lo_operation->addWidget(lb_max_h,1,4, Qt::AlignRight);
    lo_operation->addWidget(le_max_h,1,5,Qt::AlignLeft);
    lo_operation->setContentsMargins(10,10,10,10);

    QGroupBox *gb_operation = new QGroupBox;
    gb_operation->setTitle("Operation");
    gb_operation->setLayout(lo_operation);

    QGridLayout *lo_tag_string = new QGridLayout;

    QLabel *lb_font = new QLabel("Font");

    cb_insert_tag = new QCheckBox;
    cb_insert_tag->setText("Insert tag string");
    connect(cb_insert_tag,SIGNAL(toggled(bool)),this,SLOT(insert_tag_img(bool)));

   // QWidget *w_ic_insert = new QWidget;


    cfcb_font_chooser = new QFontComboBox;
    cfcb_font_chooser->setEnabled(false);

    QMap<QString,QString>fmap;

    fmap["jpg"]=jpg_font;
    fmap["png"]=png_font;
    fmap["ico"]=ico_font;
    fmap["bmp"]=bmp_font;
    fmap["tif"]=tif_font;
    fmap["pcx"]=pcx_font;
    fmap["tga"]=tga_font;

    if(!fmap[g_target_format].isEmpty())
     cfcb_font_chooser->setCurrentText(fmap[g_target_format]);


    QLabel *lb_position = new QLabel("Position");

    QLabel *lb_color = new QLabel("Color");

    cbb_position = new QComboBox;
    cbb_position->addItem("Bottom right");
    cbb_position->addItem("Bottom left");
    cbb_position->addItem("Top right");
    cbb_position->addItem("Top left");
    cbb_position->addItem("Center");
    cbb_position->setEnabled(false);

    QMap<QString,QString>posmap;
    posmap["jpg"]=jpg_text_pos;
    posmap["png"]=png_text_pos;
    posmap["ico"]=ico_text_pos;
    posmap["bmp"]=bmp_text_pos;
    posmap["tif"]=tif_text_pos;
    posmap["pcx"]=pcx_text_pos;
    posmap["tga"]=tga_text_pos;

    cbb_position->setCurrentText(posmap[g_target_format]);

   cbb_color = new QComboBox;
   const QStringList colorNames = QColor::colorNames();
   int index = 0;
   foreach (const QString &colorName, colorNames) {
       const QColor color(colorName);
       cbb_color->addItem(colorName, color);
       const QModelIndex idx = cbb_color->model()->index(index++, 0);
       cbb_color->model()->setData(idx, color, Qt::BackgroundColorRole);
   }
   cbb_color->setEnabled(false);

   QMap<QString,QString>cmap;
   cmap["jpg"]=jpg_text_color;
   cmap["png"]=png_text_color;
   cmap["ico"]=ico_text_color;
   cmap["bmp"]=bmp_text_color;
   cmap["tif"]=tif_text_color;
   cmap["pcx"]=pcx_text_color;
   cmap["tga"]=tga_text_color;

   cbb_color->setCurrentText(cmap[g_target_format]);



   QLabel *lb_margin = new QLabel("Margin");

   QLabel *lb_size = new QLabel("Size");

   le_margin = new QLineEdit;
    le_margin->setFixedWidth(60);
    le_margin->setEnabled(false);

   cbb_size = new QComboBox;
   cbb_size->setFixedWidth(60);
   cbb_size->addItem("Auto");
   cbb_size->addItem("8");
   cbb_size->addItem("9");
   cbb_size->addItem("10");
   cbb_size->addItem("12");
   cbb_size->addItem("14");
   cbb_size->addItem("16");
   cbb_size->addItem("18");
   cbb_size->addItem("20");
   cbb_size->addItem("24");
   cbb_size->addItem("36");
   cbb_size->addItem("48");
   cbb_size->addItem("72");
   cbb_size->setEnabled(false);

   QMap<QString,QString> fsizemap;
   fsizemap["jpg"]=jpg_font_size;
   fsizemap["png"]=png_font_size;
   fsizemap["ico"]=ico_font_size;
   fsizemap["bmp"]=bmp_font_size;
   fsizemap["tif"]=tif_font_size;
   fsizemap["pcx"]=pcx_font_size;
   fsizemap["tga"]=tga_font_size;



   cbb_size->setCurrentText(fsizemap[g_target_format]);



   cb_italic = new QCheckBox;
   cb_italic->setText("Italic");
   cb_italic->setEnabled(false);

   QMap<QString,bool>italmap;
   italmap["jpg"]=jpg_italic;
   italmap["png"]=png_italic;
   italmap["ico"]=ico_italic;
   italmap["bmp"]=bmp_italic;
   italmap["tif"]=tif_italic;
   italmap["pcx"]=pcx_italic;
   italmap["tga"]=tga_italic;

   cb_italic->setChecked(italmap[g_target_format]);

   cb_underline = new QCheckBox;
   cb_underline->setText("Underline");
   cb_underline->setEnabled(false);

   QMap<QString,bool>undmap;
   undmap["jpg"]=jpg_underline;
   undmap["png"]=png_underline;
   undmap["ico"]=ico_underline;
   undmap["bmp"]=bmp_underline;
   undmap["tif"]=tif_underline;
   undmap["pcx"]=pcx_underline;
   undmap["tga"]=tga_underline;

   cb_underline->setChecked(undmap[g_target_format]);



    QLabel *lb_string = new QLabel;
    lb_string->setText("Tag string");

    le_string = new QLineEdit;
    le_string->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    le_string->setEnabled(false);


    QMap<QString,QString> tagmap;
    tagmap["jpg"]=jpg_tag_string;
    tagmap["png"]=png_tag_string;
    tagmap["ico"]=ico_tag_string;
    tagmap["bmp"]=bmp_tag_string;
    tagmap["tif"]=tif_tag_string;
    tagmap["pcx"]=pcx_tag_string;
    tagmap["tga"]=tga_tag_string;


        le_string->setText(tagmap[g_target_format]);



    QMap<QString,bool>ins;
    ins["jpg"]=jpg_insert_text;
    ins["png"]=png_insert_text;
    ins["ico"]=ico_insert_text;
    ins["bmp"]=bmp_insert_text;
    ins["tif"]=tif_insert_text;
    ins["pcx"]=pcx_insert_text;
    ins["tga"]=tga_insert_text;

    cb_insert_tag->setChecked(ins[g_target_format]);


    lo_tag_string->addWidget(lb_font,1,0);
    lo_tag_string->addWidget(cb_insert_tag,0,1);
    lo_tag_string->addWidget(cfcb_font_chooser,1,1);
    lo_tag_string->addWidget(lb_position,0,2,Qt::AlignRight);
    lo_tag_string->addWidget(lb_color,1,2,Qt::AlignRight);
    lo_tag_string->addWidget(cbb_position,0,3);
    lo_tag_string->addWidget(cbb_color,1,3);
    lo_tag_string->addWidget(lb_margin, 0,4,Qt::AlignRight);
    lo_tag_string->addWidget(lb_size,1,4,Qt::AlignRight);
    lo_tag_string->addWidget(le_margin,0,5);
    lo_tag_string->addWidget(cbb_size,1,5);
    lo_tag_string->addWidget(cb_italic, 2, 1);
    lo_tag_string->addWidget(cb_underline, 2,2);
    lo_tag_string->addWidget(lb_string,3,0);
    lo_tag_string->addWidget(le_string,3,1,1,4);

    QGroupBox *gb_tag_string = new QGroupBox;
    gb_tag_string->setTitle("Tag string");
    gb_tag_string->setLayout(lo_tag_string);

    QGridLayout *lo_watermark = new QGridLayout;

    cb_watermark = new QCheckBox;
    cb_watermark->setText("Watermark");

    connect(cb_watermark,SIGNAL(toggled(bool)),this,SLOT(add_watermark(bool)));

    QLabel *lb_wm_position = new QLabel("Position");

    cbb_wm_position = new QComboBox;
    cbb_wm_position->addItem("Bottom right");
    cbb_wm_position->addItem("Bottom left");
    cbb_wm_position->addItem("Top right");
    cbb_wm_position->addItem("Top left");
    cbb_wm_position->addItem("Center");
    cbb_wm_position->setEnabled(false);

    QMap<QString,QString>wpos;
    wpos["jpg"]=jpg_wm_pos;
    wpos["png"]=png_wm_pos;
    wpos["ico"]=ico_wm_pos;
    wpos["bmp"]=bmp_wm_pos;
    wpos["tif"]=tif_wm_pos;
    wpos["pcx"]=pcx_wm_pos;
    wpos["tga"]=tga_wm_pos;

    cbb_wm_position->setCurrentText(wpos[g_target_format]);


    QLabel *lb_wm_margin = new QLabel("Margin");

    le_wm_margin = new QLineEdit;
    le_wm_margin->setFixedWidth(60);
    le_wm_margin->setEnabled(false);

    QLabel *lb_wm_size = new QLabel("size");
    QLabel *lb_wm_percent = new QLabel("%");
    lb_wm_percent->setFixedWidth(20);

    cbb_wm_size = new QComboBox;
    cbb_wm_size->addItem("Original size");
    cbb_wm_size->addItem("5");
    cbb_wm_size->addItem("10");
    cbb_wm_size->addItem("15");
    cbb_wm_size->addItem("20");
    cbb_wm_size->addItem("25");
    cbb_wm_size->addItem("30");
    cbb_wm_size->setEnabled(false);


    QMap<QString,QString>wmsizemap;
    wmsizemap["jpg"]=jpg_wm_size;
    wmsizemap["png"]=png_wm_size;
    wmsizemap["ico"]=ico_wm_size;
    wmsizemap["bmp"]=bmp_wm_size;
    wmsizemap["tif"]=tif_wm_size;
    wmsizemap["pcx"]=pcx_wm_size;
    wmsizemap["tga"]=tga_wm_size;

    cbb_wm_size->setCurrentText(wmsizemap[g_target_format]);

    le_wm_file = new QLineEdit;
    QMap<QString,QString>wmfilemap;
    wmfilemap["jpg"]=jpg_wm_file;
    wmfilemap["png"]=png_wm_file;
    wmfilemap["ico"]=ico_wm_file;
    wmfilemap["bmp"]=bmp_wm_file;
    wmfilemap["tif"]=tif_wm_file;
    wmfilemap["pcx"]=pcx_wm_file;
    wmfilemap["tga"]=tga_wm_file;

    le_wm_file->setText(wmfilemap[g_target_format]);


    btn_wm_browse = new QPushButton("Browse");
    btn_wm_browse->setEnabled(false);
    connect(btn_wm_browse,SIGNAL(pressed()),this,SLOT(getWatermarkPict()));

    QMap<QString,bool>inswm;
    inswm["jpg"]=jpg_insert_wm;
    inswm["png"]=png_insert_wm;
    inswm["ico"]=ico_insert_wm;
    inswm["tif"]=tif_insert_wm;
    inswm["bmp"]=bmp_insert_wm;
    inswm["pcx"]=pcx_insert_wm;
    inswm["tga"]=tga_insert_wm;

    cb_watermark->setChecked(inswm[g_target_format]);


    lo_watermark->setRowStretch(0,1);
    lo_watermark->addWidget(cb_watermark,0,1);
    lo_watermark->addWidget(lb_wm_position,0,2,Qt::AlignRight);
    lo_watermark->addWidget(cbb_wm_position,0,3);
    lo_watermark->addWidget(lb_wm_margin,0,4,Qt::AlignRight);
    lo_watermark->addWidget(le_wm_margin,0,5,Qt::AlignRight);
    lo_watermark->addWidget(lb_wm_size,1,4,Qt::AlignRight);
    lo_watermark->addWidget(cbb_wm_size,1,5,Qt::AlignRight);
    lo_watermark->addWidget(lb_wm_percent,1,6);
    lo_watermark->addWidget(le_wm_file, 2,2,1,3);
    lo_watermark->addWidget(btn_wm_browse,2,5);


    QGroupBox *gb_watermark = new QGroupBox;
    gb_watermark->setTitle("Watermark");
    gb_watermark->setLayout(lo_watermark);

    lo_pict_dial->addWidget(frame_top);

    lo_pict_dial->addWidget(gb_operation);
    lo_pict_dial->addWidget(gb_tag_string);
    lo_pict_dial->addWidget(gb_watermark);

    dialog_pict->setLayout(lo_pict_dial);
    dialog_pict->setFixedSize(720,560);
    dialog_pict->setWindowTitle("-> "+g_target_format.toUpper());
    dialog_pict->exec();

}

void dialogConversion::size_limit_img(bool l){

        le_max_h->setEnabled(l);
        le_max_w->setEnabled(l);
}

void dialogConversion::rotate_img(bool r){

        cbb_angle->setEnabled(r);
}

void dialogConversion::insert_tag_img(bool t){

        cbb_position->setEnabled(t);
        cbb_color->setEnabled(t);
        le_margin->setEnabled(t);
        cbb_size->setEnabled(t);
        cfcb_font_chooser->setEnabled(t);
        cb_italic->setEnabled(t);
        cb_underline->setEnabled(t);
        le_string->setEnabled(t);
}

void dialogConversion::on_cbb_parameter_mp4_changed(int i){

    switch(i){

    case 0://mpeg4 high
        cbb_v_encoder->setCurrentIndex(0);
        cbb_v_size->setCurrentIndex(0);
        cbb_v_bitrate->setCurrentIndex(0);
        cbb_v_fps->setCurrentIndex(0);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_a_channel->setCurrentIndex(1);
        break;

    case 1://mpeg4 medium
        cbb_v_encoder->setCurrentIndex(0);
        insertSpecialItem(cbb_v_size, "Autox480");
        cbb_v_bitrate->setCurrentIndex(0);
        cbb_v_fps->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_channel->setCurrentIndex(1);
        break;

    case 2://mpeg4 low
        cbb_v_encoder->setCurrentIndex(0);
        cbb_v_bitrate->setCurrentIndex(2);
        cbb_v_fps->setCurrentIndex(3);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(3);
        cbb_a_srate->setCurrentIndex(1);
        cbb_a_channel->setCurrentIndex(1);
        break;

    case 3://mpeg4 720p
        cbb_v_encoder->setCurrentIndex(0);
        insertSpecialItem(cbb_v_size,"Autox720");
        cbb_v_bitrate->addItem("2048");
        cbb_v_bitrate->setCurrentText("2048");
        cbb_v_fps->setCurrentIndex(9);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_a_channel->setCurrentIndex(1);
        break;

    case 4: //mpeg4 480p
        cbb_v_encoder->setCurrentIndex(0);
        insertSpecialItem(cbb_v_size,"Autox480");
        cbb_v_bitrate->setCurrentIndex(5);
        cbb_v_fps->setCurrentIndex(6);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_a_channel->setCurrentIndex(1);
        break;

    case 5://mpeg360
        cbb_v_encoder->setCurrentIndex(0);
        cbb_v_size->setItemText(20,"Autox360");
        cbb_v_bitrate->setCurrentIndex(3);
        cbb_v_fps->setCurrentIndex(6);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_a_channel->setCurrentIndex(1);
        break;

    case 6://mpeg4240
        cbb_v_encoder->setCurrentIndex(0);
        insertSpecialItem(cbb_v_size,"Autox240");
        cbb_v_bitrate->setCurrentIndex(2);
        cbb_v_fps->setCurrentIndex(6);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(1);
        cbb_a_bitrate->setCurrentIndex(3);
        cbb_a_channel->setCurrentIndex(1);
        break;

    case 7://x264 high
        cbb_v_encoder->setCurrentIndex(1);
        cbb_v_size->setEditable(false);
        cbb_v_size->setCurrentIndex(0);
        cbb_v_bitrate->setCurrentIndex(0);
        cbb_v_fps->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_v_ratio->setCurrentIndex(1);
        cbb_a_channel->setCurrentIndex(1);
        break;

    case 8://x264 medium
        cbb_v_encoder->setCurrentIndex(1);
        insertSpecialItem(cbb_v_size,"Autox480");
        cbb_v_bitrate->setCurrentIndex(0);
        cbb_v_fps->setCurrentIndex(0);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_channel->setCurrentIndex(1);
        break;

    case 9://x264 low
        cbb_v_encoder->setCurrentIndex(1);
        insertSpecialItem(cbb_v_size,"Autox240");
        cbb_v_bitrate->setCurrentIndex(2);
        cbb_v_fps->setCurrentIndex(3);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(3);
        cbb_a_srate->setCurrentIndex(1);
        cbb_a_channel->setCurrentIndex(1);
        break;

    case 10://x264 720p
        cbb_v_encoder->setCurrentIndex(1);
        insertSpecialItem(cbb_v_size,"Autox720");
        cbb_v_bitrate->addItem("1536");
        cbb_v_bitrate->setCurrentText("1536");
        cbb_v_fps->setCurrentIndex(9);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_a_channel->setCurrentIndex(1);
        break;

    case 11://x264 480p
        cbb_v_encoder->setCurrentIndex(1);
        insertSpecialItem(cbb_v_size,"Autox480");
        cbb_v_bitrate->setCurrentIndex(4);
        cbb_v_fps->setCurrentIndex(6);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_a_channel->setCurrentIndex(1);
        break;

    case 12:
        cbb_v_encoder->setCurrentIndex(1);
        insertSpecialItem(cbb_v_size,"Autox360");
        cbb_v_bitrate->setCurrentIndex(2);
        cbb_v_fps->setCurrentIndex(6);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_a_channel->setCurrentIndex(1);
        break;

    case 13:
        cbb_v_encoder->setCurrentIndex(1);
        insertSpecialItem(cbb_v_size,"Autox240");
        cbb_v_bitrate->addItem("288");
        cbb_v_bitrate->setCurrentText("288");
        cbb_v_fps->setCurrentIndex(6);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(1);
        cbb_a_bitrate->setCurrentIndex(3);
        cbb_a_channel->setCurrentIndex(1);
        break;

    }

}

void dialogConversion::on_cbb_parameter_avi_changed(int i)
{
    switch(i){
    case 0://xvid
        cbb_v_encoder->setCurrentIndex(1);
        cbb_v_size->setCurrentIndex(0);
        cbb_v_bitrate->setCurrentIndex(0);
        cbb_v_fps->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_v_ratio->setCurrentIndex(1);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_a_channel->setCurrentIndex(1);
        break;

    case 1:
        cbb_v_encoder->setCurrentIndex(1);
        insertSpecialItem(cbb_v_size,"Autox480");
        cbb_v_bitrate->setCurrentIndex(0);
        cbb_v_fps->setCurrentIndex(0);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_channel->setCurrentIndex(1);
        break;

    case 2://xvid low
        cbb_v_encoder->setCurrentIndex(1);
        cbb_v_bitrate->setCurrentIndex(2);
        cbb_v_fps->setCurrentIndex(3);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(3);
        cbb_a_srate->setCurrentIndex(1);
        cbb_a_channel->setCurrentIndex(1);
        break;

    case 3://xvid 720p
        cbb_v_encoder->setCurrentIndex(1);
        insertSpecialItem(cbb_v_size,"Autox720");
        insertSpecialItem(cbb_v_bitrate,"2048");
        cbb_v_fps->setCurrentIndex(9);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_a_channel->setCurrentIndex(1);
        break;

    case 4: //xvid 480p
        cbb_v_encoder->setCurrentIndex(1);
        cbb_v_size->setCurrentIndex(24);
        cbb_v_bitrate->setCurrentIndex(5);
        cbb_v_fps->setCurrentIndex(6);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_a_channel->setCurrentIndex(1);
        break;

    case 5://xvid 360p
        cbb_v_encoder->setCurrentIndex(1);
        insertSpecialItem(cbb_v_size,"Autox360");
        cbb_v_bitrate->setCurrentIndex(2);
        cbb_v_fps->setCurrentIndex(6);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_a_channel->setCurrentIndex(1);
        break;

    case 6:
        cbb_v_encoder->setCurrentIndex(1);
        insertSpecialItem(cbb_v_size,"Autox240");
        insertSpecialItem(cbb_v_bitrate,"288");
        cbb_v_fps->setCurrentIndex(6);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(1);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(3);
        cbb_a_channel->setCurrentIndex(1);
        break;
    case 7://divx
        cbb_v_encoder->setCurrentIndex(0);
        cbb_v_size->setCurrentIndex(0);
        cbb_v_bitrate->setCurrentIndex(0);
        cbb_v_fps->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_v_ratio->setCurrentIndex(1);
        cbb_a_channel->setCurrentIndex(1);
        break;

    case 8:
        cbb_v_encoder->setCurrentIndex(0);
        insertSpecialItem(cbb_v_size,"Autox480");
        cbb_v_bitrate->setCurrentIndex(0);
        cbb_v_fps->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_channel->setCurrentIndex(1);
        break;

    case 9://xvid low
        cbb_v_encoder->setCurrentIndex(0);
        cbb_v_bitrate->setCurrentIndex(2);
        cbb_v_fps->setCurrentIndex(3);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(3);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(1);
        cbb_a_channel->setCurrentIndex(1);
        break;

    case 10://divx 720p
        cbb_v_encoder->setCurrentIndex(0);
        insertSpecialItem(cbb_v_size,"Autox720");
        insertSpecialItem(cbb_v_bitrate,"2048");
        cbb_v_fps->setCurrentIndex(9);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_a_channel->setCurrentIndex(1);
        break;

    case 11: //divx 480p
        cbb_v_encoder->setCurrentIndex(0);
        cbb_v_size->setCurrentIndex(24);
        cbb_v_bitrate->setCurrentIndex(5);
        cbb_v_fps->setCurrentIndex(6);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_a_channel->setCurrentIndex(1);
        break;

    case 12://divx 360p
        cbb_v_encoder->setCurrentIndex(0);
        insertSpecialItem(cbb_v_size,"Autox360");
        cbb_v_bitrate->setCurrentIndex(2);
        cbb_v_fps->setCurrentIndex(6);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_a_channel->setCurrentIndex(1);
        break;

    case 13://divx 240
        cbb_v_encoder->setCurrentIndex(0);
        insertSpecialItem(cbb_v_size,"Autox240");
        insertSpecialItem(cbb_v_bitrate,"288");
        cbb_v_fps->setCurrentIndex(6);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(1);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(3);
        cbb_a_channel->setCurrentIndex(1);
        break;

    case 14://avc
        cbb_v_encoder->setCurrentIndex(2);
        cbb_v_size->setCurrentIndex(0);
        cbb_v_bitrate->setCurrentIndex(0);
        cbb_v_fps->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_v_ratio->setCurrentIndex(1);
        cbb_a_channel->setCurrentIndex(1);
        break;

    case 15://avc mdium
        cbb_v_encoder->setCurrentIndex(2);
        insertSpecialItem(cbb_v_size,"Autox480");
        cbb_v_bitrate->setCurrentIndex(0);
        cbb_v_fps->setCurrentIndex(0);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_channel->setCurrentIndex(1);
        break;

    case 16://avc low
        cbb_v_encoder->setCurrentIndex(2);
        cbb_v_bitrate->setCurrentIndex(2);
        cbb_v_fps->setCurrentIndex(3);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(3);
        cbb_a_srate->setCurrentIndex(1);
        cbb_a_channel->setCurrentIndex(1);
        break;

    case 17://avc 720p
        cbb_v_encoder->setCurrentIndex(2);
        insertSpecialItem(cbb_v_size,"Autox720");
        insertSpecialItem(cbb_v_bitrate,"2048");
        cbb_v_fps->setCurrentIndex(9);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_a_channel->setCurrentIndex(1);
        break;

    case 18: //avc 480p
        cbb_v_encoder->setCurrentIndex(2);
        cbb_v_size->setCurrentIndex(24);
        cbb_v_bitrate->setCurrentIndex(5);
        cbb_v_fps->setCurrentIndex(6);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_a_channel->setCurrentIndex(1);
        break;

    case 19://avc 360p
        cbb_v_encoder->setCurrentIndex(2);
        insertSpecialItem(cbb_v_size,"Autox360");
        cbb_v_bitrate->setCurrentIndex(2);
        cbb_v_fps->setCurrentIndex(6);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_a_channel->setCurrentIndex(1);
        break;

    case 20://avc 240p
        cbb_v_encoder->setCurrentIndex(2);
        insertSpecialItem(cbb_v_size,"Autox240");
        insertSpecialItem(cbb_v_bitrate,"288");
        cbb_v_fps->setCurrentIndex(6);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(1);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(3);
        cbb_a_channel->setCurrentIndex(1);
        break;
    }

}

void dialogConversion::on_cbb_parameter_3gp_changed(int i){
    switch(i){
    case 0:
        cbb_v_encoder->setCurrentIndex(1);
        cbb_v_size->setCurrentIndex(1);
        cbb_v_bitrate->setCurrentIndex(3);
        cbb_v_fps->setCurrentIndex(2);
        cbb_v_ratio->setCurrentIndex(0);
        break;
    case 1:
        cbb_v_encoder->setCurrentIndex(1);
        cbb_v_size->setCurrentIndex(2);
        cbb_v_bitrate->setCurrentIndex(3);
        cbb_v_fps->setCurrentIndex(3);
        cbb_v_ratio->setCurrentIndex(0);
        break;
    case 2:
        cbb_v_encoder->setCurrentIndex(0);
        cbb_v_size->setCurrentIndex(1);
        cbb_v_bitrate->setCurrentIndex(3);
        cbb_v_fps->setCurrentIndex(2);
        cbb_v_ratio->setCurrentIndex(0);
        break;
    case 3:
        cbb_v_encoder->setCurrentIndex(0);
        cbb_v_size->setCurrentIndex(2);
        cbb_v_bitrate->setCurrentIndex(3);
        cbb_v_fps->setCurrentIndex(3);
        cbb_v_ratio->setCurrentIndex(0);
        break;

    }

}

void dialogConversion::on_cbb_parameter_webm_changed(int ){

         //webm_quality = cbb_parameter->currentText();
        //webm_quality = cbb_parameter->currentIndex();
}

void dialogConversion::on_cbb_parameter_mkv_changed(int i){
    switch(i){
    case 0://x264 high
        cbb_v_encoder->setCurrentIndex(2);
        cbb_v_size->setEditable(false);
        cbb_v_size->setCurrentIndex(0);
        cbb_v_bitrate->setCurrentIndex(0);
        cbb_v_fps->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_v_ratio->setCurrentIndex(1);
        break;
    case 1://x264 medium
        cbb_v_encoder->setCurrentIndex(2);
        insertSpecialItem(cbb_v_size,"Autox480");
        cbb_v_bitrate->setCurrentIndex(0);
        cbb_v_fps->setCurrentIndex(0);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_a_srate->setCurrentIndex(2);
        break;

    case 2://x264 low
        cbb_v_encoder->setCurrentIndex(2);
        insertSpecialItem(cbb_v_size,"Autox240");
        cbb_v_bitrate->setCurrentIndex(2);
        cbb_v_fps->setCurrentIndex(3);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(3);
        cbb_a_srate->setCurrentIndex(1);
        break;

    case 3://x264 720p
        cbb_v_encoder->setCurrentIndex(2);
        insertSpecialItem(cbb_v_size,"Autox720");
        insertSpecialItem(cbb_v_bitrate,"1536");
        cbb_v_fps->setCurrentIndex(9);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(5);
        break;

    case 4://x264 480p
        cbb_v_encoder->setCurrentIndex(2);
        insertSpecialItem(cbb_v_size,"Autox480");
        cbb_v_bitrate->setCurrentIndex(4);
        cbb_v_fps->setCurrentIndex(6);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(5);
        break;

    case 5:
        cbb_v_encoder->setCurrentIndex(2);
        insertSpecialItem(cbb_v_size,"Autox360");
        cbb_v_bitrate->setCurrentIndex(2);
        cbb_v_fps->setCurrentIndex(6);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_bitrate->setCurrentIndex(5);
        break;

    case 6:
        cbb_v_encoder->setCurrentIndex(2);
        insertSpecialItem(cbb_v_size,"Autox240");
        insertSpecialItem(cbb_v_bitrate,"288");
        cbb_v_fps->setCurrentIndex(6);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(1);
        cbb_a_bitrate->setCurrentIndex(3);
        break;
    }

}

void dialogConversion::on_cbb_parameter_wmv_changed(int i)
{
    switch(i) {
    case 0:
        cbb_v_encoder->setCurrentIndex(0);
        cbb_v_size->setCurrentIndex(0);
        cbb_v_bitrate->setCurrentIndex(0);
        cbb_v_fps->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_v_ratio->setCurrentIndex(1);
        break;
    case 1:
        cbb_v_encoder->setCurrentIndex(0);
        cbb_v_size->setCurrentIndex(21);
        cbb_v_bitrate->setCurrentIndex(0);
        cbb_v_fps->setCurrentIndex(6);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_channel->setCurrentIndex(1);
        break;
    case 2:
        cbb_v_encoder->setCurrentIndex(0);
        insertSpecialItem(cbb_v_size,"Autox240");
        cbb_v_bitrate->setCurrentIndex(2);
        cbb_v_fps->setCurrentIndex(3);
        cbb_a_srate->setCurrentIndex(1);
        cbb_a_bitrate->setCurrentIndex(3);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_channel->setCurrentIndex(1);
        break;
    case 3:
        cbb_v_encoder->setCurrentIndex(0);
        insertSpecialItem(cbb_v_size,"Autox480");
        insertSpecialItem(cbb_v_bitrate,"1000");
        cbb_v_fps->setCurrentIndex(7);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_channel->setCurrentIndex(1);
        break;
    case 4:
        cbb_v_encoder->setCurrentIndex(0);
        insertSpecialItem(cbb_v_size,"Autox360");
        cbb_v_bitrate->setCurrentIndex(4);
        cbb_v_fps->setCurrentIndex(7);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_channel->setCurrentIndex(1);
        break;
    case 5:
        cbb_v_encoder->setCurrentIndex(0);
        insertSpecialItem(cbb_v_size,"Autox240");
        cbb_v_bitrate->setCurrentIndex(2);
        cbb_v_fps->setCurrentIndex(3);
        cbb_a_srate->setCurrentIndex(1);
        cbb_a_bitrate->setCurrentIndex(3);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_channel->setCurrentIndex(1);
        break;
    }

}

void dialogConversion::on_cbb_parameter_mpg_changed(int i)
{
    switch(i){
    case 0:
        insertSpecialItem(cbb_v_size, "325x288");
        insertSpecialItem(cbb_v_bitrate, "1150");
        cbb_v_fps->setCurrentIndex(7);
        cbb_v_ratio->setCurrentIndex(5);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_bitrate->setCurrentIndex(7);
        break;
    case 1:
        insertSpecialItem(cbb_v_size, "352x240");
        insertSpecialItem(cbb_v_bitrate, "1150");
        cbb_v_fps->setCurrentIndex(8);
        cbb_v_ratio->setCurrentIndex(5);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_bitrate->setCurrentIndex(7);
        break;
    case 2:
        insertSpecialItem(cbb_v_size, "480x576");
        insertSpecialItem(cbb_v_bitrate, "2040");
        cbb_v_fps->setCurrentIndex(7);
        cbb_v_ratio->setCurrentIndex(3);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_bitrate->setCurrentIndex(7);
        break;
    case 3:
        insertSpecialItem(cbb_v_size, "480x480");
        insertSpecialItem(cbb_v_bitrate, "2040");
        cbb_v_fps->setCurrentIndex(8);
        cbb_v_ratio->setCurrentIndex(3);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_bitrate->setCurrentIndex(7);
        break;
    case 4:
        insertSpecialItem(cbb_v_size, "352x288");
        insertSpecialItem(cbb_v_bitrate, "1856");
        cbb_v_fps->setCurrentIndex(7);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_encoder->setCurrentIndex(1);
        cbb_a_srate->setCurrentIndex(4);
        insertSpecialItem(cbb_a_bitrate,"448");
        break;
    case 5:
        insertSpecialItem(cbb_v_size, "720x576");
        insertSpecialItem(cbb_v_bitrate, "6000");
        cbb_v_fps->setCurrentIndex(7);
        cbb_v_ratio->setCurrentIndex(0);
       cbb_a_encoder->setCurrentIndex(1);
        cbb_a_srate->setCurrentIndex(4);
        insertSpecialItem(cbb_a_bitrate,"448");
    case 6:
        insertSpecialItem(cbb_v_size, "352x240");
        insertSpecialItem(cbb_v_bitrate, "1856");
        cbb_v_fps->setCurrentIndex(8);
        cbb_v_ratio->setCurrentIndex(0);
       cbb_a_encoder->setCurrentIndex(1);
        cbb_a_srate->setCurrentIndex(4);
        insertSpecialItem(cbb_a_bitrate,"448");
        break;
    case 7:
        insertSpecialItem(cbb_v_size, "720x480");
        insertSpecialItem(cbb_v_bitrate, "6000");
        cbb_v_fps->setCurrentIndex(8);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_encoder->setCurrentIndex(1);
        cbb_a_srate->setCurrentIndex(4);
        insertSpecialItem(cbb_a_bitrate,"448");
        break;

    }
}
void dialogConversion::on_cbb_parameter_vob_changed(int i){
    switch(i){
    case 0:
        insertSpecialItem(cbb_v_size, "352x288");
        insertSpecialItem(cbb_v_bitrate, "1856");
        cbb_v_fps->setCurrentIndex(7);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(4);
        insertSpecialItem( cbb_a_bitrate, "448");
        insertSpecialItem(cbb_a_channel,"2");
        break;
    case 1:
        insertSpecialItem(cbb_v_size, "720x576");
        insertSpecialItem(cbb_v_bitrate, "6000");
        cbb_v_fps->setCurrentIndex(7);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(4);
        insertSpecialItem( cbb_a_bitrate, "448");
        insertSpecialItem(cbb_a_channel,"2");
        break;
    case 2:
        insertSpecialItem(cbb_v_size, "352x240");
        insertSpecialItem(cbb_v_bitrate, "1856");
        cbb_v_fps->setCurrentIndex(8);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(4);
        insertSpecialItem( cbb_a_bitrate, "448");
        insertSpecialItem(cbb_a_channel,"2");
        break;
    case 3:
        insertSpecialItem(cbb_v_size, "720x480");
        insertSpecialItem(cbb_v_bitrate, "6000");
        cbb_v_fps->setCurrentIndex(8);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(4);
        insertSpecialItem( cbb_a_bitrate, "448");
        insertSpecialItem(cbb_a_channel,"2");
        break;

        }
}

void dialogConversion::on_cbb_parameter_mov_changed(int i)
{
    switch(i){
    case 0:
        cbb_v_encoder->setCurrentIndex(0);
        cbb_v_size->setCurrentIndex(0);
        cbb_v_bitrate->setCurrentIndex(0);
        cbb_v_fps->setCurrentIndex(0);
        cbb_v_ratio->setCurrentIndex(1);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_bitrate->setCurrentIndex(5);

        break;
    case 1:
        cbb_v_encoder->setCurrentIndex(0);
        insertSpecialItem(cbb_v_size,"Autox480");
        cbb_v_bitrate->setCurrentIndex(0);
        cbb_v_fps->setCurrentIndex(6);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_bitrate->setCurrentIndex(5);
        insertSpecialItem(cbb_a_channel,"2");
        break;
    case 2:
        cbb_v_encoder->setCurrentIndex(0);
        insertSpecialItem(cbb_v_size,"Autox240");
        insertSpecialItem(cbb_v_bitrate,"288");
        cbb_v_fps->setCurrentIndex(3);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(1);
        cbb_a_bitrate->setCurrentIndex(3);
        insertSpecialItem(cbb_a_channel,"2");
        break;
    case 3:
        cbb_v_encoder->setCurrentIndex(0);
        insertSpecialItem(cbb_v_size,"320x240");
        insertSpecialItem(cbb_v_bitrate,"288");
        cbb_v_fps->setCurrentIndex(3);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(1);
        cbb_a_bitrate->setCurrentIndex(3);
        insertSpecialItem(cbb_a_channel,"2");
        break;
    case 4:
        cbb_v_encoder->setCurrentIndex(0);
        insertSpecialItem(cbb_v_size,"640x360");
        cbb_v_bitrate->setCurrentIndex(3);
        cbb_v_fps->setCurrentIndex(6);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_bitrate->setCurrentIndex(5);
        insertSpecialItem(cbb_a_channel,"2");
        break;
    case 5:
        cbb_v_encoder->setCurrentIndex(0);
        insertSpecialItem(cbb_v_size,"640x480");
        cbb_v_bitrate->setCurrentIndex(4);
        cbb_v_fps->setCurrentIndex(6);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_bitrate->setCurrentIndex(5);
        insertSpecialItem(cbb_a_channel,"2");
        break;
     }
}

void dialogConversion::on_cbb_parameter_flv_changed(int i)
{
    switch(i){
    case 0:
        cbb_v_encoder->setCurrentIndex(0);
        insertSpecialItem(cbb_v_size,"320x240");
        cbb_v_bitrate->setCurrentIndex(2);
        cbb_v_fps->setCurrentIndex(3);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(1);
        cbb_a_bitrate->setCurrentIndex(3);
        insertSpecialItem(cbb_a_channel,"2");
        break;
    case 1:
        cbb_v_encoder->setCurrentIndex(0);
        insertSpecialItem(cbb_v_size,"640x480");
        cbb_v_bitrate->setCurrentIndex(3);
        cbb_v_fps->setCurrentIndex(3);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_bitrate->setCurrentIndex(5);
        insertSpecialItem(cbb_a_channel,"2");
        break;
    case 2:
        cbb_v_encoder->setCurrentIndex(0);
        insertSpecialItem(cbb_v_size,"176x144");
        insertSpecialItem(cbb_v_bitrate,"180");
        cbb_v_fps->setCurrentIndex(3);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(1);
        cbb_a_bitrate->setCurrentIndex(3);
        insertSpecialItem(cbb_a_channel,"2");
        break;
        }
}

void dialogConversion::on_cbb_parameter_swf_changed(int i){

    switch(i){
    case 0:
        cbb_v_encoder->setCurrentIndex(3);
        insertSpecialItem(cbb_v_size,"320x240");
        cbb_v_bitrate->setCurrentIndex(2);
        cbb_v_fps->setCurrentIndex(3);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(1);
        cbb_a_bitrate->setCurrentIndex(3);
        insertSpecialItem(cbb_a_channel,"2");
        break;
    case 1:
        cbb_v_encoder->setCurrentIndex(3);
        insertSpecialItem(cbb_v_size,"640x480");
        cbb_v_bitrate->setCurrentIndex(3);
        cbb_v_fps->setCurrentIndex(3);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_bitrate->setCurrentIndex(5);
        insertSpecialItem(cbb_a_channel,"2");
        break;
    case 2:
        cbb_v_encoder->setCurrentIndex(3);
        insertSpecialItem(cbb_v_size,"176x144");
        insertSpecialItem(cbb_v_bitrate,"180");
        cbb_v_fps->setCurrentIndex(3);
        cbb_v_ratio->setCurrentIndex(0);
        cbb_a_encoder->setCurrentIndex(0);
        cbb_a_srate->setCurrentIndex(1);
        cbb_a_bitrate->setCurrentIndex(3);
        insertSpecialItem(cbb_a_channel,"2");
        break;
        }
}

void dialogConversion::list_to_save(const QString &fmt){

    QSettings settings("danton","quality");

    switch(g_mediaType){
        case 1:

        settings.setValue(fmt+"_quality",cbb_parameter->currentText());
        settings.setValue(fmt+"_v_encoder",cbb_v_encoder->currentText());
        settings.setValue(fmt+"_v_size",cbb_v_size->currentText());
        settings.setValue(fmt+"_v_bitrate", cbb_v_bitrate->currentText());
        settings.setValue(fmt+"_v_fps", cbb_v_fps->currentText());
        settings.setValue(fmt+"_v_ratio", cbb_v_ratio->currentText());
        settings.setValue(fmt+"_a_encoder", cbb_a_encoder->currentText());
        settings.setValue(fmt+"_a_a_srate", cbb_a_srate->currentText());
        settings.setValue(fmt+"_a_bitrate", cbb_a_bitrate->currentText());
        settings.setValue(fmt+"_a_channel", cbb_a_channel->currentText());
        break;

        case 2:
        settings.setValue(fmt+"_quality", cbb_parameter->currentText());
        settings.setValue(fmt+"_a_srate", cbb_a_srate->currentText());
        settings.setValue(fmt+"_a_bitrate", cbb_a_bitrate->currentText());
        settings.setValue(fmt+"_a_channel", cbb_a_channel->currentText());
        break;

//        case 3:
//            break;

        }
}

void dialogConversion:: saveParameter(){

    list_to_save(g_target_format);

//not to save in QSettings, temp
//is there any cool way than below?
    if(g_target_format=="mp3")
        mp3_vol_ctr=cbb_volume_ctr->currentText();
    else if(g_target_format=="wma")
        wma_vol_ctr=cbb_volume_ctr->currentText();
    else  if(g_target_format=="ape")
        ape_vol_ctr=cbb_volume_ctr->currentText();
    else  if(g_target_format=="flac")
        flac_vol_ctr=cbb_volume_ctr->currentText();
    else  if(g_target_format=="aac")
        aac_vol_ctr=cbb_volume_ctr->currentText();
    else  if(g_target_format=="mmf")
        mmf_vol_ctr=cbb_volume_ctr->currentText();
    else  if(g_target_format=="m4a")
        m4a_vol_ctr=cbb_volume_ctr->currentText();
    else  if(g_target_format=="m4r")
        m4r_vol_ctr=cbb_volume_ctr->currentText();
    else  if(g_target_format=="amr")
        amr_vol_ctr=cbb_volume_ctr->currentText();
    else  if(g_target_format=="ogg")
        ogg_vol_ctr=cbb_volume_ctr->currentText();
    else if(g_target_format=="wav")
        wav_vol_ctr=cbb_volume_ctr->currentText();
    else  if(g_target_format=="mp2")
        mp2_vol_ctr=cbb_volume_ctr->currentText();


     updateLabelQuality();
     d_output_setting->accept();

}

void dialogConversion::clearTable()
{
    table_on_d_conv->clearContents();
    table_on_d_conv->setRowCount(0);
    tb_clear_list->setEnabled(false);
    tb_play_file->setEnabled(false);
    tb_delete_item->setEnabled(false);
    pb_ok->setEnabled(false);
    pb_option_on_d_conv->setEnabled(false);
}

void dialogConversion::onBtnDeleteClicked(){

    int baris_saat_ini = table_on_d_conv->currentRow();
    table_on_d_conv->removeRow(baris_saat_ini);

    if(table_on_d_conv->rowCount()==0){
        tb_delete_item->setEnabled(false);
        tb_clear_list->setEnabled(false);
        tb_play_file->setEnabled(false);
        pb_ok->setEnabled(false);
        tb_mediainfo->setEnabled(false);
        pb_option_on_d_conv->setEnabled(false);
    }
}

void dialogConversion::playFile()
{
    int row = table_on_d_conv->currentRow();
    QProcess *tb_play_file = new QProcess(this);
    tb_play_file->start("xdg-open", QStringList()<<table_on_d_conv->item(row,0)->toolTip());

}


void dialogConversion::insertSpecialItem(QComboBox *cabe, const QString &yy){
    cabe->setEditable(true);

    QLineEdit *xx = cabe->lineEdit();
    xx->setText(yy);
    xx->setReadOnly(true);
}

void dialogConversion::sendToMainTable(){
     QStringList toSent;
    for(int i=0;i<table_on_d_conv->rowCount();i++){
        toSent << table_on_d_conv->item(i,0)->toolTip();
    }

    emit sendFileList(toSent);
    emit sendOutputFolder(g_output_path);
    table_on_d_conv->clearContents();
    //save last dir
    QSettings setting("danton","danton");
    setting.setValue("last_dir",last_dir);
    setting.setValue("additionalFolder",additionalFolder);
    if(!additionalFolderList.isEmpty())
    setting.setValue("additionalFolderList",additionalFolderList);

    accept();

}


void dialogConversion::outputDir()
{

    QString path = QFileDialog::getExistingDirectory(this,"Pilih folder", QDir::homePath(),QFileDialog::ShowDirsOnly);

        if(!path.isEmpty()){
            g_output_path=path;
            cbb_output_path->addItem(g_output_path);
            cbb_output_path->setCurrentText(g_output_path);
            }

}

void dialogConversion::comboOutputFolder(int dex){
    //0 add folder
    //1 clear additional folder
    //2 save to surce

      if(dex==0){

        QString x = QFileDialog::getExistingDirectory(this, "Choose Folder", QDir::homePath(),QFileDialog::ShowDirsOnly);

        if(!x.isEmpty()){
                if(cbb_output_path->findText(x)==-1){
                additionalFolderList<<x;
                cbb_output_path->addItem(x);
                cbb_output_path->setCurrentText(x);
                currenIndex=cbb_output_path->currentIndex();
                }
                else{
                    cbb_output_path->setCurrentText(x);
                }

                emit sendOutputFolder(x);
                additionalFolder=true;
        }
        else{
            cbb_output_path->setCurrentIndex(currenIndex);
        }

    }

    if(dex==1){

        int curCount=cbb_output_path->count();
            while(curCount>defaultCount){
                cbb_output_path->removeItem(curCount);
                curCount--;
            }

        additionalFolderList.clear();
        cbb_output_path->setCurrentIndex(4);
        emit sendOutputFolder(cbb_output_path->itemText(4));
        additionalFolder=false;

        QSettings setting("danton", "danton");
        setting.setValue("additionalFolder",additionalFolder);
        setting.setValue("additionalFolderList",additionalFolderList);
    }

        if(dex==2)
        save_to_source=true;


//set uotput path
        if(dex>3)
        g_output_path=cbb_output_path->currentText();

}

void dialogConversion::updateLabelQuality()
{
    loadFromSetting();

    QMap<QString,QString> map;

    map["mp4"]=mp4_quality;
    map["avi"]=avi_quality;
    map["3gp"]=_3gp_quality;
    map["webm"]=webm_quality;
    map["mkv"]=mkv_quality;
    map["wmv"]=wmv_quality;
    map["mpg"]=mpg_quality;
    map["vob"]=vob_quality;
    map["mov"]=mov_quality;
    map["flv"]=flv_quality;
    map["swf"]=swf_quality;
    map["mp3"]=mp3_quality;
    map["wma"]=wma_quality;
    map["ape"]=ape_quality;
    map["flac"]=flac_quality;
    map["aac"]=aac_quality;
    map["mmf"]=mmf_quality;
    map["m4a"]=m4a_quality;
    map["m4r"]=m4r_quality;
    map["amr"]=amr_quality;
    map["ogg"]=ogg_quality;
    map["wav"]=wav_quality;
    map["mp2"]=mp2_quality;
    map["jpg"]=jpg_cur_text;
    map["png"]=png_cur_text;
    map["ico"]=ico_cur_text;
    map["bmp"]=bmp_cur_text;
    map["tif"]=tif_cur_text;
    map["pcx"]=pcx_cur_text;
    map["tga"]=tga_cur_text;

    l_quality->setText(map[g_target_format]);
}

void dialogConversion::loadFromFolder(){
    d_recursive = new QDialog;
    QGroupBox *gr_l =new QGroupBox;

    QHBoxLayout *lo_file = new QHBoxLayout;
    le_f_name = new QLineEdit();

    QPushButton *pb_browse = new QPushButton("browse");
    connect(pb_browse,SIGNAL(clicked(bool)), this, SLOT(selectFolder()));

    QHBoxLayout *lo_filter = new QHBoxLayout;

    QLabel *lb_filter = new QLabel();
    lb_filter->setText("Filter");

    cb_e = new QCheckBox();
    cb_e->setText("Entire folder");
    lo_filter->addWidget(lb_filter);
    lo_filter->addWidget(cb_e);

    connect(cb_e,SIGNAL(toggled(bool)),this,SLOT(entireSubDir(bool)));

    lo_file->addWidget(le_f_name);
    lo_file->addWidget(pb_browse);


    le_filter = new QLineEdit();


    switch(g_mediaType){
    case 1:
        le_filter->setText("*.mp4;*.avi;*.3gp;*.webm;*.mkv;*.wmv;*.mpg;*.vob;*.mov;*.flv;*.swf;*.dat");
        break;
    case 2:
        le_filter->setText("*.mp3;*.wma;*.ape;*.flac;*.amr;*.ogg;*.mp2");
        break;
    case 3:
        le_filter->setText("*.png;*.jpg");
        break;
    }


    QPushButton *oke = new QPushButton("OK");
    oke->setFixedWidth(100);
    connect(oke,SIGNAL(clicked(bool)), this, SLOT(filterFromFolder()));


    QVBoxLayout *a = new QVBoxLayout;

    a->addLayout(lo_file);
    a->addLayout(lo_filter);
    a->addWidget(le_filter);
    a->addWidget(oke);
    a->setAlignment(Qt::AlignHCenter);
    gr_l->setLayout(a);



    QVBoxLayout *lo_l = new QVBoxLayout;
    lo_l->addWidget(gr_l);
    d_recursive->setLayout(lo_l);
    d_recursive->setFixedWidth(480);
    d_recursive->setWindowTitle("Add files in folder");
    d_recursive->setAttribute(Qt::WA_DeleteOnClose);
    d_recursive->exec();

}


void dialogConversion::selectFolder(){
    QString pakdir = QFileDialog::getExistingDirectory(this,"choose dir", QDir::homePath(),QFileDialog::ShowDirsOnly);
    le_f_name->setText(pakdir);
}

void dialogConversion::filterFromFolder(){


    QString xa = le_f_name->text();
    QStringList filter = QStringList()<< le_filter->text().split(";");
    d_recursive->accept();

     QStringList files;



//how to show loading animation?

    QDirIterator it(xa, filter, QDir::Files, ent());


      while (it.hasNext()) {


            files << it.next();
       }


    emit sendtToTable(files);

}
void dialogConversion::entireSubDir(bool e){

    if(e)
        entireSubDir_ = QDirIterator::Subdirectories;
    else
        entireSubDir_ = QDirIterator::NoIteratorFlags;
}

void dialogConversion::getParameter(const QString &x, QString *fin_par){

   loadFromSetting();
   int mediaType = getMediaType(x);

   if(mediaType==1){
        struct parameter{
            QString v_encoder;
            QString v_size;
            QString v_bitrate;
            QString v_fps;
            QString v_ratio;
            QString a_encoder;
            QString a_rate;
            QString a_bitrate;
            QString a_channel;

        };



        parameter video;
        if(x=="mp4"){
        video.v_encoder=mp4_v_encoder;
        video.v_size=mp4_v_size;
        video.v_bitrate=mp4_v_bitrate;
        video.v_fps=mp4_v_fps;
        video.v_ratio=mp4_v_ratio;
        video.a_encoder=mp4_a_encoder;
        video.a_rate=mp4_a_a_srate;
        video.a_bitrate=mp4_a_bitrate;
        video.a_channel=mp4_a_channel;

        }

        else if(x=="avi"){
            video.v_encoder=avi_v_encoder;
            video.v_size=avi_v_size;
            video.v_bitrate=avi_v_bitrate;
            video.v_fps=avi_v_fps_avi;
            video.v_ratio=avi_v_ratio;
            video.a_encoder=avi_a_encoder;
            video.a_rate=avi_a_a_srate;
            video.a_bitrate=avi_a_bitrate;
            video.a_channel=avi_a_channel;

        }

        else if(x=="3gp"){
            video.v_encoder=_3gp_v_encoder;
            video.v_size=_3gp_v_size;
            video.v_bitrate=_3gp_v_bitrate;
            video.v_fps=_3gp_v_fps;
            video.v_ratio=_3gp_v_ratio;
            video.a_encoder=_3gp_a_encoder;
            video.a_rate=_3gp_a_a_srate;
            video.a_bitrate=_3gp_a_bitrate;
            video.a_channel=_3gp_a_channel;
        }

        else if(x=="mkv"){
            video.v_encoder=mkv_v_encoder;
            video.v_size=mkv_v_size;
            video.v_bitrate=mkv_v_bitrate;
            video.v_fps=mkv_v_fps;
            video.v_ratio=mkv_v_ratio;
            video.a_encoder=mkv_a_encoder;
            video.a_rate=mkv_a_a_srate;
            video.a_bitrate=mkv_a_bitrate;
            video.a_channel=mkv_a_channel;
        }

        else if(x=="wmv"){
            video.v_encoder=wmv_v_encoder;
            video.v_size=wmv_v_size;
            video.v_bitrate=wmv_v_bitrate;
            video.v_fps=wmv_v_fps;
            video.v_ratio=wmv_v_ratio;
            video.a_encoder=wmv_a_encoder;
            video.a_rate=wmv_a_a_srate;
            video.a_bitrate=wmv_a_bitrate;
            video.a_channel=wmv_a_channel;

        }

        else if(x=="mpg"){
            video.v_encoder=mpg_v_encoder;
            video.v_size=mpg_v_size;
            video.v_bitrate=mpg_v_bitrate;
            video.v_fps=mpg_v_fps;
            video.v_ratio=mpg_v_ratio;
            video.a_encoder=mpg_a_encoder;
            video.a_rate=mpg_a_a_srate;
            video.a_bitrate=mpg_a_bitrate;
            video.a_channel=mpg_a_channel;
        }

        else if(x=="vob"){
            video.v_encoder=vob_v_encoder;
            video.v_size=vob_v_size;
            video.v_bitrate=vob_v_bitrate;
            video.v_fps=vob_v_fps;
            video.v_ratio=vob_v_ratio;
            video.a_encoder=vob_a_encoder;
            video.a_rate=vob_a_a_srate;
            video.a_bitrate=vob_a_bitrate;
            video.a_channel=vob_a_channel;
        }

        else if(x=="mov"){
            video.v_encoder=mov_v_encoder;
            video.v_size=mov_v_size;
            video.v_bitrate=mov_v_bitrate;
            video.v_fps=mov_v_fps;
            video.v_ratio=mov_v_ratio;
            video.a_encoder=mov_a_encoder;
            video.a_rate=mov_a_a_srate;
            video.a_bitrate=mov_a_bitrate;
            video.a_channel=mov_a_channel;
        }

        else if(x=="flv"){
            video.v_encoder=flv_v_encoder;
            video.v_size=flv_v_size;
            video.v_bitrate=flv_v_bitrate;
            video.v_fps=flv_v_fps;
            video.v_ratio=flv_v_ratio;
            video.a_encoder=flv_a_encoder;
            video.a_rate=flv_a_a_srate;
            video.a_bitrate=flv_a_bitrate;
            video.a_channel=flv_a_channel;
        }

        else if(x=="swf"){
            video.v_encoder=swf_v_encoder;
            video.v_size=swf_v_size;
            video.v_bitrate=swf_v_bitrate;
            video.v_fps=swf_v_fps;
            video.v_ratio=swf_v_ratio;
            video.a_encoder=swf_a_encoder;
            video.a_rate=swf_a_a_srate;
            video.a_bitrate=swf_a_bitrate;
            video.a_channel=swf_a_channel;
        }

//video encoder
        if(video.v_encoder.contains("Xvid")){
            video.v_encoder="mpeg4;-vtag;xvid";
        }
        else if(video.v_encoder.contains("DivX")){
            video.v_encoder="mpeg4;-vtag;divx";
        }
        else if(video.v_encoder.contains("H264")){
            video.v_encoder="libx264";
        }

         else if(video.v_encoder=="mpeg1"){
            video.v_encoder="mpeg1video";
        }

        else if(video.v_encoder=="mpeg2"){
           video.v_encoder="mpeg2video";
        }

//video size
        video.v_size.replace("Auto",QString::number(-1));

               if(video.v_size.contains("x")){
            QRegExp sss("\\D\\d+x\\d+");
           int pos=0;
           if ((pos = sss.indexIn(video.v_size, pos)) != -1) {
            video.v_size=sss.cap(0);
            video.v_size.replace("x",":");

            }
        }
//audio encoder
        if(video.a_encoder=="MP3"){
            video.a_encoder="libmp3lame";
        }


        video.a_channel.replace("2 stereo","2");

        fin_par->append("-c:v;"+video.v_encoder.toLower());

        fin_par->append(";-q:v;2;");//quality

        if(video.v_size!="Default")
        fin_par->append("-vf;scale="+video.v_size+";");

        if(video.v_bitrate!="Default")
        fin_par->append("-b:v;"+video.v_bitrate+"k;");

        if(video.v_fps!="Default")
        fin_par->append("-r;"+video.v_fps+";");
         if(video.v_ratio!="Automatic"){
        fin_par->append("-aspect;"+video.v_ratio+";");}

        fin_par->append("-c:a;"+video.a_encoder.toLower()+";");

        fin_par->append("-b:a;"+video.a_bitrate+"k;");
        fin_par->append("-ar;"+video.a_rate+";");
        fin_par->append("-ac;"+video.a_channel);

    }//end vvideo parmtr

    if(mediaType==2){
        struct parameter{
            QString a_encoder;
            QString a_rate;
            QString a_bitrate;
            QString a_channel;
            QString a_volume;

        };

        parameter audio;

        if(g_target_format=="mp3"){
            audio.a_encoder="libmp3lame";
            audio.a_rate=mp3_a_srate;
            audio.a_bitrate=mp3_a_bitrate;
            audio.a_channel=mp3_a_channel;
            audio.a_volume=mp3_vol_ctr;
        }

        else if(g_target_format=="wma"){
            audio.a_encoder="wmav2";
            audio.a_rate=wav_a_srate;
            audio.a_bitrate=wma_a_bitrate;
            audio.a_channel=wma_a_channel;
            audio.a_volume=wma_vol_ctr;


        }

        else if(g_target_format=="flac"){
            audio.a_encoder="flac";
            audio.a_rate=flac_a_srate;
            audio.a_bitrate=flac_a_bitrate;
            audio.a_channel=flac_a_channel;
            audio.a_volume=flac_vol_ctr;
        }
        else if(g_target_format=="aac"){
            audio.a_encoder="libfdk_aac";
            audio.a_rate=aac_a_srate;
            audio.a_bitrate=aac_a_bitrate;
            audio.a_channel=aac_a_channel;
            audio.a_volume=aac_vol_ctr;
        }

        else if(g_target_format=="m4a"){
            audio.a_encoder="libfdk_aac";
            audio.a_bitrate=m4a_a_bitrate;
            audio.a_rate=m4a_a_srate;
            audio.a_channel=m4a_a_channel;
            audio.a_volume=m4a_vol_ctr;
        }

        else if(g_target_format=="mmf"){
             audio.a_encoder="mmf";
             audio.a_rate=mmf_a_srate;
             audio.a_bitrate=mmf_a_bitrate;
             audio.a_channel=mmf_a_channel;
             audio.a_volume=mmf_vol_ctr;
        }

        else if(g_target_format=="m4r"){
            audio.a_encoder="libfaac";
            audio.a_rate=m4r_a_srate;
            audio.a_bitrate=m4a_a_bitrate;
            audio.a_channel=m4a_a_channel;
            audio.a_volume=m4r_vol_ctr;
        }

        else if(g_target_format=="amr"){
            audio.a_encoder="amr";
            audio.a_rate=amr_a_srate;
            audio.a_bitrate=amr_a_bitrate;
            audio.a_channel=amr_a_channel;
            audio.a_volume=amr_vol_ctr;
        }
        else if(g_target_format=="ogg"){
            audio.a_encoder="libvorbis";
            audio.a_rate=ogg_a_srate;
            audio.a_bitrate=ogg_a_bitrate;
            audio.a_channel=ogg_a_channel;
            audio.a_volume=ogg_vol_ctr;
        }
        else if(g_target_format=="wav"){
            audio.a_encoder="wav";
            audio.a_rate=wav_a_srate;
            audio.a_bitrate=wav_a_bitrate;
            audio.a_channel=wav_a_channel;
            audio.a_volume=wav_vol_ctr;
        }
        else if(g_target_format=="mp2"){
            audio.a_encoder="mp2";
            audio.a_rate=mp2_a_srate;
            audio.a_bitrate=mp2_a_bitrate;
            audio.a_channel=mp2_a_channel;
            audio.a_volume=mp2_vol_ctr;
        }


        fin_par->append("-c:a;"+audio.a_encoder);
          if(audio.a_bitrate!="Automatic")
        fin_par->append(";-b:a;"+audio.a_bitrate);
          if(audio.a_rate!="Automatic")
        fin_par->append(";-ar;"+audio.a_rate);
          if(audio.a_channel!="Automatic")
        fin_par->append(";-ac;"+audio.a_channel);
          if(audio.a_volume!="100%"){
              audio.a_volume.replace("50%","0.5");
              audio.a_volume.replace("150%","1.5");
              audio.a_volume.replace("200%","2.0");
              fin_par->append(";-af \"volume="+audio.a_volume+"\"");
          }


    }//end audio prmtr

    if (mediaType==3){

       QString angle;
//       QString font;
//       QString font_size;

       if(g_target_format=="jpg" ){
           if(jpg_rotate){
           angle=jpg_angle;
           }

       }

       if(g_target_format=="png" && png_rotate){
           angle=png_angle;
       }
       qDebug()<<angle<<"angle";


       if(angle!="0" && !angle.isEmpty()){
       fin_par->append("-rotate;"+angle);
       }

    }//end pict param


}


QString dialogConversion::subLoad(QString g, const QString &h, const QString &i){

    QSettings settings("danton","quality");
    g=settings.value(i).toString();

    //set default if empty
    if(g.isEmpty()){
        g=h;
    }
    return g;
}

void dialogConversion::loadFromSetting()
{

    if(g_target_format=="mp4"){

         mp4_quality=subLoad(mp4_quality,"High quality and size","mp4_quality");
         mp4_v_encoder=subLoad(mp4_v_encoder,"MPEG4(Divx)","mp4_v_encoder");
         mp4_v_size=subLoad(mp4_v_size,"Default","mp4_v_size");
         mp4_v_bitrate=subLoad(mp4_v_bitrate,"Default","mp4_v_bitrate");
         mp4_v_fps=subLoad(mp4_v_fps,"Default","mp4_v_fps");
         mp4_v_ratio=subLoad(mp4_v_ratio,"Automatic","mp4_video-ratio");
         mp4_a_encoder=subLoad(mp4_a_encoder,"AAC","mp4_a_encoder");
         mp4_a_a_srate=subLoad(mp4_a_a_srate,"44100","mp4_a_a_srate");
         mp4_a_bitrate=subLoad(mp4_a_bitrate,"128","mp4_a_bitrate");
         mp4_a_channel=subLoad(mp4_a_channel,"2","mp4_a_channel");

    }

    else if(g_target_format=="avi"){
         avi_quality=subLoad(avi_quality,"High quality and size","avi_quality");
         avi_v_encoder=subLoad(avi_v_encoder,"MPEG(Xvid)","avi_v_encoder");
         avi_v_size=subLoad(avi_v_size,"Default","avi_v_size");
         avi_v_bitrate=subLoad(avi_v_bitrate,"Default","avi_v_bitrate");
         avi_v_fps_avi=subLoad(avi_v_fps_avi,"24","avi_v_fps_avi");
         avi_v_ratio=subLoad(avi_v_ratio,"Automatic(Width)","avi_v_ratio");
         avi_a_encoder=subLoad(avi_a_encoder,"MP3","avi_a_encoder");
         avi_a_a_srate=subLoad(avi_a_a_srate,"44100","avi_a_a_srate");
         avi_a_bitrate=subLoad(avi_a_bitrate,"128","avi_a_bitrate");
         avi_a_channel=subLoad(avi_a_channel,"2","avi_a_channel");

    }

    else if(g_target_format=="3gp"){
         _3gp_quality=subLoad(_3gp_quality,"176x144 H263","_3gp_quality");
         _3gp_v_encoder=subLoad(_3gp_v_encoder,"H263","_3gp_v_encoder");
         _3gp_v_size=subLoad(_3gp_v_size,"176x144","_3gp_v_size");
         _3gp_v_bitrate=subLoad(_3gp_v_bitrate,"160","_3gp_v_bitrate");
         _3gp_v_fps=subLoad(_3gp_v_fps,"15","_3gp_v_fps");
         _3gp_v_ratio=subLoad(_3gp_v_ratio,"Automatic","_3gp_v_ratio");
         _3gp_a_encoder=subLoad(_3gp_a_encoder,"AMR_NB","_3gp_a_encoder");
         _3gp_a_a_srate=subLoad(_3gp_a_a_srate,"8000","_3gp_a_a_srate");
         _3gp_a_bitrate=subLoad(_3gp_a_bitrate,"12.20","_3gp_a_bitrate");
         _3gp_a_channel=subLoad(_3gp_a_channel,"1","_3gp_a_channel");

    }
//    else if(g_target_format=="webm"){

//        webm_quality=settings.value("webm_quality").toString();
//    }

     else if(g_target_format=="mkv"){
         mkv_quality=subLoad(mkv_quality,"High quality and size","mkv_quality");
         mkv_v_encoder=subLoad(mkv_v_encoder,"AVC(H264)","mkv_v_encoder");
         mkv_v_size=subLoad(mkv_v_size,"Default","mkv_v_size");
         mkv_v_bitrate=subLoad(mkv_v_bitrate,"Default","mkv_v_bitrate");
         mkv_v_fps=subLoad(mkv_v_fps,"Default","mkv_v_fps");
         mkv_v_ratio=subLoad(mkv_v_ratio,"Automatic(Width)","mkv_v_ratio");
         mkv_a_encoder=subLoad(mkv_a_encoder,"AAC","mkv_a_encoder");
         mkv_a_a_srate=subLoad(mkv_a_a_srate,"44100","mkv_a_a_srate");
         mkv_a_bitrate=subLoad(mkv_a_bitrate,"128","mkv_a_bitrate");
         mkv_a_channel=subLoad(mkv_a_channel,"2","mkv_a_channel");
    }

//     else if(g_target_format=="gif"){
//        gif_quality=settings.value("gif_quality").toString();
//    }

    else if(g_target_format=="wmv"){
         wmv_quality=subLoad(wmv_quality,"High quality and size","wmv_quality");
         wmv_v_encoder=subLoad(wmv_v_encoder,"WMV2","wmv_v_encoder");
         wmv_v_size=subLoad(wmv_v_size,"Default","wmv_v_size");
         wmv_v_bitrate=subLoad(wmv_v_bitrate,"Default","wmv_v_bitrate");
         wmv_v_fps=subLoad(wmv_v_fps,"Default","wmv_v_fps");
         wmv_v_ratio=subLoad(wmv_v_ratio,"Automatic(Width)","wmv_v_ratio");
         wmv_a_encoder=subLoad(wmv_a_encoder,"WMAV2","wmv_a_encoder");
         wmv_a_a_srate=subLoad(wmv_a_a_srate,"44100","wmv_a_a_srate");
         wmv_a_bitrate=subLoad(wmv_a_bitrate,"128","wmv_a_bitrate");
         wmv_a_channel=subLoad(wmv_a_channel,"2","wmv_a_channel");
    }

    else if(g_target_format=="mpg"){
         mpg_quality=subLoad(mpg_quality,"VCD PAL","mpg_quality");
         mpg_v_encoder=subLoad(mpg_v_encoder,"mpeg1","mpg_v_encoder");
         mpg_v_size=subLoad(mpg_v_size,"353x288","mpg_v_size");
         mpg_v_bitrate=subLoad(mpg_v_bitrate,"1150","mpg_v_bitrate");
         mpg_v_fps=subLoad(mpg_v_fps,"25","mpg_v_fps");
         mpg_v_ratio=subLoad(mpg_v_ratio,"4:3","mpg_v_ratio");
         mpg_a_encoder=subLoad(mpg_a_encoder,"MP2","mpg_a_encoder");
         mpg_a_a_srate=subLoad(mpg_a_a_srate,"44100","mpg_a_a_srate");
         mpg_a_bitrate=subLoad(mpg_a_bitrate,"224","mpg_a_bitrate");
         mpg_a_channel=subLoad(mpg_a_channel,"2","mpg_a_channel");

    }
    else if(g_target_format=="vob"){
         vob_quality=subLoad(vob_quality,"DVD NTSC small","vob_quality");
         vob_v_encoder=subLoad(vob_v_encoder,"mpeg2","vob_v_encoder");
         vob_v_size=subLoad(vob_v_size,"352x240","vob_v_size");
         vob_v_bitrate=subLoad(vob_v_bitrate,"1856","vob_v_bitrate");
         vob_v_fps=subLoad(vob_v_fps,"29.97","vob_v_fps");
         vob_v_ratio=subLoad(vob_v_ratio,"Automatic","vob_v_ratio");
         vob_a_encoder=subLoad(vob_a_encoder,"AC3","vob_a_encoder");
         vob_a_a_srate=subLoad(vob_a_a_srate,"48000","vob_a_a_srate");
         vob_a_bitrate=subLoad(vob_a_bitrate,"448","vob_a_bitrate");
         vob_a_channel=subLoad(vob_a_channel,"2","vob_a_channel");
    }
    else if(g_target_format=="mov"){
         mov_quality=subLoad(mov_quality,"High quality and size","mov_quality");
         mov_v_encoder=subLoad(mov_v_encoder,"AVC(H264)","mov_v_encoder");
         mov_v_size=subLoad(mov_v_size,"Default","mov_v_size");
         mov_v_bitrate=subLoad(mov_v_bitrate,"Default","mov_v_bitrate");
         mov_v_fps=subLoad(mov_v_fps,"24","mov_v_fps");
         mov_v_ratio=subLoad(mov_v_ratio,"Automatic(Width)","mov_v_ratio");
         mov_a_encoder=subLoad(mov_a_encoder,"AAC","mov_a_encoder");
         mov_a_a_srate=subLoad(mov_a_a_srate,"44100","mov_a_a_srate");
         mov_a_bitrate=subLoad(mov_a_bitrate,"128","mov_a_bitrate");
         mov_a_channel=subLoad(mov_a_channel,"2","mov_a_channel");
    }

    else if(g_target_format=="flv"){
         flv_quality=subLoad(flv_quality,"320x240","flv_quality");
         flv_v_encoder=subLoad(flv_v_encoder,"FLV1","flv_v_encoder");
         flv_v_size=subLoad(flv_v_size,"320x240","flv_v_size");
         flv_v_bitrate=subLoad(flv_v_bitrate,"384","flv_v_bitrate");
         flv_v_fps=subLoad(flv_v_fps,"18","flv_v_fps");
         flv_v_ratio=subLoad(flv_v_ratio,"Automatic","flv_v_ratio");
         flv_a_encoder=subLoad(flv_a_encoder,"MP3","flv_a_encoder");
         flv_a_a_srate=subLoad(flv_a_a_srate,"22050","flv_a_a_srate");
         flv_a_bitrate=subLoad(flv_a_bitrate,"64","flv_a_bitrate");
         flv_a_channel=subLoad(flv_a_channel,"2","flv_a_channel");
 }

else if(g_target_format=="swf"){
         swf_quality=subLoad(swf_quality,"320x240","swf_quality");
         swf_v_encoder=subLoad(swf_v_encoder,"FLV1","swf_v_encoder");
         swf_v_size=subLoad(swf_v_size,"320x240","swf_v_size");
         swf_v_bitrate=subLoad(swf_v_bitrate,"384","swf_v_bitrate");
         swf_v_fps=subLoad(swf_v_fps,"18","swf_v_fps");
         swf_v_ratio=subLoad(swf_v_ratio,"Automatic","swf_v_ratio");
         swf_a_encoder=subLoad(swf_a_encoder,"MP3","swf_a_encoder");
         swf_a_a_srate=subLoad(swf_a_a_srate,"22050","swf_a_a_srate");
         swf_a_bitrate=subLoad(swf_a_bitrate,"64","swf_a_bitrate");
         swf_a_channel=subLoad(swf_a_channel,"2","swf_a_channel");
   }

    else if(g_target_format=="mp3"){
            mp3_quality=subLoad(mp3_quality,"High quality","mp3_quality");
            mp3_a_bitrate=subLoad(mp3_a_bitrate,"Automatic","mp3_a_bitrate");
            mp3_a_srate=subLoad(mp3_a_srate,"Automatic","mp3_a_srate");
            mp3_a_channel=subLoad(mp3_a_channel,"Automatic", "mp3_a_channel");
           // mp3_vol_ctr=subLoad(mp3_vol_ctr,"100%","mp3_vol_ctr");
    }

    else if(g_target_format=="wma"){
            wma_quality=subLoad(wma_quality,"High quality","wma_quality");
            wma_a_bitrate=subLoad(wma_a_bitrate,"Automatic","wma_a_bitrate");
            wma_a_srate=subLoad(wma_a_srate,"Automatic","wma_a_srate");
            wma_a_channel=subLoad(wma_a_channel,"Automatic", "wma_a_channel");
           // wma_vol_ctr=subLoad(wma_vol_ctr,"100%","wma_vol_ctr");
    }

    else if(g_target_format=="ape"){

            ape_a_srate=subLoad(ape_a_srate,"Automatic","ape_a_srate");
            ape_a_bitrate="Automatic";
            ape_a_channel="Automatic";
           // ape_vol_ctr=subLoad(ape_vol_ctr,"100%","ape_vol_ctr");
    }

    else if(g_target_format=="flac"){
            flac_quality=subLoad(flac_quality,"High quality","flac_quality");
            flac_a_bitrate=subLoad(flac_a_bitrate,"Automatic","flac_a_bitrate");
            flac_a_srate=subLoad(flac_a_srate,"Automatic","flac_a_srate");
            flac_a_channel=subLoad(flac_a_channel,"Automatic", "flac_a_channel");
           // flac_vol_ctr=subLoad(flac_vol_ctr,"100%","flac_vol_ctr");
    }

    else if(g_target_format=="aac"){
            aac_quality=subLoad(aac_quality,"High quality","aac_quality");
            aac_a_bitrate=subLoad(aac_a_bitrate,"Automatic","aac_a_bitrate");
            aac_a_srate=subLoad(aac_a_srate,"Automatic","aac_a_srate");
            aac_a_channel=subLoad(aac_a_channel,"Automatic", "aac_a_channel");
            //aac_vol_ctr=subLoad(aac_vol_ctr,"100%","aac_vol_ctr");
    }

    else if(g_target_format=="mmf"){
            mmf_quality=subLoad(mmf_quality,"High quality","mmf_quality");
            mmf_a_bitrate="Automatic";
            mmf_a_srate=subLoad(mmf_a_srate,"8000","mmf_a_srate");
            mmf_a_channel=subLoad(mmf_a_channel,"1", "mmf_a_channel");
            //mmf_vol_ctr=subLoad(mmf_vol_ctr,"100%","mmf_vol_ctr");
    }

    else if(g_target_format=="m4a"){
            m4a_quality=subLoad(m4a_quality,"High quality","m4a_quality");
            m4a_a_bitrate=subLoad(m4a_a_bitrate,"Automatic","m4a_a_bitrate");
            m4a_a_srate=subLoad(m4a_a_srate,"Automatic","m4a_a_srate");
            m4a_a_channel=subLoad(m4a_a_channel,"Automatic", "m4a_a_channel");
            //m4a_vol_ctr=subLoad(m4a_vol_ctr,"100%","m4a_vol_ctr");
    }

    else if(g_target_format=="m4r"){
            m4r_quality=subLoad(m4r_quality,"High quality","m4r_quality");
            m4r_a_bitrate=subLoad(m4r_a_bitrate,"Automatic","m4r_a_bitrate");
            m4r_a_srate=subLoad(m4r_a_srate,"Automatic","m4r_a_srate");
            m4r_a_channel=subLoad(m4r_a_channel,"Automatic", "m4r_a_channel");
            //m4r_vol_ctr=subLoad(m4r_vol_ctr,"100%","m4r_vol_ctr");
    }

    else if(g_target_format=="amr"){
            amr_quality=subLoad(amr_quality,"High quality","amr_quality");
            amr_a_bitrate=subLoad(amr_a_bitrate,"12","amr_a_bitrate");
            amr_a_srate="8000";
            amr_a_channel=subLoad(amr_a_channel,"1", "amr_a_channel");
            //amr_vol_ctr=subLoad(amr_vol_ctr,"100%","amr_vol_ctr");
    }

    else if(g_target_format=="ogg"){
            ogg_quality=subLoad(ogg_quality,"High quality","ogg_quality");
            ogg_a_bitrate=subLoad(ogg_a_bitrate,"Automatic","ogg_a_bitrate");
            ogg_a_srate=subLoad(ogg_a_srate,"Automatic","ogg_a_srate");
            ogg_a_channel=subLoad(ogg_a_channel,"Automatic", "ogg_a_channel");
            //ogg_vol_ctr=subLoad(ogg_vol_ctr,"100%","ogg_vol_ctr");
    }

    else if(g_target_format=="wav"){
            wav_quality=subLoad(wav_quality,"High quality","wav_quality");
            wav_a_bitrate="Automatic";
            wav_a_srate=subLoad(wav_a_srate,"Automatic","wav_a_srate");
            wav_a_channel=subLoad(wav_a_channel,"Automatic", "wav_a_channel");
            //wav_vol_ctr=subLoad(wav_vol_ctr,"100%","wav_vol_ctr");
    }

    else if(g_target_format=="mp2"){
            mp2_quality=subLoad(mp2_quality,"High quality","mp2_quality");
            mp2_a_bitrate=subLoad(mp2_a_bitrate,"Automatic","mp2_a_bitrate");;
            mp2_a_srate=subLoad(mp2_a_srate,"Automatic","mp2_a_srate");
            mp2_a_channel=subLoad(mp2_a_channel,"Automatic", "mp2_a_channel");
            //mp2_vol_ctr=subLoad(mp2_vol_ctr,"100%","mp2_vol_ctr");
    }

}

int dialogConversion::getMediaType(const QString &mt){

    int cur_media_type=0;
     if(mt=="mp4" || mt=="avi" || mt=="3gp" || mt=="webm" || mt=="mkv" || mt=="gif" || mt=="wmv" || mt=="mpg" || mt=="vob" || mt=="mov" || mt=="flv" || mt=="swf"){
         return cur_media_type=1;
     }
     else if(mt=="mp3" || mt=="wma" || mt=="ape" || mt=="flac" || mt=="aac" || mt=="mmf" || mt=="m4a" || mt=="m4r" || mt=="amr" || mt=="ogg" || mt=="wav" || mt=="mp2"){
        return cur_media_type=2;
     }

     else if(mt=="webp" || mt=="jpg" || mt=="png" || mt=="ico" || mt=="bmp" || mt=="gif" || mt=="tif" || mt=="pcx" || mt=="tga"){
         return cur_media_type=3;
    }
     return cur_media_type;
 }


float dialogConversion::getDuration(QString file){
            file.replace("\"", "\\\"");
            file.replace( "`", "\\`" );
            QString cmd="ffprobe -v error -show_entries format=duration -of default=noprint_wrappers=1:nokey=1 \""+file+"\"";
            FILE* pipe = popen(cmd.toLocal8Bit().data(), "r");
            char buffer[10];
            string result = "";
            while(!feof(pipe)) {
                if(fgets(buffer, 10, pipe) != NULL)
                    result += buffer;
                }
            pclose(pipe);
            QString res = QString::fromStdString(result);
           return res.toFloat();
}

QString dialogConversion::getVideoSize(QString file){
    file.replace("\"", "\\\"");
    file.replace( "`", "\\`" );
    QString cmd="ffprobe -v error -select_streams v:0 -show_entries stream=height,width -of default=noprint_wrappers=1:nokey=1 \""+file+"\"";
    FILE* pipe = popen(cmd.toLocal8Bit().data(), "r");
    char buffer[10];
    string result = "";
    while(!feof(pipe)) {
        if(fgets(buffer, 10, pipe) != NULL)
            result += buffer;
        }
    pclose(pipe);

    QString res = QString::fromStdString(result);
    res.replace("\n","x").chop(1);
    return res;
}

void dialogConversion::on_cbb_parameter_mp3_changed(int i)
{
    switch(i){
    case 0:
        cbb_a_srate->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(0);
        cbb_a_channel->setCurrentIndex(0);
        cbb_volume_ctr->setCurrentIndex(1);

        break;
    case 1:
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_a_channel->setCurrentIndex(0);
        cbb_volume_ctr->setCurrentIndex(1);
        break;
    case 2:
        cbb_a_srate->setCurrentIndex(3);
        cbb_a_bitrate->setCurrentIndex(8);
        cbb_a_channel->setCurrentIndex(0);
        cbb_volume_ctr->setCurrentIndex(1);
        break;

    }
}

void dialogConversion::on_cbb_parameter_wma_changed(int i){
    switch(i){
    case 0:
        cbb_a_srate->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(0);
        cbb_a_channel->setCurrentIndex(0);
        cbb_volume_ctr->setCurrentIndex(1);
        break;
    case 1:
        cbb_a_srate->setCurrentIndex(1);
        cbb_a_bitrate->setCurrentIndex(2);
        cbb_a_channel->setCurrentIndex(0);
        cbb_volume_ctr->setCurrentIndex(1);
        break;
    case 2:
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_a_channel->setCurrentIndex(0);
        cbb_volume_ctr->setCurrentIndex(1);
        break;
    }
}

void dialogConversion::on_cbb_parameter_flac_changed(int i){
    switch(i){
    case 0:
        cbb_a_srate->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(0);
        cbb_a_channel->setCurrentIndex(0);
        cbb_a_channel->setEditable(false);
        cbb_volume_ctr->setCurrentIndex(1);
        break;
    case 1:
        cbb_a_srate->setCurrentIndex(1);
        insertSpecialItem(cbb_a_bitrate, "128");
        cbb_a_channel->setCurrentIndex(0);
        cbb_a_channel->setEditable(false);
        cbb_volume_ctr->setCurrentIndex(1);
        break;
    case 2:
        cbb_a_srate->setCurrentIndex(2);
        insertSpecialItem(cbb_a_bitrate,"32");
        cbb_a_channel->setCurrentIndex(0);
        cbb_a_channel->setEditable(false);
        cbb_volume_ctr->setCurrentIndex(1);
        break;
    case 3:
        cbb_a_srate->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(0);
        insertSpecialItem(cbb_a_channel,"8");
        cbb_volume_ctr->setCurrentIndex(1);
        break;
    case 4:
        cbb_a_srate->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(0);
        insertSpecialItem(cbb_a_channel,"6");
        cbb_volume_ctr->setCurrentIndex(1);
        break;
    }
}

void dialogConversion::on_cbb_parameter_aac_changed(int i){
    switch(i){
        case 0:
            cbb_a_srate->setCurrentIndex(0);
            cbb_a_bitrate->setCurrentIndex(0);
            cbb_a_channel->setCurrentIndex(0);
            cbb_volume_ctr->setCurrentIndex(1);
            break;
        case 1:
            cbb_a_srate->setCurrentIndex(1);
            cbb_a_bitrate->setCurrentIndex(2);
            cbb_a_channel->setCurrentIndex(0);
            cbb_volume_ctr->setCurrentIndex(1);
            break;
        case 2:
            cbb_a_srate->setCurrentIndex(2);
            cbb_a_bitrate->setCurrentIndex(5);
            cbb_a_channel->setCurrentIndex(0);
            cbb_volume_ctr->setCurrentIndex(1);
            break;

        }
}

void dialogConversion::on_cbb_parameter_mmf_changed(int ){
    switch(cbb_parameter->currentIndex()){
    case 0:
        cbb_a_srate->setCurrentIndex(0);
        insertSpecialItem(cbb_a_channel,"1");
        cbb_volume_ctr->setCurrentIndex(1);
        break;
    case 1:
        cbb_a_srate->setCurrentIndex(1);
        insertSpecialItem(cbb_a_channel,"1");
        cbb_volume_ctr->setCurrentIndex(1);
        break;
        }
}

void dialogConversion::on_cbb_parameter_amr_changed(int i){

    switch(i){
        case 0:
            insertSpecialItem(cbb_a_bitrate,"12");
            insertSpecialItem(cbb_a_channel,"1");
            cbb_volume_ctr->setCurrentIndex(1);
            break;
    case 1:
            insertSpecialItem(cbb_a_bitrate,"6");
            insertSpecialItem(cbb_a_channel,"1");
            cbb_volume_ctr->setCurrentIndex(1);
            break;
    }

}

void dialogConversion::on_cbb_parameter_m4a_changed(int i){

    switch(i){
    case 0:
        cbb_a_srate->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(0);
        cbb_a_channel->setCurrentIndex(0);
        cbb_volume_ctr->setCurrentIndex(1);
        break;
    case 1:
        cbb_a_srate->setCurrentIndex(1);
        cbb_a_bitrate->setCurrentIndex(2);
        cbb_a_channel->setCurrentIndex(0);
        cbb_volume_ctr->setCurrentIndex(1);
        break;
    case 2:
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_a_channel->setCurrentIndex(0);
        cbb_volume_ctr->setCurrentIndex(1);
        break;
    }
}

void dialogConversion::on_cbb_parameter_m4r_changed(int i){
    switch(i){
    case 0:
        cbb_a_srate->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(0);
        cbb_a_channel->setCurrentIndex(0);
        cbb_volume_ctr->setCurrentIndex(1);
        break;
    case 1:
        cbb_a_srate->setCurrentIndex(1);
        cbb_a_bitrate->setCurrentIndex(2);
        cbb_a_channel->setCurrentIndex(0);
        cbb_volume_ctr->setCurrentIndex(1);
        break;
    case 2:
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_a_channel->setCurrentIndex(0);
        cbb_volume_ctr->setCurrentIndex(1);
        break;

    }
}

void dialogConversion::on_cbb_parameter_ogg_changed(int i){
    switch(i){
    case 0:
        cbb_a_srate->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(0);
        cbb_a_channel->setCurrentIndex(0);
        cbb_volume_ctr->setCurrentIndex(1);
        break;
    case 1:
        cbb_a_srate->setCurrentIndex(1);
        cbb_a_bitrate->setCurrentIndex(2);
        cbb_a_channel->setCurrentIndex(0);
        cbb_volume_ctr->setCurrentIndex(1);
        break;
    case 2:
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_a_channel->setCurrentIndex(0);
        cbb_volume_ctr->setCurrentIndex(1);
        break;
    }
}

void dialogConversion::on_cbb_parameter_wav_changed(int i){
    switch(i){
    case 0:
        cbb_a_srate->setCurrentIndex(0);
        cbb_a_channel->setCurrentIndex(0);
        cbb_a_channel->setEditable(false);
        cbb_volume_ctr->setCurrentIndex(1);
        break;
    case 1:
        cbb_a_srate->setCurrentIndex(1);
        insertSpecialItem(cbb_a_channel,"2");
        cbb_volume_ctr->setCurrentIndex(1);
        break;
    case 2:
        cbb_a_srate->setCurrentIndex(2);
        insertSpecialItem(cbb_a_channel,"2");
        cbb_volume_ctr->setCurrentIndex(1);
        break;
    case 3:
        cbb_a_srate->setCurrentIndex(0);
        insertSpecialItem(cbb_a_channel,"8");
        cbb_volume_ctr->setCurrentIndex(1);
        break;
    case 4:
        cbb_a_srate->setCurrentIndex(0);
        insertSpecialItem(cbb_a_channel,"6");
        cbb_volume_ctr->setCurrentIndex(1);
        break;
    }
}

void dialogConversion::on_cbb_parameter_mp2_changed(int i){
    switch(i){
    case 0:
        cbb_a_srate->setCurrentIndex(0);
        cbb_a_bitrate->setCurrentIndex(0);
        cbb_a_channel->setCurrentIndex(0);
        cbb_volume_ctr->setCurrentIndex(1);
        break;
    case 1:
        cbb_a_srate->setCurrentIndex(2);
        cbb_a_bitrate->setCurrentIndex(5);
        cbb_a_channel->setCurrentIndex(0);
        cbb_volume_ctr->setCurrentIndex(1);
        break;
    case 2:
        cbb_a_srate->setCurrentIndex(3);
        cbb_a_bitrate->setCurrentIndex(8);
        cbb_a_channel->setCurrentIndex(0);
        cbb_volume_ctr->setCurrentIndex(1);
        break;
    }
}

void dialogConversion::audioChannelValueConvert(){

    QString x = cbb_a_channel->currentText();
    if(x!="Automatic"){
        x.replace("8 Stereo 7.1", "8");
        x.replace("6 Stereo 5.1", "6");
        x.replace("2 Stereo","2");
        x.replace("1 Mono","1");
        insertSpecialItem(cbb_a_channel, x);
    }
    else{
        cbb_a_channel->setEditable(false);
    }
}


void dialogConversion::cso_output_dialog_setting(){

    d_output_setting = new QDialog(this);
    QGroupBox *gr_cso_output = new QGroupBox();
    QHBoxLayout *lo_output_cso = new QHBoxLayout();

    QLabel *lb_compress = new QLabel();
    lb_compress->setText("Compress level");

    sd_cso = new QSlider(Qt::Horizontal);
    sd_cso->setRange(1,9);
    sd_cso->setValue(value_compress);
    connect(sd_cso,SIGNAL(valueChanged(int)),this,SLOT(changeValueCompress()));

    lb_value_compress = new QLabel();
    lb_value_compress->setText(QString::number(value_compress));

    QPushButton *pb_ok_cso = new QPushButton("OK");
    connect(pb_ok_cso,SIGNAL(clicked(bool)),this,SLOT(saveValueCompress()));

    lo_output_cso->addWidget(lb_compress);
    lo_output_cso->addWidget(sd_cso);
    lo_output_cso->addWidget(lb_value_compress);
    lo_output_cso->addWidget(pb_ok_cso);

    gr_cso_output->setLayout(lo_output_cso);
    gr_cso_output->setStyleSheet("QGroupBox{border: 1px solid #ccc;border-radius:8px;margin-top:0.5em}");

    QHBoxLayout *lo_cso = new QHBoxLayout();
    lo_cso->addWidget(gr_cso_output);
    d_output_setting->setLayout(lo_cso);
    d_output_setting->setFixedSize(500,180);
    d_output_setting->setWindowTitle("ISO <--> CSO");
    d_output_setting->exec();

}

void dialogConversion::changeValueCompress(){

    lb_value_compress->setText(QString::number(sd_cso->sliderPosition()));

}

void dialogConversion::saveValueCompress(){

    value_compress = sd_cso->sliderPosition();
    d_output_setting->accept();
}

void dialogConversion::dialogOption(){

    d_option = new QDialog(this);

    QHBoxLayout *lo_d_option = new QHBoxLayout;

    int crow = table_on_d_conv->currentRow();
    QString file = table_on_d_conv->item(crow,0)->toolTip();

    QVBoxLayout *lo_left = new QVBoxLayout;
    QVBoxLayout *lo_right = new QVBoxLayout;



    player = new QMediaPlayer(d_option);

    QVideoWidget *vw = new QVideoWidget(d_option);
    vw->setAttribute(Qt::WA_DeleteOnClose);

    player->setVideoOutput(vw);
    player->setMedia(QUrl::fromLocalFile(file));
    vw->setGeometry(0,0,400,200);

    player->play();

    QHBoxLayout *lo_v_control = new QHBoxLayout;

    l_curTime = new QLabel();

    QSlider *slider = new QSlider(Qt::Horizontal);

    connect(player,&QMediaPlayer::durationChanged,slider,&QSlider::setMaximum);
    connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(getVideoDuration()));
    connect(player,&QMediaPlayer::positionChanged,slider,&QSlider::setValue);
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(getPlayingTime()));
    connect(player,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this,SLOT(replayPlayer()));
    connect(slider,&QSlider::sliderMoved,player,&QMediaPlayer::setPosition);
    connect(d_option,SIGNAL(rejected()),player,SLOT(stop()));

    l_duration = new QLabel("00:00:00");

    lo_v_control->addWidget(l_curTime);
    lo_v_control->addWidget(slider);
    lo_v_control->addWidget(l_duration);

    tb_play_pause = new QToolButton;
    tb_play_pause->setIcon(QIcon::fromTheme("player_pause"));
    connect(tb_play_pause,SIGNAL(clicked(bool)),this,SLOT(playPause()));

    QToolButton *tb_stop = new QToolButton;
    tb_stop->setIcon(QIcon::fromTheme("player_stop"));
    connect(tb_stop,SIGNAL(clicked(bool)),this,SLOT(stopPlayer()));

    tb_mute = new QToolButton;
    tb_mute->setIcon(QIcon::fromTheme("stock_volume-mute"));
    connect(tb_mute,SIGNAL(clicked(bool)),this,SLOT(muteSound()));

    QHBoxLayout *lo_btn = new QHBoxLayout;
    lo_btn->addWidget(tb_play_pause);
    lo_btn->addWidget(tb_stop);
    lo_btn->addWidget(tb_mute);

    QVBoxLayout *lo_left_top = new QVBoxLayout;
    lo_left_top->addWidget(vw);
    lo_left_top->addLayout(lo_v_control);
    lo_left_top->addLayout(lo_btn);

    QGroupBox *gr_left_top = new QGroupBox;
    gr_left_top->setLayout(lo_left_top);
    gr_left_top->setFixedWidth(500);
    gr_left_top->setStyleSheet("QGroupBox{border: 1px solid #ccc;border-radius:8px;margin-top:0.5em}");

    //left bottom

    QVBoxLayout *lo_left_bottom = new QVBoxLayout;

    QHBoxLayout *lo_pb_time = new QHBoxLayout;

    QPushButton *pb_start = new QPushButton("Start Time");
    pb_start->setFixedWidth(140);
    connect(pb_start,SIGNAL(clicked(bool)),this,SLOT(getStartTime()));

    QPushButton *pb_end = new QPushButton("End Time");
    pb_end->setFixedWidth(140);
    connect(pb_end,SIGNAL(clicked(bool)),this,SLOT(getEndTime()));

    lo_pb_time->addWidget(pb_start,0,Qt::AlignLeft);
    lo_pb_time->addWidget(pb_end,Qt::AlignRight);

    QHBoxLayout *lo_time_entry = new QHBoxLayout;

    QPushButton *pb_play_at_start = new QPushButton;
    pb_play_at_start->setFixedWidth(40);
    pb_play_at_start->setIcon(QIcon::fromTheme("stock_media-play"));
    connect(pb_play_at_start,SIGNAL(clicked(bool)),this,SLOT(jumpToStartTime()));

    le_start = new QLineEdit;
    le_start->setText("00:00:00");
    le_start->setFixedWidth(100);

    QPushButton *pb_plat_at_end = new QPushButton;
    pb_plat_at_end->setFixedWidth(40);
    pb_plat_at_end->setIcon(QIcon::fromTheme("stock_media-play"));
    connect(pb_plat_at_end,SIGNAL(clicked(bool)),this,SLOT(jumpToEndTime()));

    le_stop = new QLineEdit;
    le_stop ->setText("00:00:00");
    le_stop->setFixedWidth(100);

    lo_time_entry->addWidget(pb_play_at_start,Qt::AlignLeft);
    lo_time_entry->addWidget(le_start,0,Qt::AlignLeft);
    lo_time_entry->addWidget(pb_plat_at_end,Qt::AlignRight);
    lo_time_entry->addWidget(le_stop,Qt::AlignRight);
    lo_time_entry->setSpacing(0);

    lo_left_bottom->addLayout(lo_pb_time);
    lo_left_bottom->addLayout(lo_time_entry);

    QGroupBox *gr_left_bottom = new QGroupBox;
    gr_left_bottom->setLayout(lo_left_bottom);
    gr_left_bottom->setTitle("Set Range");
    gr_left_bottom->setStyleSheet("QGroupBox{border: 1px solid #ccc;border-radius:8px;margin-top:0.5em}"
                                  "QGroupBox::title{subcontrol-origin:margin;left:10px;padding: 0 3px 0 3px}");

    lo_left->addWidget(gr_left_top);
    lo_left->addWidget(gr_left_bottom);

    //right------------------------------------------------------------------
    QPushButton *pb_convert = new QPushButton("OK");
    pb_convert->setFixedWidth(140);
    connect(pb_convert,SIGNAL(clicked(bool)),this,SLOT(sendOptionValue()));

    QHBoxLayout *lo_crop = new QHBoxLayout();

    QCheckBox *cb_crop = new QCheckBox();
    cb_crop->setText("Crop");

    QLineEdit *le_crop = new QLineEdit();

    lo_crop->addWidget(cb_crop);
    lo_crop->addWidget(le_crop);

    QRadioButton *rb_default = new QRadioButton("Default");

    QRadioButton *rb_left = new QRadioButton("Left");

    QRadioButton *rb_right =new QRadioButton("Right");

    QVBoxLayout *lo_a_channel = new  QVBoxLayout();

    lo_a_channel->addWidget(rb_default);
    lo_a_channel->addWidget(rb_left);
    lo_a_channel->addWidget(rb_right);

    QGroupBox *gb_a_channel = new QGroupBox();
    gb_a_channel->setTitle("Source Audio Channel");
    gb_a_channel->setLayout(lo_a_channel);
    gb_a_channel->setStyleSheet("QGroupBox{border: 1px solid #ccc;border-radius:8px;margin-top:0.5em}"
                                "QGroupBox::title{subcontrol-origin:margin;left:10px;padding: 0 3px 0 3px}");

    QGroupBox *gr_audio = new QGroupBox;
    gr_audio->setTitle("Audio Stream");
    gr_audio->setStyleSheet("QGroupBox{border: 1px solid #ccc;border-radius:8px;margin-top:0.5em}"
                            "QGroupBox::title{subcontrol-origin:margin;left:10px;padding: 0 3px 0 3px}");

    QHBoxLayout *lo_a_stream = new QHBoxLayout;

    QTextEdit *te_a_stream = new QTextEdit;

    lo_a_stream->addWidget(te_a_stream);
    gr_audio->setLayout(lo_a_stream);

    QHBoxLayout *lo_subt_lang = new QHBoxLayout();

    QTextEdit *te_subt_lang = new QTextEdit();
    lo_subt_lang->addWidget(te_subt_lang);

    QGroupBox *gb_subt_lang = new  QGroupBox();
    gb_subt_lang->setTitle("Subtitle Language");
    gb_subt_lang->setLayout(lo_subt_lang);
    gb_subt_lang->setStyleSheet("QGroupBox{border: 1px solid #ccc;border-radius:8px;margin-top:0.5em}"
                                "QGroupBox::title{subcontrol-origin:margin;left:10px;padding: 0 3px 0 3px}");

    lo_right->addWidget(pb_convert,Qt::AlignRight);
    lo_right->addLayout(lo_crop);
    lo_right->addWidget(gb_a_channel);
    lo_right->addWidget(gr_audio);
    lo_right->addWidget(gb_subt_lang);

    lo_d_option->addLayout(lo_left);
    lo_d_option->addLayout(lo_right);

    d_option->setLayout(lo_d_option);
    d_option->setFixedSize(800,500);
    d_option->setWindowTitle(file);
    d_option->show();

}

void dialogConversion::getPlayingTime(){

    auto st = player->position();
    auto hour = (st/1000)/3600;
    auto minute = ((st/1000)%3600)/60;
    auto second = ((st/1000)%3600)%60;

    QTime waktu(hour,minute,second);
    l_curTime->setText(waktu.toString("HH:mm:ss"));

}

void dialogConversion::playPause(){

    if(player->state()==QMediaPlayer::PlayingState){
         tb_play_pause->setIcon(QIcon::fromTheme("player_play"));
         player->pause();

    }
    else{
        tb_play_pause->setIcon(QIcon::fromTheme("player_pause"));
        player->play();
    }
}

void dialogConversion::stopPlayer(){

    player->stop();
    tb_play_pause->setIcon(QIcon::fromTheme("player_play"));

}

void dialogConversion::muteSound(){

    if(!player->isMuted()){
        player->setMuted(true);
        tb_mute->setIcon(QIcon::fromTheme("stock_volume"));
    }
    else{

        player->setMuted(false);
        tb_mute->setIcon(QIcon::fromTheme("stock_volume-mute"));
    }
}

void dialogConversion::getStartTime(){

    vStartTime = player->position();
    auto hour = (vStartTime/1000)/3600;
    auto minute = ((vStartTime/1000)%3600)/60;
    auto second = ((vStartTime/1000)%3600)%60;

    QTime waktu(hour,minute,second);
    le_start->setText(waktu.toString("HH:mm:ss"));
}

void dialogConversion::getEndTime(){

    vEndTime = player->position();
    auto hour = (vEndTime /1000)/3600;
    auto minute = ((vEndTime/1000)%3600)/60;
    auto second = ((vEndTime/1000)%3600)%60;

    QTime endTime(hour,minute,second);
    le_stop->setText(endTime.toString("HH:mm:ss"));

}

void dialogConversion::getVideoDuration(){

    auto dur = player->duration();
    auto hour = (dur/1000)/3600;
    auto minute = ((dur/1000)%3600)/60;
    auto second = ((dur/1000)%3600)%60;

    QTime durationg(hour,minute,second);
    l_duration->setText(durationg.toString("HH:mm:ss"));
}

void dialogConversion::jumpToStartTime(){

    if(vStartTime!=0)
    player->setPosition(vStartTime);
}

void dialogConversion::jumpToEndTime(){

    if(vEndTime!=0)
      player->setPosition(vEndTime);

}

void dialogConversion::replayPlayer(){

    if(player->mediaStatus()==QMediaPlayer::EndOfMedia)
       player->play();

}

void dialogConversion::sendOptionValue(){

    auto dur = player->duration();
    auto hour = (dur/1000)/3600;
    auto minute = ((dur/1000)%3600)/60;
    auto second = ((dur/1000)%3600)%60;

    QTime xx(hour,minute,second);

    player->stop();
    if(vStartTime!=0 || vEndTime!=0){
        int crow = table_on_d_conv->currentRow();
        QTableWidgetItem *item_range = new QTableWidgetItem();


        if(vEndTime==0)
            item_range->setText(le_start->text()+"-"+xx.toString("HH:mm::ss"));
        else
            item_range->setText(le_start->text()+"-"+le_stop->text());


        item_range->setTextAlignment(Qt::AlignCenter);
        table_on_d_conv->setItem(crow,5,item_range);
    }

    vStartTime=0;
    vEndTime=0;

    d_option->accept();
}

void dialogConversion::appendName(bool a){

    append_name=a;
}

void dialogConversion::on_cbb_pict_param_changed(int x){
    switch (x) {
    case 0:
        cb_size_limit->setChecked(false);
        le_max_h->clear();
        le_max_w->clear();
        break;
    case 1:
        cb_size_limit->setChecked(true);
        le_max_w->setText("2400");
        le_max_h->setText("1800");
        break;

    case 2:
        cb_size_limit->setChecked(true);
        le_max_w->setText("1024");
        le_max_h->setText("768");
        break;

    case 3:
        cb_size_limit->setChecked(true);
        le_max_w->setText("640");
        le_max_h->setText("480");
        break;

    case 4:
        cb_size_limit->setChecked(true);
        le_max_w->setText("320");
        le_max_h->setText("240");
        break;

    case 5:
        cb_size_limit->setChecked(true);
        le_max_w->setText("176");
        le_max_h->setText("144");
        break;

    }
}
void dialogConversion::add_watermark(bool w){
    cbb_wm_position->setEnabled(w);
    cbb_wm_size->setEnabled(w);
    le_wm_margin->setEnabled(w);
    le_wm_file->setEnabled(w);
    btn_wm_browse->setEnabled(w);
}

void dialogConversion::getWatermarkPict(){

    QString wm_pict = QFileDialog::getOpenFileName(nullptr,"Pick Watermark file", QDir::homePath(),"*.png *.jpg *.webp *.ico *.gif *.bmp");
    if(!wm_pict.isEmpty()){
        le_wm_file->setText(wm_pict);
    }


}

void dialogConversion::on_cbb_ico_changed(int i){

    switch (i) {
    case 0:
        le_max_h->setText("16");
        le_max_w->setText("16");
        break;
    case 1:
        le_max_h->setText("32");
        le_max_w->setText("32");
        break;
    case 2:
        le_max_h->setText("48");
        le_max_w->setText("48");
        break;
    case 3:
        le_max_h->setText("64");
        le_max_w->setText("64");
        break;
    case 4:
        le_max_h->setText("128");
        le_max_w->setText("128");
        break;
    case 5:
        le_max_h->setText("256");
        le_max_w->setText("256");
        break;

    }

}

void dialogConversion::acceptDialogPict(){

    if(g_target_format=="jpg"){
        jpg_cur_text=cbb_pict_prmtr->currentText();
        jpg_limit_size=cb_size_limit->isChecked();

        jpg_max_heigth=le_max_h->text();
        jpg_max_width=le_max_w->text();

        jpg_rotate=cb_rotate->isChecked();
        jpg_angle=cbb_angle->currentText();

        jpg_insert_text=cb_insert_tag->isChecked();

        jpg_font=cfcb_font_chooser->currentText();
        jpg_text_pos=cbb_position->currentText();
        jpg_text_color=cbb_color->currentText();
        jpg_font_size=cbb_size->currentText();
        jpg_italic=cb_italic->isChecked();
        jpg_underline=cb_underline->isChecked();
        jpg_tag_string=le_string->text();

        jpg_insert_wm=cb_watermark->isChecked();
        jpg_wm_pos=cbb_wm_position->currentText();
        jpg_wm_size=cbb_wm_size->currentText();
        jpg_wm_file=le_wm_file->text();

    }
    else if(g_target_format=="png"){
        png_cur_text=cbb_pict_prmtr->currentText();
        png_limit_size=cb_size_limit->isChecked();

        png_max_heigth=le_max_h->text();
        png_max_width=le_max_w->text();

        png_rotate=cb_rotate->isChecked();
        png_angle=cbb_angle->currentText();

        png_insert_text=cb_insert_tag->isChecked();

        png_font=cfcb_font_chooser->currentText();
        png_text_pos=cbb_position->currentText();
        png_text_color=cbb_color->currentText();
        png_font_size=cbb_size->currentText();
        png_italic=cb_italic->isChecked();
        png_underline=cb_underline->isChecked();
        png_tag_string=le_string->text();

        png_insert_wm=cb_watermark->isChecked();
        png_wm_pos=cbb_wm_position->currentText();
        png_wm_size=cbb_wm_size->currentText();
        png_wm_file=le_wm_file->text();

    }

    else if(g_target_format=="ico"){
        ico_cur_text=cbb_pict_prmtr->currentText();
        ico_limit_size=cb_size_limit->isChecked();

        ico_max_heigth=le_max_h->text();
        ico_max_width=le_max_w->text();

        ico_rotate=cb_rotate->isChecked();
        ico_angle=cbb_angle->currentText();
        ico_insert_text=cb_insert_tag->isChecked();

        ico_font=cfcb_font_chooser->currentText();
        ico_text_pos=cbb_position->currentText();
        ico_text_color=cbb_color->currentText();
        ico_font_size=cbb_size->currentText();
        ico_italic=cb_italic->isChecked();
        ico_underline=cb_underline->isChecked();
        ico_tag_string=le_string->text();

        ico_insert_wm=cb_watermark->isChecked();
        ico_wm_pos=cbb_wm_position->currentText();
        ico_wm_size=cbb_wm_size->currentText();
        ico_wm_file=le_wm_file->text();

    }

    else if(g_target_format=="bmp"){
        bmp_cur_text=cbb_pict_prmtr->currentText();
        bmp_limit_size=cb_size_limit->isChecked();

        bmp_max_heigth=le_max_h->text();
        bmp_max_width=le_max_w->text();

        bmp_rotate=cb_rotate->isChecked();
        bmp_angle=cbb_angle->currentText();
        bmp_insert_text=cb_insert_tag->isChecked();

        bmp_font=cfcb_font_chooser->currentText();
        bmp_text_pos=cbb_position->currentText();
        bmp_text_color=cbb_color->currentText();
        bmp_font_size=cbb_size->currentText();
        bmp_italic=cb_italic->isChecked();
        bmp_underline=cb_underline->isChecked();
        bmp_tag_string=le_string->text();

        bmp_insert_wm=cb_watermark->isChecked();
        bmp_wm_pos=cbb_wm_position->currentText();
        bmp_wm_size=cbb_wm_size->currentText();
        bmp_wm_file=le_wm_file->text();

    }

    else if(g_target_format=="tif"){
        tif_cur_text=cbb_pict_prmtr->currentText();
        tif_limit_size=cb_size_limit->isChecked();

        tif_max_heigth=le_max_h->text();
        tif_max_width=le_max_w->text();

        tif_rotate=cb_rotate->isChecked();
        tif_angle=cbb_angle->currentText();
        tif_insert_text=cb_insert_tag->isChecked();

        tif_font=cfcb_font_chooser->currentText();
        tif_text_pos=cbb_position->currentText();
        tif_text_color=cbb_color->currentText();
        tif_font_size=cbb_size->currentText();
        tif_italic=cb_italic->isChecked();
        tif_underline=cb_underline->isChecked();
        tif_tag_string=le_string->text();

        tif_insert_wm=cb_watermark->isChecked();
        tif_wm_pos=cbb_wm_position->currentText();
        tif_wm_size=cbb_wm_size->currentText();
        tif_wm_file=le_wm_file->text();

    }

    else if(g_target_format=="pcx"){
        pcx_cur_text=cbb_pict_prmtr->currentText();
        pcx_limit_size=cb_size_limit->isChecked();

        pcx_max_heigth=le_max_h->text();
        pcx_max_width=le_max_w->text();

        pcx_rotate=cb_rotate->isChecked();
        pcx_angle=cbb_angle->currentText();
        pcx_insert_text=cb_insert_tag->isChecked();

        pcx_font=cfcb_font_chooser->currentText();
        pcx_text_pos=cbb_position->currentText();
        pcx_text_color=cbb_color->currentText();
        pcx_font_size=cbb_size->currentText();
        pcx_italic=cb_italic->isChecked();
        pcx_underline=cb_underline->isChecked();
        pcx_tag_string=le_string->text();

        pcx_insert_wm=cb_watermark->isChecked();
        pcx_wm_pos=cbb_wm_position->currentText();
        pcx_wm_size=cbb_wm_size->currentText();
        pcx_wm_file=le_wm_file->text();

    }

    else if(g_target_format=="tga"){
        tga_cur_text=cbb_pict_prmtr->currentText();
        tga_limit_size=cb_size_limit->isChecked();

        tga_max_heigth=le_max_h->text();
        tga_max_width=le_max_w->text();

        tga_rotate=cb_rotate->isChecked();
        tga_angle=cbb_angle->currentText();

        tga_insert_text=cb_insert_tag->isChecked();

        tga_font=cfcb_font_chooser->currentText();
        tga_text_pos=cbb_position->currentText();
        tga_text_color=cbb_color->currentText();
        tga_font_size=cbb_size->currentText();
        tga_italic=cb_italic->isChecked();
        tga_underline=cb_underline->isChecked();
        tga_tag_string=le_string->text();

        tga_insert_wm=cb_watermark->isChecked();
        tga_wm_pos=cbb_wm_position->currentText();
        tga_wm_size=cbb_wm_size->currentText();
        tga_wm_file=le_wm_file->text();

    }

    updateLabelQuality();

    dialog_pict->accept();

}
