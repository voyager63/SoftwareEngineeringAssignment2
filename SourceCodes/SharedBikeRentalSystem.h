#pragma once
#include <iostream>

using namespace std;

class User {
private:
	string id_;
	string password_;
	string phone_number_;
	char user_type_;
	RentedBikeCollection* owned_rented_bike_collection_;
public:
	string GetPassword();
	RentedBikeCollection* GetUserBikes();
	bool IsAdmin();
	bool IsMember();
};

class UserCollection {
private:
	User* user_list_[50];
	int num_users_;
public:
	void AddNewUser();
	User* GetUserByID(string id);
};

class Bike {
private:
	string bike_id_;
	string bike_product_name_;
public:
	string GetBikeDetails();
};

class BikeCollection {
private:
	Bike* bike_list_[50];
	int num_bikes_;
public:
	void AddNewBike();
	Bike* GetBikeByID(string bike_id);
};

class RentedBikeCollection {
private:
	Bike* owned_rented_bike_[50];
public:
	void AddNewBike();
};

class AccessManager {
private:
	User* current_user_;
public:
	void Connect();
	void Disconnect();
	User* GetCurrentUser();
};


class SignUpUI {
public:
	void StartInterface();
	void CreateNewUser();
};

class SignUp {
public:
	void AddNewUser();
};

class LoginUI{
public:
	void StartInterface();
	void ClickLogin();
};

class Login {
public:
	void CheckValid();
	bool IsEqual();
};

class LogoutUI {
public:
	void StartInterface();
	void ClickLogout();
};

class Logout {
public:
	void ExitSystemAccess();
};

class RegisterBikeUI {
public:
	void StartInterface();
	void RegisterNewBike();
};

class RegisterBike {
public:
	void CreateNewBike();
};

class RentBikeUI {
public:
	void StartInterface();
	void RentBike();

};

class RentBike {
public:
	void AddNewBike();
};

class CheckBikeRentalInformationUI {
public:
	void StartInterface();
	void CheckBikeRentalInformation();
};

class CheckBikeRentalInformation {
public:
	void ShowBikeRentalInformation();
};