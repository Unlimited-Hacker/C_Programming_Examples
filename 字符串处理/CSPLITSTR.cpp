////�ַ������ô��� ��ȥ��-�󲹿ո�---���#include <splitstr.h>ͷ�ļ�
#include <stdio.h>
#include <cstring>
#include "splitstr.h"
#include <iostream>
using namespace std;
int main()
{
    char mat_no[20] = "H1345   ";
    char left_zero[10] = "000abcde";

    //ͨ��trim_r(char *t)ʵ�ֶ��ַ�����ȥ�ո�
    CSPLITSTR::trim_r(mat_no);

    //ͨ��TrimLeftZeroStr(char *ibuf)ʵ�ֶ��ַ�����ȥ'0'
    CSPLITSTR::TrimLeftZeroStr(left_zero);
    
    cout<< mat_no << "123" <<endl;
    cout<< "123" << left_zero << "123" <<endl;
    return 0;
}