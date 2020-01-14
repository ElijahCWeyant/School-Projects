#include <iostream>
#include <string>
#include <queue>


using namespace std;

/*As is the problem only works for B<10.  It can easily be modified to work for any B>0*/
const int BoatMax = 1;
const int MisMax = 5;  //Max number of Mis
const int CanMax = 5;  //Max number of Can


struct nodeType
{
	int stateId;
	int parent;  //the id of the state it came from
	string action; //the action that was taken to get this state
	double cost;  //the number of steps to get to this state
};

void getSuccesor(nodeType curr, nodeType Children[], int &numChildren);
bool graphBFS(nodeType path[], int goal, int &pathsize);
bool is_valid(int);
void print(int);

int main()
{
	cout << 0;
	int goal = 0;
	int pathsize;
	nodeType path[72];
	if (graphBFS(path, goal, pathsize))
	{
		cout << 1;
		system("cls");
		cout << "\n\nSolution:\n";
		for (int i = 0; i <= pathsize; i++)
		{
			cout << 2;
			cout << "\tAction " << i << " : " << path[i].action << endl;
			int boat = path[i].stateId / 36;
			int mis = (path[i].stateId-(boat*36)) / 6;
			int can = path[i].stateId % 6;
			cout << "\t\t\t(" << boat << ", " << mis << ","<< can <<")" << endl;
			print(path[i].stateId);
			cout << endl;
			system("pause");
			system("cls");
		}
	}
	system("pause");
	return 0;
}

bool graphBFS(nodeType path[], int goal, int &pathsize)
{
	cout << 6 ;
	nodeType Closed[72]; //closed set, the nodes already visited
	bool Visited[72] = { 0 };  //Visited[stateId]==true if stateId is visited
	nodeType Children[17];
	queue<nodeType> Fringe;  //Fringe is a queue for BFS
	nodeType start = { 71,-1,"starting state",0 }, curr;
	Fringe.push(start);
	while (!Fringe.empty())
	{
		cout << 5;
		curr = Fringe.front(); Fringe.pop(); //take next node from the Fringe
		if ((curr.stateId == goal))  //reached the goal state
		{
			cout << 6;
			//return solution
			pathsize = curr.cost;
			path[pathsize] = curr;
			for (int i = pathsize - 1; i >= 0; i--)  //alternatively use a while loop until curr.parent==-1
			{
				cout << 7;
				curr = Closed[curr.parent];
				path[i] = curr;
			}
			return true;
		}
		if (!Visited[curr.stateId])  //if not has not been visited, expand
		{
			cout << 8;
			Visited[curr.stateId] = true;  //mark it as visited
			Closed[curr.stateId] = curr;   //add it to the closed set
			int numChildren;
			getSuccesor(curr, Children, numChildren);  //get the children nodes
			for (int i = 0; i < numChildren; i++) {
				//cout << Children[i].stateId << "\n";
				Fringe.push(Children[i]);   //add them to the fringe
			}
		}
	}
	return false;
}



