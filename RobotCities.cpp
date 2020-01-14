#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>
#include <math.h>

using namespace std;

const int maxV = 100; //maximum allowed number of cities
const int maxC = 200; //maximum allowed number of connections

double getdistance(int, int);
void print();

struct nodeType    //structure of each node in the tree
{
	int state;          //the index of the city
	int parent;         //the state of the parent node
	int costG;          //g(n), cost from start to present
	int costH;          //h(n), estimated cost by heuristic from present to goal
	//overload the < operator so we can use it for the priority queue
	friend bool operator<(nodeType x, nodeType y)
	{
		return x.costG + x.costH > y.costG + y.costH;
	};
};

/*Problem information***********************************************************************************************/
/*******************************************************************************************************************/
string Cities[maxV] = { "A" , "B", "Start", "C", "D", "E", "F", "G", "H",
"I", "J", "K", "L", "M", "N", "O","P", "Q", "R", "S" ,"T", "U", "V", "W", "X", "Y", "Z", "1", "2", "3", "Goal", "4"};




//physical coordinates {x,y} of the cities 
//for the robot navigtion problem, these could be the coordinates of the corners of the obstacles
double Coords[maxV][2] = { {1, 7},{ 2,14 },{ 2,29 },{ 3,17 },{ 3,27 },{ 4,10 },{ 5,1 },{ 5,7 },
{ 5,17 },{ 5,27 },{ 6,14 },{ 7,22 },{ 8,8 },{ 8,16 },{ 9,2 },{ 9,6 },{ 10,19 },{ 10,25 },{ 11,2 },{ 11,6 },
{ 12,12 },{ 13,6 },{ 13,22 },{ 13,28 },{ 15,4 },{ 15,8 },{ 15,11 },{ 15,24 },{ 16,11 },{ 16,24 },{ 17,3 },
{ 17,6 } };


