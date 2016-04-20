//#include "mainwindow.h"
//#include "ui_mainwindow.h"
//#include <cmath>
//#include <QMessageBox>
//#include <QPixmap>
//#include <QPalette>
//#include <stdio.h>
//#include <QString>

//void MainWindow::CalculateAndUpdate()
//{
//    QString TypeSelected;
//    float   PowerParam;

//    frame.TargetSpeed = ui->TargetSpeed->text().toFloat();
//    frame.TargetAngleTheta = ui->TargetAngleTheta->text().toFloat();
//    frame.TargetAnglePhi = ui->TargetAnglePhi->text().toFloat();

//    //-------- target distance calculate --------
//    TypeSelected = ui->DistanceTypeButtonGroup->checkedButton()->text();
//    if(TypeSelected == QString("直接设定距离"))
//    {
//        CalculateDirectDistance();

//    }
//    else if(TypeSelected == QString("坐标计算距离"))
//    {
//        CalculateCoordinateDistance();
//    }
//    else
//    {
//        qDebug() << "An error occured, DistanceTypeCheck()!;";
//    }

//    //-------- target power calculate --------
//    TypeSelected = ui->PowerTypeButtonGroup->checkedButton()->text();
//    if(TypeSelected == QString("间接计算功率"))
//    {
//        PowerParam = CalculatePower();
//    }

//    //--------point target and solid target--------
//    TypeSelected = ui->TargetTypeButtonGroup->checkedButton()->text();
//    if(TypeSelected == QString("点目标"))
//    {
//        TypeSelected = ui->PowerTypeButtonGroup->checkedButton()->text();
//        if(TypeSelected == QString("直接设定功率"))
//        {
//            CalculatePointTargetScatteringPoint();
//        }
//        else if(TypeSelected == QString("间接计算功率"))
//        {
//            CalculatePointTargetScatteringPoint(PowerParam);
//        }
//    }
//    else if(TypeSelected == QString("体目标"))
//    {
//        CalculateSolidTargetScatteringPoint(PowerParam);
//    }

//    //----------------- Check if the sum of scattering point power is overflowed ----------------
//    PowerOverflowCheck();

//    //----------------- Jamming ------------------------------------------
//    if(ui->JammingTabWidget->currentIndex() == 0)   //No jamming
//    {
//        frame.JammingType = 0;
//    }
//    else if(ui->JammingTabWidget->currentIndex() == 1)   //ISRJ
//    {
//        frame.JammingType = 1;
//        frame.Isrj.JammingDistance      = ui->IsrjJammingDistance->text().toFloat();
//        frame.Isrj.JammingSpeed         = ui->IsrjJammingSpeed->text().toFloat();
//        frame.Isrj.JammingAngleTheta    = ui->IsrjJammingAngleTheta->text().toFloat();
//        frame.Isrj.JammingAnglePhi      = ui->IsrjJammingAnglePhi->text().toFloat();
//        frame.Isrj.JammingPower         = ui->IsrjJammingPower->text().toFloat();
//        frame.Isrj.SampleTimeWidth      = (char)ui->IsrjSampleTimeWidth->text().toUShort();
//        frame.Isrj.RepeatTimeWidth      = (char)ui->IsrjRepeatTimeWidth->text().toUShort();
//        frame.Isrj.RepeatStartTime      = (char)ui->IsrjRepeatStartTime->text().toUShort();
//        frame.Isrj.RepeatNum            = (char)ui->IsrjRepeatNum->text().toUShort();
//    }
//}

////--------distance calculate--------
//void MainWindow::CalculateDirectDistance(void)
//{
//    float TargetDistanceCalTmp;
//    TargetDistanceCalTmp = ui->TargetDistanceTransmit->text().toFloat() +
//                           ui->TargetDistanceReceive->text().toFloat();
//    ui->TargetDistance->setText(QString::number(TargetDistanceCalTmp));
//    frame.TargetDistance = TargetDistanceCalTmp;
//    frame.TargetReceiveDistance = ui->TargetDistanceReceive->text().toFloat();
//}

//void MainWindow::CalculateCoordinateDistance(void)
//{
//    float TargetDistanceCalTmp1;
//    float TargetDistanceCalTmp2;

//    float TransmitRadarX = ui->TransmitRadarX->text().toFloat();
//    float TransmitRadarY = ui->TransmitRadarY->text().toFloat();
//    float TransmitRadarZ = ui->TransmitRadarZ->text().toFloat();
//    float TargetX = ui->TargetX->text().toFloat();
//    float TargetY = ui->TargetY->text().toFloat();
//    float TargetZ = ui->TargetZ->text().toFloat();
//    float ReceiveRadarX = ui->ReceiveRadarX->text().toFloat();
//    float ReceiveRadarY = ui->ReceiveRadarY->text().toFloat();
//    float ReceiveRadarZ = ui->ReceiveRadarZ->text().toFloat();

//    TargetDistanceCalTmp1 = sqrt((TransmitRadarX - TargetX)*(TransmitRadarX - TargetX) +
//                                 (TransmitRadarY - TargetY)*(TransmitRadarY - TargetY) +
//                                 (TransmitRadarZ - TargetZ)*(TransmitRadarZ - TargetZ)  );
//    ui->TargetDistanceTransmitCal->setText(QString::number(TargetDistanceCalTmp1));

//    TargetDistanceCalTmp2 = sqrt(  (ReceiveRadarX - TargetX)*(ReceiveRadarX - TargetX) +
//                                   (ReceiveRadarY - TargetY)*(ReceiveRadarY - TargetY) +
//                                   (ReceiveRadarZ - TargetZ)*(ReceiveRadarZ - TargetZ)  );
//    ui->TargetDistanceReceiveCal->setText(QString::number(TargetDistanceCalTmp2));

//    ui->TargetDistanceCal->setText(QString::number(TargetDistanceCalTmp1 + TargetDistanceCalTmp2));

//    frame.TargetDistance = TargetDistanceCalTmp1 + TargetDistanceCalTmp2;
//    frame.TargetReceiveDistance = TargetDistanceCalTmp2;
//}


////-------- power calculate --------
//float MainWindow::CalculatePower()
//{
//    qDebug() << "Enter CalculatePower";
//    float PowerParam;
//    float AreaTransmitTmp;
//    float AreaReceiveTmp;
//    float AreaDbm;

//    //update AreaTransmit
//    AreaTransmitTmp = 4 * 3.1415926 * ui->TargetDistanceTransmit->text().toFloat() * ui->TargetDistanceTransmit->text().toFloat();
//    ui->AreaTransmit->setText(QString::number(AreaTransmitTmp));

//    //update AreaReceive
//    AreaReceiveTmp = 4 * 3.1415926 * ui->TargetDistanceReceive->text().toFloat() * ui->TargetDistanceReceive->text().toFloat();
//    ui->AreaReceive->setText(QString::number(AreaReceiveTmp));

//    AreaDbm = 10*log10(1/AreaTransmitTmp/AreaReceiveTmp) + 30;    //calculate the area information in dBm

//    //calculate in dBm
//    PowerParam =    (ui->Pt ->text().toFloat()) +
//                    (ui->G  ->text().toFloat()) +
//                    (ui->Ae ->text().toFloat()) +
//                    AreaDbm;

