#ifndef SERIAL_H
#define SERIAL_H

    #include <QStringList>
    #include<QTextStream>
    #include<QSerialPort>
    #include<QSerialPortInfo>

    class Serial {

    private :
        QSerialPort serialPort;
    public :
        Serial(){}

        Serial(QString serialPortName, QSerialPort::BaudRate serialPortBaudRate = QSerialPort::Baud9600,
            QSerialPort::StopBits serialPortStopBits = QSerialPort::OneStop, QSerialPort::Parity serialPortParity = QSerialPort::NoParity);

        virtual ~Serial();

        /** Writes a string of bytes to the serial port.
        *
        * @param buffer pointer to the buffer containing the bytes
        * @param buffLen the number of bytes in the buffer
        *
        * @return int the number of bytes written
        */
        qint64 write(const char *buffer, qint64 buffLen);

        /** Reads a string of bytes from the serial port.
         *
        * @param buffer pointer to the buffer to be written to
        * @param buffLen the size of the buffer
        * @param nullTerminate if set to true it will null terminate the string
        *
        * @return int the number of bytes read
        */

        qint64 read(char *buffer, qint64 buffLen, bool nullTerminate = false);

        /** Flushes everything from the serial port's read buffer
        */
        void flush();

        friend void availableSerialPorts();

    };

    void availableSerialPorts();

#endif // SERIAL_H
