#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
 
#define NUMCARS 10
 
enum CONDITION {esquerda, direita};
bool condition[] = {false,false};
 
const float FPS = 100;  
const int SCREEN_W = 960;
const int SCREEN_H = 540;
 
 
int SKY_H;
 
float CAR_W = 100;
float CAR_H = 20;
float WHEEL_W = 30;
float WHEEL_H = 40;
 
float TRACK_TOP_W;
float TRACK_BOTTOM_W;
 
float CAR_X;
float CAR_Y;
float WHEEL_ESQ_X;
float WHEEL_ESQ_Y;
float WHEEL_DIR_X;
float WHEEL_DIR_Y;
 
float TRACK_TOP_LEFT_X;
float TRACK_TOP_LEFT_Y;
float TRACK_BOTTOM_LEFT_X;
float TRACK_BOTTOM_LEFT_Y;
 
float TRACK_TOP_RIGHT_X;
float TRACK_TOP_RIGHT_Y;
float TRACK_BOTTOM_RIGHT_X;
float TRACK_BOTTOM_RIGHT_Y;
 
float THETA;
 
 
 
/*
const float FPS = 100;  
const int SCREEN_W = 640*1.5;
const int SCREEN_H = 540;
 
int SKY_H = SCREEN_H/4;
 
const float CAR_W = 100;
const float CAR_H = 50;
 
const int TRACK_TOP_W = SCREEN_W/10;
const int TRACK_BOTTOM_W = SCREEN_W/5;
 
const int TRACK_TOP_LEFT_X = SCREEN_W/2 - TRACK_TOP_W/2;
const int TRACK_TOP_LEFT_Y = SKY_H;
const int TRACK_BOTTOM_LEFT_X = SCREEN_W/2 - TRACK_BOTTOM_W/2;
const int TRACK_BOTTOM_LEFT_Y = SCREEN_H;
*/
 
int score = 0;
 
typedef struct Car {
    float x1Car,y1Car;
    float x2Car,y2Car;
    float x1RodaEsq,y1RodaEsq;
    float x2RodaEsq,y2RodaEsq;
    float x1RodaDir,y1RodaDir;
    float x2RodaDir,y2RodaDir;
    float accel;
    float var;
    bool status;
    int cor1,cor2,cor3,cor4,cor5,cor6;
    ALLEGRO_COLOR cor;
} Car;
 
 
void init_global_vars() {
   
    SKY_H = SCREEN_H/4;
 
    TRACK_TOP_W = SCREEN_W/100;
    TRACK_BOTTOM_W = SCREEN_W/1.2;
   
    CAR_X = SCREEN_W/2.25;
    CAR_Y = SCREEN_H - (SCREEN_H/17);
    WHEEL_ESQ_X = CAR_X - WHEEL_W;
    WHEEL_ESQ_Y = CAR_Y - WHEEL_H/4;
    WHEEL_DIR_X = CAR_X + CAR_W;
    WHEEL_DIR_Y = CAR_Y - WHEEL_H/4;
   
    TRACK_TOP_LEFT_X = SCREEN_W/2 - TRACK_TOP_W/2;
    TRACK_TOP_LEFT_Y = SKY_H;
    TRACK_BOTTOM_LEFT_X = SCREEN_W/2 - TRACK_BOTTOM_W/2;
    TRACK_BOTTOM_LEFT_Y = SCREEN_H;
   
    TRACK_TOP_RIGHT_X = SCREEN_W/2 + TRACK_TOP_W/2;
    TRACK_TOP_RIGHT_Y = SKY_H;
    TRACK_BOTTOM_RIGHT_X = SCREEN_W/2 + TRACK_BOTTOM_W/2;
    TRACK_BOTTOM_RIGHT_Y = SCREEN_H;
 
    //track angle
    THETA = atan((TRACK_BOTTOM_LEFT_Y - TRACK_TOP_LEFT_Y)/(TRACK_TOP_LEFT_X - TRACK_BOTTOM_LEFT_X));
}
 
 
void draw_scenario(ALLEGRO_DISPLAY *display) {
   
    //grass
    ALLEGRO_COLOR BKG_COLOR = al_map_rgb(55,171,38);
    al_set_target_bitmap(al_get_backbuffer(display));
    al_clear_to_color(BKG_COLOR);  
   
    //sky
    al_draw_filled_rectangle(0, 0, SCREEN_W, SKY_H, al_map_rgb(0,255,247));
   
   //desenha a pista:
   al_draw_line(TRACK_TOP_LEFT_X, TRACK_TOP_LEFT_Y, TRACK_BOTTOM_LEFT_X, TRACK_BOTTOM_LEFT_Y, al_map_rgb(255,255,255), 10);
   al_draw_line(TRACK_TOP_RIGHT_X, TRACK_TOP_RIGHT_Y, TRACK_BOTTOM_RIGHT_X, TRACK_BOTTOM_RIGHT_Y, al_map_rgb(255,255,255), 10);  
   al_draw_filled_triangle(TRACK_BOTTOM_LEFT_X, TRACK_BOTTOM_LEFT_Y, TRACK_BOTTOM_RIGHT_X, TRACK_BOTTOM_RIGHT_Y,  (TRACK_TOP_LEFT_X+TRACK_TOP_RIGHT_X)/2, TRACK_TOP_RIGHT_Y, al_map_rgb(89,89,89));
   
}
 
