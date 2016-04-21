#ifndef SIMULATOR_GUI
#define SIMULATOR_GUI




#define FPGA_CLOCK              100000000

#define AUTO_MODE               1
#define MANUAL_MODE             2
#define ANGLE_STEPPING          10
#define RANGE_PROFILE_NUM       32
#define POEWR_MAX_DBM           -10
#define AMPLITUDE_MAX           0xffff

/* Frame ID */
#define COMMUNICATION_CHECK		1
#define SELF_CHECKING			2
#define	WORK_ENABLE				3
#define	SLEEP_ENABLE			4
#define	SCATTERING_POINT_INPUT	5
#define	WORK_PARAM_SET			6

/* Target param bit31:16 */
#define	MANUAL_MODE				0x0000
#define	AUTO_MODE_PASS_BACK		0x0001
#define	AUTO_MODE_NO_PASS_BACK	0x0002

/* Target param bit15:0 */
#define	POINT_TARGET			0x0000
#define	RANGE_SPREAD_TARGET_0	0x0001
#define	RANGE_SPREAD_TARGET_1	0x0002
#define	RANGE_SPREAD_TARGET_2	0x0003

/* Jamming param */
#define	NO_JAMMING				0x00000000
#define	ISRJ_0					0x00010000
#define	ISRJ_1					0x00010001
#define	ISRJ_2					0x00010002

typedef unsigned short Uint16;
typedef short Int16;
typedef unsigned int Uint32;
typedef int Int32;
typedef unsigned char Uint8;
typedef char Int8;


//--------目标参数----------------------
//点目标
typedef struct
{
    float TargetSpeedTran;
    float TargetSpeedRecv;
    float TargetPower;
    float TargetDistanceTran;
    float TargetDistanceRecv;
    float TargetTheta;
    float TargetPhi;
}PointTargetParam;
//扩展目标，参数0
typedef struct
{
    float TargetSpeedTran;
    float TargetSpeedRecv;
    float TargetDistanceTran;
    float TargetDistanceRecv;
    float TargetTheta;
    float TargetPhi;
    float TargetPt;
    float TargetG;
    float TargetAe;
    float TargetAttitudeTheta;
    float TargetAttitudePhi;
}RangeSpreadTargetParam0;
//扩展目标，参数1
typedef struct
{
    float TargetSpeedTran;
    float TargetSpeedRecv;
    float TargetPt;
    float TargetG;
    float TargetAe;
    float GroundCoordRadarTranX;
    float GroundCoordRadarTranY;
    float GroundCoordRadarTranZ;
    float GroundCoordTargetX;
    float GroundCoordTargetY;
    float GroundCoordTargetZ;
    float GroundCoordRadarRecvX;
    float GroundCoordRadarRecvY;
    float GroundCoordRadarRecvZ;
    float GroundCoordToRadarCoordAngleX;
    float GroundCoordToRadarCoordAngleY;
    float GroundCoordToRadarCoordAngleZ;
    float GroundCoordToTargetCoordAngleX;
    float GroundCoordToTargetCoordAngleY;
    float GroundCoordToTargetCoordAngleZ;
}RangeSpreadTargetParam1;
//扩展目标，参数2
typedef struct
{
    float TargetSpeedTran;
    float TargetSpeedRecv;
    float TargetPt;
    float TargetG;
    float TargetAe;
    float GroundCoordRadarTranX;
    float GroundCoordRadarTranY;
    float GroundCoordRadarTranZ;
    float GroundCoordTargetX;
    float GroundCoordTargetY;
    float GroundCoordTargetZ;
    float GroundCoordRadarRecvX;
    float GroundCoordRadarRecvY;
    float GroundCoordRadarRecvZ;
    float RadarCoordOxVectorX;
    float RadarCoordOxVectorY;
    float RadarCoordOxVectorZ;
    float RadarCoordOyVectorX;
    float RadarCoordOyVectorY;
    float RadarCoordOyVectorZ;
    float TargetCoordOxVectorX;
    float TargetCoordOxVectorY;
    float TargetCoordOxVectorZ;
    float TargetCoordOyVectorX;
    float TargetCoordOyVectorY;
    float TargetCoordOyVectorZ;
}RangeSpreadTargetParam2;

