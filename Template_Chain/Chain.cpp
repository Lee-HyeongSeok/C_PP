#include <iostream>

using namespace std;

template <typename T> class Chain;
template <typename T> class ChainIterator;
template <typename T>

// 하나의 노드를 나타내는 클래스 
class ChainNode {
private:
	T data;
	ChainNode<T> *link;
public:
	friend class Chain<T>;
	
	ChainNode(T element = 0, ChainNode *next = NULL)
		:data(element), link(next) {

	}
	T getData() {
		return data;
	}
	ChainNode *Link() {
		return link;
	}
};

template <typename T>
class Chain {
private:
	ChainNode<T> *first; // 노드의 헤드
	ChainNode<T> *last;	// 노드의 꼬리 
public :
	Chain() {
		first = 0;
	}
	ChainNode<T> *getFirst() {
		return first;
	}
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
	void insertBack(const T& e) {
		if (first) {	// 공백이 아닌 체인 
			last->link = new ChainNode<T>(e);
			last = last->link;
		}
		else {	// 공백일 때 
			first = last = new ChainNode<T>(e);
		}
	}
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
	class ChainIterator {
	private:
		ChainNode<T> *current;

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
	ChainIterator begin() {
		return ChainIterator(first);
	}
	ChainIterator end() {
		return ChainIterator(0);
	}
	template <typename T>
	friend ostream &operator<<(ostream &os, Chain<T> &c);
};

template<typename T>
ostream &operator<<(ostream &os, Chain<T> &c) {
	/* Chain<T>::ChainIterator가 멤버이름인지 형식이름인지 
		알 수 없기 때문에 typename을 붙여서 형식 이름임을 알려줘야 한다.
	*/
	typename Chain<T>::ChainIterator iter = c.begin();
	
	while (iter != c.end()) {
		os << iter.getData() << "-> ";
		iter++;

	}
	os << endl;
	return os;
}

int main() {
	Chain<int> Ch;
	ChainNode<int> *CN = Ch.getFirst();	// head

	// 리스트에 값 입력 
	for (int i = 0; i < 10; i++) {
		CN = Ch.insert(CN, i + 1);
	}
	cout << "output" << endl;
	cout << Ch << endl;

	cout << "reversed element" << endl;
	Ch.Reverse();
	cout << Ch << endl;

	return 0;
}