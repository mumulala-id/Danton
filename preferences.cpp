#include "preferences.h"

#include <QSettings>
#include <QToolButton>
#include <QPushButton>
#include <QLabel>
#include <QDialogButtonBox>
#include <QDir>
#include <QFileDialog>
#include <QDebug>

preferences::preferences(QWidget *parent):
    QDialog(parent)
{

    readSetting();

    QVBoxLayout *layout_opsi = new QVBoxLayout;
    QHBoxLayout *layout_jendela_opsi = new QHBoxLayout;
    //menu iko vertikal
    QVBoxLayout *lo_mn_ic_v = new QVBoxLayout;
    lo_mn_ic_v->setAlignment(Qt::AlignTop);

    QSize x(60,60);
    QToolButton *btn_st_opsi = new QToolButton;
    btn_st_opsi->setText("Opsi");
    btn_st_opsi->setIcon(QIcon::fromTheme("stock_properties"));
    btn_st_opsi->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btn_st_opsi->setFixedSize(x);
    connect(btn_st_opsi, SIGNAL(clicked(bool)), this, SLOT(on_btn_st_opsi_clicked()));

    QToolButton *btn_st_subtitle = new QToolButton;
    btn_st_subtitle->setText(tr("Subtitle"));
    btn_st_subtitle->setIcon(QIcon::fromTheme("stock_properties"));
    btn_st_subtitle->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btn_st_subtitle->setFixedSize(x);
    connect(btn_st_subtitle, SIGNAL(clicked(bool)), this, SLOT(on_btn_st_subtitle_clicked()));

    QToolButton *btn_st_pict = new QToolButton;
    btn_st_pict->setText(tr("pict"));
    btn_st_pict->setIcon(QIcon::fromTheme("stock_properties"));
    btn_st_pict->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btn_st_pict->setFixedSize(x);
    connect(btn_st_pict, SIGNAL(clicked(bool)), this, SLOT(on_btn_st_pict_clicked()));

    QToolButton *btn_ops_h264 = new QToolButton;
    btn_ops_h264->setText(tr("H264"));
    btn_ops_h264->setIcon(QIcon::fromTheme("stock_properties"));
    btn_ops_h264->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btn_ops_h264->setFixedSize(x);

    QToolButton *btn_ops_mpeg4 = new QToolButton;
    btn_ops_mpeg4->setText(tr("MPEG4"));
    btn_ops_mpeg4->setIcon(QIcon::fromTheme("stock_properties"));
    btn_ops_mpeg4->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btn_ops_mpeg4->setFixedSize(x);

   /* QToolButton *btn_ops_divx = new QToolButton;
    btn_ops_divx->setText(tr("DivX"));
    btn_ops_divx->setIcon(QIcon::fromTheme("stock_properties"));
    btn_ops_divx->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btn_ops_divx->setFixedSize(x);
    btn_ops_divx->setStyleSheet("QToolButton{background-color:#ffffff;border:1px solid #cccccc; border-radius:4px;}"
                                      "QToolButton:hover{color:#ffffff;background:#0f61f5}");

    QToolButton *btn_ops_xvid = new QToolButton;
    btn_ops_xvid->setText(tr("Xvid"));
    btn_ops_xvid->setIcon(QIcon::fromTheme("stock_properties"));
    btn_ops_xvid->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btn_ops_xvid->setFixedSize(x);
    btn_ops_xvid->setStyleSheet("QToolButton{background-color:#ffffff;border:1px solid #cccccc; border-radius:4px;}"
                                      "QToolButton:hover{color:#ffffff;background:#0f61f5}");


    QToolButton *btn_ops_wmv2 = new QToolButton;
    btn_ops_wmv2->setText(tr("WMV2"));
    btn_ops_wmv2->setIcon(QIcon::fromTheme("stock_properties"));
    btn_ops_wmv2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btn_ops_wmv2->setFixedSize(x);
    btn_ops_wmv2->setStyleSheet("QToolButton{background-color:#ffffff;border:1px solid #cccccc; border-radius:4px;}"
                                      "QToolButton:hover{color:#ffffff;background:#0f61f5}");*/

    lo_mn_ic_v->addWidget(btn_st_opsi);
    lo_mn_ic_v->addWidget(btn_st_subtitle);
    lo_mn_ic_v->addWidget(btn_st_pict);
    lo_mn_ic_v->addWidget(btn_ops_mpeg4);
    lo_mn_ic_v->addWidget(btn_ops_h264);
    //lo_mn_ic_v->addWidget(btn_ops_divx);
    //lo_mn_ic_v->addWidget(btn_ops_xvid);
   // lo_mn_ic_v->addWidget(btn_ops_wmv2);

    // stacked layout

    QGroupBox *gr_stack_opt = new QGroupBox;
    gr_stack_opt->setTitle("Option");

    QHBoxLayout *lo_file = new QHBoxLayout;
    QGroupBox *group_file = new QGroupBox;

    cb_rm_source_file = new QCheckBox;
    cb_rm_source_file->setChecked(delete_original);
    cb_rm_source_file->setText("Delete original file");
    connect(cb_rm_source_file, SIGNAL(toggled(bool)),this,SLOT(on_cb_rm_source_file_checked(bool)));

    cb_overwrite_file = new QCheckBox;
    cb_overwrite_file->setChecked(overwrite_file);
    cb_overwrite_file->setText("Overwrite file");
    connect(cb_overwrite_file,SIGNAL(toggled(bool)),this,SLOT(on_cb_overwrite_file_checked(bool)));

    lo_file->addWidget(cb_rm_source_file);
    lo_file->addWidget(cb_overwrite_file);

    group_file->setLayout(lo_file);
    group_file->setTitle("File");
    group_file->setStyleSheet("QGroupBox{border: 1px solid #ccc;border-radius:8px;margin-top:0.5em}"
                              "QGroupBox::title{subcontrol-origin:margin;left:10px;padding: 0 3px 0 3px}");

    te_output = new QLineEdit;
    te_output->setText(g_output_path);

    QPushButton *pb_change_folder = new QPushButton(tr("Change Folder"));
    connect(pb_change_folder, SIGNAL(pressed()), this, SLOT(setOutpuFolder()));


    QHBoxLayout *lo_st_output_folder = new QHBoxLayout;
    lo_st_output_folder->addWidget(te_output);
    lo_st_output_folder->addWidget(pb_change_folder);

    QHBoxLayout *isi_stack_opsi_2 = new QHBoxLayout;

    cb_output = new QCheckBox;
    cb_output->setText(tr("Save output to source folder"));
    cb_output->setChecked(save_to_source);
    isi_stack_opsi_2->addWidget(cb_output);
    connect(cb_output, SIGNAL(toggled(bool)), this, SLOT(on_cb_output_checked(bool)));

    cb_append_name = new QCheckBox;
    cb_append_name->setText(tr("Append name setting(name.avi-> name[320x480].avi)"));
    cb_append_name->setChecked(append_name);
    connect(cb_append_name, SIGNAL(toggled(bool)),this,SLOT(status_append_name(bool)));


    QHBoxLayout *lo_append_name = new QHBoxLayout;
    lo_append_name->addWidget(cb_append_name);

    QVBoxLayout *lo_st_ops_output = new QVBoxLayout;
    lo_st_ops_output->setAlignment(Qt::AlignTop);
    lo_st_ops_output->addLayout(lo_st_output_folder);
    lo_st_ops_output->addLayout(isi_stack_opsi_2);
    lo_st_ops_output->addLayout(lo_append_name);

    QGroupBox *group_output =new QGroupBox;
    group_output->setLayout(lo_st_ops_output);
    group_output->setTitle("Output");
    group_output->setStyleSheet("QGroupBox{border: 1px solid #ccc;border-radius:8px;margin-top:0.5em}"
                                "QGroupBox::title{subcontrol-origin:margin;left:10px;padding: 0 3px 0 3px}");

    QGridLayout *lo_after_conv = new QGridLayout;
    cb_poweroff = new QCheckBox;
    cb_poweroff->setText(tr("Power off computer"));
    cb_poweroff->setChecked(poweroff_computer);
    connect(cb_poweroff,SIGNAL(toggled(bool)),this,SLOT(on_cb_poweroff_checked(bool)));

    cb_open_folder = new QCheckBox;
    cb_open_folder->setText(tr("Open folder"));
    cb_open_folder->setChecked(open_folder_at_finish);
    connect(cb_open_folder,SIGNAL(toggled(bool)),this,SLOT(on_cb_open_folder_checked(bool)));

    lo_after_conv->addWidget(cb_poweroff,0,0);
    lo_after_conv->addWidget(cb_open_folder,0,1);

    QGroupBox *group_finish = new QGroupBox;
    group_finish->setTitle("After conversion finish");
    group_finish->setLayout(lo_after_conv);
    group_finish->setStyleSheet("QGroupBox{border: 1px solid #ccc;border-radius:8px;margin-top:0.5em}"
                                "QGroupBox::title{subcontrol-origin:margin;left:10px;padding: 0 3px 0 3px}");

    cek_box_komplit = new QCheckBox;
    cek_box_komplit->setChecked(show_noty_succes);
    cek_box_komplit->setText(tr("Complete notify"));
    connect(cek_box_komplit, SIGNAL(toggled(bool)),this,SLOT(on_cb_complete_checked(bool)));

    cb_error = new QCheckBox;
    cb_error->setText(tr("error notify"));
    cb_error->setChecked(show_noty_error);
    connect(cb_error, SIGNAL(toggled(bool)),this, SLOT(on_cb_error_checked(bool)));

    QGridLayout *layout_notifikasi_suara = new QGridLayout;
    layout_notifikasi_suara->addWidget(cek_box_komplit,0,0);
    layout_notifikasi_suara->addWidget(cb_error,0,1);

    QGroupBox *group_notification = new QGroupBox;
    group_notification->setTitle("Notifications");
    group_notification->setLayout(layout_notifikasi_suara);
    group_notification->setStyleSheet("QGroupBox{border: 1px solid #ccc;border-radius:8px;margin-top:0.5em}"
                                      "QGroupBox::title{subcontrol-origin:margin;left:10px;padding: 0 3px 0 3px}");

    QVBoxLayout *lo_st_opsi = new QVBoxLayout;
    lo_st_opsi->addWidget(group_file);
    lo_st_opsi->addWidget(group_output);
    lo_st_opsi->addWidget(group_finish);
    lo_st_opsi->addWidget(group_notification);
    lo_st_opsi->setSpacing(30);
    lo_st_opsi->setAlignment(Qt::AlignTop);


    gr_stack_opt->setLayout(lo_st_opsi);

    QLabel *label_subtitle_font = new QLabel;
    label_subtitle_font->setText(tr("Subtitle font"));

    QVBoxLayout *lo_st_subtitle = new QVBoxLayout;
    lo_st_subtitle->setAlignment(Qt::AlignTop);
    lo_st_subtitle->setSpacing(30);
    lo_st_subtitle->addWidget(label_subtitle_font);


    QGroupBox *gr_stack_subt = new QGroupBox;
    gr_stack_subt->setLayout(lo_st_subtitle);
    gr_stack_subt->setTitle("Subtitle");


    //------------------------stack pict
    QLabel *l_img_quality = new QLabel;
    l_img_quality->setText(tr("Image quality"));

    le_img_quality = new QLineEdit;
    le_img_quality->setFixedWidth(40);
    le_img_quality->setText(QString::number(kualitas_gambar));
    le_img_quality->setReadOnly(true);
    le_img_quality->setAlignment(Qt::AlignCenter);

    QLabel *l_0 = new QLabel;
    l_0->setText("0");
    l_0->setAlignment(Qt::AlignRight);

    sd_quality = new QSlider(Qt::Horizontal);
    sd_quality->setFixedWidth(300);
    sd_quality->setRange(0,100);
    sd_quality->setValue(kualitas_gambar);

    connect(sd_quality, SIGNAL(valueChanged(int)), this , SLOT(img_quality_value(int)));


    QLabel *l_100 = new QLabel;
    l_100->setText("100");

    QGridLayout *lo_stack_pick = new QGridLayout;
    lo_stack_pick->addWidget(l_img_quality,0,0);
    lo_stack_pick->addWidget(le_img_quality,0,1);
    lo_stack_pick->addWidget(l_0,0,2);
    lo_stack_pick->addWidget(sd_quality,0,3);
    lo_stack_pick->addWidget(l_100,0,4);

    QVBoxLayout *lo_st_pict = new QVBoxLayout;
    lo_st_pict->setSpacing(30);

    lo_st_pict->addLayout(lo_stack_pick);
    lo_st_pict->setAlignment(Qt::AlignTop);

    QGroupBox *gr_stack_pict = new QGroupBox;
    gr_stack_pict->setLayout(lo_st_pict);
    gr_stack_pict->setTitle("Picture");

    stack = new QStackedLayout;
    stack->addWidget(gr_stack_opt);
    stack->addWidget(gr_stack_subt);
    stack->addWidget(gr_stack_pict);
    stack->setCurrentIndex(posisi_stack);

    QDialogButtonBox *box = new QDialogButtonBox( Qt::Horizontal );

    QPushButton *pb_cancel = new QPushButton("Cancel");
    connect(pb_cancel, SIGNAL(clicked(bool)),this,SLOT(close()));
    box->addButton(pb_cancel,QDialogButtonBox::RejectRole );

    QPushButton *pb_apply = new QPushButton("Apply");
    connect(pb_apply, SIGNAL(clicked(bool)),this,SLOT(close_n_apply()));
    box->addButton(pb_apply,QDialogButtonBox::ApplyRole );

    layout_jendela_opsi->addLayout(lo_mn_ic_v);
    layout_jendela_opsi->addLayout(stack);

    layout_opsi->addLayout(layout_jendela_opsi);
    layout_opsi->addWidget(box);

    setLayout(layout_opsi);
    setFixedSize(800,560);
    setWindowTitle(tr("Option"));

}
preferences::~preferences(){

}

