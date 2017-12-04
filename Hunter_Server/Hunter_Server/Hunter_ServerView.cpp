
// Hunter_ServerView.cpp : CHunter_ServerView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Hunter_Server.h"
#endif

#include "Hunter_ServerDoc.h"
#include "Hunter_ServerView.h"
#include "MainFrm.h"
#include "MySheet.h"
#include "NetworkMgr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHunter_ServerView

IMPLEMENT_DYNCREATE(CHunter_ServerView, CView)

BEGIN_MESSAGE_MAP(CHunter_ServerView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CHunter_ServerView 생성/소멸

CHunter_ServerView::CHunter_ServerView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_pMySheet = NULL;

	MainView = this;
}

CHunter_ServerView::~CHunter_ServerView()
{
	if (m_pMySheet != NULL)
	{
		delete m_pMySheet;
		m_pMySheet = NULL;
	}

	CNetworkMgr::GetInstance()->DestoryInstance();
}

BOOL CHunter_ServerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

void CHunter_ServerView::Update()
{
	CNetworkMgr::GetInstance()->Update();
}

// CHunter_ServerView 그리기

void CHunter_ServerView::OnDraw(CDC* /*pDC*/)
{
	CHunter_ServerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}

// CHunter_ServerView 인쇄

BOOL CHunter_ServerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CHunter_ServerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CHunter_ServerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

// CHunter_ServerView 진단

#ifdef _DEBUG
void CHunter_ServerView::AssertValid() const
{
	CView::AssertValid();
}

void CHunter_ServerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

void CHunter_ServerView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	RECT rcWindow;

	pFrame->GetWindowRect(&rcWindow);

	SetRect(&rcWindow, 0, 0, rcWindow.right - rcWindow.left, rcWindow.bottom - rcWindow.top);

	RECT rcMainView;
	GetClientRect(&rcMainView);

	float fRowFrm = float(rcWindow.right - rcMainView.right);
	float fColFrm = float(rcWindow.bottom - rcMainView.bottom);

	int WINCX = 800;
	int WINCY = 600;

	pFrame->SetWindowPos(NULL, 0, 0, int(WINCX + fRowFrm), int(WINCY + fColFrm), SWP_NOZORDER);

	pFrame->SetActiveView(this);

	m_pMySheet = new CMySheet;
	m_pMySheet->Create(this, WS_CHILD | WS_VISIBLE);

	m_pMySheet->MoveWindow(0, 0, WINCX, WINCY);

	//여기서 서버 열기.

	CNetworkMgr::GetInstance()->Init_NetworkMgr(m_pMySheet);

	/*m_pMySheet->m_MyPage.AddLog(CString(L"TestCase1"));
	m_pMySheet->m_MyPage.AddLog(CString(L"TestCase2"));*/
}

CHunter_ServerDoc* CHunter_ServerView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHunter_ServerDoc)));
	return (CHunter_ServerDoc*)m_pDocument;
}
#endif //_DEBUG


// CHunter_ServerView 메시지 처리기
