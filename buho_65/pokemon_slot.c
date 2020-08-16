# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <time.h>
void print_slot(char *left, char *center, char *right);
char* slot( int lane , char slot[][30]);
void bonus_mode( int *have_coin );
void check_slot(char *left, char *center, char *right, int *have_coin);




char* slot( int lane , char slot[][30]){
  srand(time(NULL));
  char *result;

  if(lane == 1){
    result = slot[rand() % 7];
  }
  else if(lane == 2){
    result = slot[rand() % 10];
  }
  else{
    result = slot[rand() % 18];
  }
  return result;
}


void check_slot(char *left, char *center, char *right, int *have_coin){
  char *seven = "    7     ";
  char *pokemon = " POKEMON  ";
  char *cherry = "  cherry  ";
  char *moon_stone = "moon_stone";
  char *pikachu = " pikachu  ";
  int bonus = rand() % 5;    // ボーナスモードに入るかのフラグ
  if(strcmp(seven, left) == 0){
    if(strcmp(seven, center) == 0){
      if(strcmp(seven, right) == 0){
        printf("You WIN! +100 coins\n");
        *have_coin += 100;
        if(bonus == 0){
          bonus_mode(have_coin);
        }
      }
    }
  }
  if(strcmp(pokemon, left) == 0){
    if(strcmp(pokemon, center) == 0){
      if(strcmp(pokemon, right) == 0){
        printf("You WIN! +100 coins\n");
        *have_coin += 100;
        if(bonus == 0){
          bonus_mode(have_coin);  
        }
      }
    }
  }
  if(strcmp(cherry, left) == 0){
    printf("You WIN! +2 coins\n");
    *have_coin += 2;
  }
  if(strcmp(moon_stone, left) == 0){
    if(strcmp(moon_stone, center) == 0){
      if(strcmp(moon_stone, right) == 0){
        printf("You WIN! +15 coins\n");
        *have_coin += 15;
        if(bonus == 0){
          bonus_mode(have_coin);
        }
      }
    }
  }
  if(strcmp(pikachu, left) == 0){
    if(strcmp(pikachu, center) == 0){
      if(strcmp(pikachu, right) == 0){
        printf("You WIN! +10 coins\n");
        *have_coin += 10;
        if(bonus == 0){
          bonus_mode(have_coin);
        }
      }
    }
  }
  return ;
}


void bonus_mode(int *have_coin){
  char bonus_slot_machine_x[2][30] = 
  {"    7     ", " POKEMON  "};
  char bonus_slot_machine_y[3][30] = 
  {"  cherry  ", "moon_stone", "moon_stone",};
  char bonus_slot_machine_z[12][30] = 
  {"    7     ", " POKEMON  ", " POKEMON  ", "  cherry  ", "  cherry  ", "  cherry  ","moon_stone", "moon_stone", "moon_stone", " pikachu  ", " pikachu  ", " pikachu  "};
  int i, j;
  int bonus_count = 1;
  int pippi;
  int put_int;
  char *replay = "  replay  ";
  char string_buffer[100];
  srand(time(NULL));

  // ボーナスモード突入
  while(1){
    printf("\n\n\nBonus_Round %d!\n", bonus_count);
    // １ラウンド15回転
    for(i = 1; i <= 15; i++){
      int judge[4] = {0, 0, 0, 0};
      char *slot[4] = {NULL, NULL, NULL, NULL};

      // コインが残っているか
      if(*have_coin <= 0){
        printf("コインが足りなくなったので終了します。残り枚数は%d枚でした。\n", *have_coin);
        exit(0);
      }
      // 1プレイ
      printf("1 Bet!\n");
      *have_coin -= 1;
      for(j = 0; j < 3; j++){
        // ピッピの道しるべ
        pippi = (rand() % 3) + 1;
        if(judge[pippi] == 1){
          j--;
          continue;
        }
        // 入力
        print_slot(slot[1], slot[2], slot[3]);
        printf("1 = left lane, 2 = center lane, 3 = right lane  (5 = exit)\n");
        printf("push %d !> ", pippi);  
        scanf("%s", string_buffer); 
        put_int = atoi(string_buffer);
        // ボーナスモード５:exit
        if(put_int == 5){
          printf("終了します。残りコインの枚数は%d枚でした。\n", *have_coin + 1);
          exit(0);
        }
        // ボーナスモード１，２，３：レーンをとめる
        if(put_int != 1 && put_int != 2 && put_int != 3){
          printf("Error! 正しい番号を入れてね\n"); 
          j--;
          continue;
        }
        if(judge[put_int] == 1){
          printf("Warning! すでに止めました\n");
          j--;
          continue;
        }
        // ピッピに従った
        if((put_int == pippi) && (judge[pippi] == 0)){ 
          slot[put_int] = replay; 
          judge[put_int] = 1;
        }
        // ピッピに従わなかった
        else if((put_int != pippi) && (judge[put_int] == 0)){
          if(put_int == 1){
            slot[put_int] = bonus_slot_machine_x[rand() % 2];
            judge[put_int] = 1;
          }
          else if(put_int == 2){
            slot[put_int] = bonus_slot_machine_y[rand() % 3];
            judge[put_int] = 1;
          }
          else{
            slot[put_int] = bonus_slot_machine_z[rand() % 12];
            judge[put_int] = 1;
          }
        }
      }
      print_slot(slot[1], slot[2], slot[3]);
      if(strcmp(replay, slot[1]) == 0){
        if(strcmp(replay, slot[2]) == 0){
          if(strcmp(replay, slot[3]) == 0){
            printf("You WIN! +15 coins\n");
            *have_coin += 15;
          }
        }
      }
      printf("\n");
    }
    // ボーナスモードを継続するか
    if(rand() % bonus_count != 0){
      printf("Bonus finish!\n\n");
      break;
    }
    bonus_count++;
  }
}


