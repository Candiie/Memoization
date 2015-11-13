
#include<iostream>
#include<vector>

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
Coin* c1 = new Coin(2,20);
Coin* c2 = new Coin(3,30);
Coin* c3 = new Coin(4,40);

//Assuming Value and Weights are sorted from lowest value to highest value are input and stored in a table
Coin* coinsInfo[NUMOFCOINS_DENOM_INFO] = { c1, c2, c3 };


//Table for memoization - assiume max no. of n and max weight 
int cachedSavings [MAX_N][MAX_WEIGHT] = {-1};

//Declaring prototype 
//int computeMinSavings (int n , int weight);
int computeMinSavings (int weight, int coindenomcount, int mincalcsavings = 0);

void main (void) {
	
	//Input from User
	int inN = 3;
	int inWeight = 70;

	cout << computeMinSavings(inWeight, 0) << endl;

}


const int NUMOFCOINS_COINCOUNTER = 10000; //assume in piggy max 100 coins

//Table to store the weight 
//vector<int> cachedCoinToDenominationWeight [NUMOFCOINS_DENOM_INFO];
int cachedCoinToDenominationWeight [NUMOFCOINS_COINCOUNTER][NUMOFCOINS_DENOM_INFO];

int computeMinSavings (int weight, int coindenomcount, int mincalcsavings) {
	
	//int mincalcsavings = 0; //mininum calculated savings
	int coininfocounter = 0;
	int tempweight = weight;
	//int revertCount = 0;
	int weightDecreased = 0;

	//return the min savings calculated at anytime the temp weight = 0;
	if(tempweight == 0) { 
		return mincalcsavings; 
	}

	if(tempweight < 0) { 
		return 0; 
	}

	while(tempweight > 0) {
			
		if ( (tempweight - coinsInfo[coindenomcount]->weight) >= 0 ) {


			if(cachedCoinToDenominationWeight [coininfocounter][coindenomcount] != -1 
				&& cachedCoinToDenominationWeight [coininfocounter][coindenomcount] != NULL){

					weightDecreased = cachedCoinToDenominationWeight [coininfocounter][coindenomcount];
			}
			else{
				weightDecreased = (coininfocounter + 1) * coinsInfo[coindenomcount]->weight;
			}

			tempweight -= weightDecreased;
			mincalcsavings += coinsInfo[coindenomcount]->value;

			//return the min savings calculated at anytime the temp weight = 0;
			if(tempweight == 0) { return mincalcsavings; }

			//store results for memoization
			cachedCoinToDenominationWeight [coininfocounter][coindenomcount] = weightDecreased;

			
			if( (tempweight - coinsInfo[coindenomcount]->weight) >= 0 ) {

				return computeMinSavings(tempweight, coindenomcount, mincalcsavings);
			}


			return computeMinSavings(tempweight += weightDecreased, coindenomcount+1, mincalcsavings -= coinsInfo[coindenomcount]->value);
		}
		else {

			//increment coin counter
			coininfocounter++;
			//revertCount++;
			break;
		}
	}

	
	//while(tempweight > 0) {

	//	for(int i = 0; i < NUMOFCOINS_DENOM_INFO; i++){
	//		
	//		bool contLoop = true;

	//		while(contLoop){



	//			coininfocounter ++;

	//		}
	//	}
	//}
}

//int computeMinSavings (int n , int weight){
//
//	int minCalcSavings = 0; //mininum calculated savings
//	int coinInfoCounter = 0;
//	int tempWeight = weight;
//	int coinsUsed = 0;
//
//
//	//Search cached table (memoization)
//	if(cachedSavings[n][weight] != -1 && cachedSavings[n][weight] != NULL ) {
//		return cachedSavings[n][weight]; //return cached results via memoization implementation
//	}
//
//	while (coinsUsed <= n) {
//
//		if(tempWeight == 0) {
//			break;
//		}
//
//		if(coinInfoCounter >= NUMOFCOINS_DENOM_INFO ) {
//			break;
//		}
//
//		//If after next coin still got weight remaining but maxing out n
//		if ( ( (tempWeight - coinsInfo[coinInfoCounter]->weight) > 0 ) && ( (coinsUsed + 1) >= n) ) {
//			coinInfoCounter += 1;
//			continue; //move on to next loop
//		}
//
//		if( ( (tempWeight - coinsInfo[coinInfoCounter]->weight) >= 0 ) && ( (coinsUsed + 1) <= n)) {
//
//			tempWeight -= coinsInfo[coinInfoCounter]->weight;
//			minCalcSavings += coinsInfo[coinInfoCounter]->value;
//			coinsUsed += 1;
//
//		}else {
//			if((coinInfoCounter + 1) < NUMOFCOINS_DENOM_INFO) {
//				coinInfoCounter += 1;
//			}else{
//				break;
//			}
//		}
//	}
//
//
//	//Meaning achieved weight with exactly n coins
//	if(tempWeight == 0) {
//
//		cachedSavings [n][weight] = minCalcSavings; //cache table for memoization
//		return minCalcSavings; 
//	}
//
//
//	return 0; // 0 means no possible combination
//}
