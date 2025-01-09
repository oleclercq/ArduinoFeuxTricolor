#include "assigne.h"


void normal();
void cligno_orange(bool mode);
void cligno();
void flipLed();
void test_rouge(int tempo);
void test_jaune(int tempo);

#define EACH_DEMI_SECONDE (50) // 5ms * 100 = 500ms

enum MODE { VERT1, ORANGE1, ROUGE1, TEMPOROUGE1, VERT2, ORANGE2, ROUGE2, TEMPOROUGE2};
enum MODE mode = VERT1;

struct ST_FEU { unsigned char ledRouge;

                unsigned char ledOrange;

                unsigned char ledVert;};

struct ST_FEU tabTeu[NB_FEU] = {  ROUGE_1, ORANGE_1, VERT_1,
                                  ROUGE_2, ORANGE_2, VERT_2,
                                  ROUGE_3, ORANGE_3, VERT_3,
                                  ROUGE_4, ORANGE_4, VERT_4,
                                  ROUGE_5, ORANGE_5, VERT_5,
                                  ROUGE_6, ORANGE_6, VERT_6,
                                  ROUGE_7, ORANGE_7, VERT_7,
                                  ROUGE_8, ORANGE_8, VERT_8,
                                  ROUGE_9, ORANGE_9, VERT_9,
                                  ROUGE_10, ORANGE_10, VERT_10,
                                  ROUGE_11, ORANGE_11, VERT_12,
                                  ROUGE_12, ORANGE_12, VERT_12,
                                
                                  };



void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);

for (int i=0 ; i<NB_FEU ; i++){
  pinMode(tabTeu[i].ledRouge,  OUTPUT);
  pinMode(tabTeu[i].ledOrange, OUTPUT);
  pinMode(tabTeu[i].ledVert,   OUTPUT);
}

for (int i=0 ; i<NB_FEU ; i++){
  digitalWrite(tabTeu[i].ledRouge,  OFF);
  digitalWrite(tabTeu[i].ledOrange, OFF);
  digitalWrite(tabTeu[i].ledVert,   OFF);
}


  // ================================================================================
// TIMER 1 16BIT
    cli();
    TCCR1A = 0;
    TCCR1B = ( 1<<WGM12) | (0<<CS12) | (1<<CS11) | (1<<CS10) ;  // Prescaler / 64 ==> des PAS de 4µs
    TCCR1C = 0;                                                 // not forcing output compare
    TCNT1 = 0;                                                  // set timer counter initial value (16 bit value)
    OCR1A = 1250;                                               // 1250 x 4µs = 5ms
    TIMSK1 = 1 << OCIE1A;                                       // enable timer compare match 1A interrupt
    sei();                                                      // enable interrupts

  delay(100);
}


/* ************************************************************************ */
/* ON EST APPELE DANS CETTE FONCTION TOUTES LES 5ms PAR LE TIMER INTERNE DU MICROP-P */
/* ************************************************************************ */
ISR(TIMER1_COMPA_vect) // 16 bit timer 1 compare 1A match
{
    static uint16_t iDemiSeconde = EACH_DEMI_SECONDE;
    if (--iDemiSeconde == 0 ) {
        flipLed();
        //action();
        //action_test2();
        iDemiSeconde = EACH_DEMI_SECONDE ;
    }
}

