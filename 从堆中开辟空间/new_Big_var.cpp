// //new ��������飬������ֹ����������ർ��ջ���--OK
// //��new �Ӷ��п��ٿռ�
// #include <stdio.h>
// #include <iostream>
// using namespace std;
// int main()
// {
// 	//��һ�ַ�ʽ  ����һλ����
// 	double *array;
// 	array = new double[80*1000];//����80*1000 ��С,double����
// 	////���ʵ�ʱ��*(array+i*y+j)��ʾarray[i][j]
// 	for(int i=0;i<80;i++){
// 		for(int j=0;j < 1000;j++){
// 			*(array+i*1000+j) = i+j;
// 		}
// 	}
// 	cout<<"��¼������CPCRec��ֵ�ɹ�����55��,333����Ϊ"<<*(array+55*1000+333)<<endl;
// }

//------------------------------------------------------------------------
//��2 ����һ����ά����
#include <stdio.h>
#include <iostream>
using namespace std;
int main(){
		double **array1;
		array1 = new double *[80];
		for(int i=0;i<80;++i)
			array1[i] = new double[1000];
		//...�õ�ʱ�����ֱ��array1[i][j]
		for(int i=0;i<80;i++){
			for(int j=0;j < 1000;j++){
				array1[i][j] = i+j;
			}
		}
	cout<<"��¼������CPCRec��ֵ�ɹ���"<<array1[50][333]<<endl;
	//��ע�⼰ʱdelete
		for(int i=0;i<80;++i)
			delete[] array1[i];
	delete[] array1;
}
