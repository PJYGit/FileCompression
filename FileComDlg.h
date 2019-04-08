
// FileComDlg.h: 头文件
//

#pragma once
#include "afxwin.h"
//哈夫曼树节点结构体
struct HTNode
{
	int weight;	//权重
	int parent;	//父节点
	int lchild; //left-child
	int rchild; //right-child
};
//压缩文件头结构体
struct HEAD
{
	char type[5];		// 文件类型
	int length;			// 文件大小
	int weight[256];	// 字符权重
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

	void GetAndSaveWeight(FILE * in, int * weight);

	void GenerateHaffmanTree(int * weight, HTNode * htNode);

	int GetDepth(HTNode * htNode, HTNode h);

	void GenerateNewCode(int depth, char * s, char ** encode, int i, HTNode * htNode, int h);

	CString GetExtensionOfFile(CString strFileName);

	int  DataToBytes(int data);

	CString m_origin;
	CString m_now;
};
