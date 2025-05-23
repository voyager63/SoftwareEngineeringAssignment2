#include "SharedBikeRentalSystem.h"
#include <fstream>

//entity

//User
User::User(string id, string password, string phone_number, char user_type) {
	id_ = id;
	password_ = password;
	phone_number_ = phone_number;
	user_type_ = user_type;
	owned_rented_bike_collection_ = new RentedBikeCollection();
}

string User::GetId() {
	return id_;
}

string User::GetPassword() {
	return password_;
}

RentedBikeCollection* User::GetUserBikes() {
	return owned_rented_bike_collection_;
}

bool User::IsAdmin() {
	if (user_type_ = 'A') return true;
	else return false;
}

bool User::IsMember() {
	if (user_type_ = 'M') return true;
	else return false;
}



//UserCollection
UserCollection::UserCollection(string admin_id, string admin_password) {
	num_users_ = 0;
	user_list_[num_users_++] = new User(admin_id, admin_password, "", 'A');
}

void UserCollection::AddNewUser(UserInput user_input) {
	user_list_[num_users_++] = new User(user_input.id, user_input.password, user_input.phone_number, user_input.user_type);
}

User* UserCollection::GetUserByID(string id) {
	for (int i = 0; i < num_users_; i++) {
		if (user_list_[i]->GetId() == id) return user_list_[i];
	}
}



//Bike
Bike::Bike(string bike_id, string bike_product_name) {
	bike_id_ = bike_id;
	bike_product_name_ = bike_product_name;
}

BikeInput Bike::GetBikeDetails() {
	BikeInput bike_input;
	bike_input.bike_id = bike_id_;
	bike_input.bike_product_name = bike_product_name_;
	return bike_input;
}



//BikeCollection
BikeCollection::BikeCollection() {
	num_bikes_ = 0;
}

void BikeCollection::AddNewBike(BikeInput bike_input) {
	bike_list_[num_bikes_++] = new Bike(bike_input.bike_id, bike_input.bike_product_name);
}

Bike* BikeCollection::GetBikeByID(string bike_id) {
	for (int i = 0; i < num_bikes_; i++) {
		if (bike_list_[i]->GetBikeDetails().bike_id == bike_id) return bike_list_[i];
	}
}



//RentedBikeCollection
RentedBikeCollection::RentedBikeCollection() {
	num_rented_bikes_ = 0;
}

void RentedBikeCollection::AddNewBike(Bike* bike) {
	owned_rented_bike_[num_rented_bikes_++] = bike;
}

int RentedBikeCollection::GetNumRentedBikes() {
	return num_rented_bikes_;
}

Bike** RentedBikeCollection::GetRentedBikes() {
	return owned_rented_bike_;
}



//AccessManager
AccessManager::AccessManager() {
	current_user_ = NULL;
}

void AccessManager::Connect(User* user) {
	current_user_ = user;
}

void AccessManager::Disconnect() {
	current_user_ = NULL;
}

User* AccessManager::GetCurrentUser() {
	return current_user_;
}



//boundary and control

//Sign up

SignUp::SignUp(ifstream* if_stream, UserCollection* user_collection) {
	user_collection_ = user_collection;
	sign_up_ui_ = new SignUpUI(this);
	sign_up_ui_->StartInterface(if_stream);
}

SignUpUI::SignUpUI(SignUp* sign_up) {
	sign_up_ = sign_up;
}


void SignUpUI::StartInterface(ifstream* if_stream)
{
	UserInput user_input;
	user_input.user_type = 'M';
	*if_stream >> user_input.id >> user_input.password >> user_input.phone_number;
	CreateNewUser(user_input);
}

void SignUpUI::CreateNewUser(UserInput user_input)
{
	sign_up_->AddNewUser(user_input);
}

void SignUp::AddNewUser(UserInput user_input) {
	user_collection_->AddNewUser(user_input);
	//id, password, phone_number 출력 코드 위치
}



//Login

Login::Login(ifstream* if_stream, UserCollection* user_collection, AccessManager* access_manager) {
	user_collection_ = user_collection;
	access_manager_ = access_manager;
	login_ui_ = new LoginUI(this);
	login_ui_->StartInterface(if_stream);
}


void Login::CheckValid(string input_id, string input_password) {
	User* user = user_collection_->GetUserByID(input_id);
	string user_password = user->GetPassword();
	if (IsEqual(input_password, user_password)) {
		access_manager_->Connect(user);
		// id, password 출력 코드 위치
	}
}

