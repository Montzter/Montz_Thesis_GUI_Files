#include "myuart.h"
#include <QDebug>
#include <iostream>
#include <QSettings>
#include <QDateTime>
#include <QTextStream>
#include <QFile>
#include <QBuffer>
#include <QDataStream>
#include <QElapsedTimer>
#include <QtCore>

MyUART::MyUART()
{

    myCrcType = crc16ccittXModem;
    initCrcTable();
    QObject::connect(&mySerialPort,SIGNAL(readyRead()),this,SLOT(readyReadSlot()));
    std::cout << "MyUART Connected";
}

MyUART::MyUART(MyUART::CRC16Type crcType)
{
    myCrcType = crcType;
    initCrcTable();
    QObject::connect(&mySerialPort,SIGNAL(readyRead()),this,SLOT(readyReadSlot()));
    std::cout << "MyUART Connected";
}

MyUART::~MyUART()
{

}

//Open mySerialPort
//return code:
//  0: no error
//  1: Port is busy
//  2: Port not found
//  3: Baudrate undefined
//  4: Data bits undefined
//  5: Parity undefined
//  6: Stop bits undefined
//  7: Flow control undefined
//  8: Error opening serialport

int MyUART::setUARTOpen()
{
    //load settings from registry
    QSettings tmpSettings("MontzThesis","GUISettingsFile");
    tmpSettings.beginGroup("Dialog");
    QVariant Port = tmpSettings.value("Port","COM1");
    QVariant BaudRate = tmpSettings.value("Baud Rate","115200");
    QVariant Data = tmpSettings.value("Data","8 bit");
    QVariant Parity = tmpSettings.value("Parity","none");
    QVariant Stop = tmpSettings.value("Stop","1 bit");
    QVariant FlowControl = tmpSettings.value("Flow Control","none");
    QVariant saveBool = tmpSettings.value("Save Log",false);
    QVariant saveDir = tmpSettings.value("Log Save Dir",".\\");
    QVariant dataSaveDir = tmpSettings.value("Image Save Dir",".\\");

    tmpSettings.endGroup();

    if(!QString::compare(saveBool.toString(),"true",Qt::CaseInsensitive))
    {
        saveLog = true;
    }
    else
    {
        saveLog = false;
    }

    fileDir = saveDir.toString();
    dataFileDirBase = dataSaveDir.toString();

    QString cDT = QDateTime::currentDateTime().toString("yyyy_MM_dd_HH-mm-ss");
    fileDir.append("/" + cDT + ".comLog");

    //Set myPort
    bool isFound = false;
    Q_FOREACH(QSerialPortInfo tmpPort, QSerialPortInfo::availablePorts())
    {
        if(!QString::compare(tmpPort.portName(),Port.toString(),Qt::CaseInsensitive))
        {
            isFound = true;
            if(tmpPort.isBusy())
            {
                return 1; //Port busy
            }
            else
            {
                mySerialPort.setPort(tmpPort);
            }
        }
    }
    if(isFound)
    {
        //Set myBaudRate
        switch(BaudRate.toInt())
        {
        case 110:
        case 300:
        case 600:
        case 1200:
        case 2400:
        case 4800:
        case 9600:
        case 14400:
        case 19200:
        case 38400:
        case 56000:
        case 57600:
        case 115200:
        case 128000:
        case 256000:
        case 460800:mySerialPort.setBaudRate(BaudRate.toInt());break;
        default: return 3;//Baudrate undefined
        }

        //Set myData
        switch(Data.toInt())
        {
            case 7:
            case 8: mySerialPort.setDataBits(static_cast<QSerialPort::DataBits>(Data.toInt())); break;
            default: return 4;//Databits undefined
        }

        //Set myParity
        if(!QString::compare(Parity.toString(),"none",Qt::CaseInsensitive))
            mySerialPort.setParity(QSerialPort::NoParity);
        else if(!QString::compare(Parity.toString(),"even",Qt::CaseInsensitive))
            mySerialPort.setParity(QSerialPort::EvenParity);
        else if(!QString::compare(Parity.toString(),"odd",Qt::CaseInsensitive))
            mySerialPort.setParity(QSerialPort::OddParity);
        else if(!QString::compare(Parity.toString(),"space",Qt::CaseInsensitive))
            mySerialPort.setParity(QSerialPort::SpaceParity);
        else if(!QString::compare(Parity.toString(),"mark",Qt::CaseInsensitive))
            mySerialPort.setParity(QSerialPort::MarkParity);
        else
            return 5;//Parity undefined

        //Set myStop
        if(!QString::compare(Stop.toString(),"1 bit",Qt::CaseInsensitive))
            mySerialPort.setStopBits(QSerialPort::OneStop);
        else if(!QString::compare(Stop.toString(),"1.5 bit",Qt::CaseInsensitive))
            mySerialPort.setStopBits(QSerialPort::OneAndHalfStop);
        else if(!QString::compare(Stop.toString(),"2 bit",Qt::CaseInsensitive))
            mySerialPort.setStopBits(QSerialPort::TwoStop);
        else
            return 6;//Stopbits undefined

        //Set myFlowControl
        if(!QString::compare(FlowControl.toString(),"none",Qt::CaseInsensitive))
            mySerialPort.setFlowControl(QSerialPort::NoFlowControl);
        else if(!QString::compare(FlowControl.toString(),"hardware",Qt::CaseInsensitive))
            mySerialPort.setFlowControl(QSerialPort::HardwareControl);
        else if(!QString::compare(FlowControl.toString(),"Xon/Xoff",Qt::CaseInsensitive))
            mySerialPort.setFlowControl(QSerialPort::SoftwareControl);
        else
            return 7;//Flow control undefined
    }
    else
    {
        return 2;// Port not found
    }

    if(!mySerialPort.open(QIODevice::ReadWrite))
        return 8;

    return 0;
}

