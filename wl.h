// wear_leveling.h

#ifndef _WEAR_LEVELING_h
#define _WEAR_LEVELING_h


// ID of the settings block
#define WL_VERSION "WL"

struct WL_Header
{
	char headerMark[2];
	unsigned int n_recs;
	unsigned int rec_size;
	unsigned long mem_size;
};


typedef enum WL_Status {
	WL_OK,
	WL_OUT_OF_RANGE,
	WL_NOK
};

typedef enum WL_Size {
	WL_8 = 0,
	WL_16,
	WL_24,
	WL_32 ,
	WL_64
} wlSize;

const uint8_t WL_ByteSize_Ordinals[] = {1, 2, 3, 4, 8};
const uint8_t WL_Size_Ordinals[] = {8, 16, 24, 32, 64};

typedef uint8_t* WL_Rec;

#define WL_REC (byte*)(void*)&


class wl
{
	
 public:
	 typedef void WL_Write_Handler(unsigned long, const uint8_t);
	 typedef uint8_t WL_Read_Handler(unsigned long);
 
 	
 private:
	unsigned long WL_head_ptr;
	unsigned long WL_status_buffer_ptr;
	unsigned long WL_param_buffer_ptr;
	WL_Write_Handler *_write_byte;
	WL_Read_Handler *_read_byte;	 
	WL_Header WL_head;

 public:

    wl(WL_Write_Handler *, WL_Read_Handler *);
	WL_Status exists(unsigned long);
	WL_Status create(unsigned long, WL_Size, unsigned int);
	
	WL_Status open(unsigned long);
	WL_Status readRec(WL_Rec);
	WL_Status writeRec(const WL_Rec);


	
	unsigned long memSize();
	unsigned long count();
	void clear();
		
  private:
	    void wlWrite(unsigned long ee, const uint8_t* p, unsigned int);
	    void wlRead(unsigned long ee, uint8_t* p, unsigned int);
	    void writeHead();
	    void readHead();
		
		
		
		uint8_t findCurrentEepromAddr();
		uint8_t getNextEepromAddr();
		void readBuffer();
		void WriteBuffer();
};

extern wl WEAR_LEVELING;

#endif

