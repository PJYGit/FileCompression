
// FileComDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "FileCom.h"
#include "FileComDlg.h"
#include "afxdialogex.h"
#include "io.h"
#include "fcntl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString GetSuffix(CString strFileName);
int  swap(int data);
int num[8];

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFileComDlg 对话框



CFileComDlg::CFileComDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILECOM_DIALOG, pParent)
	, m_chosen_file(_T(""))
	, m_com_file(_T(""))
	, m_uncom_file(_T(""))
	, m_persent(_T(""))
	, m_origin(_T(""))
	, m_now(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileComDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BROT_EDIT, m_chosen_file);
	DDX_Text(pDX, IDC_COMT_EDIT, m_com_file);
	DDX_Text(pDX, IDC_UNCOMT_EDIT, m_uncom_file);
	DDX_Text(pDX, IDC_PER_EDIT, m_persent);
	DDX_Text(pDX, IDC_EDIT1, m_origin);
	DDX_Text(pDX, IDC_EDIT2, m_now);
}

BEGIN_MESSAGE_MAP(CFileComDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BRO_BUTTON, &CFileComDlg::OnBnClickedBroButton)
	ON_BN_CLICKED(IDC_COM_BUTTON, &CFileComDlg::OnBnClickedComButton)
	ON_BN_CLICKED(IDC_UNCOM_BUTTON, &CFileComDlg::OnBnClickedUncomButton)
END_MESSAGE_MAP()


// CFileComDlg 消息处理程序

BOOL CFileComDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFileComDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFileComDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFileComDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFileComDlg::OnBnClickedBroButton()
{
	HWND hwnd = GetSafeHwnd();   //得到窗口句柄
	CString filePath = _T("");	//得到文件路径
	LPMALLOC pMalloc;
	if (::SHGetMalloc(&pMalloc) == NOERROR)	//取得IMalloc分配器接口
	{
		CString strFile = _T("");

		CFileDialog    dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("All Files (*.*)|*.*||"), NULL);

		if (dlgFile.DoModal())
		{
			strFile = dlgFile.GetPathName();
		}
		UpdateData(TRUE);
		m_chosen_file = strFile;
		UpdateData(FALSE);

	}
	//CString strInfo;
	//GetDlgItem(IDC_BROT_EDIT)->GetWindowText(strInfo);
	//int nLength = strInfo.GetLength();
	//m_editFilePath.SetSel(nLength, nLength, FALSE);
	//m_editFilePath.SetFocus();
}


void CFileComDlg::OnBnClickedComButton()
{
	HWND hwnd = GetSafeHwnd();   //得到窗口句柄
	CString filePath = _T("");	//得到文件路径
	LPMALLOC pMalloc;
	if (::SHGetMalloc(&pMalloc) == NOERROR)	//取得IMalloc分配器接口
	{
		CString strFile = _T("");

		CFileDialog    dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("All Files (*.*)|*.*||"), NULL);

		if (dlgFile.DoModal())
		{
			strFile = dlgFile.GetPathName();
		}
		UpdateData(TRUE);
		m_com_file = strFile;
		UpdateData(FALSE);

	}

	FILE *in = _tfopen(m_chosen_file, _T("rb"));
	int weight[256];
	for (int i = 0; i < 256; i++) {//初始化权重数组
		weight[i] = 0;
	}

	saveToWeight(in, weight);//按照字节流读取存入数组
	HTNode htNode[511];
	createHFM(weight, htNode);
	int depth;
	depth = DepthHFM(htNode, htNode[510]);
	
	char* encode[256];
	for (int i = 0; i < 256; i++) {
		encode[i] = (char*)malloc(depth * sizeof(char));
	}
	char *s;
	s = (char*)malloc(depth * sizeof(char));
	encodeHFM(depth, s, encode, 0, htNode, 510);

	fseek(in, 0, SEEK_SET);
	fseek(in, 0L, SEEK_END);
	int sizeIn = ftell(in);
	CString strIn;
	strIn.Format(_T("%d Bytes"), sizeIn / 1024);
	HEAD h;
	h.length = sizeIn;
	for (int r = 0; r < 256; r++) {
		h.weight[r] = weight[r];
	}
	CString splittedStr;
	splittedStr = GetSuffix(m_chosen_file);
	LPCTSTR p = splittedStr.GetBuffer(0);
	splittedStr.ReleaseBuffer();
	strcpy_s(h.type, splittedStr.GetLength() + 1, CT2CA(p));
	h.type[splittedStr.GetLength()] = '\0';


	FILE *out = _tfopen(m_com_file + ".huf", _T("wb"));
	fwrite(&h, sizeof(HEAD), 1, out);

	fseek(in, 0, SEEK_SET);
	//向压缩文件里写入Huffman编码  
	int pos = 0;
	char value = 0;
	int ch1 = fgetc(in);//读一个字节
	while (ch1 != EOF)
	{
		if (feof(in))
			break;
		char* code = encode[ch1];
		for (int i = 0; encode[ch1][i] != '\0'; i++)
		{
			value = value << 1;
			if (code[i] == '1')  //得到二进制的1  
			{
				value = value | 1;
			}
			if (++pos == 8)   //满8位写入文件  
			{
				fputc(value, out);//转化为哈夫曼编码写入文件
				value = 0;
				pos = 0;
			}
		}

		ch1 = fgetc(in);
	}
	if (pos)    //最后的编码不满足一个字节 ，补0 
	{
		value = value << (8 - pos);
		fputc(value, out);
	}
	fclose(in);
	fclose(out);

	UpdateData(TRUE);
	m_origin = _T("");
	m_now = _T("");
	m_persent = _T("");
	UpdateData(FALSE);


	UpdateData(TRUE);
	m_origin = m_origin + strIn;
	UpdateData(FALSE);

	out = _tfopen(m_com_file + ".huf", _T("rb"));
	fseek(out, 0L, SEEK_END);
	int sizeOut = ftell(out);
	CString strOut;
	strOut.Format(_T("%d Bytes"), sizeOut / 1024);
	fclose(out);

	UpdateData(TRUE);
	m_now = m_now + strOut;
	UpdateData(FALSE);

	CString strPercent;
	strPercent.Format(_T("%.2f"), sizeOut*(100.0) / sizeIn);
	UpdateData(TRUE);
	m_persent = m_persent + strPercent;
	UpdateData(FALSE);

	AfxMessageBox(_T("压缩成功！"));
}


