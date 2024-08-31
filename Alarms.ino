void alarms(){
   //Alarms!!
 
  if ((bat <= 12) && (rpm >=600)){
     userscreen = 3;} 
  if ((afr >=1.0) && (kpa > 110)){
     userscreen = 0;}
  if (clt >= 100){
     userscreen = 2;}
  if (du >= 90){
     userscreen = 1;
   } 

}