//    return PowerParam;
//}


////--------point target and solid target--------
////It is a overloaded function
//void MainWindow::CalculatePointTargetScatteringPoint(float PowerParam)
//{
//    int FloatNull = 0xffffffff;
//    for(int i=0 ; i<RANGE_PROFILE_NUM ; i++)
//    {
//        if(i == (RANGE_PROFILE_NUM/2 - 1))
//        {
//            //About solid target, the power is calculated by the parameter from CalculatePower.
//            frame.ScatteringPointPowerEquivalentRecv[i] = PowerParam + 10*log10(ui->Rcs->text().toFloat()) + 30;   //dB
//            frame.ScatteringPointPowerTheta[i] = 0;
//            frame.ScatteringPointPowerPhi[i] = 0;
//            //display in SolidTargetTextEdit
//            QString TextEditString;
//            TextEditString.clear();
//            //clear the TextEdit
//            ui->SolidTargetTextEdit->clear();

//            TextEditString.sprintf("ScatteringPointPowerEquivalentRecv[%d] = %f\n",
//                                (RANGE_PROFILE_NUM/2 - 1), frame.ScatteringPointPowerEquivalentRecv[RANGE_PROFILE_NUM/2 - 1]);
//            ui->SolidTargetTextEdit->append(TextEditString);
//        }
//        else
//        {
//            memcpy(&frame.ScatteringPointPowerEquivalentRecv[i], &FloatNull, sizeof(float)); //indicate the value is invalid
//            memcpy(&frame.ScatteringPointPowerTheta[i], &FloatNull, sizeof(float)); //indicate the value is invalid
//            memcpy(&frame.ScatteringPointPowerPhi[i], &FloatNull, sizeof(float)); //indicate the value is invalid
//        }
//    }
//}

//void MainWindow::CalculatePointTargetScatteringPoint()
//{
//    int FloatNull = 0xffffffff;
//    for(int i=0 ; i<RANGE_PROFILE_NUM ; i++)
//    {
//        if(i == (RANGE_PROFILE_NUM/2 - 1))
//        {
//            //About point target, the power is directly set by TargetPower.
//            frame.ScatteringPointPowerEquivalentRecv[i] = ui->TargetPower->text().toFloat();   //dB
//            frame.ScatteringPointPowerTheta[i] = 0;
//            frame.ScatteringPointPowerPhi[i] = 0;
//        }
//        else
//        {
//            memcpy(&frame.ScatteringPointPowerEquivalentRecv[i], &FloatNull, sizeof(float)); //indicate the value is invalid
//            memcpy(&frame.ScatteringPointPowerTheta[i], &FloatNull, sizeof(float)); //indicate the value is invalid
//            memcpy(&frame.ScatteringPointPowerPhi[i], &FloatNull, sizeof(float)); //indicate the value is invalid
//        }
//    }
//}



////check if the string is "data"
//int IsData(char *temp)
//{
//    int i;
//    char data[] = "data";
//    for(i = 0 ; i < 4 ; i++)
//    {
//        if(*(temp+i) != *(data+i))
//        {
//            return - 1;
//        }
//    }
//    return 0;
//}

////calculate coordinate tranformation from origin coordinate to transformational coordinate
//void CoordinateCalculateOriginToTrans(float OriginToTransAnglePhi, float OriginToTransAngleTheta, float OriginToTransAngleGamma,
//                                   float OriginalX, float OriginalY, float OriginalZ,
//                                   float &TransX, float &TransY, float &TransZ)
//{
//    float TransMatrix[3][3];

//    float OriginToTransAnglePhiRad = OriginToTransAnglePhi / 3.1415926 * 180;
//    float OriginToTransAngleThetaRad = OriginToTransAngleTheta / 3.1415926 * 180;
//    float OriginToTransAngleGammaRad = OriginToTransAngleGamma / 3.1415926 * 180;

//    float CosPhi = cos(OriginToTransAnglePhiRad);
//    float SinPhi = sin(OriginToTransAnglePhiRad);
//    float CosTheta = cos(OriginToTransAngleThetaRad);
//    float SinTheta = sin(OriginToTransAngleThetaRad);
//    float CosGamma = cos(OriginToTransAngleGammaRad);
//    float SinGamma = sin(OriginToTransAngleGammaRad);

//    TransMatrix[0][0] = CosPhi*CosTheta;
//    TransMatrix[0][1] = -CosPhi*SinTheta*CosGamma + SinPhi*SinGamma;
//    TransMatrix[0][2] = CosPhi*SinTheta*SinGamma + SinPhi*CosGamma;
//    TransMatrix[1][0] = SinTheta;
//    TransMatrix[1][1] = CosTheta*CosGamma;
//    TransMatrix[1][2] = -CosTheta*SinGamma;
//    TransMatrix[2][0] = -SinPhi*CosTheta;
//    TransMatrix[2][1] = SinPhi*SinTheta*CosGamma + CosPhi*SinGamma;
//    TransMatrix[2][2] = -SinPhi*SinTheta*SinGamma + CosPhi*CosGamma;

//    TransX = OriginalX*TransMatrix[0][0] + OriginalY*TransMatrix[0][1] + OriginalZ*TransMatrix[0][2];
//    TransY = OriginalX*TransMatrix[1][0] + OriginalY*TransMatrix[1][1] + OriginalZ*TransMatrix[1][2];
//    TransZ = OriginalX*TransMatrix[2][0] + OriginalY*TransMatrix[2][1] + OriginalZ*TransMatrix[2][2];
//}

////calculate coordinate tranformation from origin coordinate to transformational coordinate
//void CoordinateCalculateTransToOrigin(float TransToOriginAnglePhi, float TransToOriginAngleTheta, float TransToOriginAngleGamma,
//                                   float OriginalX, float OriginalY, float OriginalZ,
//                                   float &TransX, float &TransY, float &TransZ)
//{
//    float TransMatrix[3][3];

//    float TransToOriginAnglePhiRad = TransToOriginAnglePhi / 3.1415926 * 180;
//    float TransToOriginAngleThetaRad = TransToOriginAngleTheta / 3.1415926 * 180;
//    float TransToOriginAngleGammaRad = TransToOriginAngleGamma / 3.1415926 * 180;

//    float CosPhi = cos(TransToOriginAnglePhiRad);
//    float SinPhi = sin(TransToOriginAnglePhiRad);
//    float CosTheta = cos(TransToOriginAngleThetaRad);
//    float SinTheta = sin(TransToOriginAngleThetaRad);
//    float CosGamma = cos(TransToOriginAngleGammaRad);
//    float SinGamma = sin(TransToOriginAngleGammaRad);

//    TransMatrix[0][0] = CosPhi*CosTheta;
//    TransMatrix[0][1] = SinTheta;
//    TransMatrix[0][2] = -SinPhi*CosTheta;
//    TransMatrix[1][0] = -CosPhi*SinTheta*CosGamma + SinPhi*SinGamma;
//    TransMatrix[1][1] = CosTheta*CosGamma;
//    TransMatrix[1][2] = SinPhi*SinTheta*CosGamma + CosPhi*SinGamma;
//    TransMatrix[2][0] = CosPhi*SinTheta*SinGamma + SinPhi*CosGamma;
//    TransMatrix[2][1] = -CosTheta*SinGamma;
//    TransMatrix[2][2] = -SinPhi*SinTheta*SinGamma + CosPhi*CosGamma;