/* ************************************************************************ */
/* Action_test2()                                                           */
/* ************************************************************************ */
void action_test2()
{
    static int led = 0;
    if (led) {/*
      digitalWrite(ROUGE_1, ON );
      digitalWrite(ROUGE_2, ON );
      digitalWrite(ROUGE_3, ON );
      digitalWrite(ROUGE_4, ON );
      digitalWrite(ROUGE_5, ON );
      digitalWrite(ROUGE_6, ON );
      digitalWrite(ROUGE_7, ON );
      digitalWrite(ROUGE_8, ON );      
      digitalWrite(ROUGE_9, ON );
      digitalWrite(ROUGE_10, ON );
      digitalWrite(ROUGE_11, ON );
      digitalWrite(ROUGE_12, ON );*/

      digitalWrite(VERT_3, ON );
      /*digitalWrite(VERT_2, ON );
      digitalWrite(VERT_3, ON );
      digitalWrite(VERT_4, ON );
      digitalWrite(VERT_5, ON );
      digitalWrite(VERT_6, ON );
      digitalWrite(VERT_7, ON );
      digitalWrite(VERT_8, ON );      
      digitalWrite(VERT_9, ON );
      digitalWrite(VERT_10, ON );
      digitalWrite(VERT_11, ON );
      digitalWrite(VERT_12, ON );*/

      /*for (int i=5; i<32 ; i++)
      {
        digitalWrite(22+i, ON );
      }*/
    } else {/*
      digitalWrite(ROUGE_1, OFF );
      digitalWrite(ROUGE_2, OFF );
      digitalWrite(ROUGE_3, OFF );
      digitalWrite(ROUGE_4, OFF );
      digitalWrite(ROUGE_5, OFF );
      digitalWrite(ROUGE_6, OFF );
      digitalWrite(ROUGE_7, OFF );
      digitalWrite(ROUGE_8, OFF );      
      digitalWrite(ROUGE_9, OFF );
      digitalWrite(ROUGE_10, OFF );
      digitalWrite(ROUGE_11, OFF );
      digitalWrite(ROUGE_12, OFF );*/

            digitalWrite(VERT_3, OFF );
      /*digitalWrite(VERT_2, OFF );
      digitalWrite(VERT_3, OFF );
      digitalWrite(VERT_4, OFF );
      digitalWrite(VERT_5, OFF );
      digitalWrite(VERT_6, OFF );
      digitalWrite(VERT_7, OFF );
      digitalWrite(VERT_8, OFF );      
      digitalWrite(VERT_9, OFF );
      digitalWrite(VERT_10, OFF );
      digitalWrite(VERT_11, OFF );
      digitalWrite(VERT_12, OFF );*/
/*
      for (int i=5; i<32 ; i++)
      {
        digitalWrite(22+i, OFF );
      }*/

    }
    led = 1-led;
}

/* ************************************************************************ */
/* Action()                                                                 */
/* ************************************************************************ */
void action()
{
      switch(mode)
      {
        case VERT1:   digitalWrite(ROUGE_2,   ON );
                      digitalWrite(ORANGE_2,  OFF );
                      digitalWrite(VERT_2,    OFF );
                      digitalWrite(ROUGE_1,   OFF );
                      digitalWrite(ORANGE_1,  OFF );
                      digitalWrite(VERT_1,    ON );
                      mode =  ORANGE1 ;           
                      break;

        case ORANGE1: digitalWrite(ROUGE_2,   ON );
                      digitalWrite(ORANGE_2,  OFF );
                      digitalWrite(VERT_2,    OFF );
                      digitalWrite(ROUGE_1,   OFF );
                      digitalWrite(ORANGE_1,  ON );
                      digitalWrite(VERT_1,    OFF );
                      mode =  ROUGE1 ;           
                      break;

        case ROUGE1:  digitalWrite(ROUGE_2,   ON );
                      digitalWrite(ORANGE_2,  OFF );
                      digitalWrite(VERT_2,    OFF );
                      digitalWrite(ROUGE_1,   ON );
                      digitalWrite(ORANGE_1,  OFF );
                      digitalWrite(VERT_1,    OFF );
                      mode =  TEMPOROUGE1 ;           
                      break;

        case VERT2:   digitalWrite(ROUGE_2,   OFF );
                      digitalWrite(ORANGE_2,  OFF );
                      digitalWrite(VERT_2,    ON );
                      digitalWrite(ROUGE_1,   ON );
                      digitalWrite(ORANGE_1,  OFF );
                      digitalWrite(VERT_1,    OFF );
                      mode =  ORANGE2 ;           
                      break;

        case ORANGE2:   digitalWrite(ROUGE_2,   OFF );
                        digitalWrite(ORANGE_2,  ON );
                        digitalWrite(VERT_2,    OFF );
                        digitalWrite(ROUGE_1,   ON );
                        digitalWrite(ORANGE_1,  OFF );
                        digitalWrite(VERT_1,    OFF );
                        mode =  ROUGE2 ;           
                        break;

        case ROUGE2:    digitalWrite(ROUGE_2,   OFF );
                        digitalWrite(ORANGE_2,  ON );
                        digitalWrite(VERT_2,    OFF );
                        digitalWrite(ROUGE_1,   ON );
                        digitalWrite(ORANGE_1,  OFF );
                        digitalWrite(VERT_1,    OFF );
                        mode =  ROUGE2 ;           
                        break;

        case TEMPOROUGE2: break;
        default: break;
      }
}

/* ************************************************** */
/*                                                    */
void loop() {
//normal();
//cligno_orange(true);
//cligno(0);
//cligno(1);
//cligno(2);

test_rouge(200);
test_jaune(200);

}

