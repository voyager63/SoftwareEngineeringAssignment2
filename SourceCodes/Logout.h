#pragma once
#include "EntityObjects.h"
#include "LogoutUI.h"

class LogoutUI;

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