//    TransX = OriginalX*TransMatrix[0][0] + OriginalY*TransMatrix[0][1] + OriginalZ*TransMatrix[0][2];
//    TransY = OriginalX*TransMatrix[1][0] + OriginalY*TransMatrix[1][1] + OriginalZ*TransMatrix[1][2];
//    TransZ = OriginalX*TransMatrix[2][0] + OriginalY*TransMatrix[2][1] + OriginalZ*TransMatrix[2][2];
//}

////calculate rectangular coordinate system to sphere coordinate system, range is [0, 180]
//void CoordinateCalRectToSphere(float RectX, float RectY, float RectZ, float &Theta, float &Phi)
//{
//    float r = sqrt(RectX*RectX + RectY*RectY);

//    if(RectZ == 0)
//        Theta = 90;
//    else
//        Theta = atan(r/RectZ) / 3.1415926 * 180;

//    if((r == 0)&&(RectZ < 0)) Theta = 180;     //the value is 180

//    while(Theta < 0)   Theta += 180;   //the value of atan is -pi~pi

//    if((Theta == 0)||(Theta == 180))
//    {
//        Phi = 90;       //Phi = 90 is the true value.
//    }
//    else
//    {
//        if(RectX == 0)
//        {
//            if(RectY > 0)
//                Phi = 90;
//            else
//                Phi = 270;
//        }
//        else
//        {
//            Phi = atan(RectY/RectX)  / 3.1415926 * 180;
//            if(Phi < 0)   Phi += 180;
//            if(RectY < 0) Phi += 180;   //the value of 180~360
//        }
//    }
//}

////Calculate the angle of scattering point in X, Y, Z direction
////Return angle range is theta [0, 180], phi[0, 360 - ANGLE_STEPPING]
//void ScatteringPointAngleCalculate(float GroundToTargetAnglePhi, float GroundToTargetAngleTheta, float GroundToTargetAngleGamma,
//                              float GroundToRadarAnglePhi, float GroundToRadarAngleTheta, float GroundToRadarAngleGamma,
//                              float TargetAngleTheta, float TargetAnglePhi,
//                              float &TargetThetaTransY, float &TargetPhiTransY, float &TargetThetaTransZ, float &TargetPhiTransZ)
//{
//    float TargetToGroundAngleX, TargetToGroundAngleY, TargetToGroundAngleZ;
//    //save the value of ground to radar coordinate system
//    float RadarToGroundAngleX, RadarToGroundAngleY, RadarToGroundAngleZ;

//    //---- calculate Y axis(trans) in radar coordinate to target coordinate, and obtain the reflect angle ------
//    CoordinateCalculateTransToOrigin(GroundToTargetAnglePhi, GroundToTargetAngleTheta, GroundToTargetAngleGamma,
//                                     sin(0 - TargetAngleTheta), cos(0 - TargetAngleTheta), 0,
//                                     TargetToGroundAngleX, TargetToGroundAngleY, TargetToGroundAngleZ);

//    CoordinateCalculateOriginToTrans(GroundToRadarAnglePhi, GroundToRadarAngleTheta, GroundToRadarAngleGamma,
//                                     TargetToGroundAngleX, TargetToGroundAngleY, TargetToGroundAngleZ,
//                                     RadarToGroundAngleX, RadarToGroundAngleY, RadarToGroundAngleZ);

//    CoordinateCalRectToSphere(RadarToGroundAngleX, RadarToGroundAngleY, RadarToGroundAngleZ,
//                              TargetThetaTransY, TargetPhiTransY);
//    //-------------------------------------------------------------------------------------------------------------

//    //---- calculate Z axis(trans) in radar coordinate to target coordinate, and obtain the reflect angle ------
//    CoordinateCalculateTransToOrigin(GroundToTargetAnglePhi, GroundToTargetAngleTheta, GroundToTargetAngleGamma,
//                                     sin(0 - TargetAnglePhi), 0, cos(0 - TargetAnglePhi),
//                                     TargetToGroundAngleX, TargetToGroundAngleY, TargetToGroundAngleZ);

//    CoordinateCalculateOriginToTrans(GroundToRadarAnglePhi, GroundToRadarAngleTheta, GroundToRadarAngleGamma,
//                                     TargetToGroundAngleX, TargetToGroundAngleY, TargetToGroundAngleZ,
//                                     RadarToGroundAngleX, RadarToGroundAngleY, RadarToGroundAngleZ);

//    CoordinateCalRectToSphere(RadarToGroundAngleX, RadarToGroundAngleY, RadarToGroundAngleZ,
//                              TargetThetaTransZ, TargetPhiTransZ);
//    //-------------------------------------------------------------------------------------------------------------
//}

//void MainWindow::CalculateSolidTargetScatteringPoint(float PowerParam)
//{

//    int i;
//    int flag1 = 0, flag2 = 0, flag3 = 0;    //indicates that corresponding data has been read
//    int flagNext1 = 0, flagNext2 = 0, flagNext3 = 0;
//    int status;
//    int phi_in, theta_in;
//    FILE* fd;
//    //save fgets() temporary data.
//    char  temp[100];
//    //Vector of equivalent receive direction
//    float EquivalentReceiveVectorX;
//    float EquivalentReceiveVectorY;
//    float EquivalentReceiveVectorZ;
//    //Angle of equivalent receive direction in target coordinate
//    float EquivalentReceiveVectorTheta;
//    float EquivalentReceiveVectorPhi;
//    //Vector of true receive direction
//    float TrueReceiveVectorX;
//    float TrueReceiveVectorY;
//    float TrueReceiveVectorZ;
//    //Angle of true receive direction in target coordinate
//    float TrueReceiveVectorTheta;
//    float TrueReceiveVectorPhi;
//    //Angle differential between equivalent and true direction of receive
//    float AngleDiffEquivalentTrueRecieveTheta;
//    float AngleDiffEquivalentTrueRecievePhi;
//    //Radar coordinate axis angle in target coordinate
//    float RadarToTargetAngleThetaTransY, RadarToTargetAnglePhiTransY;
//    float RadarToTargetAngleThetaTransZ, RadarToTargetAnglePhiTransZ;
//    //Angle that lookup table used
//    int EquivalentReceiveVectorThetaInt, EquivalentReceiveVectorPhiInt;
//    int RadarToTargetAngleThetaTransYInt, RadarToTargetAnglePhiTransYInt;
//    int RadarToTargetAngleThetaTransZInt, RadarToTargetAnglePhiTransZInt;
//    //Used to interpolation
//    int EquivalentReceiveVectorThetaIntNext, EquivalentReceiveVectorPhiIntNext;
//    int RadarToTargetAngleThetaTransYIntNext, RadarToTargetAnglePhiTransYIntNext;
//    int RadarToTargetAngleThetaTransZIntNext, RadarToTargetAnglePhiTransZIntNext;
//    //Range profile
//    float ScatteringPointRangeProfileEquivalentRecv[RANGE_PROFILE_NUM];
//    float ScatteringPointRangeProfileTheta[RANGE_PROFILE_NUM];
//    float ScatteringPointRangeProfilePhi[RANGE_PROFILE_NUM];

