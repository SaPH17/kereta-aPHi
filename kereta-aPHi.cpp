#include "stdio.h"
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#define gchr while(getchar() != '\n');

const int NATION_STATION = 0;
const int CITY_STATION = 1;
const int NATION_STATION_VIEW = 0;
const int NATION_STATION_DELETE = 1;
const int NATION_STATION_INSERT = 2;
const int CITY_STATION_VIEW = 0;
const int CITY_STATION_DELETE = 1;
const int CITY_STATION_INSERT = 2;

struct cityStation{
	char name[100];
	int ticketPrice;
	int row, column;
	cityStation *up, *down, *left, *right;
	bool printed, printed2;
};

int nationStationSize = 0;
struct nationStation{
	char name[100];
	int ticketPrice;
	int row, column;
	nationStation *up, *down, *left, *right;
	cityStation *root;
	int cityStationSize;
	bool printed, printed2;
}*root;

struct queueNation{
	nationStation *station;
	queueNation *next;
}*headQN, *tailQN;

struct stackNation{
	nationStation *from, *to;
	stackNation *next;
}*headSN, *tailSN;

struct queueCity{
	cityStation *station;
	queueCity *next;
}*headQC, *tailQC;

struct stackCity{
	cityStation *from, *to;
	stackCity *next;
}*headSC, *tailSC;

void pushCityStack(cityStation *from, cityStation *to){
	stackCity *newNode = (stackCity*) malloc(sizeof(stackCity));
	newNode->from = from;
	newNode->to = to;
	newNode->next = NULL;

	if(!headSC){
		headSC = tailSC = newNode;
	}
	else{
		newNode->next = headSC;
		headSC = newNode;
	}
}

void popCityStack(){
	if(!headSC){
		return;
	}
	else if(headSC == tailSC){
		free(headSC);
		headSC = tailSC = NULL;
	}
	else{
		stackCity *temp = headSC;
		headSC = headSC->next;
		free(temp);
		temp = NULL;
	}
}

void popAllCityStack(){
	while(headSC){
		popCityStack();
	}
}

void pushCityQueue(cityStation *station){
	queueCity *newNode = (queueCity*) malloc(sizeof(queueCity));
	newNode->station = station;
	newNode->next = NULL;

	if(!headQC){
		headQC = tailQC = newNode;
	}
	else{
		tailQC->next = newNode;
		tailQC = newNode;
	}
}

void popCityQueue(){
	if(!headQC){
		return;
	}
	else if(headQC == tailQC){
		free(headQC);
		headQC = tailQC = NULL;
	}
	else{
		queueCity *temp = headQC;
		headQC = headQC->next;
		free(temp);
	}
}

void popAllCityQueue(){
	while(headQC){
		popCityQueue();
	}
}

void pushNationStack(nationStation *from, nationStation *to){
	stackNation *newNode = (stackNation*) malloc(sizeof(stackNation));
	newNode->from = from;
	newNode->to = to;
	newNode->next = NULL;

	if(!headSN){
		headSN = tailSN = newNode;
	}
	else{
		newNode->next = headSN;
		headSN = newNode;
	}
}

void popNationStack(){
	if(!headSN){
		return;
	}
	else if(headSN == tailSN){
		free(headSN);
		headSN = tailSN = NULL;
	}
	else{
		stackNation *temp = headSN;
		headSN = headSN->next;
		free(temp);
		temp = NULL;
	}
}

void popAllNationStack(){
	while(headSN){
		popNationStack();
	}
}

void pushNationQueue(nationStation *station){
	queueNation *newNode = (queueNation*) malloc(sizeof(queueNation));
	newNode->station = station;
	newNode->next = NULL;

	if(!headQN){
		headQN = tailQN = newNode;
	}
	else{
		tailQN->next = newNode;
		tailQN = newNode;
	}
}

void popNationQueue(){
	if(!headQN){
		return;
	}
	else if(headQN == tailQN){
		free(headQN);
		headQN = tailQN = NULL;
	}
	else{
		queueNation *temp = headQN;
		headQN = headQN->next;
		free(temp);
	}
}

void popAllNationQueue(){
	while(headQN){
		popNationQueue();
	}
}

cityStation* pushUpCityStation(nationStation *parent, cityStation *curr, char name[], int ticketPrice){
	if(curr->up != NULL){
		printf(" There is already a station named %s there!", curr->up->name);
		return NULL;
	}

	cityStation *newNode = (cityStation*) malloc(sizeof(cityStation));
	strcpy(newNode->name, name);
	newNode->ticketPrice = ticketPrice;
	newNode->printed = newNode->printed2 = false;
	newNode->column = curr->column;
	newNode->row = curr->row - 1;
	newNode->right = newNode->left = newNode->up = newNode->down = NULL;

	curr->up = newNode;
	newNode->down = curr;

	parent->cityStationSize++;
	
	return newNode;
}

cityStation* pushDownCityStation(nationStation *parent, cityStation *curr, char name[], int ticketPrice){
	if(curr->down != NULL){
		printf(" There is already a station named %s there!", curr->down->name);
		return NULL;
	}

	cityStation *newNode = (cityStation*) malloc(sizeof(cityStation));
	strcpy(newNode->name, name);
	newNode->ticketPrice = ticketPrice;
	newNode->printed = newNode->printed2 = false;
	newNode->column = curr->column;
	newNode->row = curr->row + 1;
	newNode->right = newNode->left = newNode->up = newNode->down = NULL;

	curr->down = newNode;
	newNode->up = curr;

	parent->cityStationSize++;
	
	return newNode;
}

cityStation* pushLeftCityStation(nationStation *parent, cityStation *curr, char name[], int ticketPrice){
	if(curr->left != NULL){
		printf(" There is already a station named %s there!", curr->left->name);
		return NULL;
	}

	cityStation *newNode = (cityStation*) malloc(sizeof(cityStation));
	strcpy(newNode->name, name);
	newNode->ticketPrice = ticketPrice;
	newNode->printed = newNode->printed2 = false;
	newNode->row = curr->row;
	newNode->column = curr->column - 1;
	newNode->right = newNode->left = newNode->up = newNode->down = NULL;

	curr->left = newNode;
	newNode->right = curr;

	parent->cityStationSize++;
	
	return newNode;
}

cityStation* pushRightCityStation(nationStation *parent, cityStation *curr, char name[], int ticketPrice){
	if(curr->right != NULL){
		printf(" There is already a station named %s there!", curr->right->name);
		return NULL;
	}

	cityStation *newNode = (cityStation*) malloc(sizeof(cityStation));
	strcpy(newNode->name, name);
	newNode->ticketPrice = ticketPrice;
	newNode->printed = newNode->printed2 = false;
	newNode->row = curr->row;
	newNode->column = curr->column + 1;
	newNode->right = newNode->left = newNode->up = newNode->down = NULL;

	curr->right = newNode;
	newNode->left = curr;

	parent->cityStationSize++;
	
	return newNode;
}

cityStation* pushFirstCityStation(nationStation *parent, char name[], int ticketPrice){
	cityStation *newNode = (cityStation*) malloc(sizeof(cityStation));
	strcpy(newNode->name, name);
	newNode->ticketPrice = ticketPrice;
	newNode->printed = newNode->printed2 = false;
	newNode->row = newNode->column = 0;
	newNode->right = newNode->left = newNode->up = newNode->down = NULL;

	parent->root = newNode;

	parent->cityStationSize++;
	
	return newNode;
}

