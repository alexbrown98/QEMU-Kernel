#include "draw.h"


typedef int pid_t;
typedef struct {
  uint32_t cpsr, pc, gpr[ 13 ], sp, lr;
} ctx_t;
typedef enum {
  STATUS_CREATED,
  STATUS_READY,
  STATUS_INVALID,
  STATUS_EXECUTING,
  STATUS_WAITING,
  STATUS_TERMINATED,
  STATUS_EXIT
} status_t;
typedef struct {
     pid_t    pid;
  status_t status;
     ctx_t    ctx;
     uint32_t tos;
     int precedence;
     int age;
} pcb_t;

void draw_top(uint16_t fb[600][800]) {
    for (int i = 50; i < 55; i++ ) {
      if (i == 50) { 
        for (int j = 205; j < 545; j++) {       //top
            fb[i][j] = 0x0FFF;
        }
      }
      else if (i == 51) {
          for (int j = 206; j < 544; j++) {       
            fb[i][j] = 0x0FFF;
        }
      }

      else if (i == 52) {
          for (int j = 207; j < 543; j++) {       
            fb[i][j] = 0x0FFF;
        }
      }

      else if (i == 53) {
          for (int j = 208; j < 542; j++) {       
            fb[i][j] = 0x0FFF;
        }
      }

      else if (i == 54) {
          for (int j = 209; j < 541; j++) {       
            fb[i][j] = 0x0FFF;
        }
      }
  }
}

void draw_top1(uint16_t fb[600][800]){
    for (int i = 50; i < 55; i++ ) {
      if (i == 50) { 
        for (int j = 205; j < 375; j++) {       //top
            fb[i][j] = 0x0FFF;
        }
      }
      else if (i == 51) {
          for (int j = 206; j < 375; j++) {       
            fb[i][j] = 0x0FFF;
        }
      }

      else if (i == 52) {
          for (int j = 207; j < 373; j++) {       
            fb[i][j] = 0x0FFF;
        }
      }

      else if (i == 53) {
          for (int j = 208; j < 372; j++) {       
            fb[i][j] = 0x0FFF;
        }
      }

      else if (i == 54) {
          for (int j = 209; j < 371; j++) {       
            fb[i][j] = 0x0FFF;
        }
      }
  }
}

void draw_top2(uint16_t fb[600][800]){
  for (int i = 50; i < 55; i++ ) {
      if (i == 50) { 
        for (int j = 380; j < 545; j++) {       //top
            fb[i][j] = 0x0FFF;
        }
      }
      else if (i == 51) {
          for (int j = 381; j < 544; j++) {       
            fb[i][j] = 0x0FFF;
        }
      }

      else if (i == 52) {
          for (int j = 382; j < 543; j++) {       
            fb[i][j] = 0x0FFF;
        }
      }

      else if (i == 53) {
          for (int j = 383; j < 542; j++) {       
            fb[i][j] = 0x0FFF;
        }
      }

      else if (i == 54) {
          for (int j = 384; j < 541; j++) {       
            fb[i][j] = 0x0FFF;
        }
      }
  }
}

void draw_bot1(uint16_t fb[600][800]){
    for (int i = 550; i < 555; i++ ) {
      if (i == 550) { 
        for (int j = 205; j < 375; j++) {       //top
            fb[i][j] = 0x0FFF;
        }
      }
      else if (i == 551) {
          for (int j = 206; j < 375; j++) {       
            fb[i][j] = 0x0FFF;
        }
      }

      else if (i == 552) {
          for (int j = 207; j < 373; j++) {       
            fb[i][j] = 0x0FFF;
        }
      }

      else if (i == 553) {
          for (int j = 208; j < 372; j++) {       
            fb[i][j] = 0x0FFF;
        }
      }

      else if (i == 554) {
          for (int j = 209; j < 371; j++) {       
            fb[i][j] = 0x0FFF;
        }
      }
  }
}

