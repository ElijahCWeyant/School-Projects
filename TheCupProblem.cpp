//An AI that, given two cups of variable sizes, that must either fill, empty, or pour one cup into another, will provide a way to get a certain measurement in one of the cups
#include <iostream>
#include <string>
#include <queue>

using namespace std;

/*As is the problem only works for B<10.  It can easily be modified to work for any B>0*/
const int A = 2;  //capacity of cup 1
const int B = 5;  //capacity of cup 2
// Our state = Position on board (x,y)
// Or we could go (x,y)








struct nodeType
{
	int stateId;
	// if state= (a,b) stateId=10*a+b
	//This is helpful so that can store nodes in array indexed by stateId (instead of using a map/dictionary)
	//can keep the state(a,b) but not necessary
	int parent;  //the id of the state it came from
	string action; //the action that was taken to get this state
	double cost;  //the number of steps to get to this state
};

void getSuccesor(nodeType curr, nodeType Children[], int &numChildren);
bool graphBFS(nodeType path[], int goal, int &pathsize);

int main()
{
	int goal = 1;
	int pathsize;
	nodeType path[100];
	cout << "Problem:\n\tHave 2 cups that can measure quantities " << A << " and " << B << " respectively.\n";
	cout << "Possible actions:\n\tCan empty or fill either cup from the tap.\n\tCan pour from any one cup to the other.\n";
	cout << "Goal:\n\tUsing minimum number of actions, measure the quantity : " << goal << "." << endl;
	if (graphBFS(path, goal, pathsize))
	{
		cout << "\n\nSolution:\n";
		for (int i = 0; i <= pathsize; i++)
		{
			cout << "\tAction " << i << " : " << path[i].action << endl;
			int a = path[i].stateId / 10;
			int b = path[i].stateId % 10;
			cout << "\t\t\t(" << a << ", " << b << ")" << endl;
		}
	}
	system("pause");
	return 0;
}

bool graphBFS(nodeType path[], int goal, int &pathsize)
{
	nodeType Closed[100]; //closed set, the nodes already visited
	bool Visited[100] = { 0 };  //Visited[stateId]==true if stateId is visited
	nodeType Children[8];
	queue<nodeType> Fringe;  //Fringe is a queue for BFS
	nodeType start = { 0,-1,"starting state",0 }, curr;
	Fringe.push(start);
	while (!Fringe.empty())
	{
		curr = Fringe.front(); Fringe.pop(); //take next node from the Fringe
		if ((curr.stateId / 10 == goal) || (curr.stateId % 10 == goal))  //reached the goal state
		{
			//return solution
			pathsize = curr.cost;
			path[pathsize] = curr;
			for (int i = pathsize - 1; i >= 0; i--)  //alternatively use a while loop until curr.parent==-1
			{
				curr = Closed[curr.parent];
				path[i] = curr;
			}
			return true;
		}
		if (!Visited[curr.stateId])  //if not has not been visited, expand
		{
			Visited[curr.stateId] = true;  //mark it as visited
			Closed[curr.stateId] = curr;   //add it to the closed set
			int numChildren;
			getSuccesor(curr, Children, numChildren);  //get the children nodes
			for (int i = 0; i < numChildren; i++)
				Fringe.push(Children[i]);   //add them to the fringe
		}
	}
	return false;
}



void getSuccesor(nodeType curr, nodeType Children[], int &numChildren)
{
	int a = curr.stateId / 10, b = curr.stateId % 10;
	nodeType newnode;
	numChildren = 0;
	newnode.parent = curr.stateId;
	if (a > 0)
	{
		//empty 1, new state (0, b) 
		newnode.stateId = b; newnode.action = "Empty 1"; newnode.cost = curr.cost + 1;
		Children[numChildren++] = newnode;
	}
	if (b > 0)
	{
		//empty 2, new state (a, 0) 
		newnode.stateId = a * 10; newnode.action = "Empty 2"; newnode.cost = curr.cost + 1;
		Children[numChildren++] = newnode;
	}
	if (a < A)
	{
		//fill 1, new state (A, b) 
		newnode.stateId = A * 10 + b; newnode.action = "Fill 1"; newnode.cost = curr.cost + 1;
		Children[numChildren++] = newnode;
	}
	if (b <B)
	{
		//fill 2, new state (a, B) 
		newnode.stateId = a * 10 + B; newnode.action = "Fill 2"; newnode.cost = curr.cost + 1;
		Children[numChildren++] = newnode;
	}
	if (a + b < A)
	{
		//pour from 2 to 1, new state (a+b, 0) 
		newnode.stateId = (a + b) * 10; newnode.action = "Pour 2->1"; newnode.cost = curr.cost + 1;
		Children[numChildren++] = newnode;
	}
	else
	{
		//pour from 2 to 1, new state (A, b-A+a) 
		newnode.stateId = A * 10 + b - A + a; newnode.action = "Pour 2->1"; newnode.cost = curr.cost + 1;
		Children[numChildren++] = newnode;
	}
	if (a + b < B)
	{
		//pour from 1 to 2, new state (0,a+b) 
		newnode.stateId = a + b; newnode.action = "Pour 1->2"; newnode.cost = curr.cost + 1;
		Children[numChildren++] = newnode;
	}
	else
	{
		//pour from 1 to 2, new state (a-B+b, B) 
		newnode.stateId = A * 10 + b - A + a; newnode.action = "Pour 2->1"; newnode.cost = curr.cost + 1;
		Children[numChildren++] = newnode;
	}

}