nationStation *pushUpNationStation(nationStation *curr, char name[], int ticketPrice){
	if(curr->up != NULL){
		printf(" There is already a station named %s there!", curr->down->name);
		return NULL;
	}

	nationStation *newNode = (nationStation*) malloc(sizeof(nationStation));
	strcpy(newNode->name, name);
	newNode->ticketPrice = ticketPrice;
	newNode->printed = newNode->printed2 = false;
	newNode->cityStationSize = 0;
	newNode->root = NULL;
	newNode->column = curr->column;
	newNode->row = curr->row - 1;
	newNode->right = newNode->left = newNode->up = newNode->down = NULL;

	curr->up = newNode;
	newNode->down = curr;

	nationStationSize++;
	
	return newNode;
}

nationStation *pushDownNationStation(nationStation *curr, char name[], int ticketPrice){
	if(curr->down != NULL){
		printf(" There is already a station named %s there!", curr->down->name);
		return NULL;
	}

	nationStation *newNode = (nationStation*) malloc(sizeof(nationStation));
	strcpy(newNode->name, name);
	newNode->ticketPrice = ticketPrice;
	newNode->printed = newNode->printed2 = false;
	newNode->cityStationSize = 0;
	newNode->root = NULL;
	newNode->column = curr->column;
	newNode->row = curr->row + 1;
	newNode->right = newNode->left = newNode->up = newNode->down = NULL;

	curr->down = newNode;
	newNode->up = curr;

	nationStationSize++;
	
	return newNode;
}

nationStation *pushLeftNationStation(nationStation *curr, char name[], int ticketPrice){
	if(curr->left != NULL){
		printf(" There is already a station named %s there!", curr->left->name);
		return NULL;
	}

	nationStation *newNode = (nationStation*) malloc(sizeof(nationStation));
	strcpy(newNode->name, name);
	newNode->ticketPrice = ticketPrice;
	newNode->printed = newNode->printed2 = false;
	newNode->cityStationSize = 0;
	newNode->root = NULL;
	newNode->row = curr->row;
	newNode->column = curr->column - 1;
	newNode->right = newNode->left = newNode->up = newNode->down = NULL;

	curr->left = newNode;
	newNode->right = curr;

	nationStationSize++;
	
	return newNode;
}

nationStation *pushRightNationStation(nationStation *curr, char name[], int ticketPrice){
	if(curr->right != NULL){
		printf(" There is already a station named %s there!", curr->right->name);
		return NULL;
	}

	nationStation *newNode = (nationStation*) malloc(sizeof(nationStation));
	strcpy(newNode->name, name);
	newNode->ticketPrice = ticketPrice;
	newNode->printed = newNode->printed2 = false;
	newNode->cityStationSize = 0;
	newNode->root = NULL;
	newNode->row = curr->row;
	newNode->column = curr->column + 1;
	newNode->right = newNode->left = newNode->up = newNode->down = NULL;

	curr->right = newNode;
	newNode->left = curr;

	nationStationSize++;
	
	return newNode;
}

nationStation *pushFirstNationStation(char name[], int ticketPrice){
	nationStation *newNode = (nationStation*) malloc(sizeof(nationStation));
	strcpy(newNode->name, name);
	newNode->ticketPrice = ticketPrice;
	newNode->printed = newNode->printed2 = false;
	newNode->cityStationSize = 0;
	newNode->root = NULL;
	newNode->row = newNode->column = 0;
	newNode->right = newNode->left = newNode->up = newNode->down = NULL;

	root = newNode;

	nationStationSize++;
	
	return newNode;
}

void neutralize2CityStation(cityStation *curr){
	if(!curr || curr->printed2 == false){
		return;
	}

	curr->printed2 = false;
	neutralize2CityStation(curr->left);
	neutralize2CityStation(curr->right);
	neutralize2CityStation(curr->up);
	neutralize2CityStation(curr->down);
}

void neutralizeCityStation(cityStation *curr){
	if(!curr || curr->printed == false){
		return;
	}

	curr->printed = false;
	neutralizeCityStation(curr->left);
	neutralizeCityStation(curr->right);
	neutralizeCityStation(curr->up);
	neutralizeCityStation(curr->down);
}

void neutralize2NationStation(nationStation *curr){
	if(!curr || curr->printed2 == false){
		return;
	}

	curr->printed2 = false;
	neutralize2NationStation(curr->left);
	neutralize2NationStation(curr->right);
	neutralize2NationStation(curr->up);
	neutralize2NationStation(curr->down);
}

void neutralizeNationStation(nationStation *curr){
	if(!curr || curr->printed == false){
		return;
	}

	curr->printed = false;
	neutralizeNationStation(curr->left);
	neutralizeNationStation(curr->right);
	neutralizeNationStation(curr->up);
	neutralizeNationStation(curr->down);
}

bool isCityStationFull(cityStation *curr){
	cityStation *arr[4] = {curr->up, curr->down, curr->left, curr->right};
	int count = 0;
	for(int i = 0; i < 4; i++){
		if(!arr[i]){
			return false;
		}
	}

	return true;
}

bool isNationStationFull(nationStation *curr){
	nationStation *arr[4] = {curr->up, curr->down, curr->left, curr->right};
	int count = 0;
	for(int i = 0; i < 4; i++){
		if(!arr[i]){
			return false;
		}
	}

	return true;
}

bool isCityStationLeaf(cityStation *curr){
	cityStation *arr[4] = {curr->up, curr->down, curr->left, curr->right};
	int count = 0;
	for(int i = 0; i < 4; i++){
		if(arr[i]){
			count++;
		}
	}

	return count <= 1;
}

bool isNationStationLeaf(nationStation *curr){
	nationStation *arr[4] = {curr->up, curr->down, curr->left, curr->right};
	int count = 0;
	for(int i = 0; i < 4; i++){
		if(arr[i]){
			count++;
		}
	}

	return count <= 1;
}

bool Cloop = false;
void doIsCityStationLoop(cityStation *target, cityStation *initial, cityStation *from, cityStation *curr){
	if(Cloop || !curr || curr->printed2 || (from == initial && curr == target)){
		return;
	}
	
	if(curr == target){
		Cloop = true;
	}
	
	curr->printed2 = true;
	doIsCityStationLoop(target, initial, curr, curr->up);
	doIsCityStationLoop(target, initial, curr, curr->down);
	doIsCityStationLoop(target, initial, curr, curr->left);
	doIsCityStationLoop(target, initial, curr, curr->right);

}

bool isCityStationLoop(cityStation *curr){
	cityStation *arr[4] = {curr->up, curr->down, curr->left, curr->right};
	for(int i = 0; i < 4; i++){
		if(arr[i]){
			neutralize2CityStation(curr);
			Cloop = false;
			doIsCityStationLoop(curr, arr[i], curr, arr[i]);
			if(Cloop == false){
				return false;
			}
		}
	}

	return Cloop;
}

bool Nloop = false;
void doIsNationStationLoop(nationStation *target, nationStation *initial, nationStation *from, nationStation *curr){
	if(Nloop || !curr || curr->printed2 || (from == initial && curr == target)){
		return;
	}
	
	if(curr == target){
		Nloop = true;
	}
	
	curr->printed2 = true;
	doIsNationStationLoop(target, initial, curr, curr->up);
	doIsNationStationLoop(target, initial, curr, curr->down);
	doIsNationStationLoop(target, initial, curr, curr->left);
	doIsNationStationLoop(target, initial, curr, curr->right);

}