void CFileComDlg::OnBnClickedUncomButton()
{
	HWND hwnd = GetSafeHwnd();   //得到窗口句柄
	CString filePath = _T("");	//得到文件路径
	LPMALLOC pMalloc;
	if (::SHGetMalloc(&pMalloc) == NOERROR)	//取得IMalloc分配器接口
	{
		CString strFile = _T("");

		CFileDialog    dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("All Files (*.*)|*.*||"), NULL);

		if (dlgFile.DoModal())
		{
			strFile = dlgFile.GetPathName();
		}
		UpdateData(TRUE);
		m_uncom_file = strFile;
		UpdateData(FALSE);

	}

	FILE *in = _tfopen(m_chosen_file, _T("rb"));
	HEAD h;
	fread(&h, sizeof(HEAD), 1, in);//读文件头
	char fileType[5];
	strcpy(fileType, h.type);
	int fileLength = h.length;

	int weight[256];
	for (int i = 0; i < 256; i++) {
		weight[i] = h.weight[i];
	}
	HTNode htNode[511];
	createHFM(weight, htNode);
	int depth;
	depth = DepthHFM(htNode, htNode[510]);
	char* encode[256];
	for (int i = 0; i < 256; i++) {
		encode[i] = (char*)malloc(depth * sizeof(char));
	}
	char *s;
	s = (char*)malloc(depth * sizeof(char));
	encodeHFM(depth, s, encode, 0, htNode, 510);

	CString strRight;
	strRight = fileType;

	UpdateData(TRUE);
	m_uncom_file = m_uncom_file + _T(".") + strRight;
	UpdateData(FALSE);

	FILE *out = _tfopen(m_uncom_file, _T("wb"));

	char str[1000];
	int i, j, k, temp = 0;
	int index;
	int sum_bit2 = 0;

	//直到读取到文件结尾  
	while (!feof(in))
	{
		if (sum_bit2 == h.length) break;

		int data = fgetc(in);
		if (data == -1) break;
		//index用来在sum_bit2小于0的时候设置读取为位数（也就是说最后不用读取8位了）  

		else
		{
			index = 0;
		}
		if (data == -1) break;

		memset(num, 0, sizeof(num));

		//将读取到的data转换成二进制数  
		swap(data);
		i = temp;
		//将转换后的二进制数变为字符串，注意顺序  

		//是一位一位的往里面填，填进去一位立即进行比较，当找到相应的信息就调出来  
		for (k = 7; k >= index; i++, k--)
		{
			if (num[k])
				str[i] = '1';
			else
				str[i] = '0';

			str[i + 1] = '\0';
			//查找编码表当中与该字符串（编码）相同的信息，然后将叶子信息写入解压文件  
			for (j = 0; j < 256; j++)
			{
				if (strcmp(str, encode[j]) == 0)
				{
					//将叶子信息写入到文件（写入的是int值，是该int值表示的字符）  
					fputc(j, out);
					sum_bit2 += 1;
					fflush(out);
					j = 256;
					i = -1;
				}
			}
		}
		if (i)
		{
			temp = i;
		}
		else
		{
			temp = 0;
		}
	}
	sum_bit2 = 0;

	fclose(in);
	fclose(out);

	AfxMessageBox(_T("解压成功！"));
}