void preferences::setOutpuFolder(){

   QString path = QFileDialog::getExistingDirectory(this,"Pick folder", QDir::homePath());

        if(!path.isEmpty()){

            g_output_path = path;

            te_output->setText(g_output_path);

         }

}

void preferences::on_cb_rm_source_file_checked(bool s)
{

        delete_original=s;
}

void preferences::on_cb_overwrite_file_checked(bool i)
{

         overwrite_file=i;

}

void preferences::on_cb_output_checked(bool c){

        save_to_source=c;
}

void preferences::on_cb_poweroff_checked(bool u)
{
    if(u){
        open_folder_at_finish=false;
        cb_open_folder->setChecked(false);
    }
        poweroff_computer=u;
}
void preferences::on_cb_open_folder_checked(bool x){
    if(x){
        poweroff_computer=false;
        cb_poweroff->setChecked(false);
       }

        open_folder_at_finish=x;

}

void preferences::on_cb_complete_checked(bool j)
{
        show_noty_succes=j;
}

void preferences::img_quality_value(int nilai)
{
    nilai = sd_quality->sliderPosition();
    le_img_quality->setText(QString::number(nilai));
    kualitas_gambar=nilai;
}

void preferences::on_btn_st_opsi_clicked()
{
    stack->setCurrentIndex(0);
}