bool isNationStationLoop(nationStation *curr){
	nationStation *arr[4] = {curr->up, curr->down, curr->left, curr->right};
	for(int i = 0; i < 4; i++){
		if(arr[i]){
			neutralize2NationStation(root);
			Nloop = false;
			doIsNationStationLoop(curr, arr[i], curr, arr[i]);
			if(Nloop == false){
				return false;
			}
		}
	}

	return Nloop;
}

int index = 0;
cityStation *Ctemp = NULL;
void printCityStationOrdered(cityStation *curr, int type){
	if(!curr || curr->printed){
		return;
	}

	if(type == CITY_STATION_VIEW){
		printf("  %d. %s\n", index, curr->name);
	}
	else if(type == CITY_STATION_DELETE){
		printf("  %d. %s", index, curr->name);
		if(isCityStationLeaf(curr) || isCityStationLoop(curr)){
			printf(" [SAFE TO BE DELETED]");
		}

		printf("\n");
	}
	else if(type == CITY_STATION_INSERT){
		printf("  %d. %s", index, curr->name);
		if(isCityStationFull(curr)){
			printf(" [FULL]");
		}

		printf("\n");
	}
	curr->printed = true;
	index++;
	printCityStationOrdered(curr->right, type);
	printCityStationOrdered(curr->left, type);
	printCityStationOrdered(curr->up, type);
	printCityStationOrdered(curr->down, type);
}

void viewCityStationOrdered(nationStation *parent, int type){
	neutralizeCityStation(parent->root);
	index = 1;
	printCityStationOrdered(parent->root, type);
}

nationStation *Ntemp = NULL;
void printNationStationOrdered(nationStation *curr, int type){
	if(!curr || curr->printed){
		return;
	}

	if(type == NATION_STATION_VIEW){
		printf("  %d. %s\n", index, curr->name);
	}
	else if(type == NATION_STATION_DELETE){
		printf("  %d. %s", index, curr->name);
		if(isNationStationLeaf(curr) || isNationStationLoop(curr)){
			printf(" [SAFE TO BE DELETED]");
		}

		printf("\n");
	}
	else if(type == NATION_STATION_INSERT){
		printf("  %d. %s", index, curr->name);
		if(isNationStationFull(curr)){
			printf(" [FULL]");
		}

		printf("\n");
	}
	curr->printed = true;
	index++;
	printNationStationOrdered(curr->right, type);
	printNationStationOrdered(curr->left, type);
	printNationStationOrdered(curr->up, type);
	printNationStationOrdered(curr->down, type);

}

void viewNationStationOrdered(int type){
	neutralizeNationStation(root);
	index = 1;
	printNationStationOrdered(root, type);
}

cityStation *doSearchCityStation(int targetIndex, cityStation *curr){
	if(!curr || curr->printed){
		return NULL;
	}
	if(index == targetIndex){
		Ctemp = curr;
	}

	index++;
	curr->printed = true;

	doSearchCityStation(targetIndex, curr->right);
	doSearchCityStation(targetIndex, curr->left);
	doSearchCityStation(targetIndex, curr->up);
	doSearchCityStation(targetIndex, curr->down);
}

cityStation *searchCityStation(nationStation *parent, int targetIndex){
	neutralizeCityStation(parent->root);
	index = 1;
	Ctemp = NULL;
	doSearchCityStation(targetIndex, parent->root);
	return Ctemp;
}

void doSearchCityStationCoord(cityStation *curr, int row, int col){
	if(!curr || curr->printed){
		return;
	}
	if(curr->row == row && curr->column == col){
		Ctemp = curr;
	}

	curr->printed = true;

	doSearchCityStationCoord(curr->right, row, col);
	doSearchCityStationCoord(curr->left, row, col);
	doSearchCityStationCoord(curr->up, row, col);
	doSearchCityStationCoord(curr->down, row, col);
}

cityStation *searchCityStationCoord(nationStation *parent, int row, int col){
	neutralizeCityStation(parent->root);
	Ctemp = NULL;
	doSearchCityStationCoord(parent->root, row, col);
	return Ctemp;
}

void doSearchNationStation(int targetIndex, nationStation *curr){
	if(!curr || curr->printed){
		return;
	}
	if(index == targetIndex){
		Ntemp = curr;
	}

	index++;
	curr->printed = true;

	doSearchNationStation(targetIndex, curr->right);
	doSearchNationStation(targetIndex, curr->left);
	doSearchNationStation(targetIndex, curr->up);
	doSearchNationStation(targetIndex, curr->down);
}

nationStation *searchNationStation(int targetIndex){
	neutralizeNationStation(root);
	index = 1;
	Ntemp = NULL;
	doSearchNationStation(targetIndex, root);
	return Ntemp;
}

void doSearchNationStationCoord(nationStation *curr, int row, int col){
	if(!curr || curr->printed){
		return;
	}
	if(curr->row == row && curr->column == col){
		Ntemp = curr;
	}

	curr->printed = true;

	doSearchNationStationCoord(curr->right, row, col);
	doSearchNationStationCoord(curr->left, row, col);
	doSearchNationStationCoord(curr->up, row, col);
	doSearchNationStationCoord(curr->down, row, col);
}

nationStation *searchNationStationCoord(int row, int col){
	neutralizeNationStation(root);
	Ntemp = NULL;
	doSearchNationStationCoord(root, row, col);
	return Ntemp;
}

bool stationNameFlag = false;
void searchCityStationName(char name[], cityStation *curr){
	if(stationNameFlag){
		return;
	}
	
	if(!curr || curr->printed){
		return;
	}
	
	if(strcmp(name, curr->name) == 0){
		stationNameFlag = true;
	}
	
	curr->printed = true;

	searchCityStationName(name, curr->right);
	searchCityStationName(name, curr->left);
	searchCityStationName(name, curr->up);
	searchCityStationName(name, curr->down);
}

void searchNationStationName(char name[], nationStation *curr){
	if(stationNameFlag){
		return;
	}
	
	if(!curr || curr->printed){
		return;
	}
	
	if(strcmp(name, curr->name) == 0){
		stationNameFlag = true;
	}

	curr->printed = true;

	searchNationStationName(name, curr->right);
	searchNationStationName(name, curr->left);
	searchNationStationName(name, curr->up);
	searchNationStationName(name, curr->down);
	
	if(curr->root){
		neutralizeCityStation(curr->root);
		searchCityStationName(name, curr->root);
	}
}

bool searchStationName(char name[]){
	neutralizeNationStation(root);
	stationNameFlag = false;
	searchNationStationName(name, root);
	return stationNameFlag;
}

bool isStationNameValid(char name[]){
	if(strlen(name) < 5 || strlen(name) > 100){
		printf("  Station name must be between 5 - 100 words!\n");
		return false;
	}
	
	if(searchStationName(name)){
		printf("  Station name must be unique!\n");
		return false;
	}
	
	int count = 0;

	for(int i = 0; i < strlen(name); i++){
		if(name[i] == ' '){
			return true;
		}
	}

	printf("  Station name must be 2 words!\n");
	return false;
}

bool isStationTicketPriceValid(int ticketPrice, int type){
	if(type == NATION_STATION && (ticketPrice < 100000 || ticketPrice > 1000000)){
		printf("  Ticket price must be between 100.000 and 1.000.000!\n");
		return false;
	}
	else if(type == CITY_STATION && (ticketPrice < 50000 || ticketPrice > 500000)){
		printf("  Ticket price must be between 50.000 and 500.000!\n");
		return false;
	}
	
	return true;
}

