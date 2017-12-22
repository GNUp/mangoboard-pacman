#include "../include/lcd.h"
#include "../include/s3c_uart.h"
#include "../include/s3c6410.h"
#include "../include/interrupt.h"
#include "../include/main.h"

#define MAX_LIFE 3

/* Map of pacman */
int start = 0;	// If 1 then, start mode
int life = MAX_LIFE;
unsigned int count = 0;
way direction = UNDEF;

block map[20][28];
pos pacman;
pos enemy[4];

void draw_map()
{
	int i, j;

	for (i = 0; i < 20; i++)
		for (j = 0; j < 28; j++)
		{
			if(map[i][j].block_type == WALL)
				print_block(0x0000ff,40+20*i,40+20*j);
			else if(map[i][j].block_type == COIN)
				print_coin(0xffff00,40+20*i,40+20*j);
			else
				print_block(0x000000,40+20*i,40+20*j);
		}
}

void main_init(void)
{
	int i, j;
	unsigned int *ph = FB_ADDR;
	for (i = 0; i < 480; i++)
		for(j = 0; j <800;j++)
			ph[i*800+j]=0x000000;
	

	/* Initiallize all the map to indicate BACK */
	for (i = 0; i < 20; i++)
		for (j = 0; j < 28; j++)
		{
			map[i][j].block_type = WALL;
		}
	
	//Positioning pacman and enemy
	pacman.x = 14;
	pacman.y = 18;
	enemy[0].x = 14;
	enemy[0].y = 6;
  enemy[1].x = 14;
  enemy[1].y = 7;
  enemy[2].x = 15;
  enemy[2].y = 6;
  enemy[3].x = 15;
  enemy[3].y = 7;
  map[6][14].block_type = BACK;
	map[7][14].block_type = BACK;
	map[6][15].block_type = BACK;
	map[7][15].block_type = BACK;

	//Positioning COIN and WALL
	coin_init();	

	// Draw controller
	print_controller();
}

void mango_menu_main(void){

	//Print first face
	draw_map();
	//print map
	while(1)
	{
	// Input code here	
	
		count = ++count % 100;
	}
}
/* This is the main function */
int main(void){

  /* Initillazing lcd */
  mango_uart_init(1, 115200);
  lcd_bl_on(MAX_BL_LEV-1);
  lcd_pwr_on();
  init_lcd_reg();
  set_lcd_pos(0, 0, S3CFB_HRES, S3CFB_VRES);
  mango_hw_init();

	/* Initiallize */
	main_init();
	draw_image_red();
	enable_interrupts();
  mango_menu_main();
  return 0;
}

void coin_init()
{
	int i;

	for(i = 1; i < 27; i++)
  	map[1][i].block_type=COIN;
	for(i = 1; i < 27; i++)
  	map[18][i].block_type=COIN;
	for(i = 1; i < 27; i++)
	  map[13][i].block_type=COIN;
	for(i = 1; i < 27; i++)
  	map[5][i].block_type=COIN;

	map[2][1].block_type=COIN;
	map[2][5].block_type=COIN;
	map[2][10].block_type=COIN;
	map[2][18].block_type=COIN;
	map[2][22].block_type=COIN;
	map[2][26].block_type=COIN;

	map[3][1].block_type=COIN;
	map[3][5].block_type=COIN;
	map[3][10].block_type=COIN;
	map[3][18].block_type=COIN;
	map[3][22].block_type=COIN;
	map[3][26].block_type=COIN;

	map[4][1].block_type=COIN;
	map[4][5].block_type=COIN;
	map[4][10].block_type=COIN;
	map[4][18].block_type=COIN;
	map[4][22].block_type=COIN;
	map[4][26].block_type=COIN;

	map[14][1].block_type=COIN;
	map[14][5].block_type=COIN;
	map[14][10].block_type=COIN;
	map[14][18].block_type=COIN;
	map[14][22].block_type=COIN;
	map[14][26].block_type=COIN;

	map[15][1].block_type=COIN;
	map[15][5].block_type=COIN;
	map[15][10].block_type=COIN;
	map[15][18].block_type=COIN;
	map[15][22].block_type=COIN;
	map[15][26].block_type=COIN;

	map[16][1].block_type=COIN;
	map[16][5].block_type=COIN;
	map[16][10].block_type=COIN;
	map[16][18].block_type=COIN;
	map[16][22].block_type=COIN;
	map[16][26].block_type=COIN;

	map[17][1].block_type=COIN;
	map[17][5].block_type=COIN;
	map[17][10].block_type=COIN;
	map[17][18].block_type=COIN;
	map[17][22].block_type=COIN;
	map[17][26].block_type=COIN;

	map[6][5].block_type=COIN;
	map[6][10].block_type=COIN;
	map[6][18].block_type=COIN;
	map[6][22].block_type=COIN;

	map[7][5].block_type=COIN;
	map[7][10].block_type=COIN;
	map[7][18].block_type=COIN;
	map[7][22].block_type=COIN;

	map[8][5].block_type=COIN;
	map[8][10].block_type=COIN;
	map[8][18].block_type=COIN;
	map[8][22].block_type=COIN;

	map[9][5].block_type=COIN;
	map[9][10].block_type=COIN;
	map[9][18].block_type=COIN;
	map[9][22].block_type=COIN;
	for(i = 0;i < 6; i++)
	  map[9][i].block_type=COIN;
	for(i = 22;i < 28; i++)
	  map[9][i].block_type=COIN;

	map[10][5].block_type=COIN;
	map[10][10].block_type=COIN;
	map[10][18].block_type=COIN;
	map[10][22].block_type=COIN;

	map[11][5].block_type=COIN;
	map[11][10].block_type=COIN;
	map[11][18].block_type=COIN;
	map[11][22].block_type=COIN;

	map[12][5].block_type=COIN;
	map[12][10].block_type=COIN;
	map[12][18].block_type=COIN;
	map[12][22].block_type=COIN;
}
