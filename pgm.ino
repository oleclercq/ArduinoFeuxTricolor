#define ORANGE_2  30
#define VERT_2  32
#define ROUGE_2  34
#define ORANGE_1  36
#define VERT_1  38
#define ROUGE_1  40

#define ON  LOW
#define OFF HIGH 

#define NB_FEU 2 

void normal();
void cligno_orange(bool mode);
void cligno_rouge();
void flipLed();

#define EACH_DEMI_SECONDE (100) // 5ms * 100 = 500ms

enum MODE { VERT1, ORANGE1, ROUGE1, TEMPOROUGE1, VERT2, ORANGE2, ROUGE2, TEMPOROUGE2};
enum MODE mode = VERT1;

struct ST_FEU { unsigned char ledRouge,
                unsigned char ledOrange,
                unsigned char ledVert};

struct ST_FEU tabTeu[NB_FEU] = {  ROUGE_1, ORANGE_1, VERT_1,
                                  ROUGE_2, ORANGE_2, VERT_2};



void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);

for (int i=0 ; i<NB_FEU ; i++){
  pinMode(tabTeu[i].ledRouge, OUTPUT);
  pinMode(tabTeu[i].ledOrange, OUTPUT);
  pinMode(tabTeu[i].ledVert, OUTPUT);
}

for (int i=0 ; i<NB_FEU ; i++){
  digitalWrite(tabTeu[i].ledRouge, OFF);
  digitalWrite(tabTeu[i].ledOrange, OFF);
  digitalWrite(tabTeu[i].ledVert, OFF);
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
/* ON EST APPELE DANS CETTE FONCTION TOUTES LES 5ms PAR LE TIMER INTERNE DU MICROP-P
/* ************************************************************************ */
ISR(TIMER1_COMPA_vect) // 16 bit timer 1 compare 1A match
{
    static uint16_t iDemiSeconde = EACH_DEMI_SECONDE;
    if (--iDemiSeconde == 0 ) {
        flipLed();
        action();
        iDemiSeconde = EACH_DEMI_SECONDE ;
    }
}

void action()
{
      switch()
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
cligno_orange(true);
//cligno_rouge();
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
void cligno_rouge()
{   
    digitalWrite(ROUGE_1,  OFF);
    digitalWrite(ROUGE_2,  ON);
    delay(300);

    digitalWrite(ROUGE_1,  ON);
    digitalWrite(ROUGE_2,  OFF);
    delay(300);
}
    
