#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <utility>

using namespace std;

class User;
class UserCollection;
class Bike;
class BikeCollection;
class RentedBikeCollection;
class AccessManager;

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


//���� �ý��ۿ� ��ϵ� �̿��� �÷����� ǥ���ϴ� Entity Class
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


//���� �ý��ۿ� ��ϵ� ������ �÷����� ǥ���ϴ� Entity Class
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


//ȸ���� �뿩�� ������ �÷����� ǥ���ϴ� Entity Class
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