void CFileComDlg::saveToWeight(FILE* in, int* weight) {
	byte num;
	int i = fread(&num, sizeof(byte), 1, in);
	weight[num]++;
	while (i != 0) {
		i = fread(&num, sizeof(byte), 1, in);
		weight[num]++;
	}
}

void CFileComDlg::createHFM(int *weight, HTNode* htNode) {
	int i;
	for (i = 0; i < 256; i++) {
		htNode[i].weight = weight[i];
		htNode[i].parent = -1;
		htNode[i].lchild = -1;
		htNode[i].rchild = -1;
	}
	while (i < 511) {
		htNode[i].weight = -1;
		htNode[i].parent = -2;
		htNode[i].lchild = -1;
		htNode[i].rchild = -1;
		i++;
	}


	int last = 256;
	int minmum1Position;
	int minmum1;//最小的
	int minmum2Position;
	int minmum2;

	while (last != 511) {
		int init = 0;
		for (int u = 0; u < 511; u++) {
			if (init == 0 && htNode[u].parent == -1) {

				minmum1Position = u;
				minmum1 = htNode[minmum1Position].weight;//最小的
				init = 1;
			}
			else if (init == 1 && htNode[u].parent == -1) {
				minmum2Position = u;
				minmum2 = htNode[minmum2Position].weight;
				init = 2;
			}
			else if (htNode[u].weight < max(minmum1, minmum2) && htNode[u].parent == -1) {
				if (minmum1 != minmum2 && minmum1 == max(minmum1, minmum2)) {
					minmum1 = htNode[u].weight;
					minmum1Position = u;
				}
				else if (minmum1 != minmum2 && minmum2 == max(minmum1, minmum2)) {
					minmum2 = htNode[u].weight;
					minmum2Position = u;
				}
				else if (minmum1 == minmum2) {
					minmum1 = htNode[u].weight;
					minmum1Position = u;
				}

			}

		}
		htNode[minmum1Position].parent = last;
		htNode[minmum2Position].parent = last;
		htNode[last].lchild = minmum1Position;
		htNode[last].rchild = minmum2Position;
		htNode[last].weight = htNode[minmum1Position].weight + htNode[minmum2Position].weight;
		htNode[last].parent = -1;
		last++;
	}


	printf("htNode\tweitght\tparent\tlchild\trchild\n");
	for (int u = 0; u < 511; u++) {
		printf("%d\t%d\t%d\t%d\t%d\n", u, htNode[u].weight, htNode[u].parent, htNode[u].lchild, htNode[u].rchild);
	}
}

int CFileComDlg::DepthHFM(HTNode *htNode, HTNode h) {
	if (h.lchild == -1 && h.rchild == -1) {
		return 0;
	}
	else {
		return (1 + max(DepthHFM(htNode, htNode[h.lchild]), DepthHFM(htNode, htNode[h.rchild])));
	}
}

void CFileComDlg::encodeHFM(int depth, char *s, char** encode, int i, HTNode *htNode, int h) {

	if (htNode != NULL)
	{
		if (htNode[h].lchild == -1 && htNode[h].rchild == -1)
		{
			s[i] = '\0';
			strcpy(encode[h], s);

		}
		else
		{
			s[i] = '0';
			encodeHFM(depth, s, encode, i + 1, htNode, htNode[h].lchild);
			s[i] = '1';
			encodeHFM(depth, s, encode, i + 1, htNode, htNode[h].rchild);
		}
	}
}

CString GetSuffix(CString strFileName)
{
	return strFileName.Right(strFileName.GetLength() - strFileName.ReverseFind('.') - 1);
}

int  swap(int data)
{
	int i = 0;
	while (data)
	{
		num[i++] = data % 2;
		data = data / 2;
	}
	return i;
}
