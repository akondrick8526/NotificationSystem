
// TestToastDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "TestToast.h"
#include "TestToastDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace WinToastLib;



// CTestToastDlg dialog



CTestToastDlg::CTestToastDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TESTTOAST_DIALOG, pParent)
	, m_WinToastHandler(this)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);


}

void CTestToastDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestToastDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SHOW_TOAST, &CTestToastDlg::OnBnClickedBtnShowToast)
END_MESSAGE_MAP()


// CTestToastDlg message handlers

BOOL CTestToastDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	WinToast::WinToastError error;
	WinToast::instance()->setAppName(L"TestToastExample");
	const auto aumi = WinToast::configureAUMI(L"company", L"wintoast", L"wintoastexample", L"20201012");
	WinToast::instance()->setAppUserModelId(aumi);

	if (!WinToast::instance()->initialize(&error)) {
		wchar_t buf[250];
		swprintf_s(buf, L"Failed to initialize WinToast :%d", error);
		MessageBox(buf, L"Error");
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestToastDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestToastDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestToastDlg::OnBnClickedBtnShowToast()
{
	WinToastTemplate templ;
	if (WinToast::isWin10AnniversaryOrHigher()) //some notification setup types are only supported past windows 10 anniversary update.
	{
		templ = WinToastTemplate(WinToastTemplate::HeroImageAndImageAndText02); //chooses to display a hero image (big top image), image (small profile-like image), and two lines of text.
		bool inlineImage = false;
		templ.setHeroImagePath(L"C:\\Users\\alk22\\Documents\\Semester 5\\SE\\TestToast\\images\\hero.jpg", inlineImage); //choose path of hero image to display
	}
	else
	{
		templ = WinToastTemplate(WinToastTemplate::ImageAndText02); //choose to display a image (small profile-like image) and two lines of text.
	}
	templ.setImagePath(
		L"C:\\Users\\alk22\\Documents\\Semester 5\\SE\\TestToast\\images\\49010242_2109247632472672_900234980716707840_n.jpg", //choose path of image to display
		WinToastTemplate::CropHint::Circle); //crop the image to the shape of a circle

	templ.setTextField(L"My First Toast", WinToastTemplate::FirstLine); //first line of text
	templ.setTextField(L"Say Hello?", WinToastTemplate::SecondLine); //second line of text

	templ.addAction(L"Yes"); //adds action with label "Yes"
	templ.addAction(L"No"); //adds action with label "No"

	templ.setDuration(WinToastTemplate::Duration::Short); //sets duration. options are Short, Long, and System (display until dismissed)
	templ.setAudioOption(WinToastTemplate::AudioOption::Default); //set audio properties. options are Default, Silent, and Loop
	templ.setAudioPath(WinToastTemplate::AudioSystemFile::Call1); //set audio played. Can be customized but input must be formatted

	if (WinToast::instance()->showToast(templ, &m_WinToastHandler) == -1L)
	{
		MessageBox(L"Could not launch your toast notification!", L"Error");
	}
}
