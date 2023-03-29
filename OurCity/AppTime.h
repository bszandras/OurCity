#pragma once
class Time
{
private:
	// elõzõ frame óta eltellt másodpercek
	// ezzel tudjuk normalizálni az idõ alapú dolgokat (camera mozgás és zoom jelenleg)
	// minnél nagyobb az fps ezek a dolgok annál "gyorsabbak"
	// deltaTime ezeket tudja normalizálni, akár frame droppok esetén
	float deltaTime;
	// játék indulás óta eltellt idõ
	// scale, ezt gyorsítja lassítja, 0 esetén megállítja
	float time;
	float scale;

	
public:
	static Time* instance;
	Time(float currTime);
	~Time();
	void UpdateTime(float currTime);
	void SetScale(float s);
	float getDelta();
};