void getSuccesor(nodeType curr, nodeType Children[], int &numChildren)
{
	int boat = curr.stateId / 36, mis = (curr.stateId- (boat * 36)) / 6, can = curr.stateId % 6;
	nodeType newnode;
	numChildren = 0;
	newnode.parent = curr.stateId;
/* move one person*/
	/*move one mis away*/
	/*move one can away*/
	/*move one mis toward*/
	/*move one can toward*/
/* move two people*/
	/*move two mis away*/
	/*move two can away*/
	/*move both away*/
	/*move two mis toward*/
	/*move two can toward*/
	/*move both toward*/
/*move three people*/
	/*Move 3 mis and 0 can away*/
	/*move 2 mis and 1 can away*/
	/*move 1 mis and 2 can away*/
	/*move 0 mis and 3 can away*/
	/*Move 3 mis and 0 can toward*/
	/*move 2 mis and 1 can toward*/
	/*move 1 mis and 2 can toward*/
	/*move 0 mis and 3 can toward*/
	

	if (boat == 1 && mis >= 1)
	{
		cout << "Frontier: 1MA " << "\n";
		//Move one Mis Away (1, mis, can)
		if (is_valid(0 + 6 * (mis - 1)+(can))) {
			newnode.stateId = 0 + 6 * (mis-1)+(can); newnode.action = "one mis away"; newnode.cost = curr.cost + 1;
			Children[numChildren++] = newnode;
			
		}
	}

	if (boat == 1 && can >= 1)
	{
		cout << "Frontier: 1CA " << "\n";
		//Move one Can Away (1, mis, can-2)
		if (is_valid(0 + 6  * (mis)+(can - 1))){
			newnode.stateId = 0 + 6  * (mis)+(can - 1); newnode.action = "one Can away"; newnode.cost = curr.cost + 1;
			Children[numChildren++] = newnode;
		}

	}

	if (boat == 0 && mis < MisMax)
	{
		cout << "Frontier: 1MT " << "\n";
		//Move one Mis Towards (1, mis + 1, can)
		if (is_valid(36 + 6  * (mis + 1) + (can))) {
			newnode.stateId = 36 + 6  * (mis + 1) + (can); newnode.action = "One mis Towards"; newnode.cost = curr.cost + 1;
			Children[numChildren++] = newnode;
		}

	}

	if (boat == 0 && can < CanMax)
	{
		cout << "Frontier: 1CT " << "\n";
		//Move one Can Towards (1, mis, can+1)
		if (is_valid(36 + 6  * (mis)+(can + 1))) {
			newnode.stateId = 36 + 6  * (mis)+(can + 1); newnode.action = "One Can Towards"; newnode.cost = curr.cost + 1;
			Children[numChildren++] = newnode;
		}

	}


	if (boat == 1 && mis - 2 >= 0)
	{
		cout << "Frontier: 2MA " << "\n";
		//Move two Mis Away (1, mis, can-2)
		if(is_valid(0 + 6  * (mis - 2) + (can))) {
			newnode.stateId = 0 + 6  * (mis - 2) + (can); newnode.action = "Two Mis Away"; newnode.cost = curr.cost + 1;
			Children[numChildren++] = newnode;
		}
	}

	if (boat == 1 && can - 2 >= 0)
	{
		cout << "Frontier: 2CA " << "\n";
		//Move two can Away (1, mis, can-2)
		if (is_valid(0 + 6  * (mis)+(can - 2))) {
			newnode.stateId = 0 + 6  * (mis)+(can - 2); newnode.action = "Two Can Away"; newnode.cost = curr.cost + 1;
			Children[numChildren++] = newnode;
		}
	}

	if (boat == 1 && mis - 1 >= 0 && can - 1 >= 0)
	{
		cout << "Frontier: 1BA " << "\n";
		//Move both Away (1, mis-1, can-1)
		if (is_valid(0 + 6  * (mis - 1) + (can - 1))) {
			newnode.stateId = 0 + 6  * (mis - 1) + (can - 1); newnode.action = "Both Away"; newnode.cost = curr.cost + 1;
			Children[numChildren++] = newnode;
		}
	}

	if (boat == 0 && mis + 2 <= MisMax)
	{
		cout << "Frontier: 2MT " << "\n";
		//Move two Mis towards (1, mis, can+2)
		if (is_valid(36 + 6  * (mis + 2) + (can))) {
			newnode.stateId = 36 + 6  * (mis + 2) + (can); newnode.action = "Two Can Towards"; newnode.cost = curr.cost + 1;
			Children[numChildren++] = newnode;
		}
	
	}

	if (boat == 0  && can+2 <= CanMax)
	{
		cout << "Frontier: 2CT " << "\n";
		//Move two can towards (1, mis, can+2)
		if (is_valid(36 + 6  * (mis)+(can + 2))) {
			newnode.stateId = 36 + 6  * (mis)+(can + 2); newnode.action = "Two Can Towards"; newnode.cost = curr.cost + 1;
			Children[numChildren++] = newnode;
		}
	}

	if (boat == 0 && mis < MisMax && can < CanMax)
	{
		cout << "Frontier: 1BT " << "\n";
		//Move both towards (1, mis+1, can+1)
		if (is_valid(36 + 6  * (mis + 1) + (can + 1))) {
			newnode.stateId = 36 + 6  * (mis + 1) + (can + 1); newnode.action = "Both Towards"; newnode.cost = curr.cost + 1;
			Children[numChildren++] = newnode;
		}
	}
	/*move three people*/
	/*Move 3 mis and 0 can away*/
	if (boat == 1 && mis - 3 >= 0 && can - 0 >= 0)
	{
		cout << "Frontier: 1BT " << "\n";
		//Move 3 mis 0 Can towards (1, mis-1, can-2)
		if (is_valid(0 + 6 * (mis - 3) + (can - 0))) {
			newnode.stateId = 36 + 6 * (mis - 3) + (can - 0); newnode.action = "-3 Mis - 0 Can Away"; newnode.cost = curr.cost + 1;
			Children[numChildren++] = newnode;
		}
	}
	/*move 2 mis and 1 can away*/
	if (boat == 1 && mis - 2 >= 0 && can - 1 >= 0)
	{
		cout << "Frontier: 1BT " << "\n";
		//Move 3 mis 0 Can towards (1, mis-1, can-2)
		if (is_valid(0 + 6 * (mis - 2) + (can - 1))) {
			newnode.stateId = 36 + 6 * (mis - 2) + (can - 1); newnode.action = "-2 Mis - 1 Can Away"; newnode.cost = curr.cost + 1;
			Children[numChildren++] = newnode;
		}
	}
	/*move 1 mis and 2 can away*/
	if (boat == 1 && mis -1 >= 0 && can - 2 >= 0)
	{
		cout << "Frontier: 1BT " << "\n";
		//Move 3 mis 0 Can towards (1, mis-1, can-2)
		if (is_valid(0 + 6 * (mis - 1) + (can - 2))) {
			newnode.stateId = 36 + 6 * (mis - 1) + (can - 2); newnode.action = "-1 Mis - 2 Can Away"; newnode.cost = curr.cost + 1;
			Children[numChildren++] = newnode;
		}
	}
	/*move 0 mis and 3 can away*/
	if (boat == 1 && can-3 >= 0)
	{
		cout << "Frontier: 1BT " << "\n";
		//Move 3 mis 0 Can towards (1, mis+3, can)
		if (is_valid(0 + 6 * (mis - 0) + (can - 3))) {
			newnode.stateId = 36 + 6 * (mis - 0) + (can - 3); newnode.action = "-0 Mis - 3 Can Away"; newnode.cost = curr.cost + 1;
			Children[numChildren++] = newnode;
		}
	}
	/*Move 3 mis and 0 can toward*/
	if (boat == 0 && mis + 3 < MisMax)
	{
		cout << "Frontier: 1BT " << "\n";
		//Move 3 mis 0 Can towards
		if (is_valid(36 + 6 * (mis + 3) + (can + 0))) {
			newnode.stateId = 36 + 6 * (mis + 3) + (can + 0); newnode.action = "3 Mis + 0 Can Towards"; newnode.cost = curr.cost + 1;
			Children[numChildren++] = newnode;
		}
	}
	/*move 2 mis and 1 can toward*/
	if (boat == 0 && mis +2 <= MisMax && can +1 <= CanMax)
	{
		cout << "Frontier: 1BT " << "\n";
		//Move 2 mis 1 Can towards 
		if (is_valid(36 + 6 * (mis+2)+(can + 1))) {
			newnode.stateId = 36 + 6 * (mis + 2) + (can + 1); newnode.action = "2 Mis + 1 Can Towards"; newnode.cost = curr.cost + 1;
			Children[numChildren++] = newnode;
		}
	}
	/*move 1 mis and 2 can toward*/
	if (boat == 0 && mis + 1 <= MisMax && can +2 <= CanMax)
	{
		cout << "Frontier: 1BT " << "\n";
		//Move 1 mis 2 Can towards 
		if (is_valid(36 + 6 * (mis+1)+(can + 2))) {
			newnode.stateId = 36 + 6 * (mis + 1) + (can + 2); newnode.action = "1 Mis + 2 Can Towards"; newnode.cost = curr.cost + 1;
			Children[numChildren++] = newnode;
		}
	}
	/*move 0 mis and 3 can toward*/
	if (boat == 0 && can + 3 <= CanMax)
	{
		cout << "Frontier: 1BT " << "\n";
		//Move 3 Can towards 
		if (is_valid(36 + 6 * (mis)+(can + 3))) {
			newnode.stateId = 36 + 6 * (mis)+(can + 3); newnode.action = "0 Mis + 3 Can Towards"; newnode.cost = curr.cost + 1;
			Children[numChildren++] = newnode;
		}
	}



};