//Close mySerialPort
void MyUART::setUARTClose()
{
    mySerialPort.close();
}

//Write
void MyUART::write(QByteArray &ba)
{
    mySerialPort.write(ba);
    txLog(ba);
}

//Write functions
void MyUART::write(QByteArray &ba, int msecs)
{
    mySerialPort.write(ba);
    txLog(ba);
    mySerialPort.waitForBytesWritten(msecs);
}

void MyUART::write(QString &myString)
{
    mySerialPort.write(myString.toLocal8Bit());
    txLog(myString.toLocal8Bit());
}

void MyUART::write(QString &myString, int msecs)
{
    mySerialPort.write(myString.toLocal8Bit());
    txLog(myString.toLocal8Bit());
    mySerialPort.waitForBytesWritten(msecs);
}

void MyUART::writeAndAppendCrc(QByteArray &ba)
{
    appendCRC(ba);
    mySerialPort.write(ba);
    txLog(ba);
}

void MyUART::writeAndAppendCrc(QByteArray &ba, int msecs)
{
    appendCRC(ba);
    mySerialPort.write(ba);
    txLog(ba);
    mySerialPort.waitForBytesWritten(msecs);
}

void MyUART::writeAndAppendCrc(QString &myString)
{
    QByteArray tmp(myString.toLatin1());
    appendCRC(tmp);
    myString.clear();
    myString=QString::fromLatin1(tmp);
    mySerialPort.write(tmp);
    txLog(tmp);
}

void MyUART::writeAndAppendCrc(QString &myString, int msecs)
{
    QByteArray tmp(myString.toLatin1());
    appendCRC(tmp);
    myString.clear();
    myString=QString::fromLatin1(tmp);
    mySerialPort.write(tmp);
    txLog(tmp);
    mySerialPort.waitForBytesWritten(msecs);
}

void MyUART::readyReadSlot()
{
    int rxLength = mySerialPort.bytesAvailable();

    QByteArray Message, Payload;
    if(rxLength < 8)
    {

        //Incomplete packet
        sendNACK();
        mySerialPort.clear();

    }
    else
    {
        Message.append(mySerialPort.read(8),8);

        if(Message.at(0) == 0x6E)
        {
            QByteArray tmpCRC = Message.mid(6,2);
            bool crcTest = checkCRC(Message);
            Message.append(tmpCRC);



            if(crcTest)
            {

                int statusByte = Message.at(1);
                int systemID = Message.at(2);
                int functionID = Message.at(3);
                int byteCount = Message.at(4) << 8;

                byteCount = byteCount + Message.at(5);
                //byteCount += 2;

                bool Payload_Integrity = true;
                if(byteCount == 0)//No data packet expected
                {

                }
                else if((byteCount > 0) && (mySerialPort.bytesAvailable() >= byteCount))
                {
                    //byteCount += 2;
                    Payload.append(mySerialPort.read(byteCount + 2));
                    bool PayloadCrcCheck = checkCRC(Payload);

                    if(!PayloadCrcCheck)
                    {
                        qDebug() << "Payload CRC error";
                        Payload_Integrity = false;

                    }
                }
                else
                {

                    Payload_Integrity = false;

                }

                if((byteCount > 0) && Payload_Integrity)
                {
                    Message.append(Payload);
                    dataLog(Payload);
                }

                rxLog(Message);
                if(!Payload_Integrity)
                    sendNACK();

                switch(functionID)
                {
                case 0: emit errorShutdownSignal(statusByte); break;
                case 1: emit ackSignal(statusByte); break;
                case 2: emit statusSignal(systemID, statusByte); break;
                case 3: emit reqOrientationDataSignal(statusByte); break;
                case 4: if(Payload_Integrity)emit DataTransferSignal(statusByte,Payload); break;
                default: break;
                }


            }
            else
            {
                qDebug() << "Error detected in CRC";
                sendNACK();
            }
        }
        else
        {
            qDebug() << "Invalid start byte";
        }
        mySerialPort.clear();
    }
}

