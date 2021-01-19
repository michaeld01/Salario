#include "principal.h"
#include "ui_principal.h"

#include <QDebug>

#include "calculosalario.h"
#include <QDir>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);

    connect(ui->action_Calcular,SIGNAL(triggered(bool)),
            this, SLOT(on_cmdCalcular_released()));
    connect(ui->action_Guardar,SIGNAL(triggered(bool)),
            this, SLOT(guardar()));
    connect(ui->action_Abrir,SIGNAL(triggered(bool)),
            this,SLOT(abrir()));
}

Principal::~Principal()
{
    delete ui;
}

void Principal::guardar()
{
    QString resultados = ui->outResultados->toPlainText();

    QString temporal = QDir::home().absolutePath() + "/sin_titulo.txt";
    qDebug() << temporal;

    // Abrir cuadro de dialogo para colocar el nombre del archivo
    QString nombreArchivo = QFileDialog::getSaveFileName(this, "Save File",
                                                         temporal,
                                                         "Archivo de texto(*.txt)");
    //Crear el objeto QFile
    QFile archivo(nombreArchivo);

    //Verificar si se puede escribir sobre el archivo
    if(archivo.open(QFile::WriteOnly | QFile::Truncate)){
        //Crear el objeto QTextStream
        QTextStream out(&archivo);
        //Escribiendo datos en el archico
        out << resultados << '\n';
        qDebug() << "Archivo almacenado en:" << nombreArchivo;
        //Cerrar archico
        archivo.close();
        QMessageBox guardado;
        guardado.setText("Archivo Guardado Exitosamente");
        guardado.exec();
    }
}

void Principal::abrir()
{
    QString nombre = QFileDialog::getOpenFileName(this, "Abrir archivo",
                                                  "c:/Ususarios", "config(*.txt)");
    QFile file(nombre);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QStringList datos;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString linea = in.readLine();
        datos << linea;
    }

    ui->outResultados->setPlainText(datos[0] + "\n" +
            datos[1] + "\n" +
            datos[2] + "\n" +
            datos[3] + "\n" +
            datos[4] + "\n");

    file.close();
}


void Principal::on_cmdCalcular_released()
{
    //Obtener datos de la UI
    QString nombre = this->ui->inNombre->text();
    int horas = this->ui->inHoras->value();
    char jornada = 'm';
    if(this->ui->inMatutino->isChecked()){
        jornada = 'm';
    }else if(this->ui->inVespertino->isChecked()){
        jornada = 'v';
    }else{
        jornada = 'n';
    }
    qDebug() << "Jornada:" << jornada;
    CalculoSalario rolPagos(nombre, horas, jornada);
    rolPagos.calcular();
    qDebug() << rolPagos.salario() << rolPagos.descuento() << rolPagos.salarioNeto();


    ui->outResultados->setPlainText( "Obrero: "+nombre +"\n"+
                                     "Salario: "+QString::number(rolPagos.salario()) +"\n"+
                                     "Descuento (9.5%): $"+QString::number(rolPagos.descuento()) +"\n"+
                                     "Salario Neto: $"+QString::number(rolPagos.salarioNeto()) + "\n"+
                                     "- - - - - - - - - - - - - - - - "+"\n");

    ui->inNombre->setText(NULL);
    ui->inHoras->setValue(NULL);
    ui->inMatutino->setChecked(1);
    ui->inNombre->hasFocus();
}


