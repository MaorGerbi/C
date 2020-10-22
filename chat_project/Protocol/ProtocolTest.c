#include <stdio.h>
#include <string.h>
#include "Protocol.h"


typedef enum
{
    PASSED = 0,
    FAILED
} Status;


Status Test_Pack_CheckTag_Request (void); /* Pack and CheckTag Request Test 1 */
Status Test_Pack_CheckTag_Response (void); /* Pack and CheckTag Response Test 2 */


Status Test_UnPack_Request (void); /*UnPack Request Test 3 */
Status Test_Response_UnPack (void); /*UnPack Response Test 4 */


void PrintTest (Status status); /* Print if Test if PASSED or FAILED */



int k;

int main (void)
{
	putchar('\n');
	printf("Pack & CheckTag Tests:\n");
	PrintTest(Test_Pack_CheckTag_Request());
	PrintTest(Test_Pack_CheckTag_Response());

	putchar('\n');
	printf("UnPack Tests:\n");
	PrintTest(Test_UnPack_Request());
	PrintTest(Test_Response_UnPack());

	return 0;
}





/* ---------- Print Function ---------- */

void PrintTest (Status status) /* Print if Test if PASSED or FAILED */
{
	if(PASSED == status)
	{
		printf("Test %d PASSED \n" , ++k);
	}
	else
	{
		printf("Test %d FAILED \n" , ++k);
	}
}



/* ---------- Pack & CheckTag Tests ---------- */

Status Test_Pack_CheckTag_Request (void) /* Pack and CheckTag Request Test 1 */
{
	char tagR, tagIn, tagOut, tagOpen, tagJoin, tagLeave;
	char bufferR[4096], bufferIn[4096], bufferOut[4096], bufferOpen[4096], bufferJoin[4096], bufferLeave[4096];
	size_t sizeR, sizeIn, sizeOut, sizeOpen, sizeJoin, sizeLeave;

	Register_Request reg = {REGISTER_REQUEST , "asaf" , "1122aabb1122"}; /* size = 1 + 5 + 13 = 19 */ 
	Register_Request login = {LOG_IN_REQUEST , "maor" , "3344ccdd4433"}; /* size = 1 + 5 + 13 = 19 */ 
	Logout_Request logout = {LOG_OUT_REQUEST , "ziv" , "2\0group1\0group2"}; /* size = 1 + 4 + 4000 = 4005 */ 
	Group_Request open = {OPEN_GROUP_REQUEST , "team1"}; /* size = 1 + 6 = 7 */ 
	Group_Request join = {JOIN_GROUP_REQUEST , "team22"}; /* size = 1 + 7 = 8 */ 
	Group_Request leave = {LEAVE_GROUP_REQUEST , "teammmm3"}; /* size = 1 + 9 = 10 */ 

	if(PROTOCOL_SUCESS != Protocol_Pack(&reg, bufferR, &sizeR) || sizeR != 20)
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS != Protocol_Pack(&login, bufferIn, &sizeIn) || sizeIn != 20)
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS != Protocol_Pack(&logout, bufferOut, &sizeOut) || sizeOut != 4006)
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS !=Protocol_Pack(&open, bufferOpen, &sizeOpen) || sizeOpen != 8)
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS != Protocol_Pack(&join, bufferJoin, &sizeJoin) || sizeJoin != 9)
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS != Protocol_Pack(&leave, bufferLeave, &sizeLeave) || sizeLeave != 11)
	{
		return FAILED;
	}


	if(PROTOCOL_SUCESS != Protocol_CheckTag(bufferR , &tagR) || tagR != REGISTER_REQUEST)
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS != Protocol_CheckTag(bufferIn , &tagIn) || tagIn != LOG_IN_REQUEST)
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS != Protocol_CheckTag(bufferOut , &tagOut) || tagOut != LOG_OUT_REQUEST)
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS != Protocol_CheckTag(bufferOpen , &tagOpen) || tagOpen != OPEN_GROUP_REQUEST)
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS != Protocol_CheckTag(bufferJoin , &tagJoin) || tagJoin != JOIN_GROUP_REQUEST)
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS != Protocol_CheckTag(bufferLeave , &tagLeave) || tagLeave != LEAVE_GROUP_REQUEST)
	{
		return FAILED;
	}
	return PASSED;
}


