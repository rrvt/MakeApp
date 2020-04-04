#pragma once


// ProjectName dialog

class ProjectName : public CDialogEx
{
	DECLARE_DYNAMIC(ProjectName)

public:
	ProjectName(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ProjectName();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString name;
	CString description;
	CString visibleName;
};
