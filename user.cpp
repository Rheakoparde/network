#include <iostream>
#include <vector>
#include "user.h"
#include <fstream>
#include <string>

using namespace std;

User::User(string user, int birthday, int zipcode, int ID){
	name=user;
	year=birthday;
	zip=zipcode;
	userId=ID;
}

User::User(){
	year=0;
	zip=0;
	userId=0;
}

User::~User(){

}
 	



void User::add_friend(int friendId){
	//checking if users are already friends
	bool found=false;
	for(int i=0; i<id.size(); i++){ 
		if(id[i]==friendId){
			found=true;
			break;
		}
	}

	if(!found){
		id.push_back(friendId);//if not friends add to vector
	}
		

}

void User:: ifFriends(int friendId){ //check if friends
	for(int i=0; i<id.size(); i++){ 
		if(id[i]==friendId){
			cout << "Already Friends" << endl;
		}
	}
	
		
		
}


void User::ifNotFriends(int friendId){ //check if not friends
	bool found=false;
	for(int i=0; i<id.size(); i++){ 
		if(id[i]==friendId){
			found=true;
		}
	}
	if(found!=false){
		cout << "Not currently friends" << endl;
	}

	
}


void User::delete_friend(int friendId){
	//checking if already friends
	bool found=false;
	for(int i=0; i<id.size(); i++){ 
		if(id[i]==friendId){
			found=true;
			break;
		}
	}

	if(found==true){ //if friends delete from vector
		id.erase(id.begin())+friendId;
	}
		

}

vector<int> User::getfriends(){ //returns user info
	return id;
}


string User::getname() const{
	return name;	
}


int User::getyear() const{
 	return year;
}

 	
 int User::getzip() const{
 	return zip;
 }

 
int User::getuserId() const{
	return userId;
}





