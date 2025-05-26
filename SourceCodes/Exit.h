#pragma once
#include "EntityObjects.h"
#include "ExitUI.h"

class ExitUI;

//종료 기능을 구현하기 위한 Control Class
class Exit {
private:
	//ExitUI Boundary object를 생성하고, Boundary object의 StartInterface()를 호출하기 위한 변수
	ExitUI* exit_ui_;

	//종료를 위한 변수의 값을 바꾸기 위한 변수
	int* is_program_exit_;

public:
	//생성자
	Exit(ifstream* input_stream, ofstream* output_stream, int* is_program_exit);

	//종료를 위한 변수의 값을 1로 바꿈.
	void ExitSystem();
};