void draw_bot2(uint16_t fb[600][800]){
  for (int i = 550; i < 555; i++ ) {
      if (i == 550) { 
        for (int j = 380; j < 545; j++) {       //top
            fb[i][j] = 0x0FFF;
        }
      }
      else if (i == 551) {
          for (int j = 381; j < 544; j++) {       
            fb[i][j] = 0x0FFF;
        }
      }

      else if (i == 552) {
          for (int j = 382; j < 543; j++) {       
            fb[i][j] = 0x0FFF;
        }
      }

      else if (i == 553) {
          for (int j = 383; j < 542; j++) {       
            fb[i][j] = 0x0FFF;
        }
      }

      else if (i == 554) {
          for (int j = 384; j < 541; j++) {       
            fb[i][j] = 0x0FFF;
        }
      }
  }
}

void draw_mid(uint16_t fb[600][800]) {
  for (int i = 300; i < 305; i++ ) {        //middle
          if (i == 300) { 
        for (int j = 205; j < 545; j++) {       
            fb[i][j] = 0x0FFF;
        }
      }
      else if (i == 301) {
          for (int j = 206; j < 544; j++) {       
            fb[i][j] = 0x0FFF;
        }
      }

      else if (i == 302) {
          for (int j = 207; j < 543; j++) {       
            fb[i][j] = 0x0FFF;
        }
      }

      else if (i == 303) {
          for (int j = 208; j < 542; j++) {       
            fb[i][j] = 0x0FFF;
        }
      }

      else if (i == 304) {
          for (int j = 209; j < 541; j++) {       
            fb[i][j] = 0x0FFF;
        }
      }
  }
}

void draw_bot(uint16_t fb[600][800]) {
    for (int i = 550; i < 555; i++ ) {        //bottom
    if (i == 550) {
      for (int j = 200; j < 550; j++) {
      fb[i][j] = 0x0FFF;
      }
    }
    else if (i == 551) {
      for (int j = 201; j < 549; j++) {
      fb[i][j] = 0x0FFF;
    }}
    else if (i == 552) {
      for (int j = 202; j < 548; j++) {
      fb[i][j] = 0x0FFF;
    }}
    else if (i == 553) {
      for (int j = 203; j < 547; j++) {
      fb[i][j] = 0x0FFF;
    }}
    else if (i == 554) {
      for (int j = 204; j < 546; j++) {
      fb[i][j] = 0x0FFF;
    }}


  }  
}

void draw_l1(uint16_t fb[600][800]) {
  for (int j = 195; j < 200; j++) {   // left 1

    if (j == 195) {
      for (int i = 65; i < 290; i++) {
        fb[i][j] = 0x0FFF;
      }
    }

    else if (j == 196) {
      for (int i = 62; i < 292; i++) {
        fb[i][j] = 0x0FFF;
      }
    }

    else if (j == 197) {
      for (int i = 60; i < 295; i++) {
        fb[i][j] = 0x0FFF;
      }
    }
    else if (j == 198) {
      for (int i = 62; i < 292; i++) {
        fb[i][j] = 0x0FFF;
      }
    }
    else if (j == 199) {
      for (int i = 65; i < 290; i++) {
        fb[i][j] = 0x0FFF;
      }
    }
  }
}

void draw_l2(uint16_t fb[600][800]) {
  for (int j = 195; j < 200; j++) {   // left 2

    if (j == 195) {
      for (int i = 310; i < 540; i++) {
        fb[i][j] = 0x0FFF;
      }
    }

    else if (j == 196) {
      for (int i = 307; i < 542; i++) {
        fb[i][j] = 0x0FFF;
      }
    }

    else if (j == 197) {
      for (int i = 305; i < 545; i++) {
        fb[i][j] = 0x0FFF;
      }
    }
    else if (j == 198) {
      for (int i = 307; i < 542; i++) {
        fb[i][j] = 0x0FFF;
      }
    }
    else if (j == 199) {
      for (int i = 310; i < 540; i++) {
        fb[i][j] = 0x0FFF;
      }
    }
  }
}

