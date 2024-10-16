#Code released under GNU/GPL
#Taha Adeel Mohammed
#March 27,2021

#GATE 2008(CS) Q27
import numpy as np

#Sample size
simlen=int(1e6)

monday=[0]*simlen #initializing to CS on monday

tuesday = np.random.choice([0,1], simlen, p =[0.4, 0.6]) #Creates a list of len simlen and element 0 or 1 with probabilities 0.4 and 0.6 respectively
wednesday = [None] * simlen #declaring an array for wednesday
for i in range(0,simlen):
  if tuesday[i]==0: #Assigning elements to wednesday depending on elements of tuesday
    wednesday[i]=np.random.choice([0,1], p =[0.4, 0.6])
  elif tuesday[i]==1:
    wednesday[i]=np.random.choice([0,1], p =[0.4, 0.6]) #same in this case, but can be changed for different examples

count = wednesday.count(0)
prob_sim= count/simlen
prob_theory=0.4
print("Simulated probablity: ", prob_sim, "\nTheoretical probablity: ", prob_theory)
