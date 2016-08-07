int IN[], NA[];
sum1, sum2
float min;
int fish[] = {2, 5, 7, 11, 30, 35, 1, 1, 69, 9}
int n = 10;
float dif;
void setup() {
  // put your setup code here, to run once:
  

  int j = 0, sum = 0;
  float avg;
  avg = sumation(n , fish)/2
  sort();
}

void sort(){
  int int i, j, tmp;
  for(i=0; i<n; i++){
    for(j=0; i<n;j++){
      if(fish[i]>fish[j]){
        tmp = fish[i];
        fish[i] = fish[j];
        fish[j] = tmp;
      }
    }
  }
}

void recur(int choose, int deep){
  if(choose)sum += fish[i];
  recur(1, deep-1);
  recur(0, deep-1);
  sumation(9-deep,)
}



int sumation(int n, int ary[]){
  int sum = 0, i = 0;
  for(i=0;i<n;i++) {
    sum += ary[i];
  }
  return sum;
}

void loop() {
  // put your main code here, to run repeatedly:
    
}
