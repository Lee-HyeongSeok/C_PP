## * Generalized List
#### * 출처 : c++ 자료구조론 & https://jaimemin.tistory.com/170?category=962731   

#### * 삽입 함수
		* void Insert(const T &item)
				* template형 값을 인자로 받는다.
		* void Insert(const GenList<T> &l)
				* template형 리스트를 인자로 받는다.

```c
// 값을 인자로 받는 함수
void insert(const T& item) {
	GenListNode<T> *temp = new GenListNode<T>;
	temp->data = item;
	temp->type = Data;
	temp->next = first->next;
	// 더미노드를 다음에 삽입한다.
	first->next = temp;
}
```

```c
// 리스트를 인자로 받는 함수
// 리스트를 추가
void insert(const GenList<T> &l) {
	GenList<T> *temp = new GenList<T>(l);
	GenListNode<T> *item = new GenListNode<T>;
	item->type = List;
	item->list = temp;
	item->next = first->next;
	first->next = item;
}
```

#### * 리스트 출력 함수
```c
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
```