#ifndef __Client_Net_H__
#define __Client_Net_H__

typedef struct ClientN ClientN;

typedef enum ClientN_Status{
	CLIENT_NET_SUCCESS,
	CLIENT_NET_UNINITIALZED,
	CLIENT_NET_CONECT_FAIL,
	CLiENT_NET_ALLOC_FAIL,
	CLIENT_NET_INVALID_PORT,
    CLIENT_NET_RECIEVE_FAIL,
    CLIENT_NET_SEND_FAIL
	}ClientN_Status;	
	
/*	
discription - Create new CLientN
input	 	- _DestIp: destination ip
		      _port  : server port number
output      - pointer to new ClientN, NULL for error 
error       - none  
*/

ClientN* ClientN_Create(char* _DestIp, int _port);

/*
discription - Disconnect from server and free alloc memory
input       - _ClientN  to Destroy
output      - none
error       - none 
*/

void ClientN_Destroy(ClientN** _clientN);

/*	
discription - Create TCP conection with required server
input	 	- _clientN: pointer to Client
output      - Status CLIENT_NET_SUCCES, error 
error       - CLIENT_NET_UNINITIALZED, CLIENT_NET_CONECT_FAIL
*/

ClientN_Status ClientN_Connect(ClientN* _clientN);

/*
discription - Send data from client by TCP conection
input       - _clientN: pointer that include soket number
              _data   : buffer that storage message
              _len    : data length
output      - Status CLIENT_NET_SUCCES , ERR
error       - CLIENT_NET_UNINITIALZED, CLIENT_NET_SEND_FAIL  
 */

ClientN_Status ClientN_Send(ClientN* _clientN, char* _data, size_t _len);

/*
discription - Recieve data from server by TCP conection
input       - _clientN  : pointer that include soket number
              _buffer   : buffer to storage incoming message
              _bufferLen: length of buffer
output      - Status CLIENT_NET_SUCCES, ERR
error       - CLIENT_NET_UNINITIALZED, CLIENT_NET_RECIEVE_FAIL   
*/

ClientN_Status ClientN_Recieve(ClientN* _clientN, char* buffer, size_t _bufferLen);

/*
discription - return sock number
input       - _client: pointer to struct  
output      - int sock number,(-1) for ERR
error       - none
*/
int ClientN_GetSock(ClientN* _clientN);

#endif /*__Client_Net_H__*/
