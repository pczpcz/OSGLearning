
// MyOsgEarthView.cpp: CMyOsgEarthView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MyOsgEarth.h"
#endif

#include "MyOsgEarthDoc.h"
#include "MyOsgEarthView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

osg::ref_ptr<osgViewer::Viewer> g_refptrViewer = new osgViewer::Viewer;
bool g_bFinished = true;

// CMyOsgEarthView

IMPLEMENT_DYNCREATE(CMyOsgEarthView, CView)

BEGIN_MESSAGE_MAP(CMyOsgEarthView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMyOsgEarthView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
END_MESSAGE_MAP()

void CMyOsgEarthView::Render(void *)
{
	while (!(g_refptrViewer->done()))
	{
		g_refptrViewer->frame();
	}
	g_bFinished = true;
}

// CMyOsgEarthView 构造/析构
CMyOsgEarthView::CMyOsgEarthView() noexcept
{
	// TODO: 在此处添加构造代码

}

CMyOsgEarthView::~CMyOsgEarthView()
{
}

BOOL CMyOsgEarthView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMyOsgEarthView 绘图

void CMyOsgEarthView::OnDraw(CDC* /*pDC*/)
{
	CMyOsgEarthDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMyOsgEarthView 打印


void CMyOsgEarthView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMyOsgEarthView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMyOsgEarthView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMyOsgEarthView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMyOsgEarthView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMyOsgEarthView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMyOsgEarthView 诊断

#ifdef _DEBUG
void CMyOsgEarthView::AssertValid() const
{
	CView::AssertValid();
}

void CMyOsgEarthView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyOsgEarthDoc* CMyOsgEarthView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyOsgEarthDoc)));
	return (CMyOsgEarthDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyOsgEarthView 消息处理程序


int CMyOsgEarthView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	osg::ref_ptr<osg::Referenced> windata = new osgViewer::GraphicsWindowWin32::WindowData(m_hWnd);

	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	traits->x = 0;
	traits->y = 0;
	CRect rect;
	GetWindowRect(&rect);
	traits->width = rect.Width();
	traits->height = rect.Height();
	traits->windowDecoration = false;
	traits->doubleBuffer = true;
	traits->inheritedWindowData = windata;

	osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());

	osg::ref_ptr<osg::Camera> camera = new osg::Camera;
	camera->setGraphicsContext(gc);
	camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));

	if (!g_refptrViewer) 
	{
		g_refptrViewer = new osgViewer::Viewer;
	}
	g_refptrViewer->addSlave(camera.get());
	g_refptrViewer->setSceneData(osgDB::readNodeFile("osgData/cow.osg"));
	g_refptrViewer->setCameraManipulator(new osgGA::TrackballManipulator);

	g_refptrViewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);
	
	g_bFinished = false;
	_beginthread(Render, 0, NULL);

	return 0;
}
