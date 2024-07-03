#include<iostream>
#include<fstream>
#include<sstream>
#include<string.h>
#include<stdio.h>
#include<bits/stdc++.h>
#include<vector>
#include<sys/time.h>
#define NUM 43577
#define E_NUM 54274

using namespace std;

struct line{
    //是否升级为消元子
    bool b;
    //首个1的位置
    int num;
    bitset<NUM> bit;
};

//消元子eliminer1
bitset<NUM> eliminer[NUM]; 
//被消元行eline1
line eline[E_NUM];


void cout1()
{
    cout<<"*****消元子******"<<NUM<<endl;
    for(int i = 0;i<NUM;i++)
        cout<<eliminer[i]<<endl;

    cout<<"*****被消元行****"<<E_NUM<<endl;
    for(int i = 0;i<E_NUM;i++)
        cout<<eline[i].b<<"  "<<eline[i].bit<<endl;
}

//判断是否全部消去完成
bool check_null()
{
    for(int i = 0;i<E_NUM;i++)
    {
        if(eline[i].b==false)
            return false;
    }
    return true;
}

void res()
{
    int rt = 0;
    for(int i = 0;i<NUM;i++)
    {
        if(eliminer[i].any())
        {
            rt++;
        }
       
    }
    cout<<"行数："<<rt;
}

int main()
{

    ifstream file;
    file.open("/home/cloud/parallel/qimo/data/7/消元子.txt",ios_base::in);

    //file.open("/home/cloud/parallel/qimo/data/1/消元子.txt",ios_base::in);
    //file.open("/home/cloud/parallel/qimo/data/2/消元子.txt",ios_base::in);
    //file.open("/home/cloud/parallel/qimo/data/3/消元子.txt",ios_base::in);
    //file.open("/home/cloud/parallel/qimo/data/4/消元子.txt",ios_base::in);
    //file.open("/home/cloud/parallel/qimo/data/5/消元子.txt",ios_base::in);
    //file.open("/home/cloud/parallel/qimo/data/6/消元子.txt",ios_base::in);
    //file.open("/home/cloud/parallel/qimo/data/7/消元子.txt",ios_base::in);
    //file.open("/home/cloud/parallel/qimo/data/8/消元子.txt",ios_base::in);
    //file.open("/home/cloud/parallel/qimo/data/9/消元子.txt",ios_base::in);
    //file.open("/home/cloud/parallel/qimo/data/10/消元子.txt",ios_base::in);
    //file.open("/home/cloud/parallel/qimo/data/11/消元子.txt",ios_base::in);

    if(!file.is_open())
    {
        cout<<"打开失败"<<endl;
    }
    string s;
    
    while(getline(file,s))
    {
        bool b = true;
        int x;
        //cout<<s<<endl;
        stringstream st;
        int temp;
        st<<s;
        
        while(st>>temp)
        {
            if(b)
            {
                x = temp;
                b = false;
            }

            eliminer[x].set(temp);
        }      

    }
    
    file.close();
    file.clear(ios::goodbit);

    file.open("/home/cloud/parallel/qimo/data/7/被消元行.txt",ios_base::in);

    //file.open("/home/cloud/parallel/qimo/data/1/被消元行.txt",ios_base::in);
    //file.open("/home/cloud/parallel/qimo/data/2/被消元行.txt",ios_base::in);
    //file.open("/home/cloud/parallel/qimo/data/3/被消元行.txt",ios_base::in);
    //file.open("/home/cloud/parallel/qimo/data/4/被消元行.txt",ios_base::in);
    //file.open("/home/cloud/parallel/qimo/data/5/被消元行.txt",ios_base::in);
    //file.open("/home/cloud/parallel/qimo/data/6/被消元行.txt",ios_base::in);
    //file.open("/home/cloud/parallel/qimo/data/7/被消元行.txt",ios_base::in);
    //file.open("/home/cloud/parallel/qimo/data/8/被消元行.txt",ios_base::in);
    //file.open("/home/cloud/parallel/qimo/data/9/被消元行.txt",ios_base::in);
    //file.open("/home/cloud/parallel/qimo/data/10/被消元行.txt",ios_base::in);
    //file.open("/home/cloud/parallel/qimo/data/11/被消元行.txt",ios_base::in);
    

    if(!file.is_open())
    {
        cout<<"打开失败"<<endl;
    }
    int x = 0;
    while(getline(file,s))
    {
        //cout<<s<<endl;
        bool bo = true;
        stringstream st;
        int temp;
        st<<s;
        eline[x].b=false;

        while(st>>temp)
        {
            if(bo)
            {
                bo = false;
                eline[x].num=temp;
            }
            eline[x].bit.set(temp);
            //eliminer[x].set(temp);
        }  
        x++;    
    }
    file.close();
    int rt = 0;
    //cout1();
    int p = 5;

//    for(int i = 0;i<E_NUM;i++)
//     {
//             for(int j = NUM-1;j>=0;j--)
//                 if(eline[i].bit[j]==1)
//                     cout<<j<<" ";
//             cout<<endl;
//     }
    cout<<"start"<<endl;
    struct timeval begin1,end1;
    gettimeofday(&begin1,NULL);
    for(int i = NUM-1;i>=0;i-=p)
    {
        if(i-p<0)
        {
            cout<<"p=i+1"<<endl;
            p=i+1;
        }
        for(int j = 0;j<E_NUM;j++)
        {
            if(eline[j].b==0)
            {
                for(int k = 0;k<p;k++)
                {
                    if(eline[j].bit[i-k]==1)
                    {
                        //消去过程
                        eline[j].bit^=eliminer[i-k];
                    }
                    if(eline[j].bit.none())
                    {
                        eline[j].b=true;
                        cout<<"null"<<rt++<<endl;
                        break;
                    }
                    else
                    {
                        for(int l = eline[j].num;l>=0;l--)
                        {
                            if(eline[j].bit[l]==1)
                            {
                                eline[j].num = l;
                                break;
                            }
                        }
                        if(eliminer[eline[j].num].none())
                        {
                            eliminer[eline[j].num]^=eline[j].bit;
                            eline[j].b=true;
                            //eline[j].num;
                            cout<<rt++<<endl;
                            break;                
                        }
                    }                
                }
                
            }       
        }
        if(check_null())
        {
            cout<<"null"<<endl;
            break;
        }      
    } 
    //cout1();
    gettimeofday(&end1,NULL);
    long long time_use = ((end1.tv_sec-begin1.tv_sec)*1000000 + end1.tv_usec-begin1.tv_usec)/1000;
    res();
    //cout1();
    cout<<time_use<<endl;
    
    return 0;
}
