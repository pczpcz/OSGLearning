
// MyOsgEarthView.h: CMyOsgEarthView 类的接口
//

#pragma once

#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgViewer/api/win32/GraphicsWindowWin32>
#include <osgGA/TrackballManipulator>

class CMyOsgEarthView : public CView
{
protected: // 仅从序列化创建
	CMyOsgEarthView() noexcept;
	DECLARE_DYNCREATE(CMyOsgEarthView)

// 特性
public:
	CMyOsgEarthDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMyOsgEarthView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

public:
	static void CMyOsgEarthView::Render(void*);
};

#ifndef _DEBUG  // MyOsgEarthView.cpp 中的调试版本
inline CMyOsgEarthDoc* CMyOsgEarthView::GetDocument() const
   { return reinterpret_cast<CMyOsgEarthDoc*>(m_pDocument); }
#endif

