#include "player.h"



void printPlayersArray(Player* arr , int length){
    int i = 0 ;
    printf("****************************** PLAYERS ***************************************\n");
    while (i < length)
    {
        printf("player %d ={id = %d ,name : %s ,score : %d , games played : %d }  \n", i+1 , arr[i].id , arr[i].name , arr[i].score , arr[i].gamesPlayed);
        ++i ;
    }
    printf("number of players : %d \n" , length) ;
    printf("******************************************************************************\n");    
}



/*    
int main() {


    FILE *ptr = initPlayersFile() ;
    // printPlayers(ptr) ;

    Player player = {1 , "rami"  , 900 , 154} ;
    // updatePlayer(ptr , player) ;

    printPlayers(ptr) ;
    int length = getPlayersNumber(ptr) ;
    Player *arr = malloc(sizeof(Player) * length) ;
    if (!arr)
    {
        printf("error malloc\n");
        return 1 ;
    }
    fread(arr , sizeof(Player) , length , ptr ) ;
    printPlayersArray(arr , length) ;
    sortPlayers(arr , length) ;

    printPlayersArray(arr , length) ;

    return 0 ;
}  
 */  




int initPlayersFile() {
    FILE *ptr = fopen(PLAYERS_FILE_NAME ,"rb+") ;
    if (!ptr) {
        printf("file doesn't exist !!\n");
        printf("will create one in this directory \n");
        ptr = fopen(PLAYERS_FILE_NAME , "wb+") ;
        if (!ptr)
        {
            printf("couldn't create the file players");
            return 0 ;
        }
        printf("file created succesfully !\n");   
    }
    printf("file charged successfully \n") ;
    
    int score  = 0; 

    fread(&score , sizeof(score) , 1 , ptr) ; 
    
    return score ;
}


int getPlayersNumber(FILE *ptr) {
    rewind(ptr);
    if (!ptr)
    {
        printf("error file doesn't exist can't get number of players");
        return -1 ;
    }
    
    fseek(ptr , 0 , SEEK_END) ;
    int length = ftell(ptr) / sizeof(Player) ;

    rewind(ptr) ;

    return length ;
}

void addPlayer(FILE *ptr, Player player) {
    int length = getPlayersNumber(ptr) ;
    if (length<0)
    {
        printf("file doesn't exist fatal error\n");
        return;
    }
    fseek(ptr , length*sizeof(player) , SEEK_SET);
    fwrite(&player ,sizeof(player) , 1 , ptr);

    rewind(ptr) ;
} 


void printPlayers(FILE *ptr) {
    int length = getPlayersNumber(ptr) ;
    if (length<0)
    {
        printf("file doesn't exist fatal error\n");
        return;
    }
    rewind(ptr) ;
    int i = 0 ;
    Player buffer ;
    printf("****************************** PLAYERS ***************************************\n");
    while (i < length)
    {
        fread(&buffer , sizeof(Player) , 1 , ptr) ;
        printf("player %d ={id = %d ,name : %s ,score : %d , games played : %d }  \n", i+1 , buffer.id , buffer.name , buffer.score , buffer.gamesPlayed);
        ++i ;
    }
    printf("number of players : %d \n" , length) ;
    printf("******************************************************************************\n");
     rewind(ptr);
}


void deletePlayer(FILE *ptr , int id) {
    rewind(ptr) ;


    FILE *temp = fopen("temp" , "wb+") ;
    if (!temp)
    {
        printf("failed to creat temp file !");
        return ;
    }
    

    int currentPos=0 ;
    Player buffer ;

    while (fread(&buffer , sizeof(buffer) , 1 , ptr) > 0)
        if (buffer.id != id)

            fwrite(&buffer , sizeof(buffer) , 1 , temp);
        

    ptr = fopen(PLAYERS_FILE_NAME , "wb+") ;
    if (!ptr) {
        printf("can't open %s file in wb+ mode !" , PLAYERS_FILE_NAME) ;
        return ;
    }
    rewind(temp) ;

    while (fread(&buffer , sizeof(buffer) , 1 , temp) > 0)
            fwrite(&buffer , sizeof(buffer) , 1 , ptr);
        
    remove("temp") ;
    rewind(ptr) ;
}



void updatePlayer(FILE *ptr , Player player) {
    int length = getPlayersNumber(ptr) ;
    if (length<0)
    {
        printf("file doesn't exist fatal error\n");
        return;
    }
    rewind(ptr) ;

    Player buffer ;
    int i = 0; 
    while (i<length)
    {
        fread(&buffer , sizeof(buffer) , 1 , ptr) ;
        if (buffer.id == player.id)
        {
            if (buffer.score < player.score)
            {
                fseek(ptr , -sizeof(Player) ,SEEK_CUR ) ;
                fwrite(&player , sizeof(Player) , 1 , ptr) ;
                printf("updated player %s successfully ! \n" , player.name);
            }
            
            return ;
        }
        
        ++i ;
    }
    printf("player not found !\n");
        
}


void sortPlayers(Player *arr ,int length) {
    int j =0  ;
    Player key ;
    for (int i = 1; i < length; i++)
    {
        // key =  arr[i] ;
        assignPlayer(&key , arr+ i ) ;
        j = i-1;
        while (j >=0  && arr[j].score < key.score)
        {
            // arr[j+1] = arr[j];
            assignPlayer(arr + j + 1, arr + j);
            --j ;
        }
        // arr[j+1] = key  ;
        assignPlayer(arr + j + 1 , &key) ;
        
    }
    
} 

void assignPlayer(Player *player1 , Player *player2) {
    player1->gamesPlayed=player2->gamesPlayed ;
    player1->id=player2->id ;
    player1->score=player2->score ;
    strcpy(player1->name , player2->name) ;
}

void swapPlayers(Player *player1 , Player *player2) {
    Player temp ;
    // first store player1 in temp

    temp.id = player1->id ;
    temp.gamesPlayed = player1->gamesPlayed ;
    temp.score = player1->score ;
    strcpy(temp.name , player1->name);

    // second store player2 in player1

    player1->id = player2->id ;
    player1->gamesPlayed = player2->gamesPlayed ;
    player1->score = player2->score ;
    strcpy(player1->name , player2->name);
    

    // then finally store player2in player1

    player2->id = temp.id ;
    player2->gamesPlayed = temp.gamesPlayed ;
    player2->score = temp.score ;
    strcpy(player2->name , temp.name);
    

}



