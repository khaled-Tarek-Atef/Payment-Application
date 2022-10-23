#include "card.h"

int string_length(char* str)
{
    int i;
    for (i = 0; str[i]; i++)
    {
    }
    return i;
}
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
    printf("please enter Card Holder Name: ");
	gets( &cardData->cardHolderName);
    int name_length;
    
    name_length=string_length(&cardData->cardHolderName);
    for (int i = 0; i < name_length; i++)
    {
        if ((cardData->cardHolderName[i] >= 'a' && cardData->cardHolderName[i] <= 'z') || (cardData->cardHolderName[i] >= 'A' && cardData->cardHolderName[i] <= 'Z') || cardData->cardHolderName[i] == ' ')
        {

        }
        else
        {
            return WRONG_NAME;
        }
    }

    if (name_length >= 20 && name_length <= 24)
    {
        return OK;
    }
    else
    {
        return WRONG_NAME;
    }
}
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
    int length, i;
    printf("please enter card PAN : ");
    gets(&cardData->primaryAccountNumber);
    length = string_length(&cardData->primaryAccountNumber);
    if (length <= 19 && length >= 16)
    {

        for (i = 0; i < length; i++)
        {
            if (cardData->primaryAccountNumber[i] < '0' || cardData->primaryAccountNumber[i]>'9')
            {
                return WRONG_PAN;
            }
        }
        return OK;
    }
    else
    {
        return WRONG_PAN;
    }
}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
    int length;
    printf("please enter card expiry date in MM/YY form : ");
    gets(&cardData->cardExpirationDate);
    length = string_length(&cardData->cardExpirationDate);
    if (length == 5)
    {        
        for (int i = 0; i < 5; i++)
        {
            if (cardData->cardExpirationDate[i] >= '0' && cardData->cardExpirationDate[i] <= '9')
            {
                if (cardData->cardExpirationDate[0] > '1')
                {
                    return WRONG_EXP_DATE;
                }
                if (cardData->cardExpirationDate[0] == '1')
                {
                    if(cardData->cardExpirationDate[1]>'2')
                    {    
                        return WRONG_EXP_DATE;
                    }
                }
            }
             if(cardData->cardExpirationDate[2]!='/')
            {
                return WRONG_EXP_DATE;
            }                 
        }
        return OK;
    }
    else
    {
        return WRONG_EXP_DATE;
    }
}


