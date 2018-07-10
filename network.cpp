#include <iostream>
#include <vector>
#include "network.h"
#include <fstream>
#include <sstream>
#include <string>
#include "user.h"
#include <iomanip>
#include <deque>

using namespace std;

Network::Network(){

}

Network::~Network(){

}

int Network::read_friends(const char* filename){ 
	//read friends from a file
	ifstream ifile(filename);
	if(ifile.fail()){
		cout << "Couldn't read in file";
		return -1;
	}

	else{

		int total;
		int ID;
		string firstname;
		string secondName;
		string name;
		string friends;
		int num;
		int zipcode;
		int birthday;
		ifile >> total;
	
		for(int i=0; i<total; i++){
			ifile >> ID;
			
			string x;
			getline(ifile, x);
			getline(ifile, name);
			stringstream s(name);
			s>>firstname;
			s>>secondName;
			name=firstname+" "+secondName;
			
			ifile >> birthday >> zipcode;
			
			getline(ifile, x);
			User newUser(name, birthday, zipcode, ID);

			stringstream ss;
			getline(ifile, friends);
			ss << friends;
			while(ss >> num){
				newUser.add_friend(num);
			}
			users.push_back(newUser);
		}

		return 0;
	}
}

int Network::write_friends(const char* filename){
	//write friends out to file
	ofstream userfile(filename);
	vector<int> newvec;
	if(userfile.fail()){
		cout << "Couldn't create file" << endl;
		return -1;
	}
	else{
		
		userfile << users.size() << endl;
		for(int i=0; i<users.size(); i++){

			userfile << users[i].getuserId() << endl;
			userfile << '\t' << users[i].getname() << endl;
			userfile << '\t' << users[i].getyear() << endl;
			userfile << '\t' << users[i].getzip() << endl;

			newvec=users[i].getfriends();
			userfile << '\t' ;
			for(int j=0; j<newvec.size(); j++){
				userfile << newvec[j] << ' ';
			}
			
			userfile << endl;
		}

	return 0;	
	}

	

}


void Network::add_user(string username, int yr, int zipcode){
	int total=users.size(); //adds a new id for user
	int id = total;
	User adduser(username, yr, zipcode, id); //adds user info in vector
	users.push_back(adduser);
	
}

int Network::add_connection(string firstName, string secondName){
	bool name1=false;
	bool name2=false;
	int id1;
	int id2;
	//checks if users exist
	for(int i=0; i<users.size(); i++){
		if(users[i].getname()==firstName){
			name1=true;
			id1=i;
		}
		if(users[i].getname()==secondName){
			name2=true;
			id2=i;
		}
		
	}	
	//if users don't exist
	if(name1!=true || name2!=true){
		return -1;
	}
	
	users[id1].ifFriends(id2);
	users[id1].add_friend(id2);
	users[id2].add_friend(id1);
	
		
	return 0;
		

		
	
}		


int Network::remove_connection(string firstName, string secondName){
	//similar to add connection 
	bool name1=false;
	bool name2=false;
	int id1;
	int id2;
	for(int i=0; i<users.size(); i++){
		if(users[i].getname()==firstName){
			name1=true;
			id1=i;
		}
		if(users[i].getname()==secondName){
			name2=true;
			id2=i;
		}
		
	}
	if(name1!=true || name2!=true){
		return -1;
	}

	users[id1].ifNotFriends(id2);
	users[id1].delete_friend(id2);
	users[id2].delete_friend(id1);
	
			
	return 0;
		
	

}


int Network::get_id(string username){
	//returns id for user
	for(int i=0; i<users.size(); i++){
		if(users[i].getname()==username){
			return users[i].getuserId();
		}
		
	}
	return -1;
}


void Network::printfriends(string username){
	//prints all friends of user and their info
	bool name;
	int friendid=0;
	User friendconnections;
	// checks if user exists
	for(int i=0; i<users.size(); i++){
		if(users[i].getname()==username){
			name=true;
			friendid=i;
		}

	}
	if(name==false){
		cout << "User doesn't exist" << endl;
	}

	else{ 
		cout << "ID" << setw(15) << "Name" << setw(15) 
			<< "Year" << setw(8) << "Zip" << endl;
		cout << "========================================";
		cout << "======================================" << endl;
		friendconnections=users[friendid];
		vector<int> myvec(friendconnections.getfriends());
		for(int i=0; i<myvec.size(); i++){
				cout << users[myvec[i]].getuserId() << '.'
				 << setw(20) << users[myvec[i]].getname() << setw(10)
				 << users[myvec[i]].getyear() << setw(10) 
				 << users[myvec[i]].getzip() << endl;
			
		}
	}


}

void Network::printNetwork(){
//prints users and their info
	for(int i=0; i<users.size(); i++){
		cout << users[i].getuserId() << '.' << setw(20) 
		<< users[i].getname() << setw(10) 
		<< users[i].getyear() << setw(10)<< users[i].getzip() << endl;
	}
}


