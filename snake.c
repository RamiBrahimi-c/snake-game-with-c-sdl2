#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#include "player.h"
#include "Menu.h"

#define WINDOW_HEIGHT 480
#define WINDOW_WIDTH 640
#define GRID_SIZE 15
#define GRID_DIM 300



enum SNAKE  {
    SNAKE_UP,
    SNAKE_DOWN,
    SNAKE_RIGHT,
    SNAKE_LEFT,
};
typedef struct Snake
{
    int x;
    int y;
    int dir;
    int move;
    struct Snake* next ;
}snake;
typedef struct
{
    int x ;
    int y ;
}Apple;


typedef struct {
    SDL_Rect bounds;      // Position and size of the scrollable pane
    int scrollY;          // Current vertical scroll position
    int contentHeight;    // Total height of the content inside the pane
    SDL_Color bgColor;    // Background color of the pane
} ScrollablePane;




ScrollablePane* ScrollablePane_Create(int x, int y, int width, int height, int contentHeight, SDL_Color bgColor);
void ScrollablePane_Destroy(ScrollablePane* pane);
void ScrollablePane_HandleEvent(ScrollablePane* pane, SDL_Event* event);
void ScrollablePane_Render(ScrollablePane* pane, SDL_Renderer* renderer, void (*renderContent)(SDL_Renderer*, int , ScrollablePane* , FILE *) , FILE *);

int renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, 
               int x, int y, SDL_Color color  , int scale);




void init_snake(snake **head ) ;



void increase_snake(snake *head ) ;



void render_snake(SDL_Renderer *renderer , snake *head, int x , int y) ;




void move_sneak(snake *head) ;


void create_apple(Apple *apple) ;


void gene_apple(SDL_Renderer *renderer , int x , int y , Apple *apple) ;




void detect_Apple(SDL_Renderer *renderer,snake *head,  int x , int y, Apple *apple , int *score , char *result ) ;




void render_grid(SDL_Renderer *renderer , int x , int y) ;




void reset_snake(snake **head ) ;



void detect_crash(snake **head , int *score , char *result , Player *player) ;



void render_Score(SDL_Renderer *renderer , TTF_Font* font , char *result , Player *player)
{
        SDL_SetRenderDrawColor(renderer , 0,0,0,255) ;
    int x =WINDOW_WIDTH/2-GRID_DIM /2, y=WINDOW_WIDTH/2-GRID_DIM/4-200 ;
    int x2 =x + 250, y2=y ;

    char buffer[20] ;
    sprintf(buffer , "HS %d" , player->score);

    renderText(renderer , font , result , x , y ,(SDL_Color) {128,128,128,255} , 1 ) ;
    renderText(renderer , font , buffer , x2 , y2 ,(SDL_Color) {255,255,0,255} , 1 ) ;


}



void renderTitle(SDL_Renderer *renderer  , TTF_Font* font  ) {
        SDL_SetRenderDrawColor(renderer , 0,0,0,255) ;
    int x =WINDOW_WIDTH/2-GRID_DIM/4 - 80 , y=WINDOW_WIDTH/2-GRID_DIM/4-200 ;

        SDL_Texture* textTexture = NULL ;
        SDL_Surface* textSurface = NULL ;

    char *result = "Snake Game sdl" ;


    renderText(renderer , font , "Snake Game sdl" , x , y ,(SDL_Color) {255 , 0 , 0 , 255} , 2);
}
    














