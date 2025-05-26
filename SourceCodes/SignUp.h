#pragma once
#include "EntityObjects.h"
#include "SignUpUI.h"

class SignUpUI;

//ȸ�� ���� ����� �����ϱ� ���� Control Class
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