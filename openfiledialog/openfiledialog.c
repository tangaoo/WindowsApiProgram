#include <Windows.h>
#include <CommDlg.h>
#include <stdio.h>

static OPENFILENAME ofn;

void PopFileInitialize(HWND hwnd)
{
	ofn.lStructSize = sizeof (OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.hInstance = NULL;
	ofn.lpstrFilter = "所有文件\0*.*\0Text\0*.TXT\0";
	ofn.lpstrCustomFilter = NULL;
	ofn.nMaxCustFilter = 0;
	ofn.nFilterIndex = 0;
	ofn.lpstrFile = NULL;          // Set in Open and Close functions
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFileTitle = NULL;          // Set in Open and Close functions
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrTitle = NULL;
	ofn.Flags = 0;             // Set in Open and Close functions
	ofn.nFileOffset = 0;
	ofn.nFileExtension = 0;
	ofn.lpstrDefExt = TEXT("jpg");
	ofn.lCustData = 0L;
	ofn.lpfnHook = NULL;
	ofn.lpTemplateName = NULL;
}

BOOL PopFileOpenDlg(HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName)
{
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = pstrFileName;
	ofn.lpstrFileTitle = pstrTitleName;
	ofn.Flags = OFN_HIDEREADONLY | OFN_CREATEPROMPT;

	return GetOpenFileName(&ofn);
}

//获取打开文件大小
int GetFilSize(FILE * pFil)
{
	fseek(pFil, 0, SEEK_END);

	return ftell(pFil);
}

int main()
{
	static TCHAR     szFileName[MAX_PATH], szTitleName[MAX_PATH];
	HWND      hwnd;

	FILE* filStream;
	char rbuf[100] = {0};
	int filSize = 0;

	hwnd = GetForegroundWindow(); //获取前台窗口句柄。本程序中的前台窗口就是控制台窗口。 
	PopFileInitialize(hwnd);  //初始化ofn
	PopFileOpenDlg(hwnd, szFileName, szTitleName);//打开文件对话框
 
//	printf("%s\n", szFileName);  //在控制台中显示选中文件的路径

	/*读取选中的文件，并在控制台上打印出来*/
	filStream = fopen(szFileName, "r+");
	if (NULL == filStream)
		printf("open failed\n");
	filSize = GetFilSize(filStream);
	fseek(filStream, 0, SEEK_SET);
	fread(rbuf, 1, filSize, filStream);
	fclose(filStream);

	printf("%s\n", rbuf);
	system("pause");

	return 0;
}