void renderPlayersStats(SDL_Renderer *renderer,FILE *ptr , TTF_Font *font1 , TTF_Font *font2  ) {
        SDL_SetRenderDrawColor(renderer , 245,57,54,255) ; // lkzdlkqs,dlk

    SDL_Rect titleRect ;
    titleRect.x = WINDOW_WIDTH/2-GRID_DIM/8-150 ; titleRect.y = WINDOW_WIDTH/2-GRID_DIM/2-150 ; 
    titleRect.w = 400 ; titleRect.h = 50 ;
    renderText(renderer ,font1 , "HIGHLIGHTS" ,(titleRect.x*2 + titleRect.w )/ 2 -80, (titleRect.y*2 + titleRect.h) /2 -20 , (SDL_Color){255,0,0,255} , 1 ) ;
    // SDL_RenderDrawRect(renderer , &titleRect) ;



    int length = getPlayersNumber(ptr) ;
    if (length<0)
    {
        printf("file doesn't exist fatal error\n");
        return;
    }
    rewind(ptr) ;


            SDL_Texture* textTexture = NULL ;
            SDL_Surface* textSurface = NULL ;
        SDL_Color textColor = {255,255,0,255} ;
        SDL_Color textColor2 = {255,255,255,255} ;





    SDL_Rect describtive_field ;


    describtive_field.x = WINDOW_WIDTH/2-GRID_DIM/6-50 ; describtive_field.y = WINDOW_WIDTH/2-GRID_DIM/2-50 ; 
       
    renderText(renderer , font2 ,"Name         Highest Score" , describtive_field.x , describtive_field.y , textColor , 1) ;



    SDL_Rect rect ;
    // rect.x = WINDOW_WIDTH/2-GRID_DIM/6-50 ; rect.y = WINDOW_WIDTH/2-GRID_DIM/2-100 ; 
    rect.x = WINDOW_WIDTH/2-GRID_DIM/6-50 ; rect.y = WINDOW_WIDTH/2-GRID_DIM/2-50 ; 
    rect.w = 200 ; rect.h = 40 ;



    Player buffer ;
    char playerInfo[50] ;

    int i = 0 ;
    while (i<length)
    {
        rect.y = rect.y + rect.h ;
        // SDL_RenderDrawRect(renderer , &rect) ;
        // ************************************************************************

        int result = fread(&buffer , sizeof(buffer) , 1 , ptr) ;
        if (!result) {
            printf("error when loading player number %d !! null pointer\n" , i+1);
            return;
        }
        sprintf(playerInfo , "%s                 %d" , buffer.name , buffer.score )  ;   

            renderText(renderer ,font2 , playerInfo , rect.x , rect.y , textColor2 , 1 ) ;


                ++i ;





        // ************************************************************************
    }
    


}


void renderHighScoreTitle(SDL_Renderer *renderer) {
        SDL_SetRenderDrawColor(renderer , 0 , 0 , 0 , 255) ;
    TTF_Font* font = TTF_OpenFont("fonts/Nunito-Regular.ttf", 18);
    if (!font) {
        fprintf(stderr, "Font Error: %s\n", TTF_GetError());
        return;
    }
    
    TTF_Font* font1 = TTF_OpenFont("fonts/Nunito-Regular.ttf", 30);
    if (!font) {
        fprintf(stderr, "Font Error: %s\n", TTF_GetError());
        return;
    }
    
    
    
    
    
    
    SDL_Rect titleRect ;
    titleRect.x = WINDOW_WIDTH/2-GRID_DIM/8-150 ; titleRect.y = WINDOW_WIDTH/2-GRID_DIM/2-150 ; 
    titleRect.w = 400 ; titleRect.h = 50 ;

    renderText(renderer ,font1 , "HIGHLIGHTS" ,titleRect.x+100, titleRect.y +10, (SDL_Color){255,0,0,255} , 1) ;
    
    
    SDL_Rect describtive_field ;


    describtive_field.x = WINDOW_WIDTH/2-GRID_DIM/6-50 ; describtive_field.y = WINDOW_WIDTH/2-GRID_DIM/2-50 ; 
       
    renderText(renderer , font ,"Name         Highest Score" , describtive_field.x , describtive_field.y+10 ,(SDL_Color) {255 , 255 , 0 , 255} , 1 ) ;
    
}