void MyUART::initCrcTable()
{
    bool calculate, ccitt;
    int i, j;
    unsigned short crc, c, polyCoef;

    switch(myCrcType)
    {
    case crc16:
    case crc16Modbus:
        calculate = true; ccitt = false; polyCoef = 0xA001; break;
    case crc16ccittXModem:
    case crc16ccitt0xFFFF:
    case crc16ccitt0x1D0F:
        calculate = true; ccitt = true; break;
    case crc16ccittKermit:
        calculate = true; ccitt = false; polyCoef = 0x8408; break;
    case crcDNP:
        calculate = true; ccitt = false; polyCoef = 0xA6BC; break;
    case crc16Sick:
    case unknown:
    default: calculate = false; break;
    }

    if(calculate)
    {
        if(ccitt)
        {
            for(i = 0; i < 256; i++)
            {
                crc = 0;
                c = ((unsigned short) i) << 8;

                for(j = 0; j < 8; j++)
                {
                    if((crc ^ c) & 0x8000)
                        crc = (crc << 1) ^ 0x1021;
                    else
                        crc = crc << 1;

                    c = c << 1;
                }
                crcTable[i] = crc;
            }
        }
        else
        {
            for(i = 0; i < 256; i++)
            {
                crc = 0;
                c = (unsigned short) i;

                for(j = 0; j < 8; j++)
                {
                    if((crc ^ c) & 0x0001)
                        crc = (crc >> 1) ^ polyCoef;
                    else
                        crc = crc >> 1;

                    c = c >> 1;
                }

                crcTable[i] = crc;
            }
        }
    }

}

//Initialize the CRC value for a new message
unsigned short MyUART::initCRC()
{
    switch(myCrcType)
    {
    case crc16ccitt0x1D0F: return 0x1D0F;
    case crc16Modbus:
    case crc16ccitt0xFFFF: return 0xFFFF;
    case crc16:
    case crcDNP:
    case crc16Sick:
    case crc16ccittXModem:
    case crc16ccittKermit:
    default: return 0x0000;
    }
}

//Calculate CRC
//ba.size should be verified before this function call
unsigned short MyUART::calcCRC(QByteArray &ba)
{
    //return 0x0000 if ba is empty or NULL, appends 0x00 if not an even number of bytes.
    if(ba.isEmpty() || ba.isNull())
        return 0x0000;
    //I think this was in error, did not need to be an even number of bytes
    //else if((ba.size()%2))
    //    ba.append("\x00");

    //Determine which calculation path to take
    int calcPath;
    switch(myCrcType)
    {
    case crc16ccittXModem:
    case crc16ccitt0xFFFF:
    case crc16ccitt0x1D0F:
        calcPath = 1; break;
    case crc16Sick:
        calcPath = 2; break;
    case crc16:
    case crc16Modbus:
    case crc16ccittKermit:
    case crcDNP:
        calcPath = 3; break;
    case unknown:
    default: calcPath = 0; break;
    }



    //Calculate CRC value
    unsigned short crc = initCRC();
    if(calcPath == 1) //ccitt
    {
        int i;
        unsigned short tmp, short_c;

        for(i = 0; i < ba.size(); i++)
        {
            short_c = 0x00ff & (unsigned short) ba[i];
            tmp = (crc >> 8) ^ short_c;
            crc = (crc << 8) ^ crcTable[tmp];
        }
        return crc;
    }
    else if(calcPath == 2)//sick
    {
        int i;
        unsigned short short_c, short_p, low_byte, high_byte;

        QByteArray tempBa = ba;
        tempBa.prepend('\0');

        for(i = 1; i < tempBa.size(); i++)
        {
            short_c = 0x00ff & (unsigned short) tempBa[i];
            short_p = (0x00ff & (unsigned short) tempBa[i-1]) << 8;

            if (crc & 0x8000)
                crc = (crc << 1) ^ 0x8005;
            else
                crc = crc << 1;

            crc &= 0xffff; //why???
            crc ^= (short_c | short_p);
        }

        low_byte = (crc & 0xff00) >> 8;
        high_byte = (crc & 0x00ff) << 8;
        crc = low_byte | high_byte;
        return crc;
    }
    else if(calcPath == 3)//crc16,kermit,dnp
    {
        int i;
        unsigned short tmp, short_c, low_byte, high_byte;

        for(i = 0; i < ba.size(); i++)
        {
            short_c = 0x00ff & (unsigned short) ba[i];
            tmp = crc ^ short_c;
            crc = (crc >> 8) ^ crcTable[tmp & 0xff];
        }

        switch(myCrcType)
        {
        case crcDNP: crc = ~crc;
        case crc16ccittKermit:  low_byte = (crc & 0xff00) >> 8;
                                high_byte = (crc & 0x00ff) << 8;
                                crc = low_byte | high_byte;
        }
        return crc;
    }
    else//unknown
        return 0x0000;
}

