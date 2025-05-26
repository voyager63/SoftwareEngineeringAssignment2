#include "SignUpUI.h"

SignUpUI::SignUpUI(ifstream* input_stream, ofstream* output_stream, SignUp* sign_up) {
	//���Ϸκ��� �Է¹ޱ� ���� ���� ������ �ʱ�ȭ��.
	input_stream_ = input_stream;

	//���Ͽ� ����ϱ� ���� ���� ������ �ʱ�ȭ��.
	output_stream_ = output_stream;

	//SignUp Control object�� �Լ��� ȣ���ϱ� ���� ������ �ʱ�ȭ��.
	sign_up_ = sign_up;
}

void SignUpUI::StartInterface()
{
	//ȸ�� ���Կ� �ʿ��� �ʼ� �Է� ������ �Է¹���.
	UserInput user_input;
	user_input.user_type = 'M';
	*input_stream_ >> user_input.id >> user_input.password >> user_input.phone_number;

	//�Է¹��� ���� ���η� �����ϱ� ���� �Լ��� ȣ����.
	CreateNewUser(user_input);
}

void SignUpUI::CreateNewUser(UserInput user_input)
{
	//Control object�� �Լ��� ȣ���ϰ�, Control object�κ��� ��ȯ���� ���� �����.
	UserInput registered_user = sign_up_->AddNewUser(user_input);
	*output_stream_ << "1.1. ȸ������" << endl << "> " << registered_user.id << ' ' << registered_user.password << ' ' << registered_user.phone_number << endl << endl;
}