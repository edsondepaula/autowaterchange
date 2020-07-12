/*******************************************************************************
* Auto Water Change - v1.0
* By Edson de Paula
* edsoncdepaula@gmail.com
*******************************************************************************/

// set pinos
int boia_max = 2;
int boia_min = 3;
int rele_descarte = 4;
int rele_reposicao = 5;
int led_reposicao = 6;
int led_descarte = 7;
int botao_liga = 8;

// set variables
int ultimo_valor_do_botao = LOW;

int OPERACIONAL = 0;
int ESVAZIANDO = 1;
int ENCHENDO = 2;

int estado_aquario = OPERACIONAL;

void setup() {
  pinMode(led_descarte, OUTPUT);
  pinMode(led_reposicao, OUTPUT);
  pinMode(botao_liga, INPUT);
  pinMode(rele_descarte, OUTPUT);
  pinMode(rele_reposicao, OUTPUT);
  pinMode(boia_max, INPUT);
  pinMode(boia_min, INPUT);
  
  digitalWrite(rele_reposicao, HIGH);
  digitalWrite(rele_descarte, HIGH);
  
  attachInterrupt(
    digitalPinToInterrupt(boia_max),
    BoiaMax,
    RISING);

  attachInterrupt(
    digitalPinToInterrupt(boia_min),
    BoiaMin,
    FALLING);
}

void loop() {
//  digitalWrite(rele_reposicao, HIGH);
//  digitalWrite(rele_descarte, HIGH);
  
  int estado_do_botao = digitalRead(botao_liga);
  
  if (estado_do_botao == HIGH && ultimo_valor_do_botao == LOW)
  {
    // Botão foi apertado
    if (estado_aquario == OPERACIONAL)
    {
      Esvazia();
    }
    else
    {
      Para();
    }
  }

  ultimo_valor_do_botao = estado_do_botao;
}

void AtivaDescarte()
{
  digitalWrite(led_descarte, HIGH);
  digitalWrite(rele_descarte, LOW);
}

void DesativaDescarte()
{
  digitalWrite(led_descarte, LOW);
  digitalWrite(rele_descarte, HIGH);
}

void AtivaReposicao()
{
  digitalWrite(led_reposicao, HIGH);
  digitalWrite(rele_reposicao, LOW);
}

void DesativaReposicao()
{
  digitalWrite(led_reposicao, LOW);
  digitalWrite(rele_reposicao, HIGH);
}

void Esvazia()
{
  AtivaDescarte();
  DesativaReposicao();
  estado_aquario = ESVAZIANDO;
}

void Enche()
{
  DesativaDescarte();
  AtivaReposicao();
  estado_aquario = ENCHENDO;
}

void Para()
{
  DesativaDescarte();
  DesativaReposicao();
  estado_aquario = OPERACIONAL;
}

void Erro()
{
  Para();
  while (1)
  {
    digitalWrite(led_descarte, !digitalRead(led_descarte));
    digitalWrite(led_reposicao, !digitalRead(led_reposicao));
    delay(500);
  }
}

void BoiaMax()
{
  Para();
}

void BoiaMin()
{
  if (estado_aquario == ESVAZIANDO)
  {
    Enche();
  }
  else
  {
    Erro();
  }
}