//    float ScatteringPointRangeProfileNextEquivalentRecv[RANGE_PROFILE_NUM];
//    float ScatteringPointRangeProfileNextTheta[RANGE_PROFILE_NUM];
//    float ScatteringPointRangeProfileNextPhi[RANGE_PROFILE_NUM];


//    //Calculate the vector of Equivalent receive direction
//    EquivalentReceiveVectorX = ui->TargetX->text().toFloat() - (ui->TransmitRadarX->text().toFloat() + ui->ReceiveRadarX->text().toFloat())/2;
//    EquivalentReceiveVectorY = ui->TargetY->text().toFloat() - (ui->TransmitRadarY->text().toFloat() + ui->ReceiveRadarY->text().toFloat())/2;
//    EquivalentReceiveVectorZ = ui->TargetZ->text().toFloat() - (ui->TransmitRadarZ->text().toFloat() + ui->ReceiveRadarZ->text().toFloat())/2;

//    //Calculate the vector of true receive direction
//    TrueReceiveVectorX = ui->TargetX->text().toFloat() - ui->ReceiveRadarX->text().toFloat();
//    TrueReceiveVectorY = ui->TargetY->text().toFloat() - ui->ReceiveRadarY->text().toFloat();
//    TrueReceiveVectorZ = ui->TargetZ->text().toFloat() - ui->ReceiveRadarZ->text().toFloat();

//    //Calculate the angle differential between Equivalent and true direction of receive
//    CoordinateCalRectToSphere(EquivalentReceiveVectorX, EquivalentReceiveVectorY, EquivalentReceiveVectorZ,
//                              EquivalentReceiveVectorTheta, EquivalentReceiveVectorPhi);
//    CoordinateCalRectToSphere(TrueReceiveVectorX, TrueReceiveVectorY, TrueReceiveVectorZ,
//                              TrueReceiveVectorTheta, TrueReceiveVectorPhi);
//    AngleDiffEquivalentTrueRecieveTheta = EquivalentReceiveVectorTheta - TrueReceiveVectorTheta;
//    AngleDiffEquivalentTrueRecievePhi = EquivalentReceiveVectorPhi - TrueReceiveVectorPhi;

//    //Calculate the direction of radar coordinate axis(trans) in target coordinate
//    ScatteringPointAngleCalculate(
//                ui->GroundToTargetAnglePhi->text().toFloat(),
//                ui->GroundToTargetAngleTheta->text().toFloat(),
//                ui->GroundToTargetAngleGamma->text().toFloat(),
//                ui->GroundToRadarAnglePhi->text().toFloat(),
//                ui->GroundToRadarAngleTheta->text().toFloat(),
//                ui->GroundToRadarAngleGamma->text().toFloat(),
//                ui->TargetAngleTheta->text().toFloat(),
//                ui->TargetAnglePhi->text().toFloat(),
//                RadarToTargetAngleThetaTransY, RadarToTargetAnglePhiTransY,
//                RadarToTargetAngleThetaTransZ, RadarToTargetAnglePhiTransZ);

//    //Convert the angle to equivalent receive direction
//    RadarToTargetAngleThetaTransY += AngleDiffEquivalentTrueRecieveTheta;
//    RadarToTargetAnglePhiTransY += AngleDiffEquivalentTrueRecievePhi;
//    RadarToTargetAngleThetaTransZ += AngleDiffEquivalentTrueRecieveTheta;
//    RadarToTargetAnglePhiTransZ += AngleDiffEquivalentTrueRecievePhi;

//    //The range of theta is [0, 180], and the range of phi is [0, 360)
//    while(RadarToTargetAngleThetaTransY < 0)    RadarToTargetAngleThetaTransY += 180;
//    while(RadarToTargetAngleThetaTransY > 180)  RadarToTargetAngleThetaTransY -= 180;
//    while(RadarToTargetAngleThetaTransZ < 180)  RadarToTargetAngleThetaTransZ += 180;
//    while(RadarToTargetAngleThetaTransZ > 180)  RadarToTargetAngleThetaTransZ -= 180;
//    while(RadarToTargetAnglePhiTransY < 0)
//        RadarToTargetAnglePhiTransY += 180;
//    while((RadarToTargetAnglePhiTransY > 360)||(RadarToTargetAnglePhiTransY == 360))
//        RadarToTargetAnglePhiTransY -= 360;
//    while(RadarToTargetAnglePhiTransZ < 0)
//        RadarToTargetAnglePhiTransZ += 180;
//    while((RadarToTargetAnglePhiTransZ > 360)||(RadarToTargetAnglePhiTransZ == 360))
//        RadarToTargetAnglePhiTransZ -= 360;



//    //Convert the angle to the format that lookup table used
//    EquivalentReceiveVectorThetaInt     = (int)(EquivalentReceiveVectorTheta    / ANGLE_STEPPING) * ANGLE_STEPPING;
//    EquivalentReceiveVectorPhiInt       = (int)(EquivalentReceiveVectorPhi      / ANGLE_STEPPING) * ANGLE_STEPPING;
//    RadarToTargetAngleThetaTransYInt    = (int)(RadarToTargetAngleThetaTransY   / ANGLE_STEPPING) * ANGLE_STEPPING;
//    RadarToTargetAnglePhiTransYInt      = (int)(RadarToTargetAnglePhiTransY     / ANGLE_STEPPING) * ANGLE_STEPPING;
//    RadarToTargetAngleThetaTransZInt    = (int)(RadarToTargetAngleThetaTransZ   / ANGLE_STEPPING) * ANGLE_STEPPING;
//    RadarToTargetAnglePhiTransZInt      = (int)(RadarToTargetAnglePhiTransZ     / ANGLE_STEPPING) * ANGLE_STEPPING;

//    //Find the next data to do interpolation
//    EquivalentReceiveVectorThetaIntNext     = EquivalentReceiveVectorThetaInt   + ANGLE_STEPPING;
//    EquivalentReceiveVectorPhiIntNext       = EquivalentReceiveVectorPhiInt     + ANGLE_STEPPING;
//    RadarToTargetAngleThetaTransYIntNext    = RadarToTargetAngleThetaTransYInt  + ANGLE_STEPPING;
//    RadarToTargetAnglePhiTransYIntNext      = RadarToTargetAnglePhiTransYInt    + ANGLE_STEPPING;
//    RadarToTargetAngleThetaTransZIntNext    = RadarToTargetAngleThetaTransZInt  + ANGLE_STEPPING;
//    RadarToTargetAnglePhiTransZIntNext      = RadarToTargetAnglePhiTransZInt    + ANGLE_STEPPING;

