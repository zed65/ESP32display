void screens(){
  //Screens
  if (ecu == 0){
      if (userscreen > 8){
    userscreen = 0;
    }
  }

  if (ecu == 1){
      if (userscreen > 9){
    userscreen = 0;
    }
  }

 
  if (userscreen == 0){
      LambdaMeter();
      screen = 1;}
    else if (userscreen == 1){
      DutyMeter();
      screen = 1;}
    else if (userscreen == 2){
      TempMeter();
      screen = 1;}
    else if (userscreen == 3){
      VoltMeter();      
      screen = 1;}
    else if (userscreen == 4){
      TurboMeter();
      screen = 1;}
    else if (userscreen == 5){
      DigiMeter();
      screen = 1;}
    else if (userscreen == 6){
      DigiMeter3();
      screen = 1;}
    else if (userscreen == 7){
      DigiMeter2();
      screen = 1;} 
    else if (userscreen == 8){
      DigiMeter4();
      screen = 1;}
    else if (userscreen == 9){
      CorrMeter();
      screen = 1;}            
     //yield();
}
