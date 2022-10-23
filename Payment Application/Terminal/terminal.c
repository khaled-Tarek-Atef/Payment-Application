
#include "terminal.h"
#include "../Server/server.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	printf("please enter date in DD/MM/YYYY form : ");
	gets(&termData->transactionDate);
	int i, length;
	length = string_length(&termData->transactionDate);
	if (length == 10)
	{
		for (i = 0; i < length; i++)
		{
			if (termData->transactionDate[i] >= '0' && termData->transactionDate<='9')
			{
			}
			else if (termData->transactionDate[2] == '/' && termData->transactionDate[5] == '/')
			{

			}
			else
			{
				return WRONG_DATE;
			}
		}
		char dd[3] = { termData->transactionDate[0],termData->transactionDate[1],0 };
		char mm[3] = { termData->transactionDate[3],termData->transactionDate[4],0 };
		char yy[5] = { termData->transactionDate[6],termData->transactionDate[7],termData->transactionDate[8],termData->transactionDate[9],0 };
		int DD, MM, YY;
		DD = atoi(dd);
		MM = atoi(mm);
		YY = atoi(yy);
		if (MM <= 12 && YY>=2022)
		{
			if (MM == 1 || MM == 3 || MM == 5 || MM == 7 || MM == 8 || MM == 10 || MM == 12)
			{
				if(DD>31 || DD<1)
					return WRONG_DATE;
			}
			else if (MM == 2)
			{
				if (DD > 28 || DD < 1)
					return WRONG_DATE;
			}
			else
			{
				if (DD > 30 || DD < 1)
					return WRONG_DATE;
			}	
		}
		else
		{
			return WRONG_DATE;
		}
		return OKK;
	}
	else
	{
		return WRONG_DATE;
	}
}


EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{	
	int DD, MM, YY,M,Y;
	char dd[3] = { termData.transactionDate[0],termData.transactionDate[1],0 };
	char mm[3] = { termData.transactionDate[3],termData.transactionDate[4],0 };
	char yy[5] = { termData.transactionDate[6],termData.transactionDate[7],termData.transactionDate[8],termData.transactionDate[9],0 };
	DD = atoi(dd);
	MM = atoi(mm);
	YY = atoi(yy);
	char m[3] = { cardData.cardExpirationDate[0],cardData.cardExpirationDate[1],0 };
	char y[3] = { cardData.cardExpirationDate[3],cardData.cardExpirationDate[4],0 };
	M = atoi(m);
	Y = atoi(y);
	Y = Y + 2000;
	if (Y > YY)
	{
		return OKK;
	}
	else if(Y==YY)
	{
		if (M > MM)
		{
			return OKK;
		}
		else
		{
			return EXPIRED_CARD;
		}
	}
	else
	{
		return EXPIRED_CARD;
	}
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	printf("please enter the transaction amount :");
	scanf_s("%f", &termData->transAmount);
	if (termData->transAmount <=0)
	{
		return INVALID_AMOUNT;
	}
	else
	{
		return OKK;
	}
	
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if (termData->maxTransAmount >= termData->transAmount)
	{
		return OKK;
	}
	else
	{
		return  EXCEED_MAX_AMOUNT;
	}
}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	//printf("please enter the max amount :");             // if you want user enter the  MaxAmount remove comment from 127 & 128
	//scanf_s("%f", &termData->maxTransAmount);            // and put comment on 129
	termData->maxTransAmount = 10000;                    // let max amount is 20000LE 
	if (termData->maxTransAmount <= 0)
	{
		return INVALID_MAX_AMOUNT;
	}
	else
	{
		return OKK;
	}
}

