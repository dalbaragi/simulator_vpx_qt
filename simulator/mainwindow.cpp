#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <QMessageBox>
#include <QPixmap>
#include <QPalette>
#include <stdio.h>
#include <QTimer>
#include <QFile>
#include <String>
#include <stdlib.h>

using std::string;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //-----------initialize the UI default state----------
    ui->setupUi(this);
    //手动模式发送
    connect(ui->ManualSendPushButton, SIGNAL(clicked()), this, SLOT(SendSigParamFrame()));
    //网口初始化
    connect(ui->EthernetInitPushButton, SIGNAL(clicked()), this, SLOT(UdpInit()));
    //建立通信
    connect(ui->ConnectBuildPushButton, SIGNAL(clicked()), this, SLOT(CommunicationCheck()));
    //导入散射点
    connect(ui->ScatPointImportPushButton, SIGNAL(clicked()), this, SLOT(ScatPointImport()));

    //UDP初始化
    UdpInit();
    UdpSocket = new QUdpSocket(this);

    //---------界面初始化-------------
    ui->NoisePowerLineEdit->setText("-30");
    //手动模式，目标参数，
    //方式0
    ui->SpeedTranLineEditType0->setText("100");
    ui->SpeedRecvLineEditType0->setText("200");
    ui->PowerLineEditType0->setText("-20");
    ui->DistanceTranLineEditType0->setText("1000");
    ui->DistanceRecvLineEditType0->setText("2000");
    ui->ThetaLineEditType0->setText("10");
    ui->PhiLineEditType0->setText("20");
    //方式1
    ui->SpeedTranLineEditType1->setText("100");
    ui->SpeedRecvLineEditType1->setText("200");
    ui->DistanceTranLineEditType1->setText("1000");
    ui->DistanceRecvLineEditType1->setText("2000");
    ui->ThetaLineEditType1->setText("10");
    ui->PhiLineEditType1->setText("20");
    ui->PtLineEditType1->setText("10");
    ui->GLineEditType1->setText("10");
    ui->AeLineEditType1->setText("10");
    ui->TargetCoordinateThetaLineEditType1->setText("45");
    ui->TargetCoordinatePhiLineEditType1->setText("30");
    //干扰参数，间歇采样转发，方式0
    ui->IsrjDistanceLineEditType0->setText("1");
    ui->IsrjSpeedLineEditType0->setText("2");
    ui->IsrjThetaLineEditType0->setText("3");
    ui->IsrjPhiLineEditType0->setText("4");
    ui->IsrjPowerLineEditType0->setText("5");
    ui->IsrjSampleWidthLineEditType0->setText("6");
    ui->IsrjRepeatWidthLineEditType0->setText("7");
    ui->IsrjRepeatStartLineEditType0->setText("8");
    ui->IsrjRepeatNumLineEditType0->setText("9");
