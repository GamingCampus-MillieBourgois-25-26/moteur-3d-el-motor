#pragma once



class Script {



public:

	virtual ~Script() = default;

	virtual void OnStart() = 0;
	virtual void Update(float deltatime) = 0;


};