//Minhas funçoes
 
void geraCarrinhos(Car carro[]){
    int i;
    for(i=0;i < NUMCARS;i++){
        carro[i].cor1 = rand()%234;
        carro[i].cor2 = rand()%234;
        carro[i].cor3 = rand()%234;
        carro[i].cor4 = 30+rand()%199;
        carro[i].cor5 = 30+rand()%199;
        carro[i].cor6 = 30+rand()%199;
        carro[i].status = false;
    }
}
 
void liberaCarrinhos(Car carro[]){
    for(int i=0;i < NUMCARS;i++){
        if(!carro[i].status){
            if (rand()%1135==0){
                    carro[i].y1Car = TRACK_TOP_RIGHT_Y;
                    carro[i].x1Car = ((TRACK_TOP_LEFT_X+TRACK_TOP_RIGHT_X)/2) - rand()%5 + rand()%5;
 
                    carro[i].y2Car = carro[i].y1Car+0.625;
                    carro[i].x2Car = carro[i].x1Car+1;
           
                    carro[i].y1RodaEsq = TRACK_TOP_RIGHT_Y-0.25;
                    carro[i].x1RodaEsq = carro[i].x1Car - 0.375;
 
                    carro[i].y2RodaEsq = TRACK_TOP_RIGHT_Y + 0.875;
                    carro[i].x2RodaEsq = carro[i].x1Car;
 
                    carro[i].y1RodaDir = TRACK_TOP_RIGHT_Y-0.25;
                    carro[i].x1RodaDir = carro[i].x2Car;
 
                    carro[i].y2RodaDir = TRACK_TOP_RIGHT_Y + 0.875;
                    carro[i].x2RodaDir = carro[i].x2Car + 0.375;

                    carro[i].accel = 0;
                    carro[i].var = (float)(rand()%10)/100 - (float)(rand()%10)/100;
                    carro[i].status = true;
                break;
            }
        }
    }
}
 
void atualizarCarrinhos(Car carro[], int *contador){
    for(int i=0;i < NUMCARS;i++){
        if(carro[i].status){
            carro[i].accel += 0.007;
            carro[i].var += carro[i].var/100;

            carro[i].y1Car += carro[i].accel-0.027;
            carro[i].x1Car += carro[i].var-0.13;
 
            carro[i].y2Car += carro[i].accel+0.027;
            carro[i].x2Car += carro[i].var+0.13;
           
            carro[i].y1RodaEsq += carro[i].accel-0.048;
            carro[i].x1RodaEsq += carro[i].var-0.2;
 
            carro[i].y2RodaEsq += carro[i].accel+0.048;
            carro[i].x2RodaEsq += carro[i].var-0.13;
 
            carro[i].y1RodaDir += carro[i].accel-0.048;
            carro[i].x1RodaDir += carro[i].var+0.13;
 
            carro[i].y2RodaDir += carro[i].accel+0.048;
            carro[i].x2RodaDir += carro[i].var+0.2;
 
 
            if(carro[i].y1RodaDir > 540){
                carro[i].status = false;
                *contador += 1;
            }
        }
    }
}
 
