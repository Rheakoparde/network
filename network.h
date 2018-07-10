#ifndef NETWORK_H
#define NETWORK_H
#include <string>
#include "user.h"
#include <vector>
#include <fstream>



class Network {
 public:
  Network();
  ~Network();
  int read_friends(const char *filename);
  int write_friends(const char *filename);
  void add_user(std::string username, int yr, int zipcode);
  int add_connection(std::string firstName, std::string secondName);
  int remove_connection(std::string firstName, std::string secondName);
  int get_id(std::string username);
  void printfriends(std::string username);
  void printNetwork();
  std::vector<int> shortest_path(int from, int to);
  std::vector<std::vector<int> > groups();
  std::vector<int> suggest_friends(int who, int& score); 
  void printBfs(int from, int to);
  void printGroups();
  void printFriendSuggestions(int who, int& score);

 private:
 	std::vector<User> users; //for user info

  
};


#endif
