// DSD.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>

using namespace std;

class sl_list {
private: 
	int data;
	sl_list * next;
	bool first;//флаг того, есть хотя бы один элемент в списке или нет
public:
	sl_list();
	sl_list(int);
	void show();
	sl_list * search(int key);
	sl_list * insert(int key);//в начало
	bool del(sl_list * d);
	bool del(int x);
	void add(int x);//в конец
};

sl_list::sl_list() {
	this->next = nullptr;
	//this->data = 0;
	first = false;
}

sl_list::sl_list(int n) {
	this->next = nullptr;
	this->data = n;
	first = true;
}

void sl_list::show() {
	if (this == nullptr) {
		cout << "The sl_list is empty. In show";
	}
	else {
		sl_list * temp = this;
		while (temp != nullptr) {
			cout << temp->data << ' ';
			temp = temp->next;
		}
		cout << endl;
	}
}

sl_list * sl_list::search(int key) {
	if (this == nullptr) {
		cout << "The sl_list is empty. In search";
		return nullptr;
	}
	else {
		sl_list * temp = this;
		while ((temp->next != nullptr) && (temp->data != key)) {
			temp = temp->next;
		}
		if (temp->data == key) {
			return temp;
		}
		else {
			return nullptr;
		}
	}
}

sl_list * sl_list::insert(int key) {//в начало (перед элементом, из которого вызывается эта функция) 
	sl_list * temp = new sl_list;
	temp->data = key;
	if (this == nullptr) {
		temp->next = nullptr;
	}
	else {
		if (first == true) {
			temp->next = this;
		}
		else {//в this еще не записывали элемент
			delete temp;//костыль
			this->data = key;
			first = true;
			return this;//в него вставили, его и возвращаем
		}
	}
	return temp;
}

bool sl_list::del(sl_list * d) {//поиск элемента и удаление его из списка
	sl_list * temp = this;
	sl_list * temp2 = this;
	while ((temp != d) && (temp != nullptr)) {
		temp2 = temp;
		temp = temp->next;
	}
	if (temp == nullptr) {//элемент не найден
		return false;
	}
	else {//надо удалить этот элемент, а ссылку предыдущего направить на его следующий элемент
		//для двух элементов и найденном во втором нормально работает
		if (temp == temp2) {//удаляемый элемент первый, придётся сдвинуть весь список к голове
			//? проверить это на практике
			temp2 = temp2->next;
			delete temp;

			/*while (temp2 != nullptr) {

			}*/
		}
		//? добавить разбор ситуации, когда один элемент в списке только
		temp2->next = temp->next;
		delete temp;
	}
}

bool sl_list::del(int x) {
	sl_list * temp = this;
	sl_list * temp2 = this;
	while ((temp->data != x) && (temp != nullptr)) {
		temp2 = temp;
		temp = temp->next;
	}
	if (temp == nullptr) {//элемент не найден
		return false;
	}
	else {
		temp2->next = temp->next;
		delete temp;
	}

}

void sl_list::add(int x)//в конец
{
	if (first == true) {//список не пуст
		sl_list * temp = this;
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = new sl_list;
		temp->next->data = x; 
		temp->next->next = nullptr;
	}
	else {//список пуст
		//sl_list * temp = new sl_list;
		this->data = x;
		first = true;
		//temp->next = nullptr;
	}
}

class dl_list {
private:
	int data;
	dl_list * next;
	dl_list * prev;
	bool first;//флаг того, есть хотя бы один элемент в списке или нет
public:
	dl_list();
	dl_list(int);
	void show();
	dl_list * search(int key);
	dl_list * insert(int key);//в начало
	bool del(dl_list * d);
	bool del(int x);
	void add(int x);//в конец
};

dl_list::dl_list() {
	next = prev = nullptr;
	first = false;
}
dl_list::dl_list(int x) {
	next = prev = nullptr;
	first = true;
	data = x;
}

