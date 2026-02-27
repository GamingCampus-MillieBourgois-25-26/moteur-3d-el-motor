#include "UserScript/UserScript.hpp"



//The constructor is called when the script is created, and is used to initialize any necessary variables or set up any necessary components for the script to function properly. It is typically called once at the beginning of the script's lifecycle.
UserScript::UserScript(std::string ScriptName)
{
	name = ScriptName;
}

//This funtion is called when the script is first loaded, and is used to initialize any variables or set up any necessary components for the script to function properly. It is typically called once at the beginning of the script's lifecycle.
void UserScript::OnStart() {


}


//This function is called every frame, and is used to update the script's behavior based on the current state of the game. It is typically called once per frame, and can be used to implement any necessary logic or behavior for the script to function properly.
void UserScript::Update(float deltatime) {

}