void draw_c1(uint16_t fb[600][800]) {
  for (int j = 375; j < 380; j++) {   // left 1

    if (j == 375) {
      for (int i = 65; i < 290; i++) {
        fb[i][j] = 0x0FFF;
      }
    }

    else if (j == 376) {
      for (int i = 62; i < 292; i++) {
        fb[i][j] = 0x0FFF;
      }
    }

    else if (j == 377) {
      for (int i = 60; i < 295; i++) {
        fb[i][j] = 0x0FFF;
      }
    }
    else if (j == 378) {
      for (int i = 62; i < 292; i++) {
        fb[i][j] = 0x0FFF;
      }
    }
    else if (j == 379) {
      for (int i = 65; i < 290; i++) {
        fb[i][j] = 0x0FFF;
      }
    }
  }
}

void draw_c2(uint16_t fb[600][800]) {
  for (int j = 375; j < 380; j++) {   

    if (j == 375) {
      for (int i = 310; i < 540; i++) {
        fb[i][j] = 0x0FFF;
      }
    }

    else if (j == 376) {
      for (int i = 307; i < 542; i++) {
        fb[i][j] = 0x0FFF;
      }
    }

    else if (j == 377) {
      for (int i = 305; i < 545; i++) {
        fb[i][j] = 0x0FFF;
      }
    }
    else if (j == 378) {
      for (int i = 307; i < 542; i++) {
        fb[i][j] = 0x0FFF;
      }
    }
    else if (j == 379) {
      for (int i = 310; i < 540; i++) {
        fb[i][j] = 0x0FFF;
      }
    }
  }
}

void draw_r1(uint16_t fb[600][800]) {
  for (int j = 550; j < 555; j++) {   // right 1

    if (j == 550) {
      for (int i = 65; i < 290; i++) {
        fb[i][j] = 0x0FFF;
      }
    }

    else if (j == 551) {
      for (int i = 62; i < 292; i++) {
        fb[i][j] = 0x0FFF;
      }
    }

    else if (j == 552) {
      for (int i = 60; i < 295; i++) {
        fb[i][j] = 0x0FFF;
      }
    }
    else if (j == 553) {
      for (int i = 62; i < 292; i++) {
        fb[i][j] = 0x0FFF;
      }
    }
    else if (j == 554) {
      for (int i = 65; i < 290; i++) {
        fb[i][j] = 0x0FFF;
      }
    }
  }
}

void draw_r2(uint16_t fb[600][800]) {

  for (int j = 550; j < 555; j++) {   // right 2

    if (j == 550) {
      for (int i = 310; i < 540; i++) {
        fb[i][j] = 0x0FFF;
      }
    }

    else if (j == 551) {
      for (int i = 307; i < 542; i++) {
        fb[i][j] = 0x0FFF;
      }
    }

    else if (j == 552) {
      for (int i = 305; i < 545; i++) {
        fb[i][j] = 0x0FFF;
      }
    }
    else if (j == 553) {
      for (int i = 307; i < 542; i++) {
        fb[i][j] = 0x0FFF;
      }
    }
    else if (j == 554) {
      for (int i = 310; i < 540; i++) {
        fb[i][j] = 0x0FFF;
      }
    }
  }
}

void clear(uint16_t fb[600][800]) {
  for( int i = 0; i < 600; i++ ) {
    for( int j = 0; j < 800; j++ ) {
      fb[ i ][ j ] = 0x0000;
    }
  }
}

void draw_a(uint16_t fb[600][800]) {
  draw_l2(fb);
  draw_l1(fb);
  draw_top(fb);
  draw_mid(fb);
  draw_r1(fb);
  draw_r2(fb);
}

void draw_b( uint16_t fb[600][800]) {
  draw_l2(fb);
  draw_l1(fb);
  draw_top(fb);
  draw_mid(fb);
  draw_bot(fb);
  draw_r1(fb);
  draw_r2(fb);
}

void draw_c( uint16_t fb[600][800]) {
  draw_l2(fb);
  draw_l1(fb);
  draw_top(fb);
  draw_bot(fb);
}

void draw_d( uint16_t fb[600][800]) {
  draw_l2(fb);
  draw_l1(fb);
  draw_top(fb);
  draw_bot(fb);
  draw_r1(fb);
  draw_r2(fb);
}