void dl_list::show() {//будем сначала подыматься наверх, а затем печатать весь список
	dl_list * temp = this;
	while (temp->prev != nullptr) {
		temp = temp->prev;
	}
	while (temp->next != nullptr) {
		cout << temp->data << ' ';
		temp = temp->next;
	}
	cout << endl;
}

dl_list * dl_list::search(int key) {//будем сначала подыматься наверх, а затем искать во всём списке
	dl_list * temp = this;
	while (temp->prev != nullptr) {
		temp = temp->prev;
	}
	while ((temp->next != nullptr) && (temp->data != key)) {
		temp = temp->next;
	}
	if (temp->data == key) {
		return temp;
	}
	else {
		return nullptr;
	}
}

dl_list * dl_list::insert(int key) {//в начало
	dl_list * temp = this;
	while (temp->prev != nullptr) {
		temp = temp->prev;
		cout << temp->data << " in insert ";
	}
	cout << endl;
	if (temp->first == true) {//здесь, в 1-м элементе списка, уже записывали 
		dl_list * temp2 = new dl_list;
		temp2->data = key;
		temp2->prev = nullptr;
		temp2->next = temp;
		temp->prev = temp2;
		return temp2;
	}
	else {//не записывали
		temp->data = key;   
		temp->first = true;
		return temp;
	}

}
bool dl_list::del(dl_list * d) {
	dl_list * temp = this;
	while (temp->prev != nullptr) {
		temp = temp->prev;
	}
	while ((temp->next != nullptr) && (temp != d)) {
		temp = temp->next;
	}
	if (temp == d) {
		//if (temp != this) {//удаляемый элемент не сам элемент
			if ((temp->prev != nullptr) && (temp->next != nullptr)) {
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
			}
			else if (temp->prev != nullptr) {//есть предыдущий, нет следующего
				temp->prev->next = nullptr;
			}
			else if (temp->next != nullptr) {//есть следующий, нет предыдущего
				temp->next->prev = nullptr;
			}
			delete temp;
			return true;
		//}
		//else {//удаляемый элемент есть this
			
		//}
	}
	else {//не нашли
		return false;
	}
}
//bool dl_list::del(int x);
//void dl_list::add(int x);//в конец

struct node {
	int data, count;
	node *prev, *left, *right;
	friend std::ostream& operator<<(std::ostream &out, const node *n) {
		out << n->data; 
		return out;
	}
	node() {
		count = 0;
		prev = left = right = nullptr;
	}
	node(int d, int c) {
		count = 1;
		data = d;
		prev = left = right = nullptr;
	}
};