//the connection map between the cities {city1, city2, distance}
int Connections[maxC][3] = {
{ 2 , 0 , getdistance(2,0) } ,
{ 2 , 1 , getdistance(2,1) } ,
{ 2 , 3 , getdistance(2,3) } ,
{ 2 , 4 , getdistance(2,4) } ,
{ 2 , 9 , getdistance(2,9) } ,
{ 9 , 10 , getdistance(9,10) } ,
{ 9 , 11 , getdistance(9,11) } ,
{ 9 , 17 , getdistance(9,17) } ,
{ 9 , 23 , getdistance(9,23) } ,
{ 10 , 12 , getdistance(10,12) } ,
{ 10 , 13 , getdistance(10,13) } ,
{ 10 , 11 , getdistance(10,11) } ,
{ 19 , 21 , getdistance(19,21) } ,
{ 19 , 25 , getdistance(19,25) } ,
{ 19 , 28 , getdistance(19,28) } ,
{ 19 , 26 , getdistance(19,26) } ,
{ 19 , 20 , getdistance(19,20) } ,
{ 22 , 25 , getdistance(22,25) } ,
{ 22 , 26 , getdistance(22,26) } ,
{ 22 , 27 , getdistance(22,27) } ,
{ 25 , 28 , getdistance(25,28) } ,
{ 26 , 31 , getdistance(26,31) } ,
{ 26 , 28 , getdistance(26,28) } ,
{ 26 , 27 , getdistance(26,27) } ,
{ 27 , 29 , getdistance(27,29) } ,
{ 28 , 31 , getdistance(28,31) } ,
{ 29 , 28 , getdistance(29,28) } ,
{ 29 , 31 , getdistance(29,31) } ,
{ 31 , 30 , getdistance(31,30) } ,
{ 0 , 1 , getdistance(0,1) } ,
{ 0 , 5 , getdistance(0,5) } ,
{ 0 , 7 , getdistance(0,7) } ,
{ 7 , 12 , getdistance(7,12) } ,
{ 7 , 15 , getdistance(7,15) } ,
{ 7 , 13 , getdistance(7,13) } ,
{ 7 , 14 , getdistance(7,14) } ,
{ 3 , 4 , getdistance(3,4) } ,
{ 3 , 13 , getdistance(3,13) } ,
{ 7 , 10 , getdistance(7,10) } ,
{ 11 , 16 , getdistance(11,16) } ,
{ 11 , 17 , getdistance(11,17) } ,
{ 11 , 13 , getdistance(11,13) } ,
{ 11 , 12 , getdistance(11,12) } ,
{ 20 , 25 , getdistance(20,25) } ,
{ 20 , 21 , getdistance(20,21) } ,
{ 20 , 26 , getdistance(20,26) } ,
{ 20 , 27 , getdistance(20,27) } ,
{ 20 , 22 , getdistance(20,22) } ,
{ 22 , 23 , getdistance(22,23) } ,
{ 23 , 27 , getdistance(23,27) } ,
{ 1 , 5 , getdistance(1,5) } ,
{ 1 , 10 , getdistance(1,10) } ,
{ 1 , 8 , getdistance(1,8) } ,
{ 3 , 8 , getdistance(3,8) } ,
{ 3 , 10 , getdistance(3,10) } ,
{ 1 , 3 , getdistance(1,3) } ,
{ 1 , 4 , getdistance(1,4) } ,
{ 1 , 13 , getdistance(1,13) } ,
{ 8 , 10 , getdistance(8,10) } ,
{ 8 , 13 , getdistance(8,13) } ,
{ 8 , 16 , getdistance(8,16) } ,
{ 8 , 11 , getdistance(8,11) } ,
{ 8 , 9 , getdistance(8,9) } ,
{ 12 , 14 , getdistance(12,14) } ,
{ 12 , 15 , getdistance(12,15) } ,
{ 12 , 19 , getdistance(12,19) } ,
{ 12 , 20 , getdistance(12,20) } ,
{ 12 , 13 , getdistance(12,13) } ,
{ 23 , 29 , getdistance(23,29) } ,
{ 24 , 30 , getdistance(24,30) } ,
{ 24 , 31 , getdistance(24,31) } ,
{ 4 , 9 , getdistance(4,9) } ,
{ 5 , 7 , getdistance(5,7) } ,
{ 5 , 10 , getdistance(5,10) } ,
{ 5 , 12 , getdistance(5,12) } ,
{ 5 , 15 , getdistance(5,15) } ,
{ 5 , 14 , getdistance(5,14) } ,
{ 17 , 22 , getdistance(17,22) } ,
{ 17 , 23 , getdistance(17,23) } ,
{ 17 , 27 , getdistance(17,27) } ,
{ 21 , 24 , getdistance(21,24) } ,
{ 21 , 25 , getdistance(21,25) } ,
{ 21 , 26 , getdistance(21,26) } ,
{ 21 , 27 , getdistance(21,27) } ,
{ 21 , 22 , getdistance(21,22) } ,
{ 13 , 20 , getdistance(13,20) } ,
{ 13 , 26 , getdistance(13,26) } ,
{ 13 , 16 , getdistance(13,16) } ,
{ 14 , 18 , getdistance(14,18) } ,
{ 14 , 15 , getdistance(14,15) } ,
{ 15 , 19 , getdistance(15,19) } ,
{ 15 , 26 , getdistance(15,26) } ,
{ 15 , 25 , getdistance(15,25) } ,
{ 15 , 28 , getdistance(15,28) } ,
{ 16 , 20 , getdistance(16,20) } ,
{ 16 , 25 , getdistance(16,25) } ,
{ 16 , 26 , getdistance(16,26) } ,
{ 16 , 22 , getdistance(16,22) } ,
{ 18 , 30 , getdistance(18,30) } ,
{ 18 , 24 , getdistance(18,24) } ,
{ 18 , 21 , getdistance(18,21) } ,
{ 18 , 20 , getdistance(18,20) } ,
{ 18 , 19 , getdistance(18,19) } ,
{ 15 , 20 , getdistance(15,20) } ,
{ 25 , 31 , getdistance(25,31) } ,
{ 25 , 26 , getdistance(25,26) }
};

