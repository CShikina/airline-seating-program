# Airplane Seating Program
## Objective 
An Airplane seating program that could accommodate 40 passengers, having 10 rows and 4 columns. It must satisfy the following requirement: (A) Seat reservation, (B) Change seats, (C) Cancel selected seat, (D) Display available seat.

>**Compiling**: This is programmed using C. The file name for the file pointer is “seats.txt”

## Operations
Operation | Description 
-------- | -----------
Create file (reset) | This will reset the file (plane.txt), overwriting the contents of it. After prompting this operation, all the seats will be set to unoccupied.
Display seats | This will display the availability of the seats. If the seats are full, a comment “Airplane is full” will be printed at the bottom section of the program.
Reserve a seat | This will prompt the user to select a seat. If the selected seat is unavailable, the program will prompt the user to select another seat.
Change seats | This will change the selected seat of the user. The program will prompt the user to type-in their current seat then make them select a new seat as a replacement for the previous seat. If the given current seat is not yet reserved, the user will choose whether to continue with the reservation or not.
Cancel a seat | This will free up the selected seat. If the selected seat is not yet reserved, the program will print “No one has reserved this seat yet.”
Exit program | This will terminate the program.

