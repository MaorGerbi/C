#include <stdio.h> /*print*/
#include <stdlib.h>
#include <string.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"

/*
discription - print open screen
input       - none
output      - none
error       - none
*/
void UI_OpenScreen();

/*
discription - print start menu
input       - none
output      - none
error       - none
*/
void UI_StartMenu();

/*
discription - print log in menu
input       - none
output      - none
error       - none
*/
void UI_LoginMenu();

/*
discription - print menue for client in group
input       - none
output      - none
error       - none
*/
void UI_GroupMenu();

/*
discription - login form
input       - _name    : sorage name from user
              _password: storage password from user
output      - none
error       - none
*/
void UI_Login(char* _name, char* _password);

/*
discription - register form
input       - _name    : sorage name from user
              _password: storage password from user
output      - none
error       - none
*/
void UI_Register(char* _name, char* _password);

void UI_Err();

void UI_OK();
