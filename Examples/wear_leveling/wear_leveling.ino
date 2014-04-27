#include <Wire.h> //I2C library
#include <I2C_eeprom.h>
#include <wl.h>

#define DATA_START 32  //Por ejemplo 32 bytes desde el origen

// DATABASE I2C
I2C_eeprom ee(0x50);


struct sample1Var {
	char charData[25];
	int intData; 
	long longData;
} _sample1Var;

long SAMPLE1VAR_START;

int _sample2Var;
long SAMPLE2VAR_START;

struct sample3Var {
	double doubleData;
	int intData;
	char charData[25];	
} _sample3Var;
long SAMPLE3VAR_START;

char _sample4Var[5];
long SAMPLE4VAR_START;

// The read and write handlers for using the I2C EEPROM Library
void writer(unsigned long address, byte data)
{
	//EEPROM.write(address, data);
	ee.writeByte(address, data );
}

byte reader(unsigned long address)
{
	return ee.readByte(address);
	//return EEPROM.read(address);
	
}

// Create an EDB object with the appropriate write and read handlers
wl wear_leveling(&writer, &reader);


void setup()
{
	Serial.begin(9600);
	Serial.println("Start");

	SAMPLE1VAR_START = DATA_START;
	// Exists _sample1Var?
	if(wear_leveling.exists(SAMPLE1VAR_START)==WL_NOK)
	{
		Serial.println("sample1Var var NOT exists");
		// Create it at SAMPLE1VAR_START Position with WL_XX length where XX is status length 8,16,24,32,64
		wear_leveling.create(SAMPLE1VAR_START, WL_16, sizeof(_sample1Var));
		wear_leveling.clear();
		
		// Write new data to the var
		sprintf(_sample1Var.charData, "AB123-31231-FAB-32341");
		_sample1Var.intData=1;
		_sample1Var.longData=1;
		wear_leveling.open(SAMPLE1VAR_START);
		wear_leveling.writeRec(WL_REC _sample1Var);
		
		
			
		// Read info data of the var
		Serial.print("Record Count sample1Var: ");
		Serial.println(wear_leveling.count());
		Serial.print("Record Limit sample1Var: ");
		Serial.println(wear_leveling.memSize());
		dumpEEPROM(SAMPLE1VAR_START,wear_leveling.memSize());
			
		// Print the var content
		wear_leveling.open(SAMPLE1VAR_START);
		wear_leveling.readRec(WL_REC _sample1Var);
		Serial.print("Data: "); Serial.println(_sample1Var.charData);
		Serial.print("Int: "); Serial.println(_sample1Var.intData);
		Serial.print("Long: "); Serial.println(_sample1Var.longData);
	}
	else
	{
		Serial.println("sample1Var var exists");
	}

	SAMPLE2VAR_START = SAMPLE1VAR_START + wear_leveling.memSize();
	// Exists _sample2Var?
	if(wear_leveling.exists(SAMPLE2VAR_START)==WL_NOK)
	{
		Serial.println("sample2Var var NOT exists");
		// Create it at SAMPLE1VAR_START Position with WL_XX length where XX is status length 8,16,24,32,64
		wear_leveling.create(SAMPLE2VAR_START, WL_8, sizeof(_sample2Var));
		wear_leveling.clear();
		
		// Write new data to the var
		_sample2Var=1;
		wear_leveling.open(SAMPLE2VAR_START);
		wear_leveling.writeRec(WL_REC _sample2Var);
		
		
		
		// Read info data of the var
		Serial.print("Record Count sample2Var: ");
		Serial.println(wear_leveling.count());
		Serial.print("Record Limit sample2Var: ");
		Serial.println(wear_leveling.memSize());
		dumpEEPROM(SAMPLE2VAR_START,wear_leveling.memSize());
		
		// Print the var content
		wear_leveling.open(SAMPLE2VAR_START);
		wear_leveling.readRec(WL_REC _sample2Var);
		Serial.print("Int 2: "); Serial.println(_sample2Var);
	}
	else
	{
		Serial.println("sample2Var var exists");
	}
	
	
	SAMPLE3VAR_START = SAMPLE2VAR_START + wear_leveling.memSize();
	// Exists _sample3Var?
	if(wear_leveling.exists(SAMPLE3VAR_START)==WL_NOK)
	{
		Serial.println("sample3Var var NOT exists");
		// Create it at SAMPLE1VAR_START Position with WL_XX length where XX is status length 8,16,24,32,64
		wear_leveling.create(SAMPLE3VAR_START, WL_24, sizeof(_sample3Var));
		wear_leveling.clear();
		
		// Write new data to the var
		sprintf(_sample3Var.charData, "BB123-31231-FAB-32342");
		_sample3Var.intData=1;
		_sample3Var.doubleData=1;
		wear_leveling.open(SAMPLE3VAR_START);
		wear_leveling.writeRec(WL_REC _sample3Var);
		
		
		
		// Read info data of the var
		Serial.print("Record Count sample1Var: ");
		Serial.println(wear_leveling.count());
		Serial.print("Record Limit sample1Var: ");
		Serial.println(wear_leveling.memSize());
		dumpEEPROM(SAMPLE3VAR_START,wear_leveling.memSize());
		
		// Print the var content
		wear_leveling.open(SAMPLE3VAR_START);
		wear_leveling.readRec(WL_REC _sample3Var);
		Serial.print("Data: "); Serial.println(_sample3Var.charData);
		Serial.print("Int: "); Serial.println(_sample3Var.intData);
		Serial.print("Double: "); Serial.println(_sample3Var.doubleData);
	}
	else
	{
		Serial.println("sample3Var var exists");
	}
	
	SAMPLE4VAR_START = SAMPLE3VAR_START + wear_leveling.memSize();
	// Exists _sample4Var?
	if(wear_leveling.exists(SAMPLE4VAR_START)==WL_NOK)
	{
		Serial.println("sample4Var var NOT exists");
		// Create it at SAMPLE1VAR_START Position with WL_XX length where XX is status length 8,16,24,32,64
		wear_leveling.create(SAMPLE4VAR_START, WL_32, sizeof(_sample4Var));
		wear_leveling.clear();
		
		// Write new data to the var
		sprintf(_sample4Var, "0000");
		wear_leveling.open(SAMPLE4VAR_START);
		wear_leveling.writeRec(WL_REC _sample4Var);
		
		
		
		// Read info data of the var
		Serial.print("Record Count sample4Var: ");
		Serial.println(wear_leveling.count());
		Serial.print("Record Limit sample4Var: ");
		Serial.println(wear_leveling.memSize());
		dumpEEPROM(SAMPLE4VAR_START,wear_leveling.memSize());
		
		// Print the var content
		wear_leveling.open(SAMPLE4VAR_START);
		wear_leveling.readRec(WL_REC _sample4Var);
		Serial.print("Data 4: "); Serial.println(_sample4Var);
	}
	else
	{
		Serial.println("sample4Var var exists");
	}
	
}

