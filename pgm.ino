#include "assigne.h"

void flipLed();
void cligno_orange(int tempo);
void cligno_all(int tempo);
void aleatoire(int tempo);
void k2000(int tempo);
void test_sw();
void AffValeur(unsigned char valeur);
void GestionBouton(void);

#define EACH_DEMI_SECONDE (50) // 5ms * 100 = 500ms
#define MENU_MAX  7

enum MODE { VERT, ORANGE, ROUGE};
enum MODE gMode = VERT;

unsigned char gCurrentState = 0;
volatile uint32_t gTicks = 0;
volatile uint32_t gVal = 0;

struct ST_FEU { unsigned char ledRouge;
                unsigned char ledOrange;
                unsigned char ledVert;};

struct ST_SW {  unsigned char pin;
                bool etat; 
                bool dernierEtatLu;
                bool etatStable;
                bool action;
                uint32_t  debutRebond; };

struct ST_SW tabSw[NB_SW] { SW1, OFF,HIGH,HIGH, false, 0,
                            SW2, OFF,HIGH,HIGH, false, 0,
                            SW3, OFF,HIGH,HIGH, false, 0,
                            SW4, OFF,HIGH,HIGH, false, 0 };

struct ST_FEU tabFeu[NB_FEU_MAX] = {  ROUGE_1, ORANGE_1, VERT_1,
                                  ROUGE_2, ORANGE_2, VERT_2,
                                  ROUGE_3, ORANGE_3, VERT_3,
                                  ROUGE_4, ORANGE_4, VERT_4,
                                  ROUGE_5, ORANGE_5, VERT_5,
                                  ROUGE_6, ORANGE_6, VERT_6,
                                  ROUGE_7, ORANGE_7, VERT_7,
                                  ROUGE_8, ORANGE_8, VERT_8,
                                  ROUGE_9, ORANGE_9, VERT_9,
                                  ROUGE_10, ORANGE_10, VERT_10,
                                  ROUGE_11, ORANGE_11, VERT_11,
                                  // ROUGE_12, ORANGE_12, VERT_12,
                                  };

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);

for (int i=0 ; i<NB_FEU_MAX ; i++){
  pinMode(tabFeu[i].ledRouge,  OUTPUT);
  pinMode(tabFeu[i].ledOrange, OUTPUT);
  pinMode(tabFeu[i].ledVert,   OUTPUT);

  digitalWrite(tabFeu[i].ledRouge,  OFF);
  digitalWrite(tabFeu[i].ledOrange, OFF);
  digitalWrite(tabFeu[i].ledVert,   OFF);
}

for (int i=0 ; i<NB_SW ; i++){
  pinMode(tabSw[i].pin,   INPUT_PULLUP);
  tabSw[i].etat = false;
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
    //sequence();
    iDemiSeconde = EACH_DEMI_SECONDE ;
    //GestionBouton();
  }
  gTicks++;
  gVal++;
  //GestionBouton();
/*  
      if (tabSw[0].etat){
        gCurrentState++;
        tabSw[0].etat = false;
      }

      if (tabSw[1].etat){
        if (gCurrentState >0) {
          gCurrentState --;
        }
        tabSw[1].etat = false;
      }

      if (tabSw[3].etat){
        gCurrentState = 0;
        tabSw[3].etat = false;
      }
*/
}

/* ************************************************************************ */
/* Que des traitement rapide dans cette fonction */
/* ************************************************************************ */
void GestionBouton(void)
{


// detection du front montant
// on attend le front descendant pour valider
// puis apres un certain temps on autorise 

/*

    int i=0;
    if (tabSw[i].etat)
    {
        if (tabSw[i].compteur++  >= 20)
        {
            tabSw[i].value = true;
            tabSw[i].compteur = 0;
            tabSw[i].etat = false;
        }
    }*/
}

