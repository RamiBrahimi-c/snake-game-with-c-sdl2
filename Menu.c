#include "Menu.h"



int WindowWidth ;
int WindowHeight ;
int GridDim ;






int getWindowWidth() {
    return WindowWidth ; 
}

int getWindowHeight() {
    return WindowHeight ; 
}

void setWindowWidth(int w) {
     WindowWidth = w ; 
}

void setWindowHeight(int h ) {
    WindowHeight = h  ; 
}



int getGridDimension() {
    return GridDim ; 
}

void setGridDimension(int gridDim) {
     GridDim = gridDim ; 
}






void renderMenu(SDL_Renderer *renderer , TTF_Font* font , MenuChoiceRectangle menu ) {
    ChoiceRectangle *temp = menu.head;   
    int i = 0 ;

            SDL_Texture* textTexture = NULL ;
            SDL_Surface* textSurface = NULL ;
        SDL_Color textColor = {255,255,255,255} ;
        SDL_Color textColor2 = {0,0,0,255} ;

    while (i<menu.size)
    {

        
        
        
        int x =getWindowWidth()/2-getGridDimension()/6  , y=getWindowWidth()/2-getGridDimension()/2 ;

        
        if (temp == menu.current_choice)
        textSurface = TTF_RenderText_Solid(font, temp->text, textColor2);
        else 
        textSurface = TTF_RenderText_Solid(font, temp->text, textColor);


        if (textSurface == NULL) {
                    printf("Unable to createtextSurface! SDL_Error: %s\n", SDL_GetError());
                    return;
        }
        textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (textTexture == NULL) {
                    printf("Unable to create texture from rendered text! SDL_Error: %s\n", SDL_GetError());
                    return;
        }


                // Free the text surface
        SDL_FreeSurface(textSurface);


            // Only render the text if the texture was successfully created

                SDL_QueryTexture(textTexture, NULL, NULL, &(temp->rect.w), &(temp->rect.h));
                SDL_Rect textRect = {temp->rect.x ,temp->rect.y + i*temp->rect.h, temp->rect.w, temp->rect.h}; // Dynamic size based on text
                

            if (temp == menu.current_choice)
            SDL_SetRenderDrawColor(renderer , 255,255,255,255) ;  
            else         
            SDL_SetRenderDrawColor(renderer , 0,0,0,255) ;  
                
                SDL_RenderFillRect(renderer, &(textRect));


                SDL_RenderCopy(renderer, textTexture, NULL, &(textRect));    
                
                if (temp == menu.current_choice)
            SDL_SetRenderDrawColor(renderer , 255,255,255,255) ;  
            else         
            SDL_SetRenderDrawColor(renderer , 0,0,0,255) ;  
                
                // SDL_SetRenderDrawColor(renderer , 255,255,255,255) ;
                SDL_RenderDrawRect(renderer, &(textRect));
                
                temp = temp->next ;
                ++i ;

    }

}
    



void initSettingsMenuChoiceRectangle(MenuChoiceRectangle *settings , int size) {
    settings->size = size ;
    
    ChoiceRectangle *head = NULL ;
    ChoiceRectangle data ;
    data.rect.x = getWindowWidth()/2-getGridDimension()/6 ;  data.rect.y = getWindowWidth()/2-getGridDimension()/2 ;
    data.rect.w = 0 ;  data.rect.h = 0 ;
    strcpy(data.text , "snake color : ") ; 
    addFifoChoiceRectangle(&head , data) ;
    

    settings->head = head ;
    settings->current_choice = head ;

}


void initMenuChoiceRectangle(MenuChoiceRectangle *menu , int size) {
    menu->size = size ;
    
    ChoiceRectangle *head = NULL ;
    ChoiceRectangle data ;
    data.rect.x = getWindowWidth()/2-getGridDimension()/6 ;  data.rect.y = getWindowWidth()/2-getGridDimension()/2 ;
    data.rect.w = 0 ;  data.rect.h = 0 ;
    strcpy(data.text ,"Start" ) ;
    
    addFifoChoiceRectangle(&head , data) ;
    

    data.rect.x = data.rect.x ;  data.rect.y += data.rect.h + 10  ;
    strcpy(data.text ,"Continue" ) ;
    addFifoChoiceRectangle(&head , data) ;




    data.rect.x = data.rect.x ;  data.rect.y += data.rect.h + 10  ;
    strcpy(data.text ,"Exit" ) ;
    addFifoChoiceRectangle(&head , data) ;

    menu->head = head ;
    menu->current_choice = head ;
    menu->size = 3 ; 

}


void addFifoChoiceRectangle(ChoiceRectangle **head ,ChoiceRectangle data) {
    ChoiceRectangle *temp = malloc(sizeof(ChoiceRectangle)) ;
    if (temp==NULL)
    {
        printf("can't allocate memory\n");
        return ;
    }
    temp->rect.h = data.rect.h ;
    temp->rect.w = data.rect.w ;
    temp->rect.x = data.rect.x ;
    temp->rect.y = data.rect.y ;
    strcpy(temp->text , data.text) ;
    if (*head)
    {

        ChoiceRectangle *find = *head ;
        while (find && find->next != *head) find = find->next ;

        temp->prev = find ;
        find->next = temp ;
        (*head)->prev = temp ;
    }
    else
    {
        *head = temp ;
        temp->prev = *head ;
    }
        temp->next = *head ;
    
}


