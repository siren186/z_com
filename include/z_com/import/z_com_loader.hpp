/*************************************************************************
 *                                                                       *
 *  I|*j^3Cl|a   "+!*%                  qt          Nd   gW              *
 *  l]{y+l?MM*  !#Wla\NNP               NW          MM   I|              *
 *        PW    ?E|    tWg              Wg  sC!     AW           ~@v~    *
 *       NC     ?M!    yN|  WW     MK   MW@K1Y%M@   RM   #Q    QP@tim    *
 *     CM|      |WQCljAE|   MD     Mg   RN     cM~  NM   WQ   MQ         *
 *    #M        aQ?         MW     M3   Mg      Q(  HQ   YR  IM|         *
 *   Dq         {Ql         MH    iMX   Mg     MM   QP   QM   Eg         *
 * !EWNaPRag2$  +M"          $WNaHaN%   MQE$%EXW    QQ   CM    %M%a$D    *
 *                                                                       *
 *               Website: https://github.com/zpublic/zpublic             *
 *                                                                       *
 ************************************************************************/
#pragma once
#include "z_com_interface_ptr.hpp"

template <typename TInterface>
class ZLComLoader
{
public:
    TInterface* GetInterface()
    {
        return (TInterface*)m_mudule;
    }

protected:
    ZLComInterfacePtr<TInterface> m_mudule;

public:
    HRESULT Initialize(LPCTSTR dllpath)
    {
        if (!dllpath)
        {
            return E_INVALIDARG;
        }

        BOOL bRet = m_mudule.LoadInterface(dllpath);
        if (!bRet)
        {
            DWORD dw = ::GetLastError();
            HRESULT hr = HRESULT_FROM_WIN32(dw);
            if (SUCCEEDED(hr))
            {
                hr = E_UNEXPECTED;
            }
            return hr;
        }
        return S_OK;
    }

    HRESULT UnInitialize()
    {
        m_mudule.Free();
        return S_OK;
    }
};
