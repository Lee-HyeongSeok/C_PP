#include <iostream>
using namespace std;

template <class T> class GenList;

// dummy, data, list
enum GenListNodeType {Head, Data, List};

template <class T>
class GenListNode {
public:
	GenListNodeType type;
	T data;
	GenList<T> *list;
	GenListNode<T> *next;
	GenListNode<T>() {
		type = Head;
		data = 0;
		list = NULL;
		next = NULL;
	}
	~GenListNode<T>() {
		if (list)
			delete list;
	}
};

template <class T>
class GenList {
private:
	GenListNode<T> *first;
public:
	GenList() {
		first = new GenListNode<T>;// 더미노드 삽입
		first->next = NULL;
	}
	void insert(const T& item) {
		GenListNode<T> *temp = new GenListNode<T>;
		temp->data = item;
		temp->type = Data;
		temp->next = first->next;
		// 더미노드를 다음에 삽입한다.
		first->next = temp;
	}
	// 리스트를 추가
	void insert(const GenList<T> &l) {
		GenList<T> *temp = new GenList<T>(l);
		GenListNode<T> *item = new GenListNode<T>;
		item->type = List;
		item->list = temp;
		item->next = first->next;
		first->next = item;
	}
	int Depth() const {
		int depth = 0;
		GenListNode<T> *p = first->next;
		while (p) {
			if (p->type == List) {
				// 리스트가 두개 이상인 경우
				int p_depth = p->list->Depth();
				if (p_depth > depth)
					depth = p_depth;
			}
			p = p->next;
		}
		return ++depth;
	}
	void Print() const {
		GenListNode<T> *p = first->next;
		while (p) {
			if (p->type == Data) {
				cout << p->data;
				if (p->next)
					cout << "->";
			}
			// 리스트가 둘 이상일 경우 재귀식으로 출력한다.
			if (p->type == List) {
				p->list->Print();
				if (p->next)
					cout << "->";
			}
			p = p->next;
		}
	}
	~GenList() {
		GenListNode<T> *p;
		// 데이터가 유효할 때
		while (first->data > 0) {
			p = first;
			first = first->next;
			delete p;
		}
	}
};

int main() {
	// 리스트에 값 삽입
	GenList<int> GL1;
	for (int i = 0; i < 5; i++) {
		GL1.insert(i + 1);
	}
	GL1.Print();
	cout << endl;

	// 리스트에 값 삽입
	GenList<int> GL2;
	for (int i = 5; i < 10; i++) {
		GL2.insert(i);
	}
	// 리스트에 리트스 삽입
	GL2.insert(GL1);
	GL2.Print();
	cout << endl;

	GenList<int> GL3;
	for (int i = 9; i < 16; i++) {
		GL3.insert(i);
	}
	GL3.insert(GL2);
	GL3.Print();
	cout << endl;

	cout << "Depth : " << GL3.Depth() << endl;
	return 0;
}