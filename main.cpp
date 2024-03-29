#include <iostream>
#include <string>
#include <ctime>
#define MAX_VALUE 21
#define DEALER_MAX 17
#define NUM_OF_CARDS 52

using namespace std;

int check_win(const int& playerSum, const int& dealerSum);
void getChoice(string& choice);

struct card{
    char face;
    string suit;

    card(){};

    void printCard(){
        if (face == 'T') cout << "10" << " of " << suit;
        else cout << face << " of " << suit;
        cout << endl;
    }
};

int i = 0;
card deck[NUM_OF_CARDS];

card dealCard();
void createDeck(card* d);
void printDeck(card* d);
void shuffleDeck(card* d);
void updateDealer(const card& c, int& sum);
void updatePlayer(const card& c, int& sum);

int main(int argc, char* argv[]){
    //The deal
    srand(time(0));

    createDeck(deck);
    shuffleDeck(deck);
    /*printDeck(deck);
    cout << "----------------" << endl;*/

    //deal lan 1
    card playerCard = dealCard();
    card dealerCard = dealCard();
    playerCard.printCard();
    dealerCard.printCard();

    //hien thi sum
    int playerSum = 0, dealerSum = 0;
    updatePlayer(playerCard, playerSum);
    updateDealer(dealerCard, dealerSum);
    cout << "Player's sum: " << playerSum << " - "
    << "Dealer's sum: " << dealerSum << endl;
    
    //deal lan 2
    playerCard = dealCard();
    dealerCard = dealCard();
    playerCard.printCard();
    updatePlayer(playerCard, playerSum);
    updateDealer(dealerCard, dealerSum);
    cout << "Player's sum: " << playerSum << endl;

    //Player's Play
    string playerChoice;
    while (playerSum <= MAX_VALUE){
        getChoice(playerChoice);
        if (playerChoice == "stand"){
            break;
        }
        playerCard = dealCard();
        playerCard.printCard();
        updatePlayer(playerCard, playerSum);
        cout << "Player's sum: " << playerSum << endl;
    }

    //dealer's play
    while (dealerSum < DEALER_MAX){
        dealerCard = dealCard();
        updateDealer(dealerCard, dealerSum);
    }
    cout << "Dealer's final sum is: " << dealerSum << endl;

    //results
    if (check_win(playerSum, dealerSum) == 1) cout << "Congrats! You win!" << endl;
    else if (check_win(playerSum, dealerSum) == 0) cout << "Tie!" << endl;
    else if (check_win(playerSum, dealerSum) == -1) cout << "You lose!" << endl;
    else cout << "Bust! You lose!" << endl;

    return 0;
}

card dealCard(){
    return deck[i++];
}

void updateDealer(const card& c, int& sum){
    if (c.face == 'K' || c.face == 'Q' || c.face == 'J' || c.face == 'T')
        sum += 10;
    else if (c.face == 'A') {
        int sum_temp = sum + 11;
        if (sum_temp <= 21){
            sum += 11;
        } else sum += 1;
    }
    else sum += (int)c.face - '0';
}

void updatePlayer(const card& c, int& sum){
    if (c.face == 'K' || c.face == 'Q' || c.face == 'J' || c.face == 'T')
        sum += 10;
    else if (c.face == 'A') {
        int sum_temp = sum + 11;
        if (sum_temp <= 21){
            cout << "Your card is A. Is it worth 1 or 11?" << endl;
            int choice;
            cin >> choice;
            sum += choice;
        } else sum += 1;
    }
    else sum += (int)c.face - '0';
}

int check_win(const int& playerSum, const int& dealerSum){
    if (playerSum > MAX_VALUE) return -2;
    if (dealerSum > MAX_VALUE || playerSum > dealerSum) return 1;
    else if (playerSum < dealerSum) return -1;
    else return 0;
}

void getChoice(string& choice){
    cout << "hit or stand?" << endl;
    cin >> choice;
    while (!(choice == "hit" || choice == "stand")){
        cout << "Invalid choice. Choose to hit or stand?\n";
        cin >> choice;
    }
}

void createDeck(card* d){
    const string suits[] = {"Spades", "Clubs", "Diamonds", "Hearts"};
    const char faces[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9','T', 'J', 'Q', 'K'};
    int n = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 13; j++){
            d[n].suit = suits[i];
            d[n].face = faces[j];
            n++;
        }
    }
}

void printDeck(card* d){
    for (int i = 0; i < NUM_OF_CARDS; i++){
        d[i].printCard();
    }
}

void shuffleDeck(card* d){
    for (int i = 0; i < NUM_OF_CARDS; i++){
        int m = rand() % NUM_OF_CARDS;
        card temp = d[i];
        d[i] = d[m];
        d[m] = temp;
    }
}