#define ORANGE_2  30
#define VERT_2  32
#define ROUGE_2  34
#define ORANGE_1  36
#define VERT_1  38
#define ROUGE_1  40

#define ON  LOW
#define OFF HIGH 

void normal();
void cligno();

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ORANGE_1, OUTPUT);
  pinMode(ORANGE_2, OUTPUT);
  pinMode(ROUGE_1, OUTPUT);
  pinMode(ROUGE_2, OUTPUT);
  pinMode(VERT_1, OUTPUT);
  pinMode(VERT_2, OUTPUT);
  digitalWrite(ORANGE_1, HIGH); 
  digitalWrite(ORANGE_2, HIGH); 
  digitalWrite(ROUGE_1, HIGH); 
  digitalWrite(ROUGE_2, HIGH); 
  digitalWrite(VERT_1, HIGH); 
  digitalWrite(VERT_2, HIGH); 
  delay(100);

}

/* ************************************************** */
/*                                                    */
void loop() {
normal();
// cligno();
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
void cligno()
{
   digitalWrite(ORANGE_1,  OFF);
   digitalWrite(ORANGE_2,  ON);
   delay(300);

   digitalWrite(ORANGE_1,  ON);
   digitalWrite(ORANGE_2,  OFF);
   delay(300);
}
