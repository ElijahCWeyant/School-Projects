//I don't know if this works I pretty much copied and pasted his code so.......yeah
#include <iostream>
#include <string>
#include <queue>
#include <stack>

using namespace std;

const int XMAX = 25;
const int YMAX = 25;
int goal = 3 * (XMAX+1) + 22;
int entrance = 1 * (YMAX +1) + 15;

char map[XMAX][YMAX] = {
// 0    1    2    3    4    5    6    7    8    9   10    11   12   13   14   15   16  17    18   19  20    21  22    23   24  
{ 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },//0
{ 'W', ' ', ' ', ' ', 'W', 'W', 'W', 'W', 'W', ' ', ' ', ' ', 'W', 'W', 'W', 'E', 'W', 'W', 'W', 'W', 'W', ' ', 'W', 'W', 'W' },//1
{ 'W', 'W', 'W', ' ', ' ', ' ', ' ', ' ', 'W', ' ', 'W', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W', 'W', 'W', ' ', 'W', 'W', 'W' },//2
{ 'W', 'W', 'W', ' ', 'W', 'W', 'W', ' ', 'W', ' ', 'W', 'W', 'W', 'W', 'W', 'W', 'W', ' ', 'W', 'W', 'W', ' ', 'W', 'W', 'W' },//3
{ 'W', ' ', ' ', ' ', 'W', 'W', ' ', ' ', 'W', ' ', 'W', 'W', 'W', 'W', 'W', 'W', 'W', ' ', 'W', 'W', 'W', ' ', 'W', 'W', 'W' },//4
{ 'W', ' ', 'W', ' ', 'W', 'W', ' ', 'W', 'W', ' ', 'W', 'W', 'W', 'W', 'W', 'W', 'W', ' ', 'W', 'W', 'W', ' ', 'W', 'W', 'W' },//5
{ 'W', ' ', ' ', ' ', 'W', 'W', ' ', 'W', 'W', ' ', 'W', 'W', 'W', 'W', 'W', 'W', 'W', ' ', 'W', 'W', 'W', ' ', ' ', ' ', 'W' },//6
{ 'W', 'W', 'W', ' ', 'W', 'W', ' ', ' ', ' ', ' ', 'W', 'W', 'W', ' ', ' ', ' ', ' ', ' ', 'W', 'W', 'W', ' ', 'W', ' ', 'W' },//7
{ 'W', 'W', 'W', ' ', 'W', 'W', 'W', 'W', 'W', ' ', 'W', 'W', 'W', 'W', 'W', 'W', 'W', ' ', 'W', 'W', 'W', ' ', 'W', ' ', 'W' },//8
{ 'W', ' ', ' ', ' ', 'W', 'W', 'W', 'W', 'W', ' ', 'W', 'W', 'W', 'W', 'W', 'W', 'W', ' ', 'W', 'W', 'W', ' ', 'W', ' ', 'W' },//9
{ 'W', 'W', 'W', ' ', 'W', 'W', 'W', 'W', 'W', ' ', 'W', 'W', 'W', 'W', 'W', 'W', 'W', ' ', 'W', 'W', 'W', ' ', 'W', ' ', 'W' },//10
{ 'W', 'W', 'W', ' ', 'W', 'W', 'W', 'W', 'W', ' ', 'W', 'W', 'W', 'W', ' ', 'W', 'W', ' ', ' ', ' ', ' ', ' ', 'W', ' ', 'W' },//11
{ 'W', ' ', ' ', ' ', 'W', ' ', ' ', ' ', 'W', ' ', ' ', ' ', 'W', 'W', ' ', 'W', 'W', ' ', 'W', 'W', 'W', 'W', 'W', ' ', 'W' },//12
{ 'W', 'W', 'W', ' ', 'W', ' ', 'W', ' ', 'W', 'W', 'W', ' ', 'W', 'W', ' ', ' ', ' ', ' ', 'W', 'W', 'W', 'W', 'W', ' ', 'W' },//13
{ 'W', 'W', 'W', ' ', ' ', ' ', 'W', ' ', 'W', 'W', 'W', ' ', 'W', 'W', 'W', 'W', 'W', ' ', 'W', ' ', ' ', ' ', 'W', ' ', 'W' },//14
{ 'W', 'W', 'W', 'W', 'W', 'W', 'W', ' ', 'W', 'W', 'W', ' ', 'W', 'W', 'W', 'W', 'W', ' ', 'W', ' ', 'W', ' ', 'W', ' ', 'W' },//15
{ 'W', 'W', 'W', 'W', 'W', 'W', 'W', ' ', ' ', ' ', 'W', ' ', 'W', 'W', 'W', 'W', 'W', ' ', 'W', ' ', 'W', ' ', 'W', ' ', 'W' },//16
{ 'W', 'W', 'W', 'W', 'W', 'W', 'W', ' ', 'W', ' ', 'W', ' ', 'W', 'W', 'W', 'W', 'W', ' ', 'W', ' ', 'W', ' ', ' ', ' ', 'W' },//17
{ 'W', 'W', 'W', 'W', 'W', 'W', 'W', ' ', 'W', ' ', 'W', ' ', 'W', 'W', 'W', 'W', 'W', ' ', 'W', ' ', 'W', 'W', 'W', 'W', 'W' },//18
{ 'W', 'W', 'W', 'W', 'W', 'W', 'W', ' ', 'W', ' ', ' ', ' ', ' ', 'W', 'W', 'W', 'W', ' ', 'W', ' ', 'W', ' ', ' ', ' ', 'W' },//19
{ 'W', ' ', ' ', ' ', ' ', ' ', 'W', ' ', 'W', 'W', 'W', 'W', ' ', 'W', 'W', 'W', 'W', ' ', 'W', ' ', 'W', ' ', 'W', ' ', 'W' },//20
{ 'W', ' ', 'W', 'W', 'W', ' ', 'W', ' ', 'W', ' ', ' ', 'W', ' ', ' ', ' ', ' ', ' ', ' ', 'W', ' ', 'W', ' ', 'W', ' ', 'W' },//21
{ 'W', ' ', 'W', 'X', 'W', ' ', 'W', ' ', 'W', 'W', ' ', 'W', ' ', 'W', ' ', 'W', 'W', 'W', 'W', ' ', 'W', 'W', 'W', ' ', 'W' },//22
{ 'W', ' ', ' ', ' ', 'W', ' ', ' ', ' ', 'W', 'W', ' ', ' ', ' ', 'W', ' ', 'W', 'W', 'W', 'W', ' ', ' ', ' ', ' ', ' ', 'W' },//23
{ 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },//24
// 0    1    2    3    4    5    6    7    8    9   10    11   12   13   14   15   16  17    18   19  20    21  22    23   24 
};
//{{W,false, false, false, true},W,W}
struct nodetype {
	int stateID; //(X,Y) -> X*(XMAX+1)+Y
	int parent; //node it came from
	string action; //east,west..ect
	int cost; //number of steps to get there
};

/*vector<>*/ void getSucc(nodetype curr, nodetype Chirldren[], int &numChild);
bool DFS(nodetype path[], int goal, nodetype start, int &pathsize);
bool mapFun(int state);
void setMap();
void printMap();
void updateMap(int State);

int main() {
	char w = 219;
	
	int pathsize;
	nodetype path[200];
	nodetype start = {entrance, -1, "start", 0};
	setMap();
	printMap();
	if (DFS(path, goal, start, pathsize)) {
		for (int i = 0; i < pathsize; i++)
		{
			system("pause");
			system("cls");
			cout << path[i].action << endl;
			updateMap(path[i].stateID);
			printMap();			
		}
	}
	else
		cout << "I am error";
	system("pause");

	return 0;
}


void getSucc(nodetype curr, nodetype Children[], int &numChild) {
	int x = curr.stateID % (XMAX + 1);
	int y = curr.stateID / (XMAX + 1);
	cout << "x = " << x << endl;
	cout << "y = " << y << endl;
	nodetype newnode;
	numChild = 0;
	newnode.parent = curr.stateID;
	if (mapFun(curr.stateID - 1)) {//we can go left
		cout << "can go left;"<< curr.stateID - 1 << endl;
		newnode.stateID = curr.stateID - 1; newnode.action = "West"; newnode.cost = curr.cost + 1;
		Children[numChild++] = newnode;
	}
	if (mapFun(curr.stateID + XMAX + 1)) {//we can go down
		cout << "can go down;" << curr.stateID + XMAX + 1 << endl;
		newnode.stateID = curr.stateID + XMAX +1; newnode.action = "South"; newnode.cost = curr.cost + 1;
		Children[numChild++] = newnode;
	}
	if (mapFun(curr.stateID + 1)) {//we can go right
		cout << "can go right;" << curr.stateID + 1 << endl;
		newnode.stateID = curr.stateID + 1; newnode.action = "East"; newnode.cost = curr.cost + 1;
		Children[numChild++] = newnode;
	}
	if (mapFun(curr.stateID - XMAX - 1 && curr.stateID - XMAX - 1 > -1)) {//we can go up
		cout << "can go up;" << curr.stateID - XMAX - 1 << endl;
		newnode.stateID = curr.stateID - XMAX - 1; newnode.action = "North"; newnode.cost = curr.cost + 1;
		Children[numChild++] = newnode;
	}
}



bool DFS(nodetype path[], int goal, nodetype start, int &pathsize) {
	nodetype Closed[XMAX*YMAX + 1];
	bool visited[XMAX*YMAX + 1] = { 0 };
	nodetype Children[4];
	stack<nodetype> fringe;
	nodetype curr;
	fringe.push(start);
	while (!fringe.empty()) {
		curr = fringe.top();
		fringe.pop();
		if (curr.stateID == goal)
		{
		
			pathsize = curr.cost;
			path[pathsize] = curr;
			for (int i = pathsize - 1; i >= 0; i--)
			{
				curr = Closed[curr.parent];
				path[i] = curr;
			}
			return true;
		}
		if (!visited[curr.stateID]) {
			visited[curr.stateID] = true;
			cout << curr.stateID << endl;
			Closed[curr.stateID] = curr;
			int numChildren = 0;
			getSucc(curr, Children, numChildren);
			for (int i = 0; i < numChildren; i++)
				fringe.push(Children[i]);
		}
	}

	return false;
}

bool mapFun(int state) {
	int x, y;
	y = state % 26;
	x = state / 26;
	if (x < 0)
		return false;
	if (y < 0)
		return false;
	if (state < 0)
		return false;
	if (map[x][y] == 219 || map[x][y] == 'W' || state == 'E' || state == entrance) return false;
	return true;
}

void updateMap(int state) {
	int x, y;
	y = state % 26;
	x = state / 26;
	for (int i = 0; i < XMAX; i++) {
		for (int k = 0; k < YMAX; k++) {
			if (map[i][k] == 43) {
				map[i][k] = 248;
			}
		}
	}
	map[x][y] = 43;
}

void setMap() {
	for (int i = 0; i < XMAX; i++) {
		for (int k = 0; k < YMAX; k++) {
			if (map[i][k] == 'W') {
				map[i][k] = 219;
			}
			if (map[i][k] == 'E') {
				map[i][k] = 43;
			}
			//if (map[i][k] == 'X') {
			//	map[i][k] = 248;
			//}
		}
	}
}

void printMap(){
	for (int i = 0; i < XMAX; i++) {
		for (int k = 0; k < YMAX; k++) {
			cout << map[i][k];
		}
		cout << endl;
	}
};