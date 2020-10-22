/**************************************************************************************
    Author        : Maor Gerbi
    Description   : ADT General definitions.
***************************************************************************************/
#ifndef __ADTDEFS_H__
#define __ADTDEFS_H__

typedef enum
{
    /* General ADT Errors */
    ERR_OK = 0,                         
    ERR_GENERAL,
    ERR_NOT_INITIALIZED,
    ERR_ALLOCATION_FAILED,
    ERR_REALLOCATION_FAILED,
    ERR_UNDERFLOW,
    ERR_OVERFLOW,
    ERR_WRONG_INDEX,
    ERR_NOT_FAOUND,

    /* Vector Errors */

    /* Stack  Errors */
    ERR_STACK_BLABLABLA = 15
    /* LinkedList  Errors */

    /* Bit Vector*/


} ADTErr;

void HandleErr(ADTErr errNum, char *msg);

#endif /*__ADTDEFS_H__*/