int numCon = 106;  //number of connections
int numV = 32;    //number of cities
/*******************************************************************************************************************/



//builds the adjacency matrix of the graph
//AM[i][j]=distance between i and j as given by Connections (0 if no connection)
void getAdjMatrix(double AM[][maxV], int numV, int Connections[][3], int numCon);

//calculate the straight line distance heuristic, from each city to the goal
void getSLD(double Coord[][2], int numV, int goal, double hSLD[]);


//All the functions bellow need some information about the problem
//in this case the adjacency matrix, the start and the goal is all the input they need
//returns path containing all the nodes to the solution

//implements the breadth first search
bool graphBFS(int start, int goal, double AM[][maxV], int numV, nodeType path[], int &pathsize);

//implements the depth first search
bool graphDFS(int start, int goal, double AM[][maxV], int numV, nodeType path[], int &pathsize);

//implements the uniform cost search
bool graphUniformCost(int start, int goal, double AM[][maxV], int numV, nodeType path[], int &pathsize);

//implements the A* search using straight line distance heuristic
bool graphAstarSLD(int start, int goal, double AM[][maxV], int numV, nodeType path[], int &pathsize);

//returns the children of current node
void getSuccesor(double AM[][maxV], int numV, nodeType curr, nodeType Children[], int &numChildren);


int main()
{
	/*Initialization information****************************************************************************************/
	/*******************************************************************************************************************/
	string startname = "Start", goalname = "Goal";
	int start = 0;  //the index of the starting city
	int goal = 0;  //the index of the goal city

	for (int i = 0; i < numV; i++)
	{
		if (Cities[i] == startname)
			start = i;
		if (Cities[i] == goalname)
			goal = i;
	}

	/*******************************************************************************************************************/


	double AM[maxV][maxV] = { {0} }; //adjacency matrix AM[i][j]>0 implies there is a connection between i and j with weight AM[i][j]
	//Get adjacency matrix
	getAdjMatrix(AM, numV, Connections, numCon);

	nodeType path[maxV];
	int pathsize;
	//BFS
	double distTraveled;
	int parent = -1;

	cout << "\nBFS:\n\n";
	if (graphBFS(start, goal, AM, numV, path, pathsize))
	{
		distTraveled = 0;
		for (int i = pathsize - 1; i >= 0; i--)
		{
			cout << Cities[path[i].state] << ", ";
			if (parent != -1)
			{
				distTraveled = distTraveled + getdistance(path[i].state, parent);
			}
			parent = path[i].state;

		}
		cout << "\nDistance traveled = " << distTraveled;
		cout << "\n\n";
	}

	distTraveled = 0;
	parent = -1;

	//DFS
	cout << "\nDFS:\n\n";
	if (graphDFS(start, goal, AM, numV, path, pathsize))
	{
		
		for (int i = pathsize - 1; i >= 0; i--)
		{
			cout << Cities[path[i].state] << ", ";
			if (parent != -1)
			{
				distTraveled = distTraveled + getdistance(path[i].state, parent);
			}
			parent = path[i].state;
		}
		cout << "\nDistance traveled = " << distTraveled;
		cout << "\n\n";
	}

	distTraveled = 0;
	parent = -1;

	//Uniform cost;
	cout << "\nUniform Cost:\n\n";
	if (graphUniformCost(start, goal, AM, numV, path, pathsize))
	{
		for (int i = pathsize - 1; i >= 0; i--)
		{
			cout << Cities[path[i].state] << ", ";
			if (parent != -1)
			{
				distTraveled = distTraveled + getdistance(path[i].state, parent);
			}
			parent = path[i].state;
		}
		cout << "\nDistance traveled = " << distTraveled;
		cout << "\n\n";
	}


	distTraveled = 0;
	parent = -1;
	//A* with straight line heuristic
	cout << "\nA* with straight line distance heuristic:\n\n";

	if (graphAstarSLD(start, goal, AM, numV, path, pathsize))
	{
		for (int i = pathsize - 1; i >= 0; i--)
		{
			cout << Cities[path[i].state] << ", ";
			if (parent != -1)
			{
				distTraveled = distTraveled + getdistance(path[i].state, parent);
			}
			parent = path[i].state;
		}
		cout << "\nDistance traveled = " << distTraveled;
		cout << "\n\n";
		//print();
	}
	system("pause");
	return 0;
}



