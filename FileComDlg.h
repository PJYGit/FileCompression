
// FileComDlg.h: 头文件
//

#pragma once
#include "afxwin.h"
struct HTNode
{
	int weight;
	int parent;
	int lchild;
	int rchild;
};
struct HEAD
{
	char type[5]; // file type
	int length; // file length
	int weight[256]; // character occurrence
};

// CFileComDlg 对话框
class CFileComDlg : public CDialogEx
{
// 构造
public:
	CFileComDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILECOM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_chosen_file;
	CString m_com_file;
	CString m_uncom_file;
	CString m_persent;
	afx_msg void OnBnClickedBroButton();
	afx_msg void OnBnClickedComButton();
	afx_msg void OnBnClickedUncomButton();

	void saveToWeight(FILE * in, int * weight);

	void createHFM(int * weight, HTNode * htNode);

	int DepthHFM(HTNode * htNode, HTNode h);

	void encodeHFM(int depth, char * s, char ** encode, int i, HTNode * htNode, int h);
	
	CString m_origin;
	CString m_now;
};
