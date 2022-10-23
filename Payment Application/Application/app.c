#include "app.h"

void appStart(void)
{
	char c;
	while (1)
	{
		while (getCardHolderName(&client.cardHolderData) == WRONG_NAME)
		{
			printf("Please enter right name \n");
		}

		while (getCardExpiryDate(&client.cardHolderData) == WRONG_EXP_DATE)
		{
			printf("Please enter right expiration date\n");
		}
		while (getCardPAN(&client.cardHolderData) == WRONG_PAN)
		{
			printf("Please enter right Card Pan\n");
		}
		while (getTransactionDate(&client.terminalData) == WRONG_DATE)
		{
			printf("Please enter right Date\n");
		}

		if (isCardExpired(client.cardHolderData, client.terminalData) == EXPIRED_CARD)
		{
			printf("sorry the card is expired\nPress any key to restart");
			getch();
			system("cls");
			continue;
		}
		while (getTransactionAmount(&client.terminalData) == INVALID_AMOUNT)
		{
			printf("please enter a valid amount of transation\n");
		}

		setMaxAmount(&client.terminalData);

		if (isBelowMaxAmount(&client.terminalData) == EXCEED_MAX_AMOUNT)
		{
			printf("Eceeded maximum amount\nPress any key to restart");
			getch(); 
			system("cls"); 
			scanf_s("%c", &c);   // to take the entered key form the buffer
			continue;
		}
		receive_OUT = recieveTransactionData(&client);
		if (receive_OUT == DECLINED_INSUFFECIENT_FUND) 
		{
			printf("Declined insuffecient funds\nPress any key to restart");
			getch(); 
			system("cls"); 
			scanf_s("%c", &c);   // to take the entered key form the buffer
			continue;
		}
		if (receive_OUT == FRAUD_CARD)
		{
			printf("Declined invalid account\nPress any key to restart"); 
			getch(); 
			system("cls");
			scanf_s("%c", &c);   // to take the entered key form the buffer
			continue;
		}
		if (receive_OUT == APPROVED)
		{
			printf("The transaction is approved\n");
		}
		if (receive_OUT == DECLINED_STOLEN_CARD)
		{
			printf("The account is Blocked\nPress any key to restart");
			getch();
			system("cls");
			scanf_s("%c", &c);   // to take the entered key form the buffer
			continue;
		}

		transaction_status =saveTransaction(&client);
		if (transaction_status == SAVING_FAILED) {
			printf("Saveing is failed \nPress any key to restart");
			getch(); 
			system("cls"); 
			scanf_s("%c", &c);   // to take the entered key form the buffer
			continue;
		}
		else {
			printf("The transaction is saved\n");
			listSavedTransactions();                           // print receipt 
			printf("Press any key to restart");
			getch(); 
			system("cls");
			scanf_s("%c", &c);    // to take the entered key form the buffer
		}
	}
}