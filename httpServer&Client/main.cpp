//#include "stdafx.h"
//ע���Ҹ����룬�ᱨ�� �������Ϊע�͵����ļ���ֹ��ɾ������ε�ע�͡�����
#include <WinSock2.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string>

#pragma comment(lib,"ws2_32")

#define HALO_S_PORT     9090

/*
LPVOID��һ��û�����͵�ָ�룬Ҳ����˵����Խ�LPVOID���͵ı�����ֵ���������͵�ָ�룬
�����ڲ�������ʱ�Ϳ��԰��������ʹ��ݸ�һ��LPVOID����Ϊ�����ķ�����
Ȼ���ڷ������ٽ�������������͡��Ӵ���ʱ�ġ�LPVOID���͡�ת��������
*/

//����߳�recv���󣬴��������ٽ����ݷ���fd��ȥ
static DWORD CALLBACK FdHandler(IN LPVOID lpCtx) {		//����һ���̺߳��� //��fd���뵽����

	SOCKET fd = (SOCKET)lpCtx;
	char  *Buffer = new char[8193];
	int    i = recv(fd, Buffer, 8192, 0);			//��TCP����һ�˽������ݣ����ص���ʵ��copy���ֽ���
	if (i > 0) {
		Buffer[i] = '\0';
		char *h = new char[i + 1];
		strcpy(h, Buffer);
		printf("\r\n%s\r\n", Buffer);
		//
		// http request parsing, and generate http response
		//
		i = sprintf(Buffer,
			"HTTP/1.1 200 OK\r\n"
			"Content-Type: text/html\r\n"
			"Connection: Close\r\n\r\n"
		);
		FILE *pf = fopen("halos_html.txt", "r");
		i += fread(&Buffer[i], 1, 8192 - i, pf);		//pf���ݶ���buffer
		/*����ԭ��
size_t fread ( void *buffer, size_t size, size_t count, FILE *stream) ;
buffer ���ڽ������ݵ��ڴ��ַ
size   Ҫ����ÿ����������ֽ�������λ���ֽ�
count  Ҫ��count�������ÿ��������size���ֽ�.
stream ������
����ֵ ������ʵ��ȡ��������������count����ζ�Ų����˴���*/

		Buffer[i] = '\0';
		fclose(pf);

		char *p = strstr(Buffer, "%_HALO_%");//strstr(str1, str2) ���������ж��ַ���str2�Ƿ���str1���Ӵ��� ����ǣ���ú�������str2��str1���״γ��ֵĵ�ַ�����򣬷���NULL��
		if (p) {								//??????????????????????????

			*p = '\0';
			std::string tmp = Buffer;
			tmp += h;
			tmp += &p[0];
			i = (int)tmp.size();
			memcpy(Buffer, tmp.c_str(), i);//��srcָ���ַΪ��ʼ��ַ������n���ֽڵ����ݸ��Ƶ���destinָ���ַΪ��ʼ��ַ�Ŀռ��ڡ�

			Buffer[i] = '\0';

		}
		printf("size:%d\r\n%s\r\n", i, Buffer);			//��ӡhalos_html.txt������

		i = send(fd, Buffer, i, 0);
	}
	delete[]Buffer;
	Sleep(1000);
	closesocket(fd);
	return 0;
}

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	WSAStartup(0x0202, &wsaData);
	SOCKADDR_IN addr;
	SOCKET lfd = socket(PF_INET, SOCK_STREAM, 0);
	int i;

	addr.sin_addr.S_un.S_addr = 0;
	addr.sin_family = PF_INET;
	addr.sin_port = htons(HALO_S_PORT);

	i = bind(lfd, (const sockaddr*)&addr, sizeof(SOCKADDR_IN));
	if (i != NOERROR) {
		printf("Oops, failed to bind:%d port\r\n", HALO_S_PORT);
		return 0;
	}
	listen(lfd, 1970);		//�������ֹ����еȴ����������������SYN_FLOOD����
	do {
		i = sizeof(SOCKADDR_IN);
		SOCKET fd = accept(lfd, (sockaddr*)&addr, &i);
		if (fd != INVALID_SOCKET) {
			printf("\r\ncoming from [%s:%d]\r\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));//����Ҫ��֤һ������ addr���Ǳ�������
					//�˿������ʱ��Ҫת��Ϊhost��ʽ
			HANDLE hThread = CreateThread(NULL, 0,
				FdHandler,
				(LPVOID)fd,
				0,
				NULL);
			CloseHandle(hThread);
/*
HANDLE CreateThread(
                    LPSECURITY_ATTRIBUTES lpThreadAttributes,ָ��SECURITY_ATTRIBUTES��ָ�룬���ڶ������̵߳İ�ȫ���ԣ�һ�����ó�NULL��
                    DWORD dwStackSize,�������ֽ�����ʾ���̶߳�ջ�Ĵ�С��Ĭ��ֵ��0��
                    LPTHREAD_START_ROUTINE lpStartAddress,ָ��һ���̺߳�����ַ��ÿ���̶߳����Լ����̺߳������̺߳������߳̾����ִ�д��룻
                    LPVOID lpParameter,���ݸ��̺߳����Ĳ�����
                    DWORD dwCreationFlags,��ʾ�����̵߳�����״̬������CREATE_SUSPEND��ʾ����ǰ�������̣߳���0��ʾ����ִ�е�ǰ�����Ľ��̣�
                    LPDWORD lpThreadID�����´������̵߳�ID��ţ�
                   );
				   ����������óɹ����򷵻����̵߳ľ����
*/
		}
		else {
			printf("Something is wrong\r\n");		//����wrong ����� û�ȵ���������Ӧ�����Է������˻���SYN_FLOOD����
		}
	} while ("Go ahead");

	WSACleanup();
	return 0;
}
//��������������������������������
//��Ȩ����������ΪCSDN������iroy33����ԭ�����£���ѭ CC 4.0 BY-SA ��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
//ԭ�����ӣ�https://blog.csdn.net/iroy33/article/details/88802916
