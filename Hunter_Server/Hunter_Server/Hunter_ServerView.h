
// Hunter_ServerView.h : CHunter_ServerView Ŭ������ �������̽�
//

#pragma once

class CMySheet;
class CHunter_ServerView : public CView
{
protected: // serialization������ ��������ϴ�.
	CHunter_ServerView();
	DECLARE_DYNCREATE(CHunter_ServerView)

// Ư���Դϴ�.
public:
	CHunter_ServerDoc* GetDocument() const;

// �۾��Դϴ�.
public:
	CMySheet* m_pMySheet;

public:
	void Update();

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CHunter_ServerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

	virtual void OnInitialUpdate() override;

};

#ifndef _DEBUG  // Hunter_ServerView.cpp�� ����� ����
inline CHunter_ServerDoc* CHunter_ServerView::GetDocument() const
   { return reinterpret_cast<CHunter_ServerDoc*>(m_pDocument); }
#endif

