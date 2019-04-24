#include <SDL.h>
#include <iostream>

class Game
{
private:
    SDL_Renderer *renderer = nullptr;
    SDL_Window *display = nullptr;

private:
    bool running, prW = false, prS = false, prD = false, prA = false;
    int x, y;
    int spd_y, spd_x;
    int scr_w, scr_h;

public:
    Game();
    int OnExecute();

public:
    bool OnInit();
    void OnEvent( SDL_Event *event );
    void OnLoop();
    void OnRender();
    void OnCleanup();
};

Game::Game()
{
    running = false;
}

int Game::OnExecute()
{
    if( !OnInit() )
    {
        return -1;
    }

    running = true;
    SDL_Event event;

    Uint32 beg = SDL_GetTicks();
    size_t frames = 0;
    while( running )
    {
        while( SDL_PollEvent( &event ) )
        {
            OnEvent( &event );
        }

        OnLoop();
        OnRender();

        frames++;
        Uint32 end = SDL_GetTicks();
        if( end - beg > 1000 )
        {
            std::cout << "Frame time: " << ( end - beg ) / frames << " ms" << std::endl;
            beg = end;
            frames = 0;
        }
    }

    OnCleanup();
    return 0;
}

bool Game::OnInit()
{
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        return false;
    }

    if( ( display = SDL_CreateWindow( "Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0 ) ) == nullptr )
    {
        return false;
    }

    scr_w = 1280;
    scr_h = 720;

    Uint32 rflags = SDL_RENDERER_ACCELERATED;
    rflags |= SDL_RENDERER_PRESENTVSYNC;
    if( ( renderer = SDL_CreateRenderer( display, -1, rflags ) ) == nullptr )
    {
        return false;
    }

    x = 0;
    y = 0;

    spd_x = 0;
    spd_y = 0;

    return true;
}

void Game::OnEvent( SDL_Event *event )
{
    if( event->type == SDL_QUIT )
    {
        running = false;
        return;
    }

    switch( event->type )
    {
    case SDL_KEYDOWN:
        switch( event->key.keysym.sym )
        {
        case SDLK_w:
            if( prS )
            {
                spd_y = 0;
            }
            else
            {
                spd_y = -5;
            }
            prW = true;
            break;
        case SDLK_s:
            if( prW )
            {
                spd_y = 0;
            }
            else
            {
                spd_y = 5;
            }
            prS = true;
            break;
        case SDLK_d:
            if( prA )
            {
                spd_x = 0;
            }
            else
            {
                spd_x = 5;
            }
            prD = true;
            break;
        case SDLK_a:
            if( prD )
            {
                spd_x = 0;
            }
            else
            {
                spd_x = -5;
            }
            prA = true;
            break;
        default:
            return;
        }

        break;
    case SDL_KEYUP:
        switch( event->key.keysym.sym )
        {
        case SDLK_w:
            if( !prS )
            {
                spd_y = 0;
            }
            else
            {
                spd_y = 5;
            }
            prW = false;
            break;
        case SDLK_s:
            if( !prW )
            {
                spd_y = 0;
            }
            else
            {
                spd_y = -5;
            }
            prS = false;
            break;
        case SDLK_a:
            if( !prD )
            {
                spd_x = 0;
            }
            else
            {
                spd_x = 5;
            }
            prA = false;
            break;
        case SDLK_d:
            if( !prA )
            {
                spd_x = 0;
            }
            else
            {
                spd_x = -5;
            }
            prD = false;
            break;
        default:
            return;
        }
    default:
        return;
    }
}

void Game::OnLoop()
{
    x += spd_x;
    y += spd_y;

    if( x < 0 )
    {
        x = 0;
    }
    else if( x > scr_w - 100 )
    {
        x = scr_w - 100;
    }

    if( y < 0 )
    {
        y = 0;
    }
    else if( y > scr_h - 100 )
    {
        y = scr_h - 100;
    }
}

void Game::OnRender()
{
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0x00 );

    SDL_RenderClear( renderer );

    SDL_Rect charc;
    charc.x = x;
    charc.y = y;
    charc.w = 100;
    charc.h = 100;

    SDL_SetRenderDrawColor( renderer, 0, 0, 0xff, 0 );

    SDL_RenderFillRect( renderer, &charc );

    SDL_Delay( 1 );
    SDL_RenderPresent( renderer );
}

void Game::OnCleanup()
{
    SDL_DestroyWindow( display );
    SDL_Quit();
}

int main( int argc, char** argv )
{
    Game game;
    return game.OnExecute();
}