/* ************************************************** */
/*                                                    */
void loop() {
  /*
switch (gCurrentState){
  case 0: break; 
  case 1: //cligno_orange(500); break; 
  case 2: cligno_all(250,0); break; 
  case 3: cligno_all(250,1); break; 
  case 4: cligno_all(250,2); break; 
  case 5: cligno_all(250,0); break; 
  case 6: aleatoire(100); break; 
  case 7: k2000(30); break; 
}*/
//cligno_orange(gCurrentState*10+10);
//cligno_all(250,0);
//aleatoire(100);
//k2000(30);
  /*for (int i=0 ; i<NB_SW ; i++) {
    if (!digitalRead(tabSw[i].pin) ){
        tabSw[i].etat = true;
    }else {
      tabSw[i].etat = false;
      tabSw[i].compteur = 0;
    }
  }

  if (tabSw[0].value) {
    gCurrentState++;
    tabSw[0].value = false ;
  }
*/
  for (int i=0 ; i<NB_SW ; i++) {
    //static bool etatStable = HIGH;
    //static bool dernierEtatLu = HIGH;
    //static uint32_t debutRebond = 0;

    bool etatLu = digitalRead(tabSw[i].pin);

    // Changement détecté
    if (etatLu != tabSw[i].dernierEtatLu)
    {
        tabSw[i].dernierEtatLu = etatLu;
        tabSw[i].debutRebond = gTicks;
    }
    // Etat stable depuis suffisamment longtemps ?
    if ((gTicks - tabSw[i].debutRebond) >= 10) {
      if (tabSw[i].etatStable != tabSw[i].dernierEtatLu) {
        bool ancienEtat = tabSw[i].etatStable;
        tabSw[i].etatStable = tabSw[i].dernierEtatLu;
        // Validation au relâchement
        if (ancienEtat == LOW && tabSw[i].etatStable == HIGH) {
          tabSw[i].action = true ;
        }
      }
    }
  }

  //Serial.println(gCurrentState);
  if (tabSw[0].action){
    tabSw[0].action = false; 
    Serial.println("BT_1");
    gCurrentState++;
    if (gCurrentState > MENU_MAX){
      gCurrentState = 0; 
      }; 
    Serial.println(gCurrentState);
    AffValeur(gCurrentState); 
    }

  if (tabSw[1].action){ 
    tabSw[1].action = false; 
    Serial.println("BT_2");
    if (gCurrentState > 0){
    gCurrentState--; 
    }
    AffValeur(gCurrentState); 
    }
  if (tabSw[2].action){tabSw[2].action = false; gCurrentState=0x80;  Serial.println("BT_3");
  AffValeur(gCurrentState);
   }
  if (tabSw[3].action){tabSw[3].action = false; gCurrentState =0;  Serial.println("BT_4");
  AffValeur(gCurrentState); 
  }
  //Serial.println(gCurrentState);
  //AffValeur(gCurrentState);
}



/* ************************************************************************ */
/*                                                                          */
/* ************************************************************************ */
void AffValeur(unsigned char valeur)
{
  static int oldValeur = 256;
  if (oldValeur != valeur) {
    for (int i = 0; i < 8; i++) {
      if (valeur & (1 << i)) { // Bit à 1
        digitalWrite(tabFeu[i].ledOrange, ON );
      } else { // Bit à 0
        digitalWrite(tabFeu[i].ledOrange, OFF );
      }
    }
  }
  // Serial.println(valeur);
}

/* ************************************************************************ */
/* A chaque appel de cette fonction on bascule l'état de la led             */
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

/* ************************************************** */
/*                                                    */
void cligno_orange(int tempo)
{
  static bool sens = false ;

  if (gVal >= tempo ){
    for (int i=0 ; i<NB_FEU ; i++){
        digitalWrite(tabFeu[i].ledOrange, sens); 
    }

    if (sens){
      sens = false;
    } else {
      sens = true;
    }
    gVal = 0;
  }
}
  

/* ************************************************** */
/*                                                    */
void cligno_all(int tempo, int couleur )
{   

  for (int i=0 ; i<NB_FEU ; i++){
    switch (couleur){
      case 0 : digitalWrite(tabFeu[i].ledRouge,  ON); break;
      case 1 : digitalWrite(tabFeu[i].ledOrange, ON); break;
      case 2 : digitalWrite(tabFeu[i].ledVert,   ON); break;
      default: break;
    }
  }

    delay(tempo);
  for (int i=0 ; i<NB_FEU ; i++){
    switch (couleur){
      case 0 : digitalWrite(tabFeu[i].ledRouge,  OFF); break;
      case 1 : digitalWrite(tabFeu[i].ledOrange, OFF); break;
      case 2 : digitalWrite(tabFeu[i].ledVert,   OFF); break;
      default: break;
    }
  }
    delay(tempo);
}
    


/* ************************************************** */
/*                                                    */
void aleatoire(int tempo)
{ 
  for (int i=0 ; i<NB_FEU ; i++){
    digitalWrite(tabFeu[i].ledRouge,  random(0,15));
    digitalWrite(tabFeu[i].ledOrange, random(0,15));
    digitalWrite(tabFeu[i].ledVert,   random(0,15));
  }
  delay(tempo);
}

/* ************************************************** */
/*                                                    */
void k2000(int tempo)
{ 
    // ALLER
    for (int i=0 ; i < NB_FEU ; i++){
      digitalWrite(tabFeu[i].ledRouge,  ON);
      if (i == 0){
       digitalWrite(tabFeu[NB_FEU-1].ledRouge,  OFF); 
      } else {
        digitalWrite(tabFeu[i-1].ledRouge,  OFF);
      }
      delay(tempo);
    }

    // RETOUR
    for (int i=NB_FEU-1 ; i >= 0 ; i--){
      digitalWrite(tabFeu[i].ledRouge,  ON);
      if (i == NB_FEU-1){
       digitalWrite(tabFeu[0].ledRouge,  OFF); 
      } else {
        digitalWrite(tabFeu[i+1].ledRouge,  OFF);
      }
      delay(tempo);
    }
}

