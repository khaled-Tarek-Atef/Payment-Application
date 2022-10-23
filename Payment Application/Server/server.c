
#include "server.h"

ST_accountsDB_t accountsDB[255] = { {25000.0,RUNNING,"1234567891234567"},{5000.0,RUNNING,"1234567891234568"},{50000,BLOCKED,"1234567891234569"},{8000,BLOCKED,"1234567891234564"}};
ST_transaction_t server_transaction[255] = { 0 };
int cardIndex;
int transactionNum;
const int accountNumberInDB = 4;
server_dataBase;

EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
	int flag = 1,i;
	for ( i = 0; i < accountNumberInDB; i++)
	{
		flag = strcmp(&cardData->primaryAccountNumber, accountsDB[i].primaryAccountNumber);
		if (flag == 0)
		{
			cardIndex = i;
			return OK_SERVER;
		}
	}
		return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_cardData_t* cardData)
{
	int flag = 1;
	for (int i = 0; i < accountNumberInDB; i++)
	{
		flag = strcmp(cardData->primaryAccountNumber, accountsDB[i].primaryAccountNumber);
		if (flag == 0)
		{
			cardIndex = i;
		}
	}
	if (termData->transAmount > accountsDB[cardIndex].balance)
	{
		return LOW_BALANCE;
	}
	else
	{
		return OK_SERVER;
	}
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	if (accountRefrence[cardIndex].state == RUNNING)
	{
		return OK_SERVER;
	}
	else
	{
		return BLOCKED_ACCOUNT;
	}
}


EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	if (transactionNum == 255)        
	{
		return SAVING_FAILED;
	}
	else
	{
		server_transaction[transactionNum].cardHolderData = transData->cardHolderData;
		server_transaction[transactionNum].terminalData = transData->terminalData;
		server_transaction[transactionNum].transactionSequenceNumber = transactionNum + 12345;
		server_transaction[transactionNum].transState = recieveTransactionData(&transData) == 0 ? APPROVED : recieveTransactionData(transData);
		transactionNum++;
		accountsDB[cardIndex].balance = accountsDB[cardIndex].balance - transData->terminalData.transAmount;
		return OK_SERVER;
	}
}

void listSavedTransactions(void)
{
	printf("\n\n##################################\n");
	printf("Transaction Sequence Number: %d\n", server_transaction[transactionNum-1].transactionSequenceNumber);
	printf("Transaction Date: %s\n", server_transaction[transactionNum-1].terminalData.transactionDate);
	printf("Transaction Amount: %f\n", server_transaction[transactionNum - 1].terminalData.transAmount);
	if(server_transaction[transactionNum - 1].transState== APPROVED)
	    printf("Transaction State: APPROVED\n");
	else if (server_transaction[transactionNum - 1].transState == DECLINED_INSUFFECIENT_FUND)
		printf("Transaction State: DECLINED_INSUFFECIENT_FUND\n");
	else if (server_transaction[transactionNum - 1].transState == DECLINED_STOLEN_CARD)
		printf("Transaction State: DECLINED_STOLEN_CARD\n");
	else if (server_transaction[transactionNum - 1].transState == FRAUD_CARD)
		printf("Transaction State: FRAUD_CARD\n");
	else if (server_transaction[transactionNum - 1].transState == INTERNAL_SERVER_ERROR)
		printf("Transaction State: INTERNAL_SERVER_ERROR\n");
	printf("Terminal Max Amount: %f\n", accountsDB[cardIndex].balance);
	printf("Card Expiration Date: %s\n", server_transaction[cardIndex].cardHolderData.cardExpirationDate);
	printf("##################################\n");
}
EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	int card_index;
	if (isValidAccount(&transData->cardHolderData) == ACCOUNT_NOT_FOUND)
	{
		return FRAUD_CARD;
	}
	if (isAmountAvailable(&transData->terminalData, &transData->cardHolderData) == LOW_BALANCE)
	{
		return DECLINED_INSUFFECIENT_FUND;
	}
	if (isBlockedAccount(&accountsDB) == BLOCKED_ACCOUNT)
	{
		return DECLINED_STOLEN_CARD;
	}	
	return APPROVED;	
}