bool Login::IsEqual(string input_password, string user_password) {
	if (input_password == user_password) return true;
	else return false;
}

LoginUI::LoginUI(Login* login) {
	login_ = login;
}

void LoginUI::StartInterface(ifstream* if_stream) {
	string user_id, user_password;
	*if_stream >> user_id >> user_password;
	ClickLogin(user_id, user_password);
}

void LoginUI::ClickLogin(string user_id, string user_password) {
	login_->CheckValid(user_id, user_password);
}

//Logout

Logout::Logout(AccessManager* access_manager) {
	access_manager_ = access_manager;
	logout_ui_ = new LogoutUI();
	logout_ui_->StartInterface();
}

void LogoutUI::StartInterface() {
	ClickLogout();
}

void LogoutUI::ClickLogout() {
	logout_->ExitSystemAccess();
}

void Logout::ExitSystemAccess() {
	access_manager_->Disconnect();
}

//Register a new bike

RegisterBike::RegisterBike(ifstream* if_stream, BikeCollection* bike_collection, AccessManager* access_manager) {
	bike_collection_ = bike_collection;
	access_manager_ = access_manager;
	register_bike_ui_ = new RegisterBikeUI(this);
	register_bike_ui_->StartInterface(if_stream);
}

RegisterBikeUI::RegisterBikeUI(RegisterBike* register_bike) {
	register_bike_ = register_bike;
}

void RegisterBikeUI::StartInterface(ifstream* if_stream) {
	BikeInput bike_input;
	*if_stream >> bike_input.bike_id >> bike_input.bike_product_name;
	RegisterNewBike(bike_input);
}

void RegisterBikeUI::RegisterNewBike(BikeInput bike_input) {
	register_bike_->CreateNewBike(bike_input);
}

void RegisterBike::CreateNewBike(BikeInput bike_input) {
	User* current_user = access_manager_->GetCurrentUser();
	if (current_user->IsAdmin()) bike_collection_->AddNewBike(bike_input);
}

//Rent a bike

RentBike::RentBike(ifstream* if_stream, BikeCollection* bike_collection, AccessManager* access_manager) {
	bike_collection_ = bike_collection;
	access_manager_ = access_manager;
	rent_bike_ui_ = new RentBikeUI(this);
	rent_bike_ui_->StartInterface(if_stream);
}

RentBikeUI::RentBikeUI(RentBike* rent_bike) {
	rent_bike_ = rent_bike;
}

void RentBikeUI::StartInterface(ifstream* if_stream) {
	string bike_id;
	*if_stream >> bike_id;
	HireBike(bike_id);
}

void RentBikeUI::HireBike(string bike_id) {
	rent_bike_->AddNewBike(bike_id);
}

void RentBike::AddNewBike(string bike_id) {
	User* current_user = access_manager_->GetCurrentUser();
	if (current_user->IsMember()) {
		Bike* selected_bike = bike_collection_->GetBikeByID(bike_id);
		current_user->GetUserBikes()->AddNewBike(selected_bike);
	}
}

//Check bike rental information

CheckBikeRentalInformation::CheckBikeRentalInformation(AccessManager* access_manager){
	access_manager_ = access_manager;
	check_bike_rental_information_ui_ = new CheckBikeRentalInformationUI(this);
	check_bike_rental_information_ui_->StartInterface();
}

CheckBikeRentalInformationUI::CheckBikeRentalInformationUI(CheckBikeRentalInformation* check_bike_rental_information) {
	check_bike_rental_information_ = check_bike_rental_information;
}

void CheckBikeRentalInformationUI::StartInterface() {
	ViewBikeRentalInformation();
}

void CheckBikeRentalInformationUI::ViewBikeRentalInformation() {
	check_bike_rental_information_->ShowBikeRentalInformation();
}

void CheckBikeRentalInformation::ShowBikeRentalInformation() {
	User* current_user = access_manager_->GetCurrentUser();
	if (current_user->IsMember()) {
		RentedBikeCollection* rented_bikes = current_user->GetUserBikes();
		for (int i = 0; i < rented_bikes->GetNumRentedBikes(); i++) {
			rented_bikes->GetRentedBikes()[i]->GetBikeDetails();
		}
	}
}
