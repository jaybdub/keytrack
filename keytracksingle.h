#ifndef KEYTRACKSINGLE_H
#define KEYTRACKSINGLE_H

#include <QMainWindow>
#include "keytrackserial.h"

namespace Ui {
class KeytrackSingle;
}

class KeytrackSingle : public QMainWindow
{
    Q_OBJECT

public:
    explicit KeytrackSingle(QWidget *parent = 0);
    ~KeytrackSingle();

private:
    Ui::KeytrackSingle *ui;
};

#endif // KEYTRACKSINGLE_H
