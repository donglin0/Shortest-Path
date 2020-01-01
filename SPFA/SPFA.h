#pragma once
#include<iostream>
#include<string>
#include<queue>
using namespace std;
/*
���㷨��ʹ��SPFA�����ͼ�ĵ�Դ���·������
�������ڽӱ���Ϊͼ�Ĵ洢�ṹ
����Ӧ�����κ��޻���ͼ
*/

//��ṹ
struct ArcNode {
	int adjvex;      //�ߵ�����һ�ߵĶ����±�
	ArcNode* next; //��һ���ߵı���
	int weight;
};
struct Vnode {
	string data;           //������Ϣ
	ArcNode* firstarc;  //��һ�������ڸö���ı�
};

struct Dis {
	string path;  //�Ӷ��㵽�øö������·��
	int  weight;  //���·����Ȩ��
};

class Graph {
private:
	int vexnum;    //�ߵĸ���
	int edge;       //�ߵ�����
	Vnode* node; //�ڽӱ�
	Dis* dis;   //��¼���·����Ϣ������
public:
	Graph(int vexnum, int edge);
	~Graph();
	void createGraph(int); //����ͼ
	bool check_edge_value(int, int, int); //�жϱߵ���Ϣ�Ƿ�Ϸ�
	void print();  //��ӡͼ���ڽӱ�
	bool SPFA(int begin);   //������·��
	void print_path(int begin); //��ӡ���·��
};