void printNeighbourNationStation(nationStation *curr){
	nationStation *arr[4] = {curr->up, curr->down, curr->left, curr->right};
	char dir[4][10] = {"Up", "Down", "Left", "Right"};
	int coord[2][4] = {{-1,1,0,0},{0,0,-1,1}};
	
	for(int i = 0; i < 4; i++){
		if(arr[i]){
			printf("  %d. %s -> %s\n", i+1, dir[i], arr[i]->name);
		}
		else{
			printf("  %d. %s -> none", i+1, dir[i]);
			nationStation *temp = searchNationStationCoord(curr->row + coord[0][i], curr->column + coord[1][i]);
			if(temp){
				printf(" [%s]\n", temp->name);
			}
			else{
				printf(" [Empty]\n");
			}
		}
	}	
}

void printNeighbourCityStation(nationStation *parent, cityStation *curr){
	cityStation *arr[4] = {curr->up, curr->down, curr->left, curr->right};
	char dir[4][10] = {"Up", "Down", "Left", "Right"};
	int coord[2][4] = {{-1,1,0,0},{0,0,-1,1}};
	
	for(int i = 0; i < 4; i++){
		if(arr[i]){
			printf("  %d. %s -> %s\n", i+1, dir[i], arr[i]->name);
		}
		else{
			printf("  %d. %s -> none", i+1, dir[i]);
			cityStation *temp = searchCityStationCoord(parent, curr->row + coord[0][i], curr->column + coord[1][i]);
			if(temp){
				printf(" [%s]\n", temp->name);
			}
			else{
				printf(" [Empty]\n");
			}
		}
	}
		
}

int maxColumn = 0;
int minColumn = 0;
void findMaxMinColumnN(nationStation *curr){
	if(!curr || curr->printed){
		return;
	}
	
	curr->printed = true;
	
	if(curr->column > maxColumn){
		maxColumn = curr->column;
	}
	if(curr->column < minColumn){
		minColumn = curr->column;
	}
	
	findMaxMinColumnN(curr->left);
	findMaxMinColumnN(curr->right);
	findMaxMinColumnN(curr->up);
	findMaxMinColumnN(curr->down);
}

void findMaxMinColumnC(cityStation *curr){
	if(!curr || curr->printed){
		return;
	}
	
	curr->printed = true;
	
	if(curr->column > maxColumn){
		maxColumn = curr->column;
	}
	if(curr->column < minColumn){
		minColumn = curr->column;
	}
	
	findMaxMinColumnC(curr->left);
	findMaxMinColumnC(curr->right);
	findMaxMinColumnC(curr->up);
	findMaxMinColumnC(curr->down);
}

int maxRow = 0;
int minRow = 0;
void findMaxMinRowN(nationStation *curr){
	if(!curr || curr->printed){
		return;
	}
	
	curr->printed = true;
	
	if(curr->row > maxRow){
		maxRow = curr->row;
	}
	if(curr->row < minRow){
		minRow = curr->row;
	}
	
	findMaxMinRowN(curr->left);
	findMaxMinRowN(curr->right);
	findMaxMinRowN(curr->up);
	findMaxMinRowN(curr->down);

}

void findMaxMinRowC(cityStation *curr){
	if(!curr || curr->printed){
		return;
	}
	
	curr->printed = true;
	
	if(curr->row > maxRow){
		maxRow = curr->row;
	}
	if(curr->row < minRow){
		minRow = curr->row;
	}
	
	findMaxMinRowC(curr->left);
	findMaxMinRowC(curr->right);
	findMaxMinRowC(curr->up);
	findMaxMinRowC(curr->down);

}

const int size = 1000;
nationStation *nationStationMap[size][size];
void fillNationStationArray(nationStation *curr){
	if(!curr || curr->printed){
		return;
	}

	curr->printed = true;
	
	nationStationMap[curr->row + abs(minRow)][curr->column + abs(minColumn)] = curr;

	fillNationStationArray(curr->left);
	fillNationStationArray(curr->right);
	fillNationStationArray(curr->up);
	fillNationStationArray(curr->down);
}

void printNationStationArray(int row, int col){
	char line[25] = "+======================+";
	char empty[25] = "|                      |";
	char vertLine[25] = "           |            ";
	
	for(int i = 0; i <= row; i++){
		

		for(int k = 0; k < 7; k++){
			for(int j = 0; j <= col; j++){

				if(!nationStationMap[i][j]){
					printf("  %-24s  ", "");
				}
				else if(k == 1 || k == 5){
					printf("  %s  ", line);
				}
				else if(k == 2 || k == 4){
					printf("  %s  ", empty);
				}
				else if(k == 3){
					if(nationStationMap[i][j]->left){
						printf("--");
					}
					else{
						printf("  ");
					}
					printf("| %-20s |", nationStationMap[i][j]);
					if(nationStationMap[i][j]->right){
						printf("--");
					}
					else{
						printf("  ");
					}
				}
				else if(k == 0){
					if(nationStationMap[i][j]->up){
						printf("  %s  ", vertLine);
					}
					else{
						printf("  %-24s  ", "");
					}
				}
				else if(k == 6){
					if(nationStationMap[i][j]->down){
						printf("  %s  ", vertLine);
					}
					else{
						printf("  %-24s  ", "");
					}
				}
			}
			printf("\n");
		}
	}
}

void printAllStationMap(){
	maxRow = 0;
	minRow = 0;
	maxColumn = 0;
	minColumn = 0;

	neutralizeNationStation(root);
	findMaxMinRowN(root);
	neutralizeNationStation(root);
	findMaxMinColumnN(root);
	
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			nationStationMap[i][j] = NULL;
		}
	}

	neutralizeNationStation(root);
	fillNationStationArray(root);
	printNationStationArray(maxRow-minRow, maxColumn-minColumn);
}

cityStation *cityStationMap[size][size];
void fillCityStationArray(cityStation *curr){
	if(!curr || curr->printed){
		return;
	}

	curr->printed = true;
	
	cityStationMap[curr->row + abs(minRow)][curr->column + abs(minColumn)] = curr;

	fillCityStationArray(curr->left);
	fillCityStationArray(curr->right);
	fillCityStationArray(curr->up);
	fillCityStationArray(curr->down);
}

void printCityStationArray(int row, int col){
	char line[25] = "+======================+";
	char empty[25] = "|                      |";
	char vertLine[25] = "           |            ";
	
	for(int i = 0; i <= row; i++){
		

		for(int k = 0; k < 7; k++){
			for(int j = 0; j <= col; j++){

				if(!cityStationMap[i][j]){
					printf("  %-24s  ", "");
				}
				else if(k == 1 || k == 5){
					printf("  %s  ", line);
				}
				else if(k == 2 || k == 4){
					printf("  %s  ", empty);
				}
				else if(k == 3){
					if(cityStationMap[i][j]->left){
						printf("--");
					}
					else{
						printf("  ");
					}
					printf("| %-20s |", cityStationMap[i][j]);
					if(cityStationMap[i][j]->right){
						printf("--");
					}
					else{
						printf("  ");
					}
				}
				else if(k == 0){
					if(cityStationMap[i][j]->up){
						printf("  %s  ", vertLine);
					}
					else{
						printf("  %-24s  ", "");
					}
				}
				else if(k == 6){
					if(cityStationMap[i][j]->down){
						printf("  %s  ", vertLine);
					}
					else{
						printf("  %-24s  ", "");
					}
				}
			}
			printf("\n");
		}
	}
}