class BinTree {
private: node* root;
public:
	BinTree() {
		root = new node;
		root->data = 0;
		root->count = 0;
		root->prev = root->left = root->right = nullptr;
	}
	BinTree(int data) {
		root = new node;
		root->data = data;
		root->count = 1;
		root->prev = root->left = root->right = nullptr;
	}
	void Inorder_tree_walk(node * x) {
		if (x != nullptr) {
			Inorder_tree_walk(x->left);
			for (int i = 0; i < x->count; i++) {
				cout << x << ' ';
			}
			Inorder_tree_walk(x->right);
		}
	}
	node * Tree_search(node *x, int key) {
		if ((x == nullptr) || (x->data == key)) {
			return x;
		}
		if (key < x->data) {
			return Tree_search(x->left, key);
		}
		else {
			return Tree_search(x->right, key);
		}
	}
	node * Iterative_tree_search(node *x, int key) {
		while ((x != nullptr) && (x->data != key)) {
			if (key < x->data) {
				x = x->left;
			}
			else {
				x = x->right;
			}
		}
		return x;
	}
	node * min(node *x) {
		while (x->left != nullptr) {
			x = x->left;
		}
		return x;
	}
	node * max(node *x) {
		while (x->right != nullptr) {
			x = x->right;
		}
		return x;
	}
	node * Tree_succ(node * x) {
		if (x->right != nullptr) {
			return min(x->right);
		}
		node * y = x->prev;
		while ((y != nullptr) || (x = y->right))  {
			x = y;
			y = y->prev;
		}
		return x;
	}
	node * Tree_prev(node * x) {
		if (x->left != nullptr) {
			return max(x->left);
		}
		node * y = x->prev;
		while ((y != nullptr) || (x = y->left)) {
			x = y;
			y = y->prev;
		}
		return x;
	}
	void insert(node * x, int key) {//дописать версию для count
		node * n = new node(key, 1);
		node * y = nullptr;
		while (x != nullptr) {
			y = x; 
			if (key < x->data) {
				x = x->left;
			}
			else if (key > x->data) {
				x = x->right;
			}
			else {
				x->count++;
				delete n;
				return;
			}
		}
		if (y == nullptr) {
			root = n; 
			return;
		}
		n->prev = y;
		if (y->data > key) {
			y->left = n;
		}
		else if (y->data < key) {
			y->right = n;
		}
	}
	void delCount(node *z) {
		if (z->count > 1) {
			z->count--;
		}
		else {
			if ((z->left == nullptr) && (z->right == nullptr)) {
				if (z->prev->left == z) {
					z->prev->left = nullptr;
					delete z;
				}
				else {
					z->prev->right = nullptr;
					delete z;
				}
			}
			else if ((z->right != nullptr) && (z->left == nullptr)) {
				if (z->prev->left == z) {
					z->prev->left = z->right;
					z->right->prev = z->prev;
					delete z;
				}
				else {
					z->prev->right = z->right;
					z->right->prev = z->prev;
					delete z;
				}
			}
			else if ((z->right == nullptr) && (z->left != nullptr)) {
				if (z->prev->left == z) {
					z->prev->left = z->left;
					z->left->prev = z->prev;
					delete z;
				}
				else {
					z->prev->right = z->left;
					z->left->prev = z->prev;
					delete z;
				}
			}
			else {
				node * y = Tree_succ(z);
				z->data = y->data;
				z->count = y->count;
				del(y);
			}
		}
	}
	void del(node *z) {
		if ((z->left == nullptr) && (z->right == nullptr)) {
			if (z->prev->left == z) {
				z->prev->left = nullptr;
				delete z;
			}
			else {
				z->prev->right = nullptr;
				delete z;
			}
		}
		else if ((z->right != nullptr) && (z->left == nullptr)) {
			if (z->prev->left == z) {
				z->prev->left = z->right;
				z->right->prev = z->prev;
				delete z;
			}
			else {
				z->prev->right = z->right;
				z->right->prev = z->prev;
				delete z;
			}
		}
		else if ((z->right == nullptr) && (z->left != nullptr)) {
			if (z->prev->left == z) {
				z->prev->left = z->left;
				z->left->prev = z->prev;
				delete z;
			}
			else {
				z->prev->right = z->left;
				z->left->prev = z->prev;
				delete z;
			}
		}
		else {
			node * y = Tree_succ(z);
			z->data = y->data;
			z->count = y->count;
			del(y);
		}
	}
	node * getRoot() {
		return root;
	}
};

