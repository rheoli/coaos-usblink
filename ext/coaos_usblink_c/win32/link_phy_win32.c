/*
 * link_phy_posix.c
 *
 *  Created on: Oct 6, 2012
 *      Author: tgil
 */


#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>
#include <limits.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "../link_flags.h"


#define COM_PORT_NAME "\\\\.\\COM"
#define COM_PORT_MAX 64


int link_phy_getname(char * dest, const char * last, int len){
	int com_port;
	char buffer[12];


	if( strlen(last) == 0 ){
		com_port = 0;
		sprintf(dest, "%s%d", COM_PORT_NAME, com_port);
		return 0;
	} else {
		com_port = 0;
		do {
			sprintf(buffer, "%s%d", COM_PORT_NAME, com_port++);
			if( strcmp(buffer, last) == 0 ){
				break;
			}
		} while(com_port < COM_PORT_MAX);
		if( com_port > (COM_PORT_MAX-1) ){
			return LINK_PHY_ERROR;
		}
	}


	sprintf(buffer, "%s%d", COM_PORT_NAME, com_port);
	strcpy(dest, buffer);

	return 0;
}


link_phy_t link_phy_open(const char * name, int baudrate){

	link_phy_t handle;
	DCB params;

	handle = CreateFile(name, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if( handle == INVALID_HANDLE_VALUE ){
		return LINK_PHY_OPEN_ERROR;
	}

	if( !GetCommState(handle, &params) ){
		CloseHandle(handle);
		return LINK_PHY_OPEN_ERROR;
	}

	/*
	params.BaudRate = CBR_19200;
	params.ByteSize = 8;
	params.StopBits = ONESTOPBIT;
	params.Parity = EVENPARITY;


	if ( !SetCommState(handle, &params)){
		CloseHandle(handle);
		return LINK_PHY_OPEN_ERROR;
	}
	*/


	COMMTIMEOUTS timeouts={0};
	timeouts.ReadIntervalTimeout=MAXDWORD;
	timeouts.ReadTotalTimeoutConstant=1;
	timeouts.ReadTotalTimeoutMultiplier=0;
	timeouts.WriteTotalTimeoutConstant=0;
	timeouts.WriteTotalTimeoutMultiplier=0;
	if(!SetCommTimeouts(handle, &timeouts)){
	//error occurred. Inform user
	}

	return handle;
}

int link_phy_write(link_phy_t handle, const void * buf, int nbyte){
	DWORD bytes_written;
	if( !WriteFile(handle, buf, nbyte, &bytes_written, NULL) ){
		return LINK_PHY_ERROR;
	}
	return bytes_written;
}

int link_phy_read(link_phy_t handle, void * buf, int nbyte){
	DWORD bytes_read;
	if( !ReadFile(handle, buf, nbyte, &bytes_read, NULL) ){
		return LINK_PHY_ERROR;
	}
	return bytes_read;
}

int link_phy_close(link_phy_t handle){
	CloseHandle(handle);
	return 0;
}

void link_phy_wait(int msec){
	Sleep(msec);
}

void link_phy_flush(link_phy_t handle){
	char c;
	while( link_phy_read(handle, &c, 1) == 1 ){
		;
	}
}


