#include "SignUp.h"

SignUp::SignUp(ifstream* input_stream, ofstream* output_stream, UserCollection* user_collection) {
	//UserCollection Entity object�� �Լ��� ȣ���ϱ� ���� ������ �ʱ�ȭ��.
	user_collection_ = user_collection;

	//SignUpUI Boundary object�� ������.
	sign_up_ui_ = new SignUpUI(input_stream, output_stream, this);

	//Boundary object�� StartInterface() �Լ��� ȣ����.
	sign_up_ui_->StartInterface();
}

UserInput SignUp::AddNewUser(UserInput user_input) {
	//�Լ��� ȣ�������ν� Entity object���� ���� ������.
	user_collection_->AddNewUser(user_input);

	//Boundary object���� ���� ��ȯ��.
	return user_input;
}