//Verify CRC on QByteArray
bool MyUART::checkCRC(QByteArray &ba)
{
    QByteArray  tmp = ba;
    tmp.chop(2);
    unsigned short oldCrc = ((unsigned short)ba[ba.size() - 2] << 8) + ((unsigned short)ba[ba.size() -1] & 0x00ff);
    unsigned short crc = calcCRC(tmp);
    if(oldCrc == crc)
    {
        ba.chop(2);
        return true;
    }
    else
        return false;
}

//Append CRC to QByteArray
void MyUART::appendCRC(QByteArray &ba)
{
    unsigned short crc = calcCRC(ba);
    ba.append((crc & 0xff00) >> 8);
    ba.append(crc & 0x00ff);
}

//*************
//Public slots
//*************
void MyUART::sendAbortShutdown()
{
    QByteArray tmp("\x6E\x00\x00\x00\x00\x00\xDF\xBB",8);
    write(tmp,-1);
}

void MyUART::sendACK()
{
    QByteArray tmp("\x6E\x00\x00\x01\x00\x00\xE8\x8B",8);
    write(tmp,-1);
}

void MyUART::sendDetectSystem(bool updates)
{
    QByteArray tmp;
    if(updates)
        tmp.append("\x6E\xFF\x00\x02\x00\x00\xEB\x74",8);
    else
        tmp.append("\x6E\x00\x00\x02\x00\x00\xB1\xDB",8);

    write(tmp,-1);
}

void MyUART::sendBeginProcess()
{
    //QByteArray tmp("\x6E\x00\x00\x03\x00\x00\x86\xEB",8);

    QSettings tmpSettings("MontzThesis","GUISettingsFile");
    tmpSettings.beginGroup("Orientation");
    QVariant Delay = tmpSettings.value("Image Spacing Delay","255");
    tmpSettings.endGroup();

    QByteArray data;
    //QBuffer buffer(&data);
    //buffer.open(QIODevice::WriteOnly);
    QDataStream out(&data,QIODevice::WriteOnly);
    out << static_cast<qint8>(Delay.toInt());

    QByteArray tmp("\x6E",1);
    tmp.append(data,1);
    tmp.append("\x00\x03\x00\x00",4);

    appendCRC(tmp);

    write(tmp,-1);
}

void MyUART::sendBeginTransmittingData()
{
    QByteArray tmp("\x6E\x00\x00\x04\x00\x00\x03\x7B",8);
    write(tmp,-1);
}

void MyUART::sendOrientationData(double currentLat,double currentLon,double currentAzi)
{
    QByteArray tmp("\x6E\x00\x00\x05\x00\x18\xA7\x72",8);
    QByteArray tmpPayload;
    cLat = currentLat;
    cLon = currentLon;
    cAzi = currentAzi;

    //tmpPayload.append(reinterpret_cast<const char*>(&currentLat),sizeof(currentLat));
    tmpPayload.append(dblToQBA(currentLat));
    //tmpPayload.append(reinterpret_cast<const char*>(&currentLon),sizeof(currentLon));
    tmpPayload.append(dblToQBA(currentLon));
    //tmpPayload.append(reinterpret_cast<const char*>(&currentAzi),sizeof(currentAzi));
    tmpPayload.append(dblToQBA(currentAzi));


    appendCRC(tmpPayload);
    tmp.append(tmpPayload);
    write(tmp,-1);
}

