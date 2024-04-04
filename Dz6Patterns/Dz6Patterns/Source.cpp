#include <iostream>
#include <string>

using namespace std;

class VideoCard
{
public:
	void Start() 
	{
		cout << "(4)\t����������: ������." << endl;
		cout << "(4)\t����������: �������� ����� � ���������." << endl;
	}

	void DisplayRAMInfo() 
	{
		cout << "(8)\t����������: ����� ������ �� ����������� ������." << endl;
	}

	void DisplayOpticalDriveInfo()
	{
		cout << "(11)\t����������: ����� ���������� �� ���������� ������ ������." << endl;
	}

	void DisplayHDDInfo() 
	{
		cout << "(14)\t����������: ����� ������ � ����������." << endl;
	}

	void ShowShutdownMessage() 
	{
		cout << "(18)\t����� �����: ������� �� ������� ������ ���������� ���������." << endl;
	}
};

class RAM
{
public:
	void InitializeAndCheck() 
	{
		cout << "(7)\t����������� ������: ������ ���������." << endl;
		cout << "(7)\t����������� ������: ������ ������." << endl;
	}

	void ClearAndCheck() 
	{
		cout << "(17)\t����������� ������: ������� ������." << endl;
		cout << "(17)\t����������� ������: ������ ������." << endl;
	}
};

class OpticalDrive
{
public:
	void StartAndCheck() 
	{
		cout << "(10)\t���������� ������ ���������� ������: ������." << endl;
		cout << "(10)\t���������� ������ ���������� ������: �������� ������� �����." << endl;
	}

	void ResetToInitialState() 
	{
		cout << "(19)\t���������� ������ ������: ������� � �������� �������." << endl;
	}
};

class HDD
{
public:
	void StartAndCheckBootSector() 
	{
		cout << "(13)\t���������: ������." << endl;
		cout << "(13)\t���������: �������� ������������ �������." << endl;
	}

	void ShutdownDevice() 
	{
		cout << "(16)\t���������: ��������� ����������." << endl;
	}
};

class PowerSupply
{
public:
	void PowerOn() 
	{
		cout << "(1)\t���� �������: ������ �������." << endl;
	}

	void PowerOnVideoCard() 
	{
		cout << "(3)\t���� �������: ������ ������� �� ����������." << endl;
	}

	void PowerOnRAM() 
	{
		cout << "(6)\t���� �������: ������ ������� �� ����������� ������." << endl;
	}

	void PowerOnOpticalDrive() 
	{
		cout << "(9)\t���� �������: ������ ������� �� ���������� ������ ������." << endl;
	}

	void PowerOnHDD() 
	{
		cout << "(12)\t���� �������: ������ ������� �� ���������." << endl;
	}

	void ShutdownAll() 
	{
		cout << "(20)\t���� �������: ���������� ������� ����� �����." << endl;
		cout << "(20)\t���� �������: ���������� ������� ����������� ������." << endl;
		cout << "(20)\t���� �������: ���������� ������� ���������� ������ ������." << endl;
		cout << "(20)\t���� �������: ���������� ������� ����������" << endl;
	}

	void TurnOff() 
	{
		cout << "(22)\t���� �������: ����������." << endl;
	}
};

class Sensors
{
public:
	void CheckAll() 
	{
		cout << "(2)\t�������: ��������� ����������." << endl;
		cout << "(2)\t�������: ��������� ����������� � ����� �������." << endl;
		cout << "(2)\t�������: ��������� ����������� � ����������." << endl;
	}

	void CheckTemperatureRAM() 
	{
		cout << "(5)\t�������: ��������� ����������� � ����������� ������." << endl;
	}

	void FinalTemperatureCheck() 
	{
		cout << "(15)\t�������: ��������� ����������� ���� ������." << endl;
	}

	void FinalVoltageCheck() 
	{
		cout << "(21)\t������� ��������� ����������." << endl;
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