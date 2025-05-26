#pragma once
#include "EntityObjects.h"
#include "Login.h"

class Login;

//�α��� ����� �����ϱ� ���� Boundary Class
class LoginUI {
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