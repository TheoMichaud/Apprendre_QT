#include "ModbusServer.h"

//Functions List

//01 (0x01) Read Coils
//02 (0x02) Read Discrete Inputs
//03 (0x03) Read Holding Registers
//04 (0x04) Read Input Registers
//05 (0x05) Write Single Coil
//06 (0x06) Write Single Register
//15 (0x0F) Write Multiple Coils
//16 (0x10) Write Multiple registers
//20 (0x14) Read File Record										(To Do)
//21 (0x15) Write File Record										(To Do)
//22 (0x16) Mask Write Register										(To Do)
//23 (0x17) Read/Write Multiple registers							(To test)
//24 (0x18) Read FIFO Queue											(To Do)
//43 (0x2B) Encapsulated Interface Transport						(To Do)

ModbusServer::ModbusServer()
{
    m_coils.fill(QVector <bool> (65536,false),1);
    m_discrete_inputs.fill(QVector <bool> (65536,false),1);
    m_hold_registers.fill(QVector <unsigned short> (65536,0),1);
    m_input_registers.fill(QVector <unsigned short> (65536,0),1);
}

ModbusServer::ModbusServer(int numberOfUnit)
{
	this->numberOfUnits = numberOfUnit;
    m_coils.fill(QVector <bool> (65536,false),numberOfUnit);
    m_discrete_inputs.fill(QVector <bool> (65536,false),numberOfUnit);
    m_hold_registers.fill(QVector <unsigned short> (65536,0),numberOfUnit);
    m_input_registers.fill(QVector <unsigned short> (65536,0),numberOfUnit);
}

ModbusFrame ModbusServer::giveRequest(ModbusFrame &requestFrame)
{
    ModbusFrame responseFrame(requestFrame);
	responseFrame.copyMobdbusHeader(requestFrame);

    int unitId = requestFrame.getUnitId();
    int referenceNumber = requestFrame.getReferenceNumber();
    int wordCount = requestFrame.getWordCount();

    QVector <QVariant> vVar(wordCount);
    QVector <bool> vBool;
    QVector <unsigned short> vUSint;
    unsigned short value;

	if (unitId > numberOfUnits)
    {
		responseFrame.setExceptionCode(ModbusFrame::SlaveDeviceFailure);
        return responseFrame;
    }

    switch(requestFrame.getFunctionCode())
    {
	case ModbusFrame::ReadCoils : //01 (0x01) Read Coils
		vBool = m_coils[unitId].mid(referenceNumber,wordCount);
		qCopy(vBool.begin(),vBool.end(),vVar.begin());
		for (int i = 0 ; i < vVar.size() ; i++)
			vVar[i].convert((QVariant::Type) QMetaType::Bool);
		responseFrame.setData(vVar);
		break;

	case ModbusFrame::ReadDiscreteInputs : //02 (0x02) Read Discrete Inputs
		vBool = m_discrete_inputs[unitId].mid(referenceNumber,wordCount);
		qCopy(vBool.begin(),vBool.end(),vVar.begin());
		for (int i = 0 ; i < vVar.size() ; i++)
			vVar[i].convert((QVariant::Type) QMetaType::Bool);
		responseFrame.setData(vVar);
		break;

	case ModbusFrame::ReadHoldingRegisters : //03 (0x03) Read Holding Registers
		vUSint = m_hold_registers[unitId].mid(referenceNumber,wordCount);
		qCopy(vUSint.begin(),vUSint.end(),vVar.begin());
		for (int i = 0 ; i < vVar.size() ; i++)
			vVar[i].convert((QVariant::Type) QMetaType::UShort);
		responseFrame.setData(vVar);
		break;

	case ModbusFrame::ReadInputRegisters : //04 (0x04) Read Input Registers
		vUSint = m_input_registers[unitId].mid(referenceNumber,wordCount);
		qCopy(vUSint.begin(),vUSint.end(),vVar.begin());
		for (int i = 0 ; i < vVar.size() ; i++)	
			vVar[i].convert((QVariant::Type) QMetaType::UShort);
		responseFrame.setData(vVar);
		break;

	case ModbusFrame::WriteSingleCoil : //05 (0x05) Write Single Coil
		value = (unsigned short) requestFrame.getData(QMetaType::UShort)[0].toUInt();
		if (value == 0xFF00 || value == 0)
		{
			if (value == 0xFF00) m_coils[unitId][referenceNumber] = true;
			else if (value == 0) m_coils[unitId][referenceNumber] = false;
			responseFrame.setReferenceNumber(requestFrame.getReferenceNumber());
			responseFrame.setWordCount(requestFrame.getWordCount());
		}
		else responseFrame.setExceptionCode(ModbusFrame::IllegalDataValue);
		break;

	case ModbusFrame::WriteSingleRegister : //06 (0x06) Write Single Register
		value = (unsigned short) requestFrame.getData(QMetaType::UShort)[0].toUInt();
		m_hold_registers[unitId][referenceNumber] = value;
		responseFrame.setReferenceNumber(requestFrame.getReferenceNumber());
		responseFrame.setWordCount(requestFrame.getWordCount());
		break;

	case ModbusFrame::WriteMultipleCoils : //15 (0x0F) Write Multiple Coils
		vVar = requestFrame.getData(QMetaType::Bool);
		for (int i = 0 ; i < vVar.size() ; i++)
			m_coils[unitId][referenceNumber+i] = vVar[i].toBool();
		responseFrame.setReferenceNumber(requestFrame.getReferenceNumber());
		responseFrame.setWordCount(requestFrame.getWordCount());
		break;

	case ModbusFrame::WriteMultipleRegisters : //16 (0x10) Write Multiple registers
		vVar = requestFrame.getData(QMetaType::UShort);
		for (int i = 0 ; i < vVar.size() ; i++)
			m_hold_registers[unitId][referenceNumber+i] = vVar[i].toUInt();
		responseFrame.setReferenceNumber(requestFrame.getReferenceNumber());
		responseFrame.setWordCount(requestFrame.getWordCount());
		break;

	case ModbusFrame::ReadWriteMultipleRegisters : //23 (0x17) Read/Write Multiple registers
		vUSint = m_hold_registers[unitId].mid(referenceNumber,wordCount);
		qCopy(vUSint.begin(),vUSint.end(),vVar.begin());
		responseFrame.setData(vVar);

		vVar = requestFrame.getData(QMetaType::UShort);
		referenceNumber = requestFrame.getReferenceNumber(2);
		for (int i = 0 ; i < vVar.size() ; i++)
			m_hold_registers[unitId][referenceNumber+i] = vVar[i].toUInt();
		break;
	default :  ;
    }
    return responseFrame;
}