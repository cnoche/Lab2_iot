int bits = 4; // Número de bits utilizados para muestrear la altura
int volt = A0;

void setup() {
    Serial.begin(9600);
    pinMode(volt, INPUT);
    pinMode(A15, OUTPUT);
    pinMode(A14, OUTPUT);
    pinMode(A13, OUTPUT);
    pinMode(A12, OUTPUT);
}

void loop() {
    volt = analogRead(A0);
    Serial.print("Valor analógico:  ");
    Serial.print(volt);
    Serial.print("\n");
    int sampleValue = map(volt, 0, 1023, 0, (1 << bits) - 1); // Mapear el valor a una muestra de altura
    Serial.print("Muestra de altura:  ");
    Serial.print(sampleValue);
    Serial.print("\n");
    delay(100); // Esperar 100ms antes de volver a leer el valor analógico
}