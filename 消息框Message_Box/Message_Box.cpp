//����WindowsAPI���--MessageBox--ģ̬�Ի���
#include <windows.h>
//WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)

{
	ShowWindow(FindWindow("ConsoleWindowClass",0),0);//�ó�������ʱ����ʾ���ڿ���̨
	int result;
 	result = MessageBox(NULL, TEXT("�����ҵ�һ�ε���WindowsAPI���--MessageBox--ģ̬�Ի���"), TEXT("ľ�����"), MB_ICONEXCLAMATION | MB_YESNO );//MB_ICONEXCLAMATION | MB_OKCANCEL| MB_ICONQUESTION | MB_DEFBUTTON2
    switch(result)
	{
	//case IDYES: MessageBox(NULL,TEXT( "YOU click yes!"),TEXT("alert"),MB_DEFBUTTON2);
	case IDYES: MessageBox(NULL,TEXT( "YOU click yes!"),TEXT("alert"),MB_DEFBUTTON2);
	return 0;
	case  IDNO: MessageBox(NULL,TEXT( "YOU click NO!"),TEXT("alert"),MB_ICONSTOP);
	}
	return 0;

}