#include <allegro.h>
#include <stdio.h>

#define RADIOON 7
#define RADIOOFF 15
#define MUDAR_FORCA_MOTOR 9712
#define BRTIPO1L 105
#define BRTIPO1R 110
#define Parado 0
#define ParaFrente 1
#define ParaTras 2
#define SUBIR 310
#define DECER 320
#define PRESSAO_ALTA 123
#define EXPLODIR 777
#define MENU 555
#define MOSTRAR_PONTUACAO 58525456
#define INICIAR 7777
#define IR_PARA_MENU 5599
#define INSTRUCOES 897
#define SOBRE 997
#define MINICIAR 12345
#define MINSTRUCOES 14
#define MSOBRE 17
#define JOGO 1005
#define PREMIO_RESGATADO 444
#define PROXIMA_PAGINA 73
#define SIM 1
#define NAO 0
#define LigDesl_som 333
#define MUDAR_TAM_TELA 551
#define MOS_FUND_FISICA 39178310
//------------------------------variaveis--------------------------//
class Sub
{
      public:
             int x;
             int y;
             int angulo;
};
int empuxo,
    peso,
    nivel_tanque_right,
    nivel_tanque_left,
    porcentagem_nivel_tanque_right,
    porcentagem_nivel_tanque_left,
    profundidade,
    pressao,
    forca_motor,
    velocidade,
    sentido=0,
    empulso_x,empulso_y,
    equilibrio;
Sub Submarino;
int sobe;
int pixel_achado;
int dece;    
int por_forca_motor;
int exe=100;
int selR,selL;
int btfposyl=458;
int btfposyr=458;
int sel;
int posx_cenario;
int posy_cenario;
int sx,sy;
int ce;
int power=0;    
int pacx,pacy;
int sai=0;
int event_id;
int vel_queda=1;
int frame;
int usuario_ciente_perigo;
int mp;
int frame_mouse;
int frame_alert;
int cor=255;
int eparaalertar=SIM;
int nuvempos;
int etapa=MENU;
int dentro_dagua=1;
int frame_menu;
int ty;
int etapa_iniciar;
int posicao_y_premio;
int posicao_x_premio;
int nivel_inicial_oxigenio=100;
int nivel_oxigenio;
int instalou_dec=NAO;
int instalou_aum=NAO;
int tempo_missao;
int pontos;
int frame_alert_premio_perto=0;
int max_risc,prof_max;
int frame_instrucao;
int bgmusic_time,restart_bgmusic=NAO;
int explodiu=NAO;
int nb;
int rad_x,rad_y;
int pos_y_radar;
int frame_som=1;
int pont_max=0;
int sonar_tocando=NAO;
int pisc;
int frame_ins_fisica;
SAMPLE *alerta_vermelho;
SAMPLE *sonar; 
MIDI *somfundo=NULL;
BITMAP *file;
//---------------funções--------------//
void init();
void deinit();

void sair(){
    putpixel(file,0,0,pont_max);
    save_bitmap("file.bmp",file,NULL);
    clear_keybuf();
    remove_timer();
    sai=1;}

void atualizar_som_sonar(){
     if(frame_alert_premio_perto==1&&etapa==JOGO&&frame_som==1)
     {
     play_sample(sonar,255,128,1000,FALSE);
     }}
     
void anime_explodir(){
     if(frame<7){frame++;}
     else{remove_int(anime_explodir);}}

int fx,fy,flar,falt,fid;

void iniciar_etapa(){
     etapa=etapa_iniciar;
     remove_int(iniciar_etapa);}
     
void checar_evento()
{
     if(mouse_x>fx&&mouse_x<fx+flar){
                                  if(mouse_y>fy&&mouse_y<fy+falt){
                                                               if(mouse_b==1){event_id=fid;}
                                                               }
                                  }
}

void checar_evento_ex()
{
     if(mouse_x>fx&&mouse_x<fx+flar){
                                  if(mouse_y>fy&&mouse_y<fy+falt){
                                                               event_id=fid;
                                                               }
                                  }
}

void checar_premio_area()
{
     if(Submarino.x+90>posicao_x_premio-30&&Submarino.x+90<posicao_x_premio+74){
                                  if(Submarino.y+127>posicao_y_premio&&Submarino.y+127<posicao_y_premio+42){
                                                               event_id=PREMIO_RESGATADO;
                                                               }
                                  }
}
     
int add_sensi_area(int x, int y, int lar,int alt, int id)
{
    fx=x;fy=y;flar=lar;falt=alt;fid=id;
}

void diminuir_oxigenio()
{
     if(nivel_oxigenio>0){nivel_oxigenio--;}
}
     
void aumentar_oxigenio()
{
     if(nivel_oxigenio<nivel_inicial_oxigenio){nivel_oxigenio++;}
}
           
