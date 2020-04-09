## * 연결리스트 : 템플릿을 이용한 체인 구현 
#### * 출처 : c++자료구조론   
#### * 목적 : 컨테이너 클랫를 더 재사용할 수 있게 만들기 위함   

#### * 체인 반복자 ChainIterator class   
		* ChainIterator가 Chain의 공용 중첩 멤버 클래스가 된다.
		* Chain<T>::ChainIterator 형식으로 사용 가능하다.
		* current : 순회를 위한 포인터이다.
		* 첫 번째 노드와 마지막 노드를 하나 지난 위치로 초기화된 반복자를 반환한다.
```c
template <typename T>

class ChainIterator {
	private:
		ChainNode<T> *current; // 순회를 위한 포인터 

	public:
		ChainIterator(ChainNode<T> *startNode = 0) {
			current = startNode;
		}
		T& operator*() const {
			return current->data;
		}
		T* operator->() const {
			return &current->data;
		}
		T getData() {
			return current->data;
		}
		ChainIterator& operator++() {
			current = current->link;
			return *this;
		}
		ChainIterator operator++(int) {
			ChainIterator old = *this;
			current = current->link;
			return old;
		}
		bool operator!=(const ChainIterator right) const {
			return current != right.current;
		}
		bool operator==(const ChainIterator right) const {
			return current == right.current;
		}
		template <typename T>
		friend ostream &operator<<(ostream &os, Chain<T> &c);

	};
```   

#### * ChainNode class
		* Node를 나타내는 클래스   
		* ChainNode의 멤버들에 Chain의 멤버들은 접근할 수 있다.(friend 선언)
		* 데이터 타입에 따라서 접근 방식이 달라진다.(template)   

```c
template <typename T>
class ChainNode {
private:
	T data;	// 데이터
	ChainNode<T> *link; // 링크 
public:	
	// Chain의 멤버들이 ChainNode의 멤버들에 접근 가능
	friend class Chain<T>;
	// 생성자 선언, 디폴트 값 허용 
	ChainNode(T element = 0, ChainNode *next = NULL)
		:data(element), link(next) {

	}
	T getData() {	// 노드의 데이터를 받아오는 메서드 
		return data;
	}
	ChainNode *Link() {	// 현재 링크를 반환하는 메서드 
		return link;
	}
};
```   

#### * Chain class   
		* 노드의 헤드를 반환받는 기능
		* 노드를 삽입, 삭제하는 기능
		* 노드의 뒤에 삽입하는 기능
		* 두 리스트를 연결시키는 기능
		* 리스트의 원소 순서를 역순으로 재배치하는 기능

```c
template <typename T>
class Chain {
private:
	ChainNode<T> *first; // 노드의 헤드
	ChainNode<T> *last;	// 노드의 꼬리 
public :
	Chain() {
		first = 0;
	}
	// 노드의 헤드를 반환받는 메서드
	ChainNode<T> *getFirst() {
		return first;
	}
	// 노드를 삽입하는 메서드 
	ChainNode<T> *insert(ChainNode<T> *in, T i) {
		if (first) {
			ChainNode<T> *temp = new ChainNode<T>(i, in->link);
			in->link = temp;	// in이 temp를 가르킨다.
			return in->link;	// 위치 반환 
		}
		else {
			first = new ChainNode<T>(i);
			return first;
		}
	}
	// 노드의 꼬리에 삽입하는 메서드 
	void insertBack(const T& e) {
		if (first) {	// 공백이 아닌 체인 
			last->link = new ChainNode<T>(e);
			last = last->link;
		}
		else {	// 공백일 때 
			first = last = new ChainNode<T>(e);
		}
	}
	// 노드를 삭제하는 메서드 
	void Delete(ChainNode<T> *De) {
		if (first == NULL) {
			cout << "Empty" << endl;
			return;
		}
		else {
			// remover 객체를 생성과 동시에 first로 초기화 
			ChainNode<T> *remover = first;

			// 삭제할 요소가 아닐경우 다음노드로 이동 
			while (remover->link != De) {
				remover = remover->link;
			}
			// 삭제할 노드가 가리키는 다음 노드를 remover에 복사 
			remover->link = De->link;
		}
		// 노드삭제
		delete De;
	}
	// 두 체인을 접합시킨다.
	void Concatenate(Chain<T>& b) {
		if (first) {
			last->link = b.first;
			last = b.last;
		}
		else {
			first = b.first;
			last = b.last;
		}
		b.first = b.last = 0;
	}
	// 체인에 있는 원소의 순서를 역순으로 변환한다.
	void Reverse() {
		ChainNode<T> *current = first, *previous = 0;

		while (current) {
			ChainNode<T> *r = previous;
			previous = current;	// r은 previous를 따라간다.
			current = current->link;	// current는 다음 노드로 이동
			previous->link = r;	// previous를 이전 노드와 연결한다.
		}
		first = previous;
	}
	/*
		이 부분에 ChainIterator class가 공용 중첩 멤버 클래스로 삽입된다.
	*/
	ChainIterator begin() {
		return ChainIterator(first);
	}
	ChainIterator end() {
		return ChainIterator(0);
	}
	// cout을 통한 객체 출력을 위해 선언한 함수 오버로딩
	template <typename T>
	friend ostream &operator<<(ostream &os, Chain<T> &c);
};
```