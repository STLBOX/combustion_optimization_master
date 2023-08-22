#ifndef __OPTCTRLDLL_H
#define __OPTCTRLDLL_H

#ifdef OPTCTRLOBJ_IMPL
#define CLASS_DECL_OPTCTRLDLL   __declspec(dllexport)
#else
#define CLASS_DECL_OPTCTRLDLL   __declspec(dllimport)
#endif

class CLASS_DECL_OPTCTRLDLL OPTTag
{ 
public:
	OPTTag();
	OPTTag(CString tag);

public:
	operator double();
	operator int();
	operator CString();
	double operator=(double d);
	CString operator=(CString tag);
	
	CString GetDesc();
	void SetScale(double minv,double maxv);
	void GetScale(double&minv,double&maxv);

private:
	CString m_strTag;
	void*m_pTag;
};

#ifdef __cplusplus
extern "C" {
#endif // __cpluspl	

	void* APIENTRY InitClnt();
	void APIENTRY CloseClnt();

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