/* ************************************************************************ */
/* a chaque appel de cette fonction on bascule l'état de la led             */
/* ************************************************************************ */
void flipLed()
{
    static int led = 0;
    if (led){
        digitalWrite(LED_BUILTIN, LOW );
    } else {
        digitalWrite(LED_BUILTIN, HIGH);
    }
    led = 1-led;
}

/* ************************************************** */
/*                                                    */
void normal()
{

  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH); 
   digitalWrite(ROUGE_2, ON);
   digitalWrite(ROUGE_1, OFF);
   digitalWrite(VERT_1,  ON);
   delay(2000);
   digitalWrite(LED_BUILTIN, LOW); 


   digitalWrite(VERT_1,  OFF);
   digitalWrite(ORANGE_1,  ON);
   delay(500);

   digitalWrite(ORANGE_1,  OFF);
   digitalWrite(ROUGE_1,  ON);
   delay(500);

   digitalWrite(ROUGE_2,  OFF);
   digitalWrite(VERT_2,  ON);
   delay(2000);

   digitalWrite(VERT_2,  OFF);
   digitalWrite(ORANGE_2,  ON);
   delay(500);

   digitalWrite(ORANGE_2,  OFF);
   digitalWrite(ROUGE_2,  ON);
   delay(200);
   }

/* ************************************************** */
/*                                                    */
void cligno_orange(bool mode)
{
  if (mode)
  {
   digitalWrite(ORANGE_1,  ON);
   digitalWrite(ORANGE_2,  ON);
   delay(500);

   digitalWrite(ORANGE_1,  OFF);
   digitalWrite(ORANGE_2,  OFF);
   delay(500);
  }else
  {
   digitalWrite(ORANGE_1,  OFF);
   digitalWrite(ORANGE_2,  ON);
   delay(100);

   digitalWrite(ORANGE_1,  ON);
   digitalWrite(ORANGE_2,  OFF);
   delay(100);
}}

/* ************************************************** */
/*                                                    */
void cligno(int feu)
{   

  for (int i=0 ; i<NB_FEU ; i++){
    switch (feu){
      case 0 : digitalWrite(tabTeu[i].ledRouge,  ON); break;
      case 1 : digitalWrite(tabTeu[i].ledOrange, ON); break;
      case 2 : digitalWrite(tabTeu[i].ledVert,   ON); break;
      default: break;
    }
  }

    delay(250);
  for (int i=0 ; i<NB_FEU ; i++){
    switch (feu){
      case 0 : digitalWrite(tabTeu[i].ledRouge,  OFF); break;
      case 1 : digitalWrite(tabTeu[i].ledOrange, OFF); break;
      case 2 : digitalWrite(tabTeu[i].ledVert,   OFF); break;
      default: break;
    }
  }
    delay(250);
}
    
/* ************************************************** */
/*                                                    */
void test_rouge(int tempo)
{   
  digitalWrite(tabTeu[0].ledRouge,  ON);  delay(tempo);
  digitalWrite(tabTeu[0].ledRouge,  OFF);
  digitalWrite(tabTeu[1].ledRouge,  ON);  delay(tempo);
  digitalWrite(tabTeu[1].ledRouge,  OFF);
  digitalWrite(tabTeu[2].ledRouge,  ON); delay(tempo);
  digitalWrite(tabTeu[2].ledRouge,  OFF); 
  digitalWrite(tabTeu[3].ledRouge,  ON); delay(tempo);
  digitalWrite(tabTeu[3].ledRouge,  OFF);
  digitalWrite(tabTeu[4].ledRouge,  ON); delay(tempo);
  digitalWrite(tabTeu[4].ledRouge,  OFF);
}

/* ************************************************** */
/*                                                    */
void test_jaune(int tempo)
{   
  digitalWrite(tabTeu[0].ledOrange,  ON);  delay(tempo);
  digitalWrite(tabTeu[0].ledOrange,  OFF);
  digitalWrite(tabTeu[1].ledOrange,  ON);  delay(tempo);
  digitalWrite(tabTeu[1].ledOrange,  OFF);
  digitalWrite(tabTeu[2].ledOrange,  ON); delay(tempo);
  digitalWrite(tabTeu[2].ledOrange,  OFF); 
  digitalWrite(tabTeu[3].ledOrange,  ON); delay(tempo);
  digitalWrite(tabTeu[3].ledOrange,  OFF);
  digitalWrite(tabTeu[4].ledOrange,  ON); delay(tempo);
  digitalWrite(tabTeu[4].ledOrange,  OFF);
}
