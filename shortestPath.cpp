/*Shivam Swarnkar
HW09
*/
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<list>
#include<fstream>
#include <list>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;


// Code from Lisa Hellerstein.
// This is a bare-bones implementation of the single-source unweighted
// shortest paths algorithm 
// It does not have nice classes.

// Assumption: The vertices of the graph are labeled from 0 to n - 1,
// where n is the number of vertices.

const int DEFAULT_VAL = -1;      // must be less than 0
const string DEFAULT_ID = "NONE";
typedef unordered_map<string, list<string>> Graph;        // The graph is given in an adjacency list.
										 // Vertices are indexed from 0 to V-1
										 // The indices of the vertices adjacent to vertex i
										 // are in the list Graph[i].
										 // Graph can be directed or undirected.

struct vertexInf                    // Stores information for a vertex
{
	vertexInf(int dist = DEFAULT_VAL, const string& prev = DEFAULT_ID) :dist(dist), prev(prev){}
	int dist;  // distance to vertex from the source
	string prev;  // previous node in BFS tree
};

void printpath(const string& s, const string& e,  unordered_map<string, vertexInf>& vertices)
{
	vertexInf back = vertices[e];
	stack<string>path;
	while (back.prev != DEFAULT_ID) {
		path.push(back.prev);
		back = vertices[back.prev];
	}
	if (path.size() > 1) {
		while (!path.empty()) {
			string top = path.top();
			cout << top << "-> ";
			path.pop();
		}
		cout << e << endl;
	}
	else {
		cout << "NO PATH!!" << endl;
	}
}



void shortestpaths(const Graph & g, const string& s, const string& e)
{
	queue<string> q;             // q is the queue of vertex numbers
	Graph::const_iterator itr = g.find(s);
	if (itr == g.end())
	{
		cout << "NO DATA FOR " << s << " STATION" << endl;
		return;
	}

	unordered_map<string, vertexInf> vertices;               // stores BFS info for the vertices
	for (; itr != g.end(); ++itr)                 // Initialize distances and prev values
	{
		if (itr->first == s) {
			vertices[itr->first] = vertexInf(0);
		}
		else {
			vertices[itr->first] = vertexInf();
		}
	}


	q.push(s);
	unordered_map<string, vertexInf>::iterator curr;
	while (!q.empty())
	{
		string v = q.front();
		q.pop();
		for (list<string>::const_iterator w = g.at(v).begin(); w != g.at(v).end(); w++)
		{
			if (vertices[*w].dist == DEFAULT_VAL)          // distance of *w from source not determined yet
			{
				vertices[*w].dist = vertices[v].dist + 1;
				vertices[*w].prev = v;
				q.push(*w);
			}
		}
	}
	printpath(s, e, vertices);

}



void adjTable(unordered_map<string, list<string>>& map) {

	ifstream ifs("transfers.txt");
	if (!ifs) { cerr << "File Does not Exist\n"; exit(0); }
	string origin, destination, type, time;
	while (getline(ifs, origin, ',') && getline(ifs, destination, ',') && getline(ifs, type, ',') && getline(ifs, time, '\n')) {
		map[origin].push_front(destination);
	}
}
void print(const unordered_map<string, list<string>>& map) {
	for (unordered_map<string, list<string>>::const_iterator itr = map.begin(); itr != map.end(); ++itr) {
		cout << itr->first;
		for (list<string>::const_iterator lstItr = itr->second.begin(); lstItr != itr->second.end(); ++lstItr) {
			cout << "-->"<< *lstItr;
		}
	
	}
}





void solution() {
	unordered_map<string, list<string>>map;
	adjTable(map);

	shortestpaths(map, "112", "A24");
	
}



int main() {
	solution();
}