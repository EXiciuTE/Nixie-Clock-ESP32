void pin_setup(void){
  pinMode(m01,OUTPUT);
  digitalWrite(m01,LOW);
  pinMode(m02,OUTPUT);
  digitalWrite(m02,LOW);
  pinMode(m03,OUTPUT);
  digitalWrite(m03,LOW);
  pinMode(m04,OUTPUT);
  digitalWrite(m04,LOW);

  pinMode(m10,OUTPUT);
  digitalWrite(m10,LOW);
  pinMode(m20,OUTPUT);
  digitalWrite(m20,LOW);
  pinMode(m30,OUTPUT);
  digitalWrite(m30,LOW);
  pinMode(m40,OUTPUT);
  digitalWrite(m40,LOW);

  pinMode(h01,OUTPUT);
  digitalWrite(h01,LOW);
  pinMode(h02,OUTPUT);
  digitalWrite(h02,LOW);
  pinMode(h03,OUTPUT);
  digitalWrite(h03,LOW);
  pinMode(h04,OUTPUT);
  digitalWrite(h04,LOW);

  pinMode(h10,OUTPUT);
  digitalWrite(h10,LOW);
  pinMode(h20,OUTPUT);
  digitalWrite(h20,LOW);
  pinMode(h30,OUTPUT);
  digitalWrite(h30,LOW);
  pinMode(h40,OUTPUT);
  digitalWrite(h40,LOW);

  pinMode(SHDN,OUTPUT);
  digitalWrite(SHDN,LOW);
  
}

