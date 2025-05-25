#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <utility>

using namespace std;

//���� ����
class User;
class UserCollection;
class Bike;
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


//�̿����� ������ �Է��ϰų� ��ȯ�ϱ� ���� ����ü
struct UserInput {
	string id;
	string password;
	string phone_number;
	char user_type;
};

//�������� ������ �Է��ϰų� ��ȯ�ϱ� ���� ����ü
struct BikeInput {
	string bike_id;
	string bike_product_name;
};


//�̿��ڸ� ǥ���ϴ� Entity Class
class User {
private:
	//�̿����� ID
	string id_;

	//�̿����� ��й�ȣ
	string password_;

	//�̿����� ��ȭ��ȣ
	string phone_number_;

	//�̿����� ����. ȸ�� �Ǵ� ��������.
	char user_type_;

	//ȸ���� �뿩�� �������� �迭
	RentedBikeCollection* owned_rented_bike_collection_;

public:
	//������
	User(string id, string password, string phone_number, char user_type);

	//�̿����� ID�� ��ȯ��.
	string GetId();

	//�̿����� ��й�ȣ�� ��ȯ��.
	string GetPassword();

	//�̿����� �ڽ��� �뿩�� ������ ����� ��ȯ��.
	RentedBikeCollection* GetUserBikes();

	//�̿����� ������ 'ȸ��'�̸� true�� ��ȯ��. �׷��� ������ false�� ��ȯ��.
	bool IsAdmin();

	//�̿����� ������ '������'�̸� true�� ��ȯ��. �׷��� ������ false�� ��ȯ��.
	bool IsMember();
};


//�̿��� ����� ǥ���ϴ� Entity Class
class UserCollection {
private:
	//���� �ý��ۿ� ��ϵ� �̿����� �迭
	User* user_list_[50];

	//���� �ý��ۿ� ��ϵ� �̿����� ��
	int num_users_;

public:
	//������. �����ʰ� ���ÿ� �����ڸ� ������.
	UserCollection(string admin_id, string admin_password);

	//�ý��ۿ� �̿��ڸ� �����.
	void AddNewUser(UserInput user_input);

	//�̿����� ID�� �̿��Ͽ� �ش� ID�� ���� �̿��ڸ� ��ȯ��.
	User* GetUserById(string id);
};


//�����Ÿ� ǥ���ϴ� Entity Class
class Bike {
private:
	//�������� ID
	string bike_id_;

	//�������� ������ ��ǰ��
	string bike_product_name_;

public:
	//������
	Bike(string bike_id, string bike_product_name);

	//�������� ������ ID, ������ ��ǰ���� ��ȯ��.
	BikeInput GetBikeDetails();
};


//��ϵ� ������ ����� ǥ���ϴ� Entity Class
class BikeCollection {
private:
	//���� �ý��ۿ� ��ϵ� �������� �迭
	Bike* bike_list_[50];

	//���� �ý��ۿ� ��ϵ� �������� ��
	int num_bikes_;

public:
	//������
	BikeCollection();

	//�ý��ۿ� �����Ÿ� �����.
	void AddNewBike(BikeInput bike_input);

	//�������� ID�� �̿��Ͽ� �ش� ID�� ���� �����Ÿ� ��ȯ��.
	Bike* GetBikeById(string bike_id);
};


//ȸ���� �뿩�� ������ ����� ǥ���ϴ� Entity Class
class RentedBikeCollection {
private:
	//ȸ���� ���� �뿩�� �������� �迭
	Bike* owned_rented_bike_[50];

	//ȸ���� ���� �뿩�� �������� ��
	int num_rented_bikes_;

public:
	//������
	RentedBikeCollection();

	//�����Ÿ� �Է¹޾� �װ��� ȸ���� ���� �뿩�� �������� �迭�� �߰���.
	void AddNewBike(Bike* bike);

	//ȸ���� ���� �뿩�� �������� ���� ��ȯ��.
	int GetNumRentedBikes();

