#!/usr/bin/env ruby

require 'bundler'
Bundler.require

TTY_DEV_PREFIX = "tty.usbmodem"

def link_phy_getname(_dest="", _last="", _len=0)
  entries=[]
  Dir.open("/dev").each do |entry|
    if entry=~/#{TTY_DEV_PREFIX}/
      entries<<entry
    end
  end
  entries
end


def link_phy_open(_name, _baudrate)
  fd = IO.open("/dev/#{_name}", O_RDWR | O_NOCTTY | O_NONBLOCK)
  fd.ioctl(TIOCEXCL)
end

link_phy_t link_phy_open(const char * name, int baudrate){
	char path[PATH_MAX];
	link_phy_t fd;
	struct termios options;

	//build the path
	strcpy(path, "/dev/");
	strcat(path, name);

	//open serial port
	fd = open(path, O_RDWR | O_NOCTTY | O_NONBLOCK);
	if( fd < 0 ){
		link_error("Failed to open %s\n", name);
		return LINK_PHY_ERROR;
	}

	if( ioctl(fd, TIOCEXCL) == -1 ){
		link_error("failed to make device exclusive\n");
		return -1;
	}

	memset(&options, 0, sizeof(options));

	if( tcgetattr(fd, &options) < 0 ){
		link_error("failed to get options\n");
		return LINK_PHY_ERROR;
	}

	//make the buffer raw
	cfmakeraw(&options); //raw with no buffering

	//115200 baud
	cfsetispeed(&options, B230400);
	cfsetospeed(&options, B230400);
	//even parity
	//8 bit data
	//one stop bit
	options.c_cflag |= PARENB; //parity on
	options.c_cflag &= ~PARODD; //parity is not odd
	options.c_cflag &= ~CSTOPB; //one stop bit
	options.c_cflag |= CREAD; //enable receiver
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CLOCAL | CS8;  //8 bit data

	//set the attributes
	if( tcsetattr(fd, TCSANOW|TCSAFLUSH, &options) < 0 ){
		return LINK_PHY_ERROR;
	}

	link_phy_flush(fd);

	return fd;
}


def link_new_device_list(_max=nil)
	handle = link_phy_open(name, 0);
	if( handle != LINK_PHY_OPEN_ERROR ){
		if( link_readserialno(handle, serialno, 256) == 0 ){
			strcpy(&(sn_list[256*cnt]), serialno);
			cnt++;
			if( cnt == max ){
				return sn_list;
			}
		}
		link_phy_close(handle);
end

p link_phy_getname

__END__

int link_phy_getname(char * dest, const char * last, int len){
	//lookup the next eligible device
	struct dirent entry;
	struct dirent * result;
	DIR * dirp;
	int pre_len;
	bool past_last;

	dirp = opendir("/dev");
	if( dirp == NULL ){
		return LINK_PHY_ERROR;
	}

	pre_len = strlen(TTY_DEV_PREFIX);
	past_last = false;
	if( strlen(last) == 0 ){
		past_last = true;
	}
	while( (readdir_r(dirp, &entry, &result) == 0) && (result != NULL) ){
		if( strncmp(TTY_DEV_PREFIX, entry.d_name, pre_len) == 0 ){
			//the entry matches the prefix
			if( past_last == true ){
				if( strlen(entry.d_name) > len ){
					//name won't fit in destination
					closedir(dirp);
					return LINK_PHY_ERROR;
				}

				strcpy(dest, entry.d_name);
				closedir(dirp);
				return 0;
			} else if( strcmp(last, entry.d_name) == 0 ){
				past_last = true;
			}
		}
	}

	//no more entries to be found
	closedir(dirp);
	return LINK_PHY_ERROR;
}


link_new_device_list:
while ( (err = link_phy_getname(name, last, LINK_PHY_NAME_MAX)) == 0 ){
	//success in getting new name
	handle = link_phy_open(name, 0);
	if( handle != LINK_PHY_OPEN_ERROR ){
		if( link_readserialno(handle, serialno, 256) == 0 ){
			strcpy(&(sn_list[256*cnt]), serialno);
			cnt++;
			if( cnt == max ){
				return sn_list;
			}
		}
		link_phy_close(handle);
	}
	strcpy(last, name);
}

list_devices:
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