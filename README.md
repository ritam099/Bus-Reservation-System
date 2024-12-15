# Bus-Reservation-System
## Key Features
- Admin Module:
- Authentication:
- Admin logs in using predefined credentials (admin12 and admin123).
## Bus Management:
- Add new buses, specifying details like bus number, boarding point, drop locations, number of seats, and timings.
- View bus details sorted in ascending order of bus numbers.
## User Management:
- Add new users to the system with a unique ID, username, password, and phone number.
- View all users sorted by their usernames.
## User Module:
- Authentication:
- Users log in with their registered username and password.
- Booking Tickets:
- Select boarding and drop-off points.
- Choose the number of seats, date of travel, and boarding time.
- Ticket cost is calculated dynamically (₹100 per drop point).
- Booking updates the number of available seats for the bus.
## View Tickets:
- Users can view their previously booked tickets with details like ticket ID, boarding/drop points, bus number, price, seats, date, and time.
- 
## Program Highlights
## Data Storage:
- Bus details are stored in a binary file (bus).
- User details are stored in userDetails.
- Ticket details are saved in ticketDetails.
  
## Sorting Mechanism:
- Bus and user details are sorted (ascending order) before display.
  
## Error Handling:
- Handles cases where files are not found.
- Ensures valid input for critical choices (e.g., boarding/drop points, dates).
  
## Dynamic Memory Allocation:
- Uses malloc to dynamically allocate memory for bus, user, and ticket data.

## Random Ticket ID Generation:
- Each ticket is assigned a unique ticket_id using the rand() function.

## Custom Struct Definitions:
-Structures for users (user), buses (bus), tickets (ticket), and dates (dates) to manage data efficiently.
