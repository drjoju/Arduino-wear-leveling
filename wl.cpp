// 
// 
// 
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "wl.h"


/**************************************************/
// private functions

// low level byte write
void wl::wlWrite(unsigned long ee, const byte* p, unsigned int recsize)
{
	for (unsigned int i = 0; i < recsize; i++)
	_write_byte(ee++, *p++);
}

// low level byte read
void wl::wlRead(unsigned long ee, byte* p, unsigned int recsize)
{
	for (unsigned i = 0; i < recsize; i++)
	*p++ = _read_byte(ee++);
}

// writes WL_Header
void wl::writeHead()
{
	wlWrite(WL_head_ptr, WL_REC WL_head, (unsigned long)sizeof(WL_Header));
}

// reads WL_Header
void wl::readHead()
{
	wlRead(WL_head_ptr, WL_REC WL_head, (unsigned long)sizeof(WL_Header));
}


/**************************************************/
// public functions
wl::wl(WL_Write_Handler *w, WL_Read_Handler *r)
{
	_write_byte = w;
	_read_byte = r;
}


// reads an existing wl header and sets header values
WL_Status wl::exists(unsigned long head_ptr)
{
	WL_head_ptr = head_ptr;
	readHead();
	// IS "WL"? 
	if(WL_head.headerMark[0]==WL_VERSION[0] && WL_head.headerMark[1]==WL_VERSION[1])
		return WL_OK;
	else
		return WL_NOK;
}


// creates a new var and sets header values
WL_Status wl::create(unsigned long head_ptr, WL_Size num_recs, unsigned int recsize)
{
	WL_head_ptr = head_ptr;
	WL_status_buffer_ptr = WL_head_ptr + sizeof(WL_Header) ;
	WL_param_buffer_ptr = WL_status_buffer_ptr + (WL_ByteSize_Ordinals[num_recs]*sizeof(byte));
	sprintf(WL_head.headerMark, WL_VERSION);
	WL_head.n_recs = num_recs;
	WL_head.rec_size = recsize;
	WL_head.mem_size = sizeof(WL_Header) + (WL_ByteSize_Ordinals[WL_head.n_recs]*sizeof(byte)) + (WL_head.rec_size*WL_Size_Ordinals[WL_head.n_recs]);
	writeHead();
	return WL_OK;
}



// reads an existing wl header at a given address and sets header values
WL_Status wl::open(unsigned long head_ptr)
{
	WL_head_ptr = head_ptr;
	readHead();
	WL_status_buffer_ptr = WL_head_ptr + sizeof(WL_Header) ;
	WL_param_buffer_ptr = WL_status_buffer_ptr + (WL_ByteSize_Ordinals[WL_head.n_recs]*sizeof(byte));
	
	return WL_OK;
}

// writes a record
WL_Status wl::writeRec(const WL_Rec rec)
{
	uint8_t currentPos = getNextEepromAddr();
	
	wlWrite(WL_param_buffer_ptr + (currentPos * WL_head.rec_size), rec, WL_head.rec_size);
	return WL_OK;
}

// reads a record
WL_Status wl::readRec(WL_Rec rec)
{
	uint8_t currentPos = findCurrentEepromAddr();
	
	wlRead(WL_param_buffer_ptr + (findCurrentEepromAddr() * WL_head.rec_size), rec, WL_head.rec_size);
	return WL_OK;
}



// returns the number of queued items
unsigned long wl::count()
{
	return WL_Size_Ordinals[WL_head.n_recs];
}

// returns the complete memory size
unsigned long wl::memSize()
{
	return WL_head.mem_size;
}

// truncates the queue by resetting the internal pointers
void wl::clear()
{
	readHead();
	
	unsigned long mem_size = (WL_Size_Ordinals[WL_head.n_recs]*WL_head.rec_size); 
	unsigned long ee = WL_param_buffer_ptr;
	for (unsigned int i = 0; i < mem_size; i++)
		_write_byte(ee++, 0);
		

	 mem_size = WL_ByteSize_Ordinals[WL_head.n_recs];
	 ee = WL_status_buffer_ptr;
	 for (unsigned int i = 0; i < mem_size; i++)
	 _write_byte(ee++, 0xFF);
	
	
}

uint8_t wl::findCurrentEepromAddr()
{
	 uint8_t currentPos = 0;
	 byte statusRec = 0;
	 uint8_t maxBytes = WL_ByteSize_Ordinals[WL_head.n_recs];
	 
	 for(int i=0;i<maxBytes;i++)
	 {
		 wlRead(WL_status_buffer_ptr + i, WL_REC statusRec, sizeof(byte));
		 
		 uint8_t mask = 0b10000000;
		 for(int j=0;j<8;j++)
		 {
			 if((mask & statusRec) == mask) break;
			 mask>>=1;
			 currentPos++;
		 }
		 
	 }
	 
	 return currentPos;
}

uint8_t wl::getNextEepromAddr()
{
	uint8_t currentPos = 0;
	byte statusRec = 0;
	uint8_t maxBytes = WL_ByteSize_Ordinals[WL_head.n_recs];
	
	int i;
	bool stop = false;
	for(i=0;i<maxBytes;i++)
	{
		wlRead(WL_status_buffer_ptr + i, WL_REC statusRec, sizeof(byte));
		
		uint8_t mask = 0b10000000;
		for(int j=0;j<8 && !stop;j++)
		{
			if((mask & statusRec) == mask) 
			{
				stop = true;
				break;
			}

			mask>>=1;
			currentPos++;
		}
		if(stop) break;
	}
	
	if((currentPos+1)>=WL_Size_Ordinals[WL_head.n_recs])
	{
		unsigned long mem_size = WL_ByteSize_Ordinals[WL_head.n_recs];
		unsigned long ee = WL_status_buffer_ptr;
		for (unsigned int i = 0; i < mem_size; i++)
		_write_byte(ee++, 0xFF);
		currentPos = 0;		
	}
	else
	{
		wlRead(WL_status_buffer_ptr + i, WL_REC statusRec, sizeof(byte));
		statusRec>>=1;
		wlWrite(WL_status_buffer_ptr + i, WL_REC statusRec, sizeof(byte));
		currentPos ++; 
	}
	
	return currentPos;
}