void draw_e( uint16_t fb[600][800]) {
  draw_l2(fb);
  draw_l1(fb);
  draw_top(fb);
  draw_mid(fb);
  draw_bot(fb);

}

void draw_f( uint16_t fb[600][800]) {
  draw_l2(fb);
  draw_l1(fb);
  draw_top(fb);
  draw_mid(fb);

}

void draw_g( uint16_t fb[600][800]) {
  draw_l2(fb);
  draw_l1(fb);
  draw_top(fb);
  draw_mid(fb);
  draw_bot(fb);
  draw_r2(fb);
}

void draw_h( uint16_t fb[600][800]) {
  draw_l2(fb);
  draw_l1(fb);
  draw_mid(fb);
  draw_r1(fb);
  draw_r2(fb);
}

void draw_i( uint16_t fb[600][800]) {
  draw_c1(fb);
  draw_c2(fb);
}

void draw_j( uint16_t fb[600][800]) {
  draw_l2(fb);
  draw_bot(fb);
  draw_r2(fb);
  draw_r1(fb);
}

void draw_k( uint16_t fb[600][800]) {
  draw_l2(fb);
  draw_l1(fb);
  draw_mid(fb);
  draw_r2(fb);
  draw_r1(fb);

}

void draw_l( uint16_t fb[600][800]) {
  draw_l2(fb);
  draw_l1(fb);
  draw_bot(fb);
}

void draw_m( uint16_t fb[600][800]) {
  draw_l2(fb);
  draw_l1(fb);
  draw_top(fb);
  draw_c1(fb);
  draw_r2(fb);
  draw_r1(fb);
}

void draw_n( uint16_t fb[600][800]) {
  draw_l2(fb);
  draw_l1(fb);
  draw_top1(fb);
  draw_c1(fb);
  draw_c2(fb);
  draw_bot2(fb);
  draw_r2(fb);
  draw_r1(fb);
}

void draw_o( uint16_t fb[600][800]) {
  draw_l2(fb);
  draw_l1(fb);
  draw_top(fb);
  draw_bot(fb);
  draw_r1(fb);
  draw_r2(fb);
}

void draw_p( uint16_t fb[600][800]) {
  draw_l2(fb);
  draw_l1(fb);
  draw_top(fb);
  draw_mid(fb);
  draw_r1(fb);
}

void draw_q( uint16_t fb[600][800]) {
  draw_l2(fb);
  draw_l1(fb);
  draw_top(fb);
  draw_bot(fb);
  draw_r1(fb);
  draw_r2(fb);
}

void draw_r( uint16_t fb[600][800]) {
  draw_l2(fb);
  draw_l1(fb);
  draw_top(fb);
  draw_mid(fb);
  draw_r1(fb);
  draw_r2(fb);
}

void draw_s( uint16_t fb[600][800]) {
  draw_l1(fb);
  draw_top(fb);
  draw_mid(fb);
  draw_bot(fb);
  draw_r2(fb);
}

void draw_tt( uint16_t fb[600][800]) {
  draw_top1(fb);
  draw_top2(fb);
  draw_c1(fb);
  draw_c2(fb);
}

void draw_u( uint16_t fb[600][800]) {
  draw_l2(fb);
  draw_l1(fb);
  draw_bot(fb);
  draw_r1(fb);
  draw_r2(fb);
}

void draw_v( uint16_t fb[600][800]) {
  draw_l2(fb);
  draw_l1(fb);
  draw_bot(fb);
  draw_r1(fb);
  draw_r2(fb);
}

void draw_w( uint16_t fb[600][800]) {
  draw_l2(fb);
  draw_l1(fb);
  draw_bot1(fb);
  draw_bot2(fb);
  draw_c2(fb);
  draw_r1(fb);
  draw_r2(fb);
}

void draw_x( uint16_t fb[600][800]) {

}

void draw_y( uint16_t fb[600][800]) {
  draw_l1(fb);
  draw_mid(fb);
  draw_r1(fb);
  draw_r2(fb);
  draw_bot(fb);
}

void draw_z( uint16_t fb[600][800]) {

}

