// ObjCombOpt.h: interface for the ObjCombOpt class.
//
//////////////////////////////////////////////////////////////////////
#pragma once
#include "fstream.h"
#include "math.h"
#include "OPTCtrlDLL.h"  // 定义了OPTTag类

const int NumModInp=18; //width of x_train   MODIFY
const int NumSupVec=500;
const int length=1;  //数据处理窗口长度
const int NumAlfa=501;  //支持向量个数 500 alpha and 1 belta
const int Comb_OpN=371;  //OP number
const int COM_ION=470;  //IO number
const int DCS_ION=292;  //IO number
const int READ_NUM=240;  //共享内存方式READ数据
const int WRITE_NUM=110;  //共享内存方式WRITE数据

const int StateParamStarNum=348;
/*
#define NumSupVec 500  //支持向量个数
#define length 20  //数据处理窗口长度
#define NumAlfa 501  //支持向量个数 500 alpha and 1 belta
#define Comb_OpN 348  //OP number
#define Comb_ION 292  //IO number
// #define ZZ_Width 9 //奇数,中值滤波窗口宽度
*/

#if !defined(AFX_OBJCOMBOPT_H__81076574_F823_4E26_9A7E_213011FD193E__INCLUDED_)
#define AFX_OBJCOMBOPT_H__81076574_F823_4E26_9A7E_213011FD193E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// 该类中存储进程所需数据以及转换函数
// COM接口数据
// IO，Op，模型从txt导入数
//IOTag，OpTag
class ObjCombOpt
{

public:
    // IO，Op，模型参数 从txt导入数，这里所有变量取为MATLAB中的转置
	double X_NOx1[NumModInp][NumSupVec], Y_NOx1[1][NumSupVec], Alfa_NOx1[1][NumAlfa], H_NOx1[NumSupVec][NumSupVec];

	double X_NOx2[NumModInp][NumSupVec], Y_NOx2[1][NumSupVec], Alfa_NOx2[1][NumAlfa], H_NOx2[NumSupVec][NumSupVec];
	double X_NOx3[NumModInp][NumSupVec], Y_NOx3[1][NumSupVec], Alfa_NOx3[1][NumAlfa], H_NOx3[NumSupVec][NumSupVec];

	double X_Etem1[NumModInp][NumSupVec], Y_Etem1[1][NumSupVec], Alfa_Etem1[1][NumAlfa], H_Etem1[NumSupVec][NumSupVec];
	double X_Etem2[NumModInp][NumSupVec], Y_Etem2[1][NumSupVec], Alfa_Etem2[1][NumAlfa], H_Etem2[NumSupVec][NumSupVec];
	double X_Etem3[NumModInp][NumSupVec], Y_Etem3[1][NumSupVec], Alfa_Etem3[1][NumAlfa], H_Etem3[NumSupVec][NumSupVec];

	double X_Rtem1[NumModInp][NumSupVec], Y_Rtem1[1][NumSupVec], Alfa_Rtem1[1][NumAlfa], H_Rtem1[NumSupVec][NumSupVec];
	double X_Rtem2[NumModInp][NumSupVec], Y_Rtem2[1][NumSupVec], Alfa_Rtem2[1][NumAlfa], H_Rtem2[NumSupVec][NumSupVec];
	double X_Rtem3[NumModInp][NumSupVec], Y_Rtem3[1][NumSupVec], Alfa_Rtem3[1][NumAlfa], H_Rtem3[NumSupVec][NumSupVec];
	double ListError_NOx[1][length],ListError_Rtem[1][length],ListError_Etem[1][length];

	double Op[Comb_OpN];  // model param in COM (model compiled with matlab)
    double IO[COM_ION];  // comunication bt database and COM

    //OPTTag Op_tag[Comb_OpN];
    //OPTTag IO_tag[COM_ION];

	BOOL bSetPara;
	BOOL CombState;  // 控制投入状态：0 为跟踪 1为控制


    // COM组件接口数据
	VARIANT mIO,mtIO,mOp;
	VARIANT mtX_NOx1,mtY_NOx1,mtAlfa_NOx1,mtH_NOx1;
	VARIANT mtX_NOx2,mtY_NOx2,mtAlfa_NOx2,mtH_NOx2;
	VARIANT mtX_NOx3,mtY_NOx3,mtAlfa_NOx3,mtH_NOx3;

	VARIANT mtX_Etem1,mtY_Etem1,mtAlfa_Etem1,mtH_Etem1;
	VARIANT mtX_Etem2,mtY_Etem2,mtAlfa_Etem2,mtH_Etem2;
	VARIANT mtX_Etem3,mtY_Etem3,mtAlfa_Etem3,mtH_Etem3;

	VARIANT mtX_Rtem1,mtY_Rtem1,mtAlfa_Rtem1,mtH_Rtem1;
	VARIANT mtX_Rtem2,mtY_Rtem2,mtAlfa_Rtem2,mtH_Rtem2;
	VARIANT mtX_Rtem3,mtY_Rtem3,mtAlfa_Rtem3,mtH_Rtem3;

	VARIANT mX_NOx1,mY_NOx1,mAlfa_NOx1,mH_NOx1;
	VARIANT mX_NOx2,mY_NOx2,mAlfa_NOx2,mH_NOx2;
	VARIANT mX_NOx3,mY_NOx3,mAlfa_NOx3,mH_NOx3;

	VARIANT mX_Etem1,mY_Etem1,mAlfa_Etem1,mH_Etem1;
	VARIANT mX_Etem2,mY_Etem2,mAlfa_Etem2,mH_Etem2;
	VARIANT mX_Etem3,mY_Etem3,mAlfa_Etem3,mH_Etem3;

	VARIANT mX_Rtem1,mY_Rtem1,mAlfa_Rtem1,mH_Rtem1;
	VARIANT mX_Rtem2,mY_Rtem2,mAlfa_Rtem2,mH_Rtem2;
	VARIANT mX_Rtem3,mY_Rtem3,mAlfa_Rtem3,mH_Rtem3;

	VARIANT mListError_NOx,mListError_Etem,mListError_Rtem;
	VARIANT mtListError_NOx,mtListError_Etem,mtListError_Rtem;	


	void LoadCombData_fg(CString fOp,\
						 CString fX_NOx1,CString fY_NOx1,CString fAlfa_NOx1,CString fH_NOx1,\
						 CString fX_NOx2,CString fY_NOx2,CString fAlfa_NOx2,CString fH_NOx2,\
						 CString fX_NOx3,CString fY_NOx3,CString fAlfa_NOx3,CString fH_NOx3,\
						 CString fX_Etem1,CString fY_Etem1,CString fAlfa_Etem1,CString fH_Etem1,\
						 CString fX_Etem2,CString fY_Etem2,CString fAlfa_Etem2,CString fH_Etem2,\
						 CString fX_Etem3,CString fY_Etem3,CString fAlfa_Etem3,CString fH_Etem3,\
						 CString fX_Rtem1,CString fY_Rtem1,CString fAlfa_Rtem1,CString fH_Rtem1,\
						 CString fX_Rtem2,CString fY_Rtem2,CString fAlfa_Rtem2,CString fH_Rtem2,\
						 CString fX_Rtem3,CString fY_Rtem3,CString fAlfa_Rtem3,CString fH_Rtem3);


	void Init_Op_tag(CString fOp);

	void ReSetPara(CString fOp);
	void MapToTag(void);
	ObjCombOpt();
	virtual ~ObjCombOpt();

};

#endif // !defined(AFX_OBJCOMBOPT_H__81076574_F823_4E26_9A7E_213011FD193E__INCLUDED_)
