/* Copyright (C) 2017 Daniel Page <csdsp@bristol.ac.uk>
 *
 * Use of this source code is restricted per the CC BY-NC-ND license, a copy of 
 * which can be found via http://creativecommons.org (and should be included as 
 * LICENSE.txt within the associated archive or repository).
 */

#include "hilevel.h"
#include <stdio.h>
#include <string.h>
#include "SP804.h"
#include "draw.h"



// Initialise the process table
pcb_t procTab[ MAX_PROCS ]; pcb_t* executing = NULL;
pcb_t* prev_proc = NULL;
pipe_t pipeTab[MAX_PROCS * 2];        // Holds all created pipes
uint16_t fb[ 600 ][ 800 ];            // LCD array

int guiOn = 0;                  // global variable that controlls the gui


void show_gui(pcb_t pcb[MAX_PROCS]){
  gui_print(" \n");
  gui_print("            |-------|------------|-----------|\n");
  gui_print("            |  \e[1;44m PID \e[0m|\e[1;44m PRIORITY \e[0m  |\e[1;44m STATE \e[0m    |\n");
  gui_print("            |-------|------------|-----------|\n");
  gui_print("            |--------------------------------|\n");
  for(int i = 0; i < MAX_PROCS; i++){
    if (i > 9) {
      gui_print("            | ");
      printNum(pcb[i].pid);
      gui_print("       ");
      printNum(pcb[i].precedence);
      gui_print("      ");
    }
    else{ 
      gui_print("            |  ");
      printNum(pcb[i].pid);
      gui_print("       ");
      printNum(pcb[i].precedence);
      gui_print("      ");
    }

    if (pcb[i].status == STATUS_READY) {
        gui_print("\e[1;33m      READY   \e[0m");
        gui_print("|\n");
      }
    else if (pcb[i].status == STATUS_CREATED) {
        gui_print("\e[1;33m    CREATED \e[0m");
        gui_print("|\n");
      }
    else if (pcb[i].status == STATUS_TERMINATED || pcb[i].status ==  STATUS_EXIT) {
        gui_print("\e[1;33m    TERMINATED \e[0m");
        gui_print("|\n");
      }
    else if (pcb[i].status == STATUS_EXECUTING) {
        gui_print("\e[1;31m    EXECUTING \e[0m");
        gui_print("|\n");
      }
    
    }
    gui_print("            |--------------------------------|\n");
  }



void keyboardController(uint8_t x) {          // simple function that prints the corresponding pressed key on the keyboard to the gui

  char k = itox( ( x >> 4 ) & 0xF );
  switch (k)
  {
  case '1':
    if (itox( ( x >> 0 ) & 0xF ) == 'C') {
      draw_a(fb);
    }
    else if (itox( ( x >> 0 ) & 0xF ) == 'A') {
      draw_z(fb);
    }

    else if (itox( ( x >> 0 ) & 0xF ) == 'B') {
      draw_s(fb);
    }
    else if (itox( ( x >> 0 ) & 0xF ) == 'D') {
      draw_w(fb);
    }    
    else if (itox( ( x >> 0 ) & 0xF ) == '5') {
      draw_q(fb);
    }
    break;

  case '2':
    if (itox( ( x >> 0 ) & 0xF ) == '1') {
      draw_c(fb);
    }
    else if (itox( ( x >> 0 ) & 0xF ) == '2') {
      draw_gui(fb, MAX_PROCS, procTab);
    }
    else if (itox( ( x >> 0 ) & 0xF ) == '3') {
      draw_d(fb);
    }
    else if (itox( ( x >> 0 ) & 0xF ) == '4') {
      draw_e(fb);
    }
    else if (itox( ( x >> 0 ) & 0xF ) == 'A') {
      draw_v(fb);
    }
    else if (itox( ( x >> 0 ) & 0xF ) == 'B') {
      draw_f(fb);
    }
    else if (itox( ( x >> 0 ) & 0xF ) == 'C') {
      draw_tt(fb);
    }
    else if (itox( ( x >> 0 ) & 0xF ) == 'D') {
      draw_r(fb);
    }


    break;
  case '3':
    if (itox( ( x >> 0 ) & 0xF ) == '2') {
      draw_b(fb);
    }
    else if (itox( ( x >> 0 ) & 0xF ) == '1') {
      draw_n(fb);
    }
    else if (itox( ( x >> 0 ) & 0xF ) == '3') {
      draw_h(fb);
    }
    else if (itox( ( x >> 0 ) & 0xF ) == '4') {
      draw_g(fb);
    }
    else if (itox( ( x >> 0 ) & 0xF ) == '5') {
      draw_y(fb);
    }
    else if (itox( ( x >> 0 ) & 0xF ) == 'A') {
      draw_m(fb);
    }
    else if (itox( ( x >> 0 ) & 0xF ) == 'B') {
      draw_j(fb);
    }
    else if (itox( ( x >> 0 ) & 0xF ) == 'C') {
      draw_u(fb);
    }


    break;
  
  case '4':
    if (itox( ( x >> 0 ) & 0xF ) == '3') {
      draw_i(fb);
    }
    else if (itox( ( x >> 0 ) & 0xF ) == '2') {
      draw_k(fb);
    }
    else if (itox( ( x >> 0 ) & 0xF ) == '4') {
      draw_o(fb);
    }
    else if (itox( ( x >> 0 ) & 0xF ) == 'B') {
      draw_l(fb);
    }
    else if (itox( ( x >> 0 ) & 0xF ) == 'D') {
      draw_p(fb);
    }

    break;


  case 'F':
    if (itox( ( x >> 0 ) & 0xF ) == '0') {
      clear(fb);
    }
  
  default:
    break;
  }
}


