#ifndef MYUART_H
#define MYUART_H
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QString>

class MyUART : public QObject
{
    Q_OBJECT

public:
    enum CRC16Type{
        unknown=0,
        crc16=1,
        crc16Modbus=2,
        crc16Sick=3,
        crc16ccittXModem=4,
        crc16ccitt0xFFFF=5,
        crc16ccitt0x1D0F=6,
        crc16ccittKermit=7,
        crcDNP=8
    };
    MyUART();
    MyUART(MyUART::CRC16Type crcType);
    int setUARTOpen();
    void setUARTClose();
    bool isUARTOpen();
    void write(QByteArray &ba);
    void write(QByteArray &ba, int msecs);
    void writeAndAppendCrc(QByteArray &ba);
    void writeAndAppendCrc(QByteArray &ba, int msecs);
    void write(QString &myString);
    void write(QString &myString, int msecs);
    void writeAndAppendCrc(QString &myString);
    void writeAndAppendCrc(QString &myString, int msecs);
    ~MyUART();

public slots:
    void sendAbortShutdown();
    void sendACK();
    void sendDetectSystem(bool updates);
    void sendBeginProcess();
    void sendBeginTransmittingData();
    void sendOrientationData(double currentLat,double currentLon,double currentAzi);
    void sendNACK();

signals:
    void errorShutdownSignal(int statusByte);
    void ackSignal(int statusByte);
    void statusSignal(int systemID, int statusByte);
    void reqOrientationDataSignal(int statusByte);
    void DataTransferSignal(int statusByte, QByteArray payload);
    void rxSignal(void);
    void txSignal(void);

private slots:
    void readyReadSlot();

private:
    void initCrcTable();
    unsigned short initCRC();
    unsigned short calcCRC(QByteArray &ba);
    bool checkCRC(QByteArray &ba);
    void appendCRC(QByteArray &ba);
    CRC16Type myCrcType;
    unsigned short crcTable[256];
    QSerialPort mySerialPort;
    bool saveLog;
    QString fileDir;
    void rxLog(QByteArray &Message);
    void txLog(QByteArray &Message);
    double cLat;
    double cLon;
    double cAzi;
    void dataLog(QByteArray &Payload);
    QString dataFileDirBase;
    QString dataFileDir;
    QByteArray dblToQBA(double input);
    double qbaToDBL(QByteArray &input);
};

#endif // MYUART_H
