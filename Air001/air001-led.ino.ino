#pragma GCC optimize ("O0")
// 855 
char font[ 95 ][ 9 ]={ 0 ,  256 ,  256 ,  0 ,  0 ,  256 ,  256 ,  0 ,  0 ,     //[ ]
 0 ,  0 ,  262 ,  351 ,  351 ,  262 ,  0 ,  0 ,  0 ,     //[!]
 0 ,  0 ,  7 ,  7 ,  256 ,  263 ,  263 ,  256 ,  0 ,     //["]
 0 ,  276 ,  383 ,  383 ,  20 ,  127 ,  383 ,  276 ,  0 ,     //[#]
 0 ,  292 ,  302 ,  363 ,  363 ,  58 ,  18 ,  0 ,  0 ,     //[$]
 0 ,  326 ,  358 ,  48 ,  24 ,  12 ,  358 ,  354 ,  0 ,     //[%]
 0 ,  304 ,  378 ,  79 ,  93 ,  55 ,  378 ,  328 ,  0 ,     //[&]
 0 ,  4 ,  7 ,  259 ,  256 ,  256 ,  0 ,  0 ,  0 ,     //[']
 0 ,  256 ,  284 ,  318 ,  355 ,  321 ,  256 ,  0 ,  0 ,     //[(]
 0 ,  0 ,  321 ,  355 ,  318 ,  284 ,  0 ,  0 ,  0 ,     //[)]
 0 ,  264 ,  298 ,  318 ,  284 ,  284 ,  318 ,  42 ,  8 ,     //[*]
 8 ,  8 ,  264 ,  318 ,  318 ,  264 ,  8 ,  0 ,  0 ,     //[+]
 0 ,  256 ,  384 ,  480 ,  352 ,  256 ,  256 ,  0 ,  0 ,     //[,]
 0 ,  264 ,  264 ,  8 ,  8 ,  264 ,  264 ,  0 ,  0 ,     //[-]
 0 ,  256 ,  256 ,  96 ,  96 ,  256 ,  256 ,  0 ,  0 ,     //[.]
 0 ,  352 ,  304 ,  24 ,  12 ,  6 ,  259 ,  257 ,  0 ,     //[/]
 0 ,  318 ,  383 ,  113 ,  89 ,  77 ,  383 ,  318 ,  0 ,     //[0]
 0 ,  320 ,  322 ,  127 ,  127 ,  320 ,  320 ,  0 ,  0 ,     //[1]
 0 ,  354 ,  371 ,  345 ,  329 ,  367 ,  358 ,  256 ,  0 ,     //[2]
 0 ,  34 ,  355 ,  329 ,  329 ,  383 ,  54 ,  0 ,  0 ,     //[3]
 0 ,  280 ,  284 ,  22 ,  83 ,  127 ,  127 ,  80 ,  0 ,     //[4]
 0 ,  39 ,  359 ,  325 ,  325 ,  381 ,  57 ,  0 ,  0 ,     //[5]
 0 ,  60 ,  126 ,  75 ,  329 ,  121 ,  48 ,  0 ,  0 ,     //[6]
 0 ,  3 ,  3 ,  113 ,  121 ,  15 ,  7 ,  0 ,  0 ,     //[7]
 0 ,  54 ,  127 ,  329 ,  329 ,  127 ,  54 ,  0 ,  0 ,     //[8]
 0 ,  6 ,  79 ,  73 ,  105 ,  63 ,  30 ,  0 ,  0 ,     //[9]
 0 ,  256 ,  256 ,  358 ,  102 ,  0 ,  0 ,  0 ,  0 ,     //[:]
 0 ,  0 ,  128 ,  230 ,  102 ,  0 ,  0 ,  0 ,  0 ,     //[;]
 0 ,  8 ,  28 ,  54 ,  355 ,  321 ,  256 ,  0 ,  0 ,     //[<]
 0 ,  36 ,  36 ,  36 ,  36 ,  36 ,  36 ,  0 ,  0 ,     //[=]
 0 ,  0 ,  65 ,  355 ,  310 ,  284 ,  8 ,  0 ,  0 ,     //[>]
 0 ,  2 ,  3 ,  81 ,  89 ,  15 ,  6 ,  0 ,  0 ,     //[?]
 0 ,  318 ,  383 ,  321 ,  93 ,  93 ,  31 ,  30 ,  0 ,     //[@]
 0 ,  124 ,  126 ,  275 ,  275 ,  126 ,  124 ,  0 ,  0 ,     //[A]
 0 ,  65 ,  127 ,  127 ,  73 ,  329 ,  383 ,  54 ,  0 ,     //[B]
 0 ,  284 ,  318 ,  355 ,  65 ,  65 ,  99 ,  34 ,  0 ,     //[C]
 0 ,  65 ,  383 ,  383 ,  321 ,  99 ,  62 ,  28 ,  0 ,     //[D]
 0 ,  65 ,  127 ,  127 ,  73 ,  93 ,  65 ,  99 ,  0 ,     //[E]
 0 ,  65 ,  127 ,  127 ,  73 ,  29 ,  1 ,  3 ,  0 ,     //[F]
 0 ,  28 ,  62 ,  99 ,  65 ,  81 ,  115 ,  114 ,  0 ,     //[G]
 0 ,  127 ,  127 ,  8 ,  8 ,  127 ,  127 ,  0 ,  0 ,     //[H]
 0 ,  0 ,  65 ,  127 ,  127 ,  65 ,  0 ,  0 ,  0 ,     //[I]
 0 ,  48 ,  112 ,  64 ,  65 ,  127 ,  63 ,  1 ,  0 ,     //[J]
 0 ,  65 ,  127 ,  127 ,  8 ,  28 ,  119 ,  99 ,  0 ,     //[K]
 0 ,  65 ,  127 ,  127 ,  321 ,  64 ,  96 ,  112 ,  0 ,     //[L]
 0 ,  127 ,  127 ,  14 ,  28 ,  14 ,  127 ,  127 ,  0 ,     //[M]
 0 ,  127 ,  127 ,  6 ,  12 ,  24 ,  127 ,  127 ,  0 ,     //[N]
 0 ,  28 ,  62 ,  99 ,  65 ,  99 ,  62 ,  28 ,  0 ,     //[O]
 0 ,  65 ,  127 ,  127 ,  73 ,  9 ,  15 ,  6 ,  0 ,     //[P]
 0 ,  30 ,  63 ,  33 ,  113 ,  127 ,  94 ,  0 ,  0 ,     //[Q]
 0 ,  65 ,  127 ,  127 ,  9 ,  25 ,  127 ,  102 ,  0 ,     //[R]
 0 ,  38 ,  111 ,  77 ,  345 ,  371 ,  306 ,  0 ,  0 ,     //[S]
 0 ,  3 ,  65 ,  127 ,  383 ,  321 ,  3 ,  0 ,  0 ,     //[T]
 0 ,  383 ,  383 ,  320 ,  64 ,  127 ,  127 ,  0 ,  0 ,     //[U]
 0 ,  31 ,  319 ,  352 ,  352 ,  63 ,  287 ,  256 ,  0 ,     //[V]
 0 ,  127 ,  127 ,  48 ,  24 ,  48 ,  127 ,  127 ,  0 ,     //[W]
 0 ,  67 ,  103 ,  60 ,  24 ,  60 ,  103 ,  67 ,  0 ,     //[X]
 0 ,  7 ,  79 ,  120 ,  120 ,  79 ,  7 ,  0 ,  0 ,     //[Y]
 0 ,  71 ,  99 ,  113 ,  89 ,  77 ,  103 ,  115 ,  0 ,     //[Z]
 0 ,  0 ,  127 ,  127 ,  65 ,  65 ,  0 ,  0 ,  0 ,     //[[]
 0 ,  1 ,  3 ,  6 ,  12 ,  24 ,  48 ,  96 ,  0 ,     //[\]
 0 ,  0 ,  65 ,  65 ,  127 ,  127 ,  0 ,  0 ,  0 ,     //[]]
 0 ,  8 ,  12 ,  6 ,  3 ,  6 ,  12 ,  8 ,  0 ,     //[^]
 0 ,  128 ,  128 ,  128 ,  128 ,  128 ,  128 ,  128 ,  128 ,     //[_]
 128 ,  0 ,  0 ,  3 ,  7 ,  4 ,  0 ,  0 ,  0 ,     //[`]
 0 ,  32 ,  116 ,  84 ,  84 ,  60 ,  120 ,  64 ,  0 ,     //[a]
 0 ,  65 ,  127 ,  63 ,  72 ,  72 ,  120 ,  48 ,  0 ,     //[b]
 0 ,  56 ,  124 ,  68 ,  68 ,  108 ,  40 ,  0 ,  0 ,     //[c]
 0 ,  48 ,  120 ,  72 ,  73 ,  63 ,  127 ,  64 ,  0 ,     //[d]
 0 ,  56 ,  124 ,  84 ,  84 ,  92 ,  24 ,  0 ,  0 ,     //[e]
 0 ,  72 ,  126 ,  127 ,  73 ,  3 ,  2 ,  0 ,  0 ,     //[f]
 0 ,  152 ,  188 ,  164 ,  164 ,  248 ,  124 ,  4 ,  0 ,     //[g]
 0 ,  65 ,  127 ,  127 ,  8 ,  4 ,  124 ,  120 ,  0 ,     //[h]
 0 ,  0 ,  68 ,  125 ,  125 ,  64 ,  0 ,  0 ,  0 ,     //[i]
 0 ,  96 ,  224 ,  128 ,  128 ,  253 ,  125 ,  0 ,  0 ,     //[j]
 0 ,  65 ,  127 ,  127 ,  16 ,  56 ,  108 ,  68 ,  0 ,     //[k]
 0 ,  0 ,  65 ,  127 ,  127 ,  64 ,  0 ,  0 ,  0 ,     //[l]
 0 ,  124 ,  124 ,  24 ,  56 ,  28 ,  124 ,  120 ,  0 ,     //[m]
 0 ,  124 ,  124 ,  4 ,  4 ,  124 ,  120 ,  0 ,  0 ,     //[n]
 0 ,  56 ,  124 ,  68 ,  68 ,  124 ,  56 ,  0 ,  0 ,     //[o]
 0 ,  132 ,  252 ,  248 ,  164 ,  36 ,  60 ,  24 ,  0 ,     //[p]
 0 ,  24 ,  60 ,  36 ,  164 ,  248 ,  252 ,  132 ,  0 ,     //[q]
 0 ,  68 ,  124 ,  120 ,  76 ,  4 ,  28 ,  24 ,  0 ,     //[r]
 0 ,  72 ,  92 ,  84 ,  84 ,  116 ,  36 ,  0 ,  0 ,     //[s]
 0 ,  0 ,  4 ,  62 ,  127 ,  68 ,  36 ,  0 ,  0 ,     //[t]
 0 ,  60 ,  124 ,  64 ,  64 ,  60 ,  124 ,  64 ,  0 ,     //[u]
 0 ,  28 ,  60 ,  96 ,  96 ,  60 ,  28 ,  0 ,  0 ,     //[v]
 0 ,  60 ,  124 ,  112 ,  56 ,  112 ,  124 ,  60 ,  0 ,     //[w]
 0 ,  68 ,  108 ,  56 ,  16 ,  56 ,  108 ,  68 ,  0 ,     //[x]
 0 ,  156 ,  188 ,  160 ,  160 ,  252 ,  124 ,  0 ,  0 ,     //[y]
 0 ,  76 ,  100 ,  116 ,  92 ,  76 ,  100 ,  0 ,  0 ,     //[z]
 0 ,  8 ,  8 ,  62 ,  119 ,  65 ,  65 ,  0 ,  0 ,     //[{]
 0 ,  0 ,  0 ,  0 ,  119 ,  119 ,  0 ,  0 ,  0 ,     //[|]
 0 ,  65 ,  65 ,  119 ,  62 ,  8 ,  8 ,  0 ,  0 ,     //[}]
 0 ,  2 ,  3 ,  1 ,  3 ,  2 ,  3 ,  1 ,  0 ,     //[~]
};
#define EVENT PB_1
#define P0 PB_2
#define P1 PB_0
#define P2 PA_7
#define P3 PA_4
#define P4 PA_3
#define P5 PA_2
#define P6 PA_1
#define P7 PA_0
const int DISP[8]={P7,P6,P5,P4,P3,P2,P1,P0}; 

