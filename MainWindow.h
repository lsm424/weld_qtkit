#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#import "RPC.tlb" no_namespace, named_guids, raw_interfaces_only, raw_native_types

#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>

#include "PQKitInitThread.h"
#include "PQKitCallback.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

	void InitAction();
	void InitMenu();
	void InitToolBar();
    void InitLog();

	void InitPQKit();
	void ShowPQKitWindown();
	void GetObjIDByName(int i_nType, std::wstring i_wsName, ULONG &o_uID);

private:
    Ui::MainWindow *ui;
	QAction* m_openAction;
	QAction* m_saveasAction;
	QAction* m_compileAction;
	QAction* m_simulateAction;
	QAction* m_insertpathAction;

	CComPtr<IPQPlatformComponent> m_ptrKit;
	CPQKitCallback* m_ptrKitCallback;
	PQKitInitThread* m_ptrKitInitThread;

	QWidget* m_pPQPlatformView;
	QWidget* m_pPQModeTreeView;
	QWidget* m_pPQDebugView;

private:
	void closeEvent(QCloseEvent* event);

protected slots:
	//owner
	void OnOpenRobx();
	void OnSaveAsRobx();
	void OnCompile();
	void OnSimulate();
	void OnInsertPath();

	//PQKit slots
	void OnInitializeResult(long lResult);
	void OnRunCMDResult(long lResult);
	void OnGetDataResult(long lResult);
	void OnRaiseDockwindow(int i_nType);
	void OnLoginResult(int i_nLoginType);
	void OnPathGenerateResult(long i_bSuccess, int i_nPathCount, int i_nIndex, unsigned long i_ulPathID);
	void OnElementPickup(unsigned long i_ulObjID, long i_lEntityID, int i_nEntityType);
	void OnRButtonUp(long i_lPosX, long i_lPosY);
	void OnLButtonUp(long i_lPosX, long i_lPosY);
	void OnMenuPop(unsigned long i_ulObjID, long i_lPosX, long i_lPosY, int* o_nHandled);
	void OnInitializeKitThread();
};
#endif // MAINWINDOW_H