Status Test_Pack_CheckTag_Response (void) /* Pack and CheckTag Response Test 2 */
{
	char tagR, tagIn, tagOut, tagOpen, tagJoin, tagNames, tagLeave;
	char bufferR[4096], bufferIn[4096], bufferOut[4096], bufferOpen[4096], bufferJoin[4096], bufferNames[4096], bufferLeave[4096];
	size_t sizeR, sizeIn, sizeOut, sizeOpen, sizeJoin, sizeNames, sizeLeave;

	Register_Response reg = {REGISTER_RESPONSE , 1};  /* size = 3 */ 
	Register_Response login = {LOG_IN_RESPONSE , 1};  /* size = 3 */ 
	Register_Response logout = {LOG_OUT_RESPONSE , 1};/* size = 3 */ 
	Group_Response open = {OPEN_GROUP_RESPONSE , 1,  "225.0.0.1" , "5000", "teamZiv"}; /* size = 3 + 10 + 5 + 8 = 26 */
	Group_Response join = {JOIN_GROUP_RESPONSE , 1, "225.0.0.4" , "5000" , "teamA"}; /* size = 3 + 10 + 5 + 6 = 24 */
	Group_Names_Response allNames = {GROUPS_NAMES_RESPONSE , "3\0aaa\0bbb\0ccc\0"}; /* size = 2 + 4000 = 4002 */
	Group_Response leave = {LEAVE_GROUP_RESPONSE , 1}; /* size = 3 */

	if(PROTOCOL_SUCESS != Protocol_Pack(&reg, bufferR, &sizeR) || sizeR != 3)
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS != Protocol_Pack(&login, bufferIn, &sizeIn) || sizeIn != 3)
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS != Protocol_Pack(&logout, bufferOut, &sizeOut) || sizeOut != 3)
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS !=Protocol_Pack(&open, bufferOpen, &sizeOpen) || sizeOpen != 26)
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS != Protocol_Pack(&join, bufferJoin, &sizeJoin) || sizeJoin != 24)
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS != Protocol_Pack(&allNames, bufferNames, &sizeNames) || sizeNames != 4002)
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS != Protocol_Pack(&leave, bufferLeave, &sizeLeave) || sizeLeave != 3)
	{
		return FAILED;
	}


	if(PROTOCOL_SUCESS != Protocol_CheckTag(bufferR , &tagR) || tagR != REGISTER_RESPONSE)
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS != Protocol_CheckTag(bufferIn , &tagIn) || tagIn != LOG_IN_RESPONSE)
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS != Protocol_CheckTag(bufferOut , &tagOut) || tagOut != LOG_OUT_RESPONSE)
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS != Protocol_CheckTag(bufferOpen , &tagOpen) || tagOpen != OPEN_GROUP_RESPONSE)
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS != Protocol_CheckTag(bufferJoin , &tagJoin) || tagJoin != JOIN_GROUP_RESPONSE)
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS != Protocol_CheckTag(bufferNames , &tagNames) || tagNames != GROUPS_NAMES_RESPONSE)
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS != Protocol_CheckTag(bufferLeave , &tagLeave) || tagLeave != LEAVE_GROUP_RESPONSE)
	{
		return FAILED;
	}
	return PASSED;
}


Status Test_UnPack_Request (void) /*UnPack Request Test 3 */
{
	char bufferR[4096], bufferIn[4096], bufferOut[4096], bufferOpen[4096], bufferJoin[4096], bufferNames[4096], bufferLeave[4096];
	size_t sizeR, sizeIn, sizeOut, sizeOpen, sizeJoin, sizeNames, sizeLeave;


	Register_Request reg = {REGISTER_REQUEST , "asaf" , "1122aabb1122"}, regEmpty;
	Register_Request login = {LOG_IN_REQUEST , "maor" , "3344ccdd4433"}, loginEmpty;
	Register_Request logout = {LOG_OUT_REQUEST , "ziv" , "123ggff321"}, logoutEmpty;
	Group_Request open = {OPEN_GROUP_REQUEST , "team1"}, openEmpty;
	Group_Request join = {JOIN_GROUP_REQUEST , "team22"}, joinEmpty;
	Group_Names_Response names = {GROUPS_NAMES_RESPONSE}, namesEmpty;
	Group_Request leave = {LEAVE_GROUP_REQUEST , "teammmm3"}, leaveEmpty;

	Protocol_Pack(&reg, bufferR, &sizeR);
	Protocol_Pack(&login, bufferIn, &sizeIn);
	Protocol_Pack(&logout, bufferOut, &sizeOut);
	Protocol_Pack(&open, bufferOpen, &sizeOpen);
	Protocol_Pack(&join, bufferJoin, &sizeJoin);
	Protocol_Pack(&names, bufferNames, &sizeNames);
	Protocol_Pack(&leave, bufferLeave, &sizeLeave);

	if(PROTOCOL_SUCESS != Protocol_Unpack(bufferR, &regEmpty) || regEmpty.m_tag != REGISTER_REQUEST || strcmp(regEmpty.m_name,"asaf") || strcmp(regEmpty.m_password,"1122aabb1122"))
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS != Protocol_Unpack(bufferIn, &loginEmpty) || loginEmpty.m_tag != LOG_IN_REQUEST || strcmp(loginEmpty.m_name,"maor") || strcmp(loginEmpty.m_password,"3344ccdd4433"))
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS != Protocol_Unpack(bufferOut, &logoutEmpty) || logoutEmpty.m_tag != LOG_OUT_REQUEST || strcmp(logoutEmpty.m_name,"ziv") || strcmp(logoutEmpty.m_password,"123ggff321"))
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS != Protocol_Unpack(bufferOpen, &openEmpty) || openEmpty.m_tag != OPEN_GROUP_REQUEST || strcmp(openEmpty.m_groupName,"team1"))
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS != Protocol_Unpack(bufferJoin, &joinEmpty) || joinEmpty.m_tag != JOIN_GROUP_REQUEST || strcmp(joinEmpty.m_groupName,"team22"))
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS != Protocol_Unpack(bufferNames, &namesEmpty) || namesEmpty.m_tag != GROUPS_NAMES_RESPONSE)
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS != Protocol_Unpack(bufferLeave, &leaveEmpty) || leaveEmpty.m_tag != LEAVE_GROUP_REQUEST || strcmp(leaveEmpty.m_groupName,"teammmm3"))
	{
		return FAILED;
	}
	return PASSED;
}