pcb_t* make_child(pcb_t* parent, ctx_t* ctx) {
  // a function to create a new child process for fork. Returns null if no space is available in the PCB array
    pcb_t* child = NULL;
    for (int i = 0; i < MAX_PROCS; i++) {
        if (procTab[ i ].status == STATUS_TERMINATED || procTab[ i ].status == STATUS_EXIT) {
            child = &procTab[ i ];
            break;
        }
    }
    if (child == NULL) {return NULL;}

    uint32_t child_bos  = child->tos - STACK_SIZE;     // child  bottom of stack address
    uint32_t parent_bos = parent->tos - STACK_SIZE;    // parent bottom of stack address
    
    memcpy(&child->ctx, ctx, sizeof(ctx_t));       // copy parent context to child
    memcpy ((void *) child_bos, (void *) parent_bos, STACK_SIZE);             //clone parent stack
    uint32_t offset = parent->tos - (ctx->sp);              // calculate relative stack pointer position
    child->ctx.sp   = child->tos - offset;                    // set child stack pointer


    child->status = STATUS_CREATED;
    return child;

}


void dispatch (ctx_t* ctx, pcb_t* prev, pcb_t* next ) {
    char prev_pid = '?', next_pid = '?';
    if( NULL != prev ) {
      memcpy( &prev->ctx, ctx, sizeof( ctx_t ) ); // preserve execution context of P_{prev}
	    prev_pid = '0' + prev->pid;
      prev-> status = STATUS_READY;
      prev -> age = 0;
    }
    if( NULL != next ) {
      memcpy( ctx, &next->ctx, sizeof( ctx_t ) ); // restore  execution context of P_{next}
	    next_pid = '0' + next->pid;
      next->status = STATUS_EXECUTING;
    }
    if (prev == NULL && prev_proc != NULL) {
      prev_pid = '0' + prev_proc->pid;
    }
                            
	PL011_putc( UART0, '[',	true );
	PL011_putc( UART0, prev_pid,	true );
	PL011_putc( UART0, '-',	true );
	PL011_putc( UART0, '>',	true );
	PL011_putc( UART0, next_pid,	true );
	PL011_putc( UART0, ']',	true );

 	executing = next;    	// update   executing index   to P_{next}
  prev_proc = NULL;
  if (guiOn) {
      show_gui( procTab);       // refresh the gui every clock tick
    }
  return;
}