void desenhaCarrinhos(Car carro[]){
    for(int i=0;i < NUMCARS;i++){
        if(carro[i].status){
            al_draw_filled_rectangle(carro[i].x1Car,carro[i].y1Car,carro[i].x2Car,carro[i].y2Car, al_map_rgb(carro[i].cor1,carro[i].cor2,carro[i].cor3));
            al_draw_filled_rectangle(carro[i].x1RodaEsq,carro[i].y1RodaEsq,carro[i].x2RodaEsq,carro[i].y2RodaEsq, al_map_rgb(carro[i].cor4,carro[i].cor5,carro[i].cor6));
            al_draw_filled_rectangle(carro[i].x1RodaDir,carro[i].y1RodaDir,carro[i].x2RodaDir,carro[i].y2RodaDir, al_map_rgb(carro[i].cor4,carro[i].cor5,carro[i].cor6));
        }
    }
}

void colisaoCarrinhos(Car carro[], int *rodando, float *rodaDirX, float *rodaEsqX, float *carroX){
    float rodadirX = *rodaDirX+28;
    float rodaesqX = *rodaEsqX+5;
    for(int i=0;i< NUMCARS;i++){
        if (carro[i].status){
            if (!(((carro[i].x2RodaEsq>rodadirX)&&(carro[i].x1RodaEsq>rodadirX)&&(carro[i].x2RodaDir>rodadirX)&&(carro[i].x1RodaDir>rodadirX))||((carro[i].x2RodaEsq<rodaesqX)&&(carro[i].x1RodaEsq<rodaesqX)&&(carro[i].x2RodaDir<rodaesqX)&&(carro[i].x1RodaDir<rodaesqX)))){
                if (carro[i].y2RodaEsq<(WHEEL_DIR_Y+CAR_Y)/2){
                    ;
                }
                else    *rodando=0;
            }
        }
    }
}