//    //Range of EquivalentReceiveVectorThetaIntNext is ANGLE_STEPPING ~ 180
//    if(EquivalentReceiveVectorThetaIntNext  > 180)                        EquivalentReceiveVectorThetaIntNext   = 180;
//    if(EquivalentReceiveVectorPhiIntNext    > (360 - ANGLE_STEPPING))     EquivalentReceiveVectorPhiIntNext     = 360;
//    if(RadarToTargetAngleThetaTransYIntNext > 180)                        RadarToTargetAngleThetaTransYIntNext  = 180;
//    if(RadarToTargetAnglePhiTransYIntNext   > (360 - ANGLE_STEPPING))     RadarToTargetAnglePhiTransYIntNext    = 360;
//    if(RadarToTargetAngleThetaTransZIntNext > 180)                        RadarToTargetAngleThetaTransZIntNext  = 180;
//    if(RadarToTargetAnglePhiTransZIntNext   > (360 - ANGLE_STEPPING))     RadarToTargetAnglePhiTransZIntNext    = 360;


//    fd = fopen("D:/lrh_workspace/projects/simulator_new/qt_projects/RangeProfileData.txt", "r");
//    if(fd == NULL)
//    {
//        qDebug() <<"File open failed!\n";
//        QMessageBox::about(this, "提示", "打开 D:/projects/simulator_new/qt_projects/RangeProfileData.txt 出错！！！");
//    }

