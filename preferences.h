#ifndef PREFERENCES
#define PREFERENCES

#include <QDialog>
#include <QCheckBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QStackedLayout>
#include <QSlider>

extern int kualitas_gambar;
extern QString g_output_path;

class preferences : public QDialog
{
    Q_OBJECT

public :
    explicit preferences(QWidget *parent = 0);
    ~preferences();

private :
    bool delete_original;
    bool overwrite_file;
    bool save_to_source;
    bool poweroff_computer;
    bool show_noty_succes;
    bool show_noty_error;
    bool append_name;
    bool open_folder_at_finish;
    int posisi_stack;
    int kualitas_gambar;
    QDialog *jendela_opsi;
    QCheckBox *cb_rm_source_file;
    QCheckBox *cb_overwrite_file;
    QLineEdit *te_output;
    QCheckBox *cb_output;
    QCheckBox *cb_error;
    QCheckBox *cek_box_komplit;
    QCheckBox *cb_poweroff;
    QLineEdit *le_img_quality;
    QStackedLayout *stack;
    QCheckBox *cb_append_name;
    QCheckBox *cb_open_folder;
    QSlider *sd_quality;

private Q_SLOTS :
    void on_cb_rm_source_file_checked(bool);
    void on_cb_overwrite_file_checked(bool);
    void on_cb_poweroff_checked(bool);
    void on_cb_open_folder_checked(bool);
    void on_cb_complete_checked(bool);
    void on_cb_error_checked(bool);
    void on_cb_output_checked(bool);
    void img_quality_value(int);
    void on_btn_st_opsi_clicked();
    void on_btn_st_subtitle_clicked();
    void on_btn_st_pict_clicked();

    void close_n_apply();
    void setOutpuFolder();
    void status_append_name(bool);
    void readSetting();

    
signals:
    void send_new_output(QString);
    void send_delete_orginal(bool);
    void send_overwrite(bool);
    void send_save_to_source(bool);
    void send_append(bool);
    void send_shutdown_status(bool);
    void send_open_folder(bool);
    void send_notify_success(bool);
    void send_notify_error(bool);

};

#endif // PREFERENCES

