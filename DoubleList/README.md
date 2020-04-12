## * 이중 연결 리스트(Doubly linked list)
#### * 출처 : c++자료구조론   
#### * 목적 : 포인트를 양 방향으로 이동해야할 때 사용하기 위한 이중 연결 리스트   

#### * 구조   
		* left, right 링크를 갖는다.
		* 각 노드는 data 필드도 갖는다.
		* p가 이중 연결 리스트의 임의의 노드를 가리킨다고 가정할 때 
				* p == p->left->right == p->right->left가 된다.
	
### right, left를 가진 class
```c
class DbListNode {
	friend class DbList;		// 실질적으로 리스트 조작 연산들을 가진 클래스 
private:
	int data;		// 각 노드별로 가지고있는 데이터 멤버
	DbListNode *left, *right;	// 노드의 왼쪽, 오른쪽 링크 
public:
	// 생성자, 모든 인자를 default 선언
	DbListNode(int element = 0, DbListNode *lNode = NULL, DbListNode *rNode = NULL)
		: data(element), left(lNode), right(rNode) {

	}
	// 노드의 출력을 위한 함수 재정의 
	friend ostream &operator<<(ostream& os, DbList &d);
};
```   

### 실질적 리스트 조작 연산을 가진 클래스
```c
class DbList {
private:
	DbListNode *first;
public:
	DbList() {	// 생성자 정의
		first = new DbListNode;
		first->left = first;
		first->right = first;
	}
	void insert(DbListNode *insert_node, DbListNode *position_node = NULL) {
		if (position_node == NULL) {	// 1개의 인자로 전달된 노드를 삽입할 때
			insert_node->left = first->left;
			insert_node->right = first;
			first->left->right = insert_node;
			first->left = insert_node;
		}
		else {	// 두 개의 인자로 전달된 노드를 연결할 때
			insert_node->left = position_node;
			insert_node->right = position_node->right;
			position_node->right->left = insert_node;
			position_node->right = insert_node;
		}
	}
	void Delete(DbListNode *remover) {
		// this 객체가 first일 때
		if (remover == first)
			throw "Deletion of header node not permitted";
		else {	
			// 노드를 한 칸 옮기는 동작
			// 삭제할 노드가 가리키는 오른쪽 노드를 저장한다.
			remover->left->right = remover->right;
			remover->right->left = remover->left;
			delete remover;
		}
	}
	~DbList() {	// 소멸자 정의
		DbListNode *remover = first;
		DbListNode *remover_next = first->right;

		while (1) {
			if (remover_next->data >= 0) {
				delete remover;
				remover = remover_next;
				remover_next = remover_next->right;
			}
			else {
				delete remover;
				break;
			}
		}
	}
	friend ostream &operator<<(ostream &os, DbList &d);
};
```   

### 노드를 출력하기 위한 함수 재정의   
```c
ostream &operator<<(ostream &os, DbList &d) {
	os << "right directioin" << endl;
	DbListNode *temp1 = d.first;		// 오른쪽 방향 탐색을 위한 선언
	DbListNode *temp2 = d.first;		// 왼쪽 방향 탐색을 위한 선언
	
	// 오른쪽 탐색
	while (temp1->right->data != 0) {
		os << temp1->right->data;
		if (temp1->right->right->data != 0)
			os << "->";
		else
			os << " ";
		temp1 = temp1->right;
	}

	os << endl << "left direction" << endl;
	
	// 왼쪽 탐색
	while (temp2->left->data != 0) {
		os << temp2->left->data;
		if (temp2->left->left->data != 0)
			os << "->";
		else
			os << " ";
		temp2 = temp2->left;
	}
	return os;
}
```