void printCityStationMap(nationStation *parent){
	maxRow = 0;
	minRow = 0;
	maxColumn = 0;
	minColumn = 0;

	neutralizeCityStation(parent->root);
	findMaxMinRowC(parent->root);
	neutralizeCityStation(parent->root);
	findMaxMinColumnC(parent->root);
	
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			cityStationMap[i][j] = NULL;
		}
	}

	neutralizeCityStation(parent->root);
	fillCityStationArray(parent->root);
	printCityStationArray(maxRow-minRow, maxColumn-minColumn);
}

bool isCityStationSpaceEmpty(nationStation *parent, int selectedDirection, cityStation *curr){
	if(selectedDirection == 1){
		return searchCityStationCoord(parent, curr->row-1, curr->column) == NULL;
	}
	else if(selectedDirection == 2){
		return searchCityStationCoord(parent, curr->row+1, curr->column) == NULL;
	}
	else if(selectedDirection == 3){
		return searchCityStationCoord(parent, curr->row, curr->column-1) == NULL;
	}
	else if(selectedDirection == 4){
		return searchCityStationCoord(parent, curr->row, curr->column+1) == NULL;
	}
}

bool isNationStationSpaceEmpty(int selectedDirection, nationStation *curr){
	if(selectedDirection == 1){
		return searchNationStationCoord(curr->row-1, curr->column) == NULL;
	}
	else if(selectedDirection == 2){
		return searchNationStationCoord(curr->row+1, curr->column) == NULL;
	}
	else if(selectedDirection == 3){
		return searchNationStationCoord(curr->row, curr->column-1) == NULL;
	}
	else if(selectedDirection == 4){
		return searchNationStationCoord(curr->row, curr->column+1) == NULL;
	}
}

void addNewCityStationMenu(nationStation *parent){
	char name[100];
	int ticketPrice;

	do{
		printf("  Enter the Station Name [5-100 Characters, 2 Words Minimal, Unique] [x to exit] : ");
		scanf("%[^\n]", name);
		gchr
		if(strcasecmp(name, "x") == 0){
			return;
		}
	}while(!isStationNameValid(name));

	do{
		printf("  Enter the Station Ticket Price [Rp. 50.000 - Rp. 500.000] [-1 to exit] : Rp. ");
		scanf("%d", &ticketPrice);
		gchr
		if(ticketPrice == -1){
			return;
		}
	}while(!isStationTicketPriceValid(ticketPrice, CITY_STATION));

	system("cls");

	if(parent->root == NULL){
		pushFirstCityStation(parent, name, ticketPrice);
	}
	else{
		int selectedStationIndex;
		cityStation *selectedStation;
		int flag = true;
		char again[100];

		do{
			printCityStationMap(parent);
			printf("  Which station can connect to this station? [-1 to exit]\n");
			viewCityStationOrdered(parent, CITY_STATION_INSERT);
			printf("  >> ");
			scanf("%d", &selectedStationIndex);
			gchr
			if(selectedStationIndex == -1){
				return;
			}
			selectedStation = searchCityStation(parent, selectedStationIndex);

			system("cls");
		}while(selectedStationIndex < 1 || selectedStationIndex > parent->cityStationSize 
				|| isCityStationFull(selectedStation));

		int selectedDirection;
		cityStation *tempArr[4] = {selectedStation->up, selectedStation->down,
										selectedStation->left, selectedStation->right};
		do{
			printCityStationMap(parent);
			printf("  Selected Station : %s [-1 to exit]\n",selectedStation->name);
			printf("  1. Up -> %s\n", selectedStation->up ? selectedStation->up->name : "None");
			printf("  2. Down -> %s\n", selectedStation->down ? selectedStation->down->name : "None");
			printf("  3. Left -> %s\n", selectedStation->left ? selectedStation->left->name : "None");
			printf("  4. Right -> %s\n", selectedStation->right ? selectedStation->right->name : "None");
			printf("  >> ");
			scanf("%d", &selectedDirection);
			gchr
			if(selectedDirection == -1){
				return;
			}
			system("cls");
		}while(selectedDirection < 1 || selectedDirection > 4 || tempArr[selectedDirection-1]
				|| !isCityStationSpaceEmpty(parent, selectedDirection, selectedStation));

		cityStation *c = NULL;

		if(selectedDirection == 1){
			c = pushUpCityStation(parent, selectedStation, name, ticketPrice);
		}
		else if(selectedDirection == 2){
			c = pushDownCityStation(parent, selectedStation, name, ticketPrice);
		}
		else if(selectedDirection == 3){
			c = pushLeftCityStation(parent, selectedStation, name, ticketPrice);
		}
		else if(selectedDirection == 4){
			c = pushRightCityStation(parent, selectedStation, name, ticketPrice);
		}
		
		int coord[2][4] = {{-1,1,0,0},{0,0,-1,1}};
		int count = 0;
		
		for(int i = 0; i < 4; i++){
			if(searchCityStationCoord(parent, c->row + coord[0][i], c->column + coord[1][i]) == NULL){
				count++;
			}
			else if(i == 0 && c->up && c == c->up->down){
				count++;
			}
			else if(i == 1 && c->down && c == c->down->up){
				count++;
			}
			else if(i == 2 && c->left && c == c->left->right){
				count++;
			}
			else if(i == 3 && c->right && c == c->right->left){
				count++;
			}
		}
		
		if(count == 4){
			printf("  %s has been Added to the System!\n", name);
		 	printf("  Press enter to continue...");
		 	gchr
		 	
			return;
		}
		
		do{
			printf("  Do you want to connect this station to other station? [Yes | No] : ");
			scanf("%[^\n]", again);
			gchr
			system("cls");
		}while(strcmp(again, "Yes") != 0 && strcmp(again, "No") != 0);
		
		if(strcmp(again, "No") == 0){
			flag = false;
		}
		
		int connect;

		while(flag){
			printCityStationMap(parent);
			printf("  Neighbour station :\n");
			printNeighbourCityStation(parent, c);
			printf("  Choose which direction you want to connect [-1 to exit] : ");
			scanf("%d", &connect);
			gchr
			system("cls");
			if(connect == -1){
				break;
			}
			
			cityStation *temp = searchCityStationCoord(parent, c->row + coord[0][connect-1], 
																c->column + coord[1][connect-1]);
						
			if(temp){
				if(connect == 1 && temp->down == NULL){
					temp->down = c;
					c->up = temp;
				}
				else if(connect == 2 && temp->up == NULL){
					temp->up = c;
					c->down = temp;
				}
				else if(connect == 3 && temp->right == NULL){
					temp->right = c;
					c->left = temp;
				}
				else if(connect == 4 && temp->left == NULL){
					temp->left = c;
					c->right = temp;
				}
			}
		}
		
		system("cls");
	}

	printf("  %s has been Added to the System!\n", name);
 	printf("  Press enter to continue...");
 	gchr
}

void deleteCityStation(nationStation *parent, cityStation *curr){
	if(curr->up){
		curr->up->down = NULL;
		if(curr == parent->root){
			parent->root = curr->up;
		}
	}
	if(curr->down){
		curr->down->up = NULL;
		if(curr == parent->root){
			parent->root = curr->down;
		}
	}
	if(curr->left){
		curr->left->right = NULL;
		if(curr == parent->root){
			parent->root = curr->left;
		}
	}
	if(curr->right){
		curr->right->left = NULL;
		if(curr == parent->root){
			parent->root = curr->right;
		}
	}

	free(curr);

	if(curr == parent->root){
		parent->root = NULL;
	}
	
	parent->cityStationSize--;
	
}

