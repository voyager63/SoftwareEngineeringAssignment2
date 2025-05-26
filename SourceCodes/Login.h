#pragma once
#include "EntityObjects.h"
#include "LoginUI.h"

class LoginUI;

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
