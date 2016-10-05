
#ifndef DIALOGCONVERSION_H
#define DIALOGCONVERSION_H

#include <QDialog>
#include <QLabel>
#include <QToolButton>
#include <QTableWidget>
#include <QComboBox>
#include <QPushButton>
#include <QProcess>
#include <QTextEdit>
#include <QCheckBox>
#include <QFontComboBox>
#include <QTreeWidget>
#include <QDirIterator>
#include <QMediaPlayer>

class dialogConversion : public QDialog
{
    Q_OBJECT
public:
   explicit dialogConversion(QWidget *parent=0);


public slots:
       void dialog_pict_setting();
       void list_to_save(const QString &);
       void video_output_dialog_setting();
       void chooseFiles();
       void playFile();
       void clearTable();
       void onBtnDeleteClicked();
       void getMediaInfo();
       void appendName(bool);
       int getMediaType(const QString &);

      void on_cbb_parameter_mp4_changed(int);
      void on_cbb_parameter_avi_changed(int);
      void on_cbb_parameter_3gp_changed(int);
      void on_cbb_parameter_webm_changed(int);
      void on_cbb_parameter_mkv_changed(int);
      void on_cbb_parameter_wmv_changed(int);
      void on_cbb_parameter_mpg_changed(int);
      void on_cbb_parameter_vob_changed(int);
      void on_cbb_parameter_mov_changed(int);
      void on_cbb_parameter_flv_changed(int);
      void on_cbb_parameter_swf_changed(int);
      void on_cbb_parameter_mp3_changed(int);
      void on_cbb_parameter_wma_changed(int);
      void on_cbb_parameter_flac_changed(int);
      void on_cbb_parameter_aac_changed(int);
      void on_cbb_parameter_mmf_changed(int);
      void on_cbb_parameter_amr_changed(int);
      void on_cbb_parameter_m4a_changed(int);
      void on_cbb_parameter_m4r_changed(int);
      void on_cbb_parameter_ogg_changed(int);
      void on_cbb_parameter_wav_changed(int);
      void on_cbb_parameter_mp2_changed(int);
      void on_cbb_pict_param_changed(int);
      void on_cbb_ico_changed(int);
     // void on_cbb_angle_jpg_changed(int);
      void acceptDialogPict();


      void audio_output_dialog_setting();
      void cso_output_dialog_setting();
      void outputDir();
      void comboOutputFolder(int);
      void createTableContents(const QStringList &files_list);

      void updateLabelQuality();
      void loadFromFolder();
     // void closeEvent(QCloseEvent *);


      //output setting pict
      void size_limit_img(bool);
      void rotate_img(bool);
      void insert_tag_img(bool);
      void add_watermark(bool);
      void getWatermarkPict();
      void saveParameter();
      void insertSpecialItem(QComboBox *, const QString &);
      void sendToMainTable();


      void loadFromSetting();

      void selectFolder();
      void filterFromFolder();
      void entireSubDir(bool);
      QDirIterator::IteratorFlag ent() const { return entireSubDir_; }
      QString subLoad(QString, const QString &, const QString &);
      void getParameter(const QString &, QString *);
      static float getDuration(QString);
      static QString getVideoSize(QString);
      void setComboValue(QComboBox *, const QString &);

      void getWatermarkFile();
      QString getWatermarkParam(QString, QString *);
      void audioChannelValueConvert();
      void changeValueCompress();
      void saveValueCompress();

      //option dialog
      void dialogOption();
      void getPlayingTime();
      void playPause();
      void muteSound();
      void stopPlayer();
      void getStartTime();
      void getEndTime();
      void getVideoDuration();
      void jumpToStartTime();
      void jumpToEndTime();
      void replayPlayer();
      void sendOptionValue();

private :
      QDirIterator::IteratorFlag entireSubDir_;
      QTreeWidget *output_setting_table;

      QDialog *d_output_setting;
      QDialog *dialog_pict;



     QString last_dir;
     QLabel *l_quality;
     QToolButton *tb_play_file;
     QToolButton *tb_delete_item;
     QToolButton *tb_clear_list;
     QToolButton *tb_mediainfo;
     QTableWidget *table_on_d_conv;
     QComboBox *cbb_output_path;
     QPushButton *pb_option_on_d_conv;
     QPushButton *pb_ok;
     QComboBox *cbb_parameter;
     QComboBox *cbb_v_encoder;
     QComboBox *cbb_v_bitrate;
     QComboBox *cbb_v_fps;
     QComboBox *cbb_a_encoder;
     QComboBox *cbb_a_srate;
     QComboBox *cbb_a_bitrate;
     QComboBox *cbb_v_ratio;
     QComboBox *cbb_a_channel;
     QComboBox *cbb_v_size;

     QComboBox *cbb_volume_ctr;

     //output setting pict
     QComboBox *cbb_pict_prmtr;
     QCheckBox *cb_size_limit;
     QLineEdit *le_max_w;
     QLineEdit *le_max_h;
     QCheckBox *cb_rotate;
     QComboBox *cbb_angle;
     QFontComboBox *cfcb_font_chooser;
     QCheckBox *cb_insert_tag;
     QComboBox *cbb_position;
     QComboBox *cbb_color;
     QLineEdit *le_margin;
     QComboBox *cbb_size;
     QCheckBox *cb_italic;
     QCheckBox *cb_underline;
     QLineEdit *le_string;
      QCheckBox *cb_watermark;
     QComboBox *cbb_wm_position;
     QLineEdit *le_wm_margin;
      QComboBox *cbb_wm_size;
      QLineEdit *le_wm_file;
      QPushButton *btn_wm_browse;


