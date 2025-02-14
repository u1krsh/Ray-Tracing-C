// Description: Ray tracing implementation.
//gcc ray-tracing.c -o raytracing -lmingw32 -lSDL2main -lSDL2
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h> 
#define SDL_MAIN_HANDLED
#define WIDTH 1366
#define HEIGHT 768
#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0x00000000
#define COLOR_YELLOW 0xffff00
#define RAYS_NUMBER 1000
#define COLOR_GRAY 0x808080

//circle struct
struct Circle{
    double x;
    double y;
    double r;
};

struct Ray{
    double x_start, y_start;
    double angle;
    double x_end, y_end;
};
void FillCircle(SDL_Surface* surface, struct Circle circle,Uint32 color)
{
    double radius_squrared = pow(circle.r,2);
    for (double x = circle.x-circle.r; x<=circle.x+circle.r;x++)
    {
        for(double y = circle.y-circle.r; y<=circle.y+circle.r;y++)
        {
            double distance_squrared = pow(x-circle.x, 2)+pow(y-circle.y, 2);
            if(distance_squrared <radius_squrared)
            {
                SDL_Rect pixel = (SDL_Rect){x,y,1,1};
                SDL_FillRect(surface, &pixel, color);
            }
        }
    }
}

void generate_rays(struct Circle circle, struct Ray rays[RAYS_NUMBER])
{

    for(int i = 0; i<RAYS_NUMBER;i++)
    {
        double angle = ((double) i/RAYS_NUMBER)*2*M_PI;
        struct Ray ray = {circle.x, circle.y, angle};
        rays[i] = ray;
        //printf("Angle: %f\n",angle);
    }

}


void FillRays(SDL_Surface* surface, struct Ray rays[RAYS_NUMBER], Uint32 color,struct Circle object)
{
    double radius_squared = pow(object.r,2);
    for(int i=0;i<RAYS_NUMBER;i++)
    {
        struct Ray ray = rays[i];
        int end_of_screen = 0;
        int object_hit = 0;

        double step = 1;
        double x_draw = ray.x_start;
        double y_draw = ray.y_start;
        while(!end_of_screen && !object_hit)
        {
            x_draw += step*cos(ray.angle); 
            y_draw += step*sin(ray.angle); 
            SDL_Rect pixel = (SDL_Rect){x_draw,y_draw,1,1};
            SDL_FillRect(surface, &pixel, color);
            if(x_draw < 0 || x_draw > WIDTH)
            {
                end_of_screen = 1;
            }
            if(y_draw < 0 || y_draw > HEIGHT)
            {
                end_of_screen = 1;
            }
            double distance_squrared = pow(x_draw-object.x, 2)+pow(y_draw-object.y, 2);
            if(distance_squrared < radius_squared)
            {
                break;
            }
        }
    }
    
}
int main(int argc, char *argv[]){   
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Raytracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WIDTH, HEIGHT,0);
    
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    //rectangle
    // SDL_Rect rect = (SDL_Rect) {200,200,200,200};
    // SDL_FillRect(surface, &rect, COLOR_WHITE);
    struct Circle circle =  {200,200,80};
    struct Circle shadow_circle =  {650,300,140};
    SDL_Rect erase_rect = (SDL_Rect){0,0,WIDTH,HEIGHT};

    struct Ray rays[RAYS_NUMBER];
    generate_rays(circle, rays);
    int simulation_running = 1;
    SDL_Event event;
    while (simulation_running)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                simulation_running = 0;
            }
            if(event.type == SDL_MOUSEMOTION && event.motion.state != 0)
            {
                circle.x = event.motion.x;
                circle.y = event.motion.y;
                generate_rays(circle, rays);
            }
        }
        SDL_FillRect(surface, &erase_rect, COLOR_BLACK);
        FillCircle(surface,circle,COLOR_YELLOW); 
        FillCircle(surface,shadow_circle,COLOR_WHITE);
        FillRays(surface,rays,COLOR_GRAY,shadow_circle);
        SDL_UpdateWindowSurface(window);
        SDL_Delay(10);

    }
}