bool is_valid(int state_id) {
	cout << "Valid: " ;
	int boat = state_id / 36;
	int	mis = (state_id-(boat*36)) / 6;
	int can = state_id % 6;

	if (mis < can && mis != 0){
		cout << "A" << boat << mis << can <<"\n";
		return 0;
	}
	if (MisMax - mis < CanMax - can && mis != MisMax) {
		cout << "B" << boat << mis << can << "\n";
		return 0;
	}
	if (mis > MisMax || can > CanMax || mis < 0 || can < 0 || boat > 1 || boat < 0) {
		cout << "C" << boat << mis << can << "\n";
		return 0;
	}
	cout << "D" << boat << mis << can << "\n";
	return 1;
};





void print(int state_id) {
	int boat = state_id / 36;
	int	mis = (state_id-(boat * 36)) / 6;
	int can = state_id % 6;
	int mis_count = 0;
	int can_count = 0;

	cout << "\n";
	while (mis_count < mis) {
		cout << "M";
		mis_count++;
	}
	cout << "\n";
	while (can_count < can) {
		cout << "C";
		can_count++;
	}
	cout << "\n";
	if (boat == 1) {
		cout << "\\___/";
	}
	cout << "\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n";
	cout << "\n";
	while (mis_count < MisMax) {
		cout << "M";
		mis_count++;
	}
	cout << "\n";
	while (can_count < CanMax) {
		cout << "C";
		can_count++;
	}
	cout << "\n";
	if (boat == 0) {
		cout << "\\___/" << endl;
	}
	
}
