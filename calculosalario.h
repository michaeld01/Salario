#ifndef CALCULOSALARIO_H
#define CALCULOSALARIO_H

#include <QObject>
//#include "principal.h"

class CalculoSalario : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float salario READ salario)
    Q_PROPERTY(float descuento READ descuento)
    Q_PROPERTY(float salarioNeto READ salarioNeto)
private:
    //CONSTANTE
    float const VALOR_HORA_MATUTINO     = 5.15;
    float const VALOR_HORA_VESPERTINO   = 8.50;
    float const VALOR_HORA_NOCTURNO     = 12.65;
    float const PORCENTAJE_DESCUENTO    = 9.5;
    //VARIABLES MIEMBRO
    int m_horas;                //Numero de horas trabajadas
    QString m_nombre;           //Nombre del trabajador
    char m_jornada;             //Jornada en la que trabaja (v=Vespertina, m=Matutina, n=Nocturno)
    float m_salario;            //Valor calculado del salario bruto
    float m_descuento;          //Valor calculado del descuento
    float m_salarioNeto;        //Valor calculado del salario bruto
public:
    explicit CalculoSalario(QObject *parent = nullptr);
    CalculoSalario(QString nombre, int horas, char jornada);
    void calcular();


    float descuento() const;
    float salarioNeto() const;
    float salario() const;

    QString nombre() const;

signals:

};

#endif // CALCULOSALARIO_H
