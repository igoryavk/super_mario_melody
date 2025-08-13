#define BUZZER_PIN 10

// Определяем ноты
#define NOTE_C5  523
#define NOTE_E5  659
#define NOTE_G5  784

// Фрагмент мелодии Super Mario Bros.
int melody[] = {
  NOTE_E5, NOTE_E5, 0, NOTE_E5, 0, NOTE_C5, NOTE_E5, 0,
  NOTE_G5, 0, 0, 0
};

// Длительности нот (8 = восьмая нота)
int noteDurations[] = {
  8, 8, 8, 8, 8, 8, 8, 8,
  4, 8, 8, 8
};

bool shouldPlay = false;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Отправьте 'play' для воспроизведения мелодии");
}

void playMelody() {
  for (int i = 0; i < sizeof(melody)/sizeof(melody[0]); i++) {
    if (melody[i] == 0) {
      noTone(BUZZER_PIN);
    } else {
      tone(BUZZER_PIN, melody[i], 1000/noteDurations[i]);
    }
    delay(1000/noteDurations[i] * 1.3);
    noTone(BUZZER_PIN);
  }
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    
    if (command == "play") {
      Serial.println("Воспроизведение...");
      playMelody();
      Serial.println("Готово!");
    }
  }
}