	//ȸ���� ���� �뿩�� �������� �迭�� ��ȯ��.
	Bike** GetRentedBikes();

	//ȸ���� ���� �뿩�� �����ŵ��� ������ ID�� ������������ ������.
	void SortBikeById();
};


//�̿����� �α���, �α׾ƿ��� ���� �α��ε� �̿��ڸ� ǥ���ϱ� ���� Entity Class
class AccessManager {
private:
	//���� �ý��ۿ� �α����� �̿���
	User* current_user_;

public:
	//������
	AccessManager();

	//�Է¹��� �̿��ڰ� �α��εǰ� ��.
	void Connect(User* user);

	//�̿��ڰ� �α׾ƿ��ǰ� ��.
	void Disconnect();

	//���� �ý��ۿ� �α����� �̿��ڸ� ��ȯ��.
	User* GetCurrentUser();
};


//ȸ������ ����� �����ϱ� ���� Boundary Class
class SignUpUI {
private:
	//SignUp Control object�� �Լ��� ȣ���ϱ� ���� ����
	SignUp* sign_up_;

	//���Ϸκ��� �Է��� �ޱ� ���� ����
	ifstream* input_stream_;

	//Control object�κ��� ��ȯ���� ���� ���Ͽ� ����ϱ� ���� ����
	ofstream* output_stream_;

public:
	//������
	SignUpUI(ifstream* input_stream, ofstream* output_stream, SignUp* sign_up);

	//����ڷκ��� �Է��� ����.
	void StartInterface();

	//������� �Է��� Control object���� ������.
	void CreateNewUser(UserInput user_input);
};


//ȸ������ ����� �����ϱ� ���� Control Class
class SignUp {
private:
	//SignUpUI Boundary object�� �����ϰ�, Boundary object�� StartInterface()�� ȣ���ϱ� ���� ����
	SignUpUI* sign_up_ui_;

	//UserCollection Entity Class�� �Լ��� ȣ���ϱ� ���� ����
	UserCollection* user_collection_;

public:
	//������
	SignUp(ifstream* input_stream, ofstream* output_stream, UserCollection* user_collection);

	//Boundary object�κ��� ���� ���� Entity object���� ������.
	UserInput AddNewUser(UserInput user_input);
};


//�α��� ����� �����ϱ� ���� Boundary Class 
class LoginUI{
private:
	//Login Control object�� �Լ��� ȣ���ϱ� ���� ����
	Login* login_;

	//���Ϸκ��� �Է��� �ޱ� ���� ����
	ifstream* input_stream_;

	//Control object�κ��� ��ȯ���� ���� ���Ͽ� ����ϱ� ���� ����
	ofstream* output_stream_;

public:
	//������
	LoginUI(ifstream* input_stream, ofstream* output_stream, Login* login);

	//�̿��ڷκ��� �Է��� ����.
	void StartInterface();

	//�̿����� �Է��� Control object���� ������.
	void ClickLogin(string user_id, string user_password);
};

//�α��� ����� �����ϱ� ���� Control Class
class Login {
private:
	//LoginUI Boundary object�� �����ϰ�, Boundary object�� StartInterface()�� ȣ���ϱ� ���� ����
	LoginUI* login_ui_;

	//UserCollection Entity Class�� �Լ��� ȣ���ϱ� ���� ����
	UserCollection* user_collection_;

	//AccessManager Entity Class�� �Լ��� ȣ���ϱ� ���� ����
	AccessManager* access_manager_;

public:
	//������
	Login(ifstream* input_stream, ofstream* output_stream, UserCollection* user_collection, AccessManager* access_manager);

	//�̿����� ID, ��й�ȣ�� �Է¹޾� �α����� �����ߴ����� ��ȯ��.
	bool IsValid(string input_id, string input_password);

