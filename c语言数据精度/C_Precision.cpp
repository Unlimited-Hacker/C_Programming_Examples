#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    float a=12.257902012398877;
    double b=12.257902012398877;
    const float PI=3.1415926;         // ��������
    cout<<setprecision(15)<<a<<endl;  // floatֻ��6-7λ��Ч���֣�����ľͲ���ȷ
    cout<<setprecision(15)<<b<<endl;  // double��15-16λ��Ч���֣�������ȫ��ȷ
    cout<<setprecision(15)<<PI<<endl; 
    cout<<setprecision(3)<<PI<<endl; //����3λ��Ч����
    return 0;
}