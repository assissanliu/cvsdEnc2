#include "StdAfx.h"
#include "Algorithm.h"
#include "Innovations.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CAlgorithm, CDialog)

CAlgorithm::CAlgorithm(CWnd* pParent /*=NULL*/)
           : CDialog(IDD_DIALOG1, pParent)
{
}

CAlgorithm::~CAlgorithm()
{
}

void CAlgorithm::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAlgorithm, CDialog)
    ON_BN_CLICKED(IDOK, &CAlgorithm::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &CAlgorithm::OnBnClickedCancel)
    ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

void CAlgorithm::Reset(const float *InitParam)
{
    //数据抽取计数
    m_extraCnt = 0.0;
    //CVSD初始化
    m_CVSD.init();
    //缓存初始化
    m_OutputBuf.clear();
}

//总函数
void CAlgorithm::RunAlgorithm(const float *InitParam, const float *pdInput, const int InputSize,
                             int& OutputSize, float& OutputRate, float **pdOutput)
{
    //参数传递
    float inputRate  = InitParam[0];  //输入参数
    float maxStep    = InitParam[1];  //最大量阶(界面设置，范围0~30,默认值20)
    float minStep    = InitParam[2];  //最小量阶(界面设置，范围0~1,默认值0.01)
    float sylIntTau  = InitParam[3];  //音节积分时间(界面设置，范围0~1,默认值0.98)
    float recIntTau  = InitParam[4];  //重构积分时间(界面设置，范围0~1,默认值0.96)
    float codeRateHz = InitParam[5];  //编码速率
    //CVSD更新参数
    m_CVSD.paraUpdate(maxStep, minStep, sylIntTau, recIntTau);
 
    //输出频率
    OutputRate = 32e3;

    //数据抽取及CVSD编码
    m_OutputBuf.resize(0);
    for (int idx = 0;idx < InputSize;idx++)
    {
        m_extraCnt = m_extraCnt+double(OutputRate) / double(inputRate);
        if (m_extraCnt >= 1.0)
        {
            m_extraCnt = m_extraCnt-1.0;
            int   encDateOut  = 0;
            float encQuanOut  = 0.0f;
            float pulseOut    = 0.0f;
            float quanStepOut = 0.0f;
            m_CVSD.enc(pdInput[idx], encDateOut, encQuanOut, pulseOut, quanStepOut);
            m_OutputBuf.push_back(3.3f*encDateOut);
        }
    }
    //输出大小
    OutputSize = int(m_OutputBuf.size());
    //端口输出
    if (OutputSize > 0)
    {
        *pdOutput = &m_OutputBuf[0];
    }
}

//界面控制
void CAlgorithm::OnBnClickedOk()
{
    ShowWindow(SW_HIDE);
}

void CAlgorithm::OnBnClickedCancel()
{
    ShowWindow(SW_HIDE);
}

void CAlgorithm::OnEnChangeEdit()
{
    ShowWindow(SW_HIDE);
}

void CAlgorithm::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CDialog::OnShowWindow(bShow, nStatus);
    if (bShow)
    {
        CString value2str;
    }
}

BOOL CAlgorithm::OnInitDialog()
{
    CDialog::OnInitDialog();
    return TRUE;
}
