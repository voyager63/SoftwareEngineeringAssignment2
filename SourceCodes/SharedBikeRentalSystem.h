#pragma once
#include <iostream>

using namespace std;


//Input Type
struct UserInput {
	string id;
	string password;
	string phone_number;
	char user_type;
};

struct BikeInput {
	string bike_id;
	string bike_product_name;
};

//entity

//User

class User {
private:
	string id_;
	string password_;
	string phone_number_;
	char user_type_;
	RentedBikeCollection* owned_rented_bike_collection_;
public:
	User(string id, string password, string phone_number, char user_type);
	string GetId();
	string GetPassword();
	RentedBikeCollection* GetUserBikes();
	bool IsAdmin();
	bool IsMember();
};

//UserCollection

class UserCollection {
private:
	User* user_list_[50];
	int num_users_;
public:
	UserCollection(string admin_id, string admin_password);
	void AddNewUser(UserInput user_input);
	User* GetUserByID(string id);
};

//Bike

class Bike {
private:
	string bike_id_;
	string bike_product_name_;
public:
	Bike(string bike_id, string bike_product_name);
	BikeInput GetBikeDetails();
};

//BikeCollection

class BikeCollection {
private:
	Bike* bike_list_[50];
	int num_bikes_;
public:
	void AddNewBike(BikeInput bike_input);
	Bike* GetBikeByID(string bike_id);
};

//RentedBikeCollection

class RentedBikeCollection {
private:
	Bike* owned_rented_bike_[50];
	int num_rented_bikes_;
public:
	void AddNewBike(Bike* bike);
	int GetNumRentedBikes();
	Bike** GetRentedBikes();
};

//AccessManager

class AccessManager {
private:
	User* current_user_;
public:
	void Connect(User* user);
	void Disconnect();
	User* GetCurrentUser();
};

//boundary and control

//Sign up

class SignUpUI {
private:
	SignUp* sign_up_;
public:
	SignUpUI(SignUp* sign_up);
	void StartInterface(ifstream* if_stream);
	void CreateNewUser(UserInput);
};

class SignUp {
private:
	SignUpUI* sign_up_ui_;
	UserCollection* user_collection_;
public:
	SignUp(ifstream* if_stream, UserCollection* user_collection);
	void AddNewUser(UserInput user_input);
};

//Login

class LoginUI{
private:
	Login* login_;
public:
	LoginUI(Login* login);
	void StartInterface(ifstream* if_stream);
	void ClickLogin(string user_id, string user_password);
};

class Login {
private:
	LoginUI* login_ui_;
	UserCollection* user_collection_;
	AccessManager* access_manager_;
public:
	Login(ifstream* if_stream, UserCollection* user_collection, AccessManager* access_manager);
	void CheckValid(string input_id, string input_password);
	bool IsEqual(string input_password, string user_password);
};

//Logout

class LogoutUI {
private:
	Logout* logout_;
public:
	void StartInterface();
	void ClickLogout();
};

class Logout {
private:
	LogoutUI* logout_ui_;
	AccessManager* access_manager_;
public:
	Logout(AccessManager* access_manager);
	void ExitSystemAccess();
};

//Register a new Bike

class RegisterBikeUI {
private:
	RegisterBike* register_bike_;
public:
	RegisterBikeUI(RegisterBike* register_bike);
	void StartInterface(ifstream* if_stream);
	void RegisterNewBike(BikeInput bike_input);
};

class RegisterBike {
private:
	RegisterBikeUI* register_bike_ui_;
	BikeCollection* bike_collection_;
	AccessManager* access_manager_;
public:
	RegisterBike(ifstream* if_stream, BikeCollection* bike_collection, AccessManager* access_manager);
	void CreateNewBike(BikeInput bike_input);
};

//Rent a bike

class RentBikeUI {
private:
	RentBike* rent_bike_;
public:
	RentBikeUI(RentBike* rent_bike);
	void StartInterface(ifstream* if_stream);
	void HireBike(string bike_id);
};

class RentBike {
private:
	RentBikeUI* rent_bike_ui_;
	BikeCollection* bike_collection_;
	AccessManager* access_manager_;
public:
	RentBike(ifstream* if_stream, BikeCollection* bike_collection, AccessManager* access_manager);
	void AddNewBike(string bike_id);
};

//Check bike rental information

class CheckBikeRentalInformationUI {
private:
	CheckBikeRentalInformation* check_bike_rental_information_;
public:
	CheckBikeRentalInformationUI(CheckBikeRentalInformation* check_bike_rental_information);
	void StartInterface();
	void ViewBikeRentalInformation();
};

class CheckBikeRentalInformation {
private:
	CheckBikeRentalInformationUI* check_bike_rental_information_ui_;
	AccessManager* access_manager_;
public:
	CheckBikeRentalInformation(AccessManager* access_manager);
	void ShowBikeRentalInformation();
};