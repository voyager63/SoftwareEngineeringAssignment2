#pragma once
#include <iostream>

using namespace std;

class User;
class Bike;
class UserCollection;
class BikeCollection;
class RentedBikeCollection;
class AccessManager;
class SignUpUI;
class SignUp;
class LoginUI;
class Login;
class LogoutUI;
class Logout;
class RegisterBikeUI;
class RegisterBike;
class RentBikeUI;
class RentBike;
class CheckBikeRentalInformationUI;
class CheckBikeRentalInformation;
class ExitUI;
class Exit;


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
	User* GetUserById(string id);
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
	BikeCollection();
	void AddNewBike(BikeInput bike_input);
	Bike* GetBikeById(string bike_id);
};

//RentedBikeCollection

class RentedBikeCollection {
private:
	Bike* owned_rented_bike_[50];
	int num_rented_bikes_;
public:
	RentedBikeCollection();
	void AddNewBike(Bike* bike);
	int GetNumRentedBikes();
	Bike** GetRentedBikes();
};

//AccessManager

class AccessManager {
private:
	User* current_user_;
public:
	AccessManager();
	void Connect(User* user);
	void Disconnect();
	User* GetCurrentUser();
};

//boundary and control

//Sign up

class SignUpUI {
private:
	SignUp* sign_up_;
	ifstream* if_stream_;
	ofstream* of_stream_;
public:
	SignUpUI(ifstream* if_stream, ofstream* of_stream, SignUp* sign_up);
	void StartInterface();
	void CreateNewUser(UserInput);
};

class SignUp {
private:
	SignUpUI* sign_up_ui_;
	UserCollection* user_collection_;
public:
	SignUp(ifstream* if_stream, ofstream* of_stream, UserCollection* user_collection);
	UserInput AddNewUser(UserInput user_input);
};

//Login

class LoginUI{
private:
	Login* login_;
	ifstream* if_stream_;
	ofstream* of_stream_;
public:
	LoginUI(ifstream* if_stream, ofstream* of_stream, Login* login);
	void StartInterface();
	void ClickLogin(string user_id, string user_password);
};

class Login {
private:
	LoginUI* login_ui_;
	UserCollection* user_collection_;
	AccessManager* access_manager_;
public:
	Login(ifstream* if_stream, ofstream* of_stream, UserCollection* user_collection, AccessManager* access_manager);
	bool IsValid(string input_id, string input_password);
	bool IsEqual(string input_password, string user_password);
};

//Logout

class LogoutUI {
private:
	Logout* logout_;
	ifstream* if_stream_;
	ofstream* of_stream_;
public:
	LogoutUI(ifstream* if_stream, ofstream* of_stream, Logout* logout);
	void StartInterface();
	void ClickLogout();
};

class Logout {
private:
	LogoutUI* logout_ui_;
	AccessManager* access_manager_;
public:
	Logout(ifstream* if_stream, ofstream* of_stream, AccessManager* access_manager);
	string ExitSystemAccess();
};

//Register a new Bike

class RegisterBikeUI {
private:
	RegisterBike* register_bike_;
	ifstream* if_stream_;
	ofstream* of_stream_;
public:
	RegisterBikeUI(ifstream* if_stream, ofstream* of_stream, RegisterBike* register_bike);
	void StartInterface();
	void RegisterNewBike(BikeInput bike_input);
};

class RegisterBike {
private:
	RegisterBikeUI* register_bike_ui_;
	BikeCollection* bike_collection_;
	AccessManager* access_manager_;
public:
	RegisterBike(ifstream* if_stream, ofstream* of_stream, BikeCollection* bike_collection, AccessManager* access_manager);
	BikeInput CreateNewBike(BikeInput bike_input);
};

//Rent a bike

class RentBikeUI {
private:
	RentBike* rent_bike_;
	ifstream* if_stream_;
	ofstream* of_stream_;
public:
	RentBikeUI(ifstream* if_stream, ofstream* of_stream, RentBike* rent_bike);
	void StartInterface();
	void HireBike(string bike_id);
};

class RentBike {
private:
	RentBikeUI* rent_bike_ui_;
	BikeCollection* bike_collection_;
	AccessManager* access_manager_;
public:
	RentBike(ifstream* if_stream, ofstream* of_stream, BikeCollection* bike_collection, AccessManager* access_manager);
	BikeInput AddNewBike(string bike_id);
};

//Check bike rental information

class CheckBikeRentalInformationUI {
private:
	CheckBikeRentalInformation* check_bike_rental_information_;
	ifstream* if_stream_;
	ofstream* of_stream_;
public:
	CheckBikeRentalInformationUI(ifstream* if_stream, ofstream* of_stream, CheckBikeRentalInformation* check_bike_rental_information);
	void StartInterface();
	void ViewBikeRentalInformation();
};

class CheckBikeRentalInformation {
private:
	CheckBikeRentalInformationUI* check_bike_rental_information_ui_;
	ofstream* of_stream_;
	AccessManager* access_manager_;
public:
	CheckBikeRentalInformation(ifstream* if_stream, ofstream* of_stream, AccessManager* access_manager);
	void ShowBikeRentalInformation();
};

class ExitUI {
private:
	Exit* exit_;
	ifstream* if_stream_;
	ofstream* of_stream_;
public:
	ExitUI(ifstream* if_stream, ofstream* of_stream, Exit* exit);
	void StartInterface();
	void ExitSystem();
};

class Exit {
private:
	ExitUI* exit_ui_;
	int* is_program_exit_;
	ofstream* of_stream_;
public:
	Exit(ifstream* if_stream, ofstream* of_stream, int* is_program_exit);
	void ExitSystem();
};