void atualizar_pos_y_e_angulo_submarino()
{
     if(etapa==JOGO){
     if(Submarino.y<0){ dentro_dagua=0;}   
     else{dentro_dagua=1;}             
     if(equilibrio<0&&Submarino.angulo>-64){equilibrio++;exe++;Submarino.angulo--;}
     if(equilibrio>0&&Submarino.angulo<64){equilibrio--;exe++;Submarino.angulo++;}
     if(peso>empuxo){empulso_y++;}
     if(peso<empuxo){empulso_y--;}
     Submarino.y+=empulso_y;
     if(empulso_y>0){empulso_y--;}
     if(empulso_y<0){empulso_y++;}
     
     //if(Submarino.y<-10){allegro_message("deu certo");sair();}
     if(Submarino.y>90&&Submarino.y<750)
     {
        posy_cenario=Submarino.y-90;
     }}
}
void decer_paredao(){
     if(ty<480){
                ty++;}
     else{remove_int(decer_paredao);}}

void subir_paredao(){
     if(ty>0){
                ty--;
                remove_int(decer_paredao);}
     else{remove_int(subir_paredao);}}
     
void alertar()
{
     if(eparaalertar==SIM){
     if(frame_som==1){
     play_sample(alerta_vermelho, 100, 128, 2000, FALSE );}
     frame_alert++;
     if(frame_alert>1){frame_alert=0;}}
     else{remove_int(alertar);}
}

void atualizar_pos_x(){
     if(etapa==JOGO){
     if(Submarino.angulo!=-64&&Submarino.angulo!=64){
     if(por_forca_motor>0&&power==0){empulso_x+=1;}
     if(por_forca_motor>0&&power==1){empulso_x-=1;}
     if(por_forca_motor==0){
                            if(empulso_x<0){empulso_x++;}
                            if(empulso_x>0){empulso_x--;}
                            }
     if(power==0){Submarino.x+=(mp)+empulso_x/5;}
     if(power==1){Submarino.x-=(mp)-empulso_x/5;}}
     else{
          empulso_x=0;
          }
     if(Submarino.x<0){empulso_x=0;Submarino.x=0;}
     if(Submarino.x>1320){empulso_x=0;Submarino.x=1320;} 
                                                   
     if(Submarino.angulo>0&&por_forca_motor!=0&&dentro_dagua){
                                                 if(power==0){Submarino.y+=pacy-5;}
                                                 if(power==1){Submarino.y-=pacy-5;}
                                                 }
                                                 
     if(Submarino.angulo<0&&por_forca_motor!=0&&dentro_dagua){
                                                 if(power==1){Submarino.y-=pacy-7;}
                                                 if(power==0){Submarino.y+=pacy-7;}
      
                                                 }
      
     if(Submarino.x>320&&Submarino.x<1180)
     {
        posx_cenario=Submarino.x-320;
     }}
     }

void fim_de_jogo(){
     event_id=0;
     install_int(decer_paredao,2);
     etapa_iniciar=MENU;
     install_int(iniciar_etapa,1000);
     remove_int(fim_de_jogo);}
                                                          
void atualizar_variaveis(){
     if(etapa==JOGO){
     if(max_risc>nivel_oxigenio){max_risc=nivel_oxigenio;}
     if(prof_max<profundidade+10){prof_max=profundidade+10;}                
     pontos=(100-tempo_missao)+max_risc+prof_max;
     if(pontos<0){pontos=0;}
     peso=1400+(porcentagem_nivel_tanque_left/4)+(porcentagem_nivel_tanque_right/4)+(porcentagem_nivel_tanque_left/8)+(porcentagem_nivel_tanque_right/8);
     if(explodiu==NAO)profundidade=(Submarino.y/4);
     empuxo=1400+profundidade-(porcentagem_nivel_tanque_left+porcentagem_nivel_tanque_right);
     pressao=1+profundidade/10;
     if(empulso_x>0){sentido=1;}
     if(empulso_x<0){sentido=2;}
     if(empulso_x==0){sentido=0;}}
     
     if(Submarino.x+90>posicao_x_premio-400&&Submarino.x+90<posicao_x_premio+444)
     {
     if(Submarino.y+127>posicao_y_premio-400&&Submarino.y+127<posicao_y_premio+442){
     frame_alert_premio_perto=1;
     rad_x=(posicao_x_premio-Submarino.x)/10-8;
     rad_y=(posicao_y_premio-Submarino.y)/10-12;
     if(pos_y_radar<100){pos_y_radar++;}}
     else{frame_alert_premio_perto=0;}
     }
     else{frame_alert_premio_perto=0;if(pos_y_radar>0){pos_y_radar--;}}
                                                                             
     if(profundidade>1&&instalou_dec==NAO){
                                          remove_int(aumentar_oxigenio);
                                          install_int(diminuir_oxigenio,1000);
                                          instalou_aum=NAO;
                                          instalou_dec=SIM;
                                          }
     if(profundidade<1&&instalou_aum==NAO){
                                          remove_int(diminuir_oxigenio);
                                          install_int(aumentar_oxigenio,100);
                                          instalou_dec=NAO;
                                          instalou_aum=SIM;
                                          }
     if(nivel_oxigenio<20&&etapa==JOGO){
                           eparaalertar=SIM;
                           install_int(alertar,1000);
                           }
                           
}

