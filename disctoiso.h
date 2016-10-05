#ifndef DISCTOISO_H
#define DISCTOISO_H

#include <QDialog>
#include <QComboBox>

class disctoiso : public QDialog
{
    Q_OBJECT

public:
    explicit disctoiso(QWidget *parent=0);
public slots:
    void getMountedDrive();
    void ejectDrive();
private :
    QComboBox *cbb_driver;
};

#endif // DISCTOISO_H
