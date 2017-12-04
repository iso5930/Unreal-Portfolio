
// Hunter_ServerView.cpp : CHunter_ServerView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CHunter_ServerView ����/�Ҹ�

CHunter_ServerView::CHunter_ServerView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
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
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

void CHunter_ServerView::Update()
{
	CNetworkMgr::GetInstance()->Update();
}

// CHunter_ServerView �׸���

void CHunter_ServerView::OnDraw(CDC* /*pDC*/)
{
	CHunter_ServerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}

// CHunter_ServerView �μ�

BOOL CHunter_ServerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CHunter_ServerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CHunter_ServerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

// CHunter_ServerView ����

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
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

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

	//���⼭ ���� ����.

	CNetworkMgr::GetInstance()->Init_NetworkMgr(m_pMySheet);

	/*m_pMySheet->m_MyPage.AddLog(CString(L"TestCase1"));
	m_pMySheet->m_MyPage.AddLog(CString(L"TestCase2"));*/
}

CHunter_ServerDoc* CHunter_ServerView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHunter_ServerDoc)));
	return (CHunter_ServerDoc*)m_pDocument;
}
#endif //_DEBUG


// CHunter_ServerView �޽��� ó����
