#include <iostream> // cout

#include "../headers/StoreUsers.h"

// Constructor.
// TODO: CREATE AS SINGLETON.
StoreUsers::StoreUsers(){
	
	for (int i = 0; i < MAX_TABLE; ++i)
	{
		this->users[i] = new std::set<User*,User> ;
	}

	this->nUsers = 0;
}


StoreUsers::~StoreUsers()
{

	// For every position of the table.
	for (int i = 0; i < MAX_TABLE; ++i)
	{
		// Retrieve the set of users.
		std::set<User*,User>* users =  this->users[i];
		std::set<User*,User>::iterator it ;

		// For every user in the set.
		for (it = users->begin(); it!=users->end(); ++it){
			// Clean the list of friends.
			(*it)->getFriends()->clear();
			// Delete the memory allocated with new 
			// when we create the list of friends.
			delete (*it)->getFriends();
			// Call the destructor of user.
			delete (*it);
		}

		// Delete the std::set allocated in the constructor.
		delete this->users[i];  	
	}
}


std::set<User*,User>** StoreUsers::getUsers()
{
	return this->users;
}

long int StoreUsers::bucketSize(std::string name)
{
	
	int long hash = this->hash(name);
	
	// Retrieve the set in the position "hash".
	std::set<User*,User>* bucket = this->users[hash];

	return bucket->size();
}

long int StoreUsers::getNUsers()
{
	return this->nUsers;
}

// Add one in the users counter.
void StoreUsers::setNUsers()
{
	this->nUsers++;
}

// Hash function for calculate an integer from
// string doing use of the ascii code of the string.
long int StoreUsers::hash(std::string name)
{
	int addAscii = 0;
	int nameLength = name.length();

	// Iterate over the string.
	for (int i=0; i<nameLength;i++){
		// 37 is prime
		addAscii = (addAscii * 37 + name[i]);
	}
	// Adjust to the size of the table.
	addAscii = addAscii % MAX_TABLE;
	
	if (addAscii < 0) 
		addAscii = addAscii + MAX_TABLE;

	return addAscii ;
}	


// Insert an user.
void StoreUsers::insert(User* &user)
{

	std::string name = user->getName();
	
	int long hash = this->hash(name);

	// Retrieve the set in the position "hash".	
	std::set<User*,User>* bucket = this->users[hash];
	
	bucket->insert(user);

}

// Insert an friends.
void StoreUsers::insert(User* &user,User* &_friend)
{
	user->insert(_friend);
}    

// Find an user by name return NULL if the User is not found.
User* StoreUsers::find(std::string name)
{
	User user(name);

	int long hash = this->hash(name);

	// Retrieve the set in the position "hash".
	std::set<User*,User>* bucket = this->users[hash];

	std::set<User*,User>::iterator result = bucket->find(&user);
	
	// If the user is not found.
	if (result == bucket->end())
		return NULL;

	// If the user is found.
	User* userPointer = *result;

	return userPointer;

}

// Return the list of friends of a User by name.
std::set<User*,User>* StoreUsers::findFriends(std::string name)
{
	User* user = this->find(name);

	return user->getFriends();
}



// Print all attributes of the User.
std::string StoreUsers::toString()
{
	
	std::set<User*,User>* users;
	std::set<User*,User>::iterator it;

	std::string out = "";
	for (int i = 0; i < MAX_TABLE; ++i)
	{
		users = this->users[i];
	
		for( it = users->begin(); it!=users->end(); ++it) {
				out += "User :";
				out += (*it)->toString();	
			}  	
	}
	
	return out;
	
}



