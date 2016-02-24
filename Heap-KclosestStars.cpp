#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<queue>
#include<array>
#include<string>
#include<functional> //for greater<T>
using namespace std;


class star{
public:
	int x, y, z;
	double dist;
	string id;
	star(){}
	star(string i, int a, int b, int c) :id(i), x(a), y(b), z(c), dist(sqrt(x*x + y*y + z*z)){}
	const bool operator<(star other) const{ return dist<other.dist; }
	const bool operator>(star other) const{ return dist>other.dist; }

};
vector<star> kFarthestStars(ifstream &ifile, int k, vector<star> &actual){
	priority_queue<star, vector<star>, greater<star>> min_heap;
	string line;

	while (getline(ifile, line)){
		stringstream ss(line);
		string buf;
		getline(ss, buf, ',');//copy id
		string id = buf;
		array<int, 3> pos;
		for (int i = 0; i<3; ++i){
			getline(ss, buf, ',');
			pos[i] = stoi(buf);
		}
		star s(id, pos[0], pos[1], pos[2]);
		actual.push_back(s);
		if (min_heap.size() == k){
			if (s>min_heap.top()){
				min_heap.pop();
				min_heap.push(s);
			}
		}
		else
			min_heap.push(s);
	}
	vector<star> res;
	while (min_heap.size()){
		res.push_back(min_heap.top());
		min_heap.pop();
	}
	return res;
}
vector<star> kClosestStars(ifstream &ifile, int k,vector<star> &actual){
	priority_queue<star, vector<star>> max_heap;
	string line;
	
	while (getline(ifile, line)){
		stringstream ss(line);
		string buf;
		getline(ss, buf, ',');//copy id
		string id = buf;
		array<int,3> pos;
		for (int i = 0; i<3; ++i){
			getline(ss, buf, ',');
			pos[i] = stoi(buf);
		}
		star s(id, pos[0], pos[1], pos[2]);
		actual.push_back(s);
		if (max_heap.size() == k){
			if (s<max_heap.top()){
				max_heap.pop();
				max_heap.push(s);
			}
		}
		else
			max_heap.push(s);
	}
	vector<star> res;
	while (max_heap.size()){
		res.push_back(max_heap.top());
		max_heap.pop();
	}
	return res;
}
int main(void){
	ifstream ipfile("data.txt");
	vector<star> act;
	vector<star> res = kClosestStars(ipfile, 3,act);
	for (int i = 0; i<res.size(); ++i)
		cout << "Id:" << res[i].id << " x:" << res[i].x << " y:" << res[i].y << " z:" << res[i].z << "Dist: "<<res[i].dist<< endl;
	cout << endl << endl;
	for (int i = 0; i<act.size(); ++i)
		cout << "Id:" << act[i].id << " x:" << act[i].x << " y:" << act[i].y << " z:" << act[i].z << "Dist: " << act[i].dist << endl;
	ipfile.close();
	ipfile.open("data.txt");
	
	cout << endl << endl;
	res = kFarthestStars(ipfile, 3, act);
	for (int i = 0; i<res.size(); ++i)
		cout << "Id:" << res[i].id << " x:" << res[i].x << " y:" << res[i].y << " z:" << res[i].z << "Dist: " << res[i].dist << endl;
	cout << endl << endl;
	
	int in;
	cin >> in;
	return 0;
}