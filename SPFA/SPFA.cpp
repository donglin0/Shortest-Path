#include "SPFA.h"


Graph::Graph(int vexnum, int edge) {
	//�Զ�������ͱߵ��������и�ֵ
	this->vexnum = vexnum;
	this->edge = edge;

	//Ϊ�ڽӾ��󿪱ٿռ�
	node = new Vnode[this->vexnum];
	dis = new Dis[this->vexnum];
	int i;
	//���ڽӱ���г�ʼ��
	for (i = 0; i < this->vexnum; ++i) {
		node[i].data = "v" + to_string(i + 1);
		node[i].firstarc = NULL;
	}
}

Graph::~Graph() {
	int i;
	//�ͷſռ䣬���Ǽ�סͼ��ÿ����������ҲҪһһ�ͷ�
	ArcNode* p, * q;
	for (i = 0; i < this->vexnum; ++i) {
		//һ��Ҫע�����Ҫ�жϸö���ĳ��ȵ����Ƿ�Ϊ�գ���Ȼ�����
		if (this->node[i].firstarc) {
			p = node[i].firstarc;
			while (p) {
				q = p->next;
				delete p;
				p = q;
			}
		}

	}
	delete[] node;
	delete[] dis;
}

// �ж�����ÿ������ĵıߵ���Ϣ�Ƿ�Ϸ�
//�����1��ʼ���
bool Graph::check_edge_value(int start, int end, int weight) {
	if (start<1 || end<1 || start>vexnum || end>vexnum || weight < 0) {
		return false;
	}
	return true;
}

void Graph::print() {
	cout << "ͼ���ڽӱ�Ĵ�ӡ��" << endl;
	int i;
	ArcNode* temp;
	//��������ڽӱ�
	for (i = 0; i < this->vexnum; ++i) {
		cout << node[i].data << " ";
		temp = node[i].firstarc;
		while (temp) {
			cout << "<"
				<< node[i].data
				<< ","
				<< node[temp->adjvex].data
				<< ">="
				<< temp->weight
				<< " ";
			temp = temp->next;
		}
		cout << "^" << endl;
	}
}

void Graph::createGraph(int kind) {
	//kind����ͼ�����࣬2Ϊ����ͼ
	cout << "����ߵ������յ��Լ����ߵ�Ȩ��(�����Ŵ�1��ʼ)��" << endl;
	int i;
	int start;
	int end;
	int weight;
	for (i = 0; i < this->edge; ++i) {
		cin >> start >> end >> weight;
		//�ж�����ı��Ƿ�Ϸ�
		while (!this->check_edge_value(start, end, weight)) {
			cout << "����ߵ���Ϣ���Ϸ������������룺" << endl;
			cin >> start >> end >> weight;
		}
		ArcNode* temp = new ArcNode;
		temp->adjvex = end - 1;
		temp->weight = weight;
		temp->next = NULL;
		//����ö��������ı�Ϊ�գ�����Ե�һ����ʼ
		if (node[start - 1].firstarc == NULL) {
			node[start - 1].firstarc = temp;
		}
		else {//��������뵽����������һ��λ��
			ArcNode* now = node[start - 1].firstarc;
			//�ҵ���������һ�����
			while (now->next) {
				now = now->next;
			}
			now->next = temp;
		}
		//���������ͼ������ҲҪ����µĽ��
		if (kind == 2) {
			//�½�һ���µı���
			ArcNode* temp_end = new ArcNode;
			temp_end->adjvex = start - 1;
			temp_end->weight = weight;
			temp_end->next = NULL;
			//����ö��������ı�Ϊ�գ�����Ե�һ����ʼ
			if (node[end - 1].firstarc == NULL) {
				node[end - 1].firstarc = temp_end;
			}
			else {//��������뵽����������һ��λ��
				ArcNode* now = node[end - 1].firstarc;
				//�ҵ���������һ�����
				while (now->next) {
					now = now->next;
				}
				now->next = temp_end;
			}
		}

	}
}

bool Graph::SPFA(int begin) {
	bool* visit;
	//visit���ڼ�¼�Ƿ��ڶ�����
	visit = new bool[this->vexnum];
	int* input_queue_time;
	//input_queue_time���ڼ�¼ĳ����������еĴ���
	//���ĳ������еĴ������ڶ�����vexnum����ô˵�����ͼ�л���
	//û�����·���������˳���
	input_queue_time = new int[this->vexnum];
	queue<int> s;  //���У����ڼ�¼���·�����ı�ĵ�

	/*
	���ֱ����ĳ�ʼ��
	*/
	int i;
	for (i = 0; i < this->vexnum; i++) {
		visit[i] = false;
		input_queue_time[i] = 0;
		//·����ʼ����ʼ��Ϊֱ��·��,���ȶ�����Ϊ�����
		dis[i].path = this->node[begin - 1].data + "-->" + this->node[i].data;
		dis[i].weight = INT_MAX;
	}
	//�������������У����Ǽ�ס�Ǹ���������Ƕ����ţ���1��ʼ��
	s.push(begin - 1);
	visit[begin - 1] = true;
	++input_queue_time[begin - 1];
	//
	dis[begin - 1].path = this->node[begin - 1].data;
	dis[begin - 1].weight = 0;

	int temp;
	int res;
	ArcNode* temp_node;
	//������е�ѭ��
	while (!s.empty()) {
		//ȡ�����׵�Ԫ�أ����ҰѶ���Ԫ�س�����
		temp = s.front(); s.pop();
		//����Ҫ��֤��һ����㲻Ϊ��
		if (node[temp].firstarc)
		{
			temp_node = node[temp].firstarc;
			while (temp_node) {
				//�����<temp,temp_node>��Ȩ�ؼ���temp���������·��
				//С��֮ǰtemp_node�����·���ĳ��ȣ������
				//temp_node�����·������Ϣ
				if (dis[temp_node->adjvex].weight > (temp_node->weight + dis[temp].weight)) {
					//����dis�������Ϣ
					dis[temp_node->adjvex].weight = temp_node->weight + dis[temp].weight;
					dis[temp_node->adjvex].path = dis[temp].path + "-->" + node[temp_node->adjvex].data;
					//�����û�ڶ����У�������У��޸Ķ�Ӧ����Ϣ
					if (!visit[temp_node->adjvex]) {
						visit[temp_node->adjvex] = true;
						++input_queue_time[temp_node->adjvex];
						s.push(temp_node->adjvex);
						if (input_queue_time[temp_node->adjvex] > this->vexnum) {
							cout << "ͼ���л�" << endl;
							return false;
						}
					}
				}
				temp_node = temp_node->next;
			}
		}
	}

	//��ӡ���·��

	return true;
}

void Graph::print_path(int begin) {
	cout << "�Զ���" << this->node[begin - 1].data
		<< "Ϊ��㣬��������������·������Ϣ��" << endl;
	int i;
	for (i = 0; i < this->vexnum; ++i) {
		if (dis[i].weight == INT_MAX) {
			cout << this->node[begin - 1].data << "---"
				<< this->node[i].data
				<< "  �����·�������������㲻��ͨ" << endl;
		}
		else
		{
			cout << this->node[begin - 1].data << "---"
				<< this->node[i].data
				<< "  Ȩֵ: "
				<< dis[i].weight
				<< "  ·��: "
				<< dis[i].path
				<< endl;
		}

	}
}