void setup() {
  // put your setup code here, to run once:
 for(int i=0;i<8;i++)
      pinMode(DISP[i], OUTPUT);
 // Serial.begin(115200);
 // Serial.printf("Hello, Air001. \n");
  pinMode(EVENT, INPUT);
}
int mydelay(int n){
  int s=0; 
  for(int k=0;k<n;k++)s+=k;
  return s;
}
void disp(char * data){
  for(int j=0;j<9;j++){
    for(int i=0;i<8;i++){
      if(data[j] & (1<<i)){
        digitalWrite(DISP[i], HIGH);
      }else{
        digitalWrite(DISP[i], LOW);
      }
      mydelay(30);
    }
  }
}
void dispB(char * data){
  for(int j=8;j>=0;j--){
    for(int i=0;i<8;i++){
      if(data[j] & (1<<i)){
        digitalWrite(DISP[i], HIGH);
      }else{
        digitalWrite(DISP[i], LOW);
      }
      mydelay(30);
    }
//     Serial.printf("%d ", j);
  }
//   Serial.printf("done\n");
}
void display(char * msg){
      //digitalWrite(PB_1, HIGH);
    int i=0;
    for(i=0;msg[i]>0;i++){
      char c=msg[i];
     // Serial.printf("%c\n", c);
      char f=c - ' ';
      disp(font[f]);
      delay(1);
    }
}
void displayB(char * msg){
  //  Serial.printf("len:%d\n",i); 
  int i=strlen(msg);
    for(i--;i>=0;i--){
      char c=msg[i];
     // Serial.printf("%c\n", c);
      char f=c - ' ';
      dispB(font[f]);
      delay(1);
    //   Serial.printf("ok:%d\n",i); 
    }
}
char old=digitalRead(EVENT);
void waitEVENT(char state){
  
  while(state==digitalRead(EVENT)){
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  static int count = 0;
  const int total=9;
  const int rep=12;
  char msg[total][64]={"  666    ",
                       "  Love   ",
                       "  Linux  ",
                       "  YYDS   ",
                       "  Hello! ",
                       "  2023   ",
                       "  China  ",
                       "  2024   ",
                       "  ^_^    "};
  //sprintf(msg,"%d", count);
 // old=digitalRead(EVENT);
  waitEVENT(LOW);
      display(msg[(count/rep) % total]);
  waitEVENT(HIGH);
      displayB(msg[(count/rep) % total]);
  count++;
}