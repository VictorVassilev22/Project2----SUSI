#include<iostream>
#include "UserInterface.hpp"

///creates Userinterface which creates SUSI system
///@see UserInterface::openCommandLine() is used
int  main() {
	UserInterface UI;
	UI.openCommandLine();
	return 0;
}