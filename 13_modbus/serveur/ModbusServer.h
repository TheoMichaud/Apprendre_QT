#ifndef MODBUSSERVER_H
#define MODBUSSERVER_H

/*--------------------------------------------------------------------------------------*/
/* 
 * File :		ModbusServer.h
 * Author :		Marc Fournier
 * Date :		01/07/10
 * Comment :	Modbus server class
 */
/*--------------------------------------------------------------------------------------*/

#include <QtCore>
#include <QtAlgorithms>
#include "ModbusFrame.h"

class ModbusServer
{
    public :
		ModbusServer();
		ModbusServer(int numberOfUnit);
		ModbusFrame giveRequest(ModbusFrame &modbusFrame);


    private:
		int numberOfUnits;

    /*-----------------Memory----------------*/
    QVector < QVector <bool> > m_coils;
    QVector < QVector <bool> > m_discrete_inputs;
    QVector < QVector <unsigned short> > m_hold_registers;
    QVector < QVector <unsigned short> > m_input_registers;

    /*QList < QList <bool> > ml_coils;
    QList < QList <bool> > ml_discrete_inputs;
    QList < QList <unsigned short> > ml_hold_registers;
    QList < QList <unsigned short> > ml_input_registers;*/
};




#endif // MODBUSSERVER_H
