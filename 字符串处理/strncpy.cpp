//�÷�:strncpy(sub,string+12,13)/*��string�д�string[12]��ʼ��13�����ָ��Ƶ�sub��*/
//�� ok! ��string[25]��ǰ19λ�ַ����Ƶ�a��
#include <iostream>
#include "string.h"
using namespace std;
int main()
{
	#define size 200//
	char a[size];
	memset(a,0x00,sizeof(a));
	char string[25]= "2007-12-20 18:31:34:123";
	strncpy(a,string,19);
	cout<<a<< endl;
	system ("pause");
	return 0;  
}