//--------干扰参数----------------------
//--无干扰--
typedef struct
{
    unsigned int  JammingFrameId;
}JammingNoJam;
/* 间歇采样转发式干扰 */
typedef struct
{
    float	Distance;
    float	Speed;
    float	Theta;
    float	Phi;
    float	Power;
    float	SampleWidth;
    float	RepeatWidth;
    float	RepeatStartTime;
    float	RepeatNum;
}JammingIsrjParam0;

typedef struct
{
    float	Speed;
    float	Power;
    float	GroundCoordJammingX;
    float	GroundCoordJammingY;
    float	GroundCoordJammingZ;
    float	SampleWidth;
    float	RepeatWidth;
    float	RepeatStartTime;
    float	RepeatNum;
}JammingIsrjParam1;

/* 目标参数回传 */
typedef struct
{
    float	RangeProfile[RANGE_PROFILE_NUM];
}RangeSpreadTargetParam0SetBack;

typedef struct
{
    float	TargetDistanceTran;
    float	TargetDistanceRecv;
    float	RangeProfile[RANGE_PROFILE_NUM];
    float	LineDeviationTheta;
    float	LineDeviationPhi;
    float	AngleDeviationTheta;
    float	AngleDeviationPhi;
}RangeSpreadTargetParam12SetBack;

/* 网口帧  */
typedef struct
{
    int		FrameId;
    int		TargetFrameId;
    union
    {
        PointTargetParam 		TargetParam0Data;
        RangeSpreadTargetParam0	RangeSpreadTargetParam0Data;
        RangeSpreadTargetParam1	RangeSpreadTargetParam1Data;
        RangeSpreadTargetParam2	RangeSpreadTargetParam2Data;
    }TargetFrame;
    int		JammingFrameId;
    union
    {
        JammingIsrjParam0		JammingIsrjParam0Data;
        JammingIsrjParam1		JammingIsrjParam1Data;
    }JammingFrame;
    float	NoisePower;
}WorkParamUdpFrame;

/* 网口工作参数设置回传数据 */
typedef struct
{
    int 	FrameId;
    int 	TargetFrameId;
    union	WorkParamSetBack
    {
        char	PointTargetBack;
        RangeSpreadTargetParam0SetBack	RangeSpreadTargetParam0SetBackFrame;
        RangeSpreadTargetParam12SetBack	RangeSpreadTargetParam12SetBackFrame;
    }TargetParamBack;
    int 	JammingFrameId;
    union
    {
        char	NoJammingBack;
        char	IsrjParam0Back;
    }JammingParamBack;
}WorkParamSetBack;



/* 散射点结构体 */
typedef struct
{
    float	X;
    float	Y;
    float	Z;
    float	RCS;
}Point;

typedef struct
{
    int		PointNum;
    Point	PointData[1024];	//最大散射点数
}ScatteringPoint;

/* 散射点信息导入帧 */
typedef struct
{
    int   			FrameId;
    ScatteringPoint	ScatteringPointData;
}ScatteringPointUdpFrame;



void ScatteringPointAngleCalculate(float GroundToTargetAnglePhi, float GroundToTargetAngleTheta, float GroundToTargetAngleGamma,
                              float GroundToRadarAnglePhi, float GroundToRadarAngleTheta, float GroundToRadarAngleGamma,
                              float TargetAngleTheta, float TargetAnglePhi,
                              float &TargetThetaY, float &TargetPhiY, float &TargetThetaZ, float &TargetPhiZ);

void CoordinateCalculateOriginToTrans(float OriginToTransAnglePhi, float OriginToTransAngleTheta, float OriginToTransAngleGamma,
                                   float OriginalX, float OriginalY, float OriginalZ,
                                   float &TransX, float &TransY, float &TransZ);

void CoordinateCalculateTransToOrigin(float TransToOriginAnglePhi, float TransToOriginAngleTheta, float TransToOriginAngleGamma,
                                   float OriginalX, float OriginalY, float OriginalZ,
                                   float &TransX, float &TransY, float &TransZ);

void CoordinateCalRectToSphere(float RectX, float RectY, float RectZ, float &Theta, float &Phi);

#endif // SIMULATOR_GUI