	//�̿��ڰ� �Է��� ��й�ȣ�� ����� ��й�ȣ�� ��ġ�ϴ����� ��ȯ��.
	bool IsEqual(string input_password, string user_password);
};


//�α׾ƿ� ����� �����ϱ� ���� Boundary Class
class LogoutUI {
private:
	//Logout Control object�� �Լ��� ȣ���ϱ� ���� ����
	Logout* logout_;

	//���Ϸκ��� �Է��� �ޱ� ���� ����
	ifstream* input_stream_;

	//Control object�κ��� ��ȯ���� ���� ���Ͽ� ����ϱ� ���� ����
	ofstream* output_stream_;

public:
	//������
	LogoutUI(ifstream* input_stream, ofstream* output_stream, Logout* logout);

	//�̿��ڷκ��� �Է��� ����.
	void StartInterface();

	//�̿����� �Է��� Control object���� ������.
	void ClickLogout();
};


//�α׾ƿ� ����� �����ϱ� ���� Control Class
class Logout {
private:
	//LogoutUI Boundary object�� �����ϰ�, Boundary object�� StartInterface()�� ȣ���ϱ� ���� ����
	LogoutUI* logout_ui_;

	//AccessManager Entity Class�� �Լ��� ȣ���ϱ� ���� ����
	AccessManager* access_manager_;

public:
	//������
	Logout(ifstream* input_stream, ofstream* output_stream, AccessManager* access_manager);

	//Entity object�� �Լ��� ȣ���Ͽ� �α׾ƿ���Ŵ.
	string ExitSystemAccess();
};


//������ ��� ����� �����ϱ� ���� Boundary Class
class RegisterBikeUI {
private:
	//RegisterBike Control object�� �Լ��� ȣ���ϱ� ���� ����
	RegisterBike* register_bike_;

	//���Ϸκ��� �Է��� �ޱ� ���� ����
	ifstream* input_stream_;

	//Control object�κ��� ��ȯ���� ���� ���Ͽ� ����ϱ� ���� ����
	ofstream* output_stream_;

public:
	//������
	RegisterBikeUI(ifstream* input_stream, ofstream* output_stream, RegisterBike* register_bike);

	//�����ڷκ��� �Է��� ����.
	void StartInterface();

	//�������� �Է��� Control object���� ������.
	void RegisterNewBike(BikeInput bike_input);
};


//������ ��� ����� �����ϱ� ���� Control Class
class RegisterBike {
private:
	//RegisterBike Boundary object�� �����ϰ�, Boundary object�� StartInterface()�� ȣ���ϱ� ���� ����
	RegisterBikeUI* register_bike_ui_;

	//BikeCollection Entity Class�� �Լ��� ȣ���ϱ� ���� ����
	BikeCollection* bike_collection_;

	//AccessManager Entity Class�� �Լ��� ȣ���ϱ� ���� ����
	AccessManager* access_manager_;

public:
	//������
	RegisterBike(ifstream* input_stream, ofstream* output_stream, BikeCollection* bike_collection, AccessManager* access_manager);

	//Boundary object�κ��� ���� �Է��� Entity object���� �����ϰ�, Boundary object���� ��ȯ���� ��ȯ��.
	BikeInput CreateNewBike(BikeInput bike_input);
};


//������ �뿩 ����� �����ϱ� ���� Boundary Class
class RentBikeUI {
private:
	//RentBike Control object�� �Լ��� ȣ���ϱ� ���� ����
	RentBike* rent_bike_;

	//���Ϸκ��� �Է��� �ޱ� ���� ����
	ifstream* input_stream_;

	//Control object�κ��� ��ȯ���� ���� ���Ͽ� ����ϱ� ���� ����
	ofstream* output_stream_;

public:
	//������
	RentBikeUI(ifstream* input_stream, ofstream* output_stream, RentBike* rent_bike);

	//ȸ�����κ��� �Է��� ����.
	void StartInterface();

	//ȸ���� �Է��� Control object���� ������.
	void HireBike(string bike_id);
};