Status Test_Response_UnPack (void) /*UnPack Response Test 4 */
{
	char bufferR[4096], bufferIn[4096], bufferOut[4096], bufferOpen[4096], bufferJoin[4096], bufferNames[4096], bufferLeave[4096];
	size_t sizeR, sizeIn, sizeOut, sizeOpen, sizeJoin, sizeNames, sizeLeave;


	Register_Response reg = {REGISTER_RESPONSE , 1}, regEmpty;
	Register_Response login = {LOG_IN_RESPONSE , 0}, loginEmpty;
	Register_Response logout = {LOG_OUT_RESPONSE , 1}, logoutEmpty;
	Group_Response open = {OPEN_GROUP_RESPONSE , 1, "225.0.0.3", "5000", "teamZiv"}, openEmpty;
	Group_Response join = {JOIN_GROUP_RESPONSE , 0, "225.0.0.1", "5000" , "teamA"}, joinEmpty;
	Group_Names_Response names = {GROUPS_NAMES_RESPONSE, "2\0aaa\0bbb"}, namesEmpty;
	Group_Response leave = {LEAVE_GROUP_RESPONSE , 1}, leaveEmpty;

	Protocol_Pack(&reg, bufferR, &sizeR);
	Protocol_Pack(&login, bufferIn, &sizeIn);
	Protocol_Pack(&logout, bufferOut, &sizeOut);
	Protocol_Pack(&open, bufferOpen, &sizeOpen);
	Protocol_Pack(&join, bufferJoin, &sizeJoin);
	Protocol_Pack(&names, bufferNames, &sizeNames);
	Protocol_Pack(&leave, bufferLeave, &sizeLeave);

	if(PROTOCOL_SUCESS != Protocol_Unpack(bufferR, &regEmpty) || regEmpty.m_tag != REGISTER_RESPONSE || regEmpty.m_status != 1)
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS != Protocol_Unpack(bufferIn, &loginEmpty) || loginEmpty.m_tag != LOG_IN_RESPONSE || loginEmpty.m_status != 0)
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS != Protocol_Unpack(bufferOut, &logoutEmpty) || logoutEmpty.m_tag != LOG_OUT_RESPONSE || logoutEmpty.m_status != 1)
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS != Protocol_Unpack(bufferOpen, &openEmpty) || openEmpty.m_tag != OPEN_GROUP_RESPONSE || openEmpty.m_status != 1 || strcmp(openEmpty.m_ipAddress,"225.0.0.3") || strcmp(openEmpty.m_port,"5000") || strcmp(openEmpty.m_groupName,"teamZiv"))
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS != Protocol_Unpack(bufferJoin, &joinEmpty) || joinEmpty.m_tag != JOIN_GROUP_RESPONSE || joinEmpty.m_status != 0 || strcmp(joinEmpty.m_ipAddress,"225.0.0.1") || strcmp(joinEmpty.m_port,"5000") || strcmp(joinEmpty.m_groupName,"teamA"))
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS != Protocol_Unpack(bufferNames, &namesEmpty) || namesEmpty.m_tag != GROUPS_NAMES_RESPONSE || namesEmpty.m_allGroups[0] != '2' || namesEmpty.m_allGroups[1] != '\0' || namesEmpty.m_allGroups[4] != 'a' || namesEmpty.m_allGroups[7] != 'b')
	{
		return FAILED;
	}
	if(PROTOCOL_SUCESS != Protocol_Unpack(bufferLeave, &leaveEmpty) || leaveEmpty.m_tag != LEAVE_GROUP_RESPONSE || leaveEmpty.m_status != 1)
	{
		return FAILED;
	}
	return PASSED;
}