void RenderContent(SDL_Renderer* renderer, int scrollY , ScrollablePane* pane , FILE *ptr) {
    SDL_SetRenderDrawColor(renderer , 0 , 0 , 255 , 255) ;
    TTF_Font* font = TTF_OpenFont("fonts/Nunito-Regular.ttf", 18);
    if (!font) {
        fprintf(stderr, "Font Error: %s\n", TTF_GetError());
        return;
    }
    
    TTF_Font* font1 = TTF_OpenFont("fonts/Nunito-Regular.ttf", 26);
    if (!font) {
        fprintf(stderr, "Font Error: %s\n", TTF_GetError());
        return;
    }
    
    
    
    
    
    
    rewind(ptr) ;
    int length = getPlayersNumber(ptr) ;
    if (length<0)
    {
        printf("fatal error when trying to render players length = %d \n" , length);
        return;
    }
    




    rewind(ptr) ;
    Player *buffer = malloc(sizeof(Player) * length)  ;
    if (!buffer)
    {
        printf("cant allocate malloc error \n") ;
        return ;
    }
    
    fread(buffer , sizeof(Player) , length , ptr) ;
    sortPlayers(buffer , length) ;

    SDL_Color textColor = {255, 255, 255, 255};  // White text
    for (int i = 0; i < length; i++) {
        
        char text[50];
        snprintf(text, sizeof(text), "%s                 %d",buffer[i].name , buffer[i].score );

        SDL_Surface* surface = TTF_RenderText_Solid(font, text, textColor);
        if (!surface) {
            fprintf(stderr, "Text Error: %s\n", TTF_GetError());
            continue;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!texture) {
            fprintf(stderr, "Texture Error: %s\n", SDL_GetError());
            SDL_FreeSurface(surface);
            continue;
        }

        SDL_Rect dest = {
            pane->bounds.x ,                       // X-position (relative to pane)
            (i * 40) - scrollY,       // Y-position (scroll-adjusted)
            surface->w,
            surface->h
        };
        dest.y += 100 ;
        // Only render if text is visible in the pane
        if (dest.y + dest.h >= 0 && dest.y <= pane->bounds.h) {
            SDL_RenderCopy(renderer, texture, NULL, &dest);
        }

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    TTF_CloseFont(font);
}


ScrollablePane* ScrollablePane_Create(int x, int y, int width, int height, int contentHeight, SDL_Color bgColor) {
    ScrollablePane* pane = (ScrollablePane*)malloc(sizeof(ScrollablePane));
    pane->bounds = (SDL_Rect){x, y, width, height};
    pane->scrollY = 0;
    pane->contentHeight = contentHeight;
    pane->bgColor = bgColor;
    pane->bgColor.a = 255 ;
    pane->bgColor.r = 0 ;
    pane->bgColor.g = 0 ;
    pane->bgColor.b = 0 ;
    return pane;
}

void ScrollablePane_Destroy(ScrollablePane* pane) {
    free(pane);
}

void ScrollablePane_HandleEvent(ScrollablePane* pane, SDL_Event* event) {
    int x , y ;
    SDL_GetMouseState(&x , &y) ;

    if (event->type == SDL_MOUSEWHEEL && x >= pane->bounds.x && x <= pane->bounds.x +pane->bounds.w
                                        && y >= pane->bounds.y &&  y <= pane->bounds.y +pane->bounds.h) {
        // Adjust scroll position based on mouse wheel
        pane->scrollY -= event->wheel.y * 10; // Scroll speed multiplier

        // Clamp scroll position to prevent overscrolling
        int maxScroll = pane->contentHeight - pane->bounds.h;
        if (pane->scrollY < 0) pane->scrollY = 0;
        if (pane->scrollY > maxScroll && maxScroll > 0) pane->scrollY = maxScroll;
    }
}

void ScrollablePane_Render(ScrollablePane* pane, SDL_Renderer* renderer, void (*renderContent)(SDL_Renderer*, int , ScrollablePane* , FILE *) , FILE *ptr) {
    // Save the current viewport
    SDL_Rect originalViewport;
    SDL_RenderGetViewport(renderer, &originalViewport);

    // Set the viewport to the scrollable pane's bounds (clipping content outside)
    SDL_RenderSetViewport(renderer, &pane->bounds);

    // Draw the background
    SDL_SetRenderDrawColor(renderer, pane->bgColor.r, pane->bgColor.g, pane->bgColor.b, pane->bgColor.a);
    SDL_RenderFillRect(renderer, NULL);

    // Apply scroll offset by translating the rendering
    SDL_RenderSetClipRect(renderer, &pane->bounds);
    SDL_RenderSetScale(renderer, 1.0f, 1.0f);
    SDL_RenderSetViewport(renderer, &pane->bounds);

    // Render the content with scroll offset
     if (renderContent) {
        renderContent(renderer, pane->scrollY, pane , ptr);
    } 
        // renderContent(renderer, pane->scrollY , pane , ptr);

    // Restore the original viewport
    if (    SDL_RenderSetViewport(renderer, &originalViewport) < 0)
    {
        printf("error ksdfklsd\n") ;
    }
    SDL_RenderSetClipRect(renderer, NULL);  // Clear any clipping
    
}






void renderSettingsTitle(SDL_Renderer  *renderer ,TTF_Font *font  ) {
    SDL_SetRenderDrawColor( renderer,0 , 0 , 0 , 255 ) ;

    renderText( renderer ,font , "Settings" , WINDOW_WIDTH/4 + 40 , 20 ,(SDL_Color) {0 , 255 , 255 , 255} , 2 ) ;




}

void SettingsHandleEvent(SDL_Event *event ,MenuChoiceRectangle settings , int *main_state , int *settings_state) {

    if (event->type == SDL_KEYDOWN && *main_state==3 && *settings_state==0)
    {
        switch (event->key.keysym.sym)
        {
        case SDLK_RETURN:
            ChoiceRectangle *temp = settings.head ;
            if (settings.current_choice==temp)
            {
                *settings_state=1 ;
            }
            
            
            break;
        case SDLK_ESCAPE:
            *main_state=0 ;
            break;    
        
        default:
            break;
        }
    } else if (event->type == SDL_KEYDOWN && *main_state==3 && *settings_state==1) {
        switch (event->key.keysym.sym)
        {
        case SDLK_ESCAPE:
            *settings_state=0 ;
            break;
        case SDLK_RETURN:
                // *settings_state=0 ;


            break;
        default:
            break;
        }
    }
    

} 


Player* initNewPlayer() {
    Player *temp = malloc(sizeof(Player)) ;
    if (!temp)
    {
        printf("can't allocate malloc error\n");
        return NULL ;
    }
    return temp ;
    
}




    // ************************************************************************
    // ************************************************************************
    // ************************************************************************
    // ************************************************************************
    // ************************************************************************
    // ************************************************************************
    // ************************************************************************
    // ************************************************************************
    // ************************************************************************
    // ************************************************************************


int main(int argc, char* argv[]) {
    
    srand(time(0));
        snake *head =  NULL;
        Apple apple , apple2 ;
        create_apple(&apple);


        init_snake(&head );
        increase_snake(head );
        increase_snake(head );
        //increase_snake(head) ;

        setWindowHeight(WINDOW_HEIGHT) ; 
        setWindowWidth(WINDOW_WIDTH) ; 
        setGridDimension(GRID_DIM) ; 

        MenuChoiceRectangle menu = {0 , NULL , NULL} ;
        initMenuChoiceRectangle(&menu , 5 ) ; // 3 buttons ;

        MenuChoiceRectangle settings = {0 , NULL , NULL} ;

        initSettingsMenuChoiceRectangle(&settings , 1) ;


        //  FILE* ptr = initPlayersFile();
        //  int highscore = initPlayersFile();

        Player *currentPlayer = initNewPlayer() ;
        currentPlayer->gamesPlayed = 0 ;
        strcpy(currentPlayer->name , "");
        currentPlayer->id = 0 ;
        currentPlayer->score = 0 ; 


    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    if (TTF_Init() == -1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }
    // jkqfnsdkfndskfndskjds hello this is 
    

    SDL_Window* window = SDL_CreateWindow("snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,WINDOW_HEIGHT , SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED) ;
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Surface *icon = SDL_LoadBMP("snake.bmp") ;
    if (!icon)
    {
        printf("error when loading image bmp\n");
        return 1 ;
    }
        SDL_SetWindowIcon(window , icon) ;


        TTF_Font* font = TTF_OpenFont("fonts/ARCADECLASSIC.TTF", 24);
    if (font == NULL) {
        printf("Failed to load font! TTF_Error: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
        TTF_Font* font2 = TTF_OpenFont("fonts/Nunito-Regular.ttf", 24);
    if (font2 == NULL) {
        printf("Failed to load font! TTF_Error: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
        TTF_Font* font3 = TTF_OpenFont("fonts/Nunito-Regular.ttf", 18);
    if (font2 == NULL) {
        printf("Failed to load font! TTF_Error: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
        
        // ScrollablePane* pane = ScrollablePane_Create(120,  100 ,400, 400, (getPlayersNumber(ptr)) ,(SDL_Color) {0,0, 0, 255});



    SDL_Color textColor = {255, 255, 255, 255}; // White color
    SDL_Texture* textTexture = NULL;
    SDL_Surface* textSurface=NULL;
    int score = 0 ;
    char result[30] = "SCORE     0000000";

    bool running = true ;
    SDL_Event event ;


    int main_state = 0 ;
    int settings_state = 0 ;


    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false ;
                break;
            }
            else if(event.type == SDL_KEYDOWN && main_state==1)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                    main_state = (main_state==0) ? 1 : 0 ;
                    break;
                    case SDLK_UP:
                    if(head->dir==SNAKE_DOWN)
                    continue ;
                    head->dir = SNAKE_UP ;
                    
                    break;
                    case SDLK_DOWN:
                    if(head->dir==SNAKE_UP)
                    continue;
                    head->dir = SNAKE_DOWN ;
                    break;
                    case SDLK_RIGHT:
                    if(head->dir==SNAKE_LEFT)
                    continue ;
                    head->dir = SNAKE_RIGHT ;
                    break;
                    case SDLK_LEFT:
                    if (head->dir==SNAKE_RIGHT)
                    continue ;
                    head->dir = SNAKE_LEFT ;
                    break;
                    case SDLK_p :
                    head->move =  (head->move ==1) ? 1 : 0  ;
                    break;

                    case SDLK_r :
                    main_state = (main_state==1) ? 1 : 0 ;
                    break;
                }

            } else if (event.type == SDL_MOUSEBUTTONDOWN) {

                
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int mouseX = event.button.x;
                    int mouseY = event.button.y;

                    // Check if the mouse is inside the button rectangle
                     if (mouseX >= menu.head->rect.x && mouseX <= menu.head->rect.x + menu.head->rect.w &&
                    mouseY >= menu.head->rect.y && mouseY <= menu.head->rect.y + menu.head->rect.h &&
                     main_state==1 ) {
                    printf("Button clicked at (%d, %d)\n", mouseX, mouseY);
                    main_state = 0 ;
                    } 
                }
                
            } else if(event.type == SDL_KEYDOWN && main_state==0) {
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    running=false ;
                    break;                    
                case SDLK_DOWN:
                    menu.current_choice = menu.current_choice->next ;
                    break;
                case SDLK_UP:
                    menu.current_choice = menu.current_choice->prev ;
                    break;
                case SDLK_RETURN :
                        ChoiceRectangle *choice = menu.head ;
                        // choice one
                        if (menu.current_choice == choice)
                        {
                            score = 0 ;
                            reset_snake(&head) ;
                                    sprintf(result,"SCORE        000000%d", score);

                            main_state = 1 ;
                        }
                        choice = choice->next ;
                        
                        // choice two
                        if (menu.current_choice == choice)
                            main_state = 1 ;
                        
                            
                        choice = menu.head->prev ;
                        // choice three
                        if (menu.current_choice == choice)
                        {
                            running = false ;
                        }        
                    break;
                default:
                    
                    break;
                }

            } else if(event.type == SDL_KEYDOWN && main_state==2) {
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    // running=false ;
                    main_state = 0 ;
                    break;                    
                default:
                    
                    break;
                }


            }  

             
        }

        
                
                
          


        SDL_SetRenderDrawColor(renderer , 0,0,0,255) ;
        SDL_RenderClear(renderer);


        switch (main_state)
        {
        case 0:
            renderTitle(renderer , font ) ;
            renderMenu(renderer , font2  , menu) ;

            break;
        case 1:
            /* code */

            // start
            move_sneak(head);
            detect_Apple(renderer , head ,  WINDOW_WIDTH/2-GRID_DIM/2,WINDOW_HEIGHT/2-GRID_DIM/2,&apple , &score , result) ;
            detect_crash( &head, &score , result  , currentPlayer ) ;

            render_grid(renderer , WINDOW_WIDTH/2-GRID_DIM/2,WINDOW_HEIGHT/2-GRID_DIM/2) ;
            render_snake(renderer , head , WINDOW_WIDTH/2-GRID_DIM/2,WINDOW_HEIGHT/2-GRID_DIM/2) ;
            gene_apple(renderer  , WINDOW_WIDTH/2-GRID_DIM/2,WINDOW_HEIGHT/2-GRID_DIM/2 , &apple);
            render_Score(renderer, font  ,result , currentPlayer);

            // end

            break;

        default:

            break;
        }


        SDL_RenderPresent(renderer) ;

        SDL_Delay(200) ;

    }

    free(currentPlayer) ; 

    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer) ;
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

