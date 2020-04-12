#include <iostream>

using namespace std;

class DbList;

class DbListNode {
	friend class DbList;
private:
	int data;
	DbListNode *left, *right;
public:
	DbListNode(int element = 0, DbListNode *lNode = NULL, DbListNode *rNode = NULL)
		: data(element), left(lNode), right(rNode) {

	}
	friend ostream &operator<<(ostream& os, DbList &d);
};

class DbList {
private:
	DbListNode *first;
public:
	DbList() {
		first = new DbListNode;
		first->left = first;
		first->right = first;
	}
	void insert(DbListNode *insert_node, DbListNode *position_node = NULL) {
		if (position_node == NULL) {
			insert_node->left = first->left;
			insert_node->right = first;
			first->left->right = insert_node;
			first->left = insert_node;
		}
		else {
			insert_node->left = position_node;
			insert_node->right = position_node->right;
			position_node->right->left = insert_node;
			position_node->right = insert_node;
		}
	}
	void Delete(DbListNode *remover) {
		if (remover == first)
			throw "Deletion of header node not permitted";
		else {
			remover->left->right = remover->right;
			remover->right->left = remover->left;
			delete remover;
		}
	}
	~DbList() {
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

ostream &operator<<(ostream &os, DbList &d) {
	os << "right directioin" << endl;
	DbListNode *temp1 = d.first;
	DbListNode *temp2 = d.first;

	while (temp1->right->data != 0) {
		os << temp1->right->data;
		if (temp1->right->right->data != 0)
			os << "->";
		else
			os << " ";
		temp1 = temp1->right;
	}

	os << endl << "left direction" << endl;

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

int main() {
	DbList d;
	DbListNode *temp1 = new DbListNode(1);
	DbListNode *temp2 = new DbListNode(2);
	DbListNode *temp3 = new DbListNode(3);
	DbListNode *temp4 = new DbListNode(4);

	d.insert(temp1);
	d.insert(temp2);
	d.insert(temp3);
	d.insert(temp4, temp3);

	cout << d << endl;
	
}