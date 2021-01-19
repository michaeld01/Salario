#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include "calculosalario.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Principal; }
QT_END_NAMESPACE

class Principal : public QMainWindow
{
    Q_OBJECT


public:
    Principal(QWidget *parent = nullptr);
    ~Principal();

    int total=0;


private slots:

    void on_cmdCalcular_released();
    void guardar();
    void abrir();


private:
    Ui::Principal *ui;
};
#endif // PRINCIPAL_H
