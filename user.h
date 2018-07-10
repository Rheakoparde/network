#ifndef USER_H
#define USER_H
#include <vector>
#include <string>




class User {
 public:
 	User(std::string user, int birthday, int zipcode, int ID);
 	User();
 	~User();
 	void add_friend(int friendId);
 	void delete_friend(int friendId);
 	std::string getname() const;
 	int getyear() const;
 	int getzip() const;
 	int getuserId() const;
 	std::vector<int> getfriends();
 	void ifFriends(int friendId);
 	void ifNotFriends(int friendId);
 	int depth;
 	int predecessor;
 	int suggestion_score;


 private:
 	std::string name;
 	int year;
 	int zip;
 	int userId;
 	std::vector<int> id; //for id of friends

};


#endif