// ******************************************************************************************************
// ******************************************************************************************************
// ******************************************************************************************************
// ******************************************************************************************************
// ******************************************************************************************************
// ******************************************************************************************************
// ******************************************************************************************************
// ******************************************************************************************************
// ******************************************************************************************************
// ******************************************************************************************************
// ******************************************************************************************************
// ******************************************************************************************************
// ******************************************************************************************************








void init_snake(snake **head ) {
    *head = (snake*) malloc(sizeof(snake)) ;
    if ( *head==NULL)
    {
        printf("error when allocating memory\n");
        return;
    }
    (*head)->x = rand() % (GRID_SIZE/2) + (GRID_SIZE/4)  ;
    (*head)->y = rand() % (GRID_SIZE/2) + (GRID_SIZE/4);
    (*head)->dir = SNAKE_RIGHT ;
    (*head)->move = 1 ;
    (*head)->next = NULL ;




}

void increase_snake(snake *head ) {
    snake *temp = (snake*) malloc(sizeof(snake))  ;
    if (temp==NULL)
    {
        printf("error when allocating memory\n");
        return;
    }
    while (head != NULL && head->next != NULL)
        head = head->next ;


    temp->dir = (head)->dir ;
    switch ((head)->dir )
    {
        case SNAKE_UP:
        temp->x = (head)->x ;
        temp->y = (head)->y - 1  ;
        break;
        case SNAKE_DOWN:
        temp->x = (head)->x ;
        temp->y = (head)->y + 1  ;
        break;
        case SNAKE_RIGHT:
        temp->x = (head)->x -1 ;
        temp->y = (head)->y  ;
        break;
        case SNAKE_LEFT:
        temp->x = (head)->x +1;
        temp->y = (head)->y   ;
        break;
        default:
        temp->x = 0;
        temp->y = 0;
        break;

    }

    temp->next = NULL ;
    head->next = temp ;

}

