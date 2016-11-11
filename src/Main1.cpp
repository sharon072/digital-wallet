#include <stdio.h>  
#include <iostream>
#include <string>
#include <sstream>  
#include <fstream>
#include <map>
#include <math.h>
#include <thread>
#include <vector>
using namespace std;

//Feature 1
void feature1(map<int, map<int, bool>>& batch, int user1, int user2, string& result) {
	if (batch[user1][user2] == true) {
		result = "true";
	}
	return;
}

//Feature 2
void feature2DFS(map<int, map<int, bool>>& batch, int user1, int user2, int index, string& result) {
	if (index > 1) {
		return;
	}
	if (batch[user1][user2] == true) {
		result = "true";
		return;
	}
	else {
		for (map<int, bool>::iterator itr = batch[user1].begin(); itr != batch[user1].end(); itr++) {
			pair<int, bool> temp_user1 = *itr;
			feature2DFS(batch, temp_user1.first, user2, index + 1, result);
		}
	}
}

//Feature 3
void feature3DFS(map<int, map<int, bool>>& batch, int user1, int user2, int index, string& result) {
	if (index > 3) {
		return;
	}
	if (batch[user1][user2] == true) {
		result = "true";
		return;
	}
	else {
		for (map<int, bool>::iterator itr = batch[user1].begin(); itr != batch[user1].end(); itr++) {
			pair<int, bool> temp_user1 = *itr;
			feature3DFS(batch, temp_user1.first , user2, index + 1, result);
		}
	}
}

int main() {
	/////////////// STORE ALL PAST DATA FROM "batch_payment.csv"
	ifstream myfile;
	myfile.open("batch_payment.csv");
	//create the map to store all users with their friend list
	map<int, map<int, bool>> batch;
	//create the map to store friend list for each user

	string time;
	string id1;
	string id2;
	string amount;
	string msg;

	int counter = 0;
	if (myfile.is_open())
	{
		while (!myfile.fail())
		{

			// Set time
			getline(myfile, time, ',');

			// Set id1
			getline(myfile, id1, ',');
			int user1 = strtod(id1.c_str(), NULL);
			// Set id2
			getline(myfile, id2, ',');
			int user2 = strtod(id2.c_str(), NULL);
			getline(myfile, amount, ',');
			getline(myfile, msg, ',');
			//Populate the batch map
			//First, add/update user1 to batch map and add/update his friend list
			if (batch.find(user1) != batch.end()) {
				if (batch[user1].find(user2) == batch[user1].end()) {
					batch[user1].insert(pair<int, bool>(user2, true));
				}
			}
			else {
				map<int, bool> friends_list;
				friends_list.insert(pair<int, bool>(user2, true));
				batch[user1]=friends_list;
			}
			//Then, add/update user2 to batch map and add/update his friend list
			if (batch.find(user2) != batch.end()) {
				if (batch[user2].find(user1) == batch[user2].end()) {
					batch[user2].insert(pair<int, bool>(user1, true));
				}
			}
			else {
				map<int, bool> friends_list;
				friends_list.insert(pair<int, bool>(user1, true));
				batch[user2] = friends_list;
			}
			counter++;
		}
	}


	myfile.close();

	///////////////// VALIDATE ALL TRANSACTIONS IN "stream_payment.csv"
	ifstream myfile2;
	myfile2.open("stream_payment.csv");
	//create the map to store all users with their friend list
	vector<string> verify;
	//create the map to store friend list for each user

	string time2;
	string sid1;
	string sid2;
	string amount2;
	string msg2;

	int x;
	cout << "Which feature? (1, 2 or 3)" << endl;
	cin >> x;
	int counter1 = 0;
	if (myfile2.is_open())
	{
		while (!myfile2.fail())
		{
			cout << counter1++ << endl;
			// Set time
			getline(myfile2, time2, ',');

			// Set id1
			getline(myfile2, sid1, ',');
			int suser1 = strtod(sid1.c_str(), NULL);
			// Set id2
			getline(myfile2, sid2, ',');
			int suser2 = strtod(sid2.c_str(), NULL);
			getline(myfile2, amount2, ',');
			getline(myfile2, msg2, ',');

			string result = "false";

			//pick a feature here and run the corresponding function
			if (x == 1) {
				feature1(batch, suser1, suser2, result);
			}
			else if (x == 2) {
				feature2DFS(batch, suser1, suser2, 0, result);
			}
			else if (x == 3) {
				feature3DFS(batch, suser1, suser2, 0, result);
			}

			//stored all results into a vector
			if (result == "false") {
				verify.push_back("unverified");
			}
			else if (result == "true"){
				verify.push_back("trusted");
			}
		}
	}
	myfile2.close();
	

	ofstream fout;
	if (x == 1) {
		fout.open("output1.txt");
	}
	else if (x == 2) {
		fout.open("output2.txt");
	}
	else if (x == 3) {
		fout.open("output3.txt");
	}
	for (int i = 0; i < verify.size(); i++) {
		fout << verify[i] << endl;
	}
	fout.close();
}