vector<int> Network::shortest_path(int from, int to){//bfs
	int start;
	int end;
	bool found1=false;
	bool found2=false;
	bool foundstart=false;
	for(int i=0; i<users.size(); i++){//check if both users are there
		if(users[i].getuserId()==from){
			start=i;
			found1=true;
		}
		if(users[i].getuserId()==to){
			end=i;
			found2=true;
		}
	}


	if(found1==true && found2==true){
		deque<int> list; //to hold users and their friends
		for(int j=0; j<users.size(); j++){
			users[j].depth=-1;
			
		}
		list.push_back(end);
		users[end].depth=0;
		while(!(list.empty())){ //bfs
			int idValue=list.front();
			vector<int> friends=users[idValue].getfriends();
			
			for(int s=0; s<friends.size(); s++){
				if(users[friends[s]].depth==-1){
					list.push_back(friends[s]);
					users[friends[s]].predecessor=idValue;
					users[friends[s]].depth=users[idValue].depth +1;
					if(users[friends[s]].getuserId()==start){
						foundstart=true;//if 2nd user is found
						break;
					}

				}

				
			}
			list.pop_front();
		}
	}
	

	if(foundstart==true || from==to){
		int predecessorID = start;
		vector <int> path;
		path.push_back(start);//start with 1st user
		while(users[predecessorID].depth !=0){
			predecessorID=users[predecessorID].predecessor;
			path.push_back(predecessorID);
		}
		return path;

	}
	else{
		
		return vector <int> ();
	}	

}

void Network::printBfs(int from, int to){//prints the vector
	vector <int> path = shortest_path(from, to);
	for(int i=0; i<path.size(); i++){
		cout << users[path[i]].getname();
		if(i!=path.size()-1){
			cout << " -> ";
		}
	}
	cout << endl;
}


vector<vector<int> > Network::groups(){
	vector<vector<int> > disjoint;//2d vector
	deque<int> list;
	
	int set=0;
	for(int i=0; i<users.size(); i++){
		users[i].depth=-1;
	
	}

	int count=0;//to count number of users
	while(users[set].depth==-1 && count<users.size()){ 
		vector<int> row;
		list.push_back(users[set].getuserId());
		users[set].depth=0;
		while(!list.empty()){	
			int idValue= list.front();
			row.push_back(idValue);
			vector<int> friends=users[idValue].getfriends();
			for(int s=0; s<friends.size(); s++){
				if(users[friends[s]].depth==-1){
					list.push_back(friends[s]);
					users[friends[s]].predecessor=idValue;
					users[friends[s]].depth=users[idValue].depth +1;
					count++;
				}	
			}

			list.pop_front();	
		}
		for(int r=0; r<users.size(); r++){
			//visits users that haven't been found yet
			if(users[r].depth==-1){
				set=r;
			}
		}
		
		disjoint.push_back(row);
		
	}
	return disjoint;

}

void Network::printGroups(){//prints the disjoint set
	vector<vector<int> > disjoint=groups();
		for(int i=0; i<disjoint.size(); i++){
			cout << "Set: " << i+1 << " => ";
			for(int j=0; j<disjoint[i].size(); j++){
				cout << users[disjoint[i][j]].getname() << " ";
			}
			cout << endl;
		}	
}

vector<int> Network::suggest_friends(int who, int& score){
	bool found=false;
	int user;
	for(int i=0; i<users.size(); i++){
		if(users[i].getuserId()==who){
			user=i;
			found=true;
		}
	}
	bool foundsugg=false;
	vector<int> friendSuggestions;//for friend suggestions
	if(found==true){
		//vector for the friends of chosen user
		vector<int> userVec= users[user].getfriends(); 
		deque <int> list;
		for(int j=0; j<users.size(); j++){
			users[j].depth=-1;
			users[j].suggestion_score=score;
		}
		list.push_back(user);
		users[user].depth=0;
		while(!(list.empty())){
			int idValue=list.front();
			vector<int> friends=users[idValue].getfriends();

			for(int s=0; s<friends.size(); s++){
				if(users[friends[s]].depth==-1){
					list.push_back(friends[s]);
					users[friends[s]].predecessor=idValue;
					users[friends[s]].depth=users[idValue].depth +1;
					
				}
			}
			list.pop_front();
		}
		for(int r=0; r<users.size(); r++){
			if(users[r].depth==2){
				foundsugg=true;//if there are suggested friends
				//friendSuggestions.push_back(users[r].getuserId());
				//vector for friends of user's suggested friends
				vector<int> friendsVec=users[r].getfriends();
				for(int q=0; q<userVec.size(); q++){
					for(int w=0; w<friendsVec.size(); w++){
						if(userVec[q]==friendsVec[w]){
							users[r].suggestion_score++;
						}
					}
				}
				if(users[r].suggestion_score>score){

					score=users[r].suggestion_score;
				}
			}						
		
		}

		for(int r=0; r<users.size(); r++){
			if(users[r].depth==2 && users[r].suggestion_score == score){

				friendSuggestions.push_back(users[r].getuserId());
				
			}
		}		
	}
	if(foundsugg==true){
		return friendSuggestions;
	}
	else{//empty vector
		return vector<int> ();
		}	
		
}

void Network::printFriendSuggestions(int who, int& score){//print friend suggestions
	
	vector<int> suggestions=suggest_friends(who, score);
	if(suggestions.size()!=0){
		for(int i=0; i<suggestions.size(); i++){
			cout << " " << users[suggestions[i]].getname() << " " << "Score: "
			 << users[suggestions[i]].suggestion_score << endl;
		}
	}
	else{
		score=-1;
		cout << "None" << endl;
	}
}

