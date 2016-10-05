#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "about.h"
#include "preferences.h"
#include <QMainWindow>
#include <QApplication>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QDialog>
#include <QToolButton>
#include <QPushButton>
#include <QProgressBar>
#include <QComboBox>
#include <QTreeWidget>
#include <QSystemTrayIcon>
#include <QFontComboBox>
#include <QMessageBox>
#include <QElapsedTimer>

class danton : public QMainWindow
{
    Q_OBJECT

public:
    danton(QWidget *parent = 0);

private slots:
    void menuNtoolbar();
    void buildIcon(QToolButton *, const QString &, const QString &);
    void createCentralWidget();
    void buatStatusBar();
    void readSetting();
    void createCategoryBtn(QPushButton *, const QString &, const QString &);
    void buka_berkas_sumber();
    void on_btn_cat_video_clicked();
    void on_btn_cat_audio_clicked();
    void on_btn_cat_img_clicked();
    void on_btn_cat_cd_clicked();
    void on_btn_advance_clicked();
    void on_btnV_avi_clicked();
    void on_btnV_mp4_clicked();
    void on_btnV_3gp_clicked();
    void on_btnV_webm_clicked();
    void on_btnV_mkv_clicked();
    void on_btnV_gif_clicked();
    void on_btnV_wmv_clicked();
    void on_btnV_mpg_clicked();
    void on_btnV_vob_clicked();
    void on_btnV_mov_clicked();
    void on_btnV_flv_clicked();
    void on_btnV_swf_clicked();
    void on_btnA_mp3_clicked();
    void on_btnA_wma_clicked();
    void on_btnA_ape_clicked();
    void on_btnA_flac_clicked();
    void on_btnA_aac_clicked();
    void on_btnA_mmf_clicked();
    void on_btnA_amr_clicked();
    void on_btnA_m4a_clicked();
    void on_btnA_m4r_clicked();
    void on_btnA_ogg_clicked();
    void on_btnA_wav_clicked();
    void on_btnA_mp2_clicked();
    void on_btnP_webp_clicked();
    void on_btnP_jpg_clicked();
    void on_btnP_png_clicked();
    void on_btnP_ico_clicked();
    void on_btnP_bmp_clicked();
    void on_btnP_tif_clicked();
    void on_btnP_gif_clicked();
    void on_btnP_pcx_clicked();
    void on_btnP_tga_clicked();
    void on_btn_mediainfo_clicked();
    void onBtnCSOClicked();
    void output_dir();
    void createContentMainTable(QStringList file_list_);
    void deleteRowMainTable();
    void openFolderOutput();

    void onBtnStartClicked();
    void onStopBtnClicked();

    void clearMainTable();

    void mainProcess(int return_code);
    void readOutputProcess();

    void rightClickMenu(const QPoint &pos);
    void settingDialog();
    void showAbout();
    void receiveOutputFolder(QString g_output_folder);


    void image_conversion_output();

    void update_counter();

    void shutdown_status(bool);
    void receive_shutdown_status(bool );
    void receiveDeleteOriginal(bool);
    void receiveOverwrite(bool);
    void receiveSaveToSource(bool);
    void receiveAppend(bool);
    void receiveOpenFolder(bool);
    void receiveNotifySuccess(bool);
    void receiveNotifyError(bool);

    void showMessage(QString message);

    void update_error_count();

    void actionAfterConvert();

    void openDialogConv();
    void dvdToFile();
    void discToISO();
    void cdToFile();
    void timer();
    void closeEvent(QCloseEvent *);

private:
    bool sh_video=true;
    bool sh_audio=false;
    bool sh_pict=false;
    bool sh_disc=false;
    bool sh_advance=false;

    QAction *preference_action;
    QAction *pick_folder_action;
    QAction *stop_action;
    QAction *clear_list_action;
    QAction *start_action;
    QAction *delete_action;

     QLabel *lb_elapsedtime;

    QWidget *wg_ic_audio;
    QWidget *wg_ic_video;
    QWidget *wg_ic_image;
    QWidget *wg_ic_cd;
    QWidget *wg_ic_advance;

    QTableWidget *main_table;

    QProcess *proses_konversi;
    QProcess *image_conversion;

    QString g_input_file="";
    QString g_output_file="";

    QProgressBar *globpro;

    QCheckBox *cb_poweroff;
    QPushButton *output_text_btn;

    QElapsedTimer *elapsedtime;
     QLabel *lb_count;
     QLabel *lb_count_error;

//noty notyify;
    QSystemTrayIcon *trayIcon;
    QMenu *trayMenu;

};



#endif // MAINWINDOW_H