//    ui->TargetSpeed->setText("2");
//    ui->TargetAngleTheta->setText("3");
//    ui->TargetAnglePhi->setText("4");
//    ui->GroundToTargetAnglePhi->setText("0");
//    ui->GroundToTargetAngleTheta->setText("0");
//    ui->GroundToTargetAngleGamma->setText("0");
//    ui->GroundToRadarAnglePhi->setText("0");
//    ui->GroundToRadarAngleTheta->setText("0");
//    ui->GroundToRadarAngleGamma->setText("0");
//    ui->TargetPower->setText("0.5");
//    ui->Pt->setText("48");
//    ui->G->setText("1");
//    ui->Ae->setText("1");
//    ui->Rcs->setText("1");
//    ui->TargetDistance->setText("1");
//    ui->TransmitRadarX->setText("1");
//    ui->TransmitRadarY->setText("2");
//    ui->TransmitRadarZ->setText("3");
//    ui->TargetX->setText("4");
//    ui->TargetY->setText("5");
//    ui->TargetZ->setText("6");
//    ui->ReceiveRadarX->setText("7");
//    ui->ReceiveRadarY->setText("8");
//    ui->ReceiveRadarZ->setText("9");
//    ui->TargetDistanceTransmit->setText("1000");
//    ui->TargetDistanceReceive->setText("1000");
//    ui->AreaTransmit->setReadOnly(1);
//    ui->AreaReceive->setReadOnly(1);
//    ui->TargetDistance->setReadOnly(1);
//    ui->TargetDistanceTransmitCal->setReadOnly(1);
//    ui->TargetDistanceReceiveCal->setReadOnly(1);
//    ui->SolidTargetTextEdit->setReadOnly(1);
//    ui->TargetDistanceCal->setReadOnly(1);
//    ui->PointTargetTypeRadioButton->toggle();
//    ui->PowerDirectRadioButton->toggle();
//    ui->DistanceDirectRadioButton->toggle();
//    //ISRJ Jamming.
//    ui->IsrjJammingDistance->setText("0");
//    ui->IsrjJammingSpeed->setText("0");
//    ui->IsrjJammingAngleTheta->setText("0");
//    ui->IsrjJammingAnglePhi->setText("0");
//    ui->IsrjJammingPower->setText("0");
//    ui->IsrjSampleTimeWidth->setText("0");
//    ui->IsrjRepeatTimeWidth->setText("0");
//    ui->IsrjRepeatStartTime->setText("0");
//    ui->IsrjRepeatNum->setText("0");
//    TargetTypeCheck();
//    PowerTypeCheck();
//    DistanceTypeCheck();


}

MainWindow::~MainWindow()
{
    delete ui;
}

//网口初始化
void MainWindow::UdpInit()
{
    //create socket, bind the socket to 本地连接, must insert net line to the PC
    Sender = QHostAddress("192.168.1.100");
    SenderPort = 45454;

    //obtain all network interface information
    NetworkInterfaceList = QNetworkInterface::allInterfaces();
    //traversal each network inter
    ui->EthernetComboBox->clear();
    foreach(QNetworkInterface interface, NetworkInterfaceList)
    {
        //update combo box
        ui->EthernetComboBox->addItem(interface.humanReadableName());
    }

    UdpInitFlag = 1;
}

//选定网络接口
void MainWindow::SetNetworkInterface(QString InterfaceName)
{
    bool tmp;
    if(UdpInitFlag == 1)
    {
        foreach(QNetworkInterface interface, NetworkInterfaceList)
        {
            //device name
            if(interface.humanReadableName() == InterfaceName)
            {
                qDebug() << "Device name: " << interface.humanReadableName();
                QList<QNetworkAddressEntry> entryList = interface.addressEntries();
                //obtain ip list, traversal
                foreach(QNetworkAddressEntry entry,entryList)
                {
                    if(entry.ip().protocol() == QAbstractSocket::IPv4Protocol) //find ipv4 address
                    {
                        qDebug()<<"”IP Address: “"<<entry.ip().toString();
                        //Closes the I/O device for the socket
                        UdpSocket->close();
                        tmp = UdpSocket->bind(QHostAddress(entry.ip().toString()), SenderPort);
                        qDebug("%d", tmp);
                    }
                }
            }
        }
    }
}

//通信检测
void MainWindow::CommunicationCheck(void)
{
    QTimer  Timer;
    char    UdpSendTmp[11] = {0x01, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99};
    UdpSocket->writeDatagram(UdpSendTmp, sizeof(UdpSendTmp), Sender, SenderPort);
    //记时1秒
    Timer.start(1000);
    //等待接收回传
    while(Timer.remainingTime() > 0)
    {
        if(UdpSocket->hasPendingDatagrams())
        {
            QByteArray RecvData;
            RecvData.resize(UdpSocket->pendingDatagramSize());
            QHostAddress RecvSender;
            quint16 RecvSenderPort;
            //接收数据
            UdpSocket->readDatagram(RecvData.data(), RecvData.size(), &RecvSender, &RecvSenderPort);
            //监测IP和端口
            if((RecvSender.toIPv4Address() == Sender.toIPv4Address())&&(RecvSenderPort == SenderPort))
            {
                if(memcmp(UdpSendTmp, RecvData.data(),RecvData.size()) == 0)
                {
                    break;
                }
                else
                {
                    QMessageBox::about(this, "错误", "网口建立通信错误！");
                    break;
                }
            }
        }
    }

    if(Timer.remainingTime() == 0)
    {
        QMessageBox::about(this, "错误", "接收回传超时！");
    }
}


