const int pinoADC = 2; // Defina o pino analógico
float V_max = 5.0;    // Tensão máxima esperada da bateria
float R1 = 465500.0;   // Resistor 1 (470k)
//float R2 = 99400.0;    // Resistor 2 (100k)
float R2 = 302000.0;

void setup() {
  Serial.begin(115200);
  // Define a atenuação para leitura de até 3.3V
  analogSetAttenuation(ADC_11db);
}

void loop() {
  int valorRaw = analogRead(pinoADC);
  
  // Converte valor bruto (0-4095) para tensão no pino (0-3.3V)
  float vPino = (valorRaw / 4095.0) * 3.3;
  
  // Calcula a tensão real da bateria baseada no divisor
  float vBateria = vPino * ((R1 + R2) / R2);
  
  Serial.print("Tensão da Bateria: ");
  Serial.print(vBateria);
  Serial.println(" V");
  
  delay(1000);
}