void print_slot(char *left, char *center, char *right){
  printf("[");
  if(left == NULL){ printf("          "); }
  else{ printf("%s", left); }
  printf(",");
  if(center == NULL){ printf("          "); }
  else{ printf("%s", center); }
  printf(",");
  if(right == NULL){ printf("          "); }
  else{ printf("%s", right); }
  printf("]\n");
  return;
}


int main(int argc, char *argv[]){
  int have_coin;
  int command;
  srand(time(NULL));
  char *replay = "  replay  ";
  char string_buffer[100];
  char slot_machine_x[7][30] = 
  {"    7     ", " POKEMON  ", "  cherry  ", "moon_stone", " pikachu  ", "  replay  ",  "  replay  "};
  char slot_machine_y[10][30] = 
  {"    7     ", " POKEMON  ", "  cherry  ", "moon_stone", "moon_stone", " pikachu  ", " pikachu  ", "  replay  ", "  replay  ",  "  replay  "};
  char slot_machine_z[18][30] = 
  {"    7     ", " POKEMON  ", " POKEMON  ", "  cherry  ", "  cherry  ", "  cherry  ","moon_stone", "moon_stone", "moon_stone", " pikachu  ", " pikachu  ", " pikachu  ","  replay  ","  replay  ","  replay  ","  replay  ", "  replay  ",   "  replay  "};


  // betコインの入力があっているかどうか
  printf("Please change the language code UTF-8\n");
  if(argc != 2){
    printf("Error! <./a.out (bet_coin_number) > と入力してね！\n");
    return 1;
  }
  have_coin = atoi(argv[1]);
  if(have_coin <= 0){
    printf("Error! コインを入れてね！\n");
    return 2;
  }

  // slot実行
  while(1){
    // コインが最小枚数以下になった。
    if(have_coin < 3){
      printf("コインが足りなくなったので終了します。残り枚数は%d枚でした。\n", have_coin);
      return 0;
    }
    // 実行モード選択
    while(1){
      printf("Now coin = %d\n", have_coin);
      printf("1 = slot start!   5 = exit\n");
      printf("> ");  scanf("%s", string_buffer); 
      command = atoi(string_buffer);
      if(command >= 0 && command <= 9){
        break;
      }
      printf("Error! 入力は1桁の数字でお願いします\n");
      command = 0;
    }
    // 実行モード５:exit
    if(command == 5){
      printf("終了します。残りコインの枚数は%d枚でした。\n", have_coin);
      return 0;
    }
    // 実行モード１：スロット実行
    else if(command == 1){
      int i;
      int stop_slot;
      int stop_flag[3] = {0, 0, 0};
      char *left = NULL; 
      char *center = NULL;
      char *right = NULL;

      printf("\n3 Bet!\n");
REPLAY:
      for(i = 0; i < 3; i++){
        print_slot(left, center, right);
        printf("1 = left lane, 2 = center lane, 3 = right lane  (5 = exit)\n");
        printf("> ");  scanf("%d", &stop_slot);
        // スロットモード５：exit
        if(stop_slot == 5){
          printf("終了します。残りコインの枚数は%d枚でした。\n", have_coin);
          return 0;
        }
        // スロットモード１、２、３：レーンストップ
        if(stop_slot == 1){
          if(stop_flag[0] == 1){
            printf("Warning! 既にとめています\n"); 
            i--; 
            continue;
          }
          left = slot(1, slot_machine_x);
          printf("left stop!\n");
          stop_flag[0] = 1;
        }
        else if(stop_slot == 2){
          if(stop_flag[1] == 1){
            printf("Warning! 既にとめています\n\n"); 
            i--; 
            continue;
          }
          center = slot(2, slot_machine_y);
          printf("center stop!\n");
          stop_flag[1] = 1;
        }
        else if(stop_slot == 3){
          if(stop_flag[2] == 1){
            printf("Warning! 既にとめています\n"); 
            i--; 
            continue;
          }
          right = slot(3, slot_machine_z);
          printf("right stop!\n");
          stop_flag[2] = 1;
        }
        else{
          printf("Not correct number\n");
          i--;
          continue;
        }
        printf("Next:\n");
      }
      // 結果
      printf("\n");
      print_slot(left, center, right);
      printf("\n");
      // 役確認（replayだけ別作業）
      check_slot(left, center, right, &have_coin);
      if(strcmp(replay, left) == 0){
        if(strcmp(replay, center) == 0){
          if(strcmp(replay, right) == 0){
            printf("One More time!\n");
            stop_flag[0] = 0;
            stop_flag[1] = 0;
            stop_flag[2] = 0;
            left = NULL; 
            center = NULL;
            right = NULL;
            goto REPLAY;
          }
        }
      }
      
    }
    else{
      printf("そのモードは未実装です。ほかの数字を入力してください\n");
      continue;
    }
    have_coin -= 3; 
  }
  return 0;
}
