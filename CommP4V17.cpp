#include "BINWORK.h"

using namespace std;

struct node // структура для представления узлов дерева
{
	int key=0;
	int row=0;
	unsigned char height=0;
	node* left=NULL;
	node* right=NULL;
	node(int k, int r) { key = k; row = r; left = right = 0; height = 1; }
};

class AVLTree {
public:
	node* root=NULL;

	unsigned char height(node* p)
	{
		return p ? p->height : 0;
	}

	int bfactor(node* p)
	{
		return height(p->right) - height(p->left);
	}

	void fixheight(node* p)
	{
		unsigned char hl = height(p->left);
		unsigned char hr = height(p->right);
		p->height = (hl > hr ? hl : hr) + 1;
	}

	node* rotateright(node* p) // правый поворот вокруг p
	{
		node* q = p->left;
		p->left = q->right;
		q->right = p;
		fixheight(p);
		fixheight(q);
		return q;
	}

	node* rotateleft(node* q) // левый поворот вокруг q
	{
		node* p = q->right;
		q->right = p->left;
		p->left = q;
		fixheight(q);
		fixheight(p);
		return p;
	}

	node* balance(node* p) // балансировка узла p
	{
		fixheight(p);
		if (bfactor(p) == 2)
		{
			if (bfactor(p->right) < 0)
				p->right = rotateright(p->right);
			return rotateleft(p);
		}
		if (bfactor(p) == -2)
		{
			if (bfactor(p->left) > 0)
				p->left = rotateleft(p->left);
			return rotateright(p);
		}
		return p; // балансировка не нужна
	}

	node* insert(node* p, int k, int r) // вставка ключа k в дерево с корнем p
	{
		if (!p) return new node(k,r);
		if (k < p->key)
			p->left = insert(p->left, k,r);
		else
			p->right = insert(p->right, k,r);
		return balance(p);
	}

	node* findmin(node* p) // поиск узла с минимальным ключом в дереве p 
	{
		return p->left ? findmin(p->left) : p;
	}

	node* removemin(node* p) // удаление узла с минимальным ключом из дерева p
	{
		if (p->left == 0)
			return p->right;
		p->left = removemin(p->left);
		return balance(p);
	}

	node* remove(node* p, int k) // удаление ключа k из дерева p
	{
		if (!p) return 0;
		if (k < p->key)
			p->left = remove(p->left, k);
		else if (k > p->key)
			p->right = remove(p->right, k);
		else //  k == p->key 
		{
			node* q = p->left;
			node* r = p->right;
			delete p;
			if (!r) return q;
			node* min = findmin(r);
			min->right = removemin(r);
			min->left = q;
			return balance(min);
		}
		return balance(p);
	}

	void printTree(node* w, int l)//Вывод дерева слева направо
	{
		if (w != NULL)
		{
			printTree(w->right, l + 1);
			for (int i = 1; i <= l; i++) cout << "   ";
			cout << w->key<<' '<<w->row  << endl;
			printTree(w->left, l + 1);
		}
	}

	node* find(node* p,int k) {//Поиск по ключу
		if (!p) return NULL;
		if (p->key == k) return p;
		else if (p->key > k) return find(p->left, k);
		else return find(p->right,k);
	}

	

};

int main() {

	AVLTree bt;
	cout << "1-Add record\n2-Delete record\n3-Print tree\n4-Find record\n0-exit\n";
	int input;
	string name;
	string word;
	int n;
	record r;
	int curPos = 0;
	node* findRes;
	//Имя бинарного файла в котором хранится вся информация
	string binName = "data";
	//Poggers.txt файл с исходными записями, можно изменить название
	CreateBinFile("Poggers.txt", binName);
	vector<record> R = outBinFile(binName);
	
	for (int i = 0; i < R.size(); ++i) {
		bt.root=bt.insert(bt.root, R[i].key, i);
		curPos++;
	}
	cin >> input;
	while (input != -1) {
		//Разбор ввода
		switch (input)
		{
		case 1:
			cout << "Print word\n";
			
			cin >> word;
			cout << "Print number of entries\n";
			cin >> n;
			bt.insert(bt.root, n,curPos);
			
			r.key = n;
			word.copy(r.data, word.size() + 1);
			addRecord(binName, r);
			break;
		case 2:
			cout << "Print key\n";
			cin >> n;
			findRes = bt.find(bt.root, n);
			if ( findRes == NULL) {
				cout << "Not found\n";
				break;
			}
			else {
				deleteRecord(binName, findRes->row);
				bt.remove(bt.root, n);
				
			}
			break;
		case 3:
			bt.printTree(bt.root, 0);
			break;
		case 4:
			cin >> n;
			findRes = bt.find(bt.root, n);
			if (findRes != NULL) {
				cout << findRes->key << ' ' << findRes->row << '\n';
			}
			else cout << "Not found!\n";
			break;
		case 0:
			return 0;
		default:
			cout << "Wrong input! Try again";
			break;
		}
		cout << "Done!\n";
		cin >> input;
	}

	return 0;
}