void MyUART::sendNACK()
{
    QByteArray tmp("\x6E\x00\x00\xFF\x00\x00\x10\xDB",8);
    write(tmp,-1);
}

void MyUART::rxLog(QByteArray &Message)
{
    emit rxSignal();

    bool OK;

    if(saveLog)
    {
        QFile mFile(fileDir);
        if(!mFile.open(QFile::Append | QFile::Text))
        {
            return;
        }
        QTextStream out(&mFile);
        out << "[";
        out << QDateTime::currentDateTime().toString() << "]" << ",";
        out << "RX,    ";
        out << "Function:";

        int SystemID = Message.at(2);
        int Status = Message.at(1);

        switch(Message.at(3))
        {
        case 0: out << "Error Encountered/Shutdown,SystemID:" << SystemID << ",Status:" << Status; break;
        case 1: out << "ACK,SystemID:" << SystemID << ",Status:" << Status; break;
        case 2: out << "Status Update,SystemID:" << SystemID << ",Status:" << Status; break;
        case 3: out << "Request Orientation Data,SystemID:" << SystemID << ",Status:" << Status; break;
        case 4: out << "Data Transfer,SystemID:" << SystemID << ",Status:" << Status << ",Packet Number: " << Message.mid(8,2).toHex().toInt(&OK,10) << ",Total Packets: " << Message.mid(10,2).toHex().toInt(&OK,10); break;
        default: break;
        }
        out << "\n";
        //out << "Packet: " << Message.toHex() << "\n";
        mFile.close();
    }
    return;
}

void MyUART::txLog(QByteArray &Message)
{
    emit txSignal();
    if(saveLog)
    {
        QFile mFile(fileDir);
        if(!mFile.open(QFile::Append | QFile::Text))
        {
            return;
        }
        QTextStream out(&mFile);
        out << "[";
        out << QDateTime::currentDateTime().toString() << "]" <<",";
        out << "TX,";
        out << "Function:";


        switch(Message.at(3))
        {
        case 0: out << "Abort/Shutdown"; break;
        case 1: out << "ACK"; break;
        case 2: out << "Detect System,Status Updates:"; if((unsigned char)Message.at(1) == 0xFF) out << "yes"; else out << "no"; break;
        case 3: out << "Begin Process"; break;
        case 4: out << "Begin Transmitting Data"; break;
        case 5:
        {
            out << "Orientation Data,Current Latitude:" << cLat;
            out << ",Current Longitude:" << cLon;
            out << ",Current Azimuth:" << cAzi ;
            break;
        }
        case -1: out << "NACK";break;
        default: break;
        }
        out << "\n";
        //out << "Packet: " << Message.toHex() << "\n";
        mFile.close();
    }
    return;
}


void MyUART::dataLog(QByteArray &Payload)
{
    bool OK;
    QByteArray tmp;

    tmp = Payload.left(2).toHex();

    int packetNumber = tmp.toInt(&OK,16);


    if(packetNumber == 1)//Payload.at(2) == 1)//first packet in new data file
    {
        QString cDT = QDateTime::currentDateTime().toString("yyyy_MM_dd_HH-mm-ss");
        dataFileDir.clear();
        dataFileDir.append(dataFileDirBase + "/" + cDT + ".imgdata");
    }

    QFile mFile(dataFileDir);
    if(!mFile.open(QFile::Append | QFile::Text))
    {
        return;
    }

    QTextStream out(&mFile);

    if(packetNumber < 15)
        out << Payload.right(Payload.length()- 4) << "\n";
    else
        out << Payload.right(Payload.length()- 4).toHex() << "\n";


    //out << Payload.toHex() << "\n";
    //out << Payload.toHex() << "\n";
    mFile.close();
    return;
}

bool MyUART::isUARTOpen()
{
    return mySerialPort.isOpen();
}

QByteArray MyUART::dblToQBA(double input)
{
    QByteArray tmp;
    double absInput;
    absInput = abs(input);

    tmp.clear();
    if(input >= 0)
        tmp.append('+');
    else
        tmp.append('-');

    if(absInput < 100)
        tmp.append('0');

    if(absInput < 10)
        tmp.append('0');

    tmp.append(QByteArray::number(absInput,'f',3));

    return tmp;
}

double MyUART::qbaToDBL(QByteArray &input)
{
    double tmp = 0.0;
    bool OK;
    tmp = input.toDouble(&OK);
    if(!OK)
        tmp = 0.0;
    return tmp;
}
