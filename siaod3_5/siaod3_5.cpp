#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

struct Graph {
private:
	vector<vector<int>> connections;
public:
	void resizeConnections() {
		vector<int> vectConnections;
		this->connections.push_back(vectConnections);
		int size = connections.size();
		for (int i = 0; i < size; i++) {
			while (connections.at(i).size() != size)
				connections.at(i).push_back(0);
		}
	}
	void addNode() {
		this->resizeConnections();
	}
	void addConnection(int first, int second, int distance) {
		connections[first - 1][second - 1] = distance;
		connections[second - 1][first - 1] = distance;
	}
	int maxDistance() {
		int maxS = -10100;
		int size = connections.size();
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				if (connections[i][j] > maxS)
					maxS = connections[i][j];
		return maxS;
	}
	void graphTable() {
		cout << "\n\n";
		int size = connections.size();
		int tab = max(to_string(connections.size()).length(), to_string(this->maxDistance()).length());
		int digTab = to_string(connections.size()).length();
		cout << left << "\t#"; 
		for (int i = 0; i < digTab-1; i++)
			cout << " ";
		cout << "| ";
		cout.flags(ios::left);
		for (int i = 0; i < size; i++) {
			cout << setw(tab + 1) << i + 1;
		}
		cout << endl;
		for (int i = 0; i < size; i++) {
			cout << "\t" << i + 1;
			for (int j = 0; j < digTab - 1; j++) {
				if (i < 9)
					cout << " ";
			}
			cout << "| ";
			for (int j = 0; j < size; j++) {
				cout << setw(tab + 1) << connections.at(i).at(j);
			}
			cout << "\n";
		}
	}
	void randomizeGraph(int graphSize) {
		for (int i = 0; i < graphSize; i++)
			this->addNode();
		for (int i = 0; i < graphSize; i++) {
			for (int z = 0; z < rand() % graphSize; z++) {
				int j = (i + 1 + rand()) % graphSize;
				if (i != j and connections[i][j] == 0)
					this->addConnection(i + 1, j + 1, rand() % 9999);
			}
		}
	}

	int findShortestWay(int begin, int end) {
		cout << setw(connections.size()) << "\tTask: find shortest way between " << min(begin, end) << " and " << max(begin, end) << " nodes" << endl;
		begin--;
		end--;
		if (begin < 0)
			return 0;
		int minindex, minN, temp;
		int size = connections.size();
		int* d = new int[size];
		int* v = new int[size];
		for (int i = 0; i < size; i++) {
			d[i] = numeric_limits<int>::max();
			v[i] = 1;
		}
		d[begin] = 0;
		do {
			minindex = numeric_limits<int>::max();
			minN = numeric_limits<int>::max();
			for (int i = 0; i < size; ++i) {
				if (v[i] == 1 and d[i] < minN) {
					minN = d[i];
					minindex = i;
				}
			}
			if (minindex != numeric_limits<int>::max()) {
				for (int i = 0; i < size; ++i) {
					if (connections[minindex][i] > 0) {
						if (minN + connections[minindex][i] < d[i])
							d[i] = minN + connections[minindex][i];
					}
				}
				v[minindex] = 0;
			}
		} while (minindex < numeric_limits<int>::max());

		if (d[end] == numeric_limits<int>::max()) {
			cout << "\tThere's no way between " << min(begin+1, end+1) << " and " << max(begin+1, end+1) << " nodes" << endl;
			return 0;
		}

		cout << "\tShortest way length: " << d[end] << endl;

		int* ver = new int[size](); // массив посещенных вершин
		ver[0] = end + 1; 
		int k = 1; 
		int weight = d[end]; 

		while (end != begin) {
			for (int i = 0; i < size; i++) 
				if (connections[i][end] != 0) {
					int temp = weight - connections[i][end]; // определяем вес пути
					if (temp == d[i]) {
						weight = temp; // сохраняем новый вес
						end = i;       // сохраняем предыдущую вершину
						ver[k] = i + 1; 
						k++;
					}
				}
		}

		cout << "\tShortest way: ";

		for (int i = k - 1; i >= 0; i--) {
			cout << ver[i];
			if (i != 0)
				cout << "-";
		}
		return 0;
		}
	};

void randomTask(Graph* _graph) {
	int graphSize = 2 + rand() % 25;
	int first, second;
	first = 1 + rand() % (graphSize);
	do {
		second = 1 + rand() % (graphSize);
	} while (first == second);

	_graph->randomizeGraph(graphSize);
	_graph->graphTable();

	cout << "\n";

	_graph->findShortestWay(first, second);
}

void exampleTask(Graph* _graph) {
	for (int i = 0; i < 6; i++)
		_graph->addNode();

	_graph->addConnection(1, 2, 8);
	_graph->addConnection(1, 3, 4);
	_graph->addConnection(2, 4, 6);
	_graph->addConnection(2, 5, 3);
	_graph->addConnection(3, 2, 3);
	_graph->addConnection(3, 4, 2);
	_graph->addConnection(3, 6, 10);
	_graph->addConnection(4, 5, 3);
	_graph->addConnection(4, 6, 1);
	_graph->addConnection(5, 6, 4);

	_graph->graphTable();
	cout << "\n";
	_graph->findShortestWay(1, 6);
}

void userTask(Graph* _graph) {
	cout << "Input size:\nSIZE = ";
	int size = 0;
	cin >> size;
	for (int i = 0; i < size; i++)
		_graph->addNode();
	cout << "Input distance between nodes (0 if don't exist):\n";
	int distance = 0, start = 0,  end = 0;
	for (int i = 0; i < size; i++) {
		for (int j = i+1; j < size; j++) {
			cout << i+1 << "-" << j+1 << ": ";
			cin >> distance;
			_graph->addConnection(i+1, j+1, distance);
		}
	}
	cout << "START = ";
	cin >> start;
	cout << "END = ";
	cin >> end;
	_graph->graphTable();
	_graph->findShortestWay(start, end);
}

int main() {
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	Graph* graph = new Graph();
	int n = -1;

	while (n < 0 or n > 3) {
		cout << "Choose way to create your graph:\n" 
			<< "1) Randomize graph (random size, start and end values)\n"
			<< "2) Use graph from task example\n"
			<< "3) Input graph from keyboard\n";
		cin >> n;

		switch (n) {
		case 1:
			randomTask(graph);
			break;
		case 2:
			exampleTask(graph);
			break;
		case 3:
			userTask(graph);
			break;
		case 0:
			cout << "End of the program..." << endl;
			break;
		default:
			cout << "Error. Try to input digit from [1, 3]\n";
			break;
		}
	}

	cout << "\n\n";

	return EXIT_SUCCESS;
}