void atualizacoes_menu()
{
posicao_y_premio=(rand()%500)+370;
posicao_x_premio=(rand()%1000)+100;
} 
     
void event(){
if(etapa==MENU){
//-----eventos do menu----//
    add_sensi_area(30,440,21,18, LigDesl_som);
    checar_evento();
    add_sensi_area(280,115,77,25, MINICIAR);
    checar_evento_ex();
    add_sensi_area(260,171,116,25, MINSTRUCOES);
    checar_evento_ex();
    add_sensi_area(280,232,63,25, MSOBRE);
    checar_evento_ex();
    
    add_sensi_area(280,115,77,25, MOS_FUND_FISICA);
    checar_evento();
    add_sensi_area(260,171,116,25, INSTRUCOES);
    checar_evento();
    add_sensi_area(280,232,63,25, SOBRE);
    checar_evento();}

//----------------EVENTOS PONTUACAO---------------------//
if(etapa==MOSTRAR_PONTUACAO){
    add_sensi_area(450,400,175,73, IR_PARA_MENU);
    checar_evento();} 

//-------------------EVENTOS SOBRE--------------------//
if(etapa==SOBRE){
    add_sensi_area(450,400,175,73, IR_PARA_MENU);
    checar_evento();}

//-------------------EVENTOS INSTRUÇÃO-------------------//    
if(etapa==INSTRUCOES){
    add_sensi_area(450,400,175,73, IR_PARA_MENU);
    checar_evento();
    add_sensi_area(40,400,175,73, PROXIMA_PAGINA);
    checar_evento();}

if(etapa==-1){
              add_sensi_area(40,400,175,73, PROXIMA_PAGINA);
              checar_evento();}       
//----eventos do jogo-----//
if(etapa==JOGO){
    if(mouse_b==1&&mouse_y<327&&mouse_y>103){
    if(mouse_x>(Submarino.x+90-posx_cenario)+30){event_id=RADIOOFF;}
    if(mouse_x<(Submarino.x+90-posx_cenario)-30){event_id=RADIOON;}}
    add_sensi_area(480,480-80,30,12, RADIOON);
    checar_evento();
    add_sensi_area(480+70,480-80,40,12, RADIOOFF);
    checar_evento();
    add_sensi_area(445,480-45, 172,27, MUDAR_FORCA_MOTOR);
    checar_evento();
    add_sensi_area(311,480-115,20,102-12, BRTIPO1L);
    checar_evento();
    add_sensi_area(373,480-115,20,102-12, BRTIPO1R);
    checar_evento();
    add_sensi_area(348,400,9,9, SUBIR);
    checar_evento();
    add_sensi_area(348,420,9,9, DECER);
    checar_evento();
    checar_premio_area();
    if(profundidade>186&&usuario_ciente_perigo==NAO){event_id=PRESSAO_ALTA;}
    if(profundidade<186&&nivel_oxigenio>20){usuario_ciente_perigo=NAO;eparaalertar=NAO;frame_alert=0;}
    if(profundidade>200||nivel_oxigenio==0){event_id=EXPLODIR;}
    if(key[KEY_LEFT]){event_id=RADIOON;}
    if(key[KEY_RIGHT]){event_id=RADIOOFF;}
    if(key[KEY_W]){event_id=SUBIR;}
    if(key[KEY_S]){event_id=DECER;}
    if(key[KEY_1]){mp=0;}
    if(key[KEY_2]){mp=1;}
    if(key[KEY_3]){mp=2;}
    if(key[KEY_4]){mp=3;}
    if(mp!=0){por_forca_motor=1;}
    else{por_forca_motor=0;}
    por_forca_motor=mp;
    if(key[KEY_P]){event_id=IR_PARA_MENU;}
    }
}

void crono(){
     tempo_missao++;}

void zerar_variaveis()
{
pos_y_radar=0;
nivel_oxigenio=nivel_inicial_oxigenio;
frame=0;
Submarino.y=0;
empulso_y=0;
empulso_x=0;
Submarino.x=-10;
nivel_tanque_left=0;
nivel_tanque_right=0;
porcentagem_nivel_tanque_left=0;
porcentagem_nivel_tanque_right=0;
Submarino.angulo=0;
mp=0;por_forca_motor=0;
btfposyl=458;
btfposyr=458;
equilibrio=0;
posy_cenario=0;
posx_cenario=0;
explodiu=NAO;
remove_int(zerar_variaveis);
}

void gerenciador_tempo()
{
    if(etapa==JOGO)
    {
    install_int(crono,1000);
    install_int(atualizar_variaveis,10);
	install_int(atualizar_pos_y_e_angulo_submarino,80);
	install_int(atualizar_pos_x,80);
    }
    
	else
    {
         remove_int(crono);
         remove_int(alertar);
         remove_int(fim_de_jogo);
         remove_int(aumentar_oxigenio);
         remove_int(diminuir_oxigenio);
         remove_int(atualizar_variaveis);
         remove_int(atualizar_pos_y_e_angulo_submarino);
         remove_int(atualizar_pos_x);
         remove_int(fim_de_jogo);
         remove_int(diminuir_oxigenio);
         remove_int(anime_explodir);
         zerar_variaveis();
    }
    if(etapa==MENU){
                    install_int(atualizacoes_menu,10);
                    }
    else{
         remove_int(atualizacoes_menu);
         }
    if(bgmusic_time>3){
                           restart_bgmusic=SIM;}
    bgmusic_time++;
}
       