int main(int argc, char **argv){
   
    //srand(2);
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *carro = NULL;
    ALLEGRO_BITMAP *roda_esq = NULL;
    ALLEGRO_BITMAP *roda_dir = NULL;
    init_global_vars();

    bool pausar = false;
    Car carros[NUMCARS];
    int contPontos=0;
    int recorde=0;
    FILE *arq;
        arq = fopen("recorde1.txt","r");
        fscanf(arq,"%d",&recorde);
        fclose(arq);


    //gerar os carrinhos inimigos
    geraCarrinhos(carros);
 
    //----------------------- rotinas de inicializacao ---------------------------------------
   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }
   
    if(!al_init_primitives_addon()){
        fprintf(stderr, "failed to initialize primitives!\n");
        return -1;
    }
 
   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return -1;
   }
 
   display = al_create_display(SCREEN_W, SCREEN_H);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      al_destroy_timer(timer);
      return -1;
   }
 
    //CRIAR O CARRINHO
    carro = al_create_bitmap(CAR_W, CAR_H);
   if(!carro) {
      fprintf(stderr, "failed to create carro bitmap!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
    al_set_target_bitmap(carro);
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_set_target_bitmap(al_get_backbuffer(display));
 
    //CRIAR A RODA ESQUERDA
    roda_esq = al_create_bitmap(WHEEL_W, WHEEL_H);
   if(!roda_esq) {
      fprintf(stderr, "failed to create roda esquerda bitmap!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
    al_set_target_bitmap(roda_esq);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_set_target_bitmap(al_get_backbuffer(display));
 
    //CRIAR A RODA DIREIRA
    roda_dir = al_create_bitmap(WHEEL_W, WHEEL_H);
   if(!roda_dir) {
      fprintf(stderr, "failed to create roda direita bitmap!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
    al_set_target_bitmap(roda_dir);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_set_target_bitmap(al_get_backbuffer(display));
 
    //inicializa o modulo allegro que carrega as fontes
    al_init_font_addon();
    //inicializa o modulo allegro que entende arquivos tff de fontes
    al_init_ttf_addon();
 
 
    //carrega o arquivo arial.ttf da fonte Arial e define que sera usado o tamanho 32 (segundo parametro)
    ALLEGRO_FONT *size_32 = al_load_font("arial.ttf", 32, 1);
 
 
 
   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_bitmap(carro);
      al_destroy_bitmap(roda_esq);
      al_destroy_bitmap(roda_dir);
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
    }
   
   al_install_keyboard();
   
   
    //registra na fila de eventos que eu quero identificar quando a tela foi alterada
   al_register_event_source(event_queue, al_get_display_event_source(display));
    //registra na fila de eventos que eu quero identificar quando o tempo alterou de t para t+1
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
   
   al_register_event_source(event_queue, al_get_keyboard_event_source());  
 
 
    //reinicializa a tela
   al_flip_display();
    //inicia o temporizador
   al_start_timer(timer);
 
 
 
   
   int playing = 1;
    //enquanto playing for verdadeiro, faca:
    while(playing) {
      ALLEGRO_EVENT ev;
      //espera por um evento e o armazena na variavel de evento ev
      al_wait_for_event(event_queue, &ev);
     
    if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
        //verifica qual tecla foi
        switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_A:
                if(CAR_X>TRACK_BOTTOM_LEFT_X){
                condition[esquerda]=true;
                }
            break;
 
            case ALLEGRO_KEY_D:
                if(CAR_X<TRACK_BOTTOM_RIGHT_X){
                condition[direita]=true;
                }
            break;

            case ALLEGRO_KEY_P:
                pausar = true;
            break;
 
            case ALLEGRO_KEY_ESCAPE:
                playing = 0;
            break;
            }
 
        }    
    else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
        //verifica qual tecla foi
        switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_A:
                condition[esquerda]=false;
            break;
 
            case ALLEGRO_KEY_D:
                condition[direita]=false;
            break;

            case ALLEGRO_KEY_P:
                pausar = false;
            break;
            }
 
        }
        
    if(pausar){
              
    }
       
   
    //se o tipo de evento for um evento do temporizador, ou seja, se o tempo passou de t para t+1
    else if(ev.type == ALLEGRO_EVENT_TIMER) {
        
        draw_scenario(display);
        al_draw_bitmap(carro, CAR_X, CAR_Y, 0);
        al_draw_bitmap(roda_esq, WHEEL_ESQ_X, WHEEL_ESQ_Y, 0);
        al_draw_bitmap(roda_dir, WHEEL_DIR_X, WHEEL_DIR_Y, 0);     
   
        //libera os carrinhos inimigos
        liberaCarrinhos(carros);
        //desenha os carrinhos inimigos
        desenhaCarrinhos(carros);
        //atualiza os carrinhos inimigos
        atualizarCarrinhos(carros, &contPontos);
        colisaoCarrinhos(carros, &playing, &WHEEL_DIR_X, &WHEEL_ESQ_X, &CAR_X);

        al_draw_textf(size_32, al_map_rgb(0,0,0), 85, 10, ALLEGRO_ALIGN_CENTRE, "Pontos: %d", contPontos);

        //reinicializo a tela
        al_flip_display();
        
 
    }
    //se o tipo de evento for o fechamento da tela (clique no x da janela)
    else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        playing = 0;
    }
    if (CAR_X < 746){
        CAR_X += condition[direita]*4;
        WHEEL_ESQ_X += condition[direita]*4;
        WHEEL_DIR_X += condition[direita]*4;
    }
    if (CAR_X > 113){
        CAR_X -= condition[esquerda]*4;
        WHEEL_ESQ_X -= condition[esquerda]*4;
        WHEEL_DIR_X -= condition[esquerda]*4;
    }
 
   if(contPontos > recorde){
        arq = fopen("recorde1.txt","w");
        fprintf(arq,"%d", contPontos);
        fclose(arq);
        recorde=contPontos;
    }

    } //fim do while

    if (!playing){
        al_draw_filled_rectangle(0, 0, SCREEN_W, SCREEN_H, al_map_rgb(255,255,255));
        al_draw_textf(size_32, al_map_rgb(0,0,0), SCREEN_W/2, SCREEN_H/2, ALLEGRO_ALIGN_CENTRE, "Pontos nessa partida: %d / Recorde: %d", contPontos, recorde);
    }

   
    //reinicializa a tela
    al_flip_display(); 
    al_rest(3);
   
    al_destroy_bitmap(carro);
    al_destroy_bitmap(roda_esq);
    al_destroy_bitmap(roda_dir);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
   
 
   return 0;
}