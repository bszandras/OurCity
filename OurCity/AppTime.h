#pragma once
class Time
{
private:
	// el�z� frame �ta eltellt m�sodpercek
	// ezzel tudjuk normaliz�lni az id� alap� dolgokat (camera mozg�s �s zoom jelenleg)
	// minn�l nagyobb az fps ezek a dolgok ann�l "gyorsabbak"
	// deltaTime ezeket tudja normaliz�lni, ak�r frame droppok eset�n
	float deltaTime;
	// j�t�k indul�s �ta eltellt id�
	// scale, ezt gyors�tja lass�tja, 0 eset�n meg�ll�tja
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