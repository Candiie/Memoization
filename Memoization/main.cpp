
#include<iostream>

using namespace std;

#define NUMOFCOINS_DENOM_INFO 3
#define MAX_N 100
#define MAX_WEIGHT 10000


class Coin {

	public:

		//attributes
		int value;
		int weight;

		//public functions
		Coin()
		{
			value = 0;
			weight = 0;
		}

		Coin(int v, int w) {
			value = v;
			weight = w;
		}
};

//Init coin values
Coin* c1 = new Coin(1,10);
Coin* c2 = new Coin(2,20);
Coin* c3 = new Coin(3,30);

//Assuming Value and Weights are sorted from lowest value to highest value are input and stored in a table
Coin* coinsInfo[NUMOFCOINS_DENOM_INFO] = { c1, c2, c3 };


//Table for memoization - assiume max no. of n and max weight 
int cachedSavings [MAX_N][MAX_WEIGHT] = {0};

//Declaring prototype 
int computeMinSavings (int n , int weight);


void main (void) {
	
	

	//Input from User
	int inN = 4;
	int inWeight = 60;

	cout << computeMinSavings(inN, inWeight) << endl;

}


int computeMinSavings (int n , int weight){

	int minCalcSavings = 0; //mininum calculated savings
	int coinInfoCounter = 0;
	int tempWeight = weight;
	int coinsUsed = 0;


	while (coinsUsed <= n) {

		if(tempWeight == 0) {
			break;
		}

		if ( ( (tempWeight - coinsInfo[coinInfoCounter]->weight) > 0 ) && ( (coinsUsed + 1) >= n) ) {
			coinInfoCounter += 1;
			continue; //move on to next loop
		}

		if( ( (tempWeight - coinsInfo[coinInfoCounter]->weight) >= 0 ) && ( (coinsUsed + 1) <= n)) {

			tempWeight -= coinsInfo[coinInfoCounter]->weight; //Lols! tempWeight /= coinsInfo[coinInfoCounter]->weight;
			minCalcSavings += coinsInfo[coinInfoCounter]->value;
			coinsUsed += 1;
		}
		//If number of coinsUser is still within given no. of coins increase coinCounter to use next type of coin
		/*else if (( tempWeight - coinsInfo[coinInfoCounter]->weight < 0 ) && ( (coinsUsed + 1) < n)) {
			coinInfoCounter += 1;
		}
		else {
			cout << "I came here" << endl;
			return 0;
		}*/else {
			if((coinInfoCounter + 1) < NUMOFCOINS_DENOM_INFO) {
				coinInfoCounter += 1;
			}else{
				break;
			}
		}
	}


	if(tempWeight == 0) {

		

		return minCalcSavings; // 0 means no possible combination
	}


	return 0;
}