void preferences::on_btn_st_subtitle_clicked()
{
    stack->setCurrentIndex(1);
}

void preferences::on_btn_st_pict_clicked()
{
    stack->setCurrentIndex(2);
}

void preferences::status_append_name(bool e){

    append_name=e;

}

void preferences::close_n_apply()
{
    QSettings setting("danton", "danton");
        setting.setValue("save_to_source", save_to_source);
        setting.setValue("kualitas_gambar", kualitas_gambar);
        setting.setValue("delete_original", delete_original);
        setting.setValue("overwrite_file", overwrite_file);
        setting.setValue("append_name",append_name);
        setting.setValue("poweroff_computer", poweroff_computer);
        setting.setValue("open_folder_at_finish", open_folder_at_finish);
        setting.setValue("show_noty_succes", show_noty_succes);
        setting.setValue("show_noty_error", show_noty_error);

        setting.setValue("posisi_stack", stack->currentIndex());
        setting.sync();

    emit send_new_output(g_output_path);
    emit send_delete_orginal(delete_original);
    emit send_overwrite(overwrite_file);
    emit send_save_to_source(save_to_source);
    emit send_append(append_name);
    emit send_shutdown_status(poweroff_computer);
    emit send_open_folder(open_folder_at_finish);
    emit send_notify_success(show_noty_succes);
    emit send_notify_error(show_noty_error);
    
    accept();
}

void preferences::on_cb_error_checked(bool h){

        show_noty_error=h;

}

void preferences::readSetting(){
    QSettings setting("danton", "danton");
    delete_original=setting.value("delete_original").toBool();
    overwrite_file=setting.value("overwrite_file").toBool();
    save_to_source=setting.value("save_to_source").toBool();
    append_name=setting.value("append_name").toBool();
    poweroff_computer=setting.value("poweroff_computer").toBool();
    open_folder_at_finish=setting.value("open_folder_at_finish").toBool();
    show_noty_succes=setting.value("show_noty_succes").toBool();
    show_noty_error=setting.value("show_noty_error").toBool();
    posisi_stack=setting.value("posisi_stack").toInt();
    kualitas_gambar=setting.value("kualitas_gambar").toInt();
}
