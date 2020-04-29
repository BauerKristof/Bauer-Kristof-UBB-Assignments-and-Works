/*
Nev: Bauer Kristof
Csoport: 511
*/

#include <iostream>
#include <fstream>
#include <limits>
using namespace std;


class BellmanFord
{
	int *distances;
	int numberofvertices;

	int akt[50] = { -1 };

public:
	const int MAX_VALUE = 999;

	BellmanFord(int numberofvertices)
	{
		this->numberofvertices = numberofvertices;
		distances = new int[numberofvertices + 1];
	}

	~BellmanFord()
	{
		delete[] distances;
	}


	void BellmanFordEvaluation(int source, int adjacencymatrix[][20])
	{
		for (int node = 1; node <= numberofvertices; node++)
		{
			distances[node] = MAX_VALUE;
		}


		distances[source] = 0;

		for (int node = 1; node <= numberofvertices - 1; node++)
		{
			for (int sourcenode = 1; sourcenode <= numberofvertices; sourcenode++)
			{
				for (int destinationnode = 1; destinationnode <= numberofvertices; destinationnode++)
				{
					if (adjacencymatrix[sourcenode][destinationnode] != MAX_VALUE)
					{
						if (distances[destinationnode] > (distances[sourcenode] + adjacencymatrix[sourcenode][destinationnode]))
						{
							distances[destinationnode] = distances[sourcenode] + adjacencymatrix[sourcenode][destinationnode];
							akt[destinationnode] = sourcenode;
						}
					}
				}
			}
		}


		for (int sourcenode = 1; sourcenode <= numberofvertices; sourcenode++)
		{
			for (int destinationnode = 1; destinationnode <= numberofvertices; destinationnode++)
			{
				if (adjacencymatrix[sourcenode][destinationnode] != MAX_VALUE)
				{
					if (distances[destinationnode] > distances[sourcenode] + adjacencymatrix[sourcenode][destinationnode])
						cout << "Negativ kor" << endl;
				}
			}
		}



	}

	int* getDistances()
	{
		return distances;
	}


	void bellmanUtKiir(int x)
	{
		cout << endl << x << " csomopont \n";


		int ut[20][20];
		int aktualiscsucs;

		for (int i = 1; i <= numberofvertices;i++)
		{
			ut[i][0] = 0;
			if (distances[i] > 0 && distances[i] < INT_MAX / 5)
			{
				aktualiscsucs = i;
				while (aktualiscsucs != x)
				{

					aktualiscsucs = akt[aktualiscsucs];
					ut[i][0]++;
					ut[i][ut[i][0]] = aktualiscsucs;
				}
			}
		}

		for (int i = 1; i <= numberofvertices; i++)
		{
			if (ut[i][0] != 0) 
			{
				cout << i << " csomopontba: ";
				for (int j = ut[i][0]; j >= 1; j--)
				{
					cout << ut[i][j] << " ";
				}
				cout << i << endl;
			}

		}
		cout << endl;

		for (int i = 1; i <= numberofvertices; i++)
		{
			for (int j = 1; j <= numberofvertices; j++)
			{
				ut[i][j] = INT_MAX / 2;
				akt[i] = -1;

			}
		}


	}
};


class DijkstraShortesPath
{
	bool settled[20];
	bool unsettled[20];
	int *distances;
	int adjacencymatrix[20][20];
	int numberofvertices;
	
	int d[20];
	int elozo[20];
	bool L[20];

public:
	const int MAX_VALUE = 999;


	DijkstraShortesPath(int numberofvertices)
	{
		this->numberofvertices = numberofvertices;
	}

	~DijkstraShortesPath()
	{
		delete[] distances;
	}

