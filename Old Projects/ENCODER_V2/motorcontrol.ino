void motor (int safe)
{
if (safe== 0)
{
        digitalWrite(motor_direction, LOW); 
        digitalWrite(motor_step, HIGH); 
        digitalWrite(motor_step, LOW);
        delay(2000);
        return;
        }

var = switches_abc;
switch(var)
{
 case 1:  // switch a at pin 9 makes motor turn clockwise
 while (encoder > 0) 
    { 
        digitalWrite(motor_direction, HIGH); 
        digitalWrite(motor_step, HIGH); 
        digitalWrite(motor_step, LOW); 
        delay(2000); 
        motor_position++; 
        encoder = 0; 
    }
 break;
 
 case 2:  // switch b at pin 10 makes motor turn anticlockwise
 while (encoder < 0) 
    {
        digitalWrite(motor_direction, LOW); 
        digitalWrite(motor_step, HIGH); 
        digitalWrite(motor_step, LOW); 
        delay(2000); 
        motor_position--; 
        encoder = 0; 
    } 
    break;
case 3:  //motor comes to the mean positon with the secound limit switch is activated
while (x==1)
{
  while(encoder < 0) 
    {
        digitalWrite(motor_direction, LOW); 
        digitalWrite(motor_step, HIGH); 
        digitalWrite(motor_step, LOW); 
        delay(2000); 
        motor_position--; 
        encoder = 0; 
    } 
}
break;
}
  
}
