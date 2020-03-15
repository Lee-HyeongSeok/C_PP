#include <list>
#include <algorithm>

using namespace std;

int main() {
	list<int> coll;

	for (int i = 1; i <= 6; i++) {
		coll.push_front(i);
		coll.push_back(i);
	}

	coll.erase(remove(coll.begin(), coll.end(), 3), coll.end());

	coll.remove(4);
}