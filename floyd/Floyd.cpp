#include"Floyd.h"


//���캯��
Graph_DG::Graph_DG(int vexnum, int edge) {
    //��ʼ���������ͱ���
    this->vexnum = vexnum;
    this->edge = edge;
    //Ϊ�ڽӾ��󿪱ٿռ�͸���ֵ
    arc = new int* [this->vexnum];
    dis = new int* [this->vexnum];
    path = new int* [this->vexnum];
    for (int i = 0; i < this->vexnum; i++) {
        arc[i] = new int[this->vexnum];
        dis[i] = new int[this->vexnum];
        path[i] = new int[this->vexnum];
        for (int k = 0; k < this->vexnum; k++) {
            //�ڽӾ����ʼ��Ϊ�����
            arc[i][k] = INT_MAX;
        }
    }
}
//��������
Graph_DG::~Graph_DG() {
    //�ͷŵ����еķ���Ŀռ�
    for (int i = 0; i < this->vexnum; i++) {
        delete this->arc[i];
        delete this->dis[i];
        delete this->path[i];
    }
    delete dis;
    delete arc;
    delete path;
}

// �ж�����ÿ������ĵıߵ���Ϣ�Ƿ�Ϸ�
//�����1��ʼ���
bool Graph_DG::check_edge_value(int start, int end, int weight) {
    if (start<1 || end<1 || start>vexnum || end>vexnum || weight < 0) {
        return false;
    }
    return true;
}

void Graph_DG::createGraph(int kind) {
    cout << "������ÿ���ߵ������յ㣨�����Ŵ�1��ʼ���Լ���Ȩ��" << endl;
    int start;
    int end;
    int weight;
    int count = 0;
    while (count != this->edge) {
        cin >> start >> end >> weight;
        //�����жϱߵ���Ϣ�Ƿ�Ϸ�
        while (!this->check_edge_value(start, end, weight)) {
            cout << "����ıߵ���Ϣ���Ϸ�������������" << endl;
            cin >> start >> end >> weight;
        }
        //���ڽӾ����Ӧ�ϵĵ㸳ֵ
        arc[start - 1][end - 1] = weight;
        //����ͼ��������д���
        if (kind == 2)
            arc[end - 1][start - 1] = weight;//����ͼΪ�Գƾ���
        ++count;
    }
}

void Graph_DG::print() {
    cout << "ͼ���ڽӾ���Ϊ��" << endl;
    int count_row = 0; //��ӡ�еı�ǩ
    int count_col = 0; //��ӡ�еı�ǩ
                       //��ʼ��ӡ
    while (count_row != this->vexnum) {//����ѭ��Ƕ������ڽӾ���
        count_col = 0;
        while (count_col != this->vexnum) {
            if (arc[count_row][count_col] == INT_MAX)
                cout <<setw(5)<< "��" ;
            else
                cout<< setw(5)<< arc[count_row][count_col] ;
            ++count_col;//�кż�һ
        }
        cout << endl;
        ++count_row;
    }
}

void Graph_DG::Floyd() {
    int row = 0;
    int col = 0;
    for (row = 0; row < this->vexnum; row++) {
        for (col = 0; col < this->vexnum; col++) {
            //�Ѿ���D��ʼ��Ϊ�ڽӾ����ֵ
            this->dis[row][col] = this->arc[row][col];
            //����P�ĳ�ֵ��Ϊ�����ߵ��յ㶥����±�
            this->path[row][col] = col;
        }
    }

    //����ѭ�������ڼ���ÿ����Ե����·��
    int temp = 0;//�н��
    int select = 0;
    for (temp = 0; temp < this->vexnum; temp++) {
        for (row = 0; row < this->vexnum; row++) {
            for (col = 0; col < this->vexnum; col++) {
                //Ϊ�˷�ֹ�����������Ҫ����һ��selectֵ
                select = (dis[row][temp] == INT_MAX || dis[temp][col] == INT_MAX) ? INT_MAX : (dis[row][temp] + dis[temp][col]);
                if (this->dis[row][col] > select) {
                    //�������ǵ�D����
                    this->dis[row][col] = select;
                    //�������ǵ�P����
                    this->path[row][col] = this->path[row][temp];
                }
            }
        }
    }
}

void Graph_DG::print_path() {
    cout << "��������Ե����·����" << endl;
    int row = 0;
    int col = 0;
    int temp = 0;
    for (row = 0; row < this->vexnum; row++) {
        for (col = row + 1; col < this->vexnum; col++) {//����ֵת��Ϊ�ַ��������ض�Ӧ���ַ�����
            cout << "v" << to_string(row + 1) << "---" << "v" << to_string(col + 1) << " Ȩֵ: "
                << this->dis[row][col] << " ·��: " << " v" << to_string(row + 1);
            temp = path[row][col];
            //ѭ�����;����ÿ��·����
            while (temp != col) {
                cout << "-->" << "v" << to_string(temp + 1);
                temp = path[temp][col];
            }
            cout << "-->" << "v" << to_string(col + 1) << endl;
        }

        cout << endl;
    }
}