//导入散射点
void MainWindow::ScatPointImport()
{
    QTimer  Timer;
    int i = 0;
    ScatteringPointUdpFrame     ScatteringPointUdpFrameData;
    ScatteringPointUdpFrameData.FrameId = SCATTERING_POINT_INPUT;
    ScatteringPointUdpFrameData.ScatteringPointData.PointNum = 0;

    //读入文件
    QString CurrentFile = ui->ScatTypeComboBox->currentText();
    CurrentFile = "../simulator/" + CurrentFile + ".txt";

    QFile file(CurrentFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while (!file.atEnd()) {
        QString line = file.readLine();
        QStringList LineList = line.split(" ");
        ScatteringPointUdpFrameData.ScatteringPointData.PointData[i].X = LineList.at(0).toFloat();
        ScatteringPointUdpFrameData.ScatteringPointData.PointData[i].Y = LineList.at(1).toFloat();
        ScatteringPointUdpFrameData.ScatteringPointData.PointData[i].Z = LineList.at(2).toFloat();
        ScatteringPointUdpFrameData.ScatteringPointData.PointData[i].RCS = LineList.at(3).toFloat();\
        ++i;
        ++ScatteringPointUdpFrameData.ScatteringPointData.PointNum;
    }

    file.close();

    //网口发送
    UdpSocket->writeDatagram((char*)&ScatteringPointUdpFrameData,
                             sizeof(ScatteringPointUdpFrameData) - sizeof(Point)*(1024 - ScatteringPointUdpFrameData.ScatteringPointData.PointNum),
                             Sender,
                             SenderPort);


    //记时1秒
    Timer.start(1000);
    //等待接收回传
    while(Timer.remainingTime() > 0)
    {
        if(UdpSocket->hasPendingDatagrams())
        {
            QByteArray RecvData;
            RecvData.resize(UdpSocket->pendingDatagramSize());
            QHostAddress RecvSender;
            quint16 RecvSenderPort;
            //接收数据
            UdpSocket->readDatagram(RecvData.data(), RecvData.size(), &RecvSender, &RecvSenderPort);
            //监测IP和端口
            if((RecvSender.toIPv4Address() == Sender.toIPv4Address())&&(RecvSenderPort == SenderPort))
            {
                if(*RecvData.data() != 0x01)
                {
                    QMessageBox::about(this, "错误", "散射点导入错误！");
                }
                break;
            }
        }
    }

    if(Timer.remainingTime() == 0)
    {
        QMessageBox::about(this, "错误", "接收回传超时！");
    }
}


//发送参数
void MainWindow::SendSigParamFrame()
{
    char        FrameId = 0x06;
    char        TargetType;\
    char        JammingType;
    QByteArray  UdpFrameBeSend;
    UdpFrameBeSend.append(FrameId);
    QTimer      Timer;
    float       NoisePower;

    WorkParamUdpFrame    UdpFrameData;   //将要发送的数据


    //---目标参数---
    UdpFrameData.FrameId = WORK_PARAM_SET;          //工作参数设定帧
    UdpFrameData.TargetFrameId = MANUAL_MODE << 4;    //手动模式
    //噪声
    UdpFrameData.NoisePower = ui->NoisePowerLineEdit->text().toFloat();
    //UdpFrameBeSend.append((char*/*)(&NoisePower), sizeof(float));*/
    //点目标
    if(ui->TargetParamTypeTab->currentIndex() == 0)
    {
        PointTargetParam PointTargetParamTmp;
        PointTargetParamTmp.TranSpeed       = ui->SpeedTranLineEditType0->text().toFloat();
        PointTargetParamTmp.RecvSpeed       = ui->SpeedRecvLineEditType0->text().toFloat();
        PointTargetParamTmp.Power           = ui->PowerLineEditType0->text().toFloat();
        PointTargetParamTmp.TranDistance    = ui->DistanceTranLineEditType0->text().toFloat();
        PointTargetParamTmp.RecvDistance    = ui->DistanceRecvLineEditType0->text().toFloat();
        PointTargetParamTmp.TargetTheta     = ui->ThetaLineEditType0->text().toFloat();
        PointTargetParamTmp.TargetPhi       = ui->PhiLineEditType0->text().toFloat();
        UdpFrameData.TargetFrameId          |= POINT_TARGET;
        memcpy(&UdpFrameData.TargetFrame, &PointTargetParamTmp, sizeof(UdpFrameData.TargetFrame));
    }
    //扩展目标参数0
    else if(ui->TargetParamTypeTab->currentIndex() == 1)
    {
        RangeSpreadTargetParam0 RangeSpreadTargetParam0Tmp;
        RangeSpreadTargetParam0Tmp.TargetSpeedTran      = ui->SpeedTranLineEditType1->text().toFloat();
        RangeSpreadTargetParam0Tmp.TargetSpeedRecv      = ui->SpeedRecvLineEditType1->text().toFloat();
        RangeSpreadTargetParam0Tmp.TargetDistanceTran   = ui->DistanceTranLineEditType1->text().toFloat();
        RangeSpreadTargetParam0Tmp.TargetDistanceRecv   = ui->DistanceRecvLineEditType1->text().toFloat();
        RangeSpreadTargetParam0Tmp.TargetTheta          = ui->ThetaLineEditType1->text().toFloat();
        RangeSpreadTargetParam0Tmp.TargetPhi            = ui->PhiLineEditType1->text().toFloat();
        RangeSpreadTargetParam0Tmp.TargetPt             = ui->PtLineEditType1->text().toFloat();
        RangeSpreadTargetParam0Tmp.TargetG              = ui->GLineEditType1->text().toFloat();
        RangeSpreadTargetParam0Tmp.TargetAe             = ui->AeLineEditType1->text().toFloat();
        RangeSpreadTargetParam0Tmp.TargetAttitudeTheta  = ui->TargetCoordinateThetaLineEditType1->text().toFloat();
        RangeSpreadTargetParam0Tmp.TargetAttitudePhi    = ui->TargetCoordinatePhiLineEditType1->text().toFloat();
        UdpFrameData.TargetFrameId                      |= RANGE_SPREAD_TARGET_0;
        memcpy(&UdpFrameData.TargetFrame, &RangeSpreadTargetParam0Tmp, sizeof(UdpFrameData.TargetFrame));
    }
    //扩展目标参数1
    else if(ui->TargetParamTypeTab->currentIndex() == 2)
    {
        RangeSpreadTargetParam1 RangeSpreadTargetParam1Tmp;
        RangeSpreadTargetParam1Tmp.TargetSpeedTran                  = ui->SpeedTranLineEditType2->text().toFloat();
        RangeSpreadTargetParam1Tmp.TargetSpeedRecv                  = ui->SpeedRecvLineEditType2->text().toFloat();
        RangeSpreadTargetParam1Tmp.TargetPt                         = ui->PtLineEditType2->text().toFloat();
        RangeSpreadTargetParam1Tmp.TargetG                          = ui->GLineEditType2->text().toFloat();
        RangeSpreadTargetParam1Tmp.TargetAe                         = ui->AeLineEditType2->text().toFloat();
        RangeSpreadTargetParam1Tmp.GroundCoordRadarTranX            = ui->GroundRadarTransXLineEditType2->text().toFloat();
        RangeSpreadTargetParam1Tmp.GroundCoordRadarTranY            = ui->GroundRadarTransYLineEditType2->text().toFloat();
        RangeSpreadTargetParam1Tmp.GroundCoordRadarTranZ            = ui->GroundRadarTransZLineEditType2->text().toFloat();
        RangeSpreadTargetParam1Tmp.GroundCoordTargetX               = ui->GroundTargetXLineEditType2->text().toFloat();
        RangeSpreadTargetParam1Tmp.GroundCoordTargetY               = ui->GroundTargetYLineEditType2->text().toFloat();
        RangeSpreadTargetParam1Tmp.GroundCoordTargetZ               = ui->GroundTargetZLineEditType2->text().toFloat();
        RangeSpreadTargetParam1Tmp.GroundCoordRadarRecvX            = ui->GroundRadarRecvXLineEditType2->text().toFloat();
        RangeSpreadTargetParam1Tmp.GroundCoordRadarRecvY            = ui->GroundRadarRecvYLineEditType2->text().toFloat();
        RangeSpreadTargetParam1Tmp.GroundCoordRadarRecvZ            = ui->GroundRadarRecvZLineEditType2->text().toFloat();
        RangeSpreadTargetParam1Tmp.GroundCoordToRadarCoordAngleX    = ui->GroundToRadarXLineEditType2->text().toFloat();
        RangeSpreadTargetParam1Tmp.GroundCoordToRadarCoordAngleY    = ui->GroundToRadarYLineEditType2->text().toFloat();
        RangeSpreadTargetParam1Tmp.GroundCoordToRadarCoordAngleZ    = ui->GroundToRadarZLineEditType2->text().toFloat();
        RangeSpreadTargetParam1Tmp.GroundCoordToTargetCoordAngleX   = ui->GroundToTargetXLineEditType2->text().toFloat();
        RangeSpreadTargetParam1Tmp.GroundCoordToTargetCoordAngleY   = ui->GroundToTargetYLineEditType2->text().toFloat();
        RangeSpreadTargetParam1Tmp.GroundCoordToTargetCoordAngleZ   = ui->GroundToTargetZLineEditType2->text().toFloat();
        UdpFrameData.TargetFrameId                                  |= RANGE_SPREAD_TARGET_1;
        memcpy(&UdpFrameData.TargetFrame, &RangeSpreadTargetParam1Tmp, sizeof(UdpFrameData.TargetFrame));
    }
    //扩展目标参数2
    else if(ui->TargetParamTypeTab->currentIndex() == 3)
    {
        RangeSpreadTargetParam2 RangeSpreadTargetParam2Tmp;
        RangeSpreadTargetParam2Tmp.TargetFrameId            = 0x03;
        RangeSpreadTargetParam2Tmp.TargetSpeedTran          = ui->SpeedTranLineEditType3->text().toFloat();
        RangeSpreadTargetParam2Tmp.TargetSpeedRecv          = ui->SpeedRecvLineEditType3->text().toFloat();
        RangeSpreadTargetParam2Tmp.TargetPt                 = ui->PtLineEditType3->text().toFloat();
        RangeSpreadTargetParam2Tmp.TargetG                  = ui->GLineEditType3->text().toFloat();
        RangeSpreadTargetParam2Tmp.TargetAe                 = ui->AeLineEditType3->text().toFloat();
        RangeSpreadTargetParam2Tmp.GroundCoordRadarTranX    = ui->GroundRadarTransXLineEditType3->text().toFloat();
        RangeSpreadTargetParam2Tmp.GroundCoordRadarTranY    = ui->GroundRadarTransYLineEditType3->text().toFloat();
        RangeSpreadTargetParam2Tmp.GroundCoordRadarTranZ    = ui->GroundRadarTransZLineEditType3->text().toFloat();
        RangeSpreadTargetParam2Tmp.GroundCoordTargetX       = ui->GroundTargetXLineEditType3->text().toFloat();
        RangeSpreadTargetParam2Tmp.GroundCoordTargetY       = ui->GroundTargetYLineEditType3->text().toFloat();
        RangeSpreadTargetParam2Tmp.GroundCoordTargetZ       = ui->GroundTargetZLineEditType3->text().toFloat();
        RangeSpreadTargetParam2Tmp.GroundCoordRadarRecvX    = ui->GroundRadarRecvXLineEditType3->text().toFloat();
        RangeSpreadTargetParam2Tmp.GroundCoordRadarRecvY    = ui->GroundRadarRecvYLineEditType3->text().toFloat();
        RangeSpreadTargetParam2Tmp.GroundCoordRadarRecvZ    = ui->GroundRadarRecvZLineEditType3->text().toFloat();
        RangeSpreadTargetParam2Tmp.RadarCoordOxVectorX      = ui->RadarAxisXCoordinateXLineEditType3->text().toFloat();
        RangeSpreadTargetParam2Tmp.RadarCoordOxVectorY      = ui->RadarAxisXCoordinateYLineEditType3->text().toFloat();
        RangeSpreadTargetParam2Tmp.RadarCoordOxVectorZ      = ui->RadarAxisXCoordinateZLineEditType3->text().toFloat();
        RangeSpreadTargetParam2Tmp.RadarCoordOyVectorX      = ui->RadarAxisYCoordinateXLineEditType3->text().toFloat();
        RangeSpreadTargetParam2Tmp.RadarCoordOyVectorY      = ui->RadarAxisYCoordinateYLineEditType3->text().toFloat();
        RangeSpreadTargetParam2Tmp.RadarCoordOyVectorZ      = ui->RadarAxisYCoordinateZLineEditType3->text().toFloat();
        RangeSpreadTargetParam2Tmp.TargetCoordOxVectorX     = ui->TargetAxisXCoordinateXLineEditType3->text().toFloat();
        RangeSpreadTargetParam2Tmp.TargetCoordOxVectorY     = ui->TargetAxisXCoordinateYLineEditType3->text().toFloat();
        RangeSpreadTargetParam2Tmp.TargetCoordOxVectorZ     = ui->TargetAxisXCoordinateZLineEditType3->text().toFloat();
        RangeSpreadTargetParam2Tmp.TargetCoordOyVectorX     = ui->TargetAxisYCoordinateXLineEditType3->text().toFloat();
        RangeSpreadTargetParam2Tmp.TargetCoordOyVectorY     = ui->TargetAxisYCoordinateYLineEditType3->text().toFloat();
        RangeSpreadTargetParam2Tmp.TargetCoordOyVectorZ     = ui->TargetAxisYCoordinateZLineEditType3->text().toFloat();
        UdpFrameData.TargetFrameId                          |= RANGE_SPREAD_TARGET_2;
        memcpy(&UdpFrameData.TargetFrame, &RangeSpreadTargetParam2Tmp, sizeof(UdpFrameData.TargetFrame));
    }

    //---干扰参数---
    //无干扰
    if(ui->JammingTypeTab->currentIndex() == 0)
    {
        UdpFrameData.JammingFrameId = NO_JAMMING;
    }
    //间歇采样转发式干扰
    else if(ui->JammingTypeTab->currentIndex() == 1)
    {       
        //参数0
        if(ui->IsrjTab->currentIndex() == 0)
        {
            JammingIsrjParam0 JammingIsrjParam0Tmp;

            UdpFrameData.JammingFrameId = ISRJ_0;
        }
        //参数1
        else if(ui->IsrjTab->currentIndex() == 1){}
        //参数2
        else if(ui->IsrjTab->currentIndex() == 2){}
    }

    //网口发送
    UdpSocket->writeDatagram((char*)&UdpFrameData, sizeof(WorkParamUdpFrame), Sender, SenderPort);

    //记时1秒
    Timer.start(1000);
    //等待接收回传
    if((UdpFrameData.FrameId>>4 == MANUAL_MODE) ||
       (UdpFrameData.FrameId>>4 == AUTO_MODE_PASS_BACK))
    {
        while(Timer.remainingTime() > 0)
        {
            if(UdpSocket->hasPendingDatagrams())
            {
                WorkParamSetBack WorkParamSetBackData;
                QHostAddress RecvSender;
                quint16 RecvSenderPort;
                //接收数据
                UdpSocket->readDatagram((char*)&WorkParamSetBackData, sizeof(WorkParamSetBackData), &RecvSender, &RecvSenderPort);
                //监测IP和端口
                if((RecvSender.toIPv4Address() == Sender.toIPv4Address())&&(RecvSenderPort == SenderPort))
                {
                    //目标回传
                    if(WorkParamSetBackData.TargetFrameId == POINT_TARGET)
                    {
                        if(WorkParamSetBackData.TargetParamBack.PointTargetBack != 0x01)
                        {
                            QMessageBox::about(this, "错误", "目标参数0，回传出错！");
                        }
                    }
                    else if(WorkParamSetBackData.TargetFrameId == RANGE_SPREAD_TARGET_0)
                    {
//                        if(*RecvData.data() != 0x01)
//                        {
//                            QMessageBox::about(this, "错误", "目标参数0，回传出错！");
//                        }
                    }
                    //干扰回传
                    //无干扰
                    if(JammingType == NO_JAMMING)
                    {
                        if(WorkParamSetBackData.JammingParamBack.NoJammingBack != 0x01)
                        {
                            QMessageBox::about(this, "错误", "无干扰，回传出错！");
                        }
                    }
                    //间歇采样转发
                    else if(JammingType == ISRJ_0)
                    {

                    }
                    else if(JammingType == ISRJ_1)
                    {

                    }
                    else if(JammingType == ISRJ_2)
                    {

                    }
                    break;
                }
            }
        }
    }
    if(Timer.remainingTime() == 0)
    {
        QMessageBox::about(this, "错误", "接收回传超时！");
    }

    qDebug("haha");

}




//void MainWindow::TargetTypeCheck(){
//    QString TypeSelected;
//    TypeSelected = ui->TargetTypeButtonGroup->checkedButton()->text();
//    if(TypeSelected == QString("点目标"))
//    {
//        qDebug()<< QString("PointTargetTypeRadioButton");
//        ui->GroundToRadarAnglePhi->setEnabled(0);
//        ui->GroundToRadarAngleTheta->setEnabled(0);
//        ui->GroundToRadarAngleGamma->setEnabled(0);
//        ui->GroundToTargetAnglePhi->setEnabled(0);
//        ui->GroundToTargetAngleTheta->setEnabled(0);
//        ui->GroundToTargetAngleGamma->setEnabled(0);
//        ui->DistanceDirectRadioButton->setEnabled(1);
//        ui->PowerDirectRadioButton->setEnabled(1);
//        ui->TargetPower->setEnabled(1);
//        ui->Rcs->setEnabled(1);
//    }
//    else if(TypeSelected == QString("体目标"))
//    {
//        qDebug() << QString("SolidTargetTypeRadioButton");
//        ui->GroundToRadarAnglePhi->setEnabled(1);
//        ui->GroundToRadarAngleTheta->setEnabled(1);
//        ui->GroundToRadarAngleGamma->setEnabled(1);
//        ui->GroundToTargetAnglePhi->setEnabled(1);
//        ui->GroundToTargetAngleTheta->setEnabled(1);
//        ui->GroundToTargetAngleGamma->setEnabled(1);
//        ui->DistanceDirectRadioButton->setEnabled(0);
//        ui->PowerDirectRadioButton->setEnabled(0);
//        ui->TargetPower->setEnabled(0);
//        ui->Rcs->setEnabled(0);
//        ui->PowerIndirectRadioButton->toggle();
//        ui->DistanceCoordinateRadioButton->toggle();
//    }
//    else
//    {
//        qDebug() << "An error occured, TargetTypeCheck()!;";
//    }
//}

//void MainWindow::PowerTypeCheck(){
//    QString TypeSelected;
//    TypeSelected = ui->PowerTypeButtonGroup->checkedButton()->text();
//    if(TypeSelected == QString("直接设定功率"))
//    {
//        qDebug()<< QString("PowerDirectRadioButton");
//        ui->TargetPower->setEnabled(1);
//        ui->Pt->setEnabled(0);
//        ui->G->setEnabled(0);
//        ui->Ae->setEnabled(0);
//        ui->Rcs->setEnabled(0);
//        ui ->AreaTransmit->setEnabled(0);
//        ui ->AreaReceive->setEnabled(0);
//        ui ->IndirectCalTab->setEnabled(0);
//    }
//    else if(TypeSelected == QString("间接计算功率"))
//    {
//        qDebug() << QString("PowerIndirectRadioButton");
//        ui->TargetPower->setEnabled(0);
//        ui->Pt->setEnabled(1);
//        ui->G->setEnabled(1);
//        ui->Ae->setEnabled(1);
//        ui->Rcs->setEnabled(1);
//        ui ->AreaTransmit->setEnabled(1);
//        ui ->AreaReceive->setEnabled(1);
//        ui ->IndirectCalTab->setEnabled(1);
//    }
//    else
//    {
//        qDebug() << "An error occured, PowerTypeCheck()!;";
//    }
//}

//void MainWindow::DistanceTypeCheck(){
//    QString TypeSelected;
//    TypeSelected = ui->DistanceTypeButtonGroup->checkedButton()->text();
//    if(TypeSelected == QString("直接设定距离"))
//    {
//        qDebug()<< QString("DistanceDirectRadioButton");
//        ui->TargetDistance->setEnabled(1);
//        ui->TransmitRadarX->setEnabled(0);
//        ui->TransmitRadarY->setEnabled(0);
//        ui->TransmitRadarZ->setEnabled(0);
//        ui->TargetX->setEnabled(0);
//        ui->TargetY->setEnabled(0);
//        ui->TargetZ->setEnabled(0);
//        ui->ReceiveRadarX->setEnabled(0);
//        ui->ReceiveRadarY->setEnabled(0);
//        ui->ReceiveRadarZ->setEnabled(0);
//        ui->TargetDistanceCal->setEnabled(0);
//        ui->TargetDistanceTransmitCal->setEnabled(0);
//        ui->TargetDistanceReceiveCal->setEnabled(0);
//        ui->TargetDistanceTransmit->setEnabled(1);
//        ui->TargetDistanceReceive->setEnabled(1);
//    }
//    else if(TypeSelected == QString("坐标计算距离"))
//    {
//        qDebug() << QString("DistanceCoordinateRadioButton");
//        ui->TargetDistance->setEnabled(0);
//        ui->TransmitRadarX->setEnabled(1);
//        ui->TransmitRadarY->setEnabled(1);
//        ui->TransmitRadarZ->setEnabled(1);
//        ui->TargetX->setEnabled(1);
//        ui->TargetY->setEnabled(1);
//        ui->TargetZ->setEnabled(1);
//        ui->ReceiveRadarX->setEnabled(1);
//        ui->ReceiveRadarY->setEnabled(1);
//        ui->ReceiveRadarZ->setEnabled(1);
//        ui->TargetDistanceCal->setEnabled(1);
//        ui->TargetDistanceTransmitCal->setEnabled(1);
//        ui->TargetDistanceReceiveCal->setEnabled(1);
//        ui->TargetDistanceTransmit->setEnabled(0);
//        ui->TargetDistanceReceive->setEnabled(0);    }
//    else
//    {
//        qDebug() << "An error occured, DistanceTypeCheck()!;";
//    }
//}