	void dijkstraShortestPath(int source, int adj[][20])
	{
		int evaluationnode;
		distances = new int[numberofvertices + 1];

		for (int vertex = 1; vertex <= numberofvertices; vertex++)
		{
			distances[vertex] = MAX_VALUE;
		}

		for (int sourcevertex = 1; sourcevertex <= numberofvertices; sourcevertex++)
		{
			for (int destinationvertex = 1; destinationvertex <= numberofvertices; destinationvertex++)
			{
				adjacencymatrix[sourcevertex][destinationvertex] = adj[sourcevertex][destinationvertex];
			}
		}

		unsettled[source] = true;
		distances[source] = 0;

		while (getUnsettledCount(unsettled) != 0)
		{
			evaluationnode = getNodeWithMinimumDistanceFromUnsettled(unsettled);
			unsettled[evaluationnode] = false;
			settled[evaluationnode] = true;
			evaluateNeighbours(evaluationnode);
		}

	}

	int getUnsettledCount(bool unsettled[20])
	{
		int count = 0;
		for (int vertex = 1; vertex <= numberofvertices; vertex++)
		{
			if (unsettled[vertex] == true)
			{
				count++;
			}
		}
		return count;
	}

	int getNodeWithMinimumDistanceFromUnsettled(bool unsettled[20])
	{
		int min = MAX_VALUE;
		int node = 0;
		for (int vertex = 1; vertex <= numberofvertices; vertex++)
		{
			if (unsettled[vertex] == true && distances[vertex] < min)
			{
				node = vertex;
				min = distances[vertex];
			}
		}
		return node;
	}

	void evaluateNeighbours(int evaluationNode)
	{
		int edgeDistance = -1;
		int newDistance = -1;

		for (int destinationNode = 1; destinationNode <= numberofvertices; destinationNode++)
		{
			if (settled[destinationNode] == false)
			{
				if (adjacencymatrix[evaluationNode][destinationNode] != MAX_VALUE)
				{
					edgeDistance = adjacencymatrix[evaluationNode][destinationNode];
					newDistance = distances[evaluationNode] + edgeDistance;
					if (newDistance < distances[destinationNode])
					{
						distances[destinationNode] = newDistance;
					}
					unsettled[destinationNode] = true;
				}
			}
		}
	}

	int d_min(int & i)
	{
		int min;

		min = INT_MAX/2;
		for (int j = 1; j <= numberofvertices; j++) 
		{
			if (L[j]) 
			{                   
				if (d[j] < min) 
				{
					min = d[j];
					i = j;
				}
			}
		}
		return min;
	}

	void dijkstraUt(int adj[][20],int kezdopont)
	{
		for (int i = 1; i <= numberofvertices; i++) 
		{
			d[i] = adj[kezdopont][i];            
			L[i] = true;
			elozo[i] = kezdopont;
		}

		d[kezdopont] = 0;
		L[kezdopont] = false;            

		int i, dd;
		while (d_min(i) < INT_MAX/2)
		{
			L[i] = false;                          
			   for (int j = 1; j <= numberofvertices; j++)
				{
					if (L[j] && adj[i][j] < INT_MAX/2)
					{
						dd = d[i] + adj[i][j];        
						if (dd < d[j])						
						{
							d[j] = dd;
							elozo[j] = i;                    
						}
					}
				}
			}
	}

	void dijkstraUtKiir(int i, int kp)
	{

		if (i != kp)
			dijkstraUtKiir(elozo[i], kp);
		cout << i << " ";
	}

	int* getDistances()
	{

		for (int i = 1; i <= numberofvertices; i++)
		{
			settled[i] = false;
			unsettled[i] = true;
		}
		return distances;
	}
};

class JohnsonsAlgorithm
{
	int SOURCE_NODE;
	int numberOfNodes;
	int augmentedMatrix[20][20];
	int *potential;
	int allPairShortestPath[20][20];

public:
	const int MAX_VALUE = 999;

	JohnsonsAlgorithm(int nrNodes)
	{
		numberOfNodes = nrNodes;
		SOURCE_NODE = nrNodes + 1;
		potential = new int[nrNodes + 2];

		for (int i = 1; i <= SOURCE_NODE; i++)
		{
			for (int j = 1; j <= SOURCE_NODE; j++)
			{
				augmentedMatrix[i][j] = MAX_VALUE;
			}
		}
		augmentedMatrix[SOURCE_NODE][SOURCE_NODE] = 0;
	}