class RBTree {
	struct node_color {
		int data;
		char color;
		int count;
		node_color *prev, *left, *right;
		friend std::ostream& operator<<(std::ostream &out, const node_color *n) {
			out << n->data << ' ' << n->color;
			return out;
		}
		node_color() {
			color = 'b';
			prev = left = right = nullptr;
			count = 0;
		}
		node_color(int d, char c) {
			color = c;
			data = d;
			prev = left = right = nullptr;
			count = 1;
		}
		node_color(int d, char c, int cnt) {
			color = c;
			data = d;
			count = cnt;
		}
		void set_color(char c) {
			color = c;
		}
		char get_color() {
			return color;
		}
	};
	node_color *root;
public:
	RBTree() {
		//nullptr = new node_color{ 0,'b', 0};
		root = nullptr;
	}
	void Inorder_tree_walk(node_color * x) {
		if (x != nullptr) {
			Inorder_tree_walk(x->left);
			for (int i = 0; i < x->count; i++) {
				cout << x << ' ';
			}
			Inorder_tree_walk(x->right);
		}
	}
	void LeftRotate(RBTree *T, node_color *x) {
		if (x->right != nullptr) {
			node_color *y = x->right;
			//node_color *y = x->left;
			if (x == root) {
				root = y;
			}
			else {
				if (x->prev->left == x) {
					x->prev->left = y;
				}
				else {
					x->prev->right = y;
				}
			}
			y->prev = x->prev;
			x->right = y->left;
			if (y->left != nullptr) y->left->prev = x;//4
			x->prev = y;
			y->left = x;
		}
	}
	void RightRotate(RBTree *T, node_color *y) {//у == 3
		if (y->left != nullptr) {
			node_color *x = y->left;//х это 2
			if (y == root) {
				root = x;
			}
			else {
				if (y->prev->right == y) {
					y->prev->right = x;
				}
				else {
					y->prev->left = x;//у 4 двойка левый потомок теперь
				}
			}
			x->prev = y->prev;//предок 2 есть 4
			y->left = x->right;//у 3 теперь левый потомок это нуллптр
			if (x->right != nullptr) x->right->prev = y;//3, сюда не заходим
			y->prev = x;//у тройки предок теперь двойка !
			x->right = y;//двойка указывает на тройку
		}
	}
	node_color * insert(RBTree *T, int key) {
		node_color * n = new node_color(key, 'r');
		node_color * y = nullptr;
		node_color * x = root;
		while (x != nullptr) {
			y = x;
			if (key < x->data) {
				x = x->left;
			}
			else if (key > x->data) {
				x = x->right;
			}
			else {
				x->count++;
				delete n;
				return x;
			}
		}
		if (y == nullptr) {
			root = n;
			return n;
		}
		n->prev = y;
		if (y->data > key) {
			y->left = n;
		}
		else if (y->data < key) {
			y->right = n;
		}
		return n;
	}
	void RBInsert(RBTree *T, int key) {
		node_color *z = insert(T, key);
		if (z->prev == nullptr) {
			z->color = 'b';
			return;
		}
		else {
			while((z != root) && (z->prev->color == 'r')) {//reded-red violation
				if (z->prev->prev != nullptr) {//G exists
					node_color *F = z->prev;
					node_color *G = z->prev->prev;
					node_color *U;
					if (F == G->left) {
						U = G->right;
					}
					else {
						U = G->left;
					}//2
					if ((U == nullptr) || (U->color == 'b')) {
						if ((z == F->left) && (F == G->left)) {//z-F-G - левые потомки, прямая линия
							F->color = 'b'; G->color = 'r';
							int j = 1;
							RightRotate(this, G);//5
							int i = 1;
						}
						else if ((z == F->right) && (F == G->right)) {//z-F-G - правые потомки, прямая линия
							F->color = 'b'; G->color = 'r';
							LeftRotate(this, G);//5
							
						}
						else if ((z == F->right) && (F == G->left)) {
							z->color = 'b'; G->color = 'r';//8
							LeftRotate(this, F);//7
							RightRotate(this, G);//6
						}
						else if ((z == F->left) && (F == G->right)) {
							z->color = 'b'; G->color = 'r';//8
							RightRotate(this, F);//7
							LeftRotate(this, G);//6
						}
						z = F;//?
					}//?Может возникнуть красно-красное нарушение между G и G->prev
					 //Если G - корень, то он должен быть чёрным, а после алгоритма сверху он красный
					else if (U->color == 'r') {//if U is red we just repaint G,F,U
						G->color = 'r';
						F->color = 'b';
						U->color = 'b';
						z = G;//?
					}
				}
				//1
				if (root->color == 'r') {
					cout << "repainting root " << root->data << endl;
					root->color = 'b';
				}
			}
			
		}

	}
	node_color * getRoot() {
		return root;
	}
	node_color * Tree_search(node_color * x, int key) {
		if ((x == nullptr) || (x->data == key)) {
			return root;
		}
		if (key < x->data) {
			return Tree_search(x->left, key);
		}
		else {
			return Tree_search(x->right, key);
		}
	}
	node_color * min(node_color *x) {
		while (x->left != nullptr) {
			x = x->left;
		}
		return x;
	}
	node_color * Tree_succ(node_color * x) {
		if (x->right != nullptr) {
			return min(x->right);
		}
		node_color * y = x->prev;
		while ((y != nullptr) || (x = y->right)) {
			x = y;
			y = y->prev;
		}
		return x;
	}

