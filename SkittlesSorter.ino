#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

int frequency = 0;

int colorDifference(int values[3], int measurement[3]);
int indexOfLowestNumber(int values[6]);
char *closestColorMatch(int values[6][3], int measurement[3], char *colors[6]);

int colors[6][3] = {
  {-900, -1200, -1800},  // red
  {-950, -900, -1600},   // green
  {-1150, -1100, -1550}, // blue
  {-700, -800, -1750},   // yellow
  {-700, -950, -1600},   // orange
  {-1000, -1150, -1850}  // brown
};

int measurement[3];
char *names[6] = {"red", "green", "blue", "yellow", "orange", "brown"};

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);
  
  Serial.begin(9600);
}
void loop() {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, 25, 72, 255, 0);
  
  measurement[0] = frequency;
  delay(100);
  
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, 30, 90, 255, 0);
  
  measurement[1] = frequency;
  delay(100);
  
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, 25, 70, 255, 0);
  
  measurement[2] = frequency;
  delay(100);

  Serial.println(closestColorMatch(colors, measurement, names));
}

int colorDifference(int values[3], int measurement[3]) {
  int sum = 0;
  
  for (int i = 0; i < 3; i++) {
    sum += abs(values[i] - measurement[i]);
  }
  
  return sum;
}

int indexOfLowestNumber(int values[6]) {
  int index = 0;
  
  for (int i = 0; i < 5; i++) {
    if (values[i+1] < values[index]) {
      index = i + 1;
    }
  }
  
  return index;
}

char *closestColorMatch(int values[6][3], int measurement[3], char *colors[6]) {
  int difference[6];
  
  for (int i = 0; i < 6; i++) {
    difference[i] = colorDifference(values[i], measurement);
  }
  
  return colors[indexOfLowestNumber(difference)];
}
