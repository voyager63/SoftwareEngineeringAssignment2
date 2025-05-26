#pragma once
#include "EntityObjects.h"
#include "LogoutUI.h"

class LogoutUI;

//로그아웃 기능을 구현하기 위한 Control Class
class Logout {
private:
	//LogoutUI Boundary object를 생성하고, Boundary object의 StartInterface()를 호출하기 위한 변수
	LogoutUI* logout_ui_;

	//AccessManager Entity Class의 함수를 호출하기 위한 변수
	AccessManager* access_manager_;

public:
	//생성자
	Logout(ifstream* input_stream, ofstream* output_stream, AccessManager* access_manager);

	//Entity object의 함수를 호출하여 로그아웃시킴.
	string ExitSystemAccess();
};