int main() {
	init();
	install_int(atualizar_som_sonar,2000);
	install_int(atualizacoes_menu,10);
	PALLETE pal;
	SAMPLE *explosao;
    if(load_wav("sonar.wav")==NULL||load_midi("somfundo.mid")==NULL||load_wav("alerta_vermelho.wav")==NULL||load_wav("explosao.wav")==NULL){allegro_message("falha ao carregar o som de fundo!");}
    else
    {
        sonar=load_wav("sonar.wav");
        explosao=load_wav("explosao.wav");
        somfundo=load_midi("somfundo.mid");
        alerta_vermelho=load_wav("alerta_vermelho.wav");
        play_midi(somfundo,FALSE);
        midi_seek(10);
    }
    if(load_bitmap("file.bmp",NULL)!=NULL)
    {file=load_bitmap("file.bmp",NULL);pont_max=getpixel(file,0,0);}
    else
    {file=create_bitmap(1,1); 
    clear_to_color(file,0);
    save_bitmap("file.bmp",file,NULL);}
	//CARREGAR IMAGENS
    BITMAP *buffer=create_bitmap(640,480);
    BITMAP *calc_sub=create_bitmap(11,11);
    BITMAP *buf_calc_sub=create_bitmap(11,11);
    //CALCULO DE DIRECAO//
    clear_to_color(buf_calc_sub,makecol(0,0,0));
    clear_to_color(calc_sub,makecol(0,0,0));
    putpixel(calc_sub,9,5,makecol(255,255,255));
    //FIM DE CALCULO DE DIRECAO//
    //CONTINUAR A CARREGAR IMAGENS
    BITMAP *cenario=create_bitmap(1500,1000);
    BITMAP *tamanho_tela[2];
    tamanho_tela[0]=load_bitmap("max.bmp",NULL);
    tamanho_tela[1]=load_bitmap("min.bmp",NULL);    
    BITMAP *som[2];
    som[0]=load_bitmap("som_desligado.bmp",NULL);
    som[1]=load_bitmap("som_ligado.bmp",NULL);
    BITMAP *buffer_cenario=create_bitmap(1500,1000);
    clear_to_color(cenario,makecol(0,24,196));
    BITMAP *controle=load_bitmap("controle.bmp",NULL);
    BITMAP *nuvem=load_bitmap("nuven.bmp",NULL);
    BITMAP *base=load_bitmap("base.bmp",NULL);
    BITMAP *paredao=load_bitmap("paredao.bmp",NULL);
    BITMAP *pontuacao=load_bitmap("pontuacao.bmp",NULL);
    BITMAP *mouse=load_bitmap("mouse.bmp",NULL);
    BITMAP *premio=load_bitmap("premio.bmp",NULL);   
    BITMAP *bolhas=load_bitmap("Bolhas01.bmp",NULL);
    BITMAP *mask_radar=create_bitmap(100,100);
    clear_to_color(mask_radar,makecol(195,195,195));
    circlefill(mask_radar,50,50,49,makecol(87,87,87));
    circlefill(mask_radar,50,50,41,makecol(255,0,255));
    circle(mask_radar,50,50,40,makecol( 0,255,0));
    circle(mask_radar,50,50,30,makecol( 0,255,0));
    circle(mask_radar,50,50,20,makecol( 0,255,0));
    circle(mask_radar,50,50,10,makecol( 0,255,0));
    line(mask_radar, 9,50, 91, 50, makecol(0,255,0));
    line(mask_radar, 50,9, 50, 91, makecol(0,255,0));
    rect(mask_radar,0,0,99,99,makecol(0,0,0));
    save_bitmap("calculo.bmp",mask_radar,NULL);
    BITMAP *radar=create_bitmap(100,100);
    //escrevendo sobre//
    BITMAP *sobre=load_bitmap("sobre.bmp",NULL); 
    textprintf_centre_ex(sobre, font, 320, 140, makecol(255,255,0), -1,"INFORMACOES TECNICAS:");
    textprintf_centre_ex(sobre, font, 320, 160, makecol(255,255,0), -1,"A criacao deste jogo foi concluida em 03/09/2012. Desenvolvido por"); 
    textprintf_centre_ex(sobre, font, 320, 170, makecol(255,255,0), -1,"Lucas Santana do Nascimento Portela.Este software simula o movimento"); 
    textprintf_centre_ex(sobre, font, 320, 180, makecol(255,255,0), -1,"de um submarino. Para sua criacao se tornar possivel foram empregados"); 
    textprintf_centre_ex(sobre, font, 320, 190, makecol(255,255,0), -1,"alguns principios da fisica: peso, empuxo, inercia e impulso.");
    textprintf_centre_ex(sobre, font, 320, 220, makecol(255,255,0), -1,"AGRADECIMENTOS:");
    textprintf_centre_ex(sobre, font, 320, 240, makecol(255,255,0), -1,"Agradeco primeiramente a Deus por colocar pessoas com grande conhecimento");
    textprintf_centre_ex(sobre, font, 320, 250, makecol(255,255,0), -1,"academico na minha vida, afim de me capacitar a alcancar frutos antes");
    textprintf_centre_ex(sobre, font, 320, 260, makecol(255,255,0), -1,"inalcancaveis, e tambem colocar pessoas que me apoiam e acreditam em mim,");
    textprintf_centre_ex(sobre, font, 320, 270, makecol(255,255,0), -1,"me dando forcas para continuar a fazer o que faco.");
    textprintf_centre_ex(sobre, font, 320, 280, makecol(255,255,0), -1,"Pessoas como essas nunca esquecerei:");
    textprintf_centre_ex(sobre, font, 320, 290, makecol(255,255,0), -1,"Evelin Santana(minha mae), Alexandre Zeitune(meu professor),");
    textprintf_centre_ex(sobre, font, 320, 300, makecol(255,255,0), -1," Sergio Freitas(um grande programador), LenoMarques e Demostenes(meus tios),");
    textprintf_centre_ex(sobre, font, 320, 310, makecol(255,255,0), -1,"Geraldo Augusto(Meu Pai).");
    
    BITMAP *instrucoes[2];
    instrucoes[0]=load_bitmap("instrucoes1.bmp",NULL);
    instrucoes[1]=load_bitmap("instrucoes2.bmp",NULL); 
     
    BITMAP *submarino[8];
    submarino[0]=load_bitmap("submarino.bmp",NULL);
    submarino[1]=load_bitmap("submarino2.bmp",NULL);
    submarino[2]=load_bitmap("submarino3.bmp",NULL);
    submarino[3]=load_bitmap("submarino4.bmp",NULL);
    submarino[4]=load_bitmap("submarino5.bmp",NULL);
    submarino[5]=load_bitmap("submarino6.bmp",NULL);
    submarino[6]=load_bitmap("submarino7.bmp",NULL);
    submarino[7]=load_bitmap("submarino8.bmp",NULL);
    
    BITMAP *alert[2];
    alert[0]=load_bitmap("alert_off.bmp",NULL);
    alert[1]=load_bitmap("alert_on.bmp",NULL);
    
    BITMAP *premio_perto[2];
    premio_perto[0]=load_bitmap("alert_off.bmp",NULL);
    premio_perto[1]=load_bitmap("alert_green.bmp",NULL);
    
    BITMAP *menu[4];
    menu[0]=load_bitmap("menu.bmp",NULL);
    menu[1]=load_bitmap("menu_iniciar.bmp",NULL);
    menu[2]=load_bitmap("menu_instrucoes.bmp",NULL);
    menu[3]=load_bitmap("menu_sobre.bmp",NULL);
    
    BITMAP *subir[2];
    subir[0]=load_bitmap("subir.bmp",NULL);
    subir[1]=load_bitmap("subir_sel.bmp",NULL);
    
    BITMAP *decer[2];
    decer[0]=load_bitmap("decer.bmp",NULL);
    decer[1]=load_bitmap("decer_sel.bmp",NULL);
    
    BITMAP *br1=load_bitmap("barra_de_rolagem_tipo1.bmp",NULL);
    BITMAP *btr1[2];
    btr1[0]=load_bitmap("botao_de_rolagem_tipo1.bmp",NULL);
    btr1[1]=load_bitmap("botao_de_rolagem_tipo_sel1.bmp",NULL);
    
    BITMAP *br2[4];
    br2[0]=load_bitmap("barra_de_rolagem_tipo2off.bmp",NULL);
    br2[1]=load_bitmap("barra_de_rolagem_tipo2_1.bmp",NULL);
    br2[2]=load_bitmap("barra_de_rolagem_tipo2_2.bmp",NULL);
    br2[3]=load_bitmap("barra_de_rolagem_tipo2_3.bmp",NULL);
    
    BITMAP *radio[2];
    radio[0]=load_bitmap("radio_off.bmp",NULL);
    radio[1]=load_bitmap("radio_on.bmp",NULL);
    
    BITMAP *fun_fisica[4];
    fun_fisica[0]=load_bitmap("instrucoes3.bmp",NULL);
    fun_fisica[1]=load_bitmap("instrucoes4.bmp",NULL);
    fun_fisica[2]=load_bitmap("instrucoes5.bmp",NULL);
    fun_fisica[3]=load_bitmap("instrucoes6.bmp",NULL);
    
    //organizando buffer do cenario
    sx=0;sy=113;
    while(sy<1000){
                   rectfill(cenario,0,sy,1500,sy+20,makecol(0,0,cor));
                   sy+=20;
                   if(cor>70){cor-=10;}}
    rectfill(cenario,0,0,1500,113,makecol(153,217,234));
    masked_blit(nuvem,cenario,0,0,nuvempos+70,0,155,86);
    masked_blit(nuvem,cenario,0,0,nuvempos+450,20,155,86);
    masked_blit(nuvem,cenario,0,0,nuvempos+800,10,155,86);
    masked_blit(nuvem,cenario,0,0,nuvempos+1300,25,155,86);
    while(nb<50){
    rotate_sprite_v_flip(cenario,bolhas,(rand()%1400),(rand()%850)+113,itofix(rand()%64));
    nb++;}
    //loop principal
	while (sai==0) {
    //GERENCIAR MUSICA DE FUNDO//
    if(frame_som==1){
    if(restart_bgmusic==SIM){
                             stop_midi();
                             restart_bgmusic=NAO;
                             bgmusic_time=0;
                             play_midi(somfundo,FALSE);
                             midi_seek(10);}}
    else{stop_midi();}
    //------------imagens da etapa sobre-----------------------------//
    if(etapa==SOBRE){
                     draw_sprite(buffer,sobre,0,0);}
    //-------------------------------IMAGENS DO JOGO----------------------//      
    if(etapa==JOGO)
    {
    blit(cenario,buffer_cenario,0,0,0,0,1500,1000);
    masked_blit(premio,buffer_cenario,0,0,posicao_x_premio,posicao_y_premio,44,42);
    rotate_sprite(buffer_cenario,submarino[frame],Submarino.x, Submarino.y+100,itofix(Submarino.angulo));
    masked_blit(base,buffer_cenario,0,0,0,19,211,157);
    if(key[KEY_L]&&key[KEY_S]){save_bitmap("mapa.bmp",buffer_cenario,NULL);}
    blit(buffer_cenario,buffer,posx_cenario,posy_cenario,0,0,640,480);
    
    //imprimindo as imagens na tela
    clear_to_color(radar,makecol(14,75,32));
    circlefill(radar,rad_x+50,rad_y+50,2,makecol(0,255,0));
    circlefill(radar,50,50,2,makecol(255,0,0));
    masked_blit(mask_radar,radar,0,0,0,0,100,100);
    masked_blit(radar,buffer,0,0,270,pos_y_radar-100,100,100);
    clear_bitmap(radar);
	blit(controle,buffer,0,0,0,480-153,640,153);
	masked_blit(alert[frame_alert],buffer,0,0,439,365,25,25);
	masked_blit(premio_perto[frame_alert_premio_perto],buffer,0,0,599,365,25,25);
	masked_blit(subir[sobe],buffer,0,0,348,400,9,9);
	masked_blit(decer[dece],buffer,0,0,348,420,9,9);
	masked_blit(br1,buffer,0,0,311,480-115,20,102);
	masked_blit(btr1[selL],buffer,0,0,311+10-15,btfposyl-6,30,12);
	masked_blit(br1,buffer,0,0,373,480-115,20,102);
	masked_blit(btr1[selR],buffer,0,0,311+10-15-(311-373),btfposyr-6,30,12);
    masked_blit(br2[mp],buffer,0,0,445,480-45,640,153);
    masked_blit(radio[power],buffer,0,0,480,480-80,104,12);   
    //colocar dados na tabela
    textprintf_ex(buffer, font, 5, 2, makecol(255,0,0), -1,"Tikuna(S-34)");
    textprintf_ex(buffer, font, 5, 12, makecol(255,0,0), -1,"Tempo Transcorrido %d s",tempo_missao);
    textprintf_right_ex(buffer, font, 265, 359, makecol(0,0,255), makecol(195,195,195),"%d ton",peso);
    textprintf_right_ex(buffer, font, 265, 373, makecol(0,0,255), makecol(195,195,195),"%d ton",empuxo);
    textprintf_right_ex(buffer, font, 265, 387, makecol(0,0,255), makecol(195,195,195),"%d m",profundidade+1);
    textprintf_right_ex(buffer, font, 265, 401, makecol(0,0,255), makecol(195,195,195),"%d atm",pressao);
    textprintf_right_ex(buffer, font, 265, 415, makecol(0,0,255), makecol(195,195,195),"%d",por_forca_motor);
    textprintf_right_ex(buffer, font, 265, 430, makecol(0,0,255), makecol(195,195,195),"%d %%",nivel_oxigenio);
    textprintf_right_ex(buffer, font, 265, 460, makecol(0,0,255), makecol(195,195,195),"%d",empulso_x);
    if(sentido==ParaFrente){textprintf_right_ex(buffer, font, 265, 445, makecol(0,0,255), makecol(195,195,195),"-->",sentido);}
    if(sentido==ParaTras){textprintf_right_ex(buffer, font, 265, 445, makecol(0,0,255), makecol(195,195,195),"<--",sentido);}
    if(sentido==Parado){textprintf_right_ex(buffer, font, 265, 445, makecol(0,0,255), makecol(195,195,195),"---",sentido);}
    //calcular inclinacao
    rotate_sprite(buf_calc_sub,calc_sub,0,0,itofix(Submarino.angulo));
    sx=0;sy=0;
    pacx=0;pacy=0;
    pixel_achado=NAO;
    while(sy<11&&pixel_achado==NAO){
                                     while(sx<11&&pixel_achado==NAO){
                                                  if(getpixel(buf_calc_sub,sx,sy)==makecol(255,255,255)){pixel_achado=SIM;}
                                                  sx++;
                                                  }
                                     sx=0;sy++;
                                     }
     if(pixel_achado==SIM){pacx=sx;pacy=sy;}
    }
    //------------------------------FIM DE IMAGENS DO JOGO--------------------------------------------//
    
    //-------------------------------PONTUACAO---------------------------------------//
    if(etapa==MOSTRAR_PONTUACAO)
    {
    if(pontos>pont_max){pont_max=pontos;}
    blit(pontuacao,buffer,0,0,0,0,640,480);
    textprintf_centre_ex(buffer, font, 320, 150, makecol(0,255,0), -1,"Parabens! Voce conseguiu completar essa missao.");
    textprintf_ex(buffer, font, 220, 250, makecol(0,255,0), -1,"Duracao da missao: %d s.",tempo_missao);
    textprintf_ex(buffer, font, 220, 260, makecol(0,255,0), -1,"Sua pontuacao: %d pontos.",pontos);
    textprintf_ex(buffer, font, 220, 270, makecol(0,255,0), -1,"Pontuacao maxima: %d pontos.",pont_max);
    }
    
    if(etapa==INSTRUCOES)
    {
    blit(instrucoes[frame_instrucao],buffer,0,0,0,0,640,480);
    }
                          
    //--------------------------IMAGES DO MENU-----------------------------------//
    if(etapa==MENU)
    {
    masked_blit(menu[frame_menu],buffer,0,0,0,0,640,480);
    masked_blit(som[frame_som],buffer,0,0,30,440,21,18);
    }
    
    if(etapa==-1){
    draw_sprite(buffer,fun_fisica[frame_ins_fisica],0,0);}
    
    blit(paredao,buffer,0,0,0,-480+ty,640,480);                             
    rotate_sprite(buffer,mouse,mouse_x,mouse_y,itofix(0));
    masked_blit(buffer,screen,0,0,0,0,640,480);
    clear_keybuf();
    //tratando eventos
    sel=0;
    selR=0;
    selL=0;
    
    //----------------------------EVENTOS GLOBAIS------------------------//
    switch(event_id){
                     case MOS_FUND_FISICA:
                          etapa=-1;
                          break;
                          
                     case IR_PARA_MENU:
                          zerar_variaveis();
                          install_int(decer_paredao,2);
                          etapa_iniciar=MENU;
                          install_int(iniciar_etapa,955);
                          event_id=0;
                          break;
                          
                     case PROXIMA_PAGINA:
                          rest(500);
                          if(etapa==INSTRUCOES){
                          frame_instrucao++;
                          if(frame_instrucao>1){frame_instrucao=0;}}
                          if(etapa==-1){
                          frame_ins_fisica++;
                          if(frame_ins_fisica>3){etapa=JOGO;event_id=INICIAR; frame_ins_fisica=0;}}
                          rest(500);
                          event_id=0;
                          break;
                     }

    if(event_id==BRTIPO1L){
    if(mouse_b==1){
                          if(btfposyl>mouse_y){key[KEY_UP]=1;}
                          else{key[KEY_UP]=0;}
                          if(btfposyl<mouse_y){key[KEY_DOWN]=1;}
                          else{key[KEY_DOWN]=0;}}
                          else{key[KEY_DOWN]=0;key[KEY_UP]=0;}}
                          
    if(event_id==BRTIPO1R){
    if(mouse_b==1){
                          if(btfposyr>mouse_y){key[KEY_UP]=1;}
                          else{key[KEY_UP]=0;}
                          if(btfposyr<mouse_y){key[KEY_DOWN]=1;}
                          else{key[KEY_DOWN]=0;}}
                          else{key[KEY_DOWN]=0;key[KEY_UP]=0;}}                  
    //------------------------------EVENTOS DO JOGO-----------------------------//
    if(etapa==JOGO){
    switch(event_id){
                     case RADIOON:
                          power=1;
                          break;
                     case RADIOOFF:
                          power=0;
                          break;
                          
                     case MUDAR_FORCA_MOTOR:
                          mp++;
                          if(mp>3){mp=0;}
                          if(mp!=0){por_forca_motor=1;}
                          else{por_forca_motor=0;}
                          rest(200);
                          event_id=0;
                          break;
                            
                     case BRTIPO1L:
                          selL=1;
                          if(key[KEY_UP]&&btfposyl>372){
                          equilibrio-=3;
                          nivel_tanque_left+=2;
                          btfposyl--;
                          rest(exe);}
                          if(key[KEY_DOWN]&&btfposyl<458){
                          equilibrio+=3;
                          nivel_tanque_left-=2;
                          btfposyl++;
                          rest(exe);}
                          porcentagem_nivel_tanque_left=(100*nivel_tanque_left)/86;
                          event_id=0;
                          break;
                     case BRTIPO1R:
                          selR=1;
                          if(key[KEY_UP]&&btfposyr>372){
                          equilibrio+=3;
                          nivel_tanque_right+=2;
                          btfposyr--;
                          rest(exe);}
                          if(key[KEY_DOWN]&&btfposyr<458){
                          equilibrio-=3;
                          nivel_tanque_right-=2;
                          btfposyr++;
                          rest(exe);}
                          porcentagem_nivel_tanque_right=(100*nivel_tanque_right)/86;
                          event_id=0;
                          break;
                          
                     case DECER:
                          dece=1;
                          sobe=0;
                          
                          if(btfposyl<458){
                          equilibrio+=3;
                          nivel_tanque_left-=2;
                          btfposyl++;}
                          porcentagem_nivel_tanque_left=(100*nivel_tanque_left)/86;
                          
                          if(btfposyr<458){
                          equilibrio-=3;
                          nivel_tanque_right-=2;
                          btfposyr++;}
                          porcentagem_nivel_tanque_right=(100*nivel_tanque_right)/86;
                          rest(exe);
                          event_id=0;
                          break;
                          
                     case SUBIR:
                          sobe=1;
                          dece=0;
                          
                          if(btfposyr>372){
                          equilibrio+=3;
                          nivel_tanque_right+=2;
                          btfposyr--;}
                          porcentagem_nivel_tanque_right=(100*nivel_tanque_right)/86;
                          
                          if(btfposyl>372){
                          equilibrio-=3;
                          nivel_tanque_left+=2;
                          btfposyl--;}
                          porcentagem_nivel_tanque_left=(100*nivel_tanque_left)/86;
                          rest(exe);
                          
                          event_id=0;
                          break;
                          
                     case PREMIO_RESGATADO:
                          remove_int(crono);
                          remove_int(alertar);
                          eparaalertar=NAO;
                          install_int(decer_paredao,2);
                          eparaalertar=NAO;
                          etapa_iniciar=MOSTRAR_PONTUACAO;
                          install_int(iniciar_etapa,955);
                          break;
                     
                     case PRESSAO_ALTA:
                          eparaalertar=SIM;
                          install_int(alertar,1000);
                          usuario_ciente_perigo=SIM;
                          break;  
                          
                     case EXPLODIR:
                          stop_midi();
                          remove_int(alertar);
                          install_int(anime_explodir,100);
                          if(explodiu==NAO){if(frame_som==1){play_sample(explosao, 255, 128, 1000, FALSE );}explodiu=SIM;}
                          install_int(fim_de_jogo,800);
                          install_int(zerar_variaveis,955+600);
                          event_id=0;
                          break;}
                               } 
                               
//-----------------------------------EVENTOS DO MENU----------------------------//
               if(etapa==MENU){
                    switch(event_id){
                     case LigDesl_som:
                          if(frame_som==1)frame_som=0;
                          else frame_som=1;
                          rest(500);
                          event_id=0;
                          break;
                     case MINICIAR:
                          frame_menu=1;
                          break;
                          
                     case MINSTRUCOES:
                          frame_menu=2;
                          break;
                     
                     case MSOBRE:
                          frame_menu=3;
                          break;
                          
                     case INICIAR:
                          tempo_missao=0;
                          nivel_inicial_oxigenio=100;
                          zerar_variaveis();
                          install_int(decer_paredao,2);
                          etapa_iniciar=JOGO;
                          install_int(iniciar_etapa,955);                      
                          break;
                          
                     case INSTRUCOES:
                          install_int(decer_paredao,2);
                          etapa_iniciar=INSTRUCOES;
                          install_int(iniciar_etapa,955);
                          break;
                     
                     case SOBRE:
                          install_int(decer_paredao,2);
                          etapa_iniciar=SOBRE;
                          install_int(iniciar_etapa,955);
                          break;
                     default:
                             tempo_missao=0;
                             break;
                      }
                     }
               
    if(ty==480){install_int(subir_paredao,2);}
    clear_keybuf();
	clear_bitmap(buffer);
	clear_bitmap(buffer_cenario);
	if(key[KEY_ENTER]){save_bitmap("snapshot.bmp",screen,NULL);}
	}
	deinit();
	return 0;
}
END_OF_MAIN();
     
void init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
	BITMAP *carregar=load_bitmap("carregando.bmp",NULL);
	blit(carregar,screen,0,0,0,0,640,480);
	//-----------------timers--------------------//
	install_int(event,5);
	install_int(gerenciador_tempo,4000);
	//--------------------------------------------//
	set_close_button_callback(sair);
    set_window_title("SubControl Tikuna(S-34)");
	install_timer();
	install_keyboard();
	install_mouse();	
    position_mouse_z(17);
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
	/* add other initializations here */
}


void deinit() {
	clear_keybuf();
	allegro_exit();
}