	void johnsonsAlgorithms(int adjacencyMatrix[20][20])
	{
		BellmanFord bellmanFord(numberOfNodes + 1);
		DijkstraShortesPath dijsktra(numberOfNodes);
		DijkstraShortesPath dijkstra2(numberOfNodes);



		computeAugmentedGraph(adjacencyMatrix);


		bellmanFord.BellmanFordEvaluation(SOURCE_NODE, augmentedMatrix);
		potential = bellmanFord.getDistances();
		//ok

		int reweightedGraph[20][20];
		reweightGraph(adjacencyMatrix, reweightedGraph);


		for (int source = 1; source <= numberOfNodes; source++)
		{
			dijsktra.dijkstraShortestPath(source, reweightedGraph);
			int* result = dijsktra.getDistances();

			for (int destination = 1; destination <= numberOfNodes; destination++)
			{
				allPairShortestPath[source][destination] = result[destination]
					+ potential[destination] - potential[source];
			}
		}


		for (int source = 1; source <= numberOfNodes; source++)
		{
			for (int destination = 1; destination <= numberOfNodes; destination++)
			{
				cout << allPairShortestPath[source][destination] << " ";
			}
			cout << endl;
		}
	}


	void computeAugmentedGraph(int adjacencyMatrix[20][20])
	{
		for (int source = 1; source <= numberOfNodes; source++)
		{
			for (int destination = 1; destination <= numberOfNodes; destination++)
			{
				augmentedMatrix[source][destination] = adjacencyMatrix[source][destination];
			}
		}

		for (int destination = 1; destination <= numberOfNodes; destination++)
		{
			augmentedMatrix[SOURCE_NODE][destination] = 0;
		}
	}

	void reweightGraph(int adjacencyMatrix[20][20], int result[20][20])
	{
		for (int source = 1; source <= numberOfNodes; source++)
		{
			for (int destination = 1; destination <= numberOfNodes; destination++)
			{
				result[source][destination] = adjacencyMatrix[source][destination]+ potential[source] - potential[destination];
			}
		}
	}
};



void beolvas(int &n, int &m, int adj[][20])
{
	ifstream file;
	file.open("graf.txt");


	if (file.is_open())
	{
		int kp, vp, suly;
		file >> n;

		for (int i = 1; i <= 19; i++)
		{
			for (int j = 1; j <= 19; j++)
			{
				adj[i][j] = 999;
			}
		}
		m = 0;
		while (file >> kp >> vp >> suly)
		{
			adj[kp][vp] = suly;
			m++;
		}
	}
}


int main()
{
	int n, m, adj[20][20];
	int *tav;
	int kezdopont, vegpont;

	beolvas(n, m, adj);
	cout << "Adja meg a kezdoponot" << endl;
	cin >> kezdopont;
	cout << "Adja meg a vegpontot" << endl;
	cin>> vegpont;

	
	cout << "BELLMANFORD" << endl;
	BellmanFord graf(n);

	graf.BellmanFordEvaluation(kezdopont, adj);
	graf.bellmanUtKiir(kezdopont);
	tav = graf.getDistances();

	cout << kezdopont << ". csomopont tavolsagi matrixa: ";
	for (int j = 1; j <= n; j++)
	{
		cout << tav[j] << " ";
	}
	cout << endl;

	cout << endl;
	cout << "DIJKSTRA" << endl<<endl;

	DijkstraShortesPath graf2(n);
	graf2.dijkstraShortestPath(kezdopont, adj);
	tav = graf2.getDistances();

	cout << "A " << kezdopont << "-bol a " << vegpont << "-ba az ut: ";
	graf2.dijkstraUt(adj, kezdopont);
	graf2.dijkstraUtKiir(vegpont, kezdopont);
	
	cout << endl;
	cout << "A " << kezdopont << " tavolsagi matrixa:";
	for (int i = 1; i <= n; i++)
	{
		cout << tav[i] << " ";
	}
	cout << endl << endl;

	
	cout << "JOHNSON" << endl;
	JohnsonsAlgorithm g3(n);
	g3.johnsonsAlgorithms(adj);

	system("pause");
	return 0;
}