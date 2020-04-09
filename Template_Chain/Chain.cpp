#include <iostream>

using namespace std;

template <typename T> class Chain;
template <typename T> class ChainIterator;
template <typename T>

// �ϳ��� ��带 ��Ÿ���� Ŭ���� 
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
	ChainNode<T> *first; // ����� ���
	ChainNode<T> *last;	// ����� ���� 
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
			in->link = temp;	// in�� temp�� ����Ų��.
			return in->link;	// ��ġ ��ȯ 
		}
		else {
			first = new ChainNode<T>(i);
			return first;
		}
	}
	void insertBack(const T& e) {
		if (first) {	// ������ �ƴ� ü�� 
			last->link = new ChainNode<T>(e);
			last = last->link;
		}
		else {	// ������ �� 
			first = last = new ChainNode<T>(e);
		}
	}
	void Delete(ChainNode<T> *De) {
		if (first == NULL) {
			cout << "Empty" << endl;
			return;
		}
		else {
			// remover ��ü�� ������ ���ÿ� first�� �ʱ�ȭ 
			ChainNode<T> *remover = first;

			// ������ ��Ұ� �ƴҰ�� �������� �̵� 
			while (remover->link != De) {
				remover = remover->link;
			}
			// ������ ��尡 ����Ű�� ���� ��带 remover�� ���� 
			remover->link = De->link;
		}
		// ������
		delete De;
	}
	// �� ü���� ���ս�Ų��.
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
	// ü�ο� �ִ� ������ ������ �������� ��ȯ�Ѵ�.
	void Reverse() {
		ChainNode<T> *current = first, *previous = 0;

		while (current) {
			ChainNode<T> *r = previous;
			previous = current;	// r�� previous�� ���󰣴�.
			current = current->link;	// current�� ���� ���� �̵�
			previous->link = r;	// previous�� ���� ���� �����Ѵ�.
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
	/* Chain<T>::ChainIterator�� ����̸����� �����̸����� 
		�� �� ���� ������ typename�� �ٿ��� ���� �̸����� �˷���� �Ѵ�.
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

	// ����Ʈ�� �� �Է� 
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