void render_snake(SDL_Renderer *renderer , snake *head, int x , int y) {
      snake *temp = head ;

    SDL_SetRenderDrawColor(renderer , 0,132,12,255) ;
    int seg_size = GRID_DIM/GRID_SIZE ;
    SDL_Rect seg ;
    seg.w = seg_size ;
    seg.h = seg_size ;
    while (head != NULL)
    {
        seg.x = x +head->x *seg_size ;
        seg.y= y +head->y*seg_size;
        SDL_RenderFillRect(renderer, &seg) ;
        head = head->next ;
    }

      SDL_SetRenderDrawColor(renderer , 0,0,0,255) ;
    SDL_Rect eye1 , eye2 ;
    eye1.w = (GRID_DIM/GRID_SIZE) -15 ;
    eye1.h = (GRID_DIM/GRID_SIZE) -15;
    eye1.x =  x+ temp->x * (GRID_DIM/GRID_SIZE) + (GRID_DIM/GRID_SIZE)/4 +5;
    eye1.y = y + temp->y * (GRID_DIM/GRID_SIZE) + (GRID_DIM/GRID_SIZE)/4 ;
    eye2.w = eye1.w ;
    eye2.h = eye1.h ;
    eye2.x = eye1.x ;
    eye2.y = eye1.y + 7;
        SDL_RenderFillRect(renderer, &eye1);
        SDL_RenderFillRect(renderer, &eye2);


}


