/***********************
*!!!!!!!!!!!!!!!!!!!!!!*
*!!!!Do not Modify!!!!!*
*!!!!!!!!!!!!!!!!!!!!!!*
************************
*�����Ҫ�޸��κ���ش��룬������ʲô���飬���ύ��
*https://github.com/zpublic/zpublic
********************************************************/
#pragma once

/*

//////////////////////////////////////////////////////////////////////////

�������COM�Ľӿڵ�������Ҫ����������

//////////////////////////////////////////////////////////////////////////

(1)
ZL_BEGIN_COM_MAP( CXXX )
    ZL_COM_INTERFACE_ENTRY( IXXX )
    ��
    ZL_COM_INTERFACE_ENTRY_IID( IXXX )
ZL_END_COM_MAP()

����ʵ��IUnknown:
�������Ҫ���뵽��ʵ�ֽӿڵ�������, ����ʵ��IUnknown��3���麯��,

��:
����ӿ���������:
struct __declspec( uuid( "7CCB588B-6746-47f4-9509-DDF3A4637A63" ) )
ICompute: public IUnknown
{
public:
virtual int __stdcall Add( int a, int b ) = 0;
virtual int __stdcall Sub( int a, int b ) = 0;
};
���ʵ��: (ֻ��Ҫʵ����Ҫ�Ľӿ�, �ټ�������, ����ʵ��IUnknown)
class KCompute : public ICompute
{
public:
    virtual int __stdcall Add( int a, int b )
    {
        return a + b;
    }
    virtual int __stdcall Sub( int a, int b )
    {
        return a - b;
    }
    ZL_BEGIN_COM_MAP( KCompute )
        ZL_COM_INTERFACE_ENTRY( ICompute )
    ZL_END_COM_MAP()
};

//////////////////////////////////////////////////////////////////////////

(2)
ZL_BEGIN_OBJECT_MAP()
    ZL_OBJECT_ENTRY( IXXX, CXXX )
ZL_END_OBJECT_MAP()

DllGetClassObject��ʵ��
���ǵļ�COM�淶��ʹ��CLSID, ��ʹ���೧, ֻ��Ҫͨ��һ���ӿ�ID��DLL�д���
��ʵ��, ���ӿ�ID���䴴����ʵ���Ķ�Ӧ��ϵ��Ҫ�������ָ��:

��:
ZL_BEGIN_OBJECT_MAP()
    ZL_OBJECT_ENTRY( ICompute, KCompute )
ZL_END_OBJECT_MAP()

//////////////////////////////////////////////////////////////////////////

(3)
ZL_USE_DEFAULT_COM_PROC
��
ZL_USE_DEFAULT_COM_PROCEX

ǰ��ʵ���� DllCanUnloadNow �� DllGetClassObject, 
����ʵ���� DllCanUnloadNow �� DllGetClassObject �� DllMain
ʡȥ���ֹ�д��д����.

��Ҳ���Բ�ʹ����������, �Լ�ʵ����������

//////////////////////////////////////////////////////////////////////////

���, ��Ҫ����д.def�ļ�
LIBRARY      "xxxmodule"
EXPORTS
DllGetClassObject   PRIVATE
DllCanUnloadNow     PRIVATE

*/

#include "export/z_com_dll_object.hpp"
#include "export/z_com_dll_module.hpp"


//////////////////////////////////////////////////////////////////////////

#define ZL_BEGIN_COM_MAP( CComImpl ) HRESULT _InternalQueryInterface( REFIID riid, void **ppvObject ) { \
    if( ppvObject == NULL ) return E_INVALIDARG; \
    HRESULT hr = E_FAIL; \
    if( false) {}

#define ZL_COM_INTERFACE_ENTRY( I ) 	 else if( riid == __uuidof( I ) || riid == IID_IUnknown ) { \
    *ppvObject = static_cast<I*>(this); \
    hr = S_OK; } 

#define ZL_COM_INTERFACE_ENTRY_IID( I )  else if( riid == IID_##I || riid == IID_IUnknown ) { \
    *ppvObject = static_cast<I*>(this); \
    hr = S_OK; } 

#define ZL_END_COM_MAP()  else { \
    *ppvObject = NULL; \
    hr = E_NOINTERFACE; } \
    return hr; }

//////////////////////////////////////////////////////////////////////////

#define ZL_BEGIN_OBJECT_MAP() HRESULT ZL_DllGetClassObject( REFIID riid, LPVOID* ppv ){ \
    if( ppv == NULL ) return E_INVALIDARG;

#define ZL_OBJECT_ENTRY( IXXX, CXXX ) if( riid == __uuidof( IXXX ) ){ \
    IXXX* pI = new ZLComDllObject<CXXX>; \
    if( pI == NULL ) return E_OUTOFMEMORY; \
    pI->AddRef(); \
    *ppv = pI; \
    return S_OK; }

#define ZL_OBJECT_ENTRY_IID( IXXX, CXXX ) if( riid == IID_##IXXX ) ){ \
    IXXX* pI = new ZLComDllObject<CXXX>; \
    if( pI == NULL ) return E_OUTOFMEMORY; \
    pI->AddRef(); \
    *ppv = pI; \
    return S_OK; }

#define ZL_END_OBJECT_MAP() *ppv = NULL; \
    return E_NOINTERFACE; }

//////////////////////////////////////////////////////////////////////////

#define ZL_USE_DEFAULT_COM_PROC  ZLComDllModule _Module; \
    STDAPI  DllCanUnloadNow(void){  \
    return _Module.DllCanUnloadNow();}  \
    STDAPI  DllGetClassObject(IN REFCLSID rclsid, IN REFIID riid, OUT LPVOID FAR* ppv){  \
    return _Module.DllGetClassObject( rclsid, riid, ppv );}


#define ZL_USE_DEFAULT_COM_PROCEX    ZL_USE_DEFAULT_COM_PROC \
    BOOL APIENTRY DllMain( HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved){ \
    if( ul_reason_for_call == DLL_PROCESS_ATTACH ) _Module.Init( hModule ); \
    return TRUE; }
