#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

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
    struct Snake* next ;
}snake;
typedef struct
{
    int x ;
    int y ;
}Apple;







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
    SDL_SetRenderDrawColor(renderer , 0,255,0,255) ;
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




}


void move_sneak(snake *head) {
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
        sprintf(result , "SCORE        %d", *score);
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
void detect_crash(snake **head , snake **tail , int *score , char *result) {
    if ((*head)->x < 0 || (*head)->y < 0 || (*head)->x >= GRID_SIZE || (*head)->y >= GRID_SIZE)
    {
        reset_snake(head);
        *score=0 ;
        sprintf(result,"SCORE        %d", *score);
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
            *score=0 ;
            sprintf(result,"SCORE        %d", *score);
            return;
        }
        temp = temp->next ;

    }

}

void render_Score(SDL_Renderer *renderer ,    SDL_Texture* textTexture ,SDL_Surface* textSurface , TTF_Font* font , int score , char *result)
{
        SDL_SetRenderDrawColor(renderer , 0,0,0,255) ;
    int x =WINDOW_WIDTH/2-GRID_DIM/4 , y=WINDOW_WIDTH/2-GRID_DIM/4-200 ;
    SDL_Color textColor = {255,255,255,255} ;
    textSurface = TTF_RenderText_Solid(font, result, textColor);
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

            int textWidth = 0, textHeight = 0;
            SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);
            SDL_Rect textRect = {x,y, textWidth, textHeight}; // Dynamic size based on text


                SDL_RenderFillRect(renderer, &textRect);
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
}



int main(int argc, char* argv[]) {
    srand(time(0));
        snake *head = NULL , *tail = NULL;
        Apple apple , apple2 ;
        create_apple(&apple);


        init_snake(&head );
        increase_snake(head );
        increase_snake(head );
        //increase_snake(head) ;


    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    if (TTF_Init() == -1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

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
        TTF_Font* font = TTF_OpenFont("fonts/ARCADECLASSIC.TTF", 24);
    if (font == NULL) {
        printf("Failed to load font! TTF_Error: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Color textColor = {255, 255, 255, 255}; // White color
    SDL_Texture* textTexture = NULL;
    SDL_Surface* textSurface=NULL;
    int score = 0 ;
    char result[20] = "SCORE        0000";

    bool running = true ;
    SDL_Event event ;


    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false ;
                break;
            }
            else if(event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                    running=false ;
                    break;
                    case SDLK_UP:
                    head->dir = SNAKE_UP ;
                    break;
                    case SDLK_DOWN:
                    head->dir = SNAKE_DOWN ;
                    break;
                    case SDLK_RIGHT:
                    head->dir = SNAKE_RIGHT ;
                    break;
                    case SDLK_LEFT:
                    head->dir = SNAKE_LEFT ;
                    break;

                }

            }
        }

        SDL_SetRenderDrawColor(renderer , 0,0,0,255) ;
        SDL_RenderClear(renderer);

        // start
        move_sneak(head);
        detect_Apple(renderer , head ,  WINDOW_WIDTH/2-GRID_DIM/2,WINDOW_HEIGHT/2-GRID_DIM/2,&apple , &score , result) ;
        detect_crash(&head , &tail ,&score , result ) ;

        render_grid(renderer , WINDOW_WIDTH/2-GRID_DIM/2,WINDOW_HEIGHT/2-GRID_DIM/2) ;
        render_snake(renderer , head , WINDOW_WIDTH/2-GRID_DIM/2,WINDOW_HEIGHT/2-GRID_DIM/2) ;
        gene_apple(renderer  , WINDOW_WIDTH/2-GRID_DIM/2,WINDOW_HEIGHT/2-GRID_DIM/2 , &apple);
        render_Score(renderer,textTexture, textSurface, font , score , result);

        // end

        SDL_RenderPresent(renderer) ;

        SDL_Delay(200) ;

    }

    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer) ;
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}