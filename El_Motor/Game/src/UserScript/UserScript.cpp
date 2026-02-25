#include "UserScript/UserScript.hpp"



//The constructor is called when the script is created, and is used to initialize any necessary variables or set up any necessary components for the script to function properly. It is typically called once at the beginning of the script's lifecycle.
UserScript::UserScript(std::string ScriptName)
{
	name = ScriptName;
}
//The destructor is called when the script is destroyed, and is used to clean up any resources or perform any necessary actions before the script is removed from memory. It is typically called once at the end of the script's lifecycle.
UserScript::~UserScript()
{


}

//This funtion is called when the script is first loaded, and is used to initialize any variables or set up any necessary components for the script to function properly. It is typically called once at the beginning of the script's lifecycle.
void UserScript::OnStart() {


}




void UserScript::Update(float deltatime) {

}