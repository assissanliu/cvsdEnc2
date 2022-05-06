// Innovations_3.cpp : 定义 DLL 的初始化例程。
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
    // TODO: 在此处添加构造代码，
    // 将所有重要的初始化放置在 InitInstance 中
}

CInnovations_App theApp;


// CInnovations_App 初始化

BOOL CInnovations_App::InitInstance()
{
    CWinApp::InitInstance();

    return TRUE;
}

//创建一个算法对象，并返回算法对象指针
void *LtCreateObject()
{
    CAlgorithm *pAlgorithm = new CAlgorithm();
    pAlgorithm->Create(IDD_DIALOG1,NULL);
    return static_cast<void*>( pAlgorithm );
}

//删除一个算法对象，此函数期待的参数（pObject）正是LtCreateObject()的返回值
void LtDestroyObject( void * pObject )
{
    ASSERT( pObject != NULL );
    ASSERT( !IsBadWritePtr( pObject, sizeof(CAlgorithm) ) );
    CAlgorithm * pAlgorithm = static_cast<CAlgorithm *>( pObject );
    pAlgorithm->DestroyWindow();
    delete pAlgorithm;	//删除一个算法对象
}

void LtResetModule(void *pObject, const float *InitParam)
{
    ASSERT( pObject != NULL );
    ASSERT( !IsBadWritePtr( pObject, sizeof(CAlgorithm) ) );
    CAlgorithm * pAlgorithm = static_cast<CAlgorithm *>( pObject );
    pAlgorithm->Reset(InitParam);
}

//CVSD编码模块(系统实验)
//InitParam[0] 输入信号速率
//InitParam[1] 最大量阶(界面设置，范围0~30,默认值20)
//InitParam[2] 最小量阶(界面设置，范围0~1,默认值0.01)
//InitParam[3] 音节积分时间(界面设置，范围0~1,默认值0.98)
//InitParam[4] 重构积分时间(界面设置，范围0~1,默认值0.96)
//pdInput      输入数据
//InputSize    输入数据大小
//OutputSize   输出数据大小
//OutputRate   输出信号速率
//pdOutput     编码数据输出
void LtDLLMain(void * pObject, const float *InitParam, const float *pdInput, const int InputSize,
               int& OutputSize, float& OutputRate, float **pdOutput)
{
    ASSERT( pObject != NULL );
    CAlgorithm * pAlgorithm = static_cast<CAlgorithm *>( pObject );
    pAlgorithm->RunAlgorithm(InitParam, pdInput, InputSize,
                             OutputSize, OutputRate, pdOutput);
}

//显示算法操作界面(仅当算法对象是继承自CDialog类,才需编写此函数)
void LtShowWindow( void * pObject )
{
    ASSERT( pObject != NULL );
    ASSERT( !IsBadWritePtr( pObject, sizeof(CAlgorithm) ) );
    CAlgorithm * pAlgorithm = static_cast<CAlgorithm *>( pObject );
    pAlgorithm->ShowWindow( SW_SHOW );
}