void printCityStationMapMenu(nationStation *parent){
	if(parent->root == NULL){
		printf("  There is no station in this city...");
		gchr
		return;
	}

	printf("  All City Station :\n\n");
	printCityStationMap(parent);
	printf("\n  Press enter to continue...");
	gchr
}

void backtrackCityStation(cityStation *source, cityStation *dest){
	int totalTicketPrice = 0;
	char *output = (char*) malloc(sizeof(char)*100), temp[100];
	char connector[5] = ",";
	int count = 1;
	strcpy(output, dest->name);
	strcpy(temp, dest->name);

	while(headSC){
		if(strcmp(headSC->to->name, temp) == 0){
			totalTicketPrice += headSC->to->ticketPrice;
			output = strcat(output, connector);
			output = strcat(output, headSC->from->name);
			strcpy(temp, headSC->from->name);
			count++;
		}

		popCityStack();
	}

	char arr[count][100];
	char *token = strtok(output, connector);

	printf("  Path from %s to %s :\n\n  ", source->name, dest->name);
	int i = 0;
	while(token != NULL){
		strcpy(arr[i], token);
		token = strtok(NULL, connector);
		i++;
	}

	for(int j = count - 1; j >= 0; j--){
		if(j > 0){
			printf("%s -> ", arr[j]);
		}
		else{
			printf("%s", arr[j]);
		}
	}

	printf("\n  Total Ticket Price : %d", totalTicketPrice);
	printf("\n\n  Press enter to continue...");
	gchr
}

void findCityStationRoute(nationStation *parent, cityStation *source, cityStation *dest){
	neutralizeCityStation(parent->root);
	pushCityQueue(source);
	source->printed = true;

	while(headQC){
		if(strcmp(headQC->station->name, dest->name) == 0){
			backtrackCityStation(source, dest);
			popAllCityQueue();
			popAllCityStack();
			return;
		}
		else{
			cityStation *arr[4] = {headQC->station->right, headQC->station->left,
										headQC->station->up, headQC->station->down};

			for(int i = 0; i < 4; i++){
				if(arr[i] && !arr[i]->printed){
					pushCityQueue(arr[i]);
					pushCityStack(headQC->station, arr[i]);
					arr[i]->printed = true;
				}
			}
		}
		
		popCityQueue();
	}
}

void findCityStationRouteMenu(nationStation *parent){
	int sourceStationIndex, destStationIndex;
	cityStation *sourceStation, *destStation;
	
	if(parent->cityStationSize < 2){
		printf("  You must have atleast 2 station to find a route!\n");
		gchr
		return;
	}

	do{
		printf("  All Station in This City [-1 to exit] :\n\n");
		printCityStationMap(parent);
		viewCityStationOrdered(parent, CITY_STATION_VIEW);
		printf("  Input Source Station : ");
		scanf("%d", &sourceStationIndex);
		gchr
		if(sourceStationIndex == -1){
			return;
		}
		system("cls");
	}while(sourceStationIndex < 1 || sourceStationIndex > parent->cityStationSize);

	do{
		printf("  All Station in This City [-1 to exit] :\n\n");
		printCityStationMap(parent);
		viewCityStationOrdered(parent, CITY_STATION_VIEW);
		printf("  Input Destination Station : ");
		scanf("%d", &destStationIndex);
		gchr
		if(destStationIndex == -1){
			return;
		}
		system("cls");
	}while(sourceStationIndex < 1 || sourceStationIndex > parent->cityStationSize
			|| destStationIndex == sourceStationIndex);

	sourceStation = searchCityStation(parent, sourceStationIndex);
	destStation = searchCityStation(parent, destStationIndex);
	findCityStationRoute(parent, sourceStation, destStation);
}

void deleteCityStationMenu(nationStation *parent){
	if(parent->root == NULL){
		printf("  There is no station in this city...");
		gchr
		return;
	}

	int deletedStationIndex;
	cityStation *deletedStation;

	do{
		system("cls");
		printf("  Station in This City [-1 to exit] :\n\n");
		printCityStationMap(parent);
		viewCityStationOrdered(parent, CITY_STATION_DELETE);
		printf("  Input station to be deleted : ");
		scanf("%d", &deletedStationIndex);
		if(deletedStationIndex == -1){
			return;
		}
		deletedStation = searchCityStation(parent, deletedStationIndex);
		gchr
	}while(deletedStationIndex < 1 || deletedStationIndex > parent->cityStationSize
				|| (!isCityStationLeaf(deletedStation) && !isCityStationLoop(deletedStation)));

	deleteCityStation(parent, deletedStation);
	system("cls");
	printf("  Station deleted!\n");
	printf("  Press enter to continue...");
	gchr
}

void manageNationStation(nationStation *selectedStation){
	
	int menu;

	do{
		system("cls");
		menu = 0;
		printf("  Station name : %s\n", selectedStation->name);
		printf("  Station ticket price : %d\n\n", selectedStation->ticketPrice);
		printf("  1. Add New City Station\n");
		printf("  2. Delete City Station\n");
		printf("  3. View All City Station\n");
		printf("  4. Find City Station Route\n");
		printf("  5. Exit\n");
		printf("  >> ");
		scanf("%d", &menu);
		gchr
		system("cls");
		if(menu == 1){
			addNewCityStationMenu(selectedStation);
		}
		else if(menu == 2){
			deleteCityStationMenu(selectedStation);
		}
		else if(menu == 3){
			printCityStationMapMenu(selectedStation);
		}
		else if(menu == 4){
			findCityStationRouteMenu(selectedStation);
		}
	}while(menu != 5);
}

void manageNationStationMenu(){

	int selectedStationIndex;
	nationStation *selectedStation;
	
	if(root == NULL){
		printf("  There is no nation station in the system...");
		gchr
		return;
	}

	do{
		printf("  Choose station that you want manage [-1 to exit] :\n");
		viewNationStationOrdered(NATION_STATION_VIEW);
		printf("  >> ");
		scanf("%d", &selectedStationIndex);
		gchr
		if(selectedStationIndex == -1){
			return;
		}
		system("cls");
	}while(selectedStationIndex < 1 || selectedStationIndex > nationStationSize);

	selectedStation = searchNationStation(selectedStationIndex);
	manageNationStation(selectedStation);
}
 
void printAllStationMapMenu(){
	if(root == NULL){
		printf("  There is no nation station in the system...");
		gchr
		return;
	}

	printf("  All Station :\n\n");
	printAllStationMap();
	printf("\n  Press enter to continue...");
	gchr
}

void deleteNationStation(nationStation *curr){
	if(curr->up){
		curr->up->down = NULL;
		if(curr == root){
			root = curr->up;
		}
	}
	if(curr->down){
		curr->down->up = NULL;
		if(curr == root){
			root = curr->down;
		}
	}
	if(curr->left){
		curr->left->right = NULL;
		if(curr == root){
			root = curr->left;
		}
	}
	if(curr->right){
		curr->right->left = NULL;
		if(curr == root){
			root = curr->right;
		}
	}
	
	free(curr);

	if(curr == root){
		root = NULL;
	}
	
	nationStationSize--;
}

