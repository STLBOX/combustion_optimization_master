// ObjCombOpt.cpp: implementation of the ObjCombOpt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ObjCombOpt.h"
#include "InterfaceDlg.h"

extern CInterfaceDlg* dp;


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

void ObjCombOpt::Init_Op_tag(CString fOp)
{
	//  txt init OP_tag
	fstream inOp(fOp,ios::in);  
	int i=0; 
	for(i=0;i<Comb_OpN;i++)
	{
		inOp>>Op[i]; 
		dp->pCombOptOP[i]=Op[i];
	}
	inOp.close();
}


void ObjCombOpt::MapToTag(void)
{
	CString Op_str[Comb_OpN]={"P","M","Ts","delta_NOx","C_NOx","NumSupVec_NOx","delta_Etem","C_Etem","NumSupVec_Etem","delta_Rtem","C_Rtem","NumSupVec_Rtem",
		"upLimit_Nox","upLimit_Rtem","downLimit_Rtem","PermitErr_NOx","PermitErr_Etem","PermitErr_Rtem","MinDampOpen","u_SOFA123","u_SOFA456",
		"u_AASecAir","u_ASecAir","u_ABSecAir","u_BABCSecAir","u_BSecAir","u_CBCCSecAir","u_CSecAir","u_DDDESecAir","u_DSecAir","u_EDEFSecAir",
		"u_ESecAir","u_FEFFSecAir","u_FSecAir","u_O2","u_AMillBias","u_BMillBias","u_CMillBias","u_DMillBias","u_EMillBias","u_FMillBias",
		"I_SOFA123","I_SOFA456","I_ASecAir","I_BSecAir","I_CSecAir","I_DSecAir","I_ESecAir","I_FSecAir","I_AASecAir","I_ABSecAir","I_BABCSecAir",
		"I_CBCCSecAir","I_DDDESecAir","I_EDEFSecAir","I_FEFFSecAir","I_O2","I_AMillBias","I_BMillBias","I_CMillBias","I_DMillBias","I_EMillBias",
		"I_FMillBias","lim_dSOFA123","lim_dSOFA456","lim_dASecAir","lim_dBSecAir","lim_dCSecAir","lim_dDSecAir","lim_dESecAir","lim_dFSecAir",
		"lim_dAASecAir","lim_dABSecAir","lim_dBABCSecAir","lim_dCBCCSecAir","lim_dDDDESecAir","lim_dEDEFSecAir","lim_dFEFFSecAir","lim_dO2",
		"lim_dAMillBias","lim_dBMillBias","lim_dCMillBias","lim_dDMillBias","lim_dEMillBias","lim_dFMillBias","dZ_SOFA123","dZ_SOFA456","dZ_ASecAir",
		"dZ_BSecAir","dZ_CSecAir","dZ_DSecAir","dZ_ESecAir","dZ_FSecAir","dZ_AASecAir","dZ_ABSecAir","dZ_BABCSecAir","dZ_CBCCSecAir","dZ_DDDESecAir",
		"dZ_EDEFSecAir","dZ_FEFFSecAir","dZ_O2","dZ_AMillBias","dZ_BMillBias","dZ_CMillBias","dZ_DMillBias","dZ_EMillBias","dZ_FMillBias","min_Fuel",
		"min_SecAir","min_SOFA","min_O2","min_Load","min_NOx","min_Etem","min_Rtem","max_Fuel","max_SecAir","max_SOFA","max_O2","max_Load","max_NOx","max_Etem",
		"max_Rtem","r_SOFA123","r_SOFA456","r_ASecAir","r_BSecAir","r_CSecAir","r_DSecAir","r_ESecAir","r_FSecAir","r_AASecAir","r_ABSecAir","r_BABCSecAir",
		"r_CBCCSecAir","r_DDDESecAir","r_EDEFSecAir","r_FEFFSecAir","r_O2","r_AMillBias","r_BMillBias","r_CMillBias","r_DMillBias","r_EMillBias","r_FMillBias",
		"OFA_x1","OFA_y1","OFA_x2","OFA_y2","OFA_x3","OFA_y3","OFA_x4","OFA_y4","OFA_x5","OFA_y5","OFA_x6","OFA_y6","SEC_x1","SEC_y1","SEC_x2","SEC_y2","SEC_x3","SEC_y3",
		"SEC_x4","SEC_y4","O_x1","O_y1","O_x2","O_y2","O_x3","O_y3","O_x4","O_y4","O_x5","O_y5","L_CO","thr_CO","L_NOx","thr_NOx","qn","qe","qt","MaxFunEvals","MaxNumCRenew",
		"Isrecord","m_CombOpt_Coef1","m_CombOpt_Coef2","m_CombOpt_Coef3","m_CombOpt_Coef4","m_CombOpt_Coef5","m_CombOpt_Coef6","m_CombOpt_deltaU1",
		"m_CombOpt_deltaU2","m_CombOpt_deltaU3","m_CombOpt_deltaU4","m_CombOpt_deltaU5","m_CombOpt_deltaU6","ErrorNum_NOx","ErrorNum_BoiEff",
		"ErrorNum_Tem","L_Rtem","L_Etem","L_Cfh","thr_Rtem","thr_Etem","thr_Cfh","norm_limit_Fp","u_Fp","l_Fp","lim_rFp","dz_Fp","dzl_Fp","al_Fp","au_Fp","w_Fp",	
		"bias_O2","bias_Amill","bias_B","bias_C","bias_D","bias_E","bias_F","Al_SOFA123","Al_SOFA456","Al_AASecAir",
		"Al_ASecAir","Al_ABSecAir","Al_BABCSecAir","Al_BSecAir","Al_CBCCSecAir","Al_CSecAir","Al_DDDESecAir","Al_DSecAir","Al_EDEFSecAir","Al_ESecAir",
		"Al_FEFFSecAir","Al_FSecAir","Al_O2","Al_AMillBias","Al_BMillBias","Al_CMillBias","Al_DMillBias","Al_EMillBias","Al_FMillBias","Au_SOFA123",
		"Au_SOFA456","Au_AASecAir","Au_ASecAir","Au_ABSecAir","Au_BABCSecAir","Au_BSecAir","Au_CBCCSecAir","Au_CSecAir","Au_DDDESecAir","Au_DSecAir",
		"Au_EDEFSecAir","Au_ESecAir","Au_FEFFSecAir","Au_FSecAir","Au_O2","Au_AMillBias","Au_BMillBias","Au_CMillBias","Au_DMillBias","Au_EMillBias",
		"Au_FMillBias","upLimit_NOx2","upLimit_NOx3","HC_State","HC_O2_State","HC_Air_State","HC_Bias_State","HC_O2_C","HC_Air_C","HC_Bias_C","HC_MaxOptNum",
		"HC_t","min_Damper","max_Damper","factor_Damper","K_Alfa","AirWeight","SupTem_Kp","SupTem_Ki","CO_Kp","CO_Ki","PI_max_CO","PI_min_CO","Load_Change",
		"Coal_Change","Imax_blower","COALmax_mill","flag_sim","delta_cfh","C_cfh","NumSupVec_cfh","PermitErr_cfh","max_Iblower","min_Iblower","qI","a_Iblower",
		"b_Iblower","c_Iblower","max_coalneed","min_coalneed","Delta_Nox1","Delta_Nox2","Delta_Nox3","C_Nox1","C_Nox2","C_Nox3","Delta_Etem1","Delta_Etem2",
		"Delta_Etem3","C_Etem1","C_Etem2","C_Etem3","Delta_Rtem1","Delta_Rtem2","Delta_Rtem3","C_Rtem1","C_Rtem2","C_Rtem3","Delta_Cfh1","Delta_Cfh2","Delta_Cfh3",
		"C_Cfh1","C_Cfh2","C_Cfh3","Nox_rate_limit","Etem_rate_limit","Rtem_rate_limit","Cfh_rate_limit","norm_limit_Load","norm_limit_O2","norm_limit_Fuel",
		"norm_limit_Sec","norm_limit_Sofa","norm_limit_Nox","norm_limit_Etem","norm_limit_Rtem","norm_limit_Cfh","dzl_Sofa","dzl_Sec","dzl_O2","dzl_Fuel",
		"bSetPara","CombState","P_Nox_k","P_Etem_k","P_Rtem_k","NumCRenew_Nox","NumCRenew_Etem","NumCRenew_Rtem","e_NOx_k","e_Etem_k","e_Rtem_k","COMState","CombOptState",
	    "ModelState","OptCalState","ManSaveModParam","SaveIOData","TDIState","P_CO_k","NumCRenew_CO","e_CO_k","Filterd_CO_k","P_Smax_k","NumCRenew_Smax","e_Smax_k"};


	CString IO_str[DCS_ION]={"UK_AI0001","UK_AI0002","UK_AI0003","UK_AI0004","UK_AI0005","UK_AI0006","UK_AI0007","UK_AI0008","UK_AI0009",
		"UK_AI0010","UK_AI0011","UK_AI0012","UK_AI0013","UK_AI0014","UK_AI0015","UK_AI0016","UK_AI0017","UK_AI0018",
		"UK_AI0019","UK_AI0020","UK_AI0021","UK_AI0022","UK_AI0023","UK_AI0024","UK_AI0025","UK_AI0026","UK_AI0027",
		"UK_AI0028","UK_AI0029","UK_AI0030","UK_AI0031","UK_AI0032","UK_AI0033","UK_AI0034","UK_AI0035","UK_AI0036",
		"UK_AI0037","UK_AI0038","UK_AI0039","UK_AI0040","UK_AI0041","UK_AI0042","UK_AI0043","UK_AI0044","UK_AI0045",
		"UK_DI0001","UK_DI0002","UK_DI0003","UK_DI0004","UK_DI0005","LOAD","TOTCOAL","MSTE_FLOW","MSTE_T","MSTE_P",
		"COAL_DEM","COAL_A_BIAS_SET","COAL_B_BIAS_SET","COAL_C_BIAS_SET","COAL_D_BIAS_SET","COAL_E_BIAS_SET","COAL_F_BIAS_SET",
		"COAL_A_OPTBIAS_SET","COAL_B_OPTBIAS_SET","COAL_C_OPTBIAS_SET","COAL_D_OPTBIAS_SET","COAL_E_OPTBIAS_SET",
		"COAL_F_OPTBIAS_SET","COAL_A_FEED_SET","COAL_B_FEED_SET","COAL_C_FEED_SET","COAL_D_FEED_SET","COAL_E_FEED_SET",
		"COAL_F_FEED_SET","COAL_A_FB","COAL_B_FB","COAL_C_FB","COAL_D_FB","COAL_E_FB","COAL_F_FB","SEC_AA_BIAS_SET",
		"SEC_A_BIAS_SET","SEC_AB_BIAS_SET","SEC_BA_BIAS_SET","SEC_B_BIAS_SET","SEC_BC_BIAS_SET","SEC_CB_BIAS_SET","SEC_C_BIAS_SET",
		"SEC_CC_BIAS_SET","SEC_DD_BIAS_SET","SEC_D_BIAS_SET","SEC_DE_BIAS_SET","SEC_ED_BIAS_SET","SEC_E_BIAS_SET","SEC_EF_BIAS_SET",
		"SEC_FE_BIAS_SET","SEC_F_BIAS_SET","SEC_FF_BIAS_SET","SEC_AA_OPTBIAS_SET","SEC_A_OPTBIAS_SET","SEC_AB_OPTBIAS_SET",
		"SEC_BA_OPTBIAS_SET","SEC_B_OPTBIAS_SET","SEC_BC_OPTBIAS_SET","SEC_CB_OPTBIAS_SET","SEC_C_OPTBIAS_SET","SEC_CC_OPTBIAS_SET",
		"SEC_DD_OPTBIAS_SET","SEC_D_OPTBIAS_SET","SEC_DE_OPTBIAS_SET","SEC_ED_OPTBIAS_SET","SEC_E_OPTBIAS_SET","SEC_EF_OPTBIAS_SET",
		"SEC_FE_OPTBIAS_SET","SEC_F_OPTBIAS_SET","SEC_FF_OPTBIAS_SET","SEC_AA_SET","SEC_A_SET","SEC_AB_SET","SEC_BA_SET","SEC_B_SET",
		"SEC_BC_SET","SEC_CB_SET","SEC_C_SET","SEC_CC_SET","SEC_DD_SET","SEC_D_SET","SEC_DE_SET","SEC_ED_SET","SEC_E_SET","SEC_EF_SET",
		"SEC_FE_SET","SEC_F_SET","SEC_FF_SET","SEC_AA_FB","SEC_A_FB","SEC_AB_FB","SEC_BA_FB","SEC_B_FB","SEC_BC_FB","SEC_CB_FB","SEC_C_FB",
		"SEC_CC_FB","SEC_DD_FB","SEC_D_FB","SEC_DE_FB","SEC_ED_FB","SEC_E_FB","SEC_EF_FB","SEC_FE_FB","SEC_F_FB","SEC_FF_FB","SOFA_L11_BIAS_SET",
		"SOFA_L12_BIAS_SET","SOFA_M11_BIAS_SET","SOFA_M12_BIAS_SET","SOFA_U11_BIAS_SET","SOFA_U12_BIAS_SET","SOFA_L11_OPTBIAS_SET","SOFA_L12_OPTBIAS_SET",
		"SOFA_M11_OPTBIAS_SET","SOFA_M12_OPTBIAS_SET","SOFA_U11_OPTBIAS_SET","SOFA_U12_OPTBIAS_SET","SOFA_L11_SET","SOFA_L12_SET","SOFA_M11_SET",
		"SOFA_M12_SET","SOFA_U11_SET","SOFA_U12_SET","SOFA_L11_FB","SOFA_L12_FB","SOFA_M11_FB","SOFA_M12_FB","SOFA_U11_FB","SOFA_U12_FB",
		"O2_BIAS_SET","O2_OPTBIAS_SET","O2_SET","O2_ECO","BURNER1_BIAS_SET","BURNER2_BIAS_SET","BURNER1_OPTBIAS_SET","BURNER2_OPTBIAS_SET",
		"BURNER1_SET","BURNER2_SET","BURNER1_FB","BURNER2_FB","PRIAIR_P_BIAS_SET","PRIAIR_P_OPTBIAS_SET","PRIAIR_P_SET","PRIAIR_PIPE_P","SOFA_ANGLE_SET",
		"SOFA_ANGLE_FB","MILL_A_SPEED_SET","MILL_B_SPEED_SET","MILL_C_SPEED_SET","MILL_D_SPEED_SET","MILL_E_SPEED_SET","MILL_F_SPEED_SET",
		"MILL_A_SPEED","MILL_B_SPEED","MILL_C_SPEED","MILL_D_SPEED","MILL_E_SPEED","MILL_F_SPEED","NOx_SCR","O2_SCR","CO_SCR","AIRPREH_GAS_T1","AIRPREH_GAS_T2",
		"AIRPREH_GAS_T3","CU_FDF","CU_IDF","MILL_A_CU","MILL_B_CU","MILL_C_CU","MILL_D_CU","MILL_E_CU","MILL_F_CU","CU_PRIAIRFAN","SH_WATER_A11",
		"SH_WATER_A12","SH_WATER_B11","SH_WATER_B12","SH_WATER_A21","SH_WATER_A22","SH_WATER_B21","SH_WATER_B22","RH_T_A","RH_T_B","RH_WATER_A1",
		"RH_WATER_A2","RH_WATER_B1","RH_WATER_B2","RHSTEAM_T","GAS_T","FLYASH_Carbon_A","FLYASH_Carbon_B","PSCREEN_WALL_Tmax","PSCREEN_HEADER_Tmax",
		"VER_WW_Tmax","OPT_SWITCH","MILL_A_SWITCH","MILL_B_SWITCH","MILL_C_SWITCH","MILL_D_SWITCH","MILL_E_SWITCH","MILL_F_SWITCH","FDR_A_AUTO","FDR_B_AUTO",
		"FDR_C_AUTO","FDR_D_AUTO","FDR_E_AUTO","FDR_F_AUTO","AA_AUTO","A_AUTO","AB_AUTO","BA_AUTO","B_AUTO","BC_AUTO","CB_AUTO","C_AUTO","CC_AUTO","DD_AUTO",
		"D_AUTO","DE_AUTO","ED_AUTO","E_AUTO","EF_AUTO","FE_AUTO","F_AUTO","FF_AUTO","L11_AUTO","L12_AUTO","M11_AUTO","M12_AUTO","U11_AUTO","U12_AUTO","O2_AUTO",
		"PAF_AUTO","BURNER1_AUTO","BURNER2_AUTO","MILL_A_SE_AUTO","MILL_B_SE_AUTO","MILL_C_SE_AUTO","MILL_D_SE_AUTO","MILL_E_SE_AUTO","MILL_F_SE_AUTO","FDF_AUTO",
		"IDF_AUTO","HEART_FB"};
	/*
	for (int i=0;i<Comb_OpN;i++)
	{
		Op_tag[i]=Op_str[i];
	}
	for (i=0;i<DCS_ION;i++)
	{
		IO_tag[i]=IO_str[i];  // IO 全部初始化为0
	}	
	*/
}

void ObjCombOpt::ReSetPara(CString fOp)
{
	int i;
	fstream outOp(fOp,ios::out|ios::trunc);
	
	for(i=0;i<Comb_OpN;i++)
	{ 
		// 状态参数都为0
		if (i < 346)
			Op[i] = dp->pCombOptOP[i];
		else
			Op[i] = 0;

		outOp<<Op[i]<<endl;
	}
	
	outOp.close();
	
}

ObjCombOpt::ObjCombOpt(void)
{}


ObjCombOpt::~ObjCombOpt(void)
{}