void getSuccesor(double AM[][maxV], int numV, nodeType curr, nodeType Children[], int &numChildren)
{
	int k = curr.state;
	nodeType newnode;
	numChildren = 0;
	newnode.parent = curr.state;
	for (int i = 0; i < numV; i++)
	{
		if (AM[k][i] > 0)
		{
			newnode.costG = curr.costG + AM[k][i]; //update the cost g(n)
			newnode.state = i;
			newnode.costH = 0;    //the heuristic cost is assumed 0 (the informed searches will update this themselves)
			Children[numChildren++] = newnode;
		}
	}
}



bool graphBFS(int start, int goal, double AM[][maxV], int numV, nodeType path[], int &pathsize)
{

	nodeType Closed[maxV]; //closed set, the nodes already visited
	bool Visited[maxV] = { 0 };  //Visited[stateId]==true if stateId is visited
	nodeType Children[maxV];
	queue<nodeType> Fringe;  //for BFS the Fringe is a queue
	nodeType startState = { start,-1,0,0 }, curr;
	Fringe.push(startState); //initialize the fringe with the start node 

	while (!Fringe.empty())
	{
		curr = Fringe.front(); Fringe.pop(); //take next node from the Fringe
		if (curr.state == goal)  //reached the goal state
		{
			//return solution
			pathsize = 0;
			path[pathsize++] = curr;
			while (curr.parent >= 0)
			{
				curr = Closed[curr.parent];
				path[pathsize++] = curr;
			}
			return true;
		}

		int numChildren;
		if (!Visited[curr.state])  //if the state has not been visited before, expand
		{
			Visited[curr.state] = true;
			Closed[curr.state] = curr;
			getSuccesor(AM, numV, curr, Children, numChildren);
			for (int i = 0; i < numChildren; i++)
			{
				Fringe.push(Children[i]);
			}
		}
	}
	return false;
}


bool graphDFS(int start, int goal, double AM[][maxV], int numV, nodeType path[], int &pathsize)
{

	nodeType Closed[maxV]; //closed set, the nodes already visited
	bool Visited[maxV] = { 0 };  //Visited[stateId]==true if stateId is visited
	nodeType Children[maxV];
	stack<nodeType> Fringe;     //for the DFS, the Fringe is a Stack.  This is the only difference between DFS and BFS
	nodeType startState = { start,-1,0,0 }, curr;
	Fringe.push(startState);
	while (!Fringe.empty())
	{
		curr = Fringe.top(); Fringe.pop(); //take next node from the Fringe
		if (curr.state == goal)  //reached the goal state
		{
			//return solution
			pathsize = 0;
			path[pathsize++] = curr;
			while (curr.parent >= 0)
			{
				curr = Closed[curr.parent];
				path[pathsize++] = curr;
			}
			return true;
		}

		int numChildren;
		if (!Visited[curr.state])
		{
			Visited[curr.state] = true;
			Closed[curr.state] = curr;
			getSuccesor(AM, numV, curr, Children, numChildren);
			for (int i = 0; i < numChildren; i++)
			{
				Fringe.push(Children[i]);
			}
		}
	}
	return false;
}


