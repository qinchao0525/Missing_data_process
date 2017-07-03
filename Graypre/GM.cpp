# include "GM.h"
# include <vector>
# include <cmath>
double GM_returnk_1(double a[], int a_num)
{
    vector<double> X0(a_num);
    vector<double> X1(a_num);
    //X0,X1
    for (int i=0; i<a_num; i++)
        X0[i] = a[i];
    for (int i_1=0; i_1<a_num; i_1++)
        X1[i_1] = sum(a,i_1);
    //计算B
    vector<vector<double> > B(a_num-1);
    for (int i_2=0; i_2<a_num-1; i_2++)
        B[i_2].resize(2);
    for (int i_3=0; i_3<a_num-1; i_3++)
    {
        B[i_3][0]=-(X1[i_3]+X1[i_3+1])*0.5;
        B[i_3][1]=1;
    }
    //计算Yn
    vector<double> Yn(a_num-1);
    for (int i_4=0; i_4<a_num-1; i_4++)
        Yn[i_4] = X0[i_4+1];
    //计算a，u
    //Bt和B相乘的结果
    vector<vector<double> > BB(2);
    for (int i_5=0; i_5<2; i_5++)
        BB[i_5].resize(2);

    for (int i_6=0; i_6<2; i_6++)
        for(int j_1=0; j_1<2; j_1++)
    {
        double sum=0;
        for(int k_1=0; k_1<a_num-1; k_1++)
            sum+=B[k_1][i_6]*B[k_1][j_1];
        BB[i_6][j_1]=sum;
    }
    //计算Bt和B相乘的逆
    vector<vector<double> > B_(2);
    for (int i_7=0; i_7<2; i_7++)
        B_[i_7].resize(2);
    double BB_z=0;
    BB_z=BB[0][0]*BB[1][1]-BB[0][1]*BB[1][0];//行列式的值
    B_[0][0]=BB[1][1]/BB_z;
    B_[0][1]=-BB[1][0]/BB_z;
    B_[1][0]=-BB[0][1]/BB_z;
    B_[1][1]=BB[0][0]/BB_z;
    //B_此时为逆矩阵，计算B_ * Bt
    vector<vector<double> > BBb(2);
    for (int i_9=0; i_9<2; i_9++)
        BBb[i_9].resize(a_num-1);
    for (int i_8=0; i_8<2; i_8++)
        for(int j_3=0; j_3<a_num-1; j_3++)
    {
        double sum=0;
        for(int k_2=0; k_2<2; k_2++)
            sum+=B_[i_8][k_2]*B[j_3][k_2];
        BBb[i_8][j_3]=sum;
    }
    //计算结果，BBb为2*5的矩阵
    vector<double> aa(2);
    for(int a_1=0; a_1<2; a_1++)
    {
        double sum=0;
        for(int j_2=0; j_2<a_num-1; j_2++)
            sum+=BBb[a_1][j_2]*Yn[j_2];
        aa[a_1]=sum;
    }
    double Aa=aa[0],Uu=aa[1];
    double re=0;
    re=(X1[0]-Uu/Aa)*exp(-Aa*a_num)+Uu/Aa;
   return (int)(re-X1[a_num-1]);
}
double sum(double a[], int i)
{
    double s=a[0];
    for (int ii=0; ii<i; ii++)
        s+=a[ii+1];
    return s;
}