void move_sneak(snake *head) {
    if (!head->move)
    return;

    int prev_x , prev_y ,temp_x , temp_y , prev_dir , temp_dir;
            prev_x = head->x ;
        prev_y = head->y ;
        prev_dir = head->dir ;
    switch (head->dir)
    {
    case SNAKE_UP:
         --head->y ;
        break;
    case SNAKE_DOWN:
        ++head->y;
        break;
    case SNAKE_RIGHT:
         ++head->x  ;
        break;
    case SNAKE_LEFT:
         --head->x ;
        break;
    default:
        break;
    }
    if (head != NULL)
    {

        head = head->next ;
    }

    while (head != NULL)
    {
        temp_x = head->x ;
        temp_y = head->y ;
        temp_dir = head->dir ;

        head->x = prev_x ;
        head->y = prev_y ;
        head->dir = prev_dir ;
        prev_x = temp_x ;
        prev_y = temp_y ;
        prev_dir = temp_dir ;

        head = head->next ;
    }

}
void create_apple(Apple *apple) {
    apple->x=  rand() % GRID_SIZE  ;
    apple->y = rand() % GRID_SIZE ;
}

void gene_apple(SDL_Renderer *renderer , int x , int y , Apple *apple) {
    SDL_SetRenderDrawColor(renderer , 255,0,0,255) ;
    int apple_size = GRID_DIM/GRID_SIZE  ;
    SDL_Rect app ;
    app.w = apple_size ;
    app.h = apple_size ;
    app.x = x + apple->x * apple_size  ;
    app.y = y + apple->y * apple_size ;

     SDL_RenderFillRect(renderer , &app) ;

}