void draw_line_vert(int ya, int yb, int x, int thickness, uint16_t fb[600][800]) {
  for (int i = ya; i < yb; i++) {
    for (int j = x; j < x+thickness; j++) {
      fb[i][j] = 0x0FFF;
    }
  }
}

void draw_line_horiz(int xa, int xb, int y, int thickness, uint16_t fb[600][800]) {
  for (int i = y; i < y+thickness; i++) {
    for (int j = xa; j < xb; j++) {
      fb[i][j] = 0x0FFF;
    }
  }
}

void draw_box(uint16_t fb[600][800], int xa, int xb, int ya, int yb, int t) {
  draw_line_vert(xa,xb,ya,t,fb);
  draw_line_horiz(ya,yb,xa,t,fb);
  draw_line_horiz(ya,yb,xb,t,fb);
  draw_line_vert(xa,xb+t,yb,t,fb);
}

void draw_1(uint16_t fb[600][800], int y, int x) {
  fb[y][x] = 0x0FFF;
  fb[y+1][x] = 0x0FFF;
  fb[y+2][x] = 0x0FFF;
  fb[y+3][x] = 0x0FFF;

}

void draw_2(uint16_t fb[600][800], int y, int x) {
  fb[y][x] = 0x0FFF;
  fb[y][x+1] = 0x0FFF;
  fb[y][x+2] = 0x0FFF;
  fb[y][x+3] = 0x0FFF;
  fb[y+1][x+3] = 0x0FFF;
  fb[y+2][x+3] = 0x0FFF;
  fb[y+3][x+3] = 0x0FFF;
  fb[y+3][x+2] = 0x0FFF;
  fb[y+3][x+1] = 0x0FFF;
  fb[y+3][x] = 0x0FFF;
  fb[y+4][x] = 0x0FFF;
  fb[y+5][x] = 0x0FFF;
  fb[y+6][x] = 0x0FFF;
  fb[y+6][x+1] = 0x0FFF;
  fb[y+6][x+2] = 0x0FFF;
  fb[y+6][x+3] = 0x0FFF;

}

void draw_3(uint16_t fb[600][800], int y, int x) {  
  fb[y][x] = 0x0FFF;
  fb[y][x+1] = 0x0FFF;
  fb[y][x+2] = 0x0FFF;
  fb[y][x+3] = 0x0FFF;
  fb[y+1][x+3] = 0x0FFF;
  fb[y+2][x+3] = 0x0FFF;
  fb[y+3][x+3] = 0x0FFF;
  fb[y+3][x+2] = 0x0FFF;
  fb[y+3][x+1] = 0x0FFF;
  fb[y+3][x] = 0x0FFF;
  fb[y+4][x+3] = 0x0FFF;
  fb[y+5][x+3] = 0x0FFF;
  fb[y+6][x+3] = 0x0FFF;
  fb[y+6][x+2] = 0x0FFF;
  fb[y+6][x+1] = 0x0FFF;
  fb[y+6][x] = 0x0FFF;
}


void draw_4(uint16_t fb[600][800], int y, int x) {  
  fb[y][x] = 0x0FFF;
  fb[y+1][x] = 0x0FFF;
  fb[y+2][x] = 0x0FFF;
  fb[y+3][x] = 0x0FFF;
  fb[y+3][x+1] = 0x0FFF;
  fb[y+3][x+2] = 0x0FFF;
  fb[y+3][x+3] = 0x0FFF;
  fb[y+2][x+2] = 0x0FFF;
  fb[y+4][x+2] = 0x0FFF;

}

void draw_5(uint16_t fb[600][800],int y, int x) {  
  fb[y][x] = 0x0FFF;
  fb[y][x+1] = 0x0FFF;
  fb[y][x+2] = 0x0FFF;
  fb[y][x+3] = 0x0FFF;
  fb[y+1][x] = 0x0FFF;
  fb[y+2][x] = 0x0FFF;
  fb[y+3][x] = 0x0FFF;
  fb[y+3][x+1] = 0x0FFF;
  fb[y+3][x+2] = 0x0FFF;
  fb[y+3][x+3] = 0x0FFF;
  fb[y+4][x+3] = 0x0FFF;
  fb[y+5][x+3] = 0x0FFF;
  fb[y+6][x+3] = 0x0FFF;
  fb[y+6][x+2] = 0x0FFF;
  fb[y+6][x+1] = 0x0FFF;
  fb[y+6][x] = 0x0FFF;

}

