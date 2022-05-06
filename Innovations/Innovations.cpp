// Innovations_3.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "Innovations.h"
#include "Algorithm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CInnovations_App, CWinApp)
END_MESSAGE_MAP()

CInnovations_App::CInnovations_App()
{
    // TODO: �ڴ˴���ӹ�����룬
    // ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

CInnovations_App theApp;


// CInnovations_App ��ʼ��

BOOL CInnovations_App::InitInstance()
{
    CWinApp::InitInstance();

    return TRUE;
}

//����һ���㷨���󣬲������㷨����ָ��
void *LtCreateObject()
{
    CAlgorithm *pAlgorithm = new CAlgorithm();
    pAlgorithm->Create(IDD_DIALOG1,NULL);
    return static_cast<void*>( pAlgorithm );
}

//ɾ��һ���㷨���󣬴˺����ڴ��Ĳ�����pObject������LtCreateObject()�ķ���ֵ
void LtDestroyObject( void * pObject )
{
    ASSERT( pObject != NULL );
    ASSERT( !IsBadWritePtr( pObject, sizeof(CAlgorithm) ) );
    CAlgorithm * pAlgorithm = static_cast<CAlgorithm *>( pObject );
    pAlgorithm->DestroyWindow();
    delete pAlgorithm;	//ɾ��һ���㷨����
}

void LtResetModule(void *pObject, const float *InitParam)
{
    ASSERT( pObject != NULL );
    ASSERT( !IsBadWritePtr( pObject, sizeof(CAlgorithm) ) );
    CAlgorithm * pAlgorithm = static_cast<CAlgorithm *>( pObject );
    pAlgorithm->Reset(InitParam);
}

//CVSD����ģ��(ϵͳʵ��)
//InitParam[0] �����ź�����
//InitParam[1] �������(�������ã���Χ0~30,Ĭ��ֵ20)
//InitParam[2] ��С����(�������ã���Χ0~1,Ĭ��ֵ0.01)
//InitParam[3] ���ڻ���ʱ��(�������ã���Χ0~1,Ĭ��ֵ0.98)
//InitParam[4] �ع�����ʱ��(�������ã���Χ0~1,Ĭ��ֵ0.96)
//pdInput      ��������
//InputSize    �������ݴ�С
//OutputSize   ������ݴ�С
//OutputRate   ����ź�����
//pdOutput     �����������
void LtDLLMain(void * pObject, const float *InitParam, const float *pdInput, const int InputSize,
               int& OutputSize, float& OutputRate, float **pdOutput)
{
    ASSERT( pObject != NULL );
    CAlgorithm * pAlgorithm = static_cast<CAlgorithm *>( pObject );
    pAlgorithm->RunAlgorithm(InitParam, pdInput, InputSize,
                             OutputSize, OutputRate, pdOutput);
}

//��ʾ�㷨��������(�����㷨�����Ǽ̳���CDialog��,�����д�˺���)
void LtShowWindow( void * pObject )
{
    ASSERT( pObject != NULL );
    ASSERT( !IsBadWritePtr( pObject, sizeof(CAlgorithm) ) );
    CAlgorithm * pAlgorithm = static_cast<CAlgorithm *>( pObject );
    pAlgorithm->ShowWindow( SW_SHOW );
}