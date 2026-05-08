const int pinoADC = 2; // Defina o pino analógico
float R1 = 465500.0;   // Resistor 1 (470k)  
float R2 = 302000.0;  // Resistor 2 (300k)

// Fator calibração obtido entre o valor real da bateria e o valor que estava sendo obtido no código
float fatorcalibracao = 1.02; 

// Função que faz a média de várias leituras do ADC
float lerMediaADC(int pino, int amostras = 50) {
  long soma = 0;
  for (int i = 0; i < amostras; i++) {
    soma += analogRead(pino);
    delay(2);
  }
  return soma / (float)amostras;
}

void setup() {
  Serial.begin(115200);
  // Define a atenuação para leitura de até 3.3V
  analogSetAttenuation(ADC_11db);
}

void loop() {
  float valorRaw = lerMediaADC(pinoADC);
  
  // Converte valor bruto (0-4095) para tensão no pino (0-3.3V)
  float vPino = (valorRaw / 4095.0) * 3.31;
  
  // Calcula a tensão real da bateria baseada no divisor
  float vBateria = vPino * ((R1 + R2) / R2) * fatorcalibracao;
  
  // Exibe o valor no monitor serial
  Serial.print("Tensão da Bateria: ");
  Serial.print(vBateria);
  Serial.println(" V");
  
  delay(10000); // aguarda 10 segundos
}