     QString mp4_v_encoder;
     QString mp4_v_size;
     QString mp4_v_bitrate;
     QString mp4_v_fps;
     QString mp4_v_ratio;
     QString mp4_a_encoder;
     QString mp4_a_a_srate;
     QString mp4_a_bitrate;
     QString mp4_a_channel;
     QString avi_v_encoder;
     QString avi_v_size;
     QString avi_v_bitrate;
     QString avi_v_fps_avi;
     QString avi_v_ratio;
     QString avi_a_encoder;
     QString avi_a_a_srate;
     QString avi_a_bitrate;
     QString avi_a_channel;
     QString _3gp_v_encoder;
     QString _3gp_v_size;
     QString _3gp_v_bitrate;
     QString _3gp_v_fps;
     QString _3gp_v_ratio;
     QString _3gp_a_encoder;
     QString _3gp_a_a_srate;
     QString _3gp_a_bitrate;
     QString _3gp_a_channel;
     QString mkv_v_encoder;
     QString mkv_v_size;
     QString mkv_v_bitrate;
     QString mkv_v_fps;
     QString mkv_v_ratio;
     QString mkv_a_encoder;
     QString mkv_a_a_srate;
     QString mkv_a_bitrate;
     QString mkv_a_channel;
     QString wmv_v_encoder;
     QString wmv_v_size;
     QString wmv_v_bitrate;
     QString wmv_v_fps;
     QString wmv_v_ratio;
     QString wmv_a_encoder;
     QString wmv_a_a_srate;
     QString wmv_a_bitrate;
     QString wmv_a_channel;
     QString mpg_v_encoder;
     QString mpg_v_size;
     QString mpg_v_bitrate;
     QString mpg_v_fps;
     QString mpg_v_ratio;
     QString mpg_a_encoder;
     QString mpg_a_a_srate;
     QString mpg_a_bitrate;
     QString mpg_a_channel;
     QString vob_v_encoder;
     QString vob_v_size;
     QString vob_v_bitrate;
     QString vob_v_fps;
     QString vob_v_ratio;
     QString vob_a_encoder;
     QString vob_a_a_srate;
     QString vob_a_bitrate;
     QString vob_a_channel;
     QString mov_v_encoder;
     QString mov_v_size;
     QString mov_v_bitrate;
     QString mov_v_fps;
     QString mov_v_ratio;
     QString mov_a_encoder;
     QString mov_a_a_srate;
     QString mov_a_bitrate;
     QString mov_a_channel;
     QString flv_v_encoder;
     QString flv_v_size;
     QString flv_v_bitrate;
     QString flv_v_fps;
     QString flv_v_ratio;
     QString flv_a_encoder;
     QString flv_a_a_srate;
     QString flv_a_bitrate;
     QString flv_a_channel;
     QString swf_v_encoder;
     QString swf_v_size;
     QString swf_v_bitrate;
     QString swf_v_fps;
     QString swf_v_ratio;
     QString swf_a_encoder;
     QString swf_a_a_srate;
     QString swf_a_bitrate;
     QString swf_a_channel;
     QString mp4_quality;
     QString avi_quality;
     QString _3gp_quality;
     QString webm_quality;
     QString mkv_quality;
     QString gif_quality;
     QString wmv_quality;
     QString mpg_quality;
     QString vob_quality;
     QString mov_quality;
     QString flv_quality;
     QString swf_quality;
     QString mp3_quality;
     QString wma_quality;
     QString ape_quality;
     QString flac_quality;
     QString aac_quality;
     QString mmf_quality;
     QString m4a_quality;
     QString m4r_quality;
     QString amr_quality;
     QString ogg_quality;
     QString wav_quality;
     QString mp2_quality;


     QString mp3_a_bitrate;
     QString mp3_a_srate;
     QString mp3_a_channel;

     QString wma_a_bitrate;
     QString wma_a_srate;
     QString wma_a_channel;

     QString ape_a_bitrate;
     QString ape_a_srate;
     QString ape_a_channel;

     QString flac_a_bitrate;
     QString flac_a_srate;
     QString flac_a_channel;

     QString aac_a_bitrate;
     QString aac_a_srate;
     QString aac_a_channel;

     QString mmf_a_bitrate;
     QString mmf_a_srate;
     QString mmf_a_channel;

     QString m4a_a_bitrate;
     QString m4a_a_srate;
     QString m4a_a_channel;

     QString m4r_a_bitrate;
     QString m4r_a_srate;
     QString m4r_a_channel;

     QString amr_a_bitrate;
     QString amr_a_srate;
     QString amr_a_channel;

     QString ogg_a_bitrate;
     QString ogg_a_srate;
     QString ogg_a_channel;

     QString wav_a_bitrate;
     QString wav_a_srate;
     QString wav_a_channel;

     QString mp2_a_bitrate;
     QString mp2_a_srate;
     QString mp2_a_channel;

//pict



     QLineEdit *le_f_name;
     QLineEdit *le_filter;
     QCheckBox *cb_e;
     QDialog *d_recursive;

     QPushButton *pb_wt;

     QStringList additionalFolderList;
     QSlider *sd_cso;

     QLabel *lb_value_compress;

     //option dialog
     QDialog *d_option;
     QMediaPlayer *player ;
     QToolButton *tb_play_pause;
     QToolButton *tb_mute;
     QLineEdit *le_start;
     QLineEdit *le_stop;
     QLabel *l_duration;
     QLabel *l_curTime;
     qint64 vStartTime=0;
     qint64 vEndTime=0;

     //wm //watermark
     bool mp4_wm=false;
     QString mp4_wm_file="";

     bool avi_wm=false;
     QString avi_wm_file="";

signals :
     void sendtToTable(QStringList);
     void sendFileList(QStringList);
     void sendOutputFolder(QString);

};

#endif // DIALOGCONVERSION_H
