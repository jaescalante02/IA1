
import sys
import random

tab= [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24]
pos=0
moves = int(sys.argv[1])
i=0

while(i<moves):

  mov = random.randrange(1, 5, 1)
 # print mov, tab[pos],pos
  if((mov==1)and(pos>=5)):
    tab[pos] = tab[pos-5]
    tab[pos-5] = 0
    pos=pos-5 
    i+=1
  elif((mov==2)and(pos%5)):
    tab[pos] = tab[pos-1]
    tab[pos-1] = 0
    pos=pos-1  
    i+=1
  elif((mov==3)and(pos%5 != 4)):
    tab[pos] = tab[pos+1]
    tab[pos+1] = 0
    pos=pos+1
    i+=1      
  elif((mov==4)and(pos<20)):
    tab[pos] = tab[pos+5]
    tab[pos+5] = 0
    pos=pos+5    
    i+=1
for j in range(0,25):
  sys.stdout.write(str(tab[j]))
  sys.stdout.write(' ')   
print ''
  
 