/* ************************************************** */
/* feux standard                                      */
void sequence()
{
    static int couleur = 0;
    static int numFeu  = 0;
    static int tempo = 5;

    switch(couleur){
      case 0: digitalWrite(tabFeu[numFeu].ledRouge,  OFF);
              digitalWrite(tabFeu[numFeu].ledOrange, OFF);
              digitalWrite(tabFeu[numFeu].ledVert,   ON);
              if (--tempo <= 0 ) {
                tempo = 3; // Tempo orange
                couleur++;
              }
              break;
      case 1: digitalWrite(tabFeu[numFeu].ledRouge,  OFF);
              digitalWrite(tabFeu[numFeu].ledOrange, ON);
              digitalWrite(tabFeu[numFeu].ledVert,   OFF);
              if (--tempo <= 0 ) {
                tempo = 1; // Tempo rouge
                couleur++;
              }
              break;
      case 2: digitalWrite(tabFeu[numFeu].ledRouge,  ON);
              digitalWrite(tabFeu[numFeu].ledOrange, OFF);
              digitalWrite(tabFeu[numFeu].ledVert,   OFF);
              if (--tempo <= 0 ) {
                tempo = 10; // Tempo vert
                couleur=0;

                if (++numFeu == NB_FEU){ 
                  numFeu = 0;
                }
              }
              
              break;
      default: break;
    }

}


/* ************************************************** */
/*                                                    */
void sequence_3()
{
  static bool bRouge = false ;
  static bool bOrange = false ;
  static bool bVert   = false ;
    if (tabSw[2].etat){ tabSw[2].etat = false; bVert = true;  bOrange = false; bRouge = false;}
    if (tabSw[1].etat){ tabSw[1].etat = false; bVert = false; bOrange = true;  bRouge = false;}
    if (tabSw[0].etat){ tabSw[0].etat = false; bVert = false; bOrange = false; bRouge = true;}

    static int etat=0;
    if (etat==0){
      digitalWrite(tabFeu[9].ledRouge,  OFF);
      digitalWrite(tabFeu[9].ledOrange,  OFF);
      digitalWrite(tabFeu[9].ledVert,  OFF);
    }else{
      digitalWrite(tabFeu[etat-1].ledRouge,  OFF);
      digitalWrite(tabFeu[etat-1].ledOrange,  OFF);
      digitalWrite(tabFeu[etat-1].ledVert,  OFF);
    }
    if (bRouge){
      digitalWrite(tabFeu[etat].ledRouge,  ON);
    }
    
    if (bOrange){
      digitalWrite(tabFeu[etat].ledOrange,  ON);
    }

    if (bVert){
      digitalWrite(tabFeu[etat].ledVert,  ON);
    }

    if (++etat == NB_FEU){
      etat = 0;
    }
}

/* ************************************************** */
/*                                                    */
void sequence2()
{
  static int nextFeu = 0;
  static int tempo = 10 ;
  static int feu = 0 ;

  switch(gMode){
    case VERT :  
        digitalWrite(tabFeu[feu].ledRouge,  OFF); 
        digitalWrite(tabFeu[feu].ledVert,   ON); 
        if (--tempo <= 0 ){ 
          tempo = 2 ; // Duree prochaine étape
          gMode = ORANGE;
        }
        break ;

    case ORANGE :  
        digitalWrite(tabFeu[feu].ledVert,   OFF); 
        digitalWrite(tabFeu[feu].ledOrange,   ON); 
        if (--tempo <= 0 ){ 
          tempo = 5 ; // Duree prochaine étape
          gMode = ROUGE;
        }
        break ;

    case ROUGE :  
        digitalWrite(tabFeu[feu].ledOrange,   OFF); 
        digitalWrite(tabFeu[feu].ledRouge,   ON); 
        if (--tempo <= 0 ){ 
          tempo = 5 ; // Duree prochaine étape
          gMode = VERT;
          nextFeu = true;
        }
        break ;
          break ;
    default : break;
  }
  if (nextFeu){
    nextFeu = false ;
    feu++ ;
    if (feu == NB_FEU){
      feu = 0;
    } 
  }
}

void test_sw()
{
    digitalWrite(tabFeu[4].ledOrange,   digitalRead(SW4));  
    digitalWrite(tabFeu[5].ledOrange,   digitalRead(SW3));  
    digitalWrite(tabFeu[6].ledOrange,   digitalRead(SW2));  
    digitalWrite(tabFeu[7].ledOrange,   digitalRead(SW1));  

} 