void show_num(int tube, int number){  //0=h10;1=h01;2=m10;3=m01
  switch(tube){
    case 1: if(number==0){digitalWrite(h10,0);digitalWrite(h20,0);digitalWrite(h30,0);digitalWrite(h40,0);}
       else if(number==1){digitalWrite(h10,0);digitalWrite(h20,0);digitalWrite(h30,0);digitalWrite(h40,1);}
       else if(number==2){digitalWrite(h10,0);digitalWrite(h20,0);digitalWrite(h30,1);digitalWrite(h40,0);}
       else if(number==3){digitalWrite(h10,0);digitalWrite(h20,0);digitalWrite(h30,1);digitalWrite(h40,1);}
       else if(number==4){digitalWrite(h10,0);digitalWrite(h20,1);digitalWrite(h30,0);digitalWrite(h40,0);}
       else if(number==5){digitalWrite(h10,0);digitalWrite(h20,1);digitalWrite(h30,0);digitalWrite(h40,1);}
       else if(number==6){digitalWrite(h10,0);digitalWrite(h20,1);digitalWrite(h30,1);digitalWrite(h40,0);}
       else if(number==7){digitalWrite(h10,0);digitalWrite(h20,1);digitalWrite(h30,1);digitalWrite(h40,1);}
       else if(number==8){digitalWrite(h10,1);digitalWrite(h20,0);digitalWrite(h30,0);digitalWrite(h40,0);}
       else if(number==9){digitalWrite(h10,1);digitalWrite(h20,0);digitalWrite(h30,0);digitalWrite(h40,1);}
       else if(number==10){digitalWrite(h10,1);digitalWrite(h20,1);digitalWrite(h30,1);digitalWrite(h40,1);}  //OFF
       break;
    case 2: if(number==0){digitalWrite(h01,0);digitalWrite(h02,0);digitalWrite(h03,0);digitalWrite(h04,0);}
       else if(number==1){digitalWrite(h01,0);digitalWrite(h02,0);digitalWrite(h03,0);digitalWrite(h04,1);}
       else if(number==2){digitalWrite(h01,0);digitalWrite(h02,0);digitalWrite(h03,1);digitalWrite(h04,0);}
       else if(number==3){digitalWrite(h01,0);digitalWrite(h02,0);digitalWrite(h03,1);digitalWrite(h04,1);}
       else if(number==4){digitalWrite(h01,0);digitalWrite(h02,1);digitalWrite(h03,0);digitalWrite(h04,0);}
       else if(number==5){digitalWrite(h01,0);digitalWrite(h02,1);digitalWrite(h03,0);digitalWrite(h04,1);}
       else if(number==6){digitalWrite(h01,0);digitalWrite(h02,1);digitalWrite(h03,1);digitalWrite(h04,0);}
       else if(number==7){digitalWrite(h01,0);digitalWrite(h02,1);digitalWrite(h03,1);digitalWrite(h04,1);}
       else if(number==8){digitalWrite(h01,1);digitalWrite(h02,0);digitalWrite(h03,0);digitalWrite(h04,0);}
       else if(number==9){digitalWrite(h01,1);digitalWrite(h02,0);digitalWrite(h03,0);digitalWrite(h04,1);}
       else if(number==10){digitalWrite(h01,1);digitalWrite(h02,1);digitalWrite(h03,1);digitalWrite(h04,1);}  //OFF
       break;
    case 3: if(number==0){digitalWrite(m10,0);digitalWrite(m20,0);digitalWrite(m30,0);digitalWrite(m40,0);}
       else if(number==1){digitalWrite(m10,0);digitalWrite(m20,0);digitalWrite(m30,0);digitalWrite(m40,1);}
       else if(number==2){digitalWrite(m10,0);digitalWrite(m20,0);digitalWrite(m30,1);digitalWrite(m40,0);}
       else if(number==3){digitalWrite(m10,0);digitalWrite(m20,0);digitalWrite(m30,1);digitalWrite(m40,1);}
       else if(number==4){digitalWrite(m10,0);digitalWrite(m20,1);digitalWrite(m30,0);digitalWrite(m40,0);}
       else if(number==5){digitalWrite(m10,0);digitalWrite(m20,1);digitalWrite(m30,0);digitalWrite(m40,1);}
       else if(number==6){digitalWrite(m10,0);digitalWrite(m20,1);digitalWrite(m30,1);digitalWrite(m40,0);}
       else if(number==7){digitalWrite(m10,0);digitalWrite(m20,1);digitalWrite(m30,1);digitalWrite(m40,1);}
       else if(number==8){digitalWrite(m10,1);digitalWrite(m20,0);digitalWrite(m30,0);digitalWrite(m40,0);}
       else if(number==9){digitalWrite(m10,1);digitalWrite(m20,0);digitalWrite(m30,0);digitalWrite(m40,1);}
       else if(number==10){digitalWrite(m10,1);digitalWrite(m20,1);digitalWrite(m30,1);digitalWrite(m40,1);}  //OFF
       break;
    case 4: if(number==0){digitalWrite(m01,0);digitalWrite(m02,0);digitalWrite(m03,0);digitalWrite(m04,0);}
       else if(number==1){digitalWrite(m01,0);digitalWrite(m02,0);digitalWrite(m03,0);digitalWrite(m04,1);}
       else if(number==2){digitalWrite(m01,0);digitalWrite(m02,0);digitalWrite(m03,1);digitalWrite(m04,0);}
       else if(number==3){digitalWrite(m01,0);digitalWrite(m02,0);digitalWrite(m03,1);digitalWrite(m04,1);}
       else if(number==4){digitalWrite(m01,0);digitalWrite(m02,1);digitalWrite(m03,0);digitalWrite(m04,0);}
       else if(number==5){digitalWrite(m01,0);digitalWrite(m02,1);digitalWrite(m03,0);digitalWrite(m04,1);}
       else if(number==6){digitalWrite(m01,0);digitalWrite(m02,1);digitalWrite(m03,1);digitalWrite(m04,0);}
       else if(number==7){digitalWrite(m01,0);digitalWrite(m02,1);digitalWrite(m03,1);digitalWrite(m04,1);}
       else if(number==8){digitalWrite(m01,1);digitalWrite(m02,0);digitalWrite(m03,0);digitalWrite(m04,0);}
       else if(number==9){digitalWrite(m01,1);digitalWrite(m02,0);digitalWrite(m03,0);digitalWrite(m04,1);}
       else if(number==10){digitalWrite(m01,1);digitalWrite(m02,1);digitalWrite(m03,1);digitalWrite(m04,1);}  //OFF
       break;       
    default: break; 
  }
}
