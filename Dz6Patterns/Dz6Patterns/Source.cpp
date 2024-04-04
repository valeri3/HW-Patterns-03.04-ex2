#include <iostream>
#include <string>

using namespace std;

class VideoCard
{
public:
	void Start() 
	{
		cout << "(4)\tВидеокарта: запуск." << endl;
		cout << "(4)\tВидеокарта: проверка связи с монитором." << endl;
	}

	void DisplayRAMInfo() 
	{
		cout << "(8)\tВидеокарта: вывод данных об оперативной памяти." << endl;
	}

	void DisplayOpticalDriveInfo()
	{
		cout << "(11)\tВидеокарта: вывод информации об устройстве чтения дисков." << endl;
	}

	void DisplayHDDInfo() 
	{
		cout << "(14)\tВидеокарта: вывод данных о винчестере." << endl;
	}

	void ShowShutdownMessage() 
	{
		cout << "(18)\tВидео карта: вывести на монитор данные прощальное сообщение." << endl;
	}
};

class RAM
{
public:
	void InitializeAndCheck() 
	{
		cout << "(7)\tОперативная память: запуск устройств." << endl;
		cout << "(7)\tОперативная память: анализ памяти." << endl;
	}

	void ClearAndCheck() 
	{
		cout << "(17)\tОперативная память: очистка памяти." << endl;
		cout << "(17)\tОперативная память: анализ памяти." << endl;
	}
};

class OpticalDrive
{
public:
	void StartAndCheck() 
	{
		cout << "(10)\tУстройство чтения оптических дисков: запуск." << endl;
		cout << "(10)\tУстройство чтения оптических дисков: проверка наличия диска." << endl;
	}

	void ResetToInitialState() 
	{
		cout << "(19)\tУстройство чтения дисков: вернуть в исходную позицию." << endl;
	}
};

class HDD
{
public:
	void StartAndCheckBootSector() 
	{
		cout << "(13)\tВинчестер: запуск." << endl;
		cout << "(13)\tВинчестер: проверка загрузочного сектора." << endl;
	}

	void ShutdownDevice() 
	{
		cout << "(16)\tВинчестер: остановка устройства." << endl;
	}
};

class PowerSupply
{
public:
	void PowerOn() 
	{
		cout << "(1)\tБлок питания: подать питание." << endl;
	}

	void PowerOnVideoCard() 
	{
		cout << "(3)\tБлок питания: подать питание на видеокарту." << endl;
	}

	void PowerOnRAM() 
	{
		cout << "(6)\tБлок питания: подать питание на оперативную память." << endl;
	}

	void PowerOnOpticalDrive() 
	{
		cout << "(9)\tБлок питания: подать питание на устройство чтения дисков." << endl;
	}

	void PowerOnHDD() 
	{
		cout << "(12)\tБлок питания: подать питание на винчестер." << endl;
	}

	void ShutdownAll() 
	{
		cout << "(20)\tБлок питания: прекратить питание видео карты." << endl;
		cout << "(20)\tБлок питания: прекратить питание оперативной памяти." << endl;
		cout << "(20)\tБлок питания: прекратить питание устройства чтения дисков." << endl;
		cout << "(20)\tБлок питания: прекратить питание винчестера" << endl;
	}

	void TurnOff() 
	{
		cout << "(22)\tБлок питания: выключение." << endl;
	}
};

class Sensors
{
public:
	void CheckAll() 
	{
		cout << "(2)\tДатчики: проверить напряжение." << endl;
		cout << "(2)\tДатчики: проверить температуру в блоке питания." << endl;
		cout << "(2)\tДатчики: проверить температуру в видеокарте." << endl;
	}

	void CheckTemperatureRAM() 
	{
		cout << "(5)\tДатчики: проверить температуру в оперативной памяти." << endl;
	}

	void FinalTemperatureCheck() 
	{
		cout << "(15)\tДатчики: проверить температуру всех систем." << endl;
	}

	void FinalVoltageCheck() 
	{
		cout << "(21)\tДатчики проверить напряжение." << endl;
	}
};

class PC
{
	VideoCard videoCard;
	RAM ram;
	OpticalDrive  opticalDrive;
	HDD hdd;
	PowerSupply powerSupply;
	Sensors sensors;
public:
	PC(VideoCard videoCard, RAM ram, OpticalDrive opticalDrive, HDD hdd, PowerSupply powerSupply, Sensors sensors)
	{
		this->videoCard = videoCard;
		this->ram = ram;
		this->opticalDrive = opticalDrive;
		this->hdd = hdd;
		this->powerSupply = powerSupply;
		this->sensors = sensors;
	}

	void Start() 
	{
		powerSupply.PowerOn();
		sensors.CheckAll();
		powerSupply.PowerOnVideoCard();
		videoCard.Start();
		sensors.CheckTemperatureRAM();
		powerSupply.PowerOnRAM();
		ram.InitializeAndCheck();
		powerSupply.PowerOnOpticalDrive();
		opticalDrive.StartAndCheck();
		videoCard.DisplayOpticalDriveInfo();
		powerSupply.PowerOnHDD();
		hdd.StartAndCheckBootSector();
		videoCard.DisplayHDDInfo();
		sensors.FinalTemperatureCheck();
	}

	void Shutdown() 
	{
		hdd.ShutdownDevice();
		ram.ClearAndCheck();
		videoCard.ShowShutdownMessage();
		opticalDrive.ResetToInitialState();
		powerSupply.ShutdownAll();
		sensors.FinalVoltageCheck();
		powerSupply.TurnOff();
	}
};

class User
{
public:
	void CreateApplication(PC facade)
	{
		facade.Start();
		facade.Shutdown();
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");

	VideoCard videoCard;
	RAM ram;
	OpticalDrive opticalDrive;
	HDD hdd;
	PowerSupply powerSupply;
	Sensors sensors;

	PC turnOn(videoCard, ram, opticalDrive, hdd, powerSupply, sensors);

	User user;
	user.CreateApplication(turnOn);

	return 0;
}