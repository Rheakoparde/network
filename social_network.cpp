#include "network.h"
#include "user.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;


int main(int argc, char *argv[])
{
	if(argc!=2){
		cout << "Enter correct number of arguments" << endl;
		return -1;
	}


	int menu;
	Network network;
	
	network.read_friends((argv[1]));
	//menu
		cout << "  " << "Menu" << endl;
		cout << "Add user: enter 1 and user's full name, birthday, and zipcode " << endl;
		cout << "Add friend connection: enter 2 and names of two people" << endl;
		cout << "Remove friend connection: enter 3 and names of two people" << endl;
		cout << "Print users: enter 4" << endl;
		cout << "List friends: enter 5 and name of user" << endl;
		cout << "Write to file: enter 6" << endl;
		cout << "Print relationship distance: enter 7 and names of two people" << endl;
		cout << "Print disjointed sets: enter 8" << endl;
		cout << "Friends suggestions: enter 9 and name of user" << endl;
		cout << "Enter invalid option to exit" << endl;


	while(cin >> menu && menu<=9){
		int yr, zipcode;
		string username;
		string firstName;
		string secondName;
		string first1;
		string last1;
		string first2;
		string last2;


		if(menu==1){ //add user
			cin >> first1 >> last1;
			username=first1 + " " + last1;
			cin >> yr;
			cin >> zipcode;
			network.add_user(username, yr, zipcode);

		}
		else if(menu==2){ //add friend
			cin >> first1 >> last1;
			firstName=first1 + " " + last1;
			cin >> first2 >> last2;
			secondName=first2 + " " + last2;
			if(network.add_connection(firstName, secondName)==-1){
				cout << "User does not exist" << endl;
			}
		}
		else if(menu==3){ //remove friend
			cin >> first1 >> last1;
			firstName=first1 + " " + last1;
			cin >> first2 >> last2;
			secondName=first2 + " " + last2;
			if(network.remove_connection(firstName, secondName)==-1){
				cout << "User does not exist" << endl;
			}
		}
		else if(menu==4){ //print network
			cout << "ID" << setw(15) << "Name" << setw(15) 
			<< "Year" << setw(10) << "Zip" << endl;
			cout << "======================================";
			cout << "========================================" << endl;
			network.printNetwork();		
		}
		else if(menu==5){ //print friends
			string friendOfUser1;
			string friendOfUser2;
			string totalfriends;
			cin >> friendOfUser1 >> friendOfUser2;
			totalfriends = friendOfUser1 + " " + friendOfUser2;
			network.printfriends(totalfriends);
			
		}
		else if(menu==6){ //write to file
			string file;
			cin >> file;
			const char* output = file.c_str();
			network.write_friends(output);
			
		}
		else if(menu==7){//print relationship of 2 users
			int from;
			int to;
			cin >> first1 >> last1;
			firstName=first1 + " " + last1;
			cin >> first2 >> last2;
			secondName=first2 + " " + last2;
			from=network.get_id(firstName);
			to=network.get_id(secondName);
			vector<int> path = network.shortest_path(from, to);
			if(!path.empty()){
				cout << "Distance: " << path.size()-1 << endl;
				network.printBfs(from, to);
				
			}
			else{
				cout << "None" << endl;
			}

		}

		else if(menu==8){//disjoint sets

			network.printGroups();
		}

		else if(menu==9){ //print suggested friends
			cin >> first1 >> last1;
			username=first1 + " " + last1;
			int idSuggest= network.get_id(username);
			int score=0;
			cout << "The suggested friend(s) is/are: " << endl;
			network.printFriendSuggestions(idSuggest, score);

		}

		else{
			break;
		}
	}

  return 0;
}
