#pragma once
/************************************************************/
/*                �������ߣ�Willam                          */
/*                �������ʱ�䣺2017/3/11                   */
/*                ���κ���������ϵ��2930526477@qq.com       */
/************************************************************/
//@����д�������ĳ���

#pragma once
//#pragma once��һ���Ƚϳ��õ�C/C++��ע��
//ֻҪ��ͷ�ļ����ʼ����������ע��
//���ܹ���֤ͷ�ļ�ֻ������һ�Ρ�

/*
�����Ϳ�ʼ��Floyd�㷨��ʹ���ڽӾ���ʵ�ֵ�
*/

#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

class Graph_DG {
private:
    int vexnum;   //ͼ�Ķ������
    int edge;     //ͼ�ı���
    int** arc;   //�ڽӾ���
    int** dis;   //��¼�����������·������Ϣ
    int** path;  //��¼�������·������Ϣ
public:
    //���캯��
    Graph_DG(int vexnum, int edge);
    //��������
    ~Graph_DG();
    // �ж�����ÿ������ĵıߵ���Ϣ�Ƿ�Ϸ�
    //�����1��ʼ���
    bool check_edge_value(int start, int end, int weight);
    //����ͼ
    void createGraph(int);
    //��ӡ�ڽӾ���
    void print();
    //�����·��
    void Floyd();
    //��ӡ���·��
    void print_path();
};