void schedule( ctx_t* ctx ) {
  /* 
  Scheduling Algorithm: Calculate a "score" for each process, with the formula
    score = precedence + age
  To change the weighting of precedence and/or age, simply multiply the precedence or age variable by a constant
  */

	pcb_t* prev = NULL;
  pcb_t* next = NULL;
  int maxscore = 0;
	for (int i = 0; i < MAX_PROCS; i++) {                               // Find and set currenctly executing task to previous
		if (procTab[ i ].status == STATUS_EXECUTING) {
      prev = &procTab[ i ];
      break;
		}
    }
    bool task_available = false;
    // Calculate a score for ready tasks and set the highest scoring task to next
    for (int i = 0; i < MAX_PROCS; i++) {
        if (procTab[ i ].status == STATUS_READY || procTab[ i ].status == STATUS_CREATED) {           
            int score = procTab[ i ].precedence + procTab[ i ].age; 
            if (score > maxscore) {
                maxscore = score;
                next = &procTab[ i ];
            }
            task_available = true;
        }
    }
    if (!task_available) {            // if there are no task available to be scheduled, re-schedule the previous task
        next = prev;
        next->age = 0;            
        dispatch(ctx, prev, next);
        return;
    }
    else {
        for (int i = 0; i < MAX_PROCS; i++) {   
          // Set the age of the next task to 0, and increase the age of all other tasks by 1.
          if (procTab[ i ].status != STATUS_TERMINATED && procTab[ i ].status != STATUS_EXIT && procTab[ i ].status != STATUS_WAITING) {                            
            if (procTab[ i ].pid == next->pid) {                      
                procTab[ i ].age = 0;
            }
            else { procTab[ i ].age ++;}
          }
        }
        dispatch(ctx,prev,next);    
        return;
    }

}

extern void	main_console();
extern uint32_t tos_console;
extern uint32_t tos_procs;


void hilevel_handler_rst(ctx_t* ctx) {
    // Indicate that a reset is being handled
    PL011_putc( UART0, '[', true );
    PL011_putc( UART0, 'R', true );
    PL011_putc( UART0, 'E', true );
    PL011_putc( UART0, 'S', true );
    PL011_putc( UART0, 'E', true );
    PL011_putc( UART0, 'T', true );
    PL011_putc( UART0, ']', true );


  SYSCONF->CLCD      = 0x2CAC;     // per per Table 4.3 of datasheet
  LCD->LCDTiming0    = 0x1313A4C4; // per per Table 4.3 of datasheet
  LCD->LCDTiming1    = 0x0505F657; // per per Table 4.3 of datasheet
  LCD->LCDTiming2    = 0x071F1800; // per per Table 4.3 of datasheet

  LCD->LCDUPBASE     = ( uint32_t )( &fb );

  LCD->LCDControl    = 0x00000020; // select TFT   display type
  LCD->LCDControl   |= 0x00000008; // select 16BPP display mode
  LCD->LCDControl   |= 0x00000800; // power-on LCD controller
  LCD->LCDControl   |= 0x00000001; // enable   LCD controller





  PS20->CR           = 0x00000010; // enable PS/2    (Rx) interrupt
  PS20->CR          |= 0x00000004; // enable PS/2 (Tx+Rx)
  PS21->CR           = 0x00000010; // enable PS/2    (Rx) interrupt
  PS21->CR          |= 0x00000004; // enable PS/2 (Tx+Rx)

  uint8_t ack;

        PL050_putc( PS20, 0xF4 );  // transmit PS/2 enable command
  ack = PL050_getc( PS20       );  // receive  PS/2 acknowledgement
        PL050_putc( PS21, 0xF4 );  // transmit PS/2 enable command
  ack = PL050_getc( PS21       );  // receive  PS/2 acknowledgement

  GICC0->PMR         = 0x000000F0; // unmask all          interrupts
  GICD0->ISENABLER1 |= 0x00300000; // enable PS2          interrupts
  GICC0->CTLR        = 0x00000001; // enable GIC interface
  GICD0->CTLR        = 0x00000001; // enable GIC distributor










    // Invalidate the entries in the process table
    for (int i = 0; i < MAX_PROCS; i++) {
        procTab[i].status = STATUS_INVALID;
    }
    
    memset( &procTab[ 0 ], 0, sizeof( pcb_t ) ); // initialise 0-th PCB = console
    procTab[ 0 ].pid      = 0;
    procTab[ 0 ].status   = STATUS_READY;
    procTab[ 0 ].tos      = ( uint32_t )( &tos_console  );
    procTab[ 0 ].ctx.cpsr = 0x50;
    procTab[ 0 ].ctx.pc   = ( uint32_t )( &main_console );
    procTab[ 0 ].ctx.sp   = procTab[ 0 ].tos;
    procTab[ 0 ].precedence = 2;
    procTab[ 0 ].age = 0;

   for (int i = 1; i < MAX_PROCS; i++) {                 // allocate space for all other user processes.       
       memset( &procTab[ i ], 0, sizeof( pcb_t ) ); 
        procTab[ i ].pid      = i;
        procTab[ i ].status   = STATUS_TERMINATED;
        procTab[ i ].tos      = ( uint32_t )( &tos_procs ) - ((i-1) * 0x00001000);
        procTab[ i ].ctx.cpsr = 0x50;
        procTab[ i ].ctx.sp   = procTab[ i ].tos;
        procTab[ i ].precedence = 1;
        procTab[ i ].age = 0;

   }

   for (int i = 0; i < MAX_PROCS * 2; i++) {        // initialise pipe array
     memset( &pipeTab[ i ], 0, sizeof( pipe_t) );
     pipeTab[ i ].data = -99;
     pipeTab[ i ].available = 1;
     pipeTab[ i ].written = 0;

   }
    
  dispatch(ctx, NULL, &procTab[0]);

  TIMER0->Timer1Load  = 0x00010000; // select period = 2^20 ticks ~= 1 sec
  TIMER0->Timer1Ctrl  = 0x00000002; // select 32-bit   timer
  TIMER0->Timer1Ctrl |= 0x00000040; // select periodic timer
  TIMER0->Timer1Ctrl |= 0x00000020; // enable          timer interrupt
  TIMER0->Timer1Ctrl |= 0x00000080; // enable          timer

  GICC0->PMR          = 0x000000F0; // unmask all            interrupts
  GICD0->ISENABLER1  |= 0x00000010; // enable timer          interrupt
  GICC0->CTLR         = 0x00000001; // enable GIC interface
  GICD0->CTLR         = 0x00000001; // enable GIC distributor

  int_enable_irq();
    


  for( int i = 0; i < 600; i++ ) {      // initialise the screen
    for( int j = 0; j < 800; j++ ) {
      fb[ i ][ j ] = 0x0000;
    }
  }
 
  return;
}

