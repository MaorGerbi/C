#ifndef _MULTICAST_H__
#define _MULTICAST_H__

typedef enum Multicast_Result {
	MULTICAST_SUCESS = 0,
	MULTICAST_PORT_ERR,
	MULTICAST_IP_ERR,
	MULTICAST_FILE_ERR,
	MULTICAST_GENERAL_ERR

} Multicast_Result;

/*description - open 2 windos, 1 window is multicast(that couple of windos can send to it) and in the second window you can right somting and send it to the multicast window.
*this function create a file in a directory that called "Files" then make you have this directory before you ran this
input - _group(the ip addres of the group 224.0.0.0 -239.255.255.255).
	_port(the port number,number from 0 to 64,000).
	_groupName(the name of the group you want to open,dont put any spaces in the name).
	_userName(the name of the user that foing to use this,dont put any spaces in the name).
output - MULTICAST_SUCESS, MULTICAST_FILE_ERR, MULTICAST_PORT_ERR, MULTICAST_GENERAL_ERR
error - MULTICAST_SUCESS(no problems).
	MULTICAST_FILE_ERR(the file could not be open, maybe you didn't created the "Files" directory). 
	MULTICAST_PORT_ERR(the port number isn't a number from 0 to 64000).
	MULTICAST_GENERAL_ERR(there is a general problem,mybe you need to apdate you system).*/
Multicast_Result MulticastCreate(char* _group, int _port, char* _groupName, char* _userName);

/*description - close the multicast windos and the second window that connect to it in your side.
input - _groupName(the name of the group you want to open,dont put any spaces in the name).
	_userName(the name of the user that foing to use this,dont put any spaces in the name).
output - MULTICAST_SUCESS, MULTICAST_IP_ERR, MULTICAST_GENERAL_ERR.
error - MULTICAST_SUCESS(no problems).
	MULTICAST_GENERAL_ERR(there is a general problem,mybe you need to apdate you system).
	MULTICAST_FILE_ERR(the file could not be open).
*/
Multicast_Result MulticastDestroy(char* _groupName, char* _userName);


#endif /* _MULTICAST_H__ */
