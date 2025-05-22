#pragma once
#include <iostream>

using namespace std;

class User {
private:
	string ID;
	string passWord;
	string phoneNumber;
	char userType;
	RentedBikeCollection* ownedRentedBikeCollection;
public:
	string getPassword();
	RentedBikeCollection* getUserBikes();
	bool isAdmin();
	bool isMember();
};

class UserCollection {
private:
	User* userList[50];
	int numUsers;
public:
	void addNewUser();
	User* getUserByID(string id);
};

class Bike {
private:
	string bikeID;
	string bikeProductName;
public:
	string getBikeDetails();
};

class BikeCollection {
private:
	Bike* bikeList[50];
	int numBikes;
public:
	void addNewBike();
	Bike* getBikeByID(string bikeID);
};

class RentedBikeCollection {
private:
	Bike* ownedRentedBike[50];
public:
	void addNewBike();
};

class AccessManager {
private:
	User* currentUser;
public:
	void connect();
	void disconnect();
	User* getCurrentUser();
};


class SignUpUI {
public:
	void startInterface();
	void createNewUser();
};

class SignUp {
public:
	void addNewUser();
};

class LoginUI{
public:
	void startInterface();
	void clickLogin();
};

class Login {
public:
	void checkValid();
	bool isEqual();
};

class LogoutUI {
public:
	void startInterface();
	void clickLogout();
};

class Logout {
public:
	void exitSystemAccess();
};

class RegisterBikeUI {
public:
	void startInterface();
	void registerNewBike();
};

class RegisterBike {
public:
	void createNewBike();
};

class RentBikeUI {
public:
	void startInterface();
	void rentBike();

};

class RentBike {
public:
	void addNewBike();
};

class CheckBikeRentalInformationUI {
public:
	void startInterface();
	void checkBikeRentalInformation();
};

class CheckBikeRentalInformation {
public:
	void showBikeRentalInformation();
};