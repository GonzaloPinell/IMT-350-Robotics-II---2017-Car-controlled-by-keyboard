#include <SoftwareSerial.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>

#define ENA 2
#define ENB 3

#define IN1 24
#define IN2 22
#define IN3 26
#define IN4 28

#define test 13

// SoftwareSerial BT1(2, 3); // Tx1, Rx1

ros::NodeHandle node;
geometry_msgs::Twist msg;

void adelante()
{

  analogWrite(ENA, 85);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  analogWrite(ENB, 85);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
}

void izquierda()
{

  analogWrite(ENA, 85);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  
}

void parar()
{

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  
}

void derecha()
{

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  analogWrite(ENB, 85);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
}

void atras()
{

  analogWrite(ENA, 85);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  analogWrite(ENB, 85);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  
}

void roverCallBack(const geometry_msgs::Twist& cmd_vel)
{

  if(cmd_vel.linear.x > 0 && cmd_vel.angular.z == 0)
  {
    adelante(); //i
    analogWrite(test, 255);
  }
  else
  {
    if(cmd_vel.linear.x == 0 && cmd_vel.angular.z > 0)
    {
      izquierda(); //j
      analogWrite(test, 255);
    }
    else
    {
      if(cmd_vel.linear.x == 0 && cmd_vel.angular.z == 0)
      {
        parar(); //k
        analogWrite(test, 0);
      }
      else
      {
        if(cmd_vel.linear.x == 0 && cmd_vel.angular.z < 0)
        {
          derecha(); //l
          analogWrite(test, 255);
        }
        else
        {
          if(cmd_vel.linear.x < 0 && cmd_vel.angular.z == 0)
          {
            atras(); //,
            analogWrite(test, 255);
          }
          else
          {
            parar(); //default
          }
        }
      }
    }
  }
}

ros::Subscriber <geometry_msgs::Twist> sub("cmd_vel", roverCallBack);

void setup()
{

//  Serial.begin(57600);
//  BT1.begin(57600);
  
  node.initNode();
  node.subscribe(sub);
  
  pinMode(test, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
} 

void loop()
{

  digitalWrite(test, LOW);

//  if(Serial.available())
//  {
//    BT1.print((char)Serial.read());
//  } 
//  if(BT1.available())
//  {
//    Serial.print((char)BT1.read());
//  }
  
  node.spinOnce(); 
  delay(1);
}
