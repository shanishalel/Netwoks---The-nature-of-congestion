# Netwoks---The-nature-of-congestion
In this implemetion we explore the performance of two different buffer management policies:
* Early-Deadline-First (EDF) 
* Bounded-delay
Each buffer management policy, managing a single queue is defined by admission policy defining which packets can be admitted and processing policy
that defines in which order the buffered packets are processed.

## Examples :
Input_file example:  
(2,3,6) (3,4,1)  
(2,4,5)  
At each time slot the packets are admitted from left to right. For example, (2,3,6) and only later (3,4,1).  
The number of lines in the file defines a number of time slots in the run. The given file contains arrivals
during two time slots.  
  
For an input file each run returns:  
Expected output:  
Total arrived packets %d, total dropped packets %d, total transmitted packets %d, total transmitted value
%d.  
The target for EDF is named edf and for the Bounded-delay is named bd. 
  
Input_file example:  
(2,3,6) (3,4,1)  
(3,4,5)  
Running example: edf 4 input_file  
Total arrived packets 8, total dropped packets 4, total transmitted packets 4, total transmitted value 17.  
