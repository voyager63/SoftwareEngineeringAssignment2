#pragma once
#include "EntityObjects.h"
#include "Logout.h"

class Logout;

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
