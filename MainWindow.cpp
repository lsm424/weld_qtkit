#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QSplitter>
#include <QWindow>
#include <QSqlDatabase>
#include "config.h"

#include "InsertPathDlg.h"
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP
#define ELPP_THREAD_SAFE


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitLog();
    //init menu/toolbar
    InitAction();
    InitMenu();
    InitToolBar();

    //load pqkit
    InitPQKit();
}

MainWindow::~MainWindow()
{
    CoUninitialize();
    delete ui;
}

void MainWindow::InitLog()
{
    el::Configurations conf;
    conf.setGlobally(el::ConfigurationType::Enabled, "true");
    conf.setGlobally(el::ConfigurationType::Filename, "log\\pq_%datetime{%Y%M%d %H%m%s}.log");
    conf.setGlobally(el::ConfigurationType::MaxLogFileSize, "1920000");
    conf.setGlobally(el::ConfigurationType::ToFile, "true");
    conf.setGlobally(el::ConfigurationType::ToStandardOutput, "true");
    conf.setGlobally(el::ConfigurationType::Format, "[%datetime] [%loc] [%level] : %msg");
    conf.setGlobally(el::ConfigurationType::LogFlushThreshold, "1");
    el::Loggers::reconfigureAllLoggers(conf);

    int verboseLevel = el::Loggers::verboseLevel();
    LOG(INFO) << "Verbose Level = " << verboseLevel;
    LOG(INFO) << "this is info log";
    LOG(WARNING) << "this is waring log";
    LOG(ERROR) << "this is error log";
    LOG(DEBUG) << "this is debug log";
    LOG(TRACE) << "this is trace log";

}

void MainWindow::InitAction()
{
    m_openAction = new QAction(QIcon(":/Images/open.png"), QString::fromLocal8Bit("打开"), this);
    m_saveasAction = new QAction(QIcon(":/Images/save.png"), QString::fromLocal8Bit("另存"), this);
    m_compileAction = new QAction(QIcon(":/Images/compile.png"), QString::fromLocal8Bit("编译"), this);
    m_simulateAction = new QAction(QIcon(":/Images/simulate.png"), QString::fromLocal8Bit("仿真"), this);
    m_insertpathAction = new QAction(QIcon(":/Images/insertpath.png"), QString::fromLocal8Bit("导入轨迹点"), this);

    connect(m_openAction, SIGNAL(triggered()), this, SLOT(OnOpenRobx()));
    connect(m_saveasAction, SIGNAL(triggered()), this, SLOT(OnSaveAsRobx()));
    connect(m_compileAction, SIGNAL(triggered()), this, SLOT(OnCompile()));
    connect(m_simulateAction, SIGNAL(triggered()), this, SLOT(OnSimulate()));
    connect(m_insertpathAction, SIGNAL(triggered()), this, SLOT(OnInsertPath()));
}

void MainWindow::InitMenu()
{
    QMenuBar *mBar = menuBar();
    QMenu *pFile = mBar->addMenu("PQKit");

    //
    pFile->addAction(m_openAction);
    pFile->addAction(m_saveasAction);
    pFile->addSeparator();
    pFile->addAction(m_insertpathAction);
    pFile->addAction(m_compileAction);
    pFile->addAction(m_simulateAction);

}

void MainWindow::InitToolBar()
{
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolBar->addAction(m_openAction);
    ui->toolBar->addAction(m_saveasAction);
    ui->toolBar->addSeparator();
    ui->toolBar->addAction(m_insertpathAction);
    ui->toolBar->addAction(m_compileAction);
    ui->toolBar->addAction(m_simulateAction);

}