void hilevel_handler_svc( ctx_t* ctx, uint32_t id ) { 
  /* Based on the identifier (i.e., the immediate operand) extracted from the
   * svc instruction, 
   *
   * - read  the arguments from preserved usr mode registers,
   * - perform whatever is appropriate for this system call, then
   * - write any return value back to preserved usr mode registers.
   */

  switch( id ) {
    case 0x00 : { // 0x00 => yield()
      schedule( ctx );

      break;
    }

    case 0x01 : { // 0x01 => write( fd, x, n )
      int   fd = ( int   )( ctx->gpr[ 0 ] );  
      char*  x = ( char* )( ctx->gpr[ 1 ] );  
      int    n = ( int   )( ctx->gpr[ 2 ] ); 

      for( int i = 0; i < n; i++ ) {
        PL011_putc( UART0, *x++, true );
      }
      
      ctx->gpr[ 0 ] = n;

      break;
    }

    case 0x03 : {  // 0x03 => fork()
        pcb_t* child = make_child(executing, ctx);
        if (child == NULL) {                        // No available empty PCB's. Return -1

            ctx->gpr[ 0 ] = -1;     
            break;
        }
        ctx->gpr[ 0 ] = child->pid;
        child->ctx.gpr[ 0 ] = 0;
        procTab[ 0 ].precedence++;
        break;
    }

    case 0x04 : {   // 0x04 => exit(x)

        prev_proc = executing;
        executing->status = STATUS_EXIT;
        executing->age = 0;
        schedule(ctx);
        procTab[ 0 ].precedence --;
        break;        

    }

    case 0x05: {    // 0x05 => exec(x)

        const void* x = (const void*) (ctx->gpr[ 0 ]);
        ctx->pc = (const void*) x;
        break;

    }

    case 0x06: {    // 0x06 => kill(pid, x)
     
        int pid = ( int ) ctx->gpr[ 0 ];
        int x   = ( int ) ctx->gpr[ 1 ];
        for (int i = 0; i < MAX_PROCS; i++) {
            if (procTab[ i ].pid == pid) {
                procTab[ i ].status = STATUS_TERMINATED;
                procTab[ i ].age = 0;
                procTab [ 0 ].precedence--; 
                ctx->gpr[ 0 ] = 0;
                break;
            }
            else {
              ctx->gpr[ 0 ] = -1;
            }
        }
        break;
    }
    
    case 0x08: {        // 0x08 => pipe(fd[2])

      int *fds = ctx->gpr[0];
      //int rd = fd[0];
      //int wr = fd[1];

      for (int i = 0; i < MAX_PROCS * 2; i++) {
        if ( pipeTab[ i ].available ) {
          pipeTab[ i ].available = 0;
          fds[0] = i;
          fds[1] = i;
          break;
            
        }
      }
      break;
    }

    case 0x09: {        // 0x09 => pipe_write(fd, data)
     
      int fd   = (int) ctx->gpr[ 0 ];
      int data = (int) ctx->gpr[ 1 ];
      if (pipeTab[fd].available) {
        ctx->gpr[ 0 ] = -1;
        break;
      }
      if (pipeTab[fd].written) {
        ctx->gpr[ 0 ] = -2;
        break;
      }
      pipeTab[fd].data = data;
      if (data != -2) {
        pipeTab[fd].written = 1;
      }
      break;
    }

    case 0x10: {        // 0x10 => pipe_read(fd)

      int fd    = (int) ctx->gpr[ 0 ];
      int clear = (int) ctx->gpr[ 1 ];
      int data;

      if (pipeTab[fd].available) {
        ctx->gpr[ 0 ] = -1;
        break;
      }
      if (!pipeTab[fd].written) {
        ctx->gpr[ 0 ] = -2;
        break;
      }
      data = pipeTab[fd].data;
      ctx->gpr[ 0 ] = data;
      if (clear) {
        pipeTab[fd].written = 0;
      }
      break;
    }


    case 0x12: {      // 0x12 => suspend()
        executing->status = STATUS_WAITING;
        schedule(ctx);
        procTab[ 0 ].precedence --;
        break;    
    }
    

    case 0x13: {    // 0x12 => restart()
      int pid = ctx->gpr[ 0 ];
      for (int i = 0; i < MAX_PROCS; i++) {
        if (procTab[ i ].pid == pid && procTab[ i ].status == STATUS_WAITING) {
          procTab[ i ].status = STATUS_READY;
          procTab[0].precedence ++;
        }
      }
    }

    case 0x14: {      //0x13 => setPrio(pid, prio)
      int pid  = ctx->gpr[ 0 ];
      int prio = ctx->gpr[ 1 ];   
      for (int i = 0; i < MAX_PROCS; i++) {
        if (procTab[ i ].pid == pid) { procTab[ i ].precedence = prio;}
      }
    }

    case 0x15 :{ // gui_on()
          guiOn = 1;
          show_gui(procTab);
          break;
    }

    case 0x16 :{ // gui_off();
          guiOn = 0;
          break;
    }

    default   : { // 0x?? => unknown/unsupported
      break;
    }
  }



  return;
}
void hilevel_handler_irq(ctx_t* ctx) {
  // Step 2: read  the interrupt identifier so we know the source.

  uint32_t id = GICC0->IAR;

  // Step 4: handle the interrupt, then clear (or reset) the source.

  if( id == GIC_SOURCE_TIMER0 ) {
    PL011_putc( UART0, '[', true ); TIMER0->Timer1IntClr = 0x01;
    PL011_putc( UART0, 'T', true ); TIMER0->Timer1IntClr = 0x01;
    PL011_putc( UART0, 'I', true ); TIMER0->Timer1IntClr = 0x01;
    PL011_putc( UART0, 'M', true ); TIMER0->Timer1IntClr = 0x01;
    PL011_putc( UART0, 'E', true ); TIMER0->Timer1IntClr = 0x01;
    PL011_putc( UART0, 'R', true ); TIMER0->Timer1IntClr = 0x01;
    PL011_putc( UART0, ']', true ); TIMER0->Timer1IntClr = 0x01;
    schedule( ctx );
  }

  else if     ( id == GIC_SOURCE_PS20 ) {
    uint8_t x = PL050_getc( PS20 );
    keyboardController(x);





    PL011_putc( UART0, '0',                      true );  
    PL011_putc( UART0, '<',                      true ); 
    PL011_putc( UART0, itox( ( x >> 4 ) & 0xF ), true ); 
    PL011_putc( UART0, itox( ( x >> 0 ) & 0xF ), true ); 
    PL011_putc( UART0, '>',                      true ); 
  }
  /*else if( id == GIC_SOURCE_PS21 ) {
    uint8_t x = PL050_getc( PS21 );

    PL011_putc( UART0, '1',                      true );  
    PL011_putc( UART0, '<',                      true ); 
    PL011_putc( UART0, itox( ( x >> 4 ) & 0xF ), true ); 
    PL011_putc( UART0, itox( ( x >> 0 ) & 0xF ), true ); 
    PL011_putc( UART0, '>',                      true ); \
    
  }*/

  // Step 5: write the interrupt identifier to signal we're done.

  GICC0->EOIR = id;

  return;
}