//    //Read data
//    while(fgets(temp, 100, fd))
//    {
//        if(IsData(temp) == 0)
//        {
//            status = fscanf(fd, "theta, phi: %d, %d\n", &theta_in, &phi_in);
//            if(status<0) QMessageBox::about(this, "提示", "读文件出错！！！");
//            //Read the data that befor the angle.
//            if((theta_in==EquivalentReceiveVectorThetaInt)&&(phi_in==EquivalentReceiveVectorPhiInt))
//            {
//                status = fscanf(fd, "\tScatteringPointRangeProfile[32] = {%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f}\n",
//                                    &ScatteringPointRangeProfileEquivalentRecv[0], &ScatteringPointRangeProfileEquivalentRecv[1], &ScatteringPointRangeProfileEquivalentRecv[2],
//                                    &ScatteringPointRangeProfileEquivalentRecv[3], &ScatteringPointRangeProfileEquivalentRecv[4], &ScatteringPointRangeProfileEquivalentRecv[5],
//                                    &ScatteringPointRangeProfileEquivalentRecv[6], &ScatteringPointRangeProfileEquivalentRecv[7], &ScatteringPointRangeProfileEquivalentRecv[8],
//                                    &ScatteringPointRangeProfileEquivalentRecv[9], &ScatteringPointRangeProfileEquivalentRecv[10], &ScatteringPointRangeProfileEquivalentRecv[11],
//                                    &ScatteringPointRangeProfileEquivalentRecv[12], &ScatteringPointRangeProfileEquivalentRecv[13], &ScatteringPointRangeProfileEquivalentRecv[14],
//                                    &ScatteringPointRangeProfileEquivalentRecv[15], &ScatteringPointRangeProfileEquivalentRecv[16], &ScatteringPointRangeProfileEquivalentRecv[17],
//                                    &ScatteringPointRangeProfileEquivalentRecv[18], &ScatteringPointRangeProfileEquivalentRecv[19], &ScatteringPointRangeProfileEquivalentRecv[20],
//                                    &ScatteringPointRangeProfileEquivalentRecv[21], &ScatteringPointRangeProfileEquivalentRecv[22], &ScatteringPointRangeProfileEquivalentRecv[23],
//                                    &ScatteringPointRangeProfileEquivalentRecv[24], &ScatteringPointRangeProfileEquivalentRecv[25], &ScatteringPointRangeProfileEquivalentRecv[26],
//                                    &ScatteringPointRangeProfileEquivalentRecv[27], &ScatteringPointRangeProfileEquivalentRecv[28], &ScatteringPointRangeProfileEquivalentRecv[29],
//                                    &ScatteringPointRangeProfileEquivalentRecv[30], &ScatteringPointRangeProfileEquivalentRecv[31]
//                                    );
//                if(status<0) QMessageBox::about(this, "提示", "读文件出错！！！");
//                flag1 = 1;
//            }
//            else if((theta_in==RadarToTargetAngleThetaTransYInt)&&(phi_in==RadarToTargetAnglePhiTransYInt))
//            {
//                status = fscanf(fd, "\tScatteringPointRangeProfile[32] = {%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f}\n",
//                                    &ScatteringPointRangeProfileTheta[0], &ScatteringPointRangeProfileTheta[1], &ScatteringPointRangeProfileTheta[2],
//                                    &ScatteringPointRangeProfileTheta[3], &ScatteringPointRangeProfileTheta[4], &ScatteringPointRangeProfileTheta[5],
//                                    &ScatteringPointRangeProfileTheta[6], &ScatteringPointRangeProfileTheta[7], &ScatteringPointRangeProfileTheta[8],
//                                    &ScatteringPointRangeProfileTheta[9], &ScatteringPointRangeProfileTheta[10], &ScatteringPointRangeProfileTheta[11],
//                                    &ScatteringPointRangeProfileTheta[12], &ScatteringPointRangeProfileTheta[13], &ScatteringPointRangeProfileTheta[14],
//                                    &ScatteringPointRangeProfileTheta[15], &ScatteringPointRangeProfileTheta[16], &ScatteringPointRangeProfileTheta[17],
//                                    &ScatteringPointRangeProfileTheta[18], &ScatteringPointRangeProfileTheta[19], &ScatteringPointRangeProfileTheta[20],
//                                    &ScatteringPointRangeProfileTheta[21], &ScatteringPointRangeProfileTheta[22], &ScatteringPointRangeProfileTheta[23],
//                                    &ScatteringPointRangeProfileTheta[24], &ScatteringPointRangeProfileTheta[25], &ScatteringPointRangeProfileTheta[26],
//                                    &ScatteringPointRangeProfileTheta[27], &ScatteringPointRangeProfileTheta[28], &ScatteringPointRangeProfileTheta[29],
//                                    &ScatteringPointRangeProfileTheta[30], &ScatteringPointRangeProfileTheta[31]
//                                    );
//                if(status<0) QMessageBox::about(this, "提示", "读文件出错！！！");
//                flag2 = 1;
//            }
//            else if((theta_in==RadarToTargetAngleThetaTransZInt)&&(phi_in==RadarToTargetAnglePhiTransZInt))
//            {
//                status = fscanf(fd, "\tScatteringPointRangeProfile[32] = {%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f}\n",
//                                    &ScatteringPointRangeProfilePhi[0], &ScatteringPointRangeProfilePhi[1], &ScatteringPointRangeProfilePhi[2],
//                                    &ScatteringPointRangeProfilePhi[3], &ScatteringPointRangeProfilePhi[4], &ScatteringPointRangeProfilePhi[5],
//                                    &ScatteringPointRangeProfilePhi[6], &ScatteringPointRangeProfilePhi[7], &ScatteringPointRangeProfilePhi[8],
//                                    &ScatteringPointRangeProfilePhi[9], &ScatteringPointRangeProfilePhi[10], &ScatteringPointRangeProfilePhi[11],
//                                    &ScatteringPointRangeProfilePhi[12], &ScatteringPointRangeProfilePhi[13], &ScatteringPointRangeProfilePhi[14],
//                                    &ScatteringPointRangeProfilePhi[15], &ScatteringPointRangeProfilePhi[16], &ScatteringPointRangeProfilePhi[17],
//                                    &ScatteringPointRangeProfilePhi[18], &ScatteringPointRangeProfilePhi[19], &ScatteringPointRangeProfilePhi[20],
//                                    &ScatteringPointRangeProfilePhi[21], &ScatteringPointRangeProfilePhi[22], &ScatteringPointRangeProfilePhi[23],
//                                    &ScatteringPointRangeProfilePhi[24], &ScatteringPointRangeProfilePhi[25], &ScatteringPointRangeProfilePhi[26],
//                                    &ScatteringPointRangeProfilePhi[27], &ScatteringPointRangeProfilePhi[28], &ScatteringPointRangeProfilePhi[29],
//                                    &ScatteringPointRangeProfilePhi[30], &ScatteringPointRangeProfilePhi[31]
//                                    );
//                if(status<0) QMessageBox::about(this, "提示", "读文件出错！！！");
//                flag3 = 1;
//            }
//            //Read the data that next to the angle.
//            else if((theta_in==EquivalentReceiveVectorThetaIntNext)&&(phi_in==EquivalentReceiveVectorPhiIntNext))
//            {
//                status = fscanf(fd, "\tScatteringPointRangeProfile[32] = {%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f}\n",
//                                    &ScatteringPointRangeProfileNextEquivalentRecv[0],  &ScatteringPointRangeProfileNextEquivalentRecv[1],  &ScatteringPointRangeProfileNextEquivalentRecv[2],
//                                    &ScatteringPointRangeProfileNextEquivalentRecv[3],  &ScatteringPointRangeProfileNextEquivalentRecv[4],  &ScatteringPointRangeProfileNextEquivalentRecv[5],
//                                    &ScatteringPointRangeProfileNextEquivalentRecv[6],  &ScatteringPointRangeProfileNextEquivalentRecv[7],  &ScatteringPointRangeProfileNextEquivalentRecv[8],
//                                    &ScatteringPointRangeProfileNextEquivalentRecv[9],  &ScatteringPointRangeProfileNextEquivalentRecv[10], &ScatteringPointRangeProfileNextEquivalentRecv[11],
//                                    &ScatteringPointRangeProfileNextEquivalentRecv[12], &ScatteringPointRangeProfileNextEquivalentRecv[13], &ScatteringPointRangeProfileNextEquivalentRecv[14],
//                                    &ScatteringPointRangeProfileNextEquivalentRecv[15], &ScatteringPointRangeProfileNextEquivalentRecv[16], &ScatteringPointRangeProfileNextEquivalentRecv[17],
//                                    &ScatteringPointRangeProfileNextEquivalentRecv[18], &ScatteringPointRangeProfileNextEquivalentRecv[19], &ScatteringPointRangeProfileNextEquivalentRecv[20],
//                                    &ScatteringPointRangeProfileNextEquivalentRecv[21], &ScatteringPointRangeProfileNextEquivalentRecv[22], &ScatteringPointRangeProfileNextEquivalentRecv[23],
//                                    &ScatteringPointRangeProfileNextEquivalentRecv[24], &ScatteringPointRangeProfileNextEquivalentRecv[25], &ScatteringPointRangeProfileNextEquivalentRecv[26],
//                                    &ScatteringPointRangeProfileNextEquivalentRecv[27], &ScatteringPointRangeProfileNextEquivalentRecv[28], &ScatteringPointRangeProfileNextEquivalentRecv[29],
//                                    &ScatteringPointRangeProfileNextEquivalentRecv[30], &ScatteringPointRangeProfileNextEquivalentRecv[31]
//                                    );
//                if(status<0) QMessageBox::about(this, "提示", "读文件出错！！！");
//                flagNext1 = 1;
//            }
//            else if((theta_in==RadarToTargetAngleThetaTransYIntNext)&&(phi_in==RadarToTargetAnglePhiTransYIntNext))
//            {
//                status = fscanf(fd, "\tScatteringPointRangeProfile[32] = {%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f}\n",
//                                    &ScatteringPointRangeProfileNextTheta[0],  &ScatteringPointRangeProfileNextTheta[1],  &ScatteringPointRangeProfileNextTheta[2],
//                                    &ScatteringPointRangeProfileNextTheta[3],  &ScatteringPointRangeProfileNextTheta[4],  &ScatteringPointRangeProfileNextTheta[5],
//                                    &ScatteringPointRangeProfileNextTheta[6],  &ScatteringPointRangeProfileNextTheta[7],  &ScatteringPointRangeProfileNextTheta[8],
//                                    &ScatteringPointRangeProfileNextTheta[9],  &ScatteringPointRangeProfileNextTheta[10], &ScatteringPointRangeProfileNextTheta[11],
//                                    &ScatteringPointRangeProfileNextTheta[12], &ScatteringPointRangeProfileNextTheta[13], &ScatteringPointRangeProfileNextTheta[14],
//                                    &ScatteringPointRangeProfileNextTheta[15], &ScatteringPointRangeProfileNextTheta[16], &ScatteringPointRangeProfileNextTheta[17],
//                                    &ScatteringPointRangeProfileNextTheta[18], &ScatteringPointRangeProfileNextTheta[19], &ScatteringPointRangeProfileNextTheta[20],
//                                    &ScatteringPointRangeProfileNextTheta[21], &ScatteringPointRangeProfileNextTheta[22], &ScatteringPointRangeProfileNextTheta[23],
//                                    &ScatteringPointRangeProfileNextTheta[24], &ScatteringPointRangeProfileNextTheta[25], &ScatteringPointRangeProfileNextTheta[26],
//                                    &ScatteringPointRangeProfileNextTheta[27], &ScatteringPointRangeProfileNextTheta[28], &ScatteringPointRangeProfileNextTheta[29],
//                                    &ScatteringPointRangeProfileNextTheta[30], &ScatteringPointRangeProfileNextTheta[31]
//                                    );
//                if(status<0) QMessageBox::about(this, "提示", "读文件出错！！！");
//                flagNext2 = 1;
//            }
//            else if((theta_in==RadarToTargetAngleThetaTransZIntNext)&&(phi_in==RadarToTargetAnglePhiTransZIntNext))
//            {
//                status = fscanf(fd, "\tScatteringPointRangeProfile[32] = {%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f}\n",
//                                    &ScatteringPointRangeProfileNextPhi[0],  &ScatteringPointRangeProfileNextPhi[1],  &ScatteringPointRangeProfileNextPhi[2],
//                                    &ScatteringPointRangeProfileNextPhi[3],  &ScatteringPointRangeProfileNextPhi[4],  &ScatteringPointRangeProfileNextPhi[5],
//                                    &ScatteringPointRangeProfileNextPhi[6],  &ScatteringPointRangeProfileNextPhi[7],  &ScatteringPointRangeProfileNextPhi[8],
//                                    &ScatteringPointRangeProfileNextPhi[9],  &ScatteringPointRangeProfileNextPhi[10], &ScatteringPointRangeProfileNextPhi[11],
//                                    &ScatteringPointRangeProfileNextPhi[12], &ScatteringPointRangeProfileNextPhi[13], &ScatteringPointRangeProfileNextPhi[14],
//                                    &ScatteringPointRangeProfileNextPhi[15], &ScatteringPointRangeProfileNextPhi[16], &ScatteringPointRangeProfileNextPhi[17],
//                                    &ScatteringPointRangeProfileNextPhi[18], &ScatteringPointRangeProfileNextPhi[19], &ScatteringPointRangeProfileNextPhi[20],
//                                    &ScatteringPointRangeProfileNextPhi[21], &ScatteringPointRangeProfileNextPhi[22], &ScatteringPointRangeProfileNextPhi[23],
//                                    &ScatteringPointRangeProfileNextPhi[24], &ScatteringPointRangeProfileNextPhi[25], &ScatteringPointRangeProfileNextPhi[26],
//                                    &ScatteringPointRangeProfileNextPhi[27], &ScatteringPointRangeProfileNextPhi[28], &ScatteringPointRangeProfileNextPhi[29],
//                                    &ScatteringPointRangeProfileNextPhi[30], &ScatteringPointRangeProfileNextPhi[31]
//                                    );
//                if(status<0) QMessageBox::about(this, "提示", "读文件出错！！！");
//                flagNext3 = 1;
//            }
//        }
//    }

