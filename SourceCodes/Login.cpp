#include "Login.h"

Login::Login(ifstream* input_stream, ofstream* output_stream, UserCollection* user_collection, AccessManager* access_manager) {
	//UserCollection Entity object의 함수를 호출하기 위한 변수를 초기화함.
	user_collection_ = user_collection;

	//AccessManager Entity object의 함수를 호출하기 위한 변수를 초기화함.
	access_manager_ = access_manager;

	//LoginUI Boundary object를 생성함.
	login_ui_ = new LoginUI(input_stream, output_stream, this);

	//Boundary object의 StartInterface() 함수를 호출함.
	login_ui_->StartInterface();
}

bool Login::IsValid(string input_id, string input_password) {
	//입력받은 ID를 가진 이용자를 받음.
	User* user = user_collection_->GetUserById(input_id);

	//입력받은 ID를 가진 이용자의 비밀번호를 받음.
	string user_password = user->GetPassword();

	//입력한 비밀번호와 저장된 비밀번호가 일치하면 로그인시킴.
	if (IsEqual(input_password, user_password)) {
		//함수를 호출함으로써 Entity object에게 값을 전달함.
		access_manager_->Connect(user);

		//로그인에 성공했다는 것을 Boundary object에게 전달함.
		return true;
	}
	return false;
}

//입력받은 비밀번호와 이용자의 저장된 비밀번호를 비교하여, 같으면 true, 그렇지 않으면 false를 반환함.
bool Login::IsEqual(string input_password, string user_password) {
	if (input_password == user_password) return true;
	else return false;
}