void deleteNationStationMenu(){
	if(root == NULL){
		printf("  There is no nation station in the system...");
		gchr
		return;
	}

	int deletedStationIndex;
	nationStation *deletedStation = NULL;

	do{
		system("cls");
		printf("  All Nation Station [-1 to exit]:\n\n");
		printAllStationMap();
		viewNationStationOrdered(NATION_STATION_DELETE);
		printf("  Input station to be deleted : ");
		scanf("%d", &deletedStationIndex);
		if(deletedStationIndex == -1){
			return;
		}
		deletedStation = searchNationStation(deletedStationIndex);
		gchr
	}while(deletedStationIndex < 1 || deletedStationIndex > nationStationSize
				|| (!isNationStationLeaf(deletedStation) && !isNationStationLoop(deletedStation)));

	deleteNationStation(deletedStation);
	system("cls");
	printf("  Station deleted!\n");
	printf("  Press enter to continue...");
	gchr
}

void addNewNationStationMenu(){
	char name[100];
	int ticketPrice;

	do{
		printf("  Enter the Station Name [5-100 Characters, 2 Words Minimal, Unique] [x to exit] : ");
		scanf("%[^\n]", name);
		gchr
		if(strcasecmp(name, "x") == 0){
			return;
		}
	}while(!isStationNameValid(name));

	do{
		printf("  Enter the Station Ticket Price [Rp. 100.000 - Rp. 1.000.000] [-1 to exit] : Rp. ");
		scanf("%d", &ticketPrice);
		gchr
		if(ticketPrice == -1){
			return;
		}
	}while(!isStationTicketPriceValid(ticketPrice, NATION_STATION));

	system("cls");

	if(root == NULL){
		pushFirstNationStation(name, ticketPrice);
	}
	else{
		int selectedStationIndex;
		nationStation *selectedStation;
		int flag = true;
		char again[100];
		
		do{
			printAllStationMap();
			printf("  Which station can connect to this station? [-1 to exit]\n");
			viewNationStationOrdered(NATION_STATION_INSERT);
			printf("  >> ");
			scanf("%d", &selectedStationIndex);
			gchr
			
			if(selectedStationIndex == -1){
				return;
			}
			selectedStation = searchNationStation(selectedStationIndex);
			system("cls");
		}while(selectedStationIndex < 1 || selectedStationIndex > nationStationSize
					|| isNationStationFull(selectedStation));

		int selectedDirection;
		nationStation *tempArr[4] = {selectedStation->up, selectedStation->down,
										selectedStation->left, selectedStation->right};
		do{
			printAllStationMap();
			printf("  Selected Station [-1 to exit] : %s\n",selectedStation->name);
			printf("  1. Up -> %s\n", selectedStation->up ? selectedStation->up->name : "None");
			printf("  2. Down -> %s\n", selectedStation->down ? selectedStation->down->name : "None");
			printf("  3. Left -> %s\n", selectedStation->left ? selectedStation->left->name : "None");
			printf("  4. Right -> %s\n", selectedStation->right ? selectedStation->right->name : "None");
			printf("  >> ");
			scanf("%d", &selectedDirection);
			if(selectedDirection == -1){
				return;
			}
			gchr
			system("cls");
		}while(selectedDirection < 1 || selectedDirection > 4 || tempArr[selectedDirection-1]
					|| !isNationStationSpaceEmpty(selectedDirection, selectedStation));

		nationStation *s = NULL;

		if(selectedDirection == 1){
			s = pushUpNationStation(selectedStation, name, ticketPrice);
		}
		else if(selectedDirection == 2){
			s = pushDownNationStation(selectedStation, name, ticketPrice);
		}
		else if(selectedDirection == 3){
			s = pushLeftNationStation(selectedStation, name, ticketPrice);
		}
		else if(selectedDirection == 4){
			s = pushRightNationStation(selectedStation, name, ticketPrice);
		}
		
		int coord[2][4] = {{-1,1,0,0},{0,0,-1,1}};
		int count = 0;
		
		for(int i = 0; i < 4; i++){
			if(searchNationStationCoord(s->row + coord[0][i], s->column + coord[1][i]) == NULL){
				count++;
			}
			else if(i == 0 && s->up && s == s->up->down){
				count++;
			}
			else if(i == 1 && s->down && s == s->down->up){
				count++;
			}
			else if(i == 2 && s->left && s == s->left->right){
				count++;
			}
			else if(i == 3 && s->right && s == s->right->left){
				count++;
			}
		}
		
		if(count == 4){
			printf("  %s has been Added to the System!\n", name);
		 	printf("  Press enter to continue...");
		 	gchr
			return;
		}		
		
		do{
			printf("  Do you want to connect this station to other station? [Yes | No] : ");
			scanf("%[^\n]", again);
			gchr
			system("cls");
		}while(strcmp(again, "Yes") != 0 && strcmp(again, "No") != 0);
		
		if(strcmp(again, "No") == 0){
			flag = false;
		}
		
		int connect;

		while(flag){
			printAllStationMap();
			printf("  Neighbour station :\n");
			printNeighbourNationStation(s);
			printf("  Choose which direction you want to connect [-1 to exit] : ");
			scanf("%d", &connect);
			gchr
			system("cls");
			if(connect == -1){
				break;
			}
			
			nationStation *temp = searchNationStationCoord(s->row + coord[0][connect-1], 
																s->column + coord[1][connect-1]);
						
			if(temp){
				if(connect == 1 && temp->down == NULL){
					temp->down = s;
					s->up = temp;
				}
				else if(connect == 2 && temp->up == NULL){
					temp->up = s;
					s->down = temp;
				}
				else if(connect == 3 && temp->right == NULL){
					temp->right = s;
					s->left = temp;
				}
				else if(connect == 4 && temp->left == NULL){
					temp->left = s;
					s->right = temp;
				}
			}
		}
		
		system("cls");
			
	}

	printf("  %s has been Added to the System!\n", name);
 	printf("  Press enter to continue...");
 	gchr
}

void backtrackNationStation(nationStation *source, nationStation *dest){
	int totalTicketPrice = 0;
	char *output = (char*) malloc(sizeof(char)*100), temp[100];
	char connector[5] = ",";
	int count = 1;
	strcpy(output, dest->name);
	strcpy(temp, dest->name);

	while(headSN){
		if(strcmp(headSN->to->name, temp) == 0){
			totalTicketPrice += headSN->to->ticketPrice;
			output = strcat(output, connector);
			output = strcat(output, headSN->from->name);
			strcpy(temp, headSN->from->name);
			count++;
		}

		popNationStack();
	}

	char arr[count][100];
	char *token = strtok(output, connector);

	printf("  Path from %s to %s :\n\n  ", source->name, dest->name);
	int i = 0;
	while(token != NULL){
		strcpy(arr[i], token);
		token = strtok(NULL, connector);
		i++;
	}

	for(int j = count - 1; j >= 0; j--){
		if(j > 0){
			printf("%s -> ", arr[j]);
		}
		else{
			printf("%s", arr[j]);
		}
	}

	printf("\n  Total Ticket Price : %d", totalTicketPrice);
	printf("\n\n  Press enter to continue...");
	gchr
}

void findNationStationRoute(nationStation *source, nationStation *dest){
	neutralizeNationStation(root);
	pushNationQueue(source);
	source->printed = true;

	while(headQN){
		if(strcmp(headQN->station->name, dest->name) == 0){
			backtrackNationStation(source, dest);
			popAllNationQueue();
			popAllNationStack();
			return;
		}
		else{
			nationStation *arr[4] = {headQN->station->right, headQN->station->left,
										headQN->station->up, headQN->station->down};

			for(int i = 0; i < 4; i++){
				if(arr[i] && !arr[i]->printed){
					pushNationQueue(arr[i]);
					pushNationStack(headQN->station, arr[i]);
					arr[i]->printed = true;
				}
			}
		}

		popNationQueue();
	}
}