//������ �뿩 ����� �����ϱ� ���� Control Class
class RentBike {
private:
	//RentBike Boundary object�� �����ϰ�, Boundary object�� StartInterface()�� ȣ���ϱ� ���� ����
	RentBikeUI* rent_bike_ui_;

	//BikeCollection Entity Class�� �Լ��� ȣ���ϱ� ���� ����
	BikeCollection* bike_collection_;

	//AccessManager Entity Class�� �Լ��� ȣ���ϱ� ���� ����
	AccessManager* access_manager_;

public:

	//������
	RentBike(ifstream* input_stream, ofstream* output_stream, BikeCollection* bike_collection, AccessManager* access_manager);

	//Boundary object�κ��� ���� �Է��� Entity object���� �����ϰ�, Boundary object���� ��ȯ���� ��ȯ��.
	BikeInput AddNewBike(string bike_id);
};


//�뿩 ���� ������ ���� ��ȸ ����� �����ϱ� ���� Boundary Class
class CheckBikeRentalInformationUI {
private:
	//CheckBikeRentalInformation Control object�� �Լ��� ȣ���ϱ� ���� ����
	CheckBikeRentalInformation* check_bike_rental_information_;

	//���Ϸκ��� �Է��� �ޱ� ���� ����
	ifstream* input_stream_;

	//Control object�κ��� ��ȯ���� ���� ���Ͽ� ����ϱ� ���� ����
	ofstream* output_stream_;

public:
	//������
	CheckBikeRentalInformationUI(ifstream* input_stream, ofstream* output_stream, CheckBikeRentalInformation* check_bike_rental_information);

	//ȸ�����κ��� �Է��� ����.
	void StartInterface();

	//ȸ���� �Է��� Control object���� ������.
	void ViewBikeRentalInformation();
};


//�뿩 ���� ������ ���� ��ȸ ����� �����ϱ� ���� Control Class
class CheckBikeRentalInformation {
private:
	//CheckBikeRentalInformation Boundary object�� �����ϰ�, Boundary object�� StartInterface()�� ȣ���ϱ� ���� ����
	CheckBikeRentalInformationUI* check_bike_rental_information_ui_;

	//AccessManager Entity Class�� �Լ��� ȣ���ϱ� ���� ����
	AccessManager* access_manager_;

public:
	//������
	CheckBikeRentalInformation(ifstream* input_stream, ofstream* output_stream, AccessManager* access_manager);

	//Entity object�κ��� ���� ���, Boundary object���� ��ȯ���� ��ȯ��.
	pair<BikeInput*, int> ShowBikeRentalInformation();
};


//���� ����� �����ϱ� ���� Boundary Class
class ExitUI {
private:
	//Exit Control object�� �Լ��� ȣ���ϱ� ���� ����
	Exit* exit_;

	//���Ϸκ��� �Է��� �ޱ� ���� ����
	ifstream* input_stream_;

	//Control object�κ��� ��ȯ���� ���� ���Ͽ� ����ϱ� ���� ����
	ofstream* output_stream_;

public:
	//������
	ExitUI(ifstream* input_stream, ofstream* output_stream, Exit* exit);

	//�����, �̿��ڷκ��� �Է��� ����.
	void StartInterface();

	//�����, �̿����� �Է��� Control object���� ������.
	void ExitSystem();
};


//���� ����� �����ϱ� ���� Control Class
class Exit {
private:
	//ExitUI Boundary object�� �����ϰ�, Boundary object�� StartInterface()�� ȣ���ϱ� ���� ����
	ExitUI* exit_ui_;

	//���Ḧ ���� ������ ���� �ٲٱ� ���� ����
	int* is_program_exit_;

public:
	//������
	Exit(ifstream* input_stream, ofstream* output_stream, int* is_program_exit);

	//���Ḧ ���� ������ ���� 1�� �ٲ�.
	void ExitSystem();
};