	void RBDelete(RBTree *T, int key) {
		node_color * z = Tree_search(T->getRoot(), key);
		if (z->count > 1) {
			z->count--;
			return;
		}
		else {
			if ((z->left != nullptr) && (z->right != nullptr)) {
				node_color * x = Tree_succ(z);
				z->data = x->data;
				z->count = x->count;
				z = x;
			}
			//у z максимум один потомок
			node_color *N = nullptr;
			node_color *B = nullptr;
			z->left != nullptr ? N = z->left : N = z->right;
			z->prev->right != z ? B = z->prev->right : B = z->prev->left;
			node_color *CL = B->left; node_color *CR = B->right;
			node_color *F = z->prev;
			if (z->color == 'r') {//ничего делать не нужно
				z->prev->left == z ? z->prev->left = N : z->prev->right = N;
				N->prev = z->prev;
				delete z;
			}
			else if ((F->color == 'r') && (B->color == 'b') && (N->color == 'b') && (((CL != nullptr) && (CL->color == 'b')) || (CL == nullptr)) && (((CR != nullptr) && (CR->color == 'b')) || (CR == nullptr))){
				F->color = 'b'; B->color = 'r';
			}
		}
		
	}
};

int main()
{
	/*BinTree b;
	b.insert(b.getRoot(), 10);
	b.insert(b.getRoot(), 11);
	b.insert(b.getRoot(), 12);
	b.Inorder_tree_walk(b.getRoot());
	b.del(b.Tree_search(b.getRoot(), 10));
	cout << endl;
	b.Inorder_tree_walk(b.getRoot());
	b.del(b.Tree_search(b.getRoot(), 11));
	cout << endl;
	b.Inorder_tree_walk(b.getRoot());
	b.del(b.Tree_search(b.getRoot(), 12));
	cout << endl;
	b.Inorder_tree_walk(b.getRoot());
	cout << endl;
	int n[10];
	int ord[10];
	srand(time(0));
	for (int i = 0; i < 10; i++) {
		n[i] = rand() % 1000;
		b.insert(b.getRoot(), n[i]);
		cout << n[i] << ' ';
	}
	cout << endl;*/
	RBTree T;
	T.RBInsert(&T, 5);
	//cout << "1" << endl;
	T.Inorder_tree_walk(T.getRoot());
	cout << endl;
	T.RBInsert(&T, 15);
	//cout << "1" << endl;
	T.Inorder_tree_walk(T.getRoot());
	cout << endl;
	T.RBInsert(&T, 7);
	//cout << "1" << endl;
	T.Inorder_tree_walk(T.getRoot());
	cout << endl;
	T.RBInsert(&T, 3);
	//cout << "1" << endl;
	T.Inorder_tree_walk(T.getRoot());
	cout << endl;
	T.RBInsert(&T, 4);
	//cout << "1" << endl;
	T.Inorder_tree_walk(T.getRoot());
	cout << endl;
	T.RBInsert(&T, 10);
	//cout << "1" << endl;
	T.Inorder_tree_walk(T.getRoot());
	cout << endl;
	T.RBInsert(&T, 1);
	//cout << "1" << endl;
	
	T.Inorder_tree_walk(T.getRoot());
	cout << endl;
	system("pause");
    return 0;
}