//    //check if data of X, Y, Z has already read
//    if((flag1!=1)||(flag2!=1)||(flag3!=1)||(flagNext1!=1)||(flagNext2!=1)||(flagNext3!=1))
//    {
//        QMessageBox::about(this, "提示", "文件读取不完整！！！");
//        qDebug("flag1 = %d, flag2 = %d, flag3 = %d, flagNext1 = %d, flagNext2 = %d, flagNext3 = %d",
//                flag1, flag2, flag3, flagNext1, flagNext2, flagNext3);
//    }


//    //Interpolation
//    for(i = 0 ; i < RANGE_PROFILE_NUM ; i++)
//    {
//        ScatteringPointRangeProfileEquivalentRecv[i] += (ScatteringPointRangeProfileNextEquivalentRecv[i] - ScatteringPointRangeProfileEquivalentRecv[i]) /
//                                     sqrt(ANGLE_STEPPING*ANGLE_STEPPING + ANGLE_STEPPING*ANGLE_STEPPING)*
//                                     sqrt((EquivalentReceiveVectorTheta-EquivalentReceiveVectorThetaInt)*(EquivalentReceiveVectorTheta-EquivalentReceiveVectorThetaInt) +
//                                            (EquivalentReceiveVectorPhi-EquivalentReceiveVectorPhiInt)*(EquivalentReceiveVectorPhi-EquivalentReceiveVectorPhiInt));
//        ScatteringPointRangeProfileTheta[i] += (ScatteringPointRangeProfileNextTheta[i] - ScatteringPointRangeProfileTheta[i]) /
//                                     sqrt(ANGLE_STEPPING*ANGLE_STEPPING + ANGLE_STEPPING*ANGLE_STEPPING)*
//                                     sqrt((RadarToTargetAngleThetaTransY-RadarToTargetAngleThetaTransYInt)*(RadarToTargetAngleThetaTransY-RadarToTargetAngleThetaTransYInt) +
//                                            (RadarToTargetAnglePhiTransY-RadarToTargetAnglePhiTransYInt)*(RadarToTargetAnglePhiTransY-RadarToTargetAnglePhiTransYInt));
//        ScatteringPointRangeProfilePhi[i] += (ScatteringPointRangeProfileNextPhi[i] - ScatteringPointRangeProfilePhi[i]) /
//                                     sqrt(ANGLE_STEPPING*ANGLE_STEPPING + ANGLE_STEPPING*ANGLE_STEPPING)*
//                                     sqrt((RadarToTargetAngleThetaTransZ-RadarToTargetAngleThetaTransZInt)*(RadarToTargetAngleThetaTransZ-RadarToTargetAngleThetaTransZInt) +
//                                            (RadarToTargetAnglePhiTransZ-RadarToTargetAnglePhiTransZInt)*(RadarToTargetAnglePhiTransZ-RadarToTargetAnglePhiTransZInt));
//    }


//    //Calculate the power of each scattering point
//    for(i = 0 ; i < RANGE_PROFILE_NUM ; i++)
//    {
//        frame.ScatteringPointPowerEquivalentRecv[i] = PowerParam + (10*log10(ScatteringPointRangeProfileEquivalentRecv[i]) + 30);
//        frame.ScatteringPointPowerTheta[i] = PowerParam + (10*log10(ScatteringPointRangeProfileTheta[i]) + 30);
//        frame.ScatteringPointPowerPhi[i] = PowerParam + (10*log10(ScatteringPointRangeProfilePhi[i]) + 30);
//    }

//    QString TextEditString;
//    TextEditString.clear();
//    //clear the TextEdit
//    ui->SolidTargetTextEdit->clear();

//    TextEditString.sprintf("EquivalentReceiveVectorTheta = %f\n"
//                           "EquivalentReceiveVectorPhi = %f\n"
//                           "RadarToTargetAngleThetaTransY = %f\n"
//                           "RadarToTargetAnglePhiTransY = %f\n"
//                           "RadarToTargetAngleThetaTransZ = %f\n"
//                           "RadarToTargetAnglePhiTransZ = %f\n",
//                        EquivalentReceiveVectorTheta, EquivalentReceiveVectorPhi,
//                        RadarToTargetAngleThetaTransY, RadarToTargetAnglePhiTransY,
//                        RadarToTargetAngleThetaTransZ, RadarToTargetAnglePhiTransZ);

//    ui->SolidTargetTextEdit->append(TextEditString);
//    TextEditString.sprintf("ScatteringPointPowerEquivalentRecv[32] = \n"
//                           "{%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f}\n",
//                           frame.ScatteringPointPowerEquivalentRecv[0],  frame.ScatteringPointPowerEquivalentRecv[1],  frame.ScatteringPointPowerEquivalentRecv[2],
//                           frame.ScatteringPointPowerEquivalentRecv[3],  frame.ScatteringPointPowerEquivalentRecv[4],  frame.ScatteringPointPowerEquivalentRecv[5],
//                           frame.ScatteringPointPowerEquivalentRecv[6],  frame.ScatteringPointPowerEquivalentRecv[7],  frame.ScatteringPointPowerEquivalentRecv[8],
//                           frame.ScatteringPointPowerEquivalentRecv[9],  frame.ScatteringPointPowerEquivalentRecv[10], frame.ScatteringPointPowerEquivalentRecv[11],
//                           frame.ScatteringPointPowerEquivalentRecv[12], frame.ScatteringPointPowerEquivalentRecv[13], frame.ScatteringPointPowerEquivalentRecv[14],
//                           frame.ScatteringPointPowerEquivalentRecv[15], frame.ScatteringPointPowerEquivalentRecv[16], frame.ScatteringPointPowerEquivalentRecv[17],
//                           frame.ScatteringPointPowerEquivalentRecv[18], frame.ScatteringPointPowerEquivalentRecv[19], frame.ScatteringPointPowerEquivalentRecv[20],
//                           frame.ScatteringPointPowerEquivalentRecv[21], frame.ScatteringPointPowerEquivalentRecv[22], frame.ScatteringPointPowerEquivalentRecv[23],
//                           frame.ScatteringPointPowerEquivalentRecv[24], frame.ScatteringPointPowerEquivalentRecv[25], frame.ScatteringPointPowerEquivalentRecv[26],
//                           frame.ScatteringPointPowerEquivalentRecv[27], frame.ScatteringPointPowerEquivalentRecv[28], frame.ScatteringPointPowerEquivalentRecv[29],
//                           frame.ScatteringPointPowerEquivalentRecv[30], frame.ScatteringPointPowerEquivalentRecv[31]);