void detect_Apple(SDL_Renderer *renderer,snake *head,  int x , int y, Apple *apple , int *score , char *result ) {
    if(head->x == apple->x && head->y == apple->y)
    {
        increase_snake(head);
        create_apple(apple) ;
        gene_apple(renderer,x , y ,apple);
        (*score) += 4 ;
        if (*score < 10000 )
        sprintf(result , "SCORE        000%d", *score);
        if (*score < 1000 )
        sprintf(result , "SCORE        0000%d", *score);
        if (*score < 100  )
        sprintf(result , "SCORE        00000%d", *score);
        if (*score < 10 )
        sprintf(result , "SCORE        000000%d", *score);

    }
}

void render_grid(SDL_Renderer *renderer , int x , int y)
{
    SDL_SetRenderDrawColor(renderer , 255,255,255,255) ;
#if 0
    int cell_size = GRID_DIM/GRID_SIZE  ;
    SDL_Rect cell ;
    cell.w = cell_size ;
    cell.h = cell_size ;

    for (size_t i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            cell.x = x +i*cell_size ;
            cell.y= y +j*cell_size;
            SDL_RenderDrawRect(renderer,&cell) ;
        }

    }
#else
    SDL_Rect playground ;
    playground.x = x ;
    playground.y = y ;
    playground.h = GRID_DIM ;
    playground.w = GRID_DIM ;
    SDL_RenderDrawRect(renderer , &playground);
#endif
}

void reset_snake(snake **head ) {

    while (*head != NULL)
    {
        snake *temp = *head ;
        *head = (*head)->next ;
        free(temp) ;
    }
    //
    *head = NULL ;
    init_snake(head) ;
    increase_snake(*head ) ;
    increase_snake(*head ) ;
   // increase_snake(*head ) ;

}

void detect_crash(snake **head , int *score , char *result , Player *player) {
    if ((*head)->x < 0 || (*head)->y < 0 || (*head)->x >= GRID_SIZE || (*head)->y >= GRID_SIZE)
    {
        reset_snake(head);
            player->gamesPlayed++ ;
            player->score = (*score > player->score) ? *score : player->score ;
        *score=0 ;
        sprintf(result,"SCORE        000000%d", *score);
    }
    snake *temp = (*head) ;
    if (temp != NULL && temp->next != NULL)
    {
        temp = temp->next ;
    }


    while (temp != NULL)
    {
        if ( (*head)->x == temp->x  &&  (*head)->y == temp->y )
        {
            reset_snake(head);
            player->gamesPlayed++ ;
            player->score = (*score > player->score) ? *score : player->score ;
            *score=0 ;
            sprintf(result,"SCORE        000000%d", *score);
            return;
        }
        temp = temp->next ;

    }

}





int renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, 
               int x, int y, SDL_Color color  , int scale) {
    // Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, color);
    if (!textSurface) {
        SDL_Log("Unable to render text surface: %s", TTF_GetError());
        return -1;
    }
    
    // Create texture from surface
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        SDL_Log("Unable to create texture from rendered text: %s", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return -1;
    }
    
    // Get texture dimensions
    int textWidth = textSurface->w;
    int textHeight = textSurface->h;
    SDL_FreeSurface(textSurface);
    
    // Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, textWidth * scale, textHeight * scale };
    SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);
    
    // Clean up texture
    SDL_DestroyTexture(textTexture);
    
    return 0;
}