void draw_6(uint16_t fb[600][800], int y, int x) {  
  fb[y][x] = 0x0FFF;
  fb[y][x+1] = 0x0FFF;
  fb[y][x+2] = 0x0FFF;
  fb[y][x+3] = 0x0FFF;
  fb[y+1][x] = 0x0FFF;
  fb[y+2][x] = 0x0FFF;
  fb[y+3][x] = 0x0FFF;
  fb[y+3][x+1] = 0x0FFF;
  fb[y+3][x+2] = 0x0FFF;
  fb[y+3][x+3] = 0x0FFF;
  fb[y+2][x+3] = 0x0FFF;
  fb[y+1][x+3] = 0x0FFF;
  fb[y+1][x+2] = 0x0FFF;
  fb[y+1][x+1] = 0x0FFF;

}

void draw_7(uint16_t fb[600][800], int y, int x) {  
  fb[y][x] = 0x0FFF;
  fb[y][x+1] = 0x0FFF;
  fb[y][x+2] = 0x0FFF;
  fb[y][x+3] = 0x0FFF;
  fb[y+1][x+3] = 0x0FFF;
  fb[y+2][x+3] = 0x0FFF;
  fb[y+3][x+3] = 0x0FFF;

}

void draw_8(uint16_t fb[600][800], int y, int x) {  
  fb[y][x] = 0x0FFF;
  fb[y][x+1] = 0x0FFF;
  fb[y][x+2] = 0x0FFF;
  fb[y][x+3] = 0x0FFF;
  fb[y+1][x+3] = 0x0FFF;
  fb[y+2][x+3] = 0x0FFF;
  fb[y+3][x+3] = 0x0FFF;
  fb[y+1][x] = 0x0FFF;
  fb[y+2][x] = 0x0FFF;
  fb[y+3][x] = 0x0FFF;
  fb[y+3][x+1] = 0x0FFF;
  fb[y+3][x+2 ] = 0x0FFF;

}

void draw_9(uint16_t fb[600][800], int y, int x) {  
  fb[y][x] = 0x0FFF;
  fb[y][x+1] = 0x0FFF;
  fb[y][x+2] = 0x0FFF;
  fb[y][x+3] = 0x0FFF;
  fb[y+1][x] = 0x0FFF;
  fb[y+1][x+1] = 0x0FFF;
  fb[y+1][x+2] = 0x0FFF;
  fb[y+1][x+3] = 0x0FFF;
  fb[y+2][x+3] = 0x0FFF;
  fb[y+3][x+3] = 0x0FFF;
  fb[y+2][x+3] = 0x0FFF;
  fb[y+1][x+3] = 0x0FFF;
  fb[y][x+3] = 0x0FFF;

}









void draw_gui(uint16_t fb[600][800], int max, pcb_t procTab[max]) {
  for (int i = 0; i < max; i++) {
    draw_box(fb,50*i,50*i + 20, 100, 300,2);
    int pid = procTab[i].pid;

    if (pid == 1) {
      draw_1(fb,50*i +5, 200);
    }
    else if (pid == 2) {
      draw_2(fb, 50*i +5, 200);

    }
    else if (pid == 3) {
      draw_3(fb, 50*i +5, 200);
    }
    else if (pid == 4) {
      draw_4(fb, 50*i +5, 200);
    }
    else if (pid == 5) {
      draw_5(fb, 50*i +5, 200);
    }
    else if (pid == 6) {
      draw_6(fb, 50*i +5, 200);
    }
    else if (pid == 7) {
      draw_7(fb, 50*i +5, 200);
    }
    else if (pid == 8) {
      draw_8(fb, 50*i +5, 200);
    }
    else if (pid == 9) {
      draw_9(fb, 50*i +5, 200);
    }

  }
 }
 




 