//    ui->SolidTargetTextEdit->append(TextEditString);
//    TextEditString.sprintf("ScatteringPointPowerTheta[32] = \n"
//                           "{%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f}\n\n"
//                           "ScatteringPointPowerPhi[32] = \n"
//                           "{%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f}\n",
//                           frame.ScatteringPointPowerTheta[0],  frame.ScatteringPointPowerTheta[1],  frame.ScatteringPointPowerTheta[2],
//                           frame.ScatteringPointPowerTheta[3],  frame.ScatteringPointPowerTheta[4],  frame.ScatteringPointPowerTheta[5],
//                           frame.ScatteringPointPowerTheta[6],  frame.ScatteringPointPowerTheta[7],  frame.ScatteringPointPowerTheta[8],
//                           frame.ScatteringPointPowerTheta[9],  frame.ScatteringPointPowerTheta[10], frame.ScatteringPointPowerTheta[11],
//                           frame.ScatteringPointPowerTheta[12], frame.ScatteringPointPowerTheta[13], frame.ScatteringPointPowerTheta[14],
//                           frame.ScatteringPointPowerTheta[15], frame.ScatteringPointPowerTheta[16], frame.ScatteringPointPowerTheta[17],
//                           frame.ScatteringPointPowerTheta[18], frame.ScatteringPointPowerTheta[19], frame.ScatteringPointPowerTheta[20],
//                           frame.ScatteringPointPowerTheta[21], frame.ScatteringPointPowerTheta[22], frame.ScatteringPointPowerTheta[23],
//                           frame.ScatteringPointPowerTheta[24], frame.ScatteringPointPowerTheta[25], frame.ScatteringPointPowerTheta[26],
//                           frame.ScatteringPointPowerTheta[27], frame.ScatteringPointPowerTheta[28], frame.ScatteringPointPowerTheta[29],
//                           frame.ScatteringPointPowerTheta[30], frame.ScatteringPointPowerTheta[31],
//                           frame.ScatteringPointPowerPhi[0],  frame.ScatteringPointPowerPhi[1],  frame.ScatteringPointPowerPhi[2],
//                           frame.ScatteringPointPowerPhi[3],  frame.ScatteringPointPowerPhi[4],  frame.ScatteringPointPowerPhi[5],
//                           frame.ScatteringPointPowerPhi[6],  frame.ScatteringPointPowerPhi[7],  frame.ScatteringPointPowerPhi[8],
//                           frame.ScatteringPointPowerPhi[9],  frame.ScatteringPointPowerPhi[10], frame.ScatteringPointPowerPhi[11],
//                           frame.ScatteringPointPowerPhi[12], frame.ScatteringPointPowerPhi[13], frame.ScatteringPointPowerPhi[14],
//                           frame.ScatteringPointPowerPhi[15], frame.ScatteringPointPowerPhi[16], frame.ScatteringPointPowerPhi[17],
//                           frame.ScatteringPointPowerPhi[18], frame.ScatteringPointPowerPhi[19], frame.ScatteringPointPowerPhi[20],
//                           frame.ScatteringPointPowerPhi[21], frame.ScatteringPointPowerPhi[22], frame.ScatteringPointPowerPhi[23],
//                           frame.ScatteringPointPowerPhi[24], frame.ScatteringPointPowerPhi[25], frame.ScatteringPointPowerPhi[26],
//                           frame.ScatteringPointPowerPhi[27], frame.ScatteringPointPowerPhi[28], frame.ScatteringPointPowerPhi[29],
//                           frame.ScatteringPointPowerPhi[30], frame.ScatteringPointPowerPhi[31]);

//    //一下这部分总是显示不出来，所以与上面的合并，不知道什么原因
//    ui->SolidTargetTextEdit->append(TextEditString);
//    TextEditString.sprintf("ScatteringPointPowerPhi[32] = \n"
//                           "{%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f, %f, \n"
//                           "%f, %f}\n",
//                           frame.ScatteringPointPowerPhi[0],  frame.ScatteringPointPowerPhi[1],  frame.ScatteringPointPowerPhi[2],
//                           frame.ScatteringPointPowerPhi[3],  frame.ScatteringPointPowerPhi[4],  frame.ScatteringPointPowerPhi[5],
//                           frame.ScatteringPointPowerPhi[6],  frame.ScatteringPointPowerPhi[7],  frame.ScatteringPointPowerPhi[8],
//                           frame.ScatteringPointPowerPhi[9],  frame.ScatteringPointPowerPhi[10], frame.ScatteringPointPowerPhi[11],
//                           frame.ScatteringPointPowerPhi[12], frame.ScatteringPointPowerPhi[13], frame.ScatteringPointPowerPhi[14],
//                           frame.ScatteringPointPowerPhi[15], frame.ScatteringPointPowerPhi[16], frame.ScatteringPointPowerPhi[17],
//                           frame.ScatteringPointPowerPhi[18], frame.ScatteringPointPowerPhi[19], frame.ScatteringPointPowerPhi[20],
//                           frame.ScatteringPointPowerPhi[21], frame.ScatteringPointPowerPhi[22], frame.ScatteringPointPowerPhi[23],
//                           frame.ScatteringPointPowerPhi[24], frame.ScatteringPointPowerPhi[25], frame.ScatteringPointPowerPhi[26],
//                           frame.ScatteringPointPowerPhi[27], frame.ScatteringPointPowerPhi[28], frame.ScatteringPointPowerPhi[29],
//                           frame.ScatteringPointPowerPhi[30], frame.ScatteringPointPowerPhi[31]);


//    fclose(fd);
//}

////Check if the sum of ScatteringPointPowerX is overflowed, Y and Z need not to check.
//void MainWindow::PowerOverflowCheck()
//{
//    int                 i;
//    unsigned long int   SumScatteringPointPowerEquivalentRecv = 0;
//    for(i = 0 ; i < RANGE_PROFILE_NUM ; i++)
//    {
//        SumScatteringPointPowerEquivalentRecv += sqrt(pow(10,((frame.ScatteringPointPowerEquivalentRecv[i] - POEWR_MAX_DBM)/10)) * AMPLITUDE_MAX * AMPLITUDE_MAX);
//    }

//    if(SumScatteringPointPowerEquivalentRecv > 0xffff)
//    {
//        QMessageBox::about(this, "提示", "功率过大，可能溢出！！！");
//    }
//}