void findNationStationRouteMenu(){
	int sourceStationIndex, destStationIndex;
	nationStation *sourceStation, *destStation;
	
	if(nationStationSize < 2 ){
		printf("  You must have atleast 2 station to find a route!");
		gchr
		return;
	}

	do{
		printf("  All Nation Station [-1 to exit]:\n\n");
		printAllStationMap();
		viewNationStationOrdered(NATION_STATION_VIEW);
		printf("  Input Source Station : ");
		scanf("%d", &sourceStationIndex);
		if(sourceStationIndex == -1){
			return;
		}
		gchr
		system("cls");
	}while(sourceStationIndex < 1 || sourceStationIndex > nationStationSize);

	do{
		printf("  All Nation Station [-1 to exit]:\n\n");
		printAllStationMap();
		viewNationStationOrdered(NATION_STATION_VIEW);
		printf("  Input Destination Station : ");
		scanf("%d", &destStationIndex);
		if(destStationIndex == -1){
			return;
		}
		gchr
		system("cls");
	}while(sourceStationIndex < 1 || sourceStationIndex > nationStationSize
			|| destStationIndex == sourceStationIndex);

	sourceStation = searchNationStation(sourceStationIndex);
	destStation = searchNationStation(destStationIndex);
	findNationStationRoute(sourceStation, destStation);
}

void openingScene(){
	char title[][100] ={"     _                 _                ____  _   _ _ \n",
						"    | | _____ _ __ ___| |_ __ _    __ _|  _ \\| | | (_)\n",
						"    | |/ / _ \\ '__/ _ \\ __/ _` |  / _` | |_) | |_| | |\n",
						"    |   <  __/ | |  __/ || (_| | | (_| |  __/|  _  | |\n",
						"    |_|\\_\\___|_|  \\___|\\__\\__,_|  \\__,_|_|   |_| |_|_|\n",
						"                                                      \n"};

	char train[][100] = { "___________   _______________________________________^__\n",
						  " ___   ___ |||  ___   ___   ___    ___ ___  |   __  ,----\\\n",
						  "|   | |   |||| |   | |   | |   |  |   |   | |  |  | |_____\\\n",
						  "|___| |___|||| |___| |___| |___|  | O | O | |  |  |        \\\n",
						  "           |||                    |___|___| |  |__|         )\n",
						  "___________|||______________________________|______________/\n",
						  "           |||                                        /--------\n",
						  "-----------'''---------------------------------------'\n"};

	printf("\n    Press space to skip...\n");

	for(int i = 0; i < 6; i+=2){
		if(GetAsyncKeyState(VK_SPACE)){
			return;
		}
		printf("%s", title[i]);
		printf("%s", title[i+1]);
		Sleep(500);
	}

	for(int i = 0; i < 8; i+=2){
		if(GetAsyncKeyState(VK_SPACE)){
			return;
		}
		printf("%s", train[i]);
		printf("%s", train[i+1]);
		Sleep(500);
	}

	printf("\n    Press enter to continue...");
	gchr
	system("cls");
}

void closingScene(){
		char title[][100] ={"     _                 _                ____  _   _ _ \n",
						"    | | _____ _ __ ___| |_ __ _    __ _|  _ \\| | | (_)\n",
						"    | |/ / _ \\ '__/ _ \\ __/ _` |  / _` | |_) | |_| | |\n",
						"    |   <  __/ | |  __/ || (_| | | (_| |  __/|  _  | |\n",
						"    |_|\\_\\___|_|  \\___|\\__\\__,_|  \\__,_|_|   |_| |_|_|\n",
						"                                                      \n"};

	char train[][200] = { "_________________________   _________________________   _______________________________________^__\n",
						  "  ___   ___   ___   ___  |||  ___   ___   ___   ___  |||  ___   ___   ___    ___ ___  |   __  ,----\\\n",
						  " |   | |   | |   | |   | ||| |   | |   | |   | |   | ||| |   | |   | |   |  |   |   | |  |  | |_____\\\n",
						  " |___| |___| |___| |___| ||| |___| |___| |___| |___| ||| |___| |___| |___|  | O | O | |  |  |        \\\n",
						  "                         |||                         |||                    |___|___| |  |__|         )\n",
						  "_________________________|||_________________________|||______________________________|______________/\n",
						  "                         |||                         |||                                        /--------\n",
						  "-------------------------```-------------------------'''---------------------------------------'\n"};

	
	int j = 40;
	fflush(stdin);
	for(int i = 0; i < 10; i++){
		system("cls");
		printf("\n    Press space to skip...\n");

		for(int i = 0; i < 6; i++){
			printf("%s", title[i]);
		}
		
		for(int i = 0; i < 8; i++){
			for(int k = j; k < strlen(train[i]); k++){
				printf("%c", train[i][k]);
			}
		}
		j-=5;
		
		Sleep(500);
		
		if(GetAsyncKeyState(VK_SPACE)){
			return;
		}
	}

	printf("\n    Thank you for using this application...");
	gchr
	system("cls");
}

int main(){
	_COORD coordinates;
    coordinates.X = 1000;
    coordinates.Y = 1000;

    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    if (0 == SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),coordinates)){
        return -1;
    }
    
	openingScene();
	int menu;
	
	//dummy :D
	pushFirstNationStation("Jakarta Station", 100000);
	pushFirstCityStation(root, "Ancol Station", 75000);
	pushLeftCityStation(root, root->root, "Jayakarta Station", 60000);
	pushUpCityStation(root, root->root, "Juanda Station", 80000);
	pushRightCityStation(root, root->root, "Gambir Station", 80000);
	pushUpNationStation(root, "Poncol Station", 125000);
	pushDownNationStation(root, "Tawang Station", 110000);
	pushLeftNationStation(root->up, "Bandung Station", 120000);
	pushRightNationStation(root, "Pekalongan Station", 130000);

	do{
		system("cls");
		menu = 0;
		printf("     _                 _                ____  _   _ _ \n");
		printf("    | | _____ _ __ ___| |_ __ _    __ _|  _ \\| | | (_)\n");
		printf("    | |/ / _ \\ '__/ _ \\ __/ _` |  / _` | |_) | |_| | |\n");
		printf("    |   <  __/ | |  __/ || (_| | | (_| |  __/|  _  | |\n");
		printf("    |_|\\_\\___|_|  \\___|\\__\\__,_|  \\__,_|_|   |_| |_|_|\n");
		printf("                                                      \n");
		printf("  1. Add New Nation Station\n");
		printf("  2. Delete Nation Station\n");
		printf("  3. Manage Nation Station\n");
		printf("  4. View All Station\n");
		printf("  5. Find Nation Station Route\n");
		printf("  6. Exit\n");
		printf("  >> ");
		scanf("%d", &menu);
		gchr
		system("cls");
		if(menu == 1){
			addNewNationStationMenu();
		}
		else if(menu == 2){
			deleteNationStationMenu();
		}
		else if(menu == 3){
			manageNationStationMenu();
		}
		else if(menu == 4){
			printAllStationMapMenu();
		}
		else if(menu == 5){
			findNationStationRouteMenu();
		}
	}while(menu != 6);
	
	closingScene();
}
