## * 연결 리스트를 이용한 희소 행렬의 표현   
#### * 출처 : c++자료구조론   
#### * 목적 : 행렬에 0이 아닌 항만을 표현할 때 연산 시간 및 공간을 절약하기 위함   


#### * MatrixNode class 설명 
		* 희소 행렬 표현은 MatrixNode 타입의 노드를 사용한다.
		* MatrixNode class는 0이 아닌 요소를 표현하는 노드를 구별하기 위한 head라는 Boolean 필드를 가진다.
		* 각 헤더 노드는 추가로 세 개의 필드 down, right, next를 가지고 있다.
		* 헤더가 아닌 노드들은 head, row, col, value, down, right를 갖는다.
		* down 필드 : 같은 열에 있는 0이 아닌 다음 항을 연결하는 데 사용
		* right 필드 : 같은 행에 있는 0이 아닌 다음 항을 연결한다.
		* row 필드, col 필드 : 행렬의 차수를 저장하는 데 사용된다.
```c
/*
	* 희소행렬의 연결을 표현(노드의 head 필드는 표시되지 않았다.)

	     |H|	     ->	    |H0|		->	|H1|	-> ....
	| 4 | 5 | 6 |		| 0 | 0 | 2 |	        | 1 | 0 | 4 |

*/
```   

#### * Matrix class 설명
		* 전체 행렬은 H를 가리키는 headnode 데이터 멤버를 가진 Matrix 클래스로 표현된다.
		* 헤더 노드들의 총 수는 max(행의 수, 열의 수)이다.   

#### * union 선언(이름이 없다.)
		* 필요한 노드 구조를 Union을 통해 정의함
		* 모든 노드들은 head, down, right 필드를 가지고 있기 때문에 이것들은 union 밖에 선언된다.
		* 헤더 노드는 next를 포함하는 반면에 다른 노드들은 row, col, value를 포함하고 있다.
		* 이 필드들은 struct Triple에 포함되며, 공간은 next와 triple 필드 중 큰 것으로 union선언에 의해 할당된다.
```c
union {
	MatrixNode *next;
	Triple triple;
};
```
