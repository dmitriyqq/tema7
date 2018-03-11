#include <bits/stdc++.h>

using namespace std;

int scan(ifstream in, vector <string>& vec){
	while(in.good()){
		string s;
		getline(in, s);
		if(s.length())
			vec.push_back(s);
	}
}

string r(vector <string> & vec){
	if(vec.size())
		return vec[rand()%(vec.size())];
}

int main(){
	srand(time(0));
	vector <string> deps;
	vector <string> pos;
	vector <string> spec;
	vector <string> eds;
	vector <string> firstnames;
	vector <string> lastnames;
	vector <string> middlenames;



	scan(ifstream("deps.txt"), deps);
	scan(ifstream("pos.txt") , pos);
	scan(ifstream("spec.txt"), spec);
	scan(ifstream("eds.txt"), eds);
	scan(ifstream("firstnames.txt"), firstnames);
	scan(ifstream("lastnames.txt"), lastnames);
	scan(ifstream("middlenames.txt"), middlenames);


	cout<<"deps"<<endl;
	for(auto e: deps){
		cout<<e<<endl;
	}
	cout<<"poss"<<endl;
	for(auto e: pos){
		cout<<e<<endl;
	}
	cout<<"specs"<<endl;
	for(auto e: spec){
		cout<<e<<endl;
	}
	cout<<"eds"<<endl;
	for(auto e: eds){
		cout<<e<<endl;
	}
	cout<<"first"<<endl;
	for(auto e: firstnames){
		cout<<e<<endl;
	}
	cout<<"last"<<endl;
	for(auto e: lastnames){
		cout<<e<<endl;
	}
	cout<<"middle"<<endl;
	for(auto e: middlenames){
		cout<<e<<endl;
	}

	for(int i = 0; i < 500; i++){
	string query ="./7 \"" + r(deps) + "\" ";
	query += "\"" + r(pos) + "\" ";
	query += "\"" + to_string((rand()%1000000)/(1+rand()%50)) + "\" ";
	bool isfree = rand()%2;
	query += "\"" + to_string((int)isfree) + "\" ";
	query += "\"" + r(firstnames) + "\" ";
	query += "\"" + r(middlenames) + "\" ";
	query += "\"" + r(lastnames) + "\" ";
	query += "\"" + r(spec) + "\" ";
	query += "\"" + r(eds) + "\" ";
		query += "\"" + to_string(rand()%25) + "\" ";

//		cout<<query<<endl;
		system(query.c_str());
	}
}
