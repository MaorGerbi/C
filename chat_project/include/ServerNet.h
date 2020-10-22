#ifndef __SERVER_NET_H__
#define __SERVER_NET_H__

#include <sys/types.h> /* size_t */

typedef struct ServerNet ServerNet;

#define BUFFER_SIZE 4096

typedef enum ServerN_Result {
	SERVER_SUCCESS = 0,
	SERVER_ACCEPT_FAILED,
	SERVER_SEND_FAILED,
	SERVER_SELECT_FAILED,
	SERVER_ALLOCATION_ERROR
} ServerN_Result;


typedef void (*New_Client)(int _client_sock, void* _context);
typedef void (*Got_Message)(int _client_sock, void* _inMsg, void*_context);
typedef void (*Close_Client)(int _client_sock, void* _context);
typedef void (*Fail)(int _client_sock, void* _context);


/**
 * @brief Function dynamically creates a new ServerNet ADT of a given pointers to functions.
 *
 * @param[in] New_Client - Function to act when new client is connects.
 * @param[in] Got_Msg - Function to act when new message is received.
 * @param[in] Close_Client - Function to act when one of the clients closed his socket.
 * @param[in] Fail - Function to act when one the server failed to receive with one of the clients.
 *
 * @return ServerNet* on success / NULL on fail
 */
ServerNet* ServerNet_Create(New_Client _newC, Got_Message _gotM, Close_Client _closeC, Fail _fail);


/**
 * @brief The function Starts running the ServerNet that created by ServerNet_Create. The server wait for new clients or for message from exist clients, and respond with the function it gets in the ServerNet_Create. 
 *
 * @param[in] _server - a server to be run.
 * @param[in] _context - parameter to be send to functions "New_Client" , "Got_Message", "Close_Client", "Fail".
 *
 * @return success or error code
 * @return SERVER_SUCCESS on success
 * @return SERVER_SELECT_FAILED if the select function was failed.
 * @return SERVER_ALLOCATION_ERROR when no memory available.
 */
ServerN_Result ServerNet_Run( ServerNet* _server, void* _context);


/**
 * @brief The function send back to the client (the last client that sent a msg) a protocol message.
 *
 * @param[in] _sock_client - a client socket to send the message.
 * @param[in] _message - message that packed by Proto_Pack() function.
 * @param[in] _msgSize - size of the message.
 *
 * @return success or error code
 * @return SERVER_SUCCESS on success
 * @return SERVER_SEND_FAILED if the message was not sent.
 */
ServerN_Result ServerNet_Send (int _sock_client, void* _message, size_t _msgSize);


/**
 * @brief The function pause the ServerNet running. 
 *
 * @param[in] _server - server to be paused.
 *
 * @return return the amout of existing clients.
 */
size_t ServerNet_Pause (ServerNet *_server);


/**
 * @brief Dynamically deallocates a previously allocated ServerNet.
 *
 * @params[in] _server - A pointer to previously created ServerNet returned via ServerNet_Create
 */
void ServerNet_Destroy (ServerNet **_server);


#endif /* __SERVER_NET_H__ */