bool graphUniformCost(int start, int goal, double AM[][maxV], int numV, nodeType path[], int &pathsize)
{

	nodeType Closed[maxV]; //closed set, the nodes already visited
	bool Visited[maxV] = { 0 };  //Visited[stateId]==true if stateId is visited
	nodeType Children[maxV];
	priority_queue<nodeType> Fringe;  //for the Uniform, the Fringe is a priority queue.  This is the only difference between it and BFS
	nodeType startState = { start,-1,0,0 }, curr;
	Fringe.push(startState);
	while (!Fringe.empty())
	{
		curr = Fringe.top(); Fringe.pop(); //take next node from the Fringe
		if (curr.state == goal)  //reached the goal state
		{
			//return solution
			pathsize = 0;
			path[pathsize++] = curr;
			while (curr.parent >= 0)
			{
				curr = Closed[curr.parent];
				path[pathsize++] = curr;
			}
			return true;
		}

		int numChildren;
		if (!Visited[curr.state])
		{
			Visited[curr.state] = true;
			Closed[curr.state] = curr;
			getSuccesor(AM, numV, curr, Children, numChildren);
			for (int i = 0; i < numChildren; i++)
			{
				Fringe.push(Children[i]);
			}
		}
	}
	return false;
}


bool graphAstarSLD(int start, int goal, double AM[][maxV], int numV, nodeType path[], int &pathsize)
{
	double h[maxV];
	//get heuristic.  For A* need to calculate a heuristic.  For the unifor cost h=0.
	getSLD(Coords, numV, goal, h);

	nodeType Closed[maxV]; //closed set, the nodes already visited
	bool Visited[maxV] = { 0 };  //Visited[stateId]==true if stateId is visited
	nodeType Children[maxV];
	priority_queue<nodeType> Fringe;
	nodeType startState = { start,-1,0,h[start] }, curr;
	Fringe.push(startState);
	while (!Fringe.empty())
	{
		curr = Fringe.top(); Fringe.pop(); //take next node from the Fringe
		if (curr.state == goal)  //reached the goal state
		{
			//return solution
			pathsize = 0;
			path[pathsize++] = curr;
			while (curr.parent >= 0)
			{
				curr = Closed[curr.parent];
				path[pathsize++] = curr;
			}
			return true;
		}

		int numChildren;
		if (!Visited[curr.state])
		{
			Visited[curr.state] = true;
			Closed[curr.state] = curr;
			getSuccesor(AM, numV, curr, Children, numChildren);
			for (int i = 0; i < numChildren; i++)
			{
				//adjust the h cost for the node.  This and the initialization of h are the only differences with the uniform cost 
				Children[i].costH = h[Children[i].state];
				Fringe.push(Children[i]);
			}
		}
	}
	return false;
}



void getAdjMatrix(double AM[][maxV], int numV, int Connections[][3], int numCon)
{
	for (int i = 0; i < numV; i++)
		for (int j = 0; j < numV; j++)
			AM[i][j] = 0;

	for (int i = 0; i < numCon; i++)
	{
		int o = Connections[i][0], d = Connections[i][1], v = Connections[i][2];
		AM[o][d] = v;
		AM[d][o] = v;
	}
}


void getSLD(double Coord[][2], int numV, int goal, double hSLD[])  //calculate the straight line distance heuristic
{
	double x0 = Coord[goal][0], y0 = Coord[goal][1];
	for (int i = 0; i < numV; i++)
	{
		double xi = Coord[i][0], yi = Coord[i][1];
		hSLD[i] = sqrt((x0 - xi)*(x0 - xi) + (y0 - yi)*(y0 - yi));
	}
}



double getdistance(int city1, int city2) {
	double distance = -1;
	distance = sqrt(pow((Coords[city1][0] - Coords[city2][0]),2) + pow((Coords[city1][1] - Coords[city2][1]),2));
	return distance;
};




void print() {
	cout << "ITS ALIVE!!!!! \n";
	const int x = 32;
	const int y = 20;
	char map[x][y] = {'A'};
	for (int i = 0; i < x; i++) {
		cout << "OwO\n";
		map[0][i] = 'B';
	}
	for (int i = 0; i < x; i++) {
		cout << "OwO\n";
		map[x][i] = 'B';
	}
	for (int i = 0; i < y; i++) {
		cout << "OwO\n";
		map[i][0] = 'B';
	}
	for (int i = 0; i < y; i++) {
		cout << "OwO\n";
		map[i][y] = 'B';
	}
	   	  


	for (int i = 0; i < x; i++) {
		for (int k = 0; k < y; k++) {
			cout << map[i][k];
		}
		cout << "\n";
	}
	return;
}