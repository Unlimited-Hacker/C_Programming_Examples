//ͨ������������������Ƿ�����
#include <stdio.h>
#include <Windows.h>
#include <iostream>
using namespace std;

char IPname[20];
	BOOL IsAlreadyRun()
	{
		HANDLE hMutex = NULL;
		hMutex = ::CreateMutex(NULL, FALSE, IPname);
		if (hMutex)
		{
			if(ERROR_ALREADY_EXISTS == ::GetLastError())
			{
				return TRUE;
			}
		}
		return FALSE;
	}
	int	main()
	{
		while(1)
		{
			cout << "���뻥���������:" << endl;
			cin >> IPname;
			if(IsAlreadyRun())
			{
				printf("alreadyRun!!!");
			}
			else 
			{
				printf("NotAlreadyRun!!!!");
			}
		}
	}