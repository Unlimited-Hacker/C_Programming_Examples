//ͷ�ļ���#include <string.h>
//strcat����ֱ�ӰѺ�һ���ַ���ƴ�ӵ�ǰһ���ַ�����
// strcat() �������������ַ�������ԭ��Ϊ��char *strcat(char *dest, const char *src);
//��������dest ΪĿ���ַ���ָ�룬src ΪԴ�ַ���ָ�롣
//strcat() �Ὣ���� src �ַ������Ƶ����� dest ��ָ���ַ���β����dest ���Ľ����ַ� NULL �ᱻ���ǵ����������Ӻ���ַ�����β��������һ�� NULL��
//ע�⣺dest �� src ��ָ���ڴ�ռ䲻���ص����� dest Ҫ���㹻�Ŀռ�������Ҫ���Ƶ��ַ�����
//������ֵ������dest �ַ�����ʼ��ַ��
#include <stdio.h>
#include <string.h>
int main ()
{
    char str[80];
    strcpy (str,"these ");
    strcat (str,"strings ");
    strcat (str,"are ");
    strcat (str,"concatenated.");
    puts (str);//���ַ����������׼����豸����'\0'ת��Ϊ�س�����
    return 0;
}