void MainWindow::InitPQKit()
{
    //
    CoInitializeEx(0, COINIT_APARTMENTTHREADED);
    HRESULT hr = m_ptrKit.CoCreateInstance(__uuidof(PQPlatformComponent));
    if (S_OK != hr)
    {
        QString strError = QString::fromLocal8Bit("PQKit创建失败！\n请排查当前启动或调试exe同目录是否有PQKit环境。\nPQkit环境包含PQkit文件夹、PQKit.manifest文件、启动或调试exe的manifest文件。");
        QMessageBox::information(NULL, "PQKit", strError, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

    //
    m_ptrKitCallback = new CPQKitCallback(this);
    connect(m_ptrKitCallback, &CPQKitCallback::signalInitializeResult, this, &MainWindow::OnInitializeResult);
    connect(m_ptrKitCallback, &CPQKitCallback::signalRunCMDResult, this, &MainWindow::OnRunCMDResult);
    connect(m_ptrKitCallback, &CPQKitCallback::signalGetDataResult, this, &MainWindow::OnGetDataResult);
    connect(m_ptrKitCallback, &CPQKitCallback::signalRaiseDockwindow, this, &MainWindow::OnRaiseDockwindow);
    connect(m_ptrKitCallback, &CPQKitCallback::signalLoginResult, this, &MainWindow::OnLoginResult);
    connect(m_ptrKitCallback, &CPQKitCallback::signalPathGenerateResult, this, &MainWindow::OnPathGenerateResult);
    connect(m_ptrKitCallback, &CPQKitCallback::signalElementPickup, this, &MainWindow::OnElementPickup);
    connect(m_ptrKitCallback, &CPQKitCallback::signalLButtonUp, this, &MainWindow::OnLButtonUp);
    connect(m_ptrKitCallback, &CPQKitCallback::signalRButtonUp, this, &MainWindow::OnRButtonUp);
    connect(m_ptrKitCallback, &CPQKitCallback::signalMenuPop, this, &MainWindow::OnMenuPop);

    //
    m_ptrKitInitThread = new PQKitInitThread;
    connect(m_ptrKitInitThread, &PQKitInitThread::signalInitializeKit, this, &MainWindow::OnInitializeKitThread);
    m_ptrKitInitThread->start();
}

void MainWindow::OnInitializeKitThread()
{
    //initialize pqkit
    CComBSTR bsName = Config::Instance().GetValue("pqaccount/user", "").toString().toStdString().data(); // L"13548987983";
    CComBSTR bsPWD =  Config::Instance().GetValue("pqaccount/passwd", "").toString().toStdString().data(); // L"987983";
    HRESULT hr = m_ptrKit->pq_InitPlatformComponent(m_ptrKitCallback, (int)(this->winId()), bsName, bsPWD);
    if (S_OK != hr)
    {
        QString strError = QString::fromLocal8Bit("PQKit初始化失败！\n请参考Fire_Initialize_Result或Fire_Login_Result函数中的具体lResult值。");
        QMessageBox::information(NULL, "PQKit", strError, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
}

void MainWindow::ShowPQKitWindown()
{
    int nHWND = 0;
    m_ptrKit->pq_GetPlatformView(&nHWND);
    HWND hWnd = (HWND)(UINT_PTR)nHWND;
    if (nullptr == hWnd)
    {
        return;
    }
    m_pPQPlatformView = QWidget::createWindowContainer(QWindow::fromWinId((WId)hWnd), this);

    ULONG_PTR nModelDoc = NULL;
    m_ptrKit->pq_GetModelTreeView(&nModelDoc);
    HWND hModelWnd = (HWND)nModelDoc;
    if (nullptr != hModelWnd)
    {
        m_pPQModeTreeView = QWidget::createWindowContainer(QWindow::fromWinId((WId)hModelWnd), this);
    }

    ULONG_PTR nDebugDoc = NULL;
    m_ptrKit->pq_GetDebugTreeView(&nDebugDoc);
    HWND hDebugWnd = (HWND)nDebugDoc;
    if (nullptr != hDebugWnd)
    {
        m_pPQDebugView = QWidget::createWindowContainer(QWindow::fromWinId((WId)hDebugWnd), this);
    }

    auto splitter = new QSplitter;
    splitter->addWidget(m_pPQModeTreeView);
    splitter->addWidget(m_pPQPlatformView);
    splitter->addWidget(m_pPQDebugView);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 5);
    splitter->setStretchFactor(2, 1);
    setCentralWidget(splitter);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (m_ptrKit)
    {
        m_ptrKit->pq_CloseComponent();
    }

    event->accept();
}

void MainWindow::OnOpenRobx()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("open robx file"), "",
        tr("Robx files(*.robx)"));
    if (fileName.isEmpty())
    {
        return;
    }
    fileName = QDir::toNativeSeparators(fileName);
    std::wstring wsFilePath = fileName.toStdWString();
    long long lResult = 0;
    CComVariant varPara(wsFilePath.c_str());
    CComBSTR bsPara = "";
    CComBSTR bsCmd = "RO_CMD_FILE_OPEN";
    m_ptrKit->pq_RunCommand(bsCmd, NULL, NULL, bsPara, varPara, &lResult);
}

void MainWindow::OnSaveAsRobx()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("open robx file"), "",
        tr("Robx files(*.robx)"));
    if (fileName.isEmpty())
    {
        return;
    }
    fileName = QDir::toNativeSeparators(fileName);
    std::wstring wsFilePath = fileName.toStdWString();
    long long lResult = 0;
    CComBSTR bsPara = wsFilePath.c_str();
    CComBSTR bsCmd = "RO_CMD_FILE_SAVE_AS";
    m_ptrKit->pq_RunCommand(bsCmd, NULL, NULL, bsPara, CComVariant(), &lResult);
}

void MainWindow::OnCompile()
{
    long long lResult = 0;
    CComBSTR bsPara = "";
    CComBSTR bsCmd = "RO_CMD_COMPILE";
    m_ptrKit->pq_RunCommand(bsCmd, NULL, NULL, bsPara, CComVariant(), &lResult);
}

void MainWindow::OnSimulate()
{
    long long lResult = 0;
    CComBSTR bsPara = "";
    CComBSTR bsCmd = "RO_CMD_SIMULATE";
    m_ptrKit->pq_RunCommand(bsCmd, NULL, NULL, bsPara, CComVariant(), &lResult);
}

void MainWindow::OnInsertPath()
{
    InsertPathDlg dlg;
    if (QDialog::Rejected == dlg.exec())
    {
        return;
    }

    //默认取第一个机器人
    ULONG uRobotID = 0;
    GetObjIDByName(32, _T(""), uRobotID);

    //
    int nType = 1;
    double dPosition[6] = { 0.0 };
    dlg.GetPosture(dPosition[0], dPosition[1], dPosition[2], dPosition[3], dPosition[4], dPosition[5], nType);

    int nInstruction[1] = { 1 };
    double dVel[1] = { 200.0 };
    double dSpeedP[1] = { 100.0 };
    int nApproach[1] = { -1 };
    CComBSTR bsPathName = "Test_Path";
    CComBSTR bsPathGroupName = "Test_Group";

    ULONG uPathID = 0;
    m_ptrKit->Path_insert_from_point(uRobotID, 1, dPosition, nType, nInstruction, dVel, dSpeedP, nApproach, bsPathName, bsPathGroupName, 0, FALSE, &uPathID);
}

void MainWindow::GetObjIDByName(int i_nType, std::wstring i_wsName, ULONG &o_uID)
{
    VARIANT vNamePara;
    vNamePara.parray = NULL;
    VARIANT vIDPara;
    vIDPara.parray = NULL;
    m_ptrKit->Doc_get_obj_bytype(i_nType, &vNamePara, &vIDPara);
    if (NULL == vNamePara.parray || NULL == vIDPara.parray)
    {
        return;
    }
    //缓存指定对象名称
    BSTR* bufName;
    long lenName = vNamePara.parray->rgsabound[0].cElements;
    SafeArrayAccessData(vNamePara.parray, (void**)&bufName);
    int nTarIndex = 0;
    if (!i_wsName.empty())
    {
        for (int i = 0; i < lenName; i++)
        {
            if (0 == i_wsName.compare(bufName[i]))
            {
                nTarIndex = i;
            }
        }
    }
    SafeArrayUnaccessData(vNamePara.parray);


    //缓存指定对象ID
    ULONG* bufID;
    long lenID = vIDPara.parray->rgsabound[0].cElements;
    SafeArrayAccessData(vIDPara.parray, (void**)&bufID);
    o_uID = bufID[nTarIndex];
    SafeArrayUnaccessData(vIDPara.parray);
}

void MainWindow::OnInitializeResult(long lResult)
{
    if (lResult > 0)
    {
        //show kit
        ShowPQKitWindown();
    }
    else
    {
        QString strError = QString::fromLocal8Bit("组件初始化失败:\n");
        switch (lResult)
        {
        case -1:
            strError.append(QString::fromLocal8Bit("未知错误"));
            break;
        case -2:
            strError.append(QString::fromLocal8Bit("初始化超时"));
            break;
        case -3:
        case -4:
        case -6:
            strError.append(QString::fromLocal8Bit("加载组件动态库错误"));
            break;
        case -7:
            strError.append(QString::fromLocal8Bit("组件重复初始化"));
            break;
        case -9:
        case -10:
        case -11:
        case -12:
            strError.append(QString::fromLocal8Bit("内部数据错误"));
            break;
        case -14:
            strError.append(QString::fromLocal8Bit("非开发版账号不能登录开发版"));
            break;
        default:
            strError.append(QString::fromLocal8Bit("错误码: "));
            strError.append(QString::number(lResult, 10));
            break;
        }

        QMessageBox::information(NULL, "PQKit Info", strError, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
}

void MainWindow::OnRunCMDResult(long lResult)
{

}

void MainWindow::OnGetDataResult(long lResult)
{

}

void MainWindow::OnRaiseDockwindow(int i_nType)
{

}

void MainWindow::OnLoginResult(int i_nLoginType)
{
    if (i_nLoginType < 0)
    {
        QString strError = QString::fromLocal8Bit("用户校验失败:\n");
        switch (i_nLoginType)
        {
        case -1:
            strError.append(QString::fromLocal8Bit("密码错误"));
            break;
        case -2:
            strError.append(QString::fromLocal8Bit("用户不存在"));
            break;
        case -4:
            strError.append(QString::fromLocal8Bit("用户已过期"));
            break;
        case -6:
            strError.append(QString::fromLocal8Bit("网络连接失败"));
            break;
        case -7:
            strError.append(QString::fromLocal8Bit("用户未激活"));
            break;
        case -14:
            strError.append(QString::fromLocal8Bit("账号与产品不匹配"));
            break;
        default:
            strError.append(QString::fromLocal8Bit("错误码: "));
            strError.append(QString::number(i_nLoginType));
            break;
        }

        QMessageBox::information(NULL, "PQKit Info", strError, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    }
}

void MainWindow::OnPathGenerateResult(long i_bSuccess, int i_nPathCount, int i_nIndex, unsigned long i_ulPathID)
{

}

void MainWindow::OnElementPickup(unsigned long i_ulObjID, long i_lEntityID, int i_nEntityType)
{

}

void MainWindow::OnRButtonUp(long i_lPosX, long i_lPosY)
{

}

void MainWindow::OnLButtonUp(long i_lPosX, long i_lPosY)
{

}

void MainWindow::OnMenuPop(unsigned long i_ulObjID, long i_lPosX, long i_lPosY, int* o_nHandled)
{

}
