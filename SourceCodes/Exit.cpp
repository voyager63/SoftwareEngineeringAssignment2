#include "Exit.h"

Exit::Exit(ifstream* input_stream, ofstream* output_stream, int* is_program_exit) {
	//종료를 위한 변수의 값을 바꾸기 위한 변수를 초기화함.
	is_program_exit_ = is_program_exit;

	//ExitUI Boundary object를 생성함.
	exit_ui_ = new ExitUI(input_stream, output_stream, this);

	//Boundary object의 StartInterface() 함수를 호출함.
	exit_ui_->StartInterface();
}

void Exit::ExitSystem() {
	//종료를 위한 변수의 값을 1로 바꿈.
	*is_program_exit_ = 1;
}