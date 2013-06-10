// Connect Tests

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link_protocol.h"

char *link_new_device_list(int max);
char *link_device_list_entry(char * list, int entry);
void link_del_device_list(char * sn_list);
extern int link_debug_level;

link_phy_t phyHandle;

void list_devices(void){
	char *deviceList;
	int  max = 10;
	
	deviceList = link_new_device_list(max);
	
	if ( deviceList ){
		int i = 0;
		char *sn;
		while( ( strlen( (sn = link_device_list_entry(deviceList, i)) ) > 0 ) && (i < max) ){
			printf ( "Found device: '%s'\n", sn );
			i++;
		}
		link_del_device_list(deviceList);
	}
}

void list_dir(char *_dir){
	int dirp;
	struct link_dirent entry;
	
	dirp = link_opendir(phyHandle, _dir);
	err = link_readdir_r(phyHandle, dirp, &entry, NULL);
	
	
	err = link_closedir(phyHandle, dirp);
}

int write_file(char *_src, char *_device, char *_dst_dir, int _file){
	FILE *hostFile;
	int flags;
	int deviceFile;
	int progressMax;
	int progress = 0;
	int bytesRead;
	const int bufferSize = 128;
	char buffer[bufferSize];
	int err;
	
	// TODO: SECURITY
	char dst_file[255];
	
	//Open the host file
	hostFile = fopen(_src, "rb");
	if ( hostFile == NULL ){
		printf ( "Could not find file %s on host.\n", _src );
		return -1;
	}
	
	if ( _file == 1 ){
		sprintf(dst_file, "%s/%s", _dst_dir, _src);
	}
	else{
		sprintf(dst_file, "%s", _dst_dir);
	}

	//Create the device file
	//flags = LINK_O_TRUNC | LINK_O_CREAT | LINK_O_WRONLY; //The create new flag settings
	flags = LINK_O_WRONLY;
	deviceFile = link_open(phyHandle, dst_file, flags, 0555);

	fseek(hostFile, 0, SEEK_END);
	progressMax = ftell(hostFile);
	rewind(hostFile);

	if ( deviceFile > 0 ){
		while( (bytesRead = fread(buffer, 1, bufferSize, hostFile)) > 0 ){
			if ( (err = link_write(phyHandle, deviceFile, buffer, bytesRead)) != bytesRead ){
				printf ( "err=%d, bytesRead=%d\n", err, bytesRead);
				printf ("Failed to write to Link device file %d\n", link_errno);
				if ( err > 0 ){
					err = -1;
				}
				break;
			} else {
				progress += bytesRead;
				err = 0;
			}
		}
	} else {
		fclose(hostFile);

		if ( deviceFile == LINK_TRANSFER_ERR ){
			printf ("Connection Failed\n");
			return -2;
		}

		printf("Failed to create file %s on Link device %d\n", dst_file, link_errno);
		return -1;
	}

	fclose(hostFile);

	if ( err == LINK_TRANSFER_ERR ){
		printf ("Connection Failed");
		return -2;
	}

	if ( link_close(phyHandle, deviceFile) ){
		printf("Failed to close Link device file %d", link_errno);
		return -1;
	}

	return err;

}

int main(int argc, char *argv[]){
	
    if (argc <= 1){
    	printf ("Usage: connect {-l | -w [file] [device] [dir]\n");
		return(0);
    }
	
	link_debug_level = 6;
	
	phyHandle = link_connect(_device);
	if ( phyHandle == LINK_PHY_OPEN_ERROR ){
		printf ( "Failed to Connect to CoActionOS\n" );
		return -1;
	}
	
	if ( strcmp(argv[1], "-l")==0 ){
		list_devices();
	}
	
	if ( strcmp(argv[1], "-d")==0 ){
		list_dir(argv[2]);
	}
	
	if ( strcmp(argv[1], "-w")==0 ){
		write_file(argv[2], argv[3], argv[4], 1);
	}
	
	if ( strcmp(argv[1], "-e")==0 ){
		write_file(argv[2], argv[3], "/app/.install", 0);
	}
	
	link_disconnect(phyHandle);
	
	return(0);
}