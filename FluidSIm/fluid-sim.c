#include <stdio.h>
#include <SDL2/SDL.h>
#define SDL_MAIN_HANDLED
#define WIDTH 900
#define HEIGHT 600
#define COLOR_WHITE 0xffffffff
#define COLOR_BLUE  0x7aabfa
#define CELL_SIZE 20
#define COLUMNS WIDTH/CELL_SIZE
#define ROWS HEIGHT/CELL_SIZE
#define LINE_WIDTH 2
#define COLOR_GRAY 0x0f0f0f0f

struct Cell
{
    int type;
    int fill_level;
    int x;
    int y;

};

void color_cell(SDL_Surface* surface,struct Cell cell)
{
    int pixel_x = cell.x*CELL_SIZE;
    int pixel_y = cell.y*CELL_SIZE;
    SDL_Rect cell_rect = (SDL_Rect){pixel_x,pixel_y,CELL_SIZE,CELL_SIZE};
    SDL_FillRect(surface, &cell_rect, COLOR_WHITE);
}

void drawGrid(SDL_Surface* surface )
{
    for(int i=0;i<COLUMNS;i++)
    {
        SDL_Rect column = (SDL_Rect){i*CELL_SIZE, 0, LINE_WIDTH, HEIGHT}; 
        SDL_FillRect(surface, &column, COLOR_GRAY);
    }

    for(int j=0;j<ROWS;j++)
    {
        SDL_Rect rows = (SDL_Rect){0,j*CELL_SIZE, WIDTH, LINE_WIDTH}; 
        SDL_FillRect(surface, &rows, COLOR_GRAY);
    }
}
int main(int argc, char *argv[])
{   
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Liquid Sim", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WIDTH, HEIGHT,0);
    
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    drawGrid(surface);

    int simulation_running = 1;
    SDL_Event event;
    while(simulation_running)
    {
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                simulation_running = 0;
            }
            if(event.type == SDL_MOUSEMOTION && event.motion.state != 0)
            {
                int cell_x = event.motion.x /CELL_SIZE;
                int cell_y = event.motion.y /CELL_SIZE;
                struct Cell cell = (struct Cell){1,0,cell_x,cell_y};
                color_cell(surface,cell);

            }
        }
        
        SDL_Rect rectangle = (SDL_Rect){50,50,100,50};
        SDL_FillRect(surface, &rectangle, COLOR_WHITE);
        
        SDL_Rect blue_rectangle = (SDL_Rect){150,50,100,50};
        SDL_FillRect(surface, &blue_rectangle, COLOR_BLUE);

        SDL_UpdateWindowSurface(window);
        SDL_Delay(100);


    }

}