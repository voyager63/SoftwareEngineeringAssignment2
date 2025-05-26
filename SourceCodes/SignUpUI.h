#pragma once
#include "EntityObjects.h"
#include "SignUp.h"

class SignUp;

//ȸ�� ���� ����� �����ϱ� ���� Boundary Class
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