void loop()
{

	// Read the new data writed and show it
	wear_leveling.open(SAMPLE1VAR_START);
	wear_leveling.readRec(WL_REC _sample1Var);
	Serial.print("Data: "); Serial.println(_sample1Var.charData);
	Serial.print("Int: "); Serial.println(_sample1Var.intData);
	Serial.print("Long: "); Serial.println(_sample1Var.longData);

	dumpEEPROM(SAMPLE1VAR_START,wear_leveling.memSize());

	int intData = _sample1Var.intData;
	long longData = _sample1Var.longData;
	for(int i=0;i<25;i++)
	{
		
		// Write new data to the var
		sprintf(_sample1Var.charData, "AB123-31231-FAB-32341");
		_sample1Var.intData=++intData;
		_sample1Var.longData=++longData;
		wear_leveling.open(SAMPLE1VAR_START);
		wear_leveling.writeRec(WL_REC _sample1Var);

	}

// Read the new data writed and show it
wear_leveling.open(SAMPLE1VAR_START);
wear_leveling.readRec(WL_REC _sample1Var);
Serial.print("Data: "); Serial.println(_sample1Var.charData);
Serial.print("Int: "); Serial.println(_sample1Var.intData);
Serial.print("Long: "); Serial.println(_sample1Var.longData);

	dumpEEPROM(SAMPLE1VAR_START,wear_leveling.memSize());
	
	
	// Read the new data writed and show it
	wear_leveling.open(SAMPLE2VAR_START);
	wear_leveling.readRec(WL_REC _sample2Var);
	Serial.print("Int 2: "); Serial.println(_sample2Var);


	dumpEEPROM(SAMPLE2VAR_START,wear_leveling.memSize());

	int int2Data = _sample2Var;
	for(int i=0;i<25;i++)
	{
		
		// Write new data to the var

		_sample2Var=++int2Data;
		wear_leveling.open(SAMPLE2VAR_START);
		wear_leveling.writeRec(WL_REC _sample2Var);

	}

	// Read the new data writed and show it
	wear_leveling.open(SAMPLE2VAR_START);
	wear_leveling.readRec(WL_REC _sample2Var);
	Serial.print("Int 2: "); Serial.println(_sample2Var);


	dumpEEPROM(SAMPLE2VAR_START,wear_leveling.memSize());



	// Read the new data writed and show it
	wear_leveling.open(SAMPLE3VAR_START);
	wear_leveling.readRec(WL_REC _sample3Var);
	Serial.print("Data: "); Serial.println(_sample3Var.charData);
	Serial.print("Int: "); Serial.println(_sample3Var.intData);
	Serial.print("Double: "); Serial.println(_sample3Var.doubleData);

	dumpEEPROM(SAMPLE3VAR_START,wear_leveling.memSize());

	intData = _sample3Var.intData;
	double doubleData = _sample3Var.doubleData;
	for(int i=0;i<25;i++)
	{
	
		// Write new data to the var
		sprintf(_sample3Var.charData, "AB123-31231-FAB-32341");
		_sample3Var.intData=++intData;
		_sample3Var.doubleData=++doubleData;
		wear_leveling.open(SAMPLE3VAR_START);
		wear_leveling.writeRec(WL_REC _sample3Var);

	}

	// Read the new data writed and show it
	wear_leveling.open(SAMPLE3VAR_START);
	wear_leveling.readRec(WL_REC _sample3Var);
	Serial.print("Data: "); Serial.println(_sample3Var.charData);
	Serial.print("Int: "); Serial.println(_sample3Var.intData);
	Serial.print("Double: "); Serial.println(_sample3Var.doubleData);

	dumpEEPROM(SAMPLE3VAR_START,wear_leveling.memSize());




	// Read the new data writed and show it
	wear_leveling.open(SAMPLE4VAR_START);
	wear_leveling.readRec(WL_REC _sample4Var);
	Serial.print("Data 4: "); Serial.println(_sample4Var);

	dumpEEPROM(SAMPLE4VAR_START,wear_leveling.memSize());

	intData = _sample4Var[3]-'0';
	for(int i=0;i<25;i++)
	{
	
		// Write new data to the var
		_sample4Var[3] = ((intData++)%10)+'0';
		wear_leveling.open(SAMPLE4VAR_START);
		wear_leveling.writeRec(WL_REC _sample4Var);

	}

	// Read the new data writed and show it
	wear_leveling.open(SAMPLE4VAR_START);
	wear_leveling.readRec(WL_REC _sample4Var);
	Serial.print("Data 4: "); Serial.println(_sample4Var);


	dumpEEPROM(SAMPLE4VAR_START,wear_leveling.memSize());

	 while(true) {
		 continue;
	 }


}


void dumpEEPROM(unsigned int addr, unsigned int length)
{
	// block to 10
	addr = addr / 10 * 10;
	length = (length + 9)/10 * 10;

	byte b = ee.readByte(addr);
	for (int i = 0; i < length; i++)
	{
		if (addr % 10 == 0)
		{
			Serial.println();
			Serial.print(addr);
			Serial.print(":\t");
		}
		Serial.print(b);
		b = ee.readByte(++addr);
		Serial.print("  ");
	}
	Serial.println();
}
