
void moveForward(double input)
{
  digitalWrite(M1A, HIGH);
  digitalWrite(M1B, LOW);
  digitalWrite(M2A, HIGH);
  digitalWrite(M2B, LOW);
  analogWrite(M1in, input);
  analogWrite(M2in, input);
  Serial.print("moving Forward: voltage = ");
  Serial.println(input);

}
void moveBackward(double input2)
{
  digitalWrite(M1A, LOW);
  digitalWrite(M1B, HIGH);
  digitalWrite(M2A, LOW);
  digitalWrite(M2B, HIGH);
  analogWrite(M1in, input2);
  analogWrite(M2in, input2);
  Serial.print("moving Backward: voltage = ");
  Serial.println(input2);
}
void Stop()
{
  analogWrite(M1in, 0);
  analogWrite(M2in, 0);
  Serial.println("STOPPED");
}
