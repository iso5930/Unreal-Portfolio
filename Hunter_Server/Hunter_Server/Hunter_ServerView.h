
// Hunter_ServerView.h : CHunter_ServerView 클래스의 인터페이스
//

#pragma once

class CMySheet;
class CHunter_ServerView : public CView
{
protected: // serialization에서만 만들어집니다.
	CHunter_ServerView();
	DECLARE_DYNCREATE(CHunter_ServerView)

// 특성입니다.
public:
	CHunter_ServerDoc* GetDocument() const;

// 작업입니다.
public:
	CMySheet* m_pMySheet;

public:
	void Update();

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CHunter_ServerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

	virtual void OnInitialUpdate() override;

};

#ifndef _DEBUG  // Hunter_ServerView.cpp의 디버그 버전
inline CHunter_ServerDoc* CHunter_ServerView::GetDocument() const
   { return reinterpret_cast<CHunter_ServerDoc*>(m_pDocument); }
#endif

