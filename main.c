//
//  Poker
//
//  Copyright (c) 2016 He Kai Lim. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int readcard(int a);
int findhands(int find[7], int password);
int uncook(int figure[5], int suit[5], int hand);

int main(void)
{
    char name[50];
    printf("Welcome to Texas Hold'em Poker!\n");
    printf("Enter your name: ");
    scanf("%s", name);
 
    // Fisher-Yates shuffle algorithm
    int newdeck[52];
    for (int x=0; x<52; x++)
    {
        newdeck[x] = x+1;
    }
    int shuffledeck[52];
    int x;
    srand ((unsigned)time(0));
    
    for (x=51; x>=0; x--)
    {
        int count = rand() % (x+1) +1;
        int test = 0;
        int card = 0;
        do
        {
            for (int y=0; y<52; y++)
            {
                if (newdeck[y]>0)
                {
                    test = test + 1;
                    card = card + 1;
                }
                if (test>=count)
                    y = 52;
                else if (newdeck[y]==0)
                {
                    test = test;
                    card = card + 1;
                }
            }
        }
        while (test<count);
        int q = newdeck[card-1];
        shuffledeck[51-x] = q;
        newdeck[card-1] = 0;
    }
    
    // Track progression of cards through the deck
    int p = 0;
    
    // Dealing Starting Cards
    printf("\n%s, you are dealt with:\n", name);
    
    int player1 = shuffledeck[p];
    int a = player1;
    readcard(a);
    p = p + 1;
    
    int player2 = shuffledeck[p];
    a = player2;
    readcard(a);
    p = p + 1;
    
    // Burn 1 card
    p = p + 1;
    // Dealing to computer
    int computer1 = shuffledeck[p];
    p = p + 1;
    int computer2 = shuffledeck[p];
    p = p + 1;
    
    printf ("\nThe computer also has been dealt his own cards\n");
    
    // Choice 1
    char choice[5];
    printf("Raise? (y/n) \n");
    scanf("%s", &choice[0]);
    
    if (choice[0] == 110)
    {
        printf("\nGame Over. Have a nice day.\n");
        return (0);
    }
    
    // 3 Community Cards
    if (choice[0] == 121)
    {
        printf("\nAlright! Dealer has dealt these Community Cards:\n");
    }
    // Burn 1 card
    p = p + 1;
    
    int com1 = shuffledeck[p];
    a = com1;
    readcard(a);
    p = p + 1;
    
    int com2 = shuffledeck[p];
    a = com2;
    readcard(a);
    p = p + 1;
    
    int com3 = shuffledeck[p];
    a = com3;
    readcard(a);
    p = p + 1;
    
    // Choice 2
    printf("\nContinue? (y/n) \n");
    scanf("%s", &choice[1]);
    
    if (choice[1] == 110)
    {
        printf("\nGame Over. Have a nice day.\n");
        return (0);
    }

    // 4th Community Card
    if (choice[1] == 121)
    {
        printf("\nWow! There is a new Community Card on the table:\n");
    }
    // burn 1 card
    p = p + 1;
    
    a = com1;
    readcard(a);
    a = com2;
    readcard(a);
    a = com3;
    readcard(a);
    
    int com4 = shuffledeck[p];
    a = com4;
    readcard(a);
    p = p + 1;
    
    // Choice 3
    printf("\nStill continue? (y/n) \n");
    scanf("%s", &choice[2]);
    
    if (choice[2] == 110)
    {
        printf("\nGame Over. Have a nice day.\n");
        return (0);
    }

    // 5th Community Card
    if (choice[2] == 121)
    {
        printf("\nOK. These are the 5 Community Cards:\n");
    }
    // burn 1 card
    p = p + 1;
    
    a = com1;
    readcard(a);
    a = com2;
    readcard(a);
    a = com3;
    readcard(a);
    a = com4;
    readcard(a);
    
    int com5 = shuffledeck[p];
    a = com5;
    readcard(a);
    p = p + 1;
    
    // Choice 4
    printf("\nReveal? (y/n) \n");
    scanf("%s", &choice[2]);
    
    if (choice[3] == 110)
    {
        printf("\nGame Over. Have a nice day.\n");
        return (0);
    }
    if (choice[3] == 121)
    {
        printf("\n");
    }
    
    // Analyze player hands
    int find[7] = {player1, player2, com1, com2, com3, com4, com5};
    int password = 10;
    int playerpoint = findhands(find, password);
    int playerfigure[5];
    int playersuit[5];
    
    for (int q=0; q<5; q++)
    {
        password = q;
        playerfigure[q] = findhands(find, password);
    }
    for (int q=5; q<10; q++)
    {
        password = q;
        playersuit[q-5] = findhands(find, password);
    }
    
    // Analyze computer hands
    find[0] = computer1;
    find[1] = computer2;
    find[2] = com1;
    find[3] = com2;
    find[4] = com3;
    find[5] = com4;
    find[6] = com5;
    password = 10;
    int computerpoint = findhands(find, password);
    int computerfigure[5];
    int computersuit[5];
    
    for (int q=0; q<5; q++)
    {
        password = q;
        computerfigure[q] = findhands(find, password);
    }
    for (int q=5; q<10; q++)
    {
        password = q;
        computersuit[q-5] = findhands(find, password);
    }
    
    // show cards
    int hand;
    printf("~~~~~~~~~~~~~~~~~~~~~~~~ DRUM ROLL ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    
    // player cards
    int playerfinal[5];
    int figure[5]= {playerfigure[0], playerfigure[1], playerfigure[2], playerfigure[3], playerfigure[4]};
    int suit[5] = {playersuit[0], playersuit[1], playersuit[2], playersuit[3], playersuit[4]};
    
    for (int q=0; q<5; q++)
    {
        hand = q;
        playerfinal[q] =uncook(figure, suit, hand);
    }
    printf("%s, ", name);
    if (playerpoint == 9)
        printf("you have a STRAIGHT FLUSH!\n");
    if (playerpoint == 8)
        printf("you have a FOUR-OF-A-KIND!\n");
    if (playerpoint == 7)
        printf("you have a FULL HOUSE!\n");
    if (playerpoint == 6)
        printf("you have a FLUSH!\n");
    if (playerpoint == 5)
        printf("you have a STRAIGHT!\n");
    if (playerpoint == 4)
        printf("you have a THREE-OF-A-KIND!\n");
    if (playerpoint == 3)
        printf("you have TWO PAIRs!\n");
    if (playerpoint == 2)
        printf("you have a PAIR!\n");
    if (playerpoint == 1)
        printf("you have a HIGH CARD!\n");
    
    printf("You have this hand:\n");
    for (int q=0; q<5; q++)
    {
        a = playerfinal[q];
        readcard(a);
    }
    printf("\n");
    
    // computer cards
    int computerfinal[5];
    for (int q=0; q<5; q++)
        figure[q] = computerfigure[q];
    for (int q=0; q<5; q++)
        suit[q] = computersuit[q];
    
    for (int q=0; q<5; q++)
    {
        hand = q;
        computerfinal[q] =uncook(figure, suit, hand);
    }
    
    if (computerpoint == 9)
        printf("Computer has a STRAIGHT FLUSH!\n");
    if (computerpoint == 8)
        printf("Computer has a FOUR-OF-A-KIND!\n");
    if (computerpoint == 7)
        printf("Computer has a FULL HOUSE!\n");
    if (computerpoint == 6)
        printf("Computer has a FLUSH!\n");
    if (computerpoint == 5)
        printf("Computer has a STRAIGHT!\n");
    if (computerpoint == 4)
        printf("Computer has a THREE-OF-A-KIND!\n");
    if (computerpoint == 3)
        printf("Computer has TWO PAIRS!\n");
    if (computerpoint == 2)
        printf("Computer has a PAIR!\n");
    if (computerpoint == 1)
        printf("Computer has a HIGH CARD!\n");
    
    printf("Computer has this hand:\n");
    for (int q=0; q<5; q++)
    {
        a = computerfinal[q];
        readcard(a);
    }
    printf("\n");
    
    // Compare hands (type)
    if (playerpoint > computerpoint)
        printf("YOU WIN!\n");
    if (computerpoint > playerpoint)
        printf("YOU LOSE!\n");
    if (computerpoint == playerpoint)
        printf("COULD IT BE A DRAW???...\n");
    
    // Compare hands (in detail)
    if (computerpoint == playerpoint)
    {
        int q;
        for (q=0; q<5; q++)
        {
            if (playerfigure[q] > computerfigure[q])
            {
                printf("YOU WIN! (by a margin)\n");
                q = 6;
            }
            
            if (playerfigure[q] < computerfigure[q])
            {
                printf("YOU LOSE! (by a margin)\n");
                q = 6;
            }
        }
        if (q == 5)
            printf("IT REALLY IS A DRAW! CONGRATULATIONS!\n");
    }
    
    // End
    printf("\n~The End~\n");
    char closeVariable;
    printf("\nThanks for playing! (Enter any key to exit) \n");
    scanf("%s", &closeVariable);
    return (0);

}


// readcard
int readcard(int a)
{
    if (2==2)
    {
        if (a == 1 || a == 14 || a == 27 || a == 40)
            printf("Two ");
        if (a == 2 || a == 15 || a == 28 || a == 41)
            printf("Three ");
        if (a == 3 || a == 16 || a == 29 || a == 42)
            printf("Four ");
        if (a == 4 || a == 17 || a == 30 || a == 43)
            printf("Five ");
        if (a == 5 || a == 18 || a == 31 || a == 44)
            printf("Six ");
        if (a == 6 || a == 19 || a == 32 || a == 45)
            printf("Seven ");
        if (a == 7 || a == 20 || a == 33 || a == 46)
            printf("Eight ");
        if (a == 8 || a == 21 || a == 34 || a == 47)
            printf("Nine ");
        if (a == 9 || a == 22 || a == 35 || a == 48)
            printf("Ten ");
        if (a == 10 || a == 23 || a == 36 || a == 49)
            printf("Jack ");
        if (a == 11 || a == 24 || a == 37 || a == 50)
            printf("Queen ");
        if (a == 12 || a == 25 || a == 38 || a == 51)
            printf("King ");
        if (a == 13 || a == 26 || a == 39 || a == 52 || a == 0)
            printf("Ace ");
    }
    
    if (2==2)
    {
        if (a <14)
            printf ("of Spades\n");
        if (a >13 && a <27)
            printf ("of Hearts\n");
        if (a >26 && a <40)
            printf ("of Diamonds\n");
        if (a >39)
            printf ("of Clubs\n");
    }
    

}


// reverse from cardsuit format to readcard format
int uncook(int figure[5], int suit[5], int hand)
{
    int multiplier;
    int other;
    int thing[5];
    for (int x=0; x<5; x++)
    {
        multiplier = suit[x]-1;
        other = multiplier * 13;
        thing[x] = figure[x] + other;
    }
    if (hand == 0)
        return (thing[0]);
    if (hand == 1)
        return (thing[1]);
    if (hand == 2)
        return (thing[2]);
    if (hand == 3)
        return (thing[3]);
    if (hand == 4)
        return (thing[4]);
    return (0);
}


//findhands
int findhands (int find[7], int password)
{
    // break down to components
    int figure[7];
    for (int x=0; x<7; x++)
    {
        if (find[x]>13)
        {
            figure[x] = find[x] - 13;
            if (figure[x]>13)
            {
                figure[x] = figure[x] - 13;
                if (figure[x]>13)
                    figure[x] = figure[x] - 13;
            }
        }
        if (find[x]<14)
        {
            figure[x] = find[x];
        }
    }
    
    int suit[7];
    for (int x=0; x<7; x++)
    {
        if (find[x] < 14)
            suit[x] = 1;
        if (find[x] > 13 && find[x] < 27)
            suit[x] = 2;
        if (find[x] > 26 && find[x] < 40)
            suit[x] = 3;
        if (find[x] > 39)
            suit[x] = 4;
    }
    
    // Selected card memory
    int point = 1;
    int cardfigure[7];
    int cardsuit[7];
    int tempfigure[7];
    int tempsuit[7];
    for (int x=0; x<7; x++)
    {
        tempfigure[x] = 0;
        tempsuit[x] = 0;
        cardfigure[x] = 0;
        cardsuit[x] = 0;
    }
    
    // 9. STRAIGHT FLUSH TEST
    if (point <9)
    {
        for (int x=0; x<7; x++)
        {
            // PART ONE 6. FLUSH TEST
            int nineone = 0;
            int n = suit[x];
            for (int y=0; y<7; y++)
            {
                if (suit[y] == n)
                {
                    tempsuit[nineone] = suit[y];
                    tempfigure[nineone] = figure[y];
                    nineone = nineone + 1;
                }
            }
            if (nineone > 4)
            {
                x = 7;
                // PART TWO STRAIGHT TEST -- ACE IS HIGH
                for (int y=0; y<7; y++)
                {
                    int m = tempfigure[y];
                    for (int z=0; z<7; z++)
                        if (tempfigure[z] == m-1)
                            for (int w=0; w<7; w++)
                                if (tempfigure[w] == m-2)
                                    for (int v=0; v<7; v++)
                                        if (tempfigure[v] == m-3)
                                            for (int u=0; u<7; u++)
                                                if (tempfigure[u] == m-4 && tempsuit[y]==tempsuit[z] && tempsuit[z]==tempsuit[w] && tempsuit[w]==tempsuit[v] && tempsuit[v]==tempsuit[u] && tempfigure[y]>cardfigure[0])
                                                {
                                                    point = 9;
                                                    cardfigure[0] = tempfigure[y];
                                                    cardsuit[0] = tempsuit[y];
                                                    cardfigure[1] = tempfigure[z];
                                                    cardsuit[1] = tempsuit[z];
                                                    cardfigure[2] = tempfigure[w];
                                                    cardsuit[2] = tempsuit[w];
                                                    cardfigure[3] = tempfigure[v];
                                                    cardsuit[3] = tempsuit[v];
                                                    cardfigure[4] = tempfigure[u];
                                                    cardsuit[4] = tempsuit[u];
                                                    x = 8;
                                                }
                }
            }
            
            if (nineone>4 && x==7)
            {
                for (int y=0; y<7; y++)
                    if (tempfigure[y]==13)
                        tempfigure[y]= 0;
                
                // PART TWO STRAIGHT TEST -- ACE IS LOW
                for (int y=0; y<7; y++)
                {
                    int m = tempfigure[y];
                    for (int z=0; z<7; z++)
                        if (tempfigure[z] == m-1)
                            for (int w=0; w<7; w++)
                                if (tempfigure[w] == m-2)
                                    for (int v=0; v<7; v++)
                                        if (tempfigure[v] == m-3)
                                            for (int u=0; u<7; u++)
                                                if (tempfigure[u] == m-4 && tempsuit[y]==tempsuit[z] && tempsuit[z]==tempsuit[w] && tempsuit[w]==tempsuit[v] && tempsuit[v]==tempsuit[u] && tempfigure[y]>cardfigure[0])
                                                {
                                                    point = 9;
                                                    cardfigure[0] = tempfigure[y];
                                                    cardsuit[0] = tempsuit[y];
                                                    cardfigure[1] = tempfigure[z];
                                                    cardsuit[1] = tempsuit[z];
                                                    cardfigure[2] = tempfigure[w];
                                                    cardsuit[2] = tempsuit[w];
                                                    cardfigure[3] = tempfigure[v];
                                                    cardsuit[3] = tempsuit[v];
                                                    cardfigure[4] = 13;
                                                    cardsuit[4] = tempsuit[u];
                                                    x = 8;
                                                }
                }
            }
        }
    }
    
    // 8. FOUR-OF-A-KIND TEST
    if (point <8)
    {
        for (int x=0; x<7; x++)
        {
            int eightone = 0;
            int eighttwo = 0;
            int n = figure[x];
            for (int y=0; y<7; y++)
            {
                if (figure[y] == n)
                {
                    cardfigure[eightone] = figure[y];
                    cardsuit[eightone] = suit[y];
                    eightone = eightone + 1;
                }
                else
                {
                    tempfigure[eighttwo] = figure[y];
                    tempsuit[eighttwo] = suit[y];
                    eighttwo = eighttwo + 1;
                }
            }
            if (eightone > 3)
            {
                x = 7;
                point = 8;
                for (int z=1; z<14; z++)
                    for (int w=0; w<3; w++)
                        if (tempfigure[w] == z)
                        {
                            cardfigure[4] = tempfigure[w];
                            cardsuit[4] = tempsuit[w];
                        }
            }
        }
    }
    
    // 7. FULL HOUSE TEST
    if (point <7)
    {
        for (int x=0; x<7; x++)
        {
            int sevenone = 0;
            int seventwo = 0;
            int n = figure[x];
            for (int y=0; y<7; y++)
            {
                if (figure[y] == n)
                {
                    tempfigure[sevenone] = figure[y];
                    tempsuit[sevenone] = suit[y];
                    sevenone = sevenone + 1;
                }
            }
            if (sevenone > 2)
            {
                x = 7;
                for (int z=0; z<7; z++)
                {
                    if (figure[z] != n)
                        for (int w=0; w<7; w++)
                            if (figure[z] == figure[w] && z!=w)
                            {
                                seventwo = seventwo + 1;
                                point = 7;
                            }
                }
                
                if (seventwo > 1)
                {
                    for (int z=0; z<7; z++)
                        for (int w=0; w<7; w++)
                            if (figure[z]!=n && figure[z]==figure[w] && z!=w)
                            {
                                if (seventwo == 4)
                                {
                                    int q = 3;
                                    for (int v=13; v>0; v--)
                                        for (int u=0; u<7; u++)
                                            if (figure[u]==v && figure[u]!=tempfigure[0])
                                            {
                                                tempfigure[q] = figure[u];
                                                tempsuit[q] = suit[u];
                                                q = q + 1;
                                                z = 7;
                                                w = 7;
                                            }
                                    
                                }
                                if (figure[z] > n && seventwo==6)
                                {
                                    tempfigure[3] = tempfigure[0];
                                    tempsuit[3] = tempsuit[0];
                                    tempfigure[4] = tempfigure[1];
                                    tempsuit[4] = tempsuit[1];
                                    tempfigure[0] = figure[z];
                                    tempsuit[0] = suit[z];
                                    for (int v=0; v<7; v++)
                                    {
                                        int o = 1;
                                        if (figure[v]==figure[z] && v!=z)
                                        {
                                            tempfigure[o] = tempfigure[v];
                                            o = o + 1;
                                        }
                                    }
                                    z = 7;
                                    w = 7;
                                }
                                else if (figure[z] <= n || seventwo==2)
                                {
                                    tempfigure[3] = figure[z];
                                    tempsuit[3] = suit[z];
                                    tempfigure[4] = figure[w];
                                    tempsuit[4] = suit[w];
                                    z = 7;
                                    w = 7;
                                }
                            }
                    for (int q=0; q<5; q++)
                    {
                        cardfigure[q] = tempfigure[q];
                        cardsuit[q] = tempsuit[q];
                    }
                }
            }
        }
    }
    
    // 6. FLUSH TEST
    if (point <6)
    {
        for (int q=0; q<7; q++)
            tempfigure[q] = 0;
        for (int q=0; q<7; q++)
            tempsuit[q] = 0;
        
        for (int x=0; x<7; x++)
        {
            int sixone = 0;
            for (int y=0; y<7; y++)
            {
                if (suit[y] == suit[x])
                {
                    tempsuit[sixone] = suit[y];
                    tempfigure[sixone] = figure[y];
                    sixone = sixone + 1;
                }
            }
            if (sixone > 4)
            {
                int w = 0;
                for (int y=13; y>0; y--)
                    for (int z=0; z<7; z++)
                        if (tempfigure[z] == y)
                        {
                            cardfigure[w] = tempfigure[z];
                            cardsuit[w] = tempsuit[z];
                            w = w + 1;
                        }
                point = 6;
                x = 8;
            }
        }
    }
    
    // 5. STRAIGHT TEST
    if (point <5)
    {
        cardfigure[0] = 0;
        // ACE IS HIGH
        for (int y=0; y<7; y++)
        {
            int m = figure[y];
            for (int z=0; z<7; z++)
                if (figure[z] == m-1)
                    for (int w=0; w<7; w++)
                        if (figure[w] == m-2)
                            for (int v=0; v<7; v++)
                                if (figure[v] == m-3)
                                    for (int u=0; u<7; u++)
                                        if (figure[u] == m-4 && figure[y]>cardfigure[0])
                                        {
                                            cardfigure[0] = figure[y];
                                            cardsuit[0] = suit[y];
                                            cardfigure[1] = figure[z];
                                            cardsuit[1] = suit[z];
                                            cardfigure[2] = figure[w];
                                            cardsuit[2] = suit[w];
                                            cardfigure[3] = figure[v];
                                            cardsuit[3] = suit[v];
                                            cardfigure[4] = figure[u];
                                            cardsuit[4] = suit[u];
                                            point = 5;
                                        }
        }
        
        // ACE IS LOW
        if (point <5)
        {
            for (int q=0; q<7; q++)
                tempfigure[q] = figure[q];
            for (int q=0; q<7; q++)
                if (tempfigure[q] == 13)
                    tempfigure[q] = 0;
            
            for (int y=0; y<7; y++)
            {
                int m = tempfigure[y];
                for (int z=0; z<7; z++)
                    if (tempfigure[z] == m-1)
                        for (int w=0; w<7; w++)
                            if (tempfigure[w] == m-2)
                                for (int v=0; v<7; v++)
                                    if (tempfigure[v] == m-3)
                                        for (int u=0; u<7; u++)
                                            if (tempfigure[u] == m-4 && figure[y]>cardfigure[0])
                                            {
                                                cardfigure[0] = tempfigure[y];
                                                cardsuit[0] = suit[y];
                                                cardfigure[1] = tempfigure[z];
                                                cardsuit[1] = suit[z];
                                                cardfigure[2] = tempfigure[w];
                                                cardsuit[2] = suit[w];
                                                cardfigure[3] = tempfigure[v];
                                                cardsuit[3] = suit[v];
                                                cardfigure[4] = 13;
                                                cardsuit[4] = suit[u];
                                                point = 5;
                                            }
            }
        }
    }
    
    // 4. THREE-OF-A-KIND TEST
    if (point <4)
    {
        for (int x=0; x<7; x++)
        {
            int fourone = 0;
            int n = figure[x];
            for (int y=0; y<7; y++)
            {
                if (figure[y] == n)
                {
                    cardfigure[fourone] = figure[y];
                    cardsuit[fourone] = suit[y];
                    fourone = fourone + 1;
                }
            }
            if (fourone > 2)
            {
                int o = 3;
                for (int z=13; z>0; z--)
                    for (int w=0; w<7; w++)
                    {
                        if (figure[w]==z && figure[w]!=n)
                        {
                            cardfigure[o] = figure[w];
                            cardsuit[o] = suit[w];
                            o = o + 1;
                        }
                    }
                point = 4;
                x = 7;
            }
        }
    }
    
    // 3. TWO PAIR TEST
    if (point<3)
    {
        int m = 0;
        int thing = 0;
        for (int x=0; x<7; x++)
        {
            int threeone = 0;
            for (int y=0; y<7; y++)
                if (figure[y] == figure[x])
                {
                    tempfigure[threeone] = figure[y];
                    tempsuit[threeone] = suit[y];
                    threeone = threeone + 1;
                }
            if (threeone>1)
            {
                for (int y=0; y<7; y++)
                {
                    int threetwo = 2;
                    for (int z=0; z<7; z++)
                        if (figure[z]!=figure[x] && figure[z]==figure[y])
                        {
                            tempfigure[threetwo] = figure[z];
                            tempsuit[threetwo] = suit[z];
                            threetwo = threetwo + 1;
                        }
                    if (threetwo>3)
                    {
                        for (int z=0; z<7; z++)
                        {
                            int threethree = 4;
                            for (int w=0; w<7; w++)
                                if (figure[w]!=figure[y] && figure[w]!=figure[x] && figure[w]==figure[z])
                                {
                                    tempfigure[threethree] = figure[w];
                                    tempsuit[threethree] = suit[w];
                                    threethree = threethree + 1;
                                }
                            if (threethree >5)
                            {
                                thing = 1;
                                z = 7;
                            }
                            
                        }
                        m = 1;
                        x = 7;
                        y = 7;
                    }
                }
            }
        }
        
        if (m == 1)
        {
            point = 3;
            int n = 0;
            if (tempfigure[0] > tempfigure[2])
            {
                for (int x=0; x<4; x++)
                {
                    cardfigure[x] = tempfigure[x];
                    cardsuit[x] = tempsuit[x];
                }
            }
            if (tempfigure[0] < tempfigure[2])
            {
                cardfigure[0] = tempfigure[2];
                cardfigure[1] = tempfigure[3];
                cardfigure[2] = tempfigure[0];
                cardfigure[3] = tempfigure[1];
                cardsuit[0] = tempsuit[2];
                cardsuit[1] = tempsuit[3];
                cardsuit[2] = tempsuit[0];
                cardsuit[3] = tempsuit[1];
            }
            if (thing == 1)
                for (int x=13; x>0; x--)
                    for (int y=0; y<6; y=y+2)
                        if (tempfigure[y] == x)
                            if (n < 4)
                            {
                                cardfigure[n] = tempfigure[y];
                                cardsuit[n] = tempsuit[y];
                                cardfigure[n+1] = tempfigure[y+1];
                                cardsuit[n+1] = tempsuit[y+1];
                                n = n + 2;
                            }
            for (int x=1; x<14; x++)
                for (int y=0; y<7; y++)
                    if (figure[y]!=cardfigure[0] && figure[y]!=cardfigure[2] && figure[y]==x)
                    {
                        cardfigure[4] = figure[y];
                        cardsuit[4] = suit[y];
                    }
        }
    }
    
    // 2. ONE PAIR TEST
    if (point<2)
    {
        int m = 0;
        for (int x=0; x<7; x++)
        {
            int twoone = 0;
            for (int y=0; y<7; y++)
                if (figure[y] == figure[x] && y!=x)
                {
                    cardfigure[twoone] = figure[y];
                    cardsuit[twoone] = suit[y];
                    twoone = twoone + 1;
                    point = 2;
                    m = 1;
                }
        }
        if (m == 1)
        {
            int n = 2;
            for (int x=13; x>0; x--)
                for (int y=0; y<7; y++)
                    if (figure[y]==x && figure[y]!=cardfigure[0])
                    {
                        cardfigure[n] = figure[y];
                        cardsuit[n] = suit[y];
                        n = n + 1;
                    }
        }
    }
    
    // 1. HIGH CARD TEST
    if (point <2)
    {
        int n = 0;
        for (int z=13; z>0; z--)
            for (int y=0; y<7; y++)
                if (figure[y] == z)
                {
                    cardfigure[n] = figure[y];
                    cardsuit[n] = suit[y];
                    n = n +1;
                }
    }
    
    // This is some ingenious shit right here
    if (password == 0)
        return (cardfigure[0]);
    if (password == 1)
        return (cardfigure[1]);
    if (password == 2)
        return (cardfigure[2]);
    if (password == 3)
        return (cardfigure[3]);
    if (password == 4)
        return (cardfigure[4]);
    if (password == 5)
        return (cardsuit[0]);
    if (password == 6)
        return (cardsuit[1]);
    if (password == 7)
        return (cardsuit[2]);
    if (password == 8)
        return (cardsuit[3]);
    if (password == 9)
        return (cardsuit[4]);
    if (password == 10)
        return (point);
    return (0);
}
