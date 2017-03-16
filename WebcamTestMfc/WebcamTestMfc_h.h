

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Mar 16 16:09:46 2017
 */
/* Compiler settings for WebcamTestMfc.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __WebcamTestMfc_h_h__
#define __WebcamTestMfc_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IWebcamTestMfc_FWD_DEFINED__
#define __IWebcamTestMfc_FWD_DEFINED__
typedef interface IWebcamTestMfc IWebcamTestMfc;

#endif 	/* __IWebcamTestMfc_FWD_DEFINED__ */


#ifndef __WebcamTestMfc_FWD_DEFINED__
#define __WebcamTestMfc_FWD_DEFINED__

#ifdef __cplusplus
typedef class WebcamTestMfc WebcamTestMfc;
#else
typedef struct WebcamTestMfc WebcamTestMfc;
#endif /* __cplusplus */

#endif 	/* __WebcamTestMfc_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __WebcamTestMfc_LIBRARY_DEFINED__
#define __WebcamTestMfc_LIBRARY_DEFINED__

/* library WebcamTestMfc */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_WebcamTestMfc;

#ifndef __IWebcamTestMfc_DISPINTERFACE_DEFINED__
#define __IWebcamTestMfc_DISPINTERFACE_DEFINED__

/* dispinterface IWebcamTestMfc */
/* [uuid] */ 


EXTERN_C const IID DIID_IWebcamTestMfc;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("7523AA71-9DE0-45F9-AF43-80CC3BD22E4A")
    IWebcamTestMfc : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IWebcamTestMfcVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWebcamTestMfc * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWebcamTestMfc * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWebcamTestMfc * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWebcamTestMfc * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWebcamTestMfc * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWebcamTestMfc * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWebcamTestMfc * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IWebcamTestMfcVtbl;

    interface IWebcamTestMfc
    {
        CONST_VTBL struct IWebcamTestMfcVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebcamTestMfc_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWebcamTestMfc_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWebcamTestMfc_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWebcamTestMfc_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWebcamTestMfc_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWebcamTestMfc_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWebcamTestMfc_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IWebcamTestMfc_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_WebcamTestMfc;

#ifdef __cplusplus

class DECLSPEC_UUID("C0B4B066-DF21-4C5D-AF65-28C799EEEF82")
WebcamTestMfc;
#endif
#endif /* __WebcamTestMfc_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


