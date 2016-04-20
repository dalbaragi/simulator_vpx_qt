#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QString>
#include <QHostAddress>
#include <QHostInfo>
#include <QtGlobal>
#include <QNetworkInterface>
#include <QAbstractSocket>
#include <QNetworkInterface>
#include <QTimer>
#include "simulator_gui.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void UdpInit();
    void CommunicationCheck();
    void SetNetworkInterface(QString);
    void SendSigParamFrame(void);
    void ScatPointImport();

//    void TargetTypeCheck();
//    void PowerTypeCheck();
//    void DistanceTypeCheck();

//    void AdapterListGet(void);
//    void AdapterChange(int index);
//    void SendFrame1();

//    void CalculateAndUpdate();


private:
    Ui::MainWindow *ui;
//    int SendCnt;
    char UdpInitFlag;
    QList<QNetworkInterface> NetworkInterfaceList;
    QUdpSocket *UdpSocket;
    QHostAddress Sender;
    quint16 SenderPort;

//    UdpFrame frame;
//    UdpFrame FrameRecv;
//    QTimer* timer;

//    float *ScatteringPointIndex[36][36];

//    float CalculatePower();
//    void CalculateCoordinateDistance();
//    void CalculateDirectDistance();
//    void PowerOverflowCheck();

//    void CalculatePointTargetScatteringPoint(float PowerParam);

//    void CalculatePointTargetScatteringPoint();

//    void CalculateSolidTargetScatteringPoint(float PowerParam);


};

//get 本地连接 ip address
//